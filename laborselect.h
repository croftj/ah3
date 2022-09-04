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

#ifndef LABORSELECT_H
#define LABORSELECT_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "ui_laborselect.h"

class LaborSelect : public QDialog
{
   Q_OBJECT

public:
   LaborSelect(int wo, QWidget *parent = 0) : QDialog(parent)
   {
      printf("LaborSelect::LaborSelect(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      workorder = wo;
      printf("LaborSelect::LaborSelect(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
      printf("LaborSelect::setDatabase(): Enter\n");
      fflush(stdout);
      printf("LaborSelect::setDatabase(): Setting up labor frame and its components\n");
      fflush(stdout);
      ui.laborForm->setDatabase();
      ui.laborTable->setDatabase();
      ui.laborFrame->setDataForm(ui.laborForm);
      ui.laborFrame->setDataTable(ui.laborTable);
      ui.laborFrame->connectButton(Qcj::SaveAction, ui.saveLaborBtn);
      ui.laborFrame->connectButton(Qcj::DelAction, ui.deleteLaborBtn);
      ui.laborFrame->enableAction(Qcj::NewAction, false);
      ui.laborFrame->enableAction(Qcj::SearchAction, false);
      ui.laborFrame->enableAction(Qcj::ClearAction, false);

      printf("LaborSelect::setDatabase(): Setting up parts frame and its components\n");
      fflush(stdout);
      ui.partsForm->setDatabase();
      ui.partsTable->setDatabase();
      ui.partsFrame->setDataForm(ui.partsForm);
      ui.partsFrame->setDataTable(ui.partsTable);
      ui.partsFrame->connectButton(Qcj::SaveAction, ui.savePartsBtn);
      ui.partsFrame->connectButton(Qcj::DelAction, ui.deletePartsBtn);
      ui.partsFrame->enableAction(Qcj::NewAction, false);
      ui.partsFrame->enableAction(Qcj::SearchAction, false);
      ui.partsFrame->enableAction(Qcj::ClearAction, false);
      ui.partsFrame->enableAction(Qcj::DelAction, false);
      connect(ui.partsFrame, SIGNAL(deleteRecord()), this, SLOT(haveDelPartBtn()));

      ui.jobSelectTable->setDatabase();

      connect(ui.addJobBtn, SIGNAL(clicked()), this, SLOT(haveAddJobBtn()));
# if 0
      connect(ui.deleteJobBtn, SIGNAL(clicked()), this, SLOT(haveDelJobBtn()));
      connect(ui.savePartBtn, SIGNAL(clicked()), this, SLOT(haveSavePartBtn()));
      connect(ui.delPartBtn, SIGNAL(clicked()), this, SLOT(haveDelPartBtn()));
# endif

      connect(ui.laborTable, SIGNAL(rowSelected(QSqlRecord*)), this, SLOT(haveLaborRecord(QSqlRecord*)));
      connect(ui.jobSelectTable, SIGNAL(rowActivated(QSqlRecord*)), this, SLOT(haveJobRecord(QSqlRecord*)));

      QString filter = "workorder = '" + QString::number(workorder) + "' and job > 0";
      printf("LaborSelect::setDatabase(): setting filter: |%s|\n", qPrintable(filter));
      fflush(stdout);
      ui.laborTable->setFilter(filter);
      ui.laborTable->refresh();

      ui.partsTable->setFilter(filter);
      ui.partsTable->refresh();

      ui.jobSelectTable->refresh();

      ui.laborTable->selectRow(0);
      printf("LaborSelect::setDatabase(): Exit\n");
      fflush(stdout);
   };

protected slots:
   void haveAddJobBtn();
   void haveDelJobBtn();
   void haveSavePartBtn();
   void haveDelPartBtn();
   void haveLaborRecord(QSqlRecord*);
   void haveJobRecord(QSqlRecord*);

private:
   int               workorder;
   Ui::LaborSelect   ui;
};

#endif



