#ifndef LINEAR_REG_H
#define LINEAR_REG_H

#if 1
int32_t SLRSamplePrices[] =
{
  13300000,
  12250000,
  12250000,
  12215000,
  11410000,
  10850000,
  10150000,
};
int32_t SLRSampleArea[] =
{
  7420,
  8960,
  9960,
  7500,
  7420,
  7500,
  8580,
};
#else
int32_t SLRSamplePrices[] =
{
  1,2,3,4
};
int32_t SLRSampleArea[] =
{
  1,2,9,4
};
#endif

#ifdef __cplusplus
extern "C" void SLRDeviationCuda(double Mean, double *Data, uint64_t Count, double *Result);
#else
void SLRDeviationCuda(double Mean, double *Data, uint64_t Count, double *Result);
#endif

//~ SINGLE LINEAR REGRESSON
typedef struct slr slr;
struct slr { arena Arena; };
typedef struct slr_gradient slr_gradient;
struct slr_gradient { double w; double b; };
typedef struct i64 i64;
struct i64 { double min; double max; };
slr GlobalSLR = {0};

void SLRInit(slr *SLR)
{
  SLR->Arena = ArenaAlloc(Kilobytes(80));
  return;
}
void SLRCleanUp(slr *SLR)
{
  ArenaFree(&SLR->Arena);
  return;
}
double SLRAverage(int32_t *Data, uint32_t Count)
{
  int32_t Sum = 0;
  for(int i=0;i<Count;i++)
  {
    Sum += Data[i];
  }
  double Result = (double)Sum/(double)Count;
  return Result;
}
double SLRAverageF64(double *Data, uint64_t Count)
{
  double Sum = 0.0;
  for(uint64_t i=0;i<Count;i++)
  {
    Sum += Data[i];
  }
  double Result = (double)Sum/(double)Count;
  return Result;
}
void SLRDeviationF64(double Mean, double *Data, uint64_t Count, double *Result, uint32_t UseCuda)
{
  if(UseCuda)
  {
    SLRDeviationCuda(Mean, Data, Count, Result);
  }
  else
  {
    double Sum = 0.0;
    for(uint64_t i=0;i<Count;i++)
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
  }
  return;
}
double SLRVarianceF64(double *Data, uint32_t Count)
{
  double Sum = 0.0;
  double Mean = SLRAverageF64(Data, Count);
  for(int i=0;i<Count;i++)
  {
    double Delta = Data[i]-Mean;
    Sum += Delta*Delta;
  }
  double Result = (double)Sum/(double)(Count-1.0);
  return Result;
}
double SLRStandardDiviationF64(double *Data, uint32_t Count)
{
  double Result = SquareRoot(SLRVarianceF64(Data, Count));
  return Result;
}
i64 SLRDataSetRange(int32_t *Data, uint32_t Count)
{
  i64 Result = {.min=F64Max, .max=F64Min};
  for(int i=0;i<Count;i++)
  {
    Result.min = Min(Result.min, Data[i]);
    Result.max = Max(Result.max, Data[i]);
  }
  return Result;
}
double *SLRGetZScoreNormalizedCopy(int32_t *Data, uint32_t Count)
{
  Assert(!"Not Implemented");
  return NULL;
}
double *SLRGetF64Copy(int32_t *Data, uint32_t Count)
{
  double *Result = ArenaPushArray(&GlobalSLR.Arena, Count, double);
  for(int i=0;i<Count;i++)
  {
    Result[i] = (double)(Data[i]);
  }
  return Result;
}
double *SLRGetMeanNormalizedCopy(int32_t *Data, uint32_t Count)
{
  double *Result = ArenaPushArray(&GlobalSLR.Arena, Count, double);
  double Avg   = SLRAverage(Data, Count);
  i64 SetRange = SLRDataSetRange(Data, Count);
  for(int i=0;i<Count;i++)
  {
    Result[i] = (double)(Data[i]-Avg)/(double)(SetRange.max-SetRange.min);
  }
  return Result;
}
double SLRCost(double w, double b, int32_t *Features, int32_t *Expected, uint32_t BatchCount)
{
  double Sum = 0.0;
  for(int i=0;i<BatchCount;i++)
  {
    double Prediction = w*(double)Features[i] + b;
    double Delta = ((double)Prediction - (double)Expected[i]);
    Sum = Sum + Delta*Delta;
  }
  double Result = Sum/(2.0*(double)BatchCount);
  return Result;
}
slr_gradient SLRGradient(double w, double b, int32_t *Features, int32_t *Expected, uint32_t BatchCount)
{
  double dJ_dW = 0.0;
  double dJ_dB = 0.0;
  for(int i=0;i<BatchCount;i++)
  {
    double Prediction = w*(double)Features[i] + b;
    double DeltaW = ((double)Prediction - (double)Expected[i])*(double)Features[i];
    double DeltaB = ((double)Prediction - (double)Expected[i]);
    dJ_dW += DeltaW;
    dJ_dB += DeltaB;
  }
  dJ_dB = dJ_dB/(double)BatchCount;
  dJ_dW = dJ_dW/(double)BatchCount;
  slr_gradient Result = (slr_gradient){ dJ_dW, dJ_dB };
  return Result;
}
void SLRGradientDescent(uint32_t IterationCount, double LearnRate, double *wInitial, double *bInitial, int32_t *Features, int32_t *Expected, uint32_t BatchCount)
{
  //get the cost
  //compute the dererivative of the cost
  //go towared the slope of given by the finding the derivative
  //do this for w and b
  //multiply the shift by a given learning rate
  //do this for some specified iteration count
  //update w and b on each iteration
  double w = *wInitial;
  double b = *bInitial;
  for(int i=0;i<IterationCount;i++)
  {
    slr_gradient Gradient = SLRGradient(w, b, SLRSampleArea, SLRSamplePrices, BatchCount);
    if(isnan(b) || isnan(w)) { printf("[iter-%d]nan detected\n",i); KillProcess(); }
    w = w - LearnRate*Gradient.w;
    b = b - LearnRate*Gradient.b;
    if(IterationCount%100==0)
    {
      printf("[%.4d]cost: %.4f\n", i, SLRCost(w,b,Features, Expected, BatchCount));
    }
  }
  *wInitial = w;
  *bInitial = b;
  return;
}
void SLRRun(void)
{
  SLRInit(&GlobalSLR);
  //model
  double w = 0.0f;
  double b = 0.0f;
  uint32_t IterationCount = 100000;
  double lr = 0.00000002941;
  uint32_t BatchCount = Min(ArrayCount(SLRSampleArea), ArrayCount(SLRSamplePrices));
  double *MeanNormArea = SLRGetMeanNormalizedCopy(SLRSampleArea, BatchCount);
  double *FCopy = SLRGetF64Copy(SLRSampleArea, BatchCount);
  printf("mean: %f\n", SLRAverageF64(FCopy, BatchCount));
  printf("variance: %f\n", SLRVarianceF64(FCopy, BatchCount));
  printf("std deviation: %f\n", SLRStandardDiviationF64(FCopy, BatchCount));
  printf("avg: %f\n", SLRAverage(SLRSampleArea, BatchCount));
  //KillProcess();
  for(int i=0;i<BatchCount; i++)
  {
    printf("%f : %d\n", MeanNormArea[i], SLRSampleArea[i]);
  }
  printf("learn rate:       %f\n"
         "iterations count: %lu\n", lr, IterationCount);
  printf("w: %12.4f, b: %12.4f, cost: %12.4f\n", w, b, SLRCost(w, b, SLRSampleArea, SLRSamplePrices, BatchCount));
  SLRGradientDescent(IterationCount, lr, &w, &b, SLRSampleArea, SLRSamplePrices, BatchCount);
  printf("w: %12.4f, b: %12.4f, cost: %12.4f\n", w, b, SLRCost(w, b, SLRSampleArea, SLRSamplePrices, BatchCount));
  for(int i=0;i<BatchCount; i++)
  {
    printf("prediction: %f vs expected: %f \n", w*SLRSampleArea[i]+b, (double)SLRSamplePrices[i]);
  }
  SLRCleanUp(&GlobalSLR);
  return;
}



#endif //LINEAR_REG_H
