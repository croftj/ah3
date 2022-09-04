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

#include <QAction>

# include "QcjData/QcjDataForm.h"
# include "QcjData/QcjDataTable.h"
# include "QcjData/QcjDataStatics.h"
# include "vendorselect.h"
# include "inventoryframe.h"

void InventoryFrame::setDatabase()
{
   printf("InventoryFrame::setDatabase(): Enter\n");

   printf("InventoryFrame::setDatabase(): invPartsTable\n");
   fflush(stdout);
   ui.invPartsTable->setDatabase();

   printf("InventoryFrame::setDatabase(): part2VendorsTable\n");
   fflush(stdout);
   ui.part2VendorsTable->setDatabase();

   printf("InventoryFrame::setDatabase(): part2VendorsPartForm\n");
   fflush(stdout);
   ui.part2VendorsPartForm->setDatabase();

   printf("InventoryFrame::setDatabase(): part2VendorsVendForm\n");
   fflush(stdout);
   ui.part2VendorsVendForm->setDatabase();

   printf("InventoryFrame::setDatabase(): Connecting signals\n");
   fflush(stdout);

   connect(ui.part2VendorsTable, SIGNAL(rowSelected(QSqlRecord*)),
           ui.part2VendorsPartForm, SLOT(refresh(QSqlRecord*)));

   connect(ui.part2VendorsTable, SIGNAL(rowSelected(QSqlRecord*)),
           this, SLOT(haveVendorPartSelected(QSqlRecord*)));

   connect(ui.part2VendorsPartForm, SIGNAL(updated()),
           ui.part2VendorsTable, SLOT(refresh()));

   connect(ui.invPartsTable, SIGNAL(rowSelected(QSqlRecord*)),
           this, SLOT(havePartSelected(QSqlRecord*)));

   connect(ui.saveBtn, SIGNAL(clicked()),
           this, SLOT(haveSaveVendor()));
   connect(ui.deleteBtn, SIGNAL(clicked()),
           this, SLOT(haveDeleteVendor()));
   connect(ui.addBtn, SIGNAL(clicked()),
           this, SLOT(haveAddVendor()));

   printf("InventoryFrame::setDatabase(): refreshing invPartsTable\n");
   fflush(stdout);
   ui.invPartsTable->refresh();

   printf("InventoryFrame::setDatabase(): creating actions\n");
   fflush(stdout);
   delAction = new QAction(this);
   delAction->setShortcut(QKeySequence::DeleteEndOfWord);
   delAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
   connect(delAction, SIGNAL(triggered(bool)), this, SLOT(haveDelAction(bool)));
   addAction(delAction);

   downAction = new QAction(this);
//   downAction->setShortcut(QKeySequence::MoveToNextLine);
   downAction->setShortcut(Qt::ALT + Qt::Key_Down);
   downAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
   connect(downAction, SIGNAL(triggered(bool)), this, SLOT(haveDownAction(bool)));
   addAction(downAction);

   newAction = new QAction(this);
   newAction->setShortcut(QKeySequence::New);
   newAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
   connect(newAction, SIGNAL(triggered(bool)), this, SLOT(haveNewAction(bool)));
   addAction(newAction);

   saveAction = new QAction(this);
   saveAction->setShortcut(QKeySequence::Save);
   saveAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
   connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(haveSaveAction(bool)));
   addAction(saveAction);

   upAction = new QAction(this);
//   upAction->setShortcut(QKeySequence::MoveToPreviousLine);
   upAction->setShortcut(Qt::ALT + Qt::Key_Up);
   upAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
   connect(upAction, SIGNAL(triggered(bool)), this, SLOT(haveUpAction(bool)));
   addAction(upAction);
   printf("InventoryFrame::setDatabase(): Exit\n");
   fflush(stdout);
}

void InventoryFrame::haveDeleteVendor()
{
   printf("InventoryFrame::haveDeleteVendor(): Enter\n");
   ui.part2VendorsPartForm->deleteRecord();
   ui.invPartsTable->refresh();
   ui.part2VendorsTable->refresh();
   ui.part2VendorsPartForm->refresh(ui.part2VendorsTable->currentRecord());
   refreshVendorForm(ui.part2VendorsTable->currentRecord()->field("vendor_ident").value().toInt());
   printf("InventoryFrame::haveDeleteVendor(): Exit\n");
}

