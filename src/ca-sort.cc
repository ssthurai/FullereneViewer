/*
 * Project: FullereneViewer
 * Version: 1.0
 * Copyright: (C) 2011-14 Dr.Sc.KAWAMOTO,Takuji (Ext)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Version.h"
#include "GeneratorLine.h"
#include "DistanceSummaryLine.h"
#include "Set.h"
#include "DebugMemory.h"

void usage(char* argv0)
{
  fprintf(stderr, "usage: %s < infile > outfile\n", argv0);
  fprintf(stderr, "     infile ..... generator formula lines,\n");
  fprintf(stderr, "               or distance summary lines.\n");
  exit(1);
}

int main(int argc, char* argv[])
{
  if ((argc == 2) &&
      ((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "--version") == 0)))
    {
      print_version("ca-sort");
      exit(0);
    }
  if (argc != 1)
    usage(argv[0]);
  setvbuf(stdout, 0, _IONBF, 0);
  print_version("ca-sort", stdout);
  char buffer[1024];
  while (1)
    {
      if (fgets(buffer, 1024, stdin) != buffer)
        exit(0);
      if (buffer[0] != '#')
        break;
    }
  if (buffer[0] == 'C')
    {
      Set<GeneratorLine> lines;
      while (1)
        {
          buffer[strlen(buffer) - 1] = '\0';
          if (buffer[0] != '#')
            {
              GeneratorLine* gtl = new GeneratorLine(buffer);
              GeneratorLine* result = lines.search_else_add(gtl);
              assert(result == 0);
            }
          if (fgets(buffer, 1024, stdin) != buffer)
            break;
        }
      int len = lines.length();
      for (int i = 0; i < len; ++i)
        lines[i]->print();
    }
  else
    {
      Set<DistanceSummaryLine> lines;
      while (1)
        {
          buffer[strlen(buffer) - 1] = '\0';
          if (buffer[0] != '#')
            {
              DistanceSummaryLine* dsl = new DistanceSummaryLine(buffer);
              DistanceSummaryLine* result = lines.search_else_add(dsl);
              assert(result == 0);
            }
          if (fgets(buffer, 1024, stdin) != buffer)
            break;
        }
      int len = lines.length();
      for (int i = 0; i < len; ++i)
        lines[i]->print();
    }
  return 0;
}

/* Local Variables:	*/
/* mode: c++		*/
/* End:			*/
