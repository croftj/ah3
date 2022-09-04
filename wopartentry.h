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

#ifndef WOPARTENTRY_H
#define WOPARTENTRY_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "isa.h"
# include "ui_wopartentry.h"

class WoPartEntry : public QFrame
{
   Q_OBJECT

public:
   WoPartEntry(QWidget *parent = 0) : QFrame(parent)
   {
      printf("WoPartEntry::WoPartEntry(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      if ( ! ::isA(parent, "QDialog") ) 
      {
         ui.doneBtn->hide();
      }
//      connect(ui.dataTable, SIGNAL(emptyTable()), ui.dataForm, SLOT(clearForm()));
      printf("WoPartEntry::WoPartEntry(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
      printf("WoPartEntry::setDatabase(): Enter\n");
      ui.dataForm->setDatabase();
      ui.dataTable->setDatabase();

      printf("WoPartEntry::setDatabase(): Adding form to frame\n");
      ui.dataFrame->setDataForm(ui.dataForm);
      printf("WoPartEntry::setDatabase(): Adding table to frame\n");
      ui.dataFrame->setDataTable(ui.dataTable);

      ui.dataFrame->connectButton(Qcj::DelAction, ui.deleteBtn);
      ui.dataFrame->connectButton(Qcj::NewAction, ui.newBtn);
      ui.dataFrame->connectButton(Qcj::SaveAction, ui.saveBtn);
      ui.dataFrame->enableAction(Qcj::NewAction, false);
 
      connect(ui.doneBtn, SIGNAL(clicked()), this, SLOT(accept()));
      connect(ui.lookupBtn, SIGNAL(clicked()), this, SLOT(haveLookupBtn()));
      connect(ui.dataFrame, SIGNAL(insertRecord()), this, SLOT(haveNewRequest()));
      connect(ui.dataForm, SIGNAL(updated()), this, SLOT(haveSaveRequest()));
      connect(ui.dataFrame, SIGNAL(frameState(Qcj::FrameState)), 
              this, SLOT(haveFrameState(Qcj::FrameState)));
//***      ui.lookupBtn->setEnabled(false);

      printf("WoPartEntry::setDatabase(): Exit\n");
   };

signals:
   void updated();
   void enableTabs(bool);

public slots:
   void setWorkorder(int wo)
   {
      printf("WoPartEntry::setWorkorder(): Enter\n");
      workorder = wo;
      QString filter = "workorder = " + QString::number(workorder) + 
            " and descr != '--DO_NOT_DELETE--'";
      printf("WoPartEntry::setWorkorder(): filter = %s\n", qPrintable(filter));
      ui.dataTable->setFilter(filter);
      printf("WoPartEntry::setWorkorder(): refreshing table\n");
      ui.dataTable->refresh();
      ui.dataTable->seek(0);
      ui.dataFrame->setState(Qcj::Updated);
      printf("WoPartEntry::setWorkorder(): Exit\n");
   };

   void refresh()
   {
      if ( ui.dataTable != 0 ) 
         ui.dataTable->refresh();
      if ( ui.dataForm != 0 ) 
         ui.dataForm->setFocus();
   };

   void haveSaveRequest()
   {
      printf("WoPartEntry::haveSaveRequest(): Enter\n");
      emit updated();
      printf("WoPartEntry::haveSaveRequest(): Exit\n");
   };

   void haveNewRequest()
   {
      printf("WoPartEntry::haveNewRequest(): Enter, workorder = %d\n", workorder);
      QMap<QString, QString> fields;
      fields.insert("workorder", QString::number(workorder));
      printf("WoPartEntry::haveNewRequest(): inserting record\n");
      ui.dataForm->insertRecord(fields);
      ui.dataFrame->setState(Qcj::Insert);
      printf("WoPartEntry::haveNewRequest(): Exit\n");
   };

   void accept()
   {
      ui.doneBtn->setFocus();
      ui.dataForm->updateRecord();
      if ( ::isA(parent(), "QDialog") ) 
         ((QDialog*)parent())->accept(); 
   };

   void reject()
   {
      if ( ui.dataForm->transactionOpen() ) 
         ui.dataForm->rollbackTransaction();
      if ( ::isA(parent(), "QDialog") ) 
         ((QDialog*)parent())->reject(); 
   };

protected slots:

   void haveLookupBtn();

   void haveFrameState(Qcj::FrameState state)
   {
      printf("WoPartEntry::haveFrameState(): Enter, state: %d\n", state);
      fflush(stdout);
      if ( state == Qcj::Insert )
      {
         printf("WoPartEntry::haveFrameState(): Disabling tabs\n");
         emit enableTabs(false);
      } 
      else
      {
         printf("WoPartEntry::haveFrameState(): Disabling tabs\n");
         emit enableTabs(true);
      }
      printf("WoPartEntry::haveFrameState(): Exit\n");
      fflush(stdout);
   };

private:
   int               workorder;
   Ui::WoPartEntry   ui;
};

#endif


