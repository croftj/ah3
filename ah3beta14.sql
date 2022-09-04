drop view workorders_v;

create view workorders_v as 
(select  workorders.ident, 
         workorders.closed, 
         workorders.r_tax, 
         workorders.r_labor, 
         customers.name, 
         vehicles.make, 
         vehicles.model, 
         vehicles.color, 
         vehicles.tag, 
         vehicles.vin, 
         workorders.parts, 
         workorders.labor, 
         workorders.date_in, 
         workorders.total, 
         workorders.vehicle, 
         workorders.customer 
   from customers, vehicles, workorders 
   where workorders.customer = customers.ident and workorders.vehicle = vehicles.ident);

create rule wo_view_delete as on delete to workorders_v
   do instead delete from workorders where ident = OLD.ident;

create rule wo_view_insert as on insert to workorders_v
   do instead insert into workorders (ident, customer, date_in, vehicle, closed, r_tax, r_labor) 
                 values (new.ident, new.customer, new.date_in, new.vehicle, new.closed, new.r_tax, new.r_labor);


