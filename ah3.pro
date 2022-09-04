#################################################################################
##
##   $Id$
##   Copyright (c) 2005 Joe Croft joe@croftj.net
##   
##   This file is part of Shelfpro.
##
##   Shelfpro is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation; either version 2 of the License, or
##   (at your option) any later version.
##
##   Foobar is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public License
##   along with Foobar; if not, write to the Free Software
##   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##
#################################################################################

#TEMPLATE   = app
#LANGUAGE   = C++
#
#CONFIG  += qt warn_on release
#
DEFINES     += QT3_SUPPORT DEFAULT_DB_TYPE=\"QPSQL\" NO_PHOTO_SELECT

QT          += xml widgets sql printsupport network
#QT          += xml qt3support sql network

RC_FILE     =  ah3-icon.rc

RESOURCES   += ah3.qrc

INCLUDEPATH += /usr/include/Qt

HEADERS     += \
         QcjData/QcjAction.h \
         QcjData/QcjDataFrame.h \
         QcjData/QcjDataForm.h \
         QcjData/QcjDataSqlTable.h \
         QcjData/QcjDataTable.h \
         QcjData/QcjDataStatics.h \
         QcjData/QcjDataDelegate.h \
         QcjData/QcjDataConfigure.h \
         QcjData/QcjDataHelpers.h \
         QcjData/QcjDataLogin.h \
         QcjData/QcjDataReport.h \
         QcjData/QcjDataReportDocument.h \
         QcjData/QcjDataSheet.h \
         QcjData/QcjDataXML.h \
         QcjData/Qcjdoubleentry.h \
         QcjData/Qcjfileentry.h \
         QcjData/Qcjintegerentry.h \
         QcjData/Qcjsinglelineentry.h \
         QcjData/Qcjtruefalse.h \
         QcjData/Qcjyesnoentry.h \
         customerentrydialog.h \
         inventoryframe.h \
         parts.h \
         partselect.h \
         vehicleentrydialog.h \
         wolaborentry.h \
         wolaborentrydialog.h \
         wopartentry.h \
         wopartentrydialog.h \
         vendors.h \
         vendorselect.h \
         laborselect.h \
         workorderselect.h \
         jobparts.h \
         autojob.h \
         about.h \
         ah3.h

FORMS    += \
         QcjData/QcjDataConfigure.ui \
         QcjData/QcjDataLogin.ui \
         QcjData/QcjDataReport.ui \
         QcjData/Qcjdoubleentry.ui \
         QcjData/Qcjfileentry.ui \
         QcjData/Qcjintegerentry.ui \
         QcjData/Qcjsinglelineentry.ui \
         QcjData/Qcjtruefalse.ui \
         QcjData/Qcjyesnoentry.ui \
         customerentrydialog.ui \
         inventoryframe.ui \
         parts.ui \
         partselect.ui \
         vehicleentrydialog.ui \
         vendors.ui \
         vendorselect.ui \
         wolaborentry.ui \
         wolaborentrydialog.ui \
         wopartentry.ui \
         wopartentrydialog.ui \
         laborselect.ui \
         workorderselect.ui \
         jobparts.ui \
         autojob.ui \
         about.ui \
         ah3.ui

SOURCES  += \
         QcjData/QcjDataFrame.cpp \
         QcjData/QcjDataForm.cpp \
         QcjData/QcjDataSqlTable.cpp \
         QcjData/QcjDataTable.cpp \
         QcjData/QcjDataStatics.cpp \
         QcjData/QcjDataXML.cpp \
         QcjData/QcjDataConfigure.cpp \
         QcjData/QcjDataLogin.cpp \
         QcjData/QcjDataHelpers.cpp \
         QcjData/QcjDataReport.cpp \
         QcjData/QcjDataReportDocument.cpp \
         QcjData/QcjDataSheet.cpp \
         QcjData/Qcjdoubleentry.cpp \
         QcjData/Qcjfileentry.cpp \
         QcjData/Qcjintegerentry.cpp \
         QcjData/Qcjsinglelineentry.cpp \
         QcjData/Qcjtruefalse.cpp \
         QcjData/Qcjyesnoentry.cpp \
         customerentrydialog.cpp \
         inventoryframe.cpp \
         vehicleentrydialog.cpp \
         wopartentry.cpp \
         laborselect.cpp \
         workorderselect.cpp \
         jobparts.cpp \
         autojob.cpp \
#        ah3_job.cpp \
#        ah3_makes.cpp \
         ah3.cpp \
         main.cpp


target.path = ah3
sources.path = .
sources.files = $$FORMS *.pro $$SOURCES $$HEADERS $$RESOURCES

INSTALLS += target sources

bin.path        = /usr/bin
bin.files       = ah3

icons.path      = /opt/ah3/icons
icons.files     = ah3-small.png ah3-small.xpm

conf.path       = /opt/ah3/conf
conf.files      = ah3.xml

sql.path        = /opt/ah3/database
sql.files       = ah3.psql

docs.path       = /opt/ah3/docs
docs.files      = COPYING

desktop.path    = /opt/kde3/share/applnk/Application
desktop.files   = ah3.desktop

rpm.target      = rpm
rpm.commands    = rpmbuild -ba ah3.spec

INSTALLS        += icons conf sql docs desktop

QMAKE_EXTRA_UNIX_TARGETS +=  rpm install

