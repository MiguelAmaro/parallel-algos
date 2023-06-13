@echo off

set DEBUG=-Zi -Od
set LIBS="C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64\cuda.lib" "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64\cudart.lib"
nvcc -c -o cuda cuda.cu
cl -nologo %DEBUG% main.c -link %LIBS% cuda.obj
