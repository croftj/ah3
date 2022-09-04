/*********************************************************************************
**
**   $Id$
**   Copyright (c) 2004 Joe Croft <joe@croftj.net>
**   
**   This file is part of ah3.
**
**   ah3 is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   (at your option) any later version.
**
**   Ah3 is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with Ah3; if not, write to the Free Software
**   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
*********************************************************************************/

# include <QMessageBox>
# include "vehicleentrydialog.h"

void VehicleEntryDialog::haveSearchVehicleBtn()
{
   QStringList sl;
   QString filter = ui.vehicleForm->makeFilter(sl);
   ui.vehicleTable->setFilter(filter);
}

void VehicleEntryDialog::haveClearVehicleBtn()
{
   if ( customer > 0 ) 
   {
      QString filter = "owner = " + QString::number(customer);
      ui.vehicleTable->setFilter(filter);
   }
   ui.vehicleForm->clearForm();
}

void VehicleEntryDialog::haveDeleteVehicleBtn()
{
   printf("VehicleEntryDialog::haveDeleteVehicleBtn(): Enter\n");
   fflush(stdout);
   QString xmldef = ui.vehicleForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);
   QString index_value = ui.vehicleForm->getFieldText(index);
   QString sql = "select count(*) from workorders where vehicle = :index";
   QSqlQuery q;
   printf("VehicleEntryDialog::haveDeleteVehicleBtn(): sql = |%s|, index = |%s|\n", qPrintable(sql), qPrintable(index_value));
   fflush(stdout);
   q.prepare(sql);
   q.bindValue(":index", index_value);
   q.exec();
   if ( q.next() ) 
   {
      int count = q.value(0).toInt();
      printf("VehicleEntryDialog::haveDeleteVehicleBtn(): count = %d\n", count);
      fflush(stdout);
      if ( count > 0 ) 
      {
         QMessageBox::warning(NULL, "Error", "This vehicle has existing workorders and cannot be deleted\n", 
                                 QMessageBox::Ok | QMessageBox::Default);
         printf("VehicleEntryDialog::haveDeleteVehicleBtn(): Exit- no record deleted\n");
         fflush(stdout);
         return;
      }
   }
   ui.vehicleForm->deleteRecord();
   printf("VehicleEntryDialog::haveDeleteVehicleBtn(): Exit\n");
   fflush(stdout);
}

