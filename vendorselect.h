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

#ifndef VENDORSELECT_H
#define VENDORSELECT_H

# include <QDialog>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "ui_vendorselect.h"


class VendorSelect : public QDialog 
{
   Q_OBJECT

public:
   VendorSelect(QWidget *parent = 0) : QDialog(parent)
   {
      printf("VendorSelect::VendorSelect(): Enter\n");
      fflush(stdout);
      ui.setupUi(this);
      connect(ui.applyBtn, SIGNAL(clicked()), this, SLOT(haveApply()));
      connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
      printf("VendorSelect::VendorSelect(): Enter\n");
      fflush(stdout);
   };

   void setDatabase()
   {
      printf("VendorSelect::setdatabase(): Enter\n");
      fflush(stdout);
      ui.vendorTable->setDatabase();
      printf("VendorSelect::setdatabase(): Exit\n");
      fflush(stdout);
   };

   QSqlRecord *currentRecord()
   {
      return(ui.vendorTable->currentRecord());
   };

public slots:
   void haveApply()
   {
      done(ui.vendorTable->currentRecord()->field(
            pFormDef->getIndexField(ui.vendorTable->readXmlDef())).value().toInt()
          );
   }


protected:
private:
   Ui::VendorSelect  ui;
};

#endif
