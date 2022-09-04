# include <QDebug>
# include <QMessageBox>
# include "QcjData/QcjDataReport.h"
# include "QcjData/QcjDataStatics.h"
# include "customerentrydialog.h"
# include "vehicleentrydialog.h"
# include "workorderselect.h"

void WorkorderSelect::haveNewBtn()
{
   int vehicle = 0;

   printf("WorkorderSelect::haveNewBtn(): Enter\n");
   CustomerEntryDialog cust(true, this);
   cust.setDatabase();
   int customer = cust.exec();
   if ( customer > 1 ) 
   {
      VehicleEntryDialog vehc(customer, true, this);
      vehc.setDatabase();
      vehicle = vehc.exec();
      if ( vehicle == 0 ) 
      {
         printf("WorkorderSelect::haveNewBtn(): Exit- No vehicle seleted\n");
         fflush(stdout);
         return;
      }
   }
   else if ( customer == 1 )
   {
      vehicle = 1;
   }
   else
   {
      printf("WorkorderSelect::haveNewBtn(): Exit- No customer seleted\n");
      fflush(stdout);
      return;
   }

   printf("WorkorderSelect::haveNewBtn(): Have customer ident |%d|\n", customer);
   printf("WorkorderSelect::haveNewBtn(): Have vehicle ident |%d|\n", vehicle);
   if ( customer > 0 and vehicle > 0 ) 
   {
      QMap<QString, QString> fields;
      fields.insert("customer", QString::number(customer));
      fields.insert("vehicle", QString::number(vehicle));

      QString xmldef = ui.dataForm->readXmlDef();
      QStringList sl = pFormDef->getFieldNames(xmldef);
      QStringListIterator namelist(sl);
      while (namelist.hasNext()) 
      {
         QString field = namelist.next();
         if ( pFormDef->getFieldType(xmldef, field) == "date" || 
              pFormDef->getFieldType(xmldef, field) == "timestamp" ) 
         {
            fields.insert(field, "now");
         }
         else if ( pFormDef->getFieldType(xmldef, field) == "integer" ||
                   pFormDef->getFieldType(xmldef, field) == "double" )
         {
            fields.insert(field, "0");
         }
      }

      double taxrate = pConfig->value("SalesTaxRate", 0.0).toDouble();
      fields.insert("r_tax", QString::number(taxrate));

      double laborrate = pConfig->value("LaborRate", 0.0).toDouble();
      fields.insert("r_labor", QString::number(laborrate));

      ui.dataForm->insertRecord(fields);
      ui.dataForm->updateRecord();

      xmldef = ui.dataForm->readXmlDef();
      QString index = pFormDef->getIndexField(xmldef);
      QString index_value = ui.dataForm->getFieldText(index);
      printf("WorkorderSelect::haveNewBtn(): Have new record, index field |%s| == |%s|\n", qPrintable(index), qPrintable(index_value));
      fflush(stdout);
      QMap<QString, QString> woIndexFields;
      woIndexFields.insert(index, index_value);
      
      ui.dataTable->refresh();
      printf("WorkorderSelect::haveNewBtn(): Finding row in dataTable\n");
      fflush(stdout);
      ui.dataTable->findRow(woIndexFields, 0);
      qDebug() << "WorkorderSelect::haveNewBtn(): record = " << ui.dataForm->record();
      emit workorderRecord(ui.dataForm->record(), true);
/*
*/
   }
   printf("WorkorderSelect::haveNewBtn(): Exit\n");
   fflush(stdout);
}

