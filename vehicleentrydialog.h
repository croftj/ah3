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

#ifndef VEHICLEENTRYDIALOG_H
#define VEHICLEENTRYDIALOG_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "ui_vehicleentrydialog.h"

extern QcjDataConfigure *pConfigDlg;

class VehicleEntryDialog : public QDialog
{
   Q_OBJECT

public:
   VehicleEntryDialog(int cust_ident, bool setSelect = false, QWidget *parent = 0) : QDialog(parent)
   {
      printf("VehicleEntryDialog::VehicleEntryDialog(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      if ( setSelect ) 
         ui.selectVehicleBtn->setText("Select");
      else
         ui.selectVehicleBtn->setText("Done");
      ui.searchVehicleBtn->setDefault(true);
      customer = cust_ident;
//      ui.showAllVehiclesBtn->setChecked("Qt::Checked");
      printf("VehicleEntryDialog::VehicleEntryDialog(): Exit\n");
      fflush(stdout);
   };

   VehicleEntryDialog(bool setSelect = false, QWidget *parent = 0) : QDialog(parent)
   {
      printf("VehicleEntryDialog::VehicleEntryDialog(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      if ( setSelect ) 
         ui.selectVehicleBtn->setText("Select");
      else
         ui.selectVehicleBtn->setText("Done");
      ui.searchVehicleBtn->setDefault(true);
//      ui.showAllVehiclesBtn->setChecked("Qt::Checked");
      printf("VehicleEntryDialog::VehicleEntryDialog(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
      printf("VehicleEntryDialog::setDatabase(): Enter\n");
      fflush(stdout);
      ui.vehicleForm->setDatabase();
      ui.vehicleTable->setDatabase();
      ui.vehicleForm->clearForm();
      connect(ui.newVehicleBtn, SIGNAL(clicked()), this, SLOT(haveNewVehicleBtn()));
      connect(ui.deleteVehicleBtn, SIGNAL(clicked()), this, SLOT(haveDeleteVehicleBtn()));
      connect(ui.searchVehicleBtn, SIGNAL(clicked()), this, SLOT(haveSearchVehicleBtn()));
      connect(ui.clearFilterBtn, SIGNAL(clicked()), this, SLOT(haveClearVehicleBtn()));
      connect(ui.selectVehicleBtn, SIGNAL(clicked()), this, SLOT(haveSelectVehicleBtn()));
      connect(ui.saveVehicleBtn, SIGNAL(clicked()), ui.vehicleForm, SLOT(setFocus()));
      if ( customer > 0 ) 
      {
         QString filter = "owner = " + QString::number(customer);
         ui.vehicleTable->setFilter(filter);
      }
      ui.vehicleTable->refresh();
      ui.vehicleTable->selectRow(0);
//      connect(ui.selectVehicleBtn, SIGNAL(clicked()), this, SLOT(haveSelectVehicleBtn()));
      printf("VehicleEntryDialog::setDatabase(): Exit\n");
      fflush(stdout);
   };

protected slots:
   void haveNewVehicleBtn()
   {
      QMap<QString, QString> fields;
//      QString idx = pFormDef->getNewIndex(ui.vehicleForm->readXmlDef());
      QString idxname = pFormDef->getIndexField(ui.vehicleForm->readXmlDef());

//      fields.insert(idxname, idx);
      fields.insert("owner", QString::number(customer));
      ui.vehicleForm->insertRecord(fields);
      ui.vehicleTable->refresh();
      ui.vehicleTable->findRow(fields);
      ui.vehicleForm->setFocus();
   };
   void haveSearchVehicleBtn();
   void haveClearVehicleBtn();
   void setCustomer(int cust_ident)
   {
      customer = cust_ident;
      if ( customer > 0 ) 
      {
         QString filter = "owner = " + QString::number(customer);
         ui.vehicleTable->setFilter(filter);
      }
   }
   void haveSelectVehicleBtn()
   {
      QString xmldef = ui.vehicleForm->readXmlDef();
      QString index = pFormDef->getIndexField(xmldef);
      done(ui.vehicleForm->getFieldValue(index).toInt());
   };
   void haveDeleteVehicleBtn();

   void accept()
   {
      ui.selectVehicleBtn->setFocus();
      ui.vehicleForm->updateRecord();
      QDialog::accept(); 
   };

   void reject()
   {
      if ( ui.vehicleForm->transactionOpen() ) 
         ui.vehicleForm->rollbackTransaction();
      QDialog::reject(); 
   };


private:
   int                     customer;
   Ui::VehicleEntryDialog  ui;
};

#endif
