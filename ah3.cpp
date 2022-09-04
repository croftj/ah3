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

# include <QApplication>
# include <QMessageBox>

#include "QcjData/QcjDataConfigure.h"
#include "QcjData/QcjDataReport.h"
#include "QcjData/QcjDataStatics.h"

# include "vehicleentrydialog.h"
# include "partselect.h"
# include "wopartentrydialog.h"
# include "wopartentry.h"
# include "wolaborentrydialog.h"
# include "wolaborentry.h"

# include "vendorselect.h"

# ifdef XS
# include "laborselect.h"
# endif

# include "ah3.h"

extern QMap<int, QString> menuMap;
extern QString invoiceReportFn;

Ah3::Ah3()
{
   ui.setupUi(this);
   tabsEnabled = true;
};

void Ah3::setDatabase()
{
   pConfig->beginGroup("MainWindow");
   if (pConfig->value("ApplicationGeometry", QRect(0, 0, 0, 0)).toRect().height() > 0)
   {
      QRect rect = pConfig->value("ApplicationGeometry").toRect();
      printf("Ah3::setDatabase(): App Height = %d, width = %d, top = %d, left = %d\n", rect.height(), rect.width(), rect.top(), rect.left());
      move(rect.topLeft());
      resize(rect.size());
   }
   pConfig->endGroup();

# ifdef XS
//   ui.tabWidget->removeTab(5);
# endif

   printf("Ah3::setDatabase(): setting database woCustomerForm\n");
   fflush(stdout);
   ui.woCustomerForm->setDatabase();         /* wocustomer_form         */
   printf("Ah3::setDatabase(): setting database woVehicleForm\n");
   fflush(stdout);
   ui.woVehicleForm->setDatabase();          /* wovehicle_form          */
   printf("Ah3::setDatabase(): setting database workorderForm\n");
   fflush(stdout);
   ui.workorderForm->setDatabase();          /* workorder_form          */

   printf("Ah3::setDatabase(): setting database woSelectForm\n");
   fflush(stdout);
   ui.workorderSelect->setDatabase();           /* woselect_form           */
   connect(ui.workorderSelect, SIGNAL(workorderRecord(QSqlRecord*, bool)),
           this, SLOT(haveWorkorderRecord(QSqlRecord*, bool)));

   ui.workorderSelect->setInvoiceReportName(invoiceReportFn);
//   ui.woSelectForm->setDatabase();           /* woselect_form           */
//   printf("Ah3::setDatabase(): setting database woSelectTable\n");
//   fflush(stdout);
//   ui.woSelectTable->setDatabase();          /* woselect_table          */


   printf("Ah3::setDatabase(): setting up autojob and jobParts\n");
   fflush(stdout);

   ui.jobParts->setDatabase();
   ui.autoJob->setJobPartsFrame(ui.jobParts);
   ui.autoJob->setDatabase();

# ifdef XS
   printf("Ah3::setDatabase(): setting database woPartsTotalForm\n");
   fflush(stdout);
   ui.woLaborFrame->setDatabase();
   ui.woPartsFrame->setDatabase();
   ui.custInfoForm1->setDatabase();
   ui.custInfoForm2->setDatabase();
   ui.vehcInfoForm1->setDatabase();
   ui.vehcInfoForm2->setDatabase();
   connect(ui.woPartsFrame, SIGNAL(enableTabs(bool)), 
           this, SLOT(setTabEnable(bool)));
   connect(ui.woLaborFrame, SIGNAL(enableTabs(bool)), 
           this, SLOT(setTabEnable(bool)));
# else
   ui.woPartsTable->setDatabase();
   ui.woLaborTable->setDatabase();
# endif

   ui.parts->setDatabase();   /* part2vendor_part_form   */
   ui.vendors->setDatabase();   /* part2vendor_part_form   */
   ui.inventory->setDatabase();

//***   ui.part2VendorsPartForm->setDatabase();   /* part2vendor_part_form   */
//***   ui.part2VendorsVendForm->setDatabase();   /* part2vendor_vend_form   */
//***   ui.part2VendorsTable->setDatabase();      /* part2vendor_table       */

   ui.woPartsTotalForm->setDatabase();
   ui.woTaxPartsTotalForm->setDatabase();

   printf("Ah3::setDatabase(): setting database woLaborTotalForm\n");
   fflush(stdout);
   ui.woLaborTotalForm->setDatabase();

   pConfig->beginGroup("MainWindow");

   pConfig->endGroup();

   connect(ui.updateWoBtn, SIGNAL(clicked()), 
           this, SLOT(haveUpdateWoBtn()));

   connect(ui.cancelWoBtn, SIGNAL(clicked()), 
           this, SLOT(haveCancelWoBtn()));

#ifndef XS
   connect(ui.woPartsTable, SIGNAL(doubleClicked()), 
           this, SLOT(haveWoPartsRequest()));

   connect(ui.woLaborTable, SIGNAL(doubleClicked()), 
           this, SLOT(haveWoLaborRequest()));
#endif
/*
   connect(ui.addJobPartBtn, SIGNAL(clicked()), 
           this, SLOT(haveNewJobPartBtn()));

   connect(ui.deleteJobPartBtn, SIGNAL(clicked()), 
           this, SLOT(haveDeleteJobPartBtn()));

   connect(ui.saveJobPartBtn, SIGNAL(clicked()), 
           this, SLOT(haveSaveJobPartBtn()));


   connect(ui.newJobBtn, SIGNAL(clicked()), 
           this, SLOT(haveNewJobBtn()));

   connect(ui.saveJobBtn, SIGNAL(clicked()), 
           this, SLOT(haveSaveJobBtn()));

   connect(ui.deleteJobBtn, SIGNAL(clicked()), 
           this, SLOT(haveDeleteJobBtn()));

   connect(ui.searchJobBtn, SIGNAL(clicked()), 
           this, SLOT(haveSearchJobBtn()));

   connect(ui.clearJobBtn, SIGNAL(clicked()), 
           this, SLOT(haveClearJobBtn()));

   connect(ui.autoJobTable, SIGNAL(rowSelected(QSqlRecord*)), 
           this, SLOT(refreshAutoJobForm(QSqlRecord*)));
*/
//***   connect(ui.addPart2VendorBtn, SIGNAL(clicked()),
//***           this, SLOT(haveNewPart2Vendor()));

//***   connect(ui.allPart2VendorBtn, SIGNAL(stateChanged(int)),
//***           this, SLOT(haveAllParts2VendorBtnChanged(int)));

   connect(ui.tabWidget, SIGNAL(currentChanged(int)),
           this, SLOT(haveTabChanged(int)));

# ifdef XS
//   connect(ui.invPartsTable, SIGNAL(rowSelected(QSqlRecord*)), 
//           this, SLOT(havePartsRecordSelected(QSqlRecord *)));

   connect(ui.woLaborFrame, SIGNAL(updated()), 
           this, SLOT(updateWoTotals()));

   connect(ui.woPartsFrame, SIGNAL(updated()), 
           this, SLOT(updateWoTotals()));
#else
//   connect(ui.parts, SIGNAL(rowSelected(QSqlRecord*)), 
//           this, SLOT(havePartsRecordSelected(QSqlRecord *)));

#endif

   for (int tab = 0; tab < ui.tabWidget->count(); tab++)
      ui.tabWidget->setCurrentIndex(tab);
   woSelectActive();
# if 0
   # ifdef XS
      ui.tabWidget->setTabEnabled(0, true);
      ui.tabWidget->setTabEnabled(1, false);
      ui.tabWidget->setTabEnabled(2, false);
      ui.tabWidget->setTabEnabled(3, false);
      ui.tabWidget->setCurrentIndex(0);

   # else
      ui.tabWidget->setTabEnabled(0, false);
      ui.tabWidget->setCurrentIndex(1);
   # endif
# endif

};

