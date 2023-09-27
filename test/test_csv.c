#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

//#include "mycuda.h"
//#include "bricksorter.h"
//#include "linear_reg.h"
#include "windows.h"
#include "common.h"
#include "csv.h"


int main(void)
{
  arena Arena = ArenaAlloc(Megabytes(10));
#if 0
  const char *Source = 
    "2.3,0.0,4.0\n"
    "400.3,0.0,100.0\n"
    "500.3,0.90,100.0, 20.0\n";
  csv CSV = CSVInit(Source, strlen(Source), &Arena);
#else
  csv CSV = CSVInitFromFile("..\\data\\housing00.csv", &Arena);
#endif
  return 0;
}