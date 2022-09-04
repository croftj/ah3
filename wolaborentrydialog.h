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

#ifndef WOLABORENTRYDIALOG_H
#define WOLABORENTRYDIALOG_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "isa.h"
# include "laborselect.h"
# include "ui_wolaborentrydialog.h"

static bool isA(QObject *obj, const char *type);

class WoLaborEntryDialog : public QDialog
{
   Q_OBJECT

public:
   WoLaborEntryDialog(int wo, QWidget *parent = 0) : QDialog(parent)
   {
      printf("WoLaborEntryDialog::WoLaborEntryDialog(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);

      workorder = wo;

      printf("WoLaborEntryDialog::WoLaborEntryDialog(): Exit\n");
      fflush(stdout);
   };

   void setDatabase()
   {
      printf("WoLaborEntryDialog::setDatabase(): Enter\n");
      ui.entryFrame->setDatabase();
      ui.entryFrame->setWorkorder(workorder);
      printf("WoLaborEntryDialog::setDatabase(): Exit\n");
   };

private:
   int                     workorder;
   Ui::WoLaborEntryDialog  ui;
};
#endif
