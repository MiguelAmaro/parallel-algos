#include <stdio.h>
#include <stdint.h>
#include "bricksorter.h"

extern "C" __global__
void CudaKernel(void)
{
  printf("hello world from cuda <%d,%d>\n",blockIdx.x, threadIdx.x);
  return;
}
extern "C" void CudaRunCodeFromC(void)
{
  CudaKernel<<<10, 1>>>();
  cudaDeviceSynchronize();
  return;
}

extern "C" __global__
void BrickSortKernel(void)
{
  printf("hello from cuda brick sorter <%d,%d>\n",blockIdx.x, threadIdx.x);
  return;
}
extern "C" void BrickSortCuda(brick_sorter *BrickSorter)
{
  //calculate thread count based on list size
  BrickSortKernel<<<BrickSorter->Count, 1>>>();
  //get device memory copy struct into gpu memory
  //get device memory copy struct data into gpu memory
  //pass in to kernel
  cudaDeviceSynchronize();
  //copy everything back into host memory
  //return...
  return;
}
// int main(void) { return; } not needed