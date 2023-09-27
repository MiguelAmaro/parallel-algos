#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "mycuda.h"
#include "common.h"
#include "debug.h"
#include "bricksorter.h"
#include "csv.h"
#include "linear_reg.h"

// we should have runs to help us know weather odds should look left or right
// pairs are constructed and are sorted independently by their threads. there needs to be a way for threads to pick up new pairs
// 

void SwapUint32(uint32_t *a, uint32_t *b)
{
  uint32_t t = *a;
  *a = *b;
  *b =  t;
  return;
}
DWORD BrickSorterThreadProc(void *Param)
{
  brick_sorter *BrickSorter = (brick_sorter *)Param;
  ThreadWaitForEventSignal(BrickSorter->BeginSignal);
  printf("hello from thread[%5lu]\n", GetCurrentThreadId());
  
  uint32_t SafeCount = BrickSorter->Count - 1;
  uint32_t *Data     = BrickSorter->Data;
  while(BrickSorter->ShouldSort)
  {
    if(BrickSorter->NextPairIndex<=SafeCount)
    {
      uint32_t PairIndex = LockedAddAndGetLastValue(&BrickSorter->NextPairIndex, 2);
      int32_t  LookDir   = BrickSorter->RunId%2==0?-1:1;
      uint32_t IndexA = Max(0        , (LookDir<1)?PairIndex+LookDir:PairIndex);
      uint32_t IndexB = Min(SafeCount, (LookDir<1)?PairIndex:PairIndex+LookDir);
      if(Data[IndexA]>Data[IndexB])
      {
        SwapUint32(&Data[IndexA], &Data[IndexB]);
        LockedSetAndGetLastValue(&BrickSorter->SwapOccurred, 1);
        
      }
      if(PairIndex==SafeCount)
      {
        //if we are assigned the last pair index set state for next run
        //set next pair id to 1
        if(BrickSorter->SwapOccurred == 0)
        {
          LockedSetAndGetLastValue(&BrickSorter->ShouldSort, 0);
        }
        else
        {
          LockedSetAndGetLastValue(&BrickSorter->NextPairIndex, 1);
          LockedSetAndGetLastValue(&BrickSorter->SwapOccurred, 0);
          LockedAddAndGetLastValue(&BrickSorter->RunId, 1);
        }
      }
    }
  }
  printf("exiting... thread[%5lu]\n", GetCurrentThreadId());
  return 0;
}
void BrickSortParallel(brick_sorter *BrickSorter)
{
  ThreadBeginWork(BrickSorter->BeginSignal);
  ThreadSync(BrickSorter->ThreadHandles, BrickSorter->ThreadCount);
  return;
}
void BrickSortSerial(brick_sorter *BrickSorter)
{
  uint32_t *Data = BrickSorter->Data;
  uint32_t SafeCount = BrickSorter->Count - 1;
  // technically bubble sort
  for(uint32_t i=0;i<SafeCount; i++)
  {
    uint32_t SwapOccurred = 0;
    for(uint32_t j=0;j<SafeCount-i; j++)
    {
      if(Data[j] > Data[j+1])
      {
        SwapUint32(&Data[j], &Data[j+1]);
        SwapOccurred = 1;
      }
    }
    if(!SwapOccurred) break;
  }
  return;
}
void BrickSorterScrambleArray(brick_sorter *BrickSorter)
{
  for(uint32_t i=0;i<BrickSorter->Count;i++)
  {
    uint32_t RandIdx = BrickSorter->Count*((float)rand()/(float)RAND_MAX);
    SwapUint32(&BrickSorter->Data[i], &BrickSorter->Data[RandIdx]);
  }
  return;
}
void RandomInitF64(double *Data, uint64_t Count, double min, double max)
{
  double Range = max-min;
  for(uint64_t i=0;i<Count;i++)
  {
    double t = (double)rand()/(double)RAND_MAX;
    Data[i] = t*Range+min;
  }
  
  return;
}
void BrickSorterInit(brick_sorter *BrickSorter, uint64_t ArrayCount)
{
  //only 32 bit integers
  uint32_t  LogicalCoreCount = GetLogicalCoreCount();
  BrickSorter->BeginSignal   = ThreadCreateEvent("Brick Sort Begin Signal");
  BrickSorter->ThreadHandles = MemAlloc(LogicalCoreCount*sizeof(uint64_t));
  BrickSorter->ThreadCount = LogicalCoreCount;
  BrickSorter->Data        = MemAlloc(ArrayCount*sizeof(uint32_t));
  BrickSorter->Count = ArrayCount;
  BrickSorter->RunId = 0;
  BrickSorter->ShouldSort = 1;
  BrickSorter->NextPairIndex = 1; //first odd number
  //Initailize
  for(uint32_t i=0;i<BrickSorter->Count;i++)
  {
    BrickSorter->Data[i] = i;
  }
  //Launch Threads - keep them ready
  uint64_t ThreadCount = BrickSorter->ThreadCount;
  for(uint32_t ThreadIdx=0; ThreadIdx<ThreadCount; ThreadIdx++)
  {
    uint64_t ThreadHandle = ThreadCreate(BrickSorter, BrickSorterThreadProc);
    printf("thread launched... id:%lu\n", GetThreadId((HANDLE)ThreadHandle));
    BrickSorter->ThreadHandles[ThreadIdx] = ThreadHandle;
  }
  return;
}
void BrickSorterPrintArray(brick_sorter *BrickSorter, uint32_t ColumnCount)
{
  printf("[");
  for(uint32_t i=0;i<BrickSorter->Count;i++)
  {
    if(i%(ColumnCount)==0 && i != 0) printf("\n");
    printf("%d%s", BrickSorter->Data[i], i==BrickSorter->Count-1?"]\n":", ");
  }
  return;
}