void Ah3::close()
{
   pConfig->beginGroup("MainWindow");
   pConfig->setValue("ApplicationGeometry", geometry());
   pConfig->endGroup();
   QWidget::close();
}

void Ah3::refresh()
{
   printf("Ah3::refresh(): Enter\n");
   fflush(stdout);
   printf("Ah3::refresh(): refreshing woPartsTable\n");
   printf("Ah3::refresh(): refreshing woPartsTotalForm\n");
   ui.woPartsTotalForm->refresh(ui.workorderForm->record());
   printf("Ah3::refresh(): refreshing woTaxPartsTotalForm\n");
   ui.woTaxPartsTotalForm->refresh(ui.workorderForm->record());
   printf("Ah3::refresh(): refreshing woLaborTable\n");
#ifndef XS
   ui.woLaborTable->refresh();
   ui.woPartsTable->refresh();
#else
   ui.woLaborFrame->refresh();
   ui.woPartsFrame->refresh();
#endif
   printf("Ah3::refresh(): refreshing woLaborTotalForm\n");
   ui.woLaborTotalForm->refresh(ui.workorderForm->record());
   if ( ui.workorderForm->getFieldText("closed") != "Y" ) 
      calcTotals();
   printf("Ah3::refresh(): Exit\n");
   fflush(stdout);
}

void Ah3::saveCurrentForm()
{
/*
   printf("Ah3::saveCurrentForm(): Enter\n");
   fflush(stdout);
   QWidget *wdt = QApplication::focusWidget();
   for (QWidget *wdt1 = wdt; wdt1 != 0; wdt1 = (QWidget*)wdt1->parent()) 
   {
      printf("Ah3::saveCurrentForm(): Widget is a |%s|\n", wdt1->className());
      fflush(stdout);
      if ( QString(wdt1->className()) == QString("QcjDataForm") ) 
      {
         printf("Ah3::saveCurrentForm(): Have a form, updating record\n");
         fflush(stdout);
         QString xmldef = ((QcjDataForm*)wdt1)->readXmlDef();
         printf("Ah3::saveCurrentForm(): xmldef = |%s|\n", qPrintable(xmldef));
         if ( xmldef == "workorder_form" ||
              xmldef == "wocustomer_form" ||
              xmldef == "wovehicle_form" ) 
         {
            wdt->clearFocus();
            haveUpdateWoBtn();
            wdt->setFocus();
         }
         else 
         {
            wdt->clearFocus();
            ((QcjDataForm*)wdt1)->updateRecord();
            wdt->setFocus();
         }
         break;
      }
   }
   printf("Ah3::saveCurrentForm(): Exit\n");
   fflush(stdout);
*/
}

# if 0
void Ah3::havePartsRecordSelected(QSqlRecord *rec)
{
//# ifndef XS
   printf("Ah3::havePartsRecordSelected(): Enter\n");
   fflush(stdout);
   if ( ui.allPart2VendorBtn->checkState() == Qt::Unchecked ) 
   {
      QString filter = "master_part = " + rec->field("ident").value().toString();
      printf("Ah3::havePartsRecordSelected(): Setting filter to: |%s|\n", qPrintable(filter));
      ui.part2VendorsTable->setFilter(filter);
   }
   printf("Ah3::havePartsRecordSelected(): Exit\n");
   fflush(stdout);
//# endif
}