void WorkorderSelect::haveRetailBtn()
{
   int vehicle = 0;

   printf("WorkorderSelect::haveRetailBtn(): Enter\n");
   CustomerEntryDialog cust(true, this);
   cust.setDatabase();
   int customer = 1;
   vehicle = 1;
   printf("WorkorderSelect::haveRetailBtn(): Have customer ident |%d|\n", customer);
   printf("WorkorderSelect::haveRetailBtn(): Have vehicle ident |%d|\n", vehicle);
   QMap<QString, QString> fields;
   fields.insert("customer", QString::number(customer));
   fields.insert("vehicle", QString::number(vehicle));

   QString xmldef = ui.dataForm->readXmlDef();
   QStringList sl = pFormDef->getFieldNames(xmldef);
   QStringListIterator namelist(sl);
   while (namelist.hasNext()) 
   {
      QString field = namelist.next();
      if ( pFormDef->getFieldType(xmldef, field) == "date" || 
            pFormDef->getFieldType(xmldef, field) == "timestamp" ) 
      {
         fields.insert(field, "now");
      }
      else if ( pFormDef->getFieldType(xmldef, field) == "integer" ||
                  pFormDef->getFieldType(xmldef, field) == "double" )
      {
         fields.insert(field, "0");
      }
   }

   double taxrate = pConfig->value("SalesTaxRate", 0.0).toDouble();
   fields.insert("r_tax", QString::number(taxrate));

   double laborrate = pConfig->value("LaborRate", 0.0).toDouble();
   fields.insert("r_labor", QString::number(laborrate));

   ui.dataForm->insertRecord(fields);
   ui.dataForm->updateRecord();

   xmldef = ui.dataForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);
   QString index_value = ui.dataForm->getFieldText(index);
   printf("WorkorderSelect::haveRetailBtn(): Have new record, index field |%s| == |%s|\n", qPrintable(index), qPrintable(index_value));
   fflush(stdout);
   QMap<QString, QString> woIndexFields;
   woIndexFields.insert(index, index_value);
   
   ui.dataTable->refresh();
   printf("WorkorderSelect::haveRetailBtn(): Finding row in dataTable\n");
   fflush(stdout);
   ui.dataTable->findRow(woIndexFields, 0);
   emit workorderRecord(ui.dataForm->record(), true);
/*
*/
   printf("WorkorderSelect::haveRetailBtn(): Exit\n");
   fflush(stdout);
}

void WorkorderSelect::haveDeleteBtn()
{
   printf("WorkorderSelect::haveDeleteBtn(): Enter\n");
   QString closed = ui.dataForm->getFieldText("closed");
   if ( closed == "Y" ) 
   {
      if ( QMessageBox::warning(NULL, "Warning", "This workorder has been closed, are you sure you want to delete it?\n", 
                                 QMessageBox::Yes | QMessageBox::Default, 
                                 QMessageBox::No | QMessageBox::Escape) == QMessageBox::No )
      {
         printf("WorkorderSelect::haveUpdateBtn(): Exiting, workorder unchanged\n");
         fflush(stdout);
         return;
      }
   }
   ui.dataForm->deleteRecord();
   ui.dataTable->refresh();
   printf("WorkorderSelect::haveDeleteBtn(): Exit\n");
}

void WorkorderSelect::havePreviewBtn()
{
   QMap<QString, QString> args;
   QString rptName;

   printf("WorkorderSelect::havePreviewBtn(): Enter\n");
   fflush(stdout);
   rptName = invoiceReportFn;

   if ( rptName.size() > 0 && ui.dataForm->record() != NULL && ui.dataForm->record()->field("ident").value().toInt() > 0) 
   {
      QString ident = ui.dataForm->record()->field("ident").value().toString();
      printf("WorkorderSelect::havePreviewBtn(): have valid ident number: |%s|\n", qPrintable(ui.dataForm->record()->field("ident").value().toString()));
      fflush(stdout);

      args["invoice"] = ident;
      QcjDataReport rpt;
      if ( rpt.setReportFileName(rptName, args) )
      {
         printf("WorkorderSelect::havePreviewBtn(): Parsed report w/o error\n");
         fflush(stdout);
         rpt.previewReport();
         rpt.exec();
      }
      else 
      {
         printf("WorkorderSelect::havePreviewBtn(): error parsing report\n");
         fflush(stdout);
      }
   }
   printf("WorkorderSelect::havePreviewBtn(): Exit\n");
   fflush(stdout);
}

void WorkorderSelect::haveShowAllBtnChanged(int)
{
   QString filter = "";

   printf("Ah3::haveShowAllWoBtnChanged(): Enter\n");
   if ( ui.showAllBtn->checkState() == Qt::Unchecked ) 
   {
      filter = "closed = 'N'";
   }
   printf("Ah3::haveShowAllWoBtnChanged(): Setting filter to: |%s|\n", qPrintable(filter));
   ui.dataTable->setFilter(filter);
//   ui.dataTable->refresh();
   printf("Ah3::haveShowAllWoBtnChanged(): Exit\n");
}
