#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wincrypt.h>

#define Assert(cond) while(!cond) { __debugbreak(); }
#define Bytes(x) (1llu*x)
#define Kilobytes(x) (1024llu*Bytes(x))
#define Megabytes(x) (1024llu*Kilobytes(x))
#define Gigabytes(x) (1024llu*Megabytes(x))
#define ArrayCount(array) (sizeof(array)/sizeof(array[0]))
#define Min(a, b) ((a)<(b)?(a):(b)) 
#define Max(a, b) ((a)>(b)?(a):(b))
#include <float.h>
#define F64Max DBL_MAX
#define F64Min DBL_MIN

int GetLogicalCoreCount(void)
{
  //https://stackoverflow.com/questions/28893786/how-to-get-the-number-of-actual-cores-on-the-cpu-on-windows
  SYSTEM_INFO SystemInfo = {0};
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX ProcessorInfo= {0};
  DWORD Length = 0;
  GetSystemInfo(&SystemInfo);
  GetLogicalProcessorInformationEx(RelationProcessorPackage, &ProcessorInfo, &Length);
  uint32_t Result = SystemInfo.dwNumberOfProcessors;
  return Result;
}
void KillProcess(void)
{
  ExitProcess(1);
  return;
}
//~Timer
typedef struct timer timer;
struct timer
{
  uint32_t IsInitialized;
  uint64_t Frequency;
};
timer GlobalTimer = {0};
void TimerInit(void)
{
  LARGE_INTEGER Freq = {0};
  QueryPerformanceFrequency(&Freq);
  GlobalTimer.Frequency = Freq.QuadPart;
  GlobalTimer.IsInitialized = 1;
}
uint64_t TimerGetTick(void)
{
  LARGE_INTEGER Tick = {0};
  QueryPerformanceCounter(&Tick);
  uint64_t Result = Tick.QuadPart;
  return Result;
}
double TimerGetSecondsElepsed(uint64_t StartTick, uint64_t EndTick)
{
  if(!GlobalTimer.IsInitialized) TimerInit();
  uint64_t Delta = EndTick-StartTick;
  double Result = (Delta*1.0)/(double)GlobalTimer.Frequency;
  return Result;
}
//~Threads
typedef DWORD threadproc(void *);
uint64_t ThreadCreate(void *Param, threadproc ThreadProc)
{
  DWORD ThreadId;
  HANDLE ThreadHandle = CreateThread(0, 0, ThreadProc, Param, 0, &ThreadId);
  return (uint64_t)ThreadHandle;
}
void ThreadKill(void)
{
  ExitThread(0);
  return;
}
void ThreadSync(uint64_t *ThreadHandles, uint32_t ThreadCount)
{
  WaitForMultipleObjects(ThreadCount, (HANDLE *)ThreadHandles, TRUE, INFINITE);
  return;
}
void ThreadBeginWork(uint64_t BeginSignal)
{
  if(SetEvent((HANDLE)BeginSignal)) { fprintf(stderr, "work begin signal set.\n"); }
  else                              { fprintf(stderr, "Error setting work queue begin signal.\n"); }
  return;
}
uint64_t ThreadCreateEvent(const char *EventName)
{
  uint64_t EventHandle = (uint64_t)CreateEvent(NULL, TRUE, FALSE, TEXT(EventName));
  return EventHandle;
}
void ThreadWaitForEventSignal(uint64_t EventSignal)
{
  WaitForSingleObject((HANDLE)EventSignal, INFINITE); 
  return;
}

//~Atomics
uint64_t LockedAddAndGetLastValue(uint64_t volatile *Target, uint64_t Addend)
{
  uint64_t Result = InterlockedExchangeAdd64((volatile LONG64 *)Target, Addend);
  return Result;
}
uint64_t LockedSetAndGetLastValue(uint64_t volatile *Target, uint64_t Value)
{
  uint64_t Result = InterlockedExchange64((volatile LONG64 *)Target, Value);
  return Result;
}