void Ah3::haveNewPart2Vendor()
{
//# ifndef XS
   printf("Ah3::haveNewPart2Vendor(): Enter\n");
   fflush(stdout);
   VendorSelect dlg;
   printf("Ah3::haveNewPart2Vendor(): Setting database\n");
   fflush(stdout);
   dlg.setDatabase();
   printf("Ah3::haveNewPart2Vendor(): Calling exec()\n");
   fflush(stdout);
   int vendor = dlg.exec();
   printf("Ah3::haveNewPart2Vendor(): vendor = %d\n", vendor);
   if ( vendor > 0 ) 
   {
      QMap<QString, QString> fields;
      fields.insert("vendor", QString::number(vendor));
      fields.insert("part", ui.parts->currentRecord()->field("ident").value().toString());
      ui.part2VendorsPartForm->insertRecord(fields);
      ui.part2VendorsTable->refresh();
      ui.part2VendorsTable->findRow(fields);
      ui.part2VendorsVendForm->refresh(ui.part2VendorsTable->currentRecord());
   }
   printf("Ah3::haveNewPart2Vendor(): Exit\n");
//# endif
}

void Ah3::haveAllParts2VendorBtnChanged(int)
{
# ifndef XS
   printf("Ah3::haveAllParts2VendorBtnChanged(): Enter\n");
   if ( ui.allPart2VendorBtn->checkState() == Qt::Checked ) 
   {
      QString filter = "";
      printf("Ah3::haveAllParts2VendorBtnChanged(): Setting filter to: |%s|\n", qPrintable(filter));
      ui.part2VendorsTable->setFilter(filter);
   }
   else 
   {
      QString filter = "master_part = " + ui.parts->currentRecord()->field("ident").value().toString();
      printf("Ah3::haveAllParts2VendorBtnChanged(): Setting filter to: |%s|\n", qPrintable(filter));
      ui.part2VendorsTable->setFilter(filter);
   }
   printf("Ah3::haveAllParts2VendorBtnChanged(): Exit\n");
# endif
}
# endif

/*
void Ah3::haveShowAllWoBtnChanged(int)
{
   QString filter = "";

   printf("Ah3::haveShowAllWoBtnChanged(): Enter\n");
   if ( ui.showAllWoBtn->checkState() == Qt::Unchecked ) 
   {
      filter = "closed = 'N'";
   }
   printf("Ah3::haveShowAllWoBtnChanged(): Setting filter to: |%s|\n", qPrintable(filter));
   ui.woSelectTable->setFilter(filter);
   printf("Ah3::haveShowAllWoBtnChanged(): Exit\n");
}

*/

