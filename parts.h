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

#ifndef PARTS_H
#define PARTS_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "ui_parts.h"

class Parts : public QFrame
{
   Q_OBJECT

public:
   Parts(QWidget *parent = 0) : QFrame(parent)
   {
      printf("Parts::Parts(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      ui.searchBtn->setDefault(true);
      printf("Parts::Parts(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
      ui.dataForm->setDatabase();
      ui.dataTable->setDatabase();

      ui.dataFrame->setDataForm(ui.dataForm);
      ui.dataFrame->setDataTable(ui.dataTable);

      ui.dataFrame->connectButton(Qcj::ClearAction, ui.clearBtn);
      ui.dataFrame->connectButton(Qcj::SearchAction, ui.searchBtn);
      ui.dataFrame->connectButton(Qcj::DelAction, ui.deleteBtn);
      ui.dataFrame->connectButton(Qcj::SaveAction, ui.saveBtn);
      ui.dataFrame->connectButton(Qcj::NewAction, ui.newBtn);

      ui.dataTable->refresh();

      connect(ui.dataTable, SIGNAL(rowSelected(QSqlRecord*)), this, SLOT(haveRowSelected(QSqlRecord*)));
   };

   QSqlRecord *currentRecord()
   {
      return(ui.dataTable->currentRecord());
   };

signals:
   void rowSelected(QSqlRecord*);

protected slots:
   void haveRowSelected(QSqlRecord *rec)
   {
      emit rowSelected(rec);
   };

private:
   Ui::Parts ui;
};

#endif
