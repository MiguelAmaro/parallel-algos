#include <immintrin.h>
#include <stdint.h>
#include "common.h"

#define StringFromIdentifier(id) (#id)
#define alignas(x) __declspec(align(x))

#define WriteToRef(ref, value) (*ref = value)

#define SIMDTEST_FALSE (0)
#define SIMDTEST_TRUE (1)
const char *SIMDTEST_TRUE_STR = "true";
const char *SIMDTEST_FALSE_STR = "false";
#define StringFromBoolean()

#define ELEM_MAXCOUNT ((uint64_t)(64*1024*1024))

uint64_t gElementCount = 10000000;
uint64_t gAlignment    = 16;
uint32_t gSeed         = 29;

const char *BooleanAsString(uint32_t Bool)
{
  //Assert that it is a valid boolean value
  const char *Result = Bool?SIMDTEST_TRUE_STR:SIMDTEST_FALSE_STR;
  return Result;
}
uint32_t MemoryIsAligned(const void *Pointer, uint64_t Alignment)
{
  uint64_t Address = (uint64_t)Pointer;
  uint32_t Result = ((Address%Alignment)==0);
  return Result;
}
void FillArrayU8(uint8_t *Array, uint64_t Count, uint8_t min, uint8_t max, uint32_t seed)
{
  uint8_t *Dest = (uint8_t *)Array;
  for(int i=0;i<Count;i++)
  {
    Dest[i] = RandRangeU8(min, max);
  }
  return;
}

