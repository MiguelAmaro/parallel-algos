@echo off

echo starting Jupiter...

pushd %cd%\test\notebooks
start C:\Users\mAmaro\anaconda3\python.exe C:\Users\mAmaro\anaconda3\cwp.py C:\Users\mAmaro\anaconda3 C:\Users\mAmaro\anaconda3\python.exe C:\Users\mAmaro\anaconda3\Scripts\jupyter-notebook-script.py %cd%
popd