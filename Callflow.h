
/**
 * 
 * Author      : D.Dinesh
 *
 * Created     : 05 Apr 2014 - Sat
 * Updated     : 05 Apr 2014 - Sat
 *
 * Licence     : Refer the license file
 *
 **/

#ifndef _CALLFLOW_H_
#define _CALLFLOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

class Callflow
{
   struct Node
   {
      int line;
      int level;
      Node *next;
      const char *szFunc;
      const char *szFile;
   };

   static int level;
   static Node *base, *last;
   static void ShutCallflow(int sig);

   public :
   Callflow();
   Callflow(int line, const char *szFunc, const char *szFile);
   ~Callflow();
};

#define _trace_callflow_ Callflow callflow(__LINE__, __FUNCTION__, __FILE__);

#endif
