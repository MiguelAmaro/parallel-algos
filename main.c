#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mycuda.h"
#include "windows.h"
#include "common.h"

// we should have runs to help us know weather odds should look left or right
// pairs are constructed and are sorted independently by their threads. there needs to be a way for threads to pick up new pairs
// 
typedef struct brick_sorter brick_sorter;
struct brick_sorter
{
  uint64_t  BeginSignal;
  uint64_t *ThreadHandles;
  uint64_t  ThreadCount;
  uint32_t *Data;
  uint32_t  Count;
  volatile uint64_t  ShouldSort;
  volatile uint64_t  SwapOccurred;
  volatile uint64_t  RunId;
  volatile uint64_t  NextPairIndex;
};
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
void BrickSorterPrintArray(brick_sorter *BrickSorter)
{
  printf("[");
  for(uint32_t i=0;i<BrickSorter->Count;i++)
  {
    printf("%d%s", BrickSorter->Data[i], i==BrickSorter->Count-1?"]\n":", ");
  }
  return;
}

int main(void)
{
  printf("hello from c\n");
  uint64_t BeginTick = 0;
  uint64_t EndTick   = 0;
  
  brick_sorter Sorter = {0};
  BrickSorterInit(&Sorter, 4);
  Sorter.Data[0] = 3;
  Sorter.Data[1] = 2;
  Sorter.Data[2] = 1;
  Sorter.Data[3] = 0;
  BrickSorterPrintArray(&Sorter);
  
  //SERIAL - CPU
  printf("serial cpu c\n");
  BeginTick = TimerGetTick();
  //BrickSortSerial(&Sorter);
  EndTick = TimerGetTick();
  printf("seconds elapsed: %fs\n", TimerGetSecondsElepsed(BeginTick, EndTick));
  BrickSorterPrintArray(&Sorter);
  
  //PARALLEL - CPU
  printf("parallel cpu c\n");
  BeginTick = TimerGetTick();
  BrickSortParallel(&Sorter);
  EndTick = TimerGetTick();
  printf("seconds elapsed: %fs\n", TimerGetSecondsElepsed(BeginTick, EndTick));
  BrickSorterPrintArray(&Sorter);
  printf("\n\n\n\n");
  
  //PARALLEL - GPU
  printf("parallel gpu c\n");
  BeginTick = TimerGetTick();
  CudaRunCodeFromC();
  EndTick = TimerGetTick();
  printf("seconds elapsed: %fs\n", TimerGetSecondsElepsed(BeginTick, EndTick));
  
  //END
  printf("done\n");
  return;
}