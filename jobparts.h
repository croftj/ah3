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

#ifndef JOBPARTS_H
#define JOBPARTS_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "autojob.h"
# include "ui_jobparts.h"

class JobParts : public QFrame
{
   Q_OBJECT

public:
   JobParts(QWidget *parent = 0) : QFrame(parent)
   {
      printf("JobParts::JobParts(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      printf("JobParts::JobParts(): Exit\n");
      fflush(stdout);
   };

   void setDatabase() 
   {
      printf("JobParts::setDatabase(): Enter\n");
      ui.dataForm->setDatabase();
      ui.dataTable->setDatabase();
      printf("JobParts::setDatabase(): dataTable  = %ld\n", (long)ui.dataTable);

      connect(ui.dataFrame, SIGNAL(insertRecord()), this, SLOT(haveNewAction()));

      ui.dataFrame->enableAction(Qcj::SearchAction, false);
      ui.dataFrame->enableAction(Qcj::ClearAction, false);

      ui.dataFrame->setDataForm(ui.dataForm);
      ui.dataFrame->setDataTable(ui.dataTable);

      ui.dataFrame->connectButton(Qcj::DelAction, ui.deleteBtn);
      ui.dataFrame->connectButton(Qcj::SaveAction, ui.saveBtn);
      ui.dataFrame->connectButton(Qcj::NewAction, ui.newBtn);

      ui.dataTable->refresh();
      printf("JobParts::setDatabase(): Exit\n");
   };

   void setParentJob(AutoJob *pj);

protected slots:
   void haveNewAction();

private:
   AutoJob        *parentJob;
   Ui::JobParts   ui;
};

#endif