//~Memory
void *MemAlloc(uint64_t Size)
{
  //we get commit and entire 4k page
  void *Ptr = VirtualAlloc(0, Size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  return Ptr;
}
void MemFree(void *Ptr)
{
  VirtualFree(Ptr, 0, MEM_RELEASE);
  return;
}
typedef struct arena arena;
struct arena
{
  void     *Base;
  uint64_t  Offset;
  uint64_t  Capacity;
};
arena ArenaInit(uint64_t *Memory, uint64_t Capacity)
{
  arena Result = { .Base = Memory, .Capacity = Capacity, .Offset = 0 };
  return Result;
}
arena ArenaAlloc(uint64_t Capacity)
{
  arena Result = ArenaInit(MemAlloc(Capacity), Capacity);
  return Result;
}
void ArenaFree(arena *Arena)
{
  MemFree(Arena->Base);
  return;
}
void *ArenaPushBlock(arena *Arena, uint64_t Size)
{
  void *Result = NULL;
  uint64_t Start = (uint64_t)Arena->Base;
  uint64_t End   = Start + Arena->Capacity;
  if((Start + Arena->Offset + Size)<End)
  {
    Result = (void *)(Start + Arena->Offset);
    Arena->Offset += Size;
  }
  else
  {
    
    printf("arena capacity is too small for resquested allocation");
    Assert("Invalid Codepath");
  }
  return Result;
}

#define ArenaPushArray(arena_ptr, count, type) ArenaPushBlock(arena_ptr, count*sizeof(type))
#define ArenaPushType(arena_ptr, type) ArenaPushBlock(arena_ptr, sizeof(type))

//~Math
double SquareRoot(double x)
{
  double r = sqrt(x);
  return r;
}

//~File
typedef struct s8 s8;
struct s8 { uint8_t *Data; uint64_t Length; };

uint64_t FileGetSize(HANDLE File)
{
  LARGE_INTEGER Whatever = { 0 };
  uint64_t Result = 0;
  uint32_t Status = GetFileSizeEx(File, &Whatever);
  Result = Whatever.QuadPart;
  Assert(Status != 0);
  return Result;
}
s8 FileReadAll(const char *Path, arena *Arena)
{
  s8 Result = {0};
  HANDLE File = CreateFileA((LPCSTR)Path, GENERIC_READ, FILE_SHARE_READ,
                            0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if(File)
  {
    uint64_t ExpectedSize = FileGetSize(File);
    uint64_t BytesRead    = 0;
    Result = (s8){ArenaPushArray(Arena, ExpectedSize, uint8_t), ExpectedSize};
    ReadFile(File, Result.Data, (uint32_t)ExpectedSize, (LPDWORD)&BytesRead, NULL);
    Assert(BytesRead == ExpectedSize);
    Result.Length = BytesRead;
    CloseHandle(File);
  }
  return Result;
}
s8 FileWrite(const char *Path, uint8_t *Buffer, uint64_t Size)
{
  s8 Result = {0};
  HANDLE File = CreateFileA((LPCSTR)Path, GENERIC_WRITE, FILE_SHARE_READ,
                            0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  if(File)
  {
    uint32_t ByteCountWriten = 0;
    WriteFile(File, Buffer, Size, (LPDWORD)&ByteCountWriten, NULL);
  }else { printf("error"); }
  return Result;
}

//~Other
void ConvertStrToValue(const char *String, const char *Format, ...)
{
  va_list ArgList;
  va_start(ArgList, Format);
  vsscanf(String, Format, ArgList);
  va_end(ArgList);
  return;
}
void MemoryCopy(void *Dst, const void *Src, uint64_t ByteCount)
{
  memcpy(Dst, Src, ByteCount);
  return;
}
void MemoryClear(void *Src, uint64_t ByteCount)
{
  memset(Src, 0, ByteCount);
  return;
}
//~Random
void EntropyGen(void *Data, uint64_t Size)
{
  HCRYPTPROV Provider = 0;
  CryptAcquireContextA(&Provider, 0, 0, 0, CRYPT_VERIFYCONTEXT);
  CryptGenRandom(Provider, (uint32_t)Size, (BYTE *)&Data);
  CryptReleaseContext(Provider, 0);
  return;
}
#include "pcg64.h"
pcg64 GlobalRNG = {0};

void RandInit(void)
{
  //sets seed generator seed
  uint64_t ResultA = 0;
  uint64_t ResultB = 0;
  EntropyGen(&ResultA, sizeof(uint64_t));
  EntropyGen(&ResultB, sizeof(uint64_t));
  pcg64_seed(&GlobalRNG, ResultA, ResultB);
  return;
}
uint64_t RandRangeU64(uint64_t Low, uint64_t High)
{
  uint64_t r = pcg64_range(&GlobalRNG, Low, High);
  return r;
}
uint32_t RandRangeU32(uint32_t Low, uint32_t High)
{
  uint32_t r = (uint32_t)pcg64_range(&GlobalRNG, Low, High);
  return r;
}
uint8_t RandRangeU8(uint8_t Low, uint8_t High)
{
  uint8_t r = (uint8_t)pcg64_range(&GlobalRNG, Low, High);
  return r;
}
double RandF64Uni(void)
{
  double r = pcg64_nextd(&GlobalRNG);
  return r;
}
double RandF64Range(double low, double high)
{
  Assert(low<=high);
  double d = high-low;
  double t = RandF64Uni();
  double r = low + d*t;
  return r;
}
double RandF64Bi(void)
{
  double r = RandF64Range(-1.0,1.0);
  return r;
}
#endif //COMMON_H
