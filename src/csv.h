#ifndef CSV_H
#define CSV_H

typedef enum csv_field_kind csv_field_kind;
enum csv_field_kind
{
  CSV_FieldKind_F32,
  CSV_FieldKind_Utf8,
};
typedef struct csv_stats csv_stats;
struct csv_stats
{
  uint32_t Rows;
  uint32_t Cols;
};
typedef struct csv csv;
struct csv
{
  uint32_t RowCount;
  uint32_t ColCount;
  uint8_t *Data;
};

csv_stats CSVGetNaiveStats(uint8_t *Source, uint32_t Length)
{
  csv_stats Result = {0};
  uint32_t MaxColCountPerLine = 0;
  uint32_t    ColCountPerLine = 0;
  uint32_t MaxRowCountPerLine = 0;
  
  for(int i=0;i<Length;i++)
  {
    uint8_t Curr = Source[i];
    
    MaxRowCountPerLine = Curr=='\n'?MaxRowCountPerLine+1:MaxRowCountPerLine;
    ColCountPerLine = Curr=='\n'?0:ColCountPerLine;
    ColCountPerLine = Curr==','?ColCountPerLine+1:ColCountPerLine;
    
    MaxColCountPerLine = Max(ColCountPerLine, MaxColCountPerLine);
  }
  Result.Rows = MaxRowCountPerLine;
  Result.Cols = MaxColCountPerLine+1;//NOTE(): assumes 2 fields per column but may not always be the case
  return Result;
}
csv CSVNaiveParseSource(uint8_t *Source, uint32_t Length, arena *Arena)
{
  csv Result = {0};
  csv_stats Stats = CSVGetNaiveStats(Source, Length);
  
  //allocate
  Result.RowCount = Stats.Rows;
  Result.ColCount = Stats.Cols;
  Result.Data = (uint8_t *)ArenaPushBlock(Arena, Stats.Rows*Stats.Cols*sizeof(float)); //NOTE(): just assuming floats for now
  float *Data =   (float *)Result.Data;
  
  //parse
  uint32_t ColCount = 0;
  uint32_t RowCount = 0;
  for(int l=0,r=0;r<Length;r++)
  {
    uint8_t Curr = Source[r];
    
    if((Curr == ',' || Curr == '\n'))
    {
      if(RowCount>0)
      {
        uint8_t TempBuffer[512] = {0};
        uint8_t *SourceAt = &Source[l];
        uint32_t SourceLength = r-l;
        MemoryCopy(TempBuffer, SourceAt, SourceLength);
        TempBuffer[Min(SourceLength, 512-1)] = '/0';
        ConvertStrToValue(TempBuffer, "%f", Data);
        MemoryClear(TempBuffer, 512);
      }
      
      l = r = r+1;
      ColCount++;
      Data++;
    }
    if(Curr == '\n')
    {
      RowCount++;
      while(ColCount<Stats.Cols)
      {
        Data++;
        ColCount++;
      }
      ColCount = 0;
    }
  }
  
  return Result;
}
csv CSVInit(uint8_t *Source, uint32_t Length, arena *Arena)
{
  csv Result = CSVNaiveParseSource(Source, Length, Arena);
  return Result;
}
csv CSVInitFromFile(uint8_t *Path, arena *Arena)
{
  s8 Source = FileReadAll(Path, Arena);
  csv Result = CSVNaiveParseSource(Source.Data, Source.Length, Arena);
  return Result;
}

#endif //CSV_H
