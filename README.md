# ReadMe



Current Output

```batch
hello from c
thread launched... id:29740
thread launched... id:27236
thread launched... id:25124
thread launched... id:8232
thread launched... id:1492
thread launched... id:22852
thread launched... id:5492
thread launched... id:26760
thread launched... id:24404
thread launched... id:24632
thread launched... id:4956
thread launched... id:25352
[3, 2, 1, 0]
serial cpu c
seconds elapsed: 0.000000s
[3, 2, 1, 0]
parallel cpu c
work begin signal set.
hello from thread[25352]
exiting... thread[25352]
hello from thread[24632]
exiting... thread[24632]
hello from thread[26760]
exiting... thread[26760]
hello from thread[ 5492]
exiting... thread[ 5492]
hello from thread[ 8232]
exiting... thread[ 8232]
hello from thread[27236]
exiting... thread[27236]
hello from thread[ 4956]
exiting... thread[ 4956]
hello from thread[22852]
exiting... thread[22852]
hello from thread[29740]
exiting... thread[29740]
hello from thread[24404]
exiting... thread[24404]
hello from thread[25124]
exiting... thread[25124]
hello from thread[ 1492]
exiting... thread[ 1492]
seconds elapsed: 0.001948s
[0, 1, 2, 3]

parallel gpu c
hello from cuda brick sorter <2,0>
hello from cuda brick sorter <3,0>
hello from cuda brick sorter <0,0>
hello from cuda brick sorter <1,0>
seconds elapsed: 0.406243s
done
```