/*
void Ah3::haveWoSelected(QSqlRecord *rec)
{
   QSqlRecord custRec;

   printf("Ah3::haveWoSelected(): Enter\n");

   ui.workorderForm->refresh(rec);
   ui.woVehicleForm->setEnabled(true);
   ui.woCustomerForm->setEnabled(true);

# ifdef XS
   ui.woPartsForm->clearForm();
   ui.woLaborFrame->clearForm();
# endif

   QString xmldef = ui.woCustomerForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);

   QSqlField custIdent(index, QVariant::Int);
   printf("Ah3::haveWoSelected(): Have customer ident |%d|\n", rec->field("customer").value().toInt());
   custIdent.setValue(rec->field("customer").value().toInt());
   custRec.append(custIdent);
   ui.woCustomerForm->refresh(&custRec);

# ifdef XS
   ui.custInfoForm1->refresh(&custRec);
   ui.custInfoForm2->refresh(&custRec);
   ui.vehcInfoForm1->refresh(&custRec);
   ui.vehcInfoForm2->refresh(&custRec);
# endif

   if ( rec->field("customer").value().toInt() == 1 ) 
   {
      ui.woCustomerForm->setEnabled(false);
   }
   
   QSqlRecord vehcRec;

   xmldef = ui.woVehicleForm->readXmlDef();
   index = pFormDef->getIndexField(xmldef);

   QSqlField vehcIdent(index, QVariant::Int);
   printf("Ah3::haveWoSelected(): Have vehicle ident |%d|\n", rec->field("vehicle").value().toInt());
   vehcIdent.setValue(rec->field("vehicle").value().toInt());
   vehcRec.append(vehcIdent);
   ui.woVehicleForm->refresh(&vehcRec);

# ifdef XS
   ui.vehcInfoForm1->refresh(&vehcRec);
   ui.vehcInfoForm2->refresh(&vehcRec);
# endif

   if ( rec->field("vehicle").value().toInt() == 1 ) 
   {
      ui.woVehicleForm->clearForm();
      ui.woVehicleForm->setEnabled(false);
   }

   printf("Ah3::haveWoSelected(): Have Filtering woPartsTable\n");
   QString filter = "workorder = '" + QString::number(rec->field("ident").value().toInt()) + "'";
   ui.woPartsTable->setFilter(filter);
   ui.woPartsTable->refresh();
   filter += " and descr != '--DO_NOT_DELETE--'";
   ui.woLaborTable->setFilter(filter);
   ui.woLaborTable->refresh();

   QWidget *wdt;
   QStringList fields;
   printf("Ah3::haveWoSelected(): Getting field widget for parts total\n");
   fflush(stdout);
   fields = pFormDef->getFieldNames("wo_parts_total_form");
   wdt = ui.woPartsTotalForm->getFieldWidget(fields[0]);

   if ( wdt != 0 ) 
   {
      printf("Ah3::haveWoSelected(): Setting property to 0.00\n");
      fflush(stdout);
      wdt->setProperty(qPrintable(wdt->property("pname").toString()), "0.00");
   }
   printf("Ah3::haveWoSelected(): Refreshing table\n");
   fflush(stdout);
   ui.woPartsTotalForm->refresh(rec);

   printf("Ah3::haveWoSelected(): Getting field widget for taxable parts total\n");
   fflush(stdout);
   fields = pFormDef->getFieldNames("wo_tax_parts_total_form");
   wdt = ui.woTaxPartsTotalForm->getFieldWidget(fields[0]);

   if ( wdt != 0 ) 
   {
      printf("Ah3::haveWoSelected(): Setting property to 0.00\n");
      fflush(stdout);
      wdt->setProperty(qPrintable(wdt->property("pname").toString()), "0.00");
   }
   printf("Ah3::haveWoSelected(): Refreshing table\n");
   fflush(stdout);
   ui.woTaxPartsTotalForm->refresh(rec);

   printf("Ah3::haveWoSelected(): Getting field widget for labor cost\n");
   fflush(stdout);
   fields = pFormDef->getFieldNames("wo_labor_total_form");
   wdt = ui.woLaborTotalForm->getFieldWidget(fields[0]);

   if ( wdt != 0 ) 
   {
      printf("Ah3::haveWoSelected(): Setting property to 0.00\n");
      fflush(stdout);
      wdt->setProperty(qPrintable(wdt->property("pname").toString()), "0.00");
   }

   printf("Ah3::haveWoSelected(): Refreshing table\n");
   fflush(stdout);
   ui.woLaborTotalForm->refresh(rec);

# ifdef XS
   ui.tabWidget->setTabEnabled(0, true);
   ui.tabWidget->setTabEnabled(1, true);
   ui.tabWidget->setTabEnabled(2, true);
   ui.tabWidget->setTabEnabled(3, true);

   ui.woPartsTable->seek(0);
   ui.woLaborTable->seek(0);
# else
   ui.tabWidget->setTabEnabled(0, true);
# endif
   printf("Ah3::haveWoSelected(): Exit\n");
   fflush(stdout);
}

void Ah3::haveWoActivated(QSqlRecord *)
{
   printf("Ah3::haveWoActivated(): Enter\n");
   fflush(stdout);

# ifdef XS
   ui.tabWidget->setCurrentIndex(1);
# else
   ui.tabWidget->setCurrentIndex(0);
# endif

   printf("Ah3::haveWoActivated(): Exit\n");
   fflush(stdout);
}
*/

void Ah3::haveUpdateWoBtn()
{
   printf("Ah3::haveUpdateWoBtn(): Enter\n");
   fflush(stdout);
   QString closed = ui.workorderForm->getFieldText("closed");
   if ( closed == "Y" ) 
   {
      if ( QMessageBox::warning(NULL, "Warning", "This workorder has been closed, are you sure you want to modify it?\n", 
                                 QMessageBox::Yes | QMessageBox::Default, 
                                 QMessageBox::No | QMessageBox::Escape) == QMessageBox::No )
      {
         printf("Ah3::haveUpdateWoBtn(): Exiting, workorder unchanged\n");
         fflush(stdout);
         return;
      }
   }
   ui.woCustomerForm->updateRecord();
   ui.woVehicleForm->updateRecord();
   ui.workorderForm->updateRecord();
   calcTotals(true);
   fflush(stdout);
//   QMessageBox::warning(NULL, "Warning", "calcTotals complete", 
//                                 QMessageBox::Yes | QMessageBox::Default); 
   ui.workorderForm->updateRecord();
   fflush(stdout);
//   QMessageBox::warning(NULL, "Warning", "Update complete", 
//                                 QMessageBox::Yes | QMessageBox::Default); 
   ui.workorderSelect->refresh();
   fflush(stdout);
//   QMessageBox::warning(NULL, "Warning", "refresh complete", 
//                                 QMessageBox::Yes | QMessageBox::Default); 
   printf("Ah3::haveUpdateWoBtn(): Exit\n");
   fflush(stdout);
}

void Ah3::haveCancelWoBtn()
{
   printf("Ah3::haveCancelWoBtn(): Enter\n");
   fflush(stdout);
   ui.woCustomerForm->refresh();
   ui.woVehicleForm->refresh();
   ui.workorderForm->refresh();
   printf("Ah3::haveCancelWoBtn(): Exit\n");
   fflush(stdout);
}

