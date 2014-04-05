
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

#include "Callflow.h"

/************ Function decalaration **********/
void Function11(); void Function12(); void Function13(); 
void Function14(); void Function15();

void Function21(); void Function22(); void Function23(); 
void Function24(); void Function25();

void Function31(); void Function32(); void Function33();

/********** Function defenition **********/
void Function11() { _trace_callflow_ Function21(); Function22(); Function23(); Function24(); Function25(); }
void Function12() { _trace_callflow_ Function21(); Function22(); }
void Function13() { _trace_callflow_ }
void Function14() { _trace_callflow_ }
void Function15() { _trace_callflow_ }

void Function21() { _trace_callflow_  Function31(); Function32(); }
void Function22() { _trace_callflow_  Function31(); Function32(); }
void Function23() { _trace_callflow_ }
void Function24() { _trace_callflow_ }
void Function25() { _trace_callflow_ }

void Function31() { _trace_callflow_ }
void Function32() { _trace_callflow_ }

int main()
{
   _trace_callflow_

   Function11();
   Function12();
   Function13();
   Function14();
   Function15();

   puts((char *)0);
   return 0;

}
