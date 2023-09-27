@echo off

set PD= %cd%
set INCLUDES=-I%PD%\thirdparty\pcg
set DEBUG=-Zi -Od
set CUDA_DEBUG=-O 0 -g -G
set LIBS="C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64\cuda.lib" "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64\cudart.lib" advapi32.lib

pushd build
rem MAIN
nvcc -c -o cuda %PD%\src\cuda.cu
cl -nologo %DEBUG% %INCLUDES% -I%PD%\src %PD%\src\main.c -link %LIBS% cuda.obj

rem TESTS
cl -nologo %DEBUG% %INCLUDES% -I%PD%\src %PD%\test\test_csv.c -link advapi32.lib
cl -nologo %DEBUG% %INCLUDES% -I%PD%\src %PD%\test\test_all.c -link %LIBS% cuda.obj
cl -nologo %DEBUG% -FAs %INCLUDES% -I%PD%\src %PD%\test\simd_ex.c -link advapi32.lib
cl -nologo %DEBUG% -FAs %INCLUDES% -I%PD%\src %PD%\test\simd_algos.c -link advapi32.lib
popd

