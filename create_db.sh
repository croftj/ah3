#!/usr/bin/ksh
set -x

######################################################################
#   Make sure the server database files are initialized              #
######################################################################
/etc/rc.d/postgresql status
if [ $? != 0 ]
then
   echo "Starting database";
   /etc/rc.d/postgresql start
else
   echo "Database already started";
fi

######################################################################
#   Apply patch to enable accessing postgres by socket               #
######################################################################
cd /etc/sysconfig
patch </opt/ah3/patches/postgres-sysconfig.patch

######################################################################
#   Apply  patch to set authentication to 'trust' for local network  #
#   connections                                                      #
######################################################################
cd ~postgres/data
su -c "patch </opt/ah3/patches/pg_hba.patch" postgres

######################################################################
#   Restart the server                                               #
######################################################################
/etc/rc.d/postgresql reload

######################################################################
#   Create  the  user  ah3, database ah3 then populate the database  #
#   with the required tables to start with                           #
######################################################################
su -c "createuser -h localhost --createdb --no-createrole --no-superuser ah3" postgres

su -c "createdb -h localhost --owner ah3 ah3" postgres

su -c "psql -h localhost --user ah3 ah3 < /opt/ah3/database/ah3.psql" postgres



