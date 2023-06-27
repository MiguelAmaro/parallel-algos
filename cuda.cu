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
extern "C" __global__
void DeviationKernel(double Mean, double *Data, uint64_t Count, double *Result)
{
  int Index = threadIdx.x + blockIdx.x * blockDim.x;
  int Stride = blockDim.x * gridDim.x;
  for(uint64_t i=Index; i<Count; i+=Stride)
  {
#if 0
    Result[i] = Data[i]-Mean;
#else
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
    Result[i] += Data[i]-Mean;
#endif
  }
  return;
}
extern "C" void SLRDeviationCuda(double Mean, double *Data, uint64_t Count, double *Result)
{
  double *DeviceDataSet;
  double *DeviceResult;
  // 記憶を割り当てコッピ
  uint64_t MemSize = sizeof(double)*Count;
  cudaMalloc(&DeviceDataSet, MemSize);
  cudaMalloc(&DeviceResult, MemSize);
  cudaMemcpy(DeviceDataSet, Data, MemSize, cudaMemcpyHostToDevice);
  
  cudaError_t err;
  err = cudaGetLastError(); // `cudaGetLastError` will return the error from above.
  if (err != cudaSuccess)
  {
    printf("Error: %s\n", cudaGetErrorString(err));
  }
  // スレッドの準備
  int DeviceId = 0;
  cudaGetDevice(&DeviceId);
  int SMCount = 0;
  cudaDeviceGetAttribute(&SMCount, cudaDevAttrMultiProcessorCount, DeviceId);
  uint64_t ThreadCountPerBlock = SMCount;
  uint64_t BlockCount  = (Count + ThreadCountPerBlock - 1)/ThreadCountPerBlock;
  DeviationKernel<<<BlockCount, ThreadCountPerBlock>>>(Mean, DeviceDataSet, Count, DeviceResult);
  cudaDeviceSynchronize();
  cudaMemcpy(Result, DeviceResult, MemSize, cudaMemcpyDeviceToHost);
  // 掃除
  cudaFree(DeviceDataSet);
  cudaFree(DeviceResult);
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