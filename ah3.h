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

#ifndef AH3_H
#define AH3_H

# include <QMainWindow>
# include "QcjData/QcjDataStatics.h"
# include "QcjData/QcjDataConfigure.h"
# include "customerentrydialog.h"
# include "about.h"

# ifdef XS
#  include "ui_ah3xs.h"
# else
#  include "ui_ah3.h"
# endif

extern QcjDataConfigure *pConfigDlg;

class Ah3 : public QMainWindow 
{
   Q_OBJECT

public:
   Ah3();
   void setDatabase();

public slots:
   void close();
   void refresh();
   void saveCurrentForm();
   void doReport(int report);

//   void haveNewPart2Vendor();
//   void haveAllParts2VendorBtnChanged(int state);
//   void havePartsRecordSelected(QSqlRecord *rec);

   void haveEditCustomer()
   {
      printf("Ah3::haveEditCustomer(): Enter\n");
      CustomerEntryDialog dlg(false, this);
      dlg.setDatabase();
      int customer = dlg.exec();
      printf("Ah3::haveEditCustomer(): Exit- customer %d selected\n", customer);
      fflush(stdout);
   };
   void haveWoLaborRequest();
   void haveWoPartsRequest();

   void updateWoTotals();

   void haveUpdateWoBtn();
   void haveCancelWoBtn();
   
   void haveTabChanged(int);
   void woActive();
   void woSelectActive();

   void haveCloseWoBtn();
   void haveDeleteWoAction();
   void haveNewWoAction();
   void haveRetailWoAction();
   void havePreviewWoAction();

#ifdef XS
   void partsActive();
   void laborActive();
   void invPartsActive();
#endif
   void jobsActive();
   void inventoryActive();
   void vendorsActive();
//   void Active();
//   void Active();

protected slots:
   void haveAbout()
   {
      AboutDlg dlg;
      dlg.exec();
   };
   void haveConfigure()
   {
      
      pConfigDlg->exec();
   };
   void calcTotals(bool force = false);

   void haveExit()
   {
      close();
   };

   void haveWorkorderRecord(QSqlRecord*, bool);
   void openConfigurationDialog(int conf);
   void havePreviewWoBtn();
   void setTabEnable(bool f)
   {
      tabsEnabled = f;
      printf("Ah3::setTabEnabled(): Enter, tabsEnabled = %d\n", tabsEnabled);
   };

protected:

private:
   int         currentTab;
   bool        tabsEnabled;
   QStatusBar  *status;
   Ui::Ah3     ui;
};

#endif
