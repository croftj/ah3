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


/**********************************************************************/
/*   This file holds the code to manage the Auto-Jobs Tab.            */
/**********************************************************************/

# include <QMessageBox>

#include "QcjData/QcjDataConfigure.h"
#include "QcjData/QcjDataReport.h"
#include "QcjData/QcjDataStatics.h"

# include "ah3.h"

void Ah3::haveNewJobPartBtn()
{
   printf("Ah3::haveNewJobPartBtn(): Enter\n");
   QString xmldef = ui.autoJobForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);
   QString index_value = ui.autoJobForm->getFieldText(index);
   printf("Ah3::haveNewJobPartBtn(): Current Job index field |%s| == |%s|\n", qPrintable(index), qPrintable(index_value));
   fflush(stdout);

   QMap<QString, QString> fields;
   fields.insert("job", index_value);
   ui.jobPartForm->insertRecord(fields);
   printf("Ah3::haveNewJobPartBtn(): Exit\n");
}

void Ah3::haveDeleteJobPartBtn()
{
   printf("Ah3::haveDeleteJobPartBtn(): Enter\n");
   ui.jobPartForm->deleteRecord();
   printf("Ah3::haveDeleteJobPartBtn(): Exit\n");
}

void Ah3::haveSaveJobPartBtn()
{
   printf("Ah3::haveSaveJobPartBtn(): Enter\n");
   ui.jobPartForm->updateRecord();
   printf("Ah3::haveSaveJobPartBtn(): Exit\n");
}

void Ah3::haveNewJobBtn()
{
   printf("Ah3::haveNewJobBtn(): Enter\n");
   ui.autoJobForm->insertRecord();
   ui.autoJobTable->refresh();
   QMap<QString, QString> index = ui.autoJobForm->getIndexMap();
   ui.autoJobTable->findRow(index);
//   QString xmldef = ui.autoJobForm->readXmlDef();
//   QString index = pFormDef->getIndexField(xmldef);
//   QString index_value = ui.autoJobForm->getFieldText(index);
//   printf("Ah3::haveNewJobBtn(): Have new record, index field |%s| == |%s|\n", qPrintable(index), qPrintable(index_value));
//   fflush(stdout);
//   ui.autoJobTable->setFilter("job = '" + index + "'");
   printf("Ah3::haveNewJobBtn(): Exit\n");
}

void Ah3::haveDeleteJobBtn()
{
   printf("Ah3::haveDeleteJobBtn(): Enter\n");
   ui.autoJobForm->deleteRecord();
   printf("Ah3::haveDeleteJobBtn(): Exit\n");
}

void Ah3::haveSaveJobBtn()
{
   printf("Ah3::haveSaveJobBtn(): Enter\n");
   ui.autoJobForm->updateRecord();

   QString xmldef = ui.autoJobForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);
   QString index_value = ui.autoJobForm->getFieldText(index);
   printf("Ah3::haveSaveJobBtn(): Have new record, index field |%s| == |%s|\n", qPrintable(index), qPrintable(index_value));
   fflush(stdout);
   ui.jobPartTable->setFilter("job = '" + index + "'");

   QMap<QString, QString> make = ui.autoJobForm->getIndexMap();
   ui.autoJobTable->findRow(make);
   printf("Ah3::haveSaveJobBtn(): Exit\n");
}

void Ah3::haveSearchJobBtn()
{
   QStringList sl;

   QString xmldef = ui.autoJobForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);

   sl << index;
   QString filter = ui.autoJobForm->makeFilter(sl);
   ui.autoJobTable->setFilter(filter);
}

void Ah3::haveClearJobBtn()
{
   ui.autoJobTable->setFilter("");
   ui.autoJobForm->clearForm();
}

void Ah3::refreshAutoJobForm(QSqlRecord *rec)
{
   printf("Ah3::refreshAutoJobForm(): Enter\n");
   ui.autoJobForm->refresh(rec);
   QString xmldef = ui.autoJobForm->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);
   QString index_value = ui.autoJobForm->getFieldText(index);
   printf("Ah3::refreshAutoJobForm(): Have new record, index field |%s| == |%s|\n", qPrintable(index), qPrintable(index_value));
   fflush(stdout);
   ui.jobPartTable->setFilter("job = '" + index_value + "'");
   printf("Ah3::refreshAutoJobForm(): Exit\n");
}