uint32_t ArrayIsValid(const uint8_t *Array, uint64_t Count)
{
  if((Count==0) || (Count>ELEM_MAXCOUNT)) return SIMDTEST_FALSE;
  if((Count%64) != 0)                     return SIMDTEST_FALSE;
  if(!MemoryIsAligned(Array, gAlignment)) return SIMDTEST_FALSE;
  return SIMDTEST_TRUE;
}
uint32_t Scalar_MeanU8(double *Mean, uint64_t *Sum, const uint8_t *Array, uint64_t Count)
{
  if(!ArrayIsValid(Array, Count)) return SIMDTEST_FALSE;
  uint64_t SumTemp = 0;
  for(uint64_t i=0;i<Count;i++) { SumTemp += Array[i]; }
  WriteToRef(Sum, SumTemp);
  WriteToRef(Mean, (double)SumTemp/(double)Count);
  return SIMDTEST_TRUE;
}
uint32_t Avx_MeanU8(double *Mean, uint64_t *Sum, const uint8_t *Array, uint64_t Count)
{
  if(!ArrayIsValid(Array, Count)) return SIMDTEST_FALSE;
  
  const uint64_t SimdElmCount = 16;
  __m128i PackedZero   = _mm_setzero_si128();
  __m128i PixelSumsU32 = _mm_setzero_si128();
  for(uint64_t i=0;i<Count; i+=SimdElmCount*4)
  {
    __m128i PixelValsU8;
    __m128i PixelValsLoU16;
    __m128i PixelValsHiU16;
    __m128i PixelSumsU16 = _mm_setzero_si128();
    // Unpacking Result which is a 16bit element
    // Hi 8bits(PackedZero)  Lo 8Bits(Pixel)
    // 00000000              10101010 <-random example
    PixelValsU8 = _mm_load_si128((__m128i*)&Array[i]);
    PixelValsLoU16 = _mm_unpacklo_epi8(PixelValsU8, PackedZero);
    PixelValsHiU16 = _mm_unpackhi_epi8(PixelValsU8, PackedZero);
    // It seems like the goals is to load using simd by using the input data size
    // and using unpacking opperations to promote the size of the opperands.
    // the size that we are using for operations must give rooom for the maximum
    // result that can possible be computed from the data set and our operations.
    // we need enough bits to represent the result.
    // the result in this case is summ and it is divided int to 8 16bit elements
    // in other words we are doing 8 sums at the same time.
    // also taking on smaller chunks at a time lets us use more lanes
    // which can then be merged into fewer but wider lanes via unpacking
    // 
    PixelSumsU16    = _mm_add_epi16(PixelSumsU16, PixelValsLoU16);
    PixelSumsU16    = _mm_add_epi16(PixelSumsU16, PixelValsHiU16);
    
    PixelValsU8 = _mm_load_si128((__m128i*)&Array[i+16]);
    PixelValsLoU16 = _mm_unpacklo_epi8(PixelValsU8, PackedZero);
    PixelValsHiU16 = _mm_unpackhi_epi8(PixelValsU8, PackedZero);
    PixelSumsU16    = _mm_add_epi16(PixelSumsU16, PixelValsLoU16);
    PixelSumsU16    = _mm_add_epi16(PixelSumsU16, PixelValsHiU16);
    
    PixelValsU8 = _mm_load_si128((__m128i*)&Array[i+32]);
    PixelValsLoU16 = _mm_unpacklo_epi8(PixelValsU8, PackedZero);
    PixelValsHiU16 = _mm_unpackhi_epi8(PixelValsU8, PackedZero);
    PixelSumsU16    = _mm_add_epi16(PixelSumsU16, PixelValsLoU16);
    PixelSumsU16    = _mm_add_epi16(PixelSumsU16, PixelValsHiU16);
    
    PixelValsU8 = _mm_load_si128((__m128i*)&Array[i+48]);
    PixelValsLoU16 = _mm_unpacklo_epi8(PixelValsU8, PackedZero);
    PixelValsHiU16 = _mm_unpackhi_epi8(PixelValsU8, PackedZero);
    PixelSumsU16    = _mm_add_epi16(PixelSumsU16, PixelValsLoU16);
    PixelSumsU16    = _mm_add_epi16(PixelSumsU16, PixelValsHiU16);
    // it seems that sumation is done by taking groups from the array promoting the the size
    // and summing up the groups individualy into a list of sums(8x 16bit sums) then merging the list of sums
    // by promoting size of the sums and and adding them(or collapsing them into a smaller list of wider sums)(4x 32bit sums)
    // then finally collapsing them via additions to the result of a single 64bit sum
    __m128i PixelSumsLoU32 = _mm_unpacklo_epi8(PixelSumsU16, PackedZero); //Take low 4 of PixelU16
    __m128i PixelSumsHiU32 = _mm_unpackhi_epi8(PixelSumsU16, PackedZero);
    PixelSumsU32 = _mm_add_epi32(PixelSumsU32 ,PixelSumsLoU32);
    PixelSumsU32 = _mm_add_epi32(PixelSumsU32 ,PixelSumsHiU32);
  }
  
  // extract looks pretty similar to an array access using an index
  // the bit width per element is 32 in this case and the second arg is the index
  // and instead of an array is just i28bit simd register
  uint64_t PixelSum = _mm_extract_epi32(PixelSumsU32, 0);
  PixelSum += _mm_extract_epi32(PixelSumsU32, 1);
  PixelSum += _mm_extract_epi32(PixelSumsU32, 2);
  PixelSum += _mm_extract_epi32(PixelSumsU32, 3);
  WriteToRef(Sum, PixelSum);
  WriteToRef(Mean, (double)PixelSum/(double)Count);
  return SIMDTEST_TRUE;
}
void ArrayInit(uint8_t *Array, uint64_t Size, uint32_t Seed)
{
  int32_t RngMinVal = 5;
  int32_t RngMaxVal = 250;
  FillArrayU8(Array, Size, RngMinVal, RngMaxVal, Seed);
#if 0
  Array[(Count/4)*3 + 1] = 2;
  Array[(Count/4)+11] = 3;
  Array[(Count/2)] = 252;
  Array[(Count/2) + 13] = 253;
  Array[(Count/8) + 5] = 253;
  Array[(Count/8) + 7] = 254;
#endif
  return;
}
int main(void)
{
#if 0
  RandInit();
  arena Arena = ArenaAlloc(Kilobytes(4000)+ELEM_MAXCOUNT*sizeof(uint8_t));
  printf("Is Aligned? [%#llx] %s\n", (uint64_t)Arena.Base, BooleanAsString(MemoryIsAligned(Arena.Base, 16)));
  uint64_t Count = 64;
  uint8_t *Array = ArenaPushArray(&Arena, Count, uint8_t);
  ArrayInit(Array, Count, gSeed);
#endif
  
  uint8_t Array[] =
  {   5, 224, 125, 150, 221, 12, 140, 145, 114, 68, 20, 206,
    203, 186, 27, 225, 38, 213, 90, 6, 66, 118, 143, 25, 6,
    27, 7, 227, 56, 65, 17, 135, 90, 145, 132, 51, 185, 150,
    158, 235, 103, 120, 158, 80, 51, 184, 18, 74, 235, 158,
    182, 60, 108, 157, 206, 153, 76, 176, 16, 152, 20, 128, 85, 35};
  uint64_t Count = ArrayCount(Array);
  uint32_t ResultA = 0;
  uint32_t ResultB = 0;
  uint64_t SumA = 0;
  uint64_t SumB = 0;
  double MeanA = 0.0;
  double MeanB = 0.0;
  
  printf("Array[]: \n");
  for(int i=0;i<Count;i++)
  {
    printf("%d\n", Array[i]);
  }
  
  ResultB = Avx_MeanU8(&MeanB, &SumB, Array, Count);
  printf("\n");
  printf("Results for Avx_MeanU8\n");
  printf("Result[Avx   ]: %s\n", BooleanAsString(ResultB));
  printf("Sum   [Avx   ]: %llu\n", SumB);
  printf("Mean  [Avx   ]: %f\n", MeanB);
  
  ResultA = Scalar_MeanU8(&MeanA, &SumA, Array, Count);
  printf("\nResults for Scalar_MeanU8\n");
  printf("Result[Scalar]: %s\n", BooleanAsString(ResultA));
  printf("Sum   [Scalar]: %llu\n", SumA);
  printf("Mean  [Scalar]: %f\n", MeanA);
  
  //ArenaFree(&Arena);
  //TODO(): Make sure that array is initialized correctly
  //TODO(): Make sure that array is aligned
  //TODO(): Make sure that array is checked. something jpeg algos and 
  return;
}