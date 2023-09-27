#ifndef BRICKSORTER_H
#define BRICKSORTER_H

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

#ifdef __cplusplus
extern "C" void BrickSortCuda(brick_sorter *BrickSorter);
#else
void BrickSortCuda(brick_sorter *BrickSorter);
#endif
#endif //BRICKSORTER_H