void InventoryFrame::haveSaveVendor()
{
   printf("InventoryFrame::SaveVendor(): Enter\n");
   ui.part2VendorsPartForm->updateRecord();
   printf("InventoryFrame::SaveVendor(): vendor text = |%s|\n", qPrintable(ui.part2VendorsPartForm->getFieldText("vendor")));
   fflush(stdout);
   int vendor = ui.part2VendorsPartForm->getFieldValue("vendor").toInt();
   printf("InventoryFrame::SaveVendor(): vendor = %d\n", vendor);
   fflush(stdout);
   refreshVendorForm(vendor);
//   ui.part2VendorsPartForm->refresh(ui.part2VendorsTable->currentRecord());
   ui.invPartsTable->refresh();
   ui.part2VendorsTable->refresh();
   setMode(InventoryFrame::Updated);
   printf("InventoryFrame::haveSaveVendor(): Exit\n");
}

void InventoryFrame::haveAddVendor()
{
   printf("InventoryFrame::haveAddVendor(): Enter\n");
   fflush(stdout);
   if ( frameMode == InventoryFrame::Insert ) 
   {
      ui.part2VendorsPartForm->updateRecord();
   }
   VendorSelect vs(this);
   vs.setDatabase();
   int vendor = vs.exec();
   if ( vendor > 0 ) 
   {
      refreshVendorForm(vendor);
      QMap<QString, QString> fields;
      fields["part"] = QString::number(currentPart);
      fields["vendor"] = QString::number(vendor);
      ui.part2VendorsPartForm->insertRecord(fields);
      setMode(InventoryFrame::Insert);
   }
   printf("InventoryFrame::haveAddVendor(): Exit\n");
   fflush(stdout);
}


void InventoryFrame::havePartSelected(QSqlRecord *rec)
{
   printf("InventoryFrame::havePartSelected(): Enter\n");
   QString partIndex = pFormDef->getIndexField(ui.invPartsTable->readXmlDef());
   printf("InventoryFrame::havePartSelected(): partIndex = %s\n", qPrintable(partIndex));
   currentPart = rec->field(partIndex).value().toInt();
   printf("InventoryFrame::havePartSelected(): currentPart = %d\n", currentPart);
   QString filter;
   filter = "master_part = '" + QString::number(currentPart) + "'";
   printf("InventoryFrame::havePartSelected(): Setting part2VendorsTable filter to: %s\n", qPrintable(filter));
   ui.part2VendorsTable->setFilter(filter);
   printf("InventoryFrame::havePartSelected(): Exit\n");
}

void InventoryFrame::haveVendorPartSelected(QSqlRecord *rec)
{
   printf("InventoryFrame::haveVendorPartSelected(): Enter\n");
   int vendor = rec->field("vendor_ident").value().toInt();
   refreshVendorForm(vendor);
   printf("InventoryFrame::haveVendorPartSelected(): Exit\n");
}

void InventoryFrame::haveUpAction(bool)
{
   printf("InventoryFrame::haveUpAction(): Enter\n");
   if ( frameMode != InventoryFrame::Insert ) 
   {
      printf("InventoryFrame::haveUpAction(): Action enabled\n");
   }
   printf("InventoryFrame::haveUpAction(): Exit\n");
   fflush(stdout);
}

void InventoryFrame::haveDownAction(bool)
{
   printf("InventoryFrame::haveDownAction(): Enter\n");
   if ( frameMode != InventoryFrame::Insert ) 
   {
      printf("InventoryFrame::haveDownAction(): Action enabled\n");
   }
   printf("InventoryFrame::haveDownAction(): Exit\n");
   fflush(stdout);
}


void InventoryFrame::setMode(InventoryFrame::Mode mode)
{
   frameMode = mode;

   switch (frameMode) 
   {
      case InventoryFrame::Insert:
         ui.invPartsTable->setEnabled(false);
         ui.part2VendorsTable->setEnabled(false);
         ui.deleteBtn->setEnabled(false);
         break;

      case InventoryFrame::Updated:
         ui.invPartsTable->setEnabled(true);
         ui.part2VendorsTable->setEnabled(true);
         ui.deleteBtn->setEnabled(true);
         break;

      default:
         break;
   }
}

void InventoryFrame::refreshVendorForm(int vendor)
{
   printf("InventoryFrame::refreshVendorForm(): Enter\n");
   QString index = pFormDef->getIndexField(ui.part2VendorsVendForm->readXmlDef());
   printf("InventoryFrame::refreshVendorForm(): index = %s, vendor = %d\n", qPrintable(index), vendor);
   QSqlField field;
   field.setName(index);
   field.setValue(vendor);
   QSqlRecord rec;
   rec.append(field);
   ui.part2VendorsVendForm->refresh(&rec);
   printf("InventoryFrame::refreshVendorForm(): Exit\n");
}


