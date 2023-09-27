
#ifndef DEBUG_H
#define DEBUG_H

void DBGGenPythonFile(double w, double b)
{
  uint8_t DummyBuffer = 0x0;
  const char *Imports =
    "import math, copy\n"
    "import numpy as np\n"
    "import pandas as pd\n"
    "import matplotlib.pyplot as plt\n";
  
  uint32_t bc1 = snprintf(&DummyBuffer, Bytes(1), "%s", Imports);
  uint32_t bc2 = snprintf(&DummyBuffer, Bytes(1), "w = %f\nb= %f", w, b);
  int ByteCount = bc1 + bc2;
  
  uint8_t *Buffer = MemAlloc(ByteCount);
  snprintf(Buffer, Bytes(bc1), "%s", Imports);
  snprintf(Buffer+bc1, Bytes(bc2), "w = %f\nb= %f", w, b);
  FileWrite("..\\scripts\\gentest.py", Buffer, ByteCount);
  return;
}


#endif //DEBUG_H
