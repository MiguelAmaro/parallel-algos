# ReadMe

Current Output

```batch
hello from c
thread launched... id:11604
thread launched... id:29636
thread launched... id:29496
thread launched... id:25944
thread launched... id:23488
thread launched... id:4920
thread launched... id:17856
thread launched... id:29016
thread launched... id:30292
thread launched... id:28684
thread launched... id:25092
thread launched... id:28980

serial cpu c
[64, 15, 59, 80, 58, 63, 97, 89, 82, 54,
79, 22, 71, 51, 32, 48, 50, 36, 30, 74,
73, 44, 40, 5, 23, 37, 1, 62, 60, 27,
39, 66, 45, 6, 93, 29, 11, 33, 81, 55,
87, 72, 88, 92, 26, 76, 75, 0, 12, 96,
21, 90, 99, 52, 61, 2, 53, 4, 68, 25,
70, 16, 67, 34, 24, 42, 57, 31, 38, 65,
83, 41, 86, 8, 10, 43, 18, 94, 9, 17,
7, 13, 49, 3, 28, 78, 56, 85, 95, 19,
84, 20, 46, 47, 14, 91, 98, 35, 69, 77]
seconds elapsed: 0.000031s
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
90, 91, 92, 93, 94, 95, 96, 97, 98, 99]

parallel cpu c
[12, 55, 49, 31, 69, 59, 32, 95, 96, 68,
24, 3, 67, 58, 16, 18, 81, 47, 17, 64,
97, 86, 27, 56, 9, 80, 72, 44, 26, 57,
83, 70, 51, 48, 39, 15, 1, 41, 54, 53,
22, 92, 84, 8, 45, 91, 98, 36, 20, 23,
38, 76, 5, 60, 71, 88, 0, 13, 99, 30,
78, 2, 63, 34, 65, 61, 62, 28, 93, 46,
77, 29, 82, 25, 79, 37, 52, 43, 6, 19,
33, 4, 14, 42, 75, 85, 40, 87, 89, 94,
11, 10, 66, 35, 50, 7, 90, 73, 74, 21]
work begin signal set.
hello from thread[28980]
hello from thread[11604]
hello from thread[29636]
hello from thread[23488]
exiting... thread[23488]
hello from thread[25944]
exiting... thread[25944]
hello from thread[25092]
exiting... thread[25092]
hello from thread[29016]
exiting... thread[29016]
hello from thread[28684]
exiting... thread[28684]
exiting... thread[11604]
exiting... thread[29636]
hello from thread[29496]
exiting... thread[29496]
hello from thread[ 4920]
exiting... thread[ 4920]
exiting... thread[28980]
hello from thread[30292]
exiting... thread[30292]
hello from thread[17856]
exiting... thread[17856]
seconds elapsed: 0.002221s
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
90, 91, 92, 93, 94, 95, 96, 97, 98, 99]

parallel gpu c
[43, 23, 57, 53, 11, 16, 65, 77, 51, 10,
70, 33, 7, 99, 2, 71, 92, 42, 30, 0,
27, 62, 24, 29, 44, 76, 41, 93, 12, 83,
94, 22, 87, 63, 85, 49, 28, 39, 56, 72,
79, 73, 55, 90, 81, 40, 84, 8, 58, 6,
54, 69, 15, 61, 38, 47, 67, 48, 45, 86,
91, 3, 37, 21, 78, 97, 46, 80, 14, 4,
18, 32, 20, 88, 13, 59, 96, 25, 98, 35,
36, 89, 19, 60, 1, 82, 26, 9, 52, 64,
5, 95, 75, 34, 31, 68, 17, 50, 66, 74]
hello from cuda brick sorter <48,0>
hello from cuda brick sorter <34,0>
hello from cuda brick sorter <39,0>
hello from cuda brick sorter <65,0>
hello from cuda brick sorter <70,0>
hello from cuda brick sorter <33,0>
hello from cuda brick sorter <50,0>
hello from cuda brick sorter <79,0>
hello from cuda brick sorter <45,0>
hello from cuda brick sorter <40,0>
hello from cuda brick sorter <64,0>
hello from cuda brick sorter <29,0>
hello from cuda brick sorter <19,0>
hello from cuda brick sorter <59,0>
hello from cuda brick sorter <37,0>
hello from cuda brick sorter <38,0>
hello from cuda brick sorter <90,0>
hello from cuda brick sorter <41,0>
hello from cuda brick sorter <42,0>
hello from cuda brick sorter <71,0>
hello from cuda brick sorter <43,0>
hello from cuda brick sorter <44,0>
hello from cuda brick sorter <76,0>
hello from cuda brick sorter <72,0>
hello from cuda brick sorter <30,0>
hello from cuda brick sorter <12,0>
hello from cuda brick sorter <68,0>
hello from cuda brick sorter <32,0>
hello from cuda brick sorter <9,0>
hello from cuda brick sorter <60,0>
hello from cuda brick sorter <47,0>
hello from cuda brick sorter <28,0>
hello from cuda brick sorter <31,0>
hello from cuda brick sorter <69,0>
hello from cuda brick sorter <56,0>
hello from cuda brick sorter <1,0>
hello from cuda brick sorter <36,0>
hello from cuda brick sorter <51,0>
hello from cuda brick sorter <74,0>
hello from cuda brick sorter <49,0>
hello from cuda brick sorter <7,0>
hello from cuda brick sorter <35,0>
hello from cuda brick sorter <73,0>
hello from cuda brick sorter <46,0>
hello from cuda brick sorter <10,0>
hello from cuda brick sorter <63,0>
hello from cuda brick sorter <25,0>
hello from cuda brick sorter <0,0>
hello from cuda brick sorter <61,0>
hello from cuda brick sorter <99,0>
hello from cuda brick sorter <62,0>
hello from cuda brick sorter <75,0>
hello from cuda brick sorter <84,0>
hello from cuda brick sorter <66,0>
hello from cuda brick sorter <78,0>
hello from cuda brick sorter <20,0>
hello from cuda brick sorter <54,0>
hello from cuda brick sorter <18,0>
hello from cuda brick sorter <96,0>
hello from cuda brick sorter <53,0>
hello from cuda brick sorter <77,0>
hello from cuda brick sorter <85,0>
hello from cuda brick sorter <55,0>
hello from cuda brick sorter <52,0>
hello from cuda brick sorter <67,0>
hello from cuda brick sorter <91,0>
hello from cuda brick sorter <23,0>
hello from cuda brick sorter <89,0>
hello from cuda brick sorter <80,0>
hello from cuda brick sorter <3,0>
hello from cuda brick sorter <17,0>
hello from cuda brick sorter <24,0>
hello from cuda brick sorter <57,0>
hello from cuda brick sorter <22,0>
hello from cuda brick sorter <94,0>
hello from cuda brick sorter <8,0>
hello from cuda brick sorter <21,0>
hello from cuda brick sorter <58,0>
hello from cuda brick sorter <15,0>
hello from cuda brick sorter <95,0>
hello from cuda brick sorter <26,0>
hello from cuda brick sorter <2,0>
hello from cuda brick sorter <5,0>
hello from cuda brick sorter <83,0>
hello from cuda brick sorter <92,0>
hello from cuda brick sorter <16,0>
hello from cuda brick sorter <88,0>
hello from cuda brick sorter <6,0>
hello from cuda brick sorter <13,0>
hello from cuda brick sorter <93,0>
hello from cuda brick sorter <4,0>
hello from cuda brick sorter <97,0>
hello from cuda brick sorter <27,0>
hello from cuda brick sorter <82,0>
hello from cuda brick sorter <11,0>
hello from cuda brick sorter <81,0>
hello from cuda brick sorter <86,0>
hello from cuda brick sorter <14,0>
hello from cuda brick sorter <98,0>
hello from cuda brick sorter <87,0>
seconds elapsed: 0.318639s
[43, 23, 57, 53, 11, 16, 65, 77, 51, 10,
70, 33, 7, 99, 2, 71, 92, 42, 30, 0,
27, 62, 24, 29, 44, 76, 41, 93, 12, 83,
94, 22, 87, 63, 85, 49, 28, 39, 56, 72,
79, 73, 55, 90, 81, 40, 84, 8, 58, 6,
54, 69, 15, 61, 38, 47, 67, 48, 45, 86,
91, 3, 37, 21, 78, 97, 46, 80, 14, 4,
18, 32, 20, 88, 13, 59, 96, 25, 98, 35,
36, 89, 19, 60, 1, 82, 26, 9, 52, 64,
5, 95, 75, 34, 31, 68, 17, 50, 66, 74]



done
```
