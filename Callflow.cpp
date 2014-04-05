
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

Callflow callflow;
int Callflow::level = 0;
int Callflow::max_level = 0;
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
   level++;
   if(level > max_level)
      max_level = level;

   Node *node = new Node;
   node->next = 0;
   node->line = line;
   node->level = level;
   node->szFunc = szFunc;
   node->szFile = szFile;

   last->next = node;
   last = node;
}

int Callflow::SslExistAtLevel(int level, Node *node)
{
   for(node = node->next; node; node = node->next)
      if(node->level < level) return 0;
      else if(node->level == level) return 1;
   return 0;
}

void Callflow::ShutCallflow(int sig)
{
   Node *node = base->next;
   bool *pSsl = new bool[max_level - 1]; /* succeeding sibling */
   printf("%s [%s:%d]\n", node->szFunc, node->szFile, node->line);

   for(node=node->next;node;node=node->next)
   {

      /* I -> Index  */
      /* L -> Level  */
      /* M -> Memory */

      int I = 0;
      int M = node->level - 1;
      memset(pSsl, true, max_level - 1);

      for(int L = 1; L < M; L++)
      {
         I = L - 1;
         if(pSsl[I])
         {
            pSsl[I] = SslExistAtLevel(L + 1, node);
            if(pSsl[I]) printf("|   ");
            else printf("    ");
         }
         else
         {
            printf("    ");
         }
      }

      if(0 == node->next || node->level > node->next->level ||
            (node->level < node->next->level && 
             !SslExistAtLevel(node->next->level - 1, node->next)))
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