void Ah3::haveWoPartsRequest()
{
   printf("Ah3::haveWoPartsRequest(): Enter\n");
   fflush(stdout);
   QString xmldef = ui.workorderForm->readXmlDef();
   printf("Ah3::haveWoPartsRequest(): workorderForm xmldef |%s|\n", qPrintable(xmldef));
   fflush(stdout);
   QString index = pFormDef->getIndexField(xmldef);
   printf("Ah3::haveWoPartsRequest(): workorderForm index = |%s|\n", qPrintable(index));
   fflush(stdout);
   int workorder = ui.workorderForm->getFieldValue(index).toInt();

   QString closed = ui.workorderForm->getFieldText("closed");
   if ( closed == "Y" ) 
   {
      if ( QMessageBox::warning(NULL, "Warning", "This workorder has been closed, are you sure you want to modify it?\n", 
                                 QMessageBox::Yes | QMessageBox::Default, 
                                 QMessageBox::No | QMessageBox::Escape) == QMessageBox::No )
      {
         printf("Ah3::haveUpdateWoBtn(): Exiting, workorder unchanged\n");
         fflush(stdout);
         return;
      }
   }
   printf("Ah3::haveWoPartsRequest(): Setting workorder to %d\n", workorder);
   fflush(stdout);
   WoPartEntryDialog dlg(workorder, this);
   dlg.setDatabase();
   dlg.exec();
#ifndef XS
   ui.woPartsTable->refresh();
#else
   ui.woPartsFrame->refresh();
#endif   
   ui.woPartsTotalForm->refresh(ui.workorderForm->record());
   ui.woTaxPartsTotalForm->refresh(ui.workorderForm->record());
   updateWoTotals();
   printf("Ah3::haveWoPartsRequest(): Exit\n");
   fflush(stdout);
}

void Ah3::haveWoLaborRequest()
{
   printf("Ah3::haveWoLaborRequest(): Enter\n");
   fflush(stdout);
   QString xmldef = ui.workorderForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);
   int workorder = ui.workorderForm->getFieldValue(index).toInt();

   QString closed = ui.workorderForm->getFieldText("closed");
   if ( closed == "Y" ) 
   {
      if ( QMessageBox::warning(NULL, "Warning", "This workorder has been closed, are you sure you want to modify it?\n", 
                                 QMessageBox::Yes | QMessageBox::Default, 
                                 QMessageBox::No | QMessageBox::Escape) == QMessageBox::No )
      {
         printf("Ah3::haveUpdateWoBtn(): Exiting, workorder unchanged\n");
         fflush(stdout);
         return;
      }
   }
   WoLaborEntryDialog dlg(workorder, this);
   dlg.setDatabase();
   dlg.exec();
#ifndef XS
   ui.woLaborTable->refresh();
   ui.woPartsTable->refresh();
#else
   ui.woLaborFrame->refresh();
   ui.woPartsFrame->refresh();
#endif
   ui.woLaborTotalForm->refresh(ui.workorderForm->record());
   ui.woPartsTotalForm->refresh(ui.workorderForm->record());
   ui.woTaxPartsTotalForm->refresh(ui.workorderForm->record());
   updateWoTotals();
   printf("Ah3::haveWoLaborRequest(): Exit\n");
   fflush(stdout);
}

void Ah3::updateWoTotals()
{
   printf("Ah3::updateWoTotals(): Enter\n");
   calcTotals();
   ui.workorderForm->updateRecord();
   calcTotals();
   ui.workorderForm->updateRecord();
   ui.woLaborTotalForm->refresh(ui.workorderForm->record());
   ui.woPartsTotalForm->refresh(ui.workorderForm->record());
   ui.woTaxPartsTotalForm->refresh(ui.workorderForm->record());
#ifdef XS
   ui.woLaborFrame->refresh();
   ui.woPartsFrame->refresh();
#endif
//***   ui.woSelectTable->refresh();
   printf("Ah3::updateWoTotals(): Exit\n");
   fflush(stdout);
}

