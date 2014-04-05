
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

struct Node
{
   int m_line;
   int m_level;
   Node *m_next;
   const char *m_szFunc;
   const char *m_szFile;
};

Callflow callflow;

static int g_level = 0;
static Node *g_base = 0;
static Node *g_last = 0;
static int g_max_level = 0;

static void ShutCallflow(int sig);
static int SslExistAtLevel(int level, Node *node);

int SslExistAtLevel(int level, Node *node)
{
   for(node = node->m_next; node; node = node->m_next)
      if(node->m_level < level) return 0;
      else if(node->m_level == level) return 1;
   return 0;
}

void ShutCallflow(int sig)
{
   Node *node = g_base->m_next;
   bool *pSsl = new bool[g_max_level - 1]; /* succeeding sibling */
   printf("%s [%s:%d]\n", node->m_szFunc, node->m_szFile, node->m_line);

   for(node = node->m_next; node; node = node->m_next)
   {

      /* I -> Index  */
      /* L -> Level  */
      /* M -> Memory */

      int I = 0;
      int M = node->m_level - 1;
      memset(pSsl, true, g_max_level - 1);

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

      if(0 == node->m_next || node->m_level > node->m_next->m_level ||
            (node->m_level < node->m_next->m_level && 
             !SslExistAtLevel(node->m_next->m_level - 1, node->m_next)))
         putchar('`');
      else putchar('|');

      printf("-- %s [%s:%d]\n", node->m_szFunc, node->m_szFile, node->m_line);
   }

   exit(0);
}

Callflow::Callflow()
{
   g_last = g_base = new Node;
   signal(SIGSEGV, ShutCallflow);
}

Callflow::Callflow(int line, const char *szFunc, const char *szFile)
{
   g_level++;
   if(g_level > g_max_level)
      g_max_level = g_level;

   Node *node = new Node;
   node->m_next = 0;
   node->m_line = line;
   node->m_level = g_level;
   node->m_szFunc = szFunc;
   node->m_szFile = szFile;

   g_last->m_next = node;
   g_last = node;
}

Callflow::~Callflow()
{
   g_level--;
}
