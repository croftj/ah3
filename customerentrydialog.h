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

#ifndef CUSTOMERENTRYDIALOG_H
#define CUSTOMERENTRYDIALOG_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "ui_customerentrydialog.h"

class CustomerEntryDialog : public QDialog
{
   Q_OBJECT

public:
   CustomerEntryDialog(bool setSelect = false, QWidget *parent = 0) : QDialog(parent)
   {
      printf("CustomerEntryDialog::CustomerEntryDialog(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      if ( setSelect ) 
         ui.selectCustomerBtn->setText("Select");
      else
         ui.selectCustomerBtn->setText("Done");
      ui.searchCustomerBtn->setDefault(true);
      printf("CustomerEntryDialog::CustomerEntryDialog(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
      ui.customerForm->setDatabase();
      ui.customerTable->setDatabase();

      ui.customerDataFrame->enableAction(Qcj::DelAction, false);

      ui.customerDataFrame->setDataForm(ui.customerForm);
      ui.customerDataFrame->setDataTable(ui.customerTable);

      ui.customerDataFrame->connectButton(Qcj::ClearAction, ui.clearFilterBtn);
      ui.customerDataFrame->connectButton(Qcj::SearchAction, ui.searchCustomerBtn);
      ui.customerDataFrame->connectButton(Qcj::DelAction, ui.deleteCustomerBtn);
      ui.customerDataFrame->connectButton(Qcj::SaveAction, ui.saveCustomerBtn);
      ui.customerDataFrame->connectButton(Qcj::NewAction, ui.newCustomerBtn);

      connect(ui.customerDataFrame, SIGNAL(deleteRecord()), this, SLOT(haveDeleteCustomerBtn()));

      connect(ui.selectCustomerBtn, SIGNAL(clicked()), this, SLOT(haveSelectCustomerBtn()));
      connect(ui.viewVehiclesBtn, SIGNAL(clicked()), this, SLOT(haveViewVehiclesBtn()));

      connect(ui.customerDataFrame, SIGNAL(frameState(Qcj::FrameState)), this, SLOT(haveFrameState(Qcj::FrameState)));

      ui.customerTable->refresh();
   };

public slots:
   void accept()
   {
      ui.selectCustomerBtn->setFocus();
      ui.customerForm->updateRecord();
      QDialog::accept(); 
   };

   void reject()
   {
      if ( ui.customerForm->transactionOpen() ) 
         ui.customerForm->rollbackTransaction();
      QDialog::reject(); 
   };

protected slots:
   void haveDeleteCustomerBtn();
   void haveSelectCustomerBtn()
   {
      ui.customerForm->updateRecord();
      QString xmldef = ui.customerForm->readXmlDef();
      QString index = pFormDef->getIndexField(xmldef);
      done(ui.customerForm->getFieldValue(index).toInt());
   };

   void haveFrameState(Qcj::FrameState state)
   {
      if ( state == Qcj::Search ) 
         ui.selectCustomerBtn->setEnabled(false);
      else
         ui.selectCustomerBtn->setEnabled(true);
   };

   void haveViewVehiclesBtn();

private:
   Ui::CustomerEntryDialog ui;
};

#endif
