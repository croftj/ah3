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

#ifndef WOLABORENTRY_H
#define WOLABORENTRY_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "isa.h"
# include "laborselect.h"
# include "ui_wolaborentry.h"

static bool isA(QObject *obj, const char *type);

class WoLaborEntry : public QFrame
{
   Q_OBJECT

public:
   WoLaborEntry(QWidget *parent = 0) : QFrame(parent)
   {
      printf("WoLaborEntry::WoLaborEntry(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      if ( ! ::isA(parent, "QDialog") ) 
      {
         ui.doneBtn->hide();
      }
      printf("WoLaborEntry::WoLaborEntry(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
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
      connect(ui.newBtn, SIGNAL(clicked()), this, SLOT(haveNewRequest()));
      connect(ui.lookupBtn, SIGNAL(clicked()), this, SLOT(haveLookupLaborBtn()));
      connect(ui.dataForm, SIGNAL(updated()), this, SLOT(haveSaveRequest()));

      connect(ui.dataFrame, SIGNAL(frameState(Qcj::FrameState)), 
              this, SLOT(haveFrameState(Qcj::FrameState)));

      QString filter = "workorder = " + QString::number(workorder) + 
            " and descr != '--DO_NOT_DELETE--'";
      ui.dataTable->setFilter(filter);
      ui.dataTable->seek(0);
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
      printf("WoPartEntry::setWorkorder(): Exit\n");
   };

   void refresh()
   {
      if ( ui.dataTable != 0 ) 
         ui.dataTable->refresh();
      if ( ui.dataForm != 0 ) 
         ui.dataForm->setFocus();
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
      printf("WoLaborEntry::reject(): Enter\n");
      fflush(stdout);
      if ( ui.dataForm->transactionOpen() ) 
         ui.dataForm->rollbackTransaction();
      if ( ::isA(parent(), "QDialog") ) 
         ((QDialog*)parent())->reject(); 
      printf("WoLaborEntry::reject(): Exit\n");
      fflush(stdout);
   };

protected slots:

   void haveSaveRequest()
   {
      printf("WoLaborEntry::haveSaveRequest(): Enter\n");
      emit updated();
      printf("WoLaborEntry::haveSaveRequest(): Exit\n");
   };

   void haveNewRequest()
   {
      printf("WoLaborEntry::haveNewRequest(): Enter, workorder = %d\n", workorder);
      QMap<QString, QString> fields;
      fields.insert("workorder", QString::number(workorder));
      ui.dataForm->insertRecord(fields);
      ui.dataFrame->setState(Qcj::Insert);
      printf("WoLaborEntry::haveNewRequest(): Exit\n");
   };

   void haveLookupLaborBtn()
   {
      printf("WoLaborEntry::haveLookupLaborBtn(): Enter\n");
      fflush(stdout);
      LaborSelect dlg(workorder, this);
      dlg.setDatabase();
      dlg.exec();
      ui.dataTable->refresh();
      emit updated();
      printf("WoLaborEntry::haveLookupLaborBtn(): Exit\n");
      fflush(stdout);
   };

   void haveFrameState(Qcj::FrameState state)
   {
      printf("WoLaborEntry::haveFrameState(): Enter, state: %d\n", state);
      fflush(stdout);
      if ( state == Qcj::Insert )
      {
         printf("WoLaborEntry::haveFrameState(): Disabling tabs\n");
         emit enableTabs(false);
      } 
      else
      {
         printf("WoLaborEntry::haveFrameState(): Disabling tabs\n");
         emit enableTabs(true);
      }
      printf("WoLaborEntry::haveFrameState(): Exit\n");
      fflush(stdout);
   };

private:
   int               workorder;
   Ui::WoLaborEntry  ui;
};

#endif
