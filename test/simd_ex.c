#include <immintrin.h>
#include <stdint.h>

#define StringFromIdentifier(id) (#id)
#define alignas(x) __declspec(align(x))

typedef struct vxmm vxmm;
struct alignas(16) vxmm
{
  union
  {
    int8_t   vs8 [16];
    int16_t  vs16[ 8];
    int32_t  vs32[ 4];
    int64_t  vs64[ 2];
    uint8_t  vu8 [16];
    uint16_t vu16[ 8];
    uint32_t vu32[ 4];
    uint64_t vu64[ 2];
    float    vf32[ 4];
    double   vf64[ 2];
  };
};

typedef struct vymm vymm;
struct alignas(32) vymm
{
  union
  {
    int8_t   vs8 [32];
    int16_t  vs16[16];
    int32_t  vs32[ 8];
    int64_t  vs64[ 4];
    uint8_t  vu8 [32];
    uint16_t vu16[16];
    uint32_t vu32[ 8];
    uint64_t vu64[ 4];
    float    vf32[ 8];
    double   vf64[ 4];
  };
};


void PrintsS16(const char *label, vxmm *a)
{
  printf("%s %8.d %8.d %8.d %8.d |"
         " %8.d %8.d %8.d %8.d\n", label,
         a->vs16[0], a->vs16[1], a->vs16[2], a->vs16[3],
         a->vs16[4], a->vs16[5], a->vs16[6], a->vs16[7]);
  return;
}
void PrintsU16(const char *label, vxmm *a)
{
  printf("%s %8.hu %8.hu %8.hu %8.hu |"
         " %8.hu %8.hu %8.hu %8.hu\n", label,
         a->vs16[0], a->vs16[1], a->vs16[2], a->vs16[3],
         a->vs16[4], a->vs16[5], a->vs16[6], a->vs16[7]);
  return;
}

void Scalar_CalcZ(const float *x, const float *y, float *Dest, uint64_t Count)
{
  for(uint64_t i=0;i<Count;i++)
  {
    Dest[i] = x[i]+y[i];
  }
  return;
}
void Avx_CalcZ(const float *x, const float *y, float *Dest, uint64_t Count)
{
  uint64_t ElemProcesesedCount = 0;
  uint64_t SimdElemCount = 8;
  while((Count-ElemProcesesedCount) >= SimdElemCount)
  {
    uint64_t Index = ElemProcesesedCount;
    //Begin Process via AVX
    __m256 XVals =  _mm256_loadu_ps(&x[Index]);
    __m256 YVals =  _mm256_loadu_ps(&y[Index]);
    __m256 ZVals =  _mm256_add_ps(XVals, YVals);
    _mm256_storeu_ps(&Dest[Index], ZVals);
    //End Process via AVX
    ElemProcesesedCount += SimdElemCount; //Batches of SimdElemCount
  }
  //Process Remaining ElmCount which is less than SimdElemCount
  while(ElemProcesesedCount < Count)
  {
    uint64_t Index = ElemProcesesedCount;
    //Begin Process via scalar
    Dest[Index] = x[Index] + y[Index];
    //Begin Process via scalar
    ElemProcesesedCount += 1; //1 at a time
  }
  return;
}

