/*********************************************************************************
**
**   $Id$
**   Copyright (c) 2004 Joe Croft <joe@croftj.net>
**   
**   This file is part of ah2.
**
**   Ah3 is free software; you can redistribute it and/or modify
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

#include <QApplication>
#include <QFileInfo>

#include "QcjData/QcjAction.h"
#include "QcjData/QcjDataLogin.h"
#include "QcjData/QcjDataStatics.h"
#include "QcjData/QcjDataXML.h"
#include "QcjData/QcjDataConfigure.h"
#include "QcjData/QcjDataReport.h"
#include "QcjData/QcjDataReportDocument.h"
#include "ah3.h"

QApplication *a;
Ah3 *mw;
QcjDataConfigure *pConfigDlg;

QStringList appPath;
QString appName;
QString reportPath;
QString invoiceReportFn;
QMap<int, QString> menuMap;

/**********************************************************************/
/*   Main function                                                    */
/**********************************************************************/
int main( int argc, char ** argv )
{
   QApplication a( argc, argv );
   printf("applicationName = |%s|\n", qPrintable(a.applicationName()));
   printf("applicationFilePath = |%s|\n", qPrintable(a.applicationFilePath()));
   printf("argv[0] = |%s|\n", qPrintable(a.arguments().at(0)));
   appPath = a.arguments().at(0).split(QRegExp("[/\\\\]"));
   QFileInfo appInfo(a.arguments().at(0));
   appName = appInfo.baseName();
   printf("testing appName\n");
   if ( appName.contains("ah3") ) 
   {
      printf("Replacing appName\n");
      appName = "ah3";
   }
   appPath.removeLast();
   printf("appName = |%s|\n", qPrintable(appName));
   fflush(stdout);

   pConfig = new QSettings("CroftJ", appName);
   pFormDef = new QcjDataXML(pConfig->value("XMLConfig", (QVariant)QcjDataForm::findXML(appPath, appName)).toString());
   
   printf("Building configure dialog\n");
   fflush(stdout);
   pConfigDlg = new QcjDataConfigure;
   pConfigDlg->initialize("app");

   mw = new Ah3;
   printf("Main window created!\n");
   fflush(stdout);

   QMenu *fileMenu = mw->menuBar()->addMenu("&File");
//   fileMenu->addAction("Refresh", &mw, SLOT(refresh()));
//   fileMenu->addAction("Print Invoice", &mw, SLOT(printInvoice()), QKeySequence(Qt::Key_Print));
//   fileMenu->addAction("&Save", mw, SLOT(saveCurrentForm()), QKeySequence::Save);
   fileMenu->addAction("&Print Invoice", mw, SLOT(havePreviewWoBtn()), QKeySequence::Print);
   fileMenu->addAction("&Close Invoice", mw, SLOT(haveCloseWoBtn()));
   fileMenu->addAction("Con&figure", pConfigDlg, SLOT(exec()));
   fileMenu->addAction("E&xit", mw, SLOT(close()));

   QMenu *editMenu = mw->menuBar()->addMenu("&Edit");
//   editMenu->addAction("&Refresh", mw, SLOT(refresh()), QKeySequence::Refresh);
#ifndef XS
   editMenu->addAction("Add &Parts", mw, SLOT(haveWoPartsRequest()));
   editMenu->addAction("Add &Labor", mw, SLOT(haveWoLaborRequest()));
   editMenu->addSeparator();
#endif
   editMenu->addAction("&Customers", mw, SLOT(haveEditCustomer()));
   editMenu->addSeparator();
   editMenu->addAction("&Refresh", mw, SLOT(refresh()), QKeySequence::Refresh);

//   editMenu->addAction("Update Record", mw, SLOT(haveUpdateRecord()), QKeySequence(Qt::Key_F10));
//   editMenu->addSeparator();

   QStringList confs = pFormDef->getConfigurationNames();
   QStringList::Iterator it;
   for (it = confs.begin(); it != confs.end(); it++) 
   {
      printf("main(): Adding Configuration menu for |%s|\n", qPrintable(*it));
      
      QcjAction *action = new QcjAction(editMenu->addAction(pFormDef->getConfigurationTitle(*it)), mw);
      menuMap[action->id()] = *it;
      a.connect(action, SIGNAL(doit(int)), mw, SLOT(openConfigurationDialog(int)));
   }

   QMenu *woMenu = mw->menuBar()->addMenu("Work&order");
   woMenu->addAction("&New Workorder", mw, SLOT(haveNewWoAction()));
   woMenu->addAction("New &Retail Workorder", mw, SLOT(haveRetailWoAction()));
   woMenu->addAction("&Print Invoice", mw, SLOT(havePreviewWoAction()));
   woMenu->addAction("&Delete Workorder", mw, SLOT(haveDeleteWoAction()));
   QMenu *reportMenu = mw->menuBar()->addMenu("&Reports");

   reportPath = pConfig->value("ReportPath", QcjDataReport::findReportsPath(appPath, appName)).toString();
   QMap<QString, QString> reportMap = QcjDataReportDocument::getReportList(reportPath);
   printf("main(): found %d reports\n", reportMap.count());
   QMapIterator<QString, QString> i(reportMap);
   while (i.hasNext()) 
   {
      i.next();
      printf("main(): checking report |%s|\n", qPrintable(i.key()));
      if ( i.key() == "Invoice" ) 
      {
         invoiceReportFn = i.value();
         printf("main(): Have invoice definition |%s|\n", qPrintable(invoiceReportFn));
      }
      else 
      {
         printf("main(): Adding Report menu for |%s|\n", qPrintable(i.key()));
         QcjAction *action = new QcjAction(reportMenu->addAction(i.key()), mw);
         menuMap[action->id()] = i.value();
         a.connect(action, SIGNAL(doit(int)), mw, SLOT(doReport(int)));
      }
   }

   QMenu *windowMenu = mw->menuBar()->addMenu("&Window");
#ifndef XS
   windowMenu->addAction("&Workorder", mw, SLOT(woActive()));
   windowMenu->addAction("Workorder &Select", mw, SLOT(woSelectActive()));
#else
   windowMenu->addAction("Workorder &Select", mw, SLOT(woSelectActive()));
   windowMenu->addAction("&Workorder", mw, SLOT(woActive()));
   windowMenu->addAction("Workorder &Parts", mw, SLOT(partsActive()));
   windowMenu->addAction("Workorder &Labor", mw, SLOT(laborActive()));
#endif
   windowMenu->addAction("Predefined &Jobs", mw, SLOT(jobsActive()));
   windowMenu->addAction("&Inventory", mw, SLOT(inventoryActive()));
#ifdef XS
   windowMenu->addAction("Inventory P&arts", mw, SLOT(invPartsActive()));
#endif
   windowMenu->addAction("&Vendors", mw, SLOT(vendorsActive()));

   QMenu *helpMenu = mw->menuBar()->addMenu("&Help");

   AboutDlg *pAbout = new AboutDlg;
   helpMenu->addAction("About", pAbout, SLOT(exec()));

   mw->show();
   printf("Setting Database!\n");
   fflush(stdout);
   mw->setDatabase();
   printf("Database set!\n");
   fflush(stdout);
   int rv = a.exec();
   pConfig->sync();
   printf("Here rv = %d!\n", rv);
   delete pConfig;
   exit(rv);
}


