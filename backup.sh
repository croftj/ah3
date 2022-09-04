#!/bin/bash
#set -x

bu_dev=`findfs LABEL=Ah3-Backup`
if [ "$bu_dev" == "" ]
then
   echo
   echo
   echo "           NO Backup Device Found! "
   echo
   echo
   exit 1
fi

set -x
umount $bu_dev
mount $bu_dev /mnt
rm -rf /mnt/save
mkdir /mnt/save
mv /mnt/* /mnt/save


######################################################################
#   Start by creating the data encryption script encrypt
######################################################################
cat >/tmp/encrypt <<END;
#!/usr/bin/perl

use Crypt::CBC;

#
# The parameter -key should probably be changed here! Something you can remember, but
# not too easily guessed
#
\$cipher = Crypt::CBC->new( -key    => 'joey',
                           -cipher => 'Blowfish'
                           );

\$cipher->start('encrypting');
open(F,"pg_dump -U ah3 -h localhost --create ah3 |");
while (read(F,\$buffer,1024)) {
      print \$cipher->crypt(\$buffer);
}
print \$cipher->finish;
END

######################################################################
#   Now encryt the database and save it on the flash drive
######################################################################
perl /tmp/encrypt >/mnt/database.db

rm /tmp/encrypt

######################################################################
#   Put simple instructions out to the flash drive
######################################################################
cd /mnt
cat >README.txt <<END;
Restoration of the Autohouse system in a nutshell.

Install the basic SuSE-10.3. If the network is connected, be sure to select
the OSS and Non OSS comunity sources.

Ensure the following packages are installed:

   libqt4
   libqt4-X11
   libqt4-sql
   libqt4-sql-postgresql
   perl-Crypt-CBC
   perl-Crypt-Blowfish
   perl-Crypt-DES
   postgresql
   postgresql-server
   postgresql-libs
   unix2dos

IF NO NETWORK IS AVAILABLE AND ANY OF THESE PACKAGES ARE MISSING, copies of them can 
be found the accompanying CD and installed manually.

During the installation, when queried, create a regular user for the ah3 program to
be run from.

Log in as root.

Plug in the flash card and change into the directory it is mounted to.

Execute the following command:

   ./restore.sh

When asked, enter your friends name for the password.

After the script runs, there are a couple of tar files with configuration data:

   The home/<user>/.config/CroftJ/ah3.conf file is name <user>-ah3.conf
   The /home/<user>/.xml directory is in the tar file <user>-xml.tar.gz
   The directort /opt/ah3 is in the tar file ah3-opt.tar.gz

These files need to be gone through and restored as appropriate.

The system should not be ready to run.

END

unix2dos README.txt


######################################################################
#   Create the restor.sh script and save it to the flash
######################################################################
cat >restore.sh <<END;
#!/bin/bash
set -x

FLASH=\`pwd\`

for pkg in `ls *.rpm`
do
   rpm -iv --hash $pkg
done

cd /etc/rc.d/rc3.d
ln -s ../postgresql S09postgresql
ln -s ../postgresql K13postgresql

cd /etc/rc.d/rc5.d
ln -s ../postgresql S09postgresql
ln -s ../postgresql K13postgresql

echo "/opt/ah3/bin/backup.sh" >>/etc/init.d/halt.local

/etc/rc.d/postgresql start

cd \$FLASH

./decrypt.pl database.db >/opt/ah3/database.db

cat >~postgres/data/pg_hba.conf <<EOF;
host all all 127.0.0.1/32 trust
local all all ident sameuser
host all all ::1/128 ident sameuser
EOF

echo "POSTGRES_OPTIONS=\"-i\"" >>/etc/sysconfig/postgresql

/etc/rc.d/postgresql restart

su -c "createuser --no-superuser --createdb --login --no-createrole ah3" postgres

/etc/rc.d/postgresql reload

psql -U ah3 -h localhost template1 </opt/ah3/database.db
END

######################################################################
#   Set it's execution bits
######################################################################
chmod +x restore.sh

######################################################################
#   Create the decryption script
######################################################################
cat >decrypt.pl <<END;
#!/usr/bin/perl

use Crypt::CBC;

print STDERR "\n\nEnter Password: ";
\$pw = readline STDIN;
chomp \$pw;

\$cipher = Crypt::CBC->new( -key    => \$pw,
                           -cipher => 'Blowfish'
                           );

\$cipher->start('decrypting');
open(F, \$ARGV[0]);
open(OUT, ">/opt/ah3/database.db" );
while (read(F, \$buffer, 1024)) {
      print \$cipher->crypt(\$buffer);
}
print \$cipher->finish;

END


chmod +x decrypt.pl

######################################################################
#   Copy and RPM packages out to the flash
######################################################################
cp /opt/ah3/rpms/* .

######################################################################
#   As well as any user's ah3 configuration files
######################################################################
for user in `ls /home`
do
   cd /home/$user
   cp .config/CroftJ/ah3.conf /mnt/$user-ah3.conf
   tar -czf /mnt/$user-xml.tar.gz .xml/
done

######################################################################
#   Get the entire /opt/ah3 directory
######################################################################
cd /opt
tar -czf /mnt/ah3-opt.tar.gz ah3


######################################################################
#   And we are done, make sure the data gets written to the flash
######################################################################
umount $bu_dev

