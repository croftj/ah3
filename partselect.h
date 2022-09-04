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

#ifndef PARTSELECT_H
#define PARTSELECT_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "ui_partselect.h"

class PartSelect : public QDialog
{
   Q_OBJECT

public:
   PartSelect(QWidget *parent = 0) : QDialog(parent)
   {
      printf("PartSelect::PartSelect(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      printf("PartSelect::PartSelect(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
      printf("PartSelect::setDatabase(): Enter\n");
      fflush(stdout);
      ui.dataForm->setDatabase();
      ui.dataTable->setDatabase();

      ui.dataFrame->setDataForm(ui.dataForm);
      ui.dataFrame->setDataTable(ui.dataTable);

      ui.dataFrame->enableAction(Qcj::SaveAction, false);
      ui.dataFrame->enableAction(Qcj::NewAction, false);
      ui.dataFrame->enableAction(Qcj::DelAction, false);

      ui.dataFrame->connectButton(Qcj::ClearAction, ui.clearBtn);
      ui.dataFrame->connectButton(Qcj::SearchAction, ui.searchBtn);
      connect(ui.selectBtn, SIGNAL(clicked()), this, SLOT(haveSelectPartBtn()));
      ui.dataTable->refresh();
      printf("PartSelect::setDatabase(): Exit\n");
      fflush(stdout);
   };

protected slots:
   void haveSelectPartBtn()
   {
      QString xmldef = ui.dataForm->readXmlDef();
      printf("PartSelect::haveSelectPartBtn(): workorderForm xmldef |%s|\n", qPrintable(xmldef));
      fflush(stdout);
      QString index = pFormDef->getIndexField(xmldef);
      printf("PartSelect::haveSelectPartBtn(): workorderForm index = |%s|\n", qPrintable(index));
      fflush(stdout);
      done(ui.dataForm->getFieldValue(index).toInt());
   }

private:
   int               workorder;
   Ui::PartSelect   ui;
};

#endif