void Avx_AddS16(vxmm *a, vxmm *b, vxmm *DestA, vxmm *DestB)
{
  __m128i av = _mm_load_si128((__m128i*)a); //NOTE(): operands must be loaded on 16byte boundaries
  __m128i bv = _mm_load_si128((__m128i*)b);
  __m128i cav = _mm_add_epi16(av, bv); //NOTE(): wraparound
  __m128i cbv = _mm_adds_epi16(av, bv); //NOTE(): usees satureted instead of wraparound arithmetic
  _mm_store_si128((__m128i*)DestA, cav);
  _mm_store_si128((__m128i*)DestB, cbv);
  return;
}
void Avx_AddU16(vxmm *a, vxmm *b, vxmm *DestA, vxmm *DestB)
{
  __m128i av = _mm_load_si128((__m128i*)a); //NOTE(): operands must be loaded on 16byte boundaries
  __m128i bv = _mm_load_si128((__m128i*)b);
  __m128i cav = _mm_add_epi16(av, bv); //NOTE(): wraparound
  __m128i cbv = _mm_adds_epu16(av, bv); //NOTE(): usees satureted instead of wraparound arithmetic
  _mm_store_si128((__m128i*)DestA, cav);
  _mm_store_si128((__m128i*)DestB, cbv);
  return;
}
void Avx_MullS16(vxmm *a, vxmm *b, vxmm Dest[2])
{
  //NOTE(): The add functions had 2 destinations for 'demo'ing wraparound
  //        and saturated addition but multiplications necessitates 2 destionations
  //        because 2 twice the number of bits as the opperand are needed to store the 
  //        results so the result are stored as packed 32 bit chuncks.
  //        that is why the operations requires more registers(twice as many) for lo and hi parts
  __m128i av = _mm_load_si128((__m128i*)a);
  __m128i bv = _mm_load_si128((__m128i*)b);
  //NOTE(): 16 means its operating on 16bit wide elements. the operands are stored ins diffent
  //        registers a and b. the operations is broken up into 2 parts where the high 16 bits of
  //        of the result is calculated by the hi variant of _mm_mull and store in a seperate register
  //        and the low 16 bits of the result is calculated by the lo variant of _mm_mull...
  __m128i temp_lo = _mm_mullo_epi16(av, bv);
  __m128i temp_hi = _mm_mulhi_epi16(av, bv);
  //NOTE(): 16 means there are 16 bit wide elements in the 128bit register
  //        therefore the element count is 8
  //        so unpack lo will get the lower 4 elements of the 8 and put it
  //        in a 128bit register as 32bit wide elements(size got promoted during the un pack)
  __m128i res_lo = _mm_unpacklo_epi16(temp_lo, temp_hi);
  __m128i res_hi = _mm_unpackhi_epi16(temp_lo, temp_hi);
  _mm_store_si128((__m128i*)&Dest[0], res_lo);
  _mm_store_si128((__m128i*)&Dest[1], res_hi);
  return;
}
void Avx_MulS16(){}
void Avx_MulS32_MethodA(){}
void Avx_MulS32_MethodB(){}
void Avx_AndU16(){}
void Avx_OrU16(){}
void Avx_XorU16(){}
void Avx_SllU16(){}
void Avx_SrlU16(){}
void Avx_SraU16(){}

//NOTE(): floating point compares have greater/less than eq and unordered(NAN or illegal values)
//NOTE(): predicates e.g. OQ, Q tells the processor what to do when it comes accross an unrdered value
//        detected in one of the operands. O means both operands must not be a NAN/illegal value. Q means
//        dont raise an exceptions if one is 
//NOTE(): There are also intrinsics for convererting between data types
void Avx_CmpF32(){}



int main(void)
{
  vxmm a = {0};
  vxmm b = {0};
  vxmm c1 = {0};
  vxmm c2 = {0};
  
  a.vs16[0] = 10;
  a.vs16[1] = 200;
  a.vs16[2] = 30;
  a.vs16[3] = -32766;
  a.vs16[4] = 50;
  a.vs16[5] = 60;
  a.vs16[6] = 32000;
  a.vs16[7] = -32000;
  
  b.vs16[0] = 100;
  b.vs16[1] = -200;
  b.vs16[2] = 32760;
  b.vs16[3] = -400;
  b.vs16[4] = 500;
  b.vs16[5] = -600;
  b.vs16[6] = 1200;
  b.vs16[7] = -950;
  
  Avx_AddS16(&a,&b,&c1,&c2);
  PrintsS16("a: ", &a);
  PrintsS16("b: ", &b);
  printf("Results for %s - Wraparound Addition\n", StringFromIdentifier(Avx_AddS16));
  PrintsS16("c1:", &c1);
  printf("Results for %s - Saturated Addition\n", StringFromIdentifier(Avx_AddS16));
  PrintsS16("c2:", &c2);
  printf("\n\n");
  
  
  
  a.vu16[0] = 10;
  a.vu16[1] = 200;
  a.vu16[2] = 300;
  a.vu16[3] = 32766;
  a.vu16[4] = 50;
  a.vu16[5] = 20000;
  a.vu16[6] = 32000;
  a.vu16[7] = 32000;
  
  b.vu16[0] = 100;
  b.vu16[1] = 200;
  b.vu16[2] = 65530;
  b.vu16[3] = 40000;
  b.vu16[4] = 500;
  b.vu16[5] = 25000;
  b.vu16[6] = 1200;
  b.vu16[7] = 50000;
  
  Avx_AddU16(&a,&b,&c1,&c2);
  PrintsU16("a: ", &a);
  PrintsU16("b: ", &b);
  printf("Results for %s - Wraparound Addition\n", StringFromIdentifier(Avx_AddU16));
  PrintsU16("c1:", &c1);
  printf("Results for %s - Saturated Addition\n", StringFromIdentifier(Avx_AddU16));
  PrintsU16("c2:", &c2);
  //NOTE(): The book goes over multiplication and subtractions but im going just listen to it
  //        and come back if i need get more familiarity and understanding
  //NOTE(): subtraction can also be saturated with the instruction's saturated variant _mm_subs_epi16()
  //        the (s) after sub stands for saturated
  //NOTE(): There is a difference between arithemetic and logical shifts
  return 0;
}