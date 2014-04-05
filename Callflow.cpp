
/**
 * 
 * Author      : D.Dinesh
 *
 * Created     : 05 Apr 2014 - Sat
 * Updated     : 05 Apr 2014 - Sat
 *
 * Licence     : Refer the licence file
 *
 **/

#include "Callflow.h"

Callflow callflow;
int Callflow::level = 0;
Callflow::Node *Callflow::base = 0;
Callflow::Node *Callflow::last = 0;

Callflow::Callflow()
{
   last = base = new Node;
   memset(base, 0, sizeof(Node));
   signal(SIGSEGV, ShutCallflow);
}

Callflow::Callflow(int line, const char *szFunc, const char *szFile)
{
   Callflow::level++;
   Node *node = new Node;
   node->level = level;
   node->szFunc = szFunc;
   node->szFile = szFile;
   node->line = line;
   node->next = 0;
   last->next = node;
   last = node;
}

void Callflow::ShutCallflow(int sig)
{
   Node *node = base->next;
   printf("%s [%s:%d]\n", node->szFunc, node->szFile, node->line);
   for(node=node->next;node;node=node->next)
   {
      char str[32];
      if(node->next) 
         strcpy(str, "|   ");
      else strcpy(str, "    ");
      int M = node->level - 1;
      for(int I = 1; I < M; I++)
         printf(str);
      if(0 == node->next || node->level > node->next->level)
         putchar('`');
      else putchar('|');
      printf("-- %s [%s:%d]\n", node->szFunc, node->szFile, node->line);
   }
   exit(0);
}

Callflow::~Callflow()
{
   level--;
}
