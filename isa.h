#ifndef ISA_H
#define ISA_H
/*!
      \fn bool isA(QObject *obj, const char *type)

       Tests  the  passed  object  to  be  of  the  type  specified by
       <em>type</em>.
*/ 
static bool isA(QObject *obj, const char *type)
{
    printf("isA(): Enter\n");
    fflush(stdout);
    if ( obj != 0 ) 
    {
       const QMetaObject *mobj = obj->metaObject();
       while (mobj != NULL) 
       {
           printf("isA(): className = |%s|\n", mobj->className());
           fflush(stdout);
           if ( QString(mobj->className()) == QString(type) ) 
           {
               printf("isA(): Exit(true)\n");
               fflush(stdout);
               return(true);
           }
           mobj = mobj->superClass();
       }
    }
    else
      printf("isA(): Object is a Null pointer\n");
    printf("isA(): Exit(false)\n");
    fflush(stdout);
    return(false);
}

#endif