/**********************************************************************/
/*   This  function calculates the totals for the workorder and sets  */
/*   the values into the form. IT DOES NOT ACTUALLY SAVE THE RECORD,  */
/*   YOU MUST CALL updateRecord() to perform this.                    */
/**********************************************************************/
void Ah3::calcTotals(bool force)
{
   printf("Ah3::calcTotals(): Enter\n");
   fflush(stdout);

   if ( ! force && ui.workorderForm->getFieldValue("closed").toString().toUpper() == "Y" ) 
   {
      printf("Ah3::calcTotals(): Exit, work order is closed\n");
      fflush(stdout);
   }
   double total = 0.0;
   QMap<QString, double> fieldValues;
/*
   double parts = 0.0;
   double labor = 0.0;
   double hazmat = 0.0;
   double salestax = 0.0;
*/
   QString xmldef = ui.workorderForm->readXmlDef();
   printf("Ah3::calcTotals(): workorderForm xmldef |%s|\n", qPrintable(xmldef));
   fflush(stdout);
   QString index = pFormDef->getIndexField(xmldef);
   printf("Ah3::calcTotals(): workorderForm index = |%s|\n", qPrintable(index));
   fflush(stdout);

   printf("Ah3::calcTotals(): Fetching resource names from group workorder_total\n");
   fflush(stdout);
   QStringList resources = pFormDef->getResourceNames("workorder_total");
   printf("Ah3::calcTotals(): Creating iterator\n");
   fflush(stdout);
   QListIterator<QString> it(resources);
   printf("Ah3::calcTotals(): Looping through the values\n");
   fflush(stdout);
   while ( it.hasNext() )
   {
      QString sql = QString::null;
      QString field = QString::null;
      QString config = QString::null;
      QString operation = QString::null;

      QString res = it.next();
      printf("Ah3::calcTotals(): Getting properties for: %s\n", qPrintable(res));
      fflush(stdout);

      if ( pFormDef->resourceHasProperties(res) ) 
      {
         QMap<QString, QVariant> properties = pFormDef->getResourceMap(res);
         printf("Ah3::calcTotals(): Making iterator\n");
         fflush(stdout);
         QMapIterator<QString, QVariant> it1(properties);
         printf("Ah3::calcTotals(): Looping through properties\n");
         fflush(stdout);
         while ( it1.hasNext() )
         {
            it1.next();
            printf("Ah3::calcTotals(): Property %s = %s\n", qPrintable(it1.key()), qPrintable(it1.value().toString()));
            fflush(stdout);
            if ( it1.key() == "query" ) 
               sql = it1.value().toString();
            if ( it1.key() == "field" ) 
            {
               field = it1.value().toString();
               QStringList sl = field.split(":");
               if ( sl.size() > 1 ) 
               {
                  config = sl[0];
                  field = sl[1];
                  operation = "add";
                  printf("Ah3::calcTotals(): have config: %s, and field %s\n", qPrintable(config), qPrintable(field));
                  fflush(stdout);
               }
            }
         }
      }
      else 
      {
         sql = pFormDef->getResource("res").toString();
      }
      if ( config.size() > 0 ) 
      {
         QString yesno = pConfig->value(config).toString();
         printf("Ah3::calcTotals(): field value (yesno): %s\n", qPrintable(yesno));
         fflush(stdout);
         if ( yesno.toUpper() != "YES" ) 
            sql = QString::null;
      }
      printf("Ah3::calcTotals(): Done, checking sql size\n");
      fflush(stdout);
      if ( sql.size() > 0 ) 
      {
         sql.replace("::workorder:", ui.workorderForm->getFieldValue(index).toString());
         printf("Ah3::calcTotals(): sql = |%s|\n", qPrintable(sql));
         fflush(stdout);
         QSqlQuery q;
         q.prepare(sql);
         q.exec();
         if ( q.next() ) 
         {
            double value = q.value(0).toDouble();
            printf("Ah3::calcTotals(): value: |%s| = %f\n", qPrintable(res), value);
            fflush(stdout);
            if ( field != QString::null ) 
            {
               printf("Ah3::calcTotals(): operation = |%s|\n", qPrintable(operation));
               fflush(stdout);
               if ( operation == "add" ) 
               {
                  double  org_value = 0.0;
                  if ( fieldValues.contains(field) ) 
                  {
                     org_value = fieldValues[field];
                     printf("Ah3::calcTotals(): org_value: %f\n", org_value);
                     total -= org_value;
                     printf("Ah3::calcTotals(): adjusted total (total - org_value): %f\n", total);
                  }
                  value += org_value;
                  printf("Ah3::calcTotals(): new value: |%s| = %f\n", qPrintable(res), value);
               }
               printf("Ah3::calcTotals(): Saving value to field: |%s|\n", qPrintable(field));
               fflush(stdout);
               ui.workorderForm->setFieldValue(field, value);
               fieldValues[field] = value;
            }
            printf("Ah3::calcTotals(): Adding field to total: |%s|, %f\n", qPrintable(field), value);
            total += value;
            printf("Ah3::calcTotals(): new total (total + value): %f\n", total);
         }
      }
   }
   printf("Ah3::calcTotals(): have total = %f\n", total);

   ui.workorderForm->setFieldValue("total", total);
   
   printf("Ah3::calcTotals(): Exit\n");
   fflush(stdout);
}

void Ah3::openConfigurationDialog(int index)
{
   printf("Ah3::openConfigurationDialog(): Enter\n");
   if ( menuMap.contains(index) ) 
   {
      QString config = menuMap[index];
      printf("Ah3::openConfigurationDialog(): Active index = %d config = |%s|\n", index, qPrintable(config));
      QcjDataConfigure cfgDlg;
      cfgDlg.initialize(config);
      cfgDlg.exec();
   }
   printf("Ah3::openConfigurationDialog(): exit\n");
   fflush(stdout);
}

void Ah3::havePreviewWoBtn()
{
   if ( tabsEnabled == true ) 
   {
      ui.workorderSelect->havePreviewBtn();
   }
   else
   {
      printf("Ah3::havePreviewWoBtn(): *** BEEP ***\n");
      ui.tabWidget->setCurrentIndex(currentTab);
      QApplication::beep();
      statusBar()->showMessage("Current part or labor record must be saved first", 1500);
   }
/*
   QMap<QString, QString> args;
   QString rptName;

   printf("Ah3::havePreviewWoBtn(): Enter\n");
   fflush(stdout);
   if ( tabsEnabled == true ) 
   {
      rptName = invoiceReportFn;

      if ( rptName.size() > 0 && ui.workorderForm->record() != NULL && ui.workorderForm->record()->field("ident").value().toInt() > 0)
      {
         QString ident = ui.workorderForm->record()->field("ident").value().toString();
         printf("Ah3::havePreviewWoBtn(): have valid ident number: |%s|\n", qPrintable(ui.workorderForm->record()->field("ident").value().toString()));
         fflush(stdout);

         args["invoice"] = ident;
         QcjDataReport rpt;
         if ( rpt.setReportFileName(rptName, args) )
         {
            printf("Ah3::havePreviewWoBtn(): Parsed report w/o error\n");
            fflush(stdout);
            rpt.previewReport();
            rpt.exec();
         }
         else
         {
            printf("Ah3::havePreviewWoBtn(): error parsing report\n");
            fflush(stdout);
         }
      }
   }
   else
   {
      printf("Ah3::havePreviewWoBtn(): *** BEEP ***\n");
      ui.tabWidget->setCurrentIndex(currentTab);
      QApplication::beep();
      statusBar()->showMessage("Current part or labor record must be saved first", 1500);
   }
   printf("Ah3::havePreviewWoBtn(): Exit\n");
   fflush(stdout);
*/
}

