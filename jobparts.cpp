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

# include <QSqlDriver>
# include "jobparts.h"

void JobParts::setParentJob(AutoJob *pj)
{
   printf("JobParts::setParentJob(): Enter\n");
   fflush(stdout);
   parentJob = pj;
   QString job = pj->getIndexValue();
   QSqlField fjob("job", QVariant::Int);
   fjob.setValue(job);
   QString where("job = " + pDb->driver()->formatValue(fjob));
   printf("JobParts::setParentJob(): Where = |%s|\n", qPrintable(where));
   fflush(stdout);
   printf("JobParts::setParentJob(): dataTable  = %ld\n", (long)ui.dataTable);
   ui.dataTable->setFilter(where);
   printf("JobParts::setParentJob():Exit\n");
   fflush(stdout);
}

void JobParts::haveNewAction()
{
   printf("JobParts::haveNewAction(): Enter\n");
   fflush(stdout);
   QString job = parentJob->getIndexValue();
   printf("JobParts::haveNewAction(): Creating new parts record for job %s\n", qPrintable(job));
   fflush(stdout);
   QMap<QString, QString> fields;
   fields.insert("job", job);
   ui.dataForm->insertRecord(fields);
   ui.dataTable->refresh();
   ui.dataTable->findRow(ui.dataForm->getIndexMap());
   ui.dataFrame->setState(Qcj::Insert);
   printf("JobParts::haveNewAction(): Exit\n");
   fflush(stdout);
}
