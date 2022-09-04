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
# include "customerentrydialog.h"
# include "vehicleentrydialog.h"

void CustomerEntryDialog::haveDeleteCustomerBtn()
{
   printf("CustomerEntryDialog::haveDeleteCustomerBtn(): Enter\n");
   fflush(stdout);
   QString xmldef = ui.customerForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);
   QString index_value = ui.customerForm->getFieldText(index);
   QString sql = "select count(*) from workorders where customer = :index";
   QSqlQuery q;
   printf("CustomerEntryDialog::haveDeleteCustomerBtn(): sql = |%s|, index = |%s|\n", qPrintable(sql), qPrintable(index_value));
   fflush(stdout);
   q.prepare(sql);
   q.bindValue(":index", index_value);
   q.exec();
   if ( q.next() ) 
   {
      int count = q.value(0).toInt();
      printf("CustomerEntryDialog::haveDeleteCustomerBtn(): count = %d\n", count);
      fflush(stdout);
      if ( count > 0 ) 
      {
         QMessageBox::warning(NULL, "Error", "This customer has existing workorders and cannot be deleted\n", 
                                 QMessageBox::Ok | QMessageBox::Default);
         printf("CustomerEntryDialog::haveDeleteCustomerBtn(): Exit- no record deleted\n");
         fflush(stdout);
         return;
      }

   }
   ui.customerForm->deleteRecord();
   printf("CustomerEntryDialog::haveDeleteCustomerBtn(): Exit\n");
   fflush(stdout);
}

void CustomerEntryDialog::haveViewVehiclesBtn()
{
   printf("CustomerEntryDialog::haveViewVehiclesBtn(): Enter\n");
   fflush(stdout);
   QString xmldef = ui.customerForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);
   QString index_value = ui.customerForm->getFieldText(index);

   VehicleEntryDialog dlg(index_value.toInt(), false, this);
   printf("CustomerEntryDialog::haveViewVehiclesBtn(): Setting database\n");
   fflush(stdout);
   dlg.setDatabase();
   dlg.exec();
   printf("CustomerEntryDialog::haveViewVehiclesBtn(): Exit\n");
   fflush(stdout);
   
}

