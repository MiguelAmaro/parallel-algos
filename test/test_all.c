#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "mycuda.h"
#include "windows.h"
#include "common.h"
#include "debug.h"
#include "csv.h"
#include "linear_reg.h"

#define TEST_PASSED (1)
#define TEST_FAILED (0)


#define TESTCOLOR_PASSED (1)
#define TESTCOLOR_FAILED (0)
#define TESTCOLOR_WHITE (6)

const char *TestColorTable[] = 
{
  "\x1b[31m", //ColorRed
  "\x1b[32m", //ColorGreen
  "\x1b[33m", //ColorYellow
  "\x1b[34m", //ColorBlue
  "\x1b[35m", //ColorMagenta
  "\x1b[96m", //ColorCyan
  "\x1b[0m"   //ColorWhite
};

void Test(const char *FuncName, double Result, double Expected)
{
  uint32_t TestStatus  = (Result == Expected);
  const char *StatusColor = (TestStatus==TEST_PASSED?
                             TestColorTable[TESTCOLOR_PASSED]:
                             TestColorTable[TESTCOLOR_FAILED]);
  printf("%s", StatusColor);
  printf("Testing: %s, Result: %f, Expected: %f\n", FuncName, Result, Expected);
  printf("%s", TestColorTable[TESTCOLOR_WHITE]);
  return;
}
void TestingDone() { printf("testing done..."); }

#define TEST(fn_name, fn_result, fn_expected) Test(#fn_name, fn_result, fn_expected)


int main(void)
{
  double TestData[] = {10.0, -10.0};
  TEST(SLRAverageF64, SLRAverageF64(TestData, ArrayCount(TestData)), 0.0);
  double TestData2[] = {0.0, -10.0, -5.0};
  TEST(SLRAverageF64, SLRAverageF64(TestData2, ArrayCount(TestData2)), -5.0);
  
  TestingDone();
  return;
}
