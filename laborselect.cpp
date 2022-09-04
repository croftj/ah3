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

# include "laborselect.h"

/**********************************************************************/
/*   void haveAddJobBtn()                                                 */
/*                                                                    */
/*   Slot  to  be  activated when the New Job Signal is received. It  */
/*   will create a new Job in the database                            */
/**********************************************************************/
void LaborSelect::haveAddJobBtn()
{
   printf("Ah3::haveAddJobBtn(): Enter\n");
   QString xmldef = ui.jobSelectTable->readXmlDef();
   QString index = pFormDef->getIndexField(xmldef);

   QString job_ident = ui.jobSelectTable->currentRecord()->field(index).value().toString();

   QString sql = "select descr, labor, charge4parts from jobs where ident = :ident";
   printf("Ah3::haveAddJobBtn():sql = |%s|, ident = |%s|\n", qPrintable(sql), qPrintable(job_ident));
   fflush(stdout);
   QSqlQuery q;
   q.prepare(sql);
   q.bindValue(":ident", job_ident);
   q.exec();
   fflush(stdout);
   if ( q.next() ) 
   {
      printf("Ah3::haveAddJobBtn(): Found labor: descr = |%s|\n", qPrintable(q.value(0).toString()));
      fflush(stdout);
      QString descr = q.value(0).toString();
      QString hours  = q.value(1).toString();
      QString charge4parts  = q.value(2).toString();

      QMap<QString, QString> fields;
      fields["workorder"] = QString::number(workorder);
      fields["job"] = job_ident;
      fields["descr"] = descr;
      fields["hours"] = hours;
      ui.laborForm->insertRecord(fields);

      printf("Ah3::haveAddJobBtn(): record ident = |%s|\n", qPrintable(ui.laborForm->record()->field("ident").value().toString()));
      fflush(stdout);
      QString labor_ident = ui.laborForm->getFieldText("ident");
      printf("Ah3::haveAddJobBtn(): labor_ident |%s|\n", qPrintable(labor_ident));
      fflush(stdout);
      QString filter = "workorder = '" + QString::number(workorder) + 
                       "' and job = '" + labor_ident + "'";
      ui.partsTable->setFilter(filter);

      ui.laborForm->updateRecord();

      sql = "select pn, descr, qty, measure, cost from job_parts where job = :job";
      printf("Ah3::haveAddJobBtn(): Found parts: sql = |%s|\n", qPrintable(sql));
      fflush(stdout);
      QSqlQuery q1;
      q1.prepare(sql);
      q1.bindValue(":job", job_ident);
      q1.exec();
      while ( q1.next() ) 
      {
         QString pn        = q1.value(0).toString();
         QString descr     = q1.value(1).toString();
         QString qty       = q1.value(2).toString();
         QString measure   = q1.value(3).toString();
         QString cost      = q1.value(4).toString();

         fields.clear();
         fields["workorder"]  = QString::number(workorder);
         fields["job"]        = labor_ident;
         fields["pn"]         = pn;
         fields["descr"]      = descr;
         fields["qty"]        = qty;
         fields["measure"]    = measure;
         fields["cost"]       = cost;
         ui.partsForm->insertRecord(fields);
         ui.partsForm->updateRecord();
      }
      ui.partsTable->refresh();
      ui.laborTable->refresh();
      fields.clear();
      fields["ident"] = labor_ident;
      ui.laborTable->findRow(fields);
   }
   printf("Ah3::haveAddJobBtn(): Exit\n");
}

void LaborSelect::haveDelJobBtn()
{
   printf("Ah3::haveDelJobBtn(): Enter\n");
   ui.laborForm->deleteRecord();
   ui.laborTable->refresh();
   ui.laborTable->selectRow(0);
   ui.partsTable->refresh();
   printf("Ah3::haveDelJobBtn(): Exit\n");
}

void LaborSelect::haveSavePartBtn()
{
   
}

void LaborSelect::haveDelPartBtn()
{
   
}

void LaborSelect::haveLaborRecord(QSqlRecord *rec)
{
   printf("Ah3::haveLaborRecord(): Enter\n");
   QString labor_ident = rec->field("ident").value().toString();
   QString filter = "workorder = '" + QString::number(workorder) + 
                     "' and job = '" + labor_ident + "'";
   ui.partsTable->setFilter(filter);
   printf("Ah3::haveLaborRecord(): Exit\n");
}

void LaborSelect::haveJobRecord(QSqlRecord*)
{
   
}
