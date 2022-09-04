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

#ifndef INVENTORYFRAME_H
#define INVENTORYFRAME_H

# include <QFrame>
# include <QSqlRecord>

# include "ui_inventoryframe.h"

class InventoryFrame : public QFrame 
{
   Q_OBJECT

public:
   InventoryFrame(QWidget *parent = 0) : QFrame(parent)
   {
      printf("InventoryFrame::InventoryFrame(): Enter\n");
      ui.setupUi(this);
      printf("InventoryFrame::InventoryFrame(): Exit\n");
      fflush(stdout);
   };

   void setDatabase();

protected:
   enum Mode  
   {
      Updated = 0,
      Insert
   };

protected slots:
   void setMode(InventoryFrame::Mode mode);

   void refreshVendorForm(int vendor);
   void havePartSelected(QSqlRecord*);
   void haveVendorPartSelected(QSqlRecord *rec);

   void haveDeleteVendor();
   void haveAddVendor();
   void haveSaveVendor();

   void haveDelAction(bool)
   {
      haveDeleteVendor();
   };

   void haveNewAction(bool)
   {
      haveAddVendor();
   };

   void haveSaveAction(bool)
   {
      haveSaveVendor();
   };

   void haveDownAction(bool);
   void haveUpAction(bool);

private:
   int                  currentPart;
   Mode                 frameMode;

   QAction              *delAction;
   QAction              *newAction;
   QAction              *downAction;
   QAction              *saveAction;
   QAction              *upAction;

   Ui::InventoryFrame   ui;
};

#endif
