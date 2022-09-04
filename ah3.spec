#*********************************************************************************
# 
#    $Id$
#    Copyright (c) 2004 Joe Croft <joe@croftj.net>
#    
#    This file is part of ah2.
# 
#    ah2 is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
# 
#    Foobar is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
# 
#    You should have received a copy of the GNU General Public License
#    along with Foobar; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# 
#*******************************************************************************/

Summary: Invoicing and Inventory System for Repair Shops
Name: ah3
#*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*
#
# The Version needs to be changed here. The version
# should match what was given when the release line
# was droped from perforce.
#
#*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*
Version: beta9
Release: 1
License: GPL
BuildRequires: qt-devel >= 4.3
Source0: %{name}.tar.gz
Group: Applications/Productivity
BuildRoot: %{_tmppath}/%{name}-build
Vendor: CroftJ Internet Services


%description
The ah3 program maintains customer and item records for repair shops. It provides a means of 
entering workorders and generating invoices for the customers. It has inventory management to track
stock. It also provides a flexible means of creating and generating reports.

%prep

%build

pwd
tar -xzf %{SOURCE}
cd %{name}
qmake %{name}.pro  
make  
qmake %{name}xs.pro  
make clean  
make  
  
%install  
cd %{name}
mkdir -p $RPM_BUILD_ROOT/opt/%{name}/reports  
mkdir -p $RPM_BUILD_ROOT/opt/%{name}/bin  
mkdir -p $RPM_BUILD_ROOT/opt/%{name}/icons  
mkdir -p $RPM_BUILD_ROOT/opt/%{name}/docs  
mkdir -p $RPM_BUILD_ROOT/opt/%{name}/conf  
mkdir -p $RPM_BUILD_ROOT/opt/%{name}/patches  
mkdir -p $RPM_BUILD_ROOT/opt/%{name}/rpms  
mkdir -p $RPM_BUILD_ROOT/usr/bin  
mkdir -p $RPM_BUILD_ROOT/usr/lib/perl5/site_perl  
mkdir -p $RPM_BUILD_ROOT/opt/%{name}/database  
mkdir -p $RPM_BUILD_ROOT/opt/kde3/share/applnk/Application/  
  
install -s -m 755 %{name}                    $RPM_BUILD_ROOT/usr/bin/%{name}  
install -s -m 755 %{name}xs                   $RPM_BUILD_ROOT/usr/bin/%{name}xs  
install -m 644 %{name}.psql                  $RPM_BUILD_ROOT/opt/%{name}/database/%{name}.psql  
install -m 644 example_db.sql             $RPM_BUILD_ROOT/opt/%{name}/database/example_db.sql  
install -m 644 %{name}-48.png            $RPM_BUILD_ROOT/opt/%{name}/icons/%{name}-48.png  
install -m 644 %{name}-48.xpm            $RPM_BUILD_ROOT/opt/%{name}/icons/%{name}-48.xpm  
install -m 644 %{name}xs-48.png              $RPM_BUILD_ROOT/opt/%{name}/icons/%{name}xs-48.png  
install -m 644 %{name}xs-48.xpm              $RPM_BUILD_ROOT/opt/%{name}/icons/%{name}xs-48.xpm  
install -m 644 COPYING                      $RPM_BUILD_ROOT/opt/%{name}/docs/COPYING  
install -m 644 CHANGES.TXT              $RPM_BUILD_ROOT/opt/%{name}/docs/CHANGES.TXT  
install -m 644 invoice.xml                 $RPM_BUILD_ROOT/opt/%{name}/reports/invoice.xml  
install -m 644 annualsales.xml           $RPM_BUILD_ROOT/opt/%{name}/reports/annualsales.xml  
install -m 644 salestotals.xml           $RPM_BUILD_ROOT/opt/%{name}/reports/salestotals.xml  
install -m 644 %{name}.xml                 $RPM_BUILD_ROOT/opt/%{name}/default_forms.xml  
install -m 644 %{name}.desktop           $RPM_BUILD_ROOT/opt/kde3/share/applnk/Application/%{name}.desktop  
install -m 644 %{name}.desktop           $RPM_BUILD_ROOT/opt/kde3/share/applnk/Application/%{name}xs.desktop  
install -m 644 docs/userman.pdf           $RPM_BUILD_ROOT/opt/%{name}/docs/userman.pdf  
install -m 644 docs/userman.xml           $RPM_BUILD_ROOT/opt/%{name}/docs/userman.xml  
install -m 644 pg_hba.patch               $RPM_BUILD_ROOT/opt/%{name}/patches/pg_hba.patch  
install -m 644 postgres-sysconfig.patch   $RPM_BUILD_ROOT/opt/%{name}/patches/postgres-sysconfig.patch  
install -m 644 create_db.sh               $RPM_BUILD_ROOT/opt/%{name}/create_db.sh  
install -m 644 backup.sh                  $RPM_BUILD_ROOT/opt/%{name}/bin/backup.sh  
  