void Ah3::haveCloseWoBtn()
{
   QMap<QString, QString> args;
   QString rptName;

   printf("Ah3::haveCloseWoBtn(): Enter\n");
   fflush(stdout);
   if ( QMessageBox::warning(NULL, "Warning", "Are you sure you are ready to close this work order? Once closed, the work order should not be modified.\n", 
                              QMessageBox::Yes | QMessageBox::Default, 
                              QMessageBox::No | QMessageBox::Escape) == QMessageBox::No )
   {
      printf("Ah3::haveCloseWoBtn(): Exiting, workorder unchanged\n");
      fflush(stdout);
      return;
   }
   QString ident = ui.workorderForm->record()->field("ident").value().toString();
   QString sql = "update workorders set closed = 'Y' where ident = :ident";
   QSqlQuery q;
   q.prepare(sql);
   q.bindValue(":ident", ident);
   q.exec();
   refresh();
   ui.tabWidget->setCurrentIndex(1);
   printf("Ah3::haveCloseWoBtn(): Exit\n");
   fflush(stdout);
}

void Ah3::doReport(int report)
{
   QMap<QString, QString> args;
   QString rptName;

   printf("Ah3::doReport(): Enter, report = %d\n", report);
   fflush(stdout);

   rptName = menuMap[report];
   printf("Ah3::doReport(): Enter, report fn = |%s|\n", qPrintable(rptName));

   if ( rptName.size() > 0 ) 
   {
      QMap<QString, QString> args;
      QcjDataReport rpt;
      if ( rpt.setReportFileName(rptName, args) )
      {
         printf("Ah3::havePreviewWoBtn(): Parsed report w/o error\n");
         fflush(stdout);
         rpt.previewReport();
         rpt.exec();
      }
      else 
      {
         printf("Ah3::havePreviewWoBtn(): error parsing report\n");
         fflush(stdout);
      }
   }
   printf("Ah3::doReport(): Exit\n");
   fflush(stdout);
}

void Ah3::haveWorkorderRecord(QSqlRecord *rec, bool moveTab)
{
   printf("Ah3::haveWorkorderRecord(): Enter\n");

   ui.workorderForm->refresh(rec);

   int customer = rec->field("customer").value().toInt();
   int vehicle = rec->field("vehicle").value().toInt();

   QString xmldef = ui.woCustomerForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);

   QSqlRecord custRec;
   QSqlField custIdent(index, QVariant::Int);
   custIdent.setValue(customer);
   custRec.append(custIdent);
   ui.woCustomerForm->refresh(&custRec);

   xmldef = ui.woVehicleForm->readXmlDef();
   index = pFormDef->getIndexField(xmldef);
   QSqlRecord vehcRec;
   QSqlField vehcIdent(index, QVariant::Int);
   vehcIdent.setValue(vehicle);
   vehcRec.append(vehcIdent);
   ui.woVehicleForm->refresh(&vehcRec);

   printf("Ah3::haveWorkorderRecord(): Setting filters for parts and labor\n");
#ifndef XS
   QString filter = "workorder = '" + QString::number(rec->field("ident").value().toInt()) + "'";
   filter += " and descr != '--DO_NOT_DELETE--'";
   ui.woLaborTable->setFilter(filter);
   ui.woPartsTable->setFilter(filter);
   ui.woLaborTable->refresh();
   ui.woPartsTable->refresh();
#else
   ui.woLaborFrame->setWorkorder(rec->field("ident").value().toInt());
   ui.woLaborFrame->refresh();
   ui.woPartsFrame->setWorkorder(rec->field("ident").value().toInt());
   ui.woPartsFrame->refresh();
   ui.custInfoForm1->refresh(&custRec);
   ui.custInfoForm2->refresh(&custRec);
   ui.vehcInfoForm1->refresh(&custRec);
   ui.vehcInfoForm2->refresh(&custRec);
#endif

   QWidget *wdt;
   QStringList fields;
   printf("Ah3::haveWoSelected(): Getting field widget for parts total\n");
   fflush(stdout);
   fields = pFormDef->getFieldNames("wo_parts_total_form");
   wdt = ui.woPartsTotalForm->getFieldWidget(fields[0]);

   if ( wdt != 0 ) 
   {
      printf("Ah3::haveWoSelected(): Setting property to 0.00\n");
      fflush(stdout);
      wdt->setProperty(qPrintable(wdt->property("pname").toString()), "0.00");
   }
   printf("Ah3::haveWoSelected(): Refreshing table\n");
   fflush(stdout);
   ui.woPartsTotalForm->refresh(rec);

   printf("Ah3::haveWoSelected(): Getting field widget for taxable parts total\n");
   fflush(stdout);
   fields = pFormDef->getFieldNames("wo_tax_parts_total_form");
   wdt = ui.woTaxPartsTotalForm->getFieldWidget(fields[0]);

   if ( wdt != 0 ) 
   {
      printf("Ah3::haveWoSelected(): Setting property to 0.00\n");
      fflush(stdout);
      wdt->setProperty(qPrintable(wdt->property("pname").toString()), "0.00");
   }
   printf("Ah3::haveWoSelected(): Refreshing table\n");
   fflush(stdout);
   ui.woTaxPartsTotalForm->refresh(rec);

   printf("Ah3::haveWoSelected(): Getting field widget for labor cost\n");
   fflush(stdout);
   fields = pFormDef->getFieldNames("wo_labor_total_form");
   wdt = ui.woLaborTotalForm->getFieldWidget(fields[0]);

   if ( wdt != 0 ) 
   {
      printf("Ah3::haveWoSelected(): Setting property to 0.00\n");
      fflush(stdout);
      wdt->setProperty(qPrintable(wdt->property("pname").toString()), "0.00");
   }

   printf("Ah3::haveWoSelected(): Refreshing table\n");
   fflush(stdout);
   ui.woLaborTotalForm->refresh(rec);

   if ( vehicle == 1 ) 
   {
      ui.woVehicleForm->setEnabled(false);
   }
   else 
   {
      ui.woVehicleForm->setEnabled(true);
   }

   if ( customer == 1 ) 
   {
      ui.woCustomerForm->setEnabled(false);
   }
   else 
   {
      ui.woCustomerForm->setEnabled(true);
   }
   refresh();

