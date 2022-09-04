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

#ifndef WORKORDERSELECT_H
#define WORKORDERSELECT_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "ui_workorderselect.h"

class WorkorderSelect : public QFrame
{
   Q_OBJECT

public:
   WorkorderSelect(QWidget *parent = 0) : QFrame(parent)
   {
      printf("WorkorderSelect::WorkorderSelect(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      printf("WorkorderSelect::WorkorderSelect(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
      ui.dataForm->setDatabase();
      ui.dataTable->setDatabase();

      ui.dataFrame->setDataForm(ui.dataForm);
      ui.dataFrame->setDataTable(ui.dataTable);

      ui.dataFrame->enableAction(Qcj::SaveAction, false);
      ui.dataFrame->enableAction(Qcj::NewAction, false);

      ui.dataFrame->connectButton(Qcj::ClearAction, ui.clearBtn);
      ui.dataFrame->connectButton(Qcj::SearchAction, ui.searchBtn);
      ui.dataFrame->connectButton(Qcj::DelAction, ui.deleteBtn);
      ui.dataFrame->connectButton(Qcj::NewAction, ui.newBtn);

      connect(ui.closeBtn, SIGNAL(clicked()), this, SLOT(haveCloseBtn()));
      connect(ui.newBtn, SIGNAL(clicked()), this, SLOT(haveNewBtn()));
      connect(ui.previewBtn, SIGNAL(clicked()), this, SLOT(havePreviewBtn()));
      connect(ui.retailBtn, SIGNAL(clicked()), this, SLOT(haveRetailBtn()));
      connect(ui.showAllBtn, SIGNAL(stateChanged(int)), this, SLOT(haveShowAllBtnChanged(int)));

      connect(ui.dataTable, SIGNAL(rowActivated(QSqlRecord*)),
           this, SLOT(haveWoActivated(QSqlRecord*)));

      connect(ui.dataTable, SIGNAL(rowSelected(QSqlRecord*)),
           this, SLOT(haveWoSelected(QSqlRecord*)));

      connect(ui.dataFrame, SIGNAL(frameState(Qcj::FrameState)), this, SLOT(haveFrameState(Qcj::FrameState)));

      ui.dataTable->refresh();

      selectAction = new QAction(this);
      selectAction->setShortcut(Qt::Key_Enter);
      selectAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
      connect(selectAction, SIGNAL(triggered(bool)), this, SLOT(haveSelectAction(bool)));
      addAction(selectAction);
      haveShowAllBtnChanged(0);
   };

   void setWorkorderForm(QcjDataForm *form)
   {
      workorderForm = form;
   };

   void setInvoiceReportName(QString str)
   {
      invoiceReportFn = str;
   };

   QSqlRecord *currentRecord()
   {
      return(ui.dataTable->currentRecord());
   };

   bool newWorkorder()
   {
      return(newRecord);
   };

   void workorderSeen()
   {
      newRecord = false;
   };

   void refresh()
   {
      ui.dataTable->refresh();
   }

signals:
   void workorderRecord(QSqlRecord*, bool);

public slots:
   void haveNewBtn();
   void haveRetailBtn();
   void haveDeleteBtn();
   void havePreviewBtn();

protected slots:
   void haveShowAllBtnChanged(int);

   void haveSelectAction(bool)
   {
      emit workorderRecord(ui.dataTable->currentRecord(), true);
   };

   void haveFrameState(Qcj::FrameState)
   {
   };

   void haveWoActivated(QSqlRecord *rec)
   {
      printf("WorkorderSelect::haveWoActivated(): Enter\n");
      fflush(stdout);
      emit workorderRecord(rec, true);
      printf("WorkorderSelect::haveWoActivated(): Exit\n");
      fflush(stdout);
   };

   void haveWoSelected(QSqlRecord*)
   {
      newRecord = true;
   };

//   void haveCloseBtn();

private:
   QString              invoiceReportFn;
   QAction              *selectAction;
   QcjDataForm          *workorderForm;
   bool                 newRecord;
   Ui::WorkorderSelect  ui;
};

#endif
