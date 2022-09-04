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

# include "partselect.h"
# include "wopartentry.h"

void WoPartEntry::haveLookupBtn()
{
   printf("WoPartEntry::haveLookupBtn(): Enter\n");
   fflush(stdout);
   PartSelect dlg(this);
   dlg.setDatabase();
   int part = dlg.exec();
   printf("WoPartEntry::haveLookupBtn(): Part selected ident = %d\n", part);
   fflush(stdout);
   if ( part > 0 ) 
   {
      QString sql = "select pn, descr, retail, measure from parts_v where ident = :ident";
      printf("WoPartEntry::haveLookupBtn(): Found part: sql = |%s|\n", qPrintable(sql));
      fflush(stdout);
      QSqlQuery q;
      q.prepare(sql);
      q.bindValue(":ident", part);
      q.exec();
      printf("WoPartEntry::haveLookupBtn(): Found part: sql = |%s|\n", qPrintable(q.lastQuery()));
      fflush(stdout);
      if ( q.next() ) 
      {
         printf("WoPartEntry::haveLookupBtn(): Found part: pn = |%s|\n", qPrintable(q.value(0).toString()));
         fflush(stdout);
         QMap<QString, QString> fields;
         fields["workorder"] = QString::number(workorder);
         fields["part"] = QString::number(part);
         fields["pn"] = q.value(0).toString();
         fields["descr"] = q.value(1).toString();
         fields["cost"] = q.value(2).toString();
         fields["measure"] = q.value(3).toString();

         if ( ui.dataForm->insertActive() ) 
         {
            foreach ( QString field, fields.keys() )
               ui.dataForm->setFieldText(field, fields.value(field));
         }
         else 
         {
            ui.dataForm->insertRecord(fields);
            ui.dataFrame->setState(Qcj::Insert);
         }
      }
   }
   printf("WoPartEntry::haveLookupBtn(): Exit\n");
   fflush(stdout);
}