# if 0
   # ifdef XS
      ui.tabWidget->setTabEnabled(0, true);
      ui.tabWidget->setTabEnabled(1, true);
      ui.tabWidget->setTabEnabled(2, true);
      ui.tabWidget->setTabEnabled(3, true);
   # else
      ui.tabWidget->setTabEnabled(0, true);
   # endif
# endif

   if ( moveTab ) 
   {
#ifndef XS
      ui.tabWidget->setCurrentIndex(0);
#else
      ui.tabWidget->setCurrentIndex(1);
#endif
   }

   ui.workorderSelect->workorderSeen();

   printf("Ah3::haveWorkorderRecord(): Exit\n");
   fflush(stdout);
}

void Ah3::haveDeleteWoAction()
{
   if ( tabsEnabled == true ) 
   {
      ui.workorderSelect->haveDeleteBtn();
   }
   else
   {
      printf("Ah3::haveDeleteWoAction(): *** BEEP ***\n");
      ui.tabWidget->setCurrentIndex(currentTab);
      QApplication::beep();
      statusBar()->showMessage("Current part or labor record must be saved first", 1500);
   }
}

void Ah3::haveNewWoAction()
{
   if ( tabsEnabled == true ) 
   {
      ui.workorderSelect->haveNewBtn();
   }
   else
   {
      printf("Ah3::haveNewWoAction(): *** BEEP ***\n");
      ui.tabWidget->setCurrentIndex(currentTab);
      QApplication::beep();
      statusBar()->showMessage("Current part or labor record must be saved first", 1500);
   }
}

void Ah3::haveRetailWoAction()
{
   if ( tabsEnabled == true ) 
   {
      ui.workorderSelect->haveRetailBtn();
   }
   else
   {
      printf("Ah3::haveRetailWoAction(): *** BEEP ***\n");
      ui.tabWidget->setCurrentIndex(currentTab);
      QApplication::beep();
      statusBar()->showMessage("Current part or labor record must be saved first", 1500);
   }
}

void Ah3::havePreviewWoAction()
{
   if ( tabsEnabled == true ) 
   {
      havePreviewWoBtn();
   }
   else
   {
      printf("Ah3::havePreviewWoAction(): *** BEEP ***\n");
      ui.tabWidget->setCurrentIndex(currentTab);
      QApplication::beep();
      statusBar()->showMessage("Current part or labor record must be saved first", 1500);
   }
}

void Ah3::haveTabChanged(int tab)
{
   printf("Ah3::haveTabChanged(): Enter, tabsEnabled = %d\n", tabsEnabled);
   if ( tabsEnabled == true ) 
   {
      #ifndef XS
         int wosTab = 1;
      #else
         int wosTab = 0;
      #endif
      if ( tab != wosTab && currentTab == wosTab ) 
      {
         if ( ui.workorderSelect->newWorkorder() ) 
         {
            haveWorkorderRecord(ui.workorderSelect->currentRecord(), true);
            ui.tabWidget->setCurrentIndex(tab);
         }
      }
      currentTab = tab;
   }
   else
   {
      printf("Ah3::haveTabChanged(): *** BEEP ***\n");
      ui.tabWidget->setCurrentIndex(currentTab);
      QApplication::beep();
      statusBar()->showMessage("Current part or labor record must be saved first", 1500);
   }
   printf("Ah3::haveTabChanged(): Exit\n");
}

void Ah3::woActive()
{
   #ifndef XS
      ui.tabWidget->setCurrentIndex(0);
   #else
      ui.tabWidget->setCurrentIndex(1);
   #endif
}

void Ah3::woSelectActive()
{
   #ifndef XS
      ui.tabWidget->setCurrentIndex(1);
   #else
      ui.tabWidget->setCurrentIndex(0);
   #endif
}

# ifdef XS
void Ah3::partsActive()
{
   ui.tabWidget->setCurrentIndex(2);
}

void Ah3::laborActive()
{
   ui.tabWidget->setCurrentIndex(3);
}
# endif

void Ah3::jobsActive()
{
   int idx = 2;
   #ifdef XS
      idx += 2;
   #endif
   ui.tabWidget->setCurrentIndex(idx);
}

void Ah3::inventoryActive()
{
   int idx = 3;
   #ifdef XS
      idx += 2;
   #endif
   ui.tabWidget->setCurrentIndex(idx);
}

# ifdef XS
void Ah3::invPartsActive()
{
   int idx = 4;
   idx += 2;
   ui.tabWidget->setCurrentIndex(idx);
}
# endif

void Ah3::vendorsActive()
{
   int idx = 5;
   #ifdef XS
      idx += 2;
   #endif
   ui.tabWidget->setCurrentIndex(idx);
}