cd $RPM_BUILD_ROOT/opt/  
ln -s %{name} %{name}xs  
  
%clean  
  
%files  
%attr(-, root, root) /usr/bin/%{name}  
%attr(-, root, root) /usr/bin/%{name}xs  
%attr(-, root, root) /opt/  
#%attr(-, root, root) /opt/%{name}/create_db.sh  
#%attr(-, root, root) /opt/%{name}/database/%{name}.psql  
#%attr(-, root, root) /opt/%{name}/database/example_db.sql  
#%attr(-, root, root) /opt/%{name}/icons/%{name}-48.png  
#%attr(-, root, root) /opt/%{name}/icons/%{name}-48.xpm  
#%attr(-, root, root) /opt/%{name}/icons/%{name}xs-48.png  
#%attr(-, root, root) /opt/%{name}/icons/%{name}xs-48.xpm  
#%attr(-, root, root) /opt/%{name}/docs/COPYING  
#%attr(-, root, root) /opt/%{name}/docs/CHANGES.TXT  
#%attr(-, root, root) /opt/%{name}/reports/  
#%attr(-, root, root) /opt/%{name}/reports/invoice.xml  
#%attr(-, root, root) /opt/%{name}/default_forms.xml  
#%attr(-, root, root) /opt/kde3/share/applnk/Application/%{name}.desktop  
#%attr(-, root, root) /opt/kde3/share/applnk/Application/%{name}xs.desktop  
#%attr(-, root, root) /opt/%{name}/docs/userman.pdf  
#%attr(-, root, root) /opt/%{name}/docs/userman.xml  
#%attr(-, root, root) /opt/%{name}/patches/pg_hba.patch  
#%attr(-, root, root) /opt/%{name}/patches/postgres-sysconfig.patch  
#%attr(-, root, root) /opt/%{name}/bin/backup.sh  
#%attr(-, root, root) /opt/%{name}/rpms  
#%attr(-, root, root) /opt/%{name}xs  
  
%changelog -n ah3
* Sat Apr 27 2008 - joe@croftj.net  
- Added Inventory to the Small Sceen version.
- Modified to allow setting the fields which calculate through the XML file
* Sat Apr 12 2008 - joe@croftj.net  
- Added small screen interface for systems with lower resolution displays  
- Fixed insert issues  
- Fixed errors with workorder totaling  
* Fri Oct 26 2007 - joe@croftj.net
- Added Whatis text to the remaining forms and tables.
- Added ability to have a graphic on a report.
- Bolstered documentation yet a little more.
- Changed backup.sh to have backups occur on shutdown when restoring system.
* Mon Oct 15 2007 - joe@croftj.net
- Added sales reports
- Added configuration sections to the user documentation
- Enhanced the input types for reports
- Added backup script
- Made the Dialogs which cover the main window slightly darker to help them standout
* Tue Sep 25 2007 - joe@croftj.net
- Added WhatsThis tags to help identify which dialog elements use which forms in the xml configuration file
- Modified spec file to be generic, moved original to ah3-spec.suse to keep the one for producing the open suse build
- Added files and scripts, added to the documentation for installing the database schema and configuring postgres
- Made clicking Done or pressing <Enter> on the form save any outstanding changes on the forms. Made pressing <Esc> or clicking the 'X' on the dialog frame discard any ne outstanding records.
* Mon Sep 09 2007 - joe@croftj.net
- Added User's Manual
- Added Predifiened Jobs
- Added ability to close work orders
- Fixed to not allow deleting customers and vehicles assigned to existing work orders
- Fixed ability to enter in new customers, vehicles and work orders
- Added example database (/opt/ah3/database/example_db.sql)
* Sun Aug 19 2007 - joe@croftj.net
- Fixed entering in new invoices, it is now possible
- Modified Customer and Vehicle Entry dialogs to make them more inuitive
- Modified Invoice sample to include totals and sample legalese to the bottom
- Fixed Labor and Parts entry dialogs to enter new records and assign them to the current workorder
- Fixed spec file so the default xml file is put in the proper directory when the rpm is installed.
* Thu Aug 16 2007 - joe@croftj.net
- Connected the Add Vendor Button on the Inventory tab.
- Added the missing Dialog titles
- Added spec file for the SuSE build service
- Added Appropriate icons and desktop file
