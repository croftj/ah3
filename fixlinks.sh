#!//bin/bash
set -x
pwd

echo "arg 1:" $1
echo "arg 2:" $2
echo "arg 3:" $3

dn=`dirname $0`
cd $dn
for fn in `ls *.so.4.3.1`
do
   ln -s `echo $fn | cut -d '.' -f 1`.so.4.3.1 `echo $fn | cut -d '.' -f 1`.so.4.3
   ln -s `echo $fn | cut -d '.' -f 1`.so.4.3 `echo $fn | cut -d '.' -f 1`.so.4
done
ln -s libpq.so.5.0 libpq.so.5
ln -s libpq.so.5 libpq.so

cat >./Ah3 <<END
cd $dn
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./ah3
END
chmod +x ./Ah3

cat >./Ah3xs <<END
cd $dn
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./ah3xs
END
chmod +x ./Ah3xs

cat >./ah3xs.desktop <<END
# KDE Config File  
[KDE Desktop Entry]
Type=Application
Exec=$dn/Ah3xs
Icon=$dn/icons/ah3xs-48.png
Comment=AutoHouse (Small Screen)
Comment[de]=
Terminal=0
Name=AutoHouse (Small Screen)
Name[de]=AutoHouse (Small Screen)
Categories=Office
END

cat >./ah3.desktop <<END
# KDE Config File  
[KDE Desktop Entry]
Type=Application
Exec=$dn/Ah3
Icon=$dn/icons/ah3-48.png
Comment=AutoHouse (Small Screen)
Comment[de]=
Terminal=0
Name=AutoHouse (Small Screen)
Name[de]=AutoHouse (Small Screen)
Categories=Office
END

exit
