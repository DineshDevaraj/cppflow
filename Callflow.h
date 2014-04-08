
/**
 * 
 * Author      : D.Dinesh
 * Licence     : Refer the license file
 *
 **/

#ifndef _CALLFLOW_H_
#define _CALLFLOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

struct Callflow
{
   Callflow(int line, const char *szFunc, const char *szFile);
   ~Callflow();
};

#define _trace_callflow_ Callflow callflow(__LINE__, __FUNCTION__, __FILE__);

#endif