int main(void)
{
  printf("hello from c\n");
  uint64_t BeginTick = 0;
  uint64_t EndTick   = 0;
  
  int8_t twoscomppos127 = -82;
  
  
  brick_sorter Sorter = {0};
  BrickSorterInit(&Sorter, 100);
  BrickSorterScrambleArray(&Sorter);
  printf("\n\n");
#if 0
  //SERIAL - CPU
  printf("serial cpu c\n");
  BrickSorterPrintArray(&Sorter, 10);
  {
    BeginTick = TimerGetTick();
    BrickSortSerial(&Sorter);
    EndTick = TimerGetTick();
  }
  printf("seconds elapsed: %fs\n", TimerGetSecondsElepsed(BeginTick, EndTick));
  BrickSorterPrintArray(&Sorter, 10);
  BrickSorterScrambleArray(&Sorter);
  printf("\n\n");
  
  //PARALLEL - CPU
  printf("parallel cpu c\n");
  BrickSorterPrintArray(&Sorter, 10);
  {
    BeginTick = TimerGetTick();
    BrickSortParallel(&Sorter);
    EndTick = TimerGetTick();
  }
  printf("seconds elapsed: %fs\n", TimerGetSecondsElepsed(BeginTick, EndTick));
  BrickSorterPrintArray(&Sorter, 10);
  BrickSorterScrambleArray(&Sorter);
  printf("\n\n");
  
  //PARALLEL - GPU
  printf("parallel gpu c\n");
  BrickSorterPrintArray(&Sorter, 10);
  {
    BeginTick = TimerGetTick();
    BrickSortCuda(&Sorter);
    EndTick = TimerGetTick();
  }
  printf("seconds elapsed: %fs\n", TimerGetSecondsElepsed(BeginTick, EndTick));
  BrickSorterPrintArray(&Sorter, 10);
  BrickSorterScrambleArray(&Sorter);
  printf("\n\n");
#endif
  
  SLRRun();
  
#if 0
  uint64_t MemSize = Megabytes(2);
  printf("%lld gb\n", MemSize);
  double  *DataSet = MemAlloc(MemSize);
  double  *Result  = MemAlloc(MemSize);
  uint64_t DataSetCount = MemSize/sizeof(double);
  uint64_t ResultCount  = MemSize/sizeof(double);
  RandomInitF64(DataSet, DataSetCount, -1, 1.0);
  
  double BestTime = F64Max;
  uint64_t TrialCount = 20;
  double Mean = SLRAverageF64(DataSet, DataSetCount);
  for(int i=0;i<TrialCount;i++)
  {
    BeginTick = TimerGetTick();
    SLRDeviationF64(Mean, DataSet, DataSetCount, Result, 0);
    EndTick = TimerGetTick();
    BestTime = Min(BestTime, TimerGetSecondsElepsed(BeginTick, EndTick));
    printf("mean %f | time: %f\n", Mean, BestTime);
  }
  printf("seconds elapsed: %fs\n", BestTime);
  BestTime = F64Max;
  for(int i=0;i<TrialCount;i++)
  {
    BeginTick = TimerGetTick();
    SLRDeviationF64(Mean, DataSet, DataSetCount, Result, 1);
    EndTick = TimerGetTick();
    BestTime = Min(BestTime, TimerGetSecondsElepsed(BeginTick, EndTick));
    printf("mean %f | time: %f\n", Mean, BestTime);
  }
  printf("seconds elapsed: %fs\n", BestTime);
#endif
  //for(int i=0; i<DataSetCount; i++) { printf("val: %f\n", DataSet[i]); }
  
  //END
  printf("done\n");
  return;
}