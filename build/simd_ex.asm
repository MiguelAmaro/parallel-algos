; Listing generated by Microsoft (R) Optimizing Compiler Version 19.32.31328.0 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	PrintsS16
PUBLIC	PrintsU16
PUBLIC	Scalar_CalcZ
PUBLIC	Avx_CalcZ
PUBLIC	Avx_AddS16
PUBLIC	Avx_AddU16
PUBLIC	Avx_MullS16
PUBLIC	Avx_MulS16
PUBLIC	Avx_MulS32_MethodA
PUBLIC	Avx_MulS32_MethodB
PUBLIC	Avx_AndU16
PUBLIC	Avx_OrU16
PUBLIC	Avx_XorU16
PUBLIC	Avx_SllU16
PUBLIC	Avx_SrlU16
PUBLIC	Avx_SraU16
PUBLIC	main
EXTRN	printf:PROC
EXTRN	__GSHandlerCheck:PROC
EXTRN	__security_check_cookie:PROC
EXTRN	__security_cookie:QWORD
EXTRN	_fltused:DWORD
pdata	SEGMENT
$pdata$PrintsS16 DD imagerel $LN3
	DD	imagerel $LN3+228
	DD	imagerel $unwind$PrintsS16
$pdata$PrintsU16 DD imagerel $LN3
	DD	imagerel $LN3+228
	DD	imagerel $unwind$PrintsU16
$pdata$Scalar_CalcZ DD imagerel $LN6
	DD	imagerel $LN6+106
	DD	imagerel $unwind$Scalar_CalcZ
$pdata$Avx_CalcZ DD imagerel $LN7
	DD	imagerel $LN7+294
	DD	imagerel $unwind$Avx_CalcZ
$pdata$Avx_AddS16 DD imagerel $LN3
	DD	imagerel $LN3+122
	DD	imagerel $unwind$Avx_AddS16
$pdata$Avx_AddU16 DD imagerel $LN3
	DD	imagerel $LN3+122
	DD	imagerel $unwind$Avx_AddU16
$pdata$Avx_MullS16 DD imagerel $LN3
	DD	imagerel $LN3+189
	DD	imagerel $unwind$Avx_MullS16
$pdata$main DD	imagerel $LN3
	DD	imagerel $LN3+992
	DD	imagerel $unwind$main
pdata	ENDS
_DATA	SEGMENT
$SG26475 DB	'%s %8.d %8.d %8.d %8.d | %8.d %8.d %8.d %8.d', 0aH, 00H
	ORG $+2
$SG26482 DB	'%s %8.hu %8.hu %8.hu %8.hu | %8.hu %8.hu %8.hu %8.hu', 0aH
	DB	00H
	ORG $+2
$SG26597 DB	'a: ', 00H
$SG26598 DB	'b: ', 00H
$SG26599 DB	'Avx_AddS16', 00H
	ORG $+1
$SG26601 DB	'c1:', 00H
$SG26600 DB	'Results for %s - Wraparound Addition', 0aH, 00H
	ORG $+2
$SG26602 DB	'Avx_AddS16', 00H
	ORG $+1
$SG26604 DB	'c2:', 00H
$SG26603 DB	'Results for %s - Saturated Addition', 0aH, 00H
	ORG $+3
$SG26605 DB	0aH, 0aH, 00H
	ORG $+1
$SG26606 DB	'a: ', 00H
$SG26607 DB	'b: ', 00H
$SG26610 DB	'c1:', 00H
$SG26608 DB	'Avx_AddU16', 00H
	ORG $+1
$SG26613 DB	'c2:', 00H
$SG26609 DB	'Results for %s - Wraparound Addition', 0aH, 00H
	ORG $+2
$SG26611 DB	'Avx_AddU16', 00H
	ORG $+5
$SG26612 DB	'Results for %s - Saturated Addition', 0aH, 00H
_DATA	ENDS
voltbl	SEGMENT
_volmd	DD	0ffffffffH
	DDSymXIndex: 	FLAT:main
	DD	010H
	DD	03cdH
voltbl	ENDS
xdata	SEGMENT
$unwind$PrintsS16 DD 031001H
	DD	0700ca210H
	DD	0300bH
$unwind$PrintsU16 DD 031001H
	DD	0700ca210H
	DD	0300bH
$unwind$Scalar_CalcZ DD 011801H
	DD	02218H
$unwind$Avx_CalcZ DD 032501H
	DD	014011cH
	DD	05015H
$unwind$Avx_AddS16 DD 011801H
	DD	08218H
$unwind$Avx_AddU16 DD 011801H
	DD	08218H
$unwind$Avx_MullS16 DD 011301H
	DD	0c213H
$unwind$main DD	021519H
	DD	07002d206H
	DD	imagerel __GSHandlerCheck
	DD	060H
xdata	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
a$ = 32
b$ = 48
c1$ = 64
c2$ = 80
__$ArrayPad$ = 96
main	PROC

; 133  : {

$LN3:
	push	rdi
	sub	rsp, 112				; 00000070H
	mov	rax, QWORD PTR __security_cookie
	xor	rax, rsp
	mov	QWORD PTR __$ArrayPad$[rsp], rax

; 134  :   vxmm a = {0};

	lea	rax, QWORD PTR a$[rsp]
	mov	rdi, rax
	xor	eax, eax
	mov	ecx, 16
	rep stosb

; 135  :   vxmm b = {0};

	lea	rax, QWORD PTR b$[rsp]
	mov	rdi, rax
	xor	eax, eax
	mov	ecx, 16
	rep stosb

; 136  :   vxmm c1 = {0};

	lea	rax, QWORD PTR c1$[rsp]
	mov	rdi, rax
	xor	eax, eax
	mov	ecx, 16
	rep stosb

; 137  :   vxmm c2 = {0};

	lea	rax, QWORD PTR c2$[rsp]
	mov	rdi, rax
	xor	eax, eax
	mov	ecx, 16
	rep stosb

; 138  :   
; 139  :   a.vs16[0] = 10;

	mov	eax, 2
	imul	rax, rax, 0
	mov	ecx, 10
	mov	WORD PTR a$[rsp+rax], cx

; 140  :   a.vs16[1] = 200;

	mov	eax, 2
	imul	rax, rax, 1
	mov	ecx, 200				; 000000c8H
	mov	WORD PTR a$[rsp+rax], cx

; 141  :   a.vs16[2] = 30;

	mov	eax, 2
	imul	rax, rax, 2
	mov	ecx, 30
	mov	WORD PTR a$[rsp+rax], cx

; 142  :   a.vs16[3] = -32766;

	mov	eax, 2
	imul	rax, rax, 3
	mov	ecx, -32766				; ffffffffffff8002H
	mov	WORD PTR a$[rsp+rax], cx

; 143  :   a.vs16[4] = 50;

	mov	eax, 2
	imul	rax, rax, 4
	mov	ecx, 50					; 00000032H
	mov	WORD PTR a$[rsp+rax], cx

; 144  :   a.vs16[5] = 60;

	mov	eax, 2
	imul	rax, rax, 5
	mov	ecx, 60					; 0000003cH
	mov	WORD PTR a$[rsp+rax], cx

; 145  :   a.vs16[6] = 32000;

	mov	eax, 2
	imul	rax, rax, 6
	mov	ecx, 32000				; 00007d00H
	mov	WORD PTR a$[rsp+rax], cx

; 146  :   a.vs16[7] = -32000;

	mov	eax, 2
	imul	rax, rax, 7
	mov	ecx, -32000				; ffffffffffff8300H
	mov	WORD PTR a$[rsp+rax], cx

; 147  :   
; 148  :   b.vs16[0] = 100;

	mov	eax, 2
	imul	rax, rax, 0
	mov	ecx, 100				; 00000064H
	mov	WORD PTR b$[rsp+rax], cx

; 149  :   b.vs16[1] = -200;

	mov	eax, 2
	imul	rax, rax, 1
	mov	ecx, -200				; ffffffffffffff38H
	mov	WORD PTR b$[rsp+rax], cx

; 150  :   b.vs16[2] = 32760;

	mov	eax, 2
	imul	rax, rax, 2
	mov	ecx, 32760				; 00007ff8H
	mov	WORD PTR b$[rsp+rax], cx

; 151  :   b.vs16[3] = -400;

	mov	eax, 2
	imul	rax, rax, 3
	mov	ecx, -400				; fffffffffffffe70H
	mov	WORD PTR b$[rsp+rax], cx

; 152  :   b.vs16[4] = 500;

	mov	eax, 2
	imul	rax, rax, 4
	mov	ecx, 500				; 000001f4H
	mov	WORD PTR b$[rsp+rax], cx

; 153  :   b.vs16[5] = -600;

	mov	eax, 2
	imul	rax, rax, 5
	mov	ecx, -600				; fffffffffffffda8H
	mov	WORD PTR b$[rsp+rax], cx

; 154  :   b.vs16[6] = 1200;

	mov	eax, 2
	imul	rax, rax, 6
	mov	ecx, 1200				; 000004b0H
	mov	WORD PTR b$[rsp+rax], cx

; 155  :   b.vs16[7] = -950;

	mov	eax, 2
	imul	rax, rax, 7
	mov	ecx, -950				; fffffffffffffc4aH
	mov	WORD PTR b$[rsp+rax], cx

; 156  :   
; 157  :   Avx_AddS16(&a,&b,&c1,&c2);

	lea	r9, QWORD PTR c2$[rsp]
	lea	r8, QWORD PTR c1$[rsp]
	lea	rdx, QWORD PTR b$[rsp]
	lea	rcx, QWORD PTR a$[rsp]
	call	Avx_AddS16

; 158  :   PrintsS16("a: ", &a);

	lea	rdx, QWORD PTR a$[rsp]
	lea	rcx, OFFSET FLAT:$SG26597
	call	PrintsS16

; 159  :   PrintsS16("b: ", &b);

	lea	rdx, QWORD PTR b$[rsp]
	lea	rcx, OFFSET FLAT:$SG26598
	call	PrintsS16

; 160  :   printf("Results for %s - Wraparound Addition\n", StringFromIdentifier(Avx_AddS16));

	lea	rdx, OFFSET FLAT:$SG26599
	lea	rcx, OFFSET FLAT:$SG26600
	call	printf

; 161  :   PrintsS16("c1:", &c1);

	lea	rdx, QWORD PTR c1$[rsp]
	lea	rcx, OFFSET FLAT:$SG26601
	call	PrintsS16

; 162  :   printf("Results for %s - Saturated Addition\n", StringFromIdentifier(Avx_AddS16));

	lea	rdx, OFFSET FLAT:$SG26602
	lea	rcx, OFFSET FLAT:$SG26603
	call	printf

; 163  :   PrintsS16("c2:", &c2);

	lea	rdx, QWORD PTR c2$[rsp]
	lea	rcx, OFFSET FLAT:$SG26604
	call	PrintsS16

; 164  :   printf("\n\n");

	lea	rcx, OFFSET FLAT:$SG26605
	call	printf

; 165  :   
; 166  :   
; 167  :   
; 168  :   a.vu16[0] = 10;

	mov	eax, 2
	imul	rax, rax, 0
	mov	ecx, 10
	mov	WORD PTR a$[rsp+rax], cx

; 169  :   a.vu16[1] = 200;

	mov	eax, 2
	imul	rax, rax, 1
	mov	ecx, 200				; 000000c8H
	mov	WORD PTR a$[rsp+rax], cx

; 170  :   a.vu16[2] = 300;

	mov	eax, 2
	imul	rax, rax, 2
	mov	ecx, 300				; 0000012cH
	mov	WORD PTR a$[rsp+rax], cx

; 171  :   a.vu16[3] = 32766;

	mov	eax, 2
	imul	rax, rax, 3
	mov	ecx, 32766				; 00007ffeH
	mov	WORD PTR a$[rsp+rax], cx

; 172  :   a.vu16[4] = 50;

	mov	eax, 2
	imul	rax, rax, 4
	mov	ecx, 50					; 00000032H
	mov	WORD PTR a$[rsp+rax], cx

; 173  :   a.vu16[5] = 20000;

	mov	eax, 2
	imul	rax, rax, 5
	mov	ecx, 20000				; 00004e20H
	mov	WORD PTR a$[rsp+rax], cx

; 174  :   a.vu16[6] = 32000;

	mov	eax, 2
	imul	rax, rax, 6
	mov	ecx, 32000				; 00007d00H
	mov	WORD PTR a$[rsp+rax], cx

; 175  :   a.vu16[7] = 32000;

	mov	eax, 2
	imul	rax, rax, 7
	mov	ecx, 32000				; 00007d00H
	mov	WORD PTR a$[rsp+rax], cx

; 176  :   
; 177  :   b.vu16[0] = 100;

	mov	eax, 2
	imul	rax, rax, 0
	mov	ecx, 100				; 00000064H
	mov	WORD PTR b$[rsp+rax], cx

; 178  :   b.vu16[1] = 200;

	mov	eax, 2
	imul	rax, rax, 1
	mov	ecx, 200				; 000000c8H
	mov	WORD PTR b$[rsp+rax], cx

; 179  :   b.vu16[2] = 65530;

	mov	eax, 2
	imul	rax, rax, 2
	mov	ecx, 65530				; 0000fffaH
	mov	WORD PTR b$[rsp+rax], cx

; 180  :   b.vu16[3] = 40000;

	mov	eax, 2
	imul	rax, rax, 3
	mov	ecx, 40000				; 00009c40H
	mov	WORD PTR b$[rsp+rax], cx

; 181  :   b.vu16[4] = 500;

	mov	eax, 2
	imul	rax, rax, 4
	mov	ecx, 500				; 000001f4H
	mov	WORD PTR b$[rsp+rax], cx

; 182  :   b.vu16[5] = 25000;

	mov	eax, 2
	imul	rax, rax, 5
	mov	ecx, 25000				; 000061a8H
	mov	WORD PTR b$[rsp+rax], cx

; 183  :   b.vu16[6] = 1200;

	mov	eax, 2
	imul	rax, rax, 6
	mov	ecx, 1200				; 000004b0H
	mov	WORD PTR b$[rsp+rax], cx

; 184  :   b.vu16[7] = 50000;

	mov	eax, 2
	imul	rax, rax, 7
	mov	ecx, 50000				; 0000c350H
	mov	WORD PTR b$[rsp+rax], cx

; 185  :   
; 186  :   Avx_AddU16(&a,&b,&c1,&c2);

	lea	r9, QWORD PTR c2$[rsp]
	lea	r8, QWORD PTR c1$[rsp]
	lea	rdx, QWORD PTR b$[rsp]
	lea	rcx, QWORD PTR a$[rsp]
	call	Avx_AddU16

; 187  :   PrintsU16("a: ", &a);

	lea	rdx, QWORD PTR a$[rsp]
	lea	rcx, OFFSET FLAT:$SG26606
	call	PrintsU16

; 188  :   PrintsU16("b: ", &b);

	lea	rdx, QWORD PTR b$[rsp]
	lea	rcx, OFFSET FLAT:$SG26607
	call	PrintsU16

; 189  :   printf("Results for %s - Wraparound Addition\n", StringFromIdentifier(Avx_AddU16));

	lea	rdx, OFFSET FLAT:$SG26608
	lea	rcx, OFFSET FLAT:$SG26609
	call	printf

; 190  :   PrintsU16("c1:", &c1);

	lea	rdx, QWORD PTR c1$[rsp]
	lea	rcx, OFFSET FLAT:$SG26610
	call	PrintsU16

; 191  :   printf("Results for %s - Saturated Addition\n", StringFromIdentifier(Avx_AddU16));

	lea	rdx, OFFSET FLAT:$SG26611
	lea	rcx, OFFSET FLAT:$SG26612
	call	printf

; 192  :   PrintsU16("c2:", &c2);

	lea	rdx, QWORD PTR c2$[rsp]
	lea	rcx, OFFSET FLAT:$SG26613
	call	PrintsU16

; 193  :   //NOTE(): The book goes over multiplication and subtractions but im going just listen to it
; 194  :   //        and come back if i need get more familiarity and understanding
; 195  :   //NOTE(): subtraction can also be saturated with the instruction's saturated variant _mm_subs_epi16()
; 196  :   //        the (s) after sub stands for saturated
; 197  :   //NOTE(): There is a difference between arithemetic and logical shifts
; 198  :   return 0;

	xor	eax, eax

; 199  : }

	mov	rcx, QWORD PTR __$ArrayPad$[rsp]
	xor	rcx, rsp
	call	__security_check_cookie
	add	rsp, 112				; 00000070H
	pop	rdi
	ret	0
main	ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_SraU16 PROC

; 131  : void Avx_SraU16(){}

	ret	0
Avx_SraU16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_SrlU16 PROC

; 130  : void Avx_SrlU16(){}

	ret	0
Avx_SrlU16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_SllU16 PROC

; 129  : void Avx_SllU16(){}

	ret	0
Avx_SllU16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_XorU16 PROC

; 128  : void Avx_XorU16(){}

	ret	0
Avx_XorU16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_OrU16 PROC

; 127  : void Avx_OrU16(){}

	ret	0
Avx_OrU16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_AndU16 PROC

; 126  : void Avx_AndU16(){}

	ret	0
Avx_AndU16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_MulS32_MethodB PROC

; 125  : void Avx_MulS32_MethodB(){}

	ret	0
Avx_MulS32_MethodB ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_MulS32_MethodA PROC

; 124  : void Avx_MulS32_MethodA(){}

	ret	0
Avx_MulS32_MethodA ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
Avx_MulS16 PROC

; 123  : void Avx_MulS16(){}

	ret	0
Avx_MulS16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
av$ = 0
bv$ = 16
temp_lo$ = 32
temp_hi$ = 48
res_lo$ = 64
res_hi$ = 80
a$ = 112
b$ = 120
Dest$ = 128
Avx_MullS16 PROC

; 99   : {

$LN3:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 100  :   //NOTE(): The add functions had 2 destinations for 'demo'ing wraparound
; 101  :   //        and saturated addition but multiplications necessitates 2 destionations
; 102  :   //        because 2 twice the number of bits as the opperand are needed to store the 
; 103  :   //        results so the result are stored as packed 32 bit chuncks.
; 104  :   //        that is why the operations requires more registers(twice as many) for lo and hi parts
; 105  :   __m128i av = _mm_load_si128((__m128i*)a);

	mov	rax, QWORD PTR a$[rsp]
	movdqu	xmm0, XMMWORD PTR [rax]
	movdqa	XMMWORD PTR av$[rsp], xmm0

; 106  :   __m128i bv = _mm_load_si128((__m128i*)b);

	mov	rax, QWORD PTR b$[rsp]
	movdqu	xmm0, XMMWORD PTR [rax]
	movdqa	XMMWORD PTR bv$[rsp], xmm0

; 107  :   //NOTE(): 16 means its operating on 16bit wide elements. the operands are stored ins diffent
; 108  :   //        registers a and b. the operations is broken up into 2 parts where the high 16 bits of
; 109  :   //        of the result is calculated by the hi variant of _mm_mull and store in a seperate register
; 110  :   //        and the low 16 bits of the result is calculated by the lo variant of _mm_mull...
; 111  :   __m128i temp_lo = _mm_mullo_epi16(av, bv);

	movdqa	xmm0, XMMWORD PTR av$[rsp]
	pmullw	xmm0, XMMWORD PTR bv$[rsp]
	movdqa	XMMWORD PTR temp_lo$[rsp], xmm0

; 112  :   __m128i temp_hi = _mm_mulhi_epi16(av, bv);

	movdqa	xmm0, XMMWORD PTR av$[rsp]
	pmulhw	xmm0, XMMWORD PTR bv$[rsp]
	movdqa	XMMWORD PTR temp_hi$[rsp], xmm0

; 113  :   //NOTE(): 16 means there are 16 bit wide elements in the 128bit register
; 114  :   //        therefore the element count is 8
; 115  :   //        so unpack lo will get the lower 4 elements of the 8 and put it
; 116  :   //        in a 128bit register as 32bit wide elements(size got promoted during the un pack)
; 117  :   __m128i res_lo = _mm_unpacklo_epi16(temp_lo, temp_hi);

	movdqa	xmm0, XMMWORD PTR temp_lo$[rsp]
	punpcklwd xmm0, XMMWORD PTR temp_hi$[rsp]
	movdqa	XMMWORD PTR res_lo$[rsp], xmm0

; 118  :   __m128i res_hi = _mm_unpackhi_epi16(temp_lo, temp_hi);

	movdqa	xmm0, XMMWORD PTR temp_lo$[rsp]
	punpckhwd xmm0, XMMWORD PTR temp_hi$[rsp]
	movdqa	XMMWORD PTR res_hi$[rsp], xmm0

; 119  :   _mm_store_si128((__m128i*)&Dest[0], res_lo);

	mov	eax, 16
	imul	rax, rax, 0
	mov	rcx, QWORD PTR Dest$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movdqa	xmm0, XMMWORD PTR res_lo$[rsp]
	movdqu	XMMWORD PTR [rax], xmm0

; 120  :   _mm_store_si128((__m128i*)&Dest[1], res_hi);

	mov	eax, 16
	imul	rax, rax, 1
	mov	rcx, QWORD PTR Dest$[rsp]
	add	rcx, rax
	mov	rax, rcx
	movdqa	xmm0, XMMWORD PTR res_hi$[rsp]
	movdqu	XMMWORD PTR [rax], xmm0

; 121  :   return;
; 122  : }

	add	rsp, 104				; 00000068H
	ret	0
Avx_MullS16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
av$ = 0
bv$ = 16
cav$ = 32
cbv$ = 48
a$ = 80
b$ = 88
DestA$ = 96
DestB$ = 104
Avx_AddU16 PROC

; 89   : {

$LN3:
	mov	QWORD PTR [rsp+32], r9
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 90   :   __m128i av = _mm_load_si128((__m128i*)a); //NOTE(): operands must be loaded on 16byte boundaries

	mov	rax, QWORD PTR a$[rsp]
	movdqu	xmm0, XMMWORD PTR [rax]
	movdqa	XMMWORD PTR av$[rsp], xmm0

; 91   :   __m128i bv = _mm_load_si128((__m128i*)b);

	mov	rax, QWORD PTR b$[rsp]
	movdqu	xmm0, XMMWORD PTR [rax]
	movdqa	XMMWORD PTR bv$[rsp], xmm0

; 92   :   __m128i cav = _mm_add_epi16(av, bv); //NOTE(): wraparound

	movdqa	xmm0, XMMWORD PTR av$[rsp]
	paddw	xmm0, XMMWORD PTR bv$[rsp]
	movdqa	XMMWORD PTR cav$[rsp], xmm0

; 93   :   __m128i cbv = _mm_adds_epu16(av, bv); //NOTE(): usees satureted instead of wraparound arithmetic

	movdqa	xmm0, XMMWORD PTR av$[rsp]
	paddusw	xmm0, XMMWORD PTR bv$[rsp]
	movdqa	XMMWORD PTR cbv$[rsp], xmm0

; 94   :   _mm_store_si128((__m128i*)DestA, cav);

	mov	rax, QWORD PTR DestA$[rsp]
	movdqa	xmm0, XMMWORD PTR cav$[rsp]
	movdqu	XMMWORD PTR [rax], xmm0

; 95   :   _mm_store_si128((__m128i*)DestB, cbv);

	mov	rax, QWORD PTR DestB$[rsp]
	movdqa	xmm0, XMMWORD PTR cbv$[rsp]
	movdqu	XMMWORD PTR [rax], xmm0

; 96   :   return;
; 97   : }

	add	rsp, 72					; 00000048H
	ret	0
Avx_AddU16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
av$ = 0
bv$ = 16
cav$ = 32
cbv$ = 48
a$ = 80
b$ = 88
DestA$ = 96
DestB$ = 104
Avx_AddS16 PROC

; 79   : {

$LN3:
	mov	QWORD PTR [rsp+32], r9
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 80   :   __m128i av = _mm_load_si128((__m128i*)a); //NOTE(): operands must be loaded on 16byte boundaries

	mov	rax, QWORD PTR a$[rsp]
	movdqu	xmm0, XMMWORD PTR [rax]
	movdqa	XMMWORD PTR av$[rsp], xmm0

; 81   :   __m128i bv = _mm_load_si128((__m128i*)b);

	mov	rax, QWORD PTR b$[rsp]
	movdqu	xmm0, XMMWORD PTR [rax]
	movdqa	XMMWORD PTR bv$[rsp], xmm0

; 82   :   __m128i cav = _mm_add_epi16(av, bv); //NOTE(): wraparound

	movdqa	xmm0, XMMWORD PTR av$[rsp]
	paddw	xmm0, XMMWORD PTR bv$[rsp]
	movdqa	XMMWORD PTR cav$[rsp], xmm0

; 83   :   __m128i cbv = _mm_adds_epi16(av, bv); //NOTE(): usees satureted instead of wraparound arithmetic

	movdqa	xmm0, XMMWORD PTR av$[rsp]
	paddsw	xmm0, XMMWORD PTR bv$[rsp]
	movdqa	XMMWORD PTR cbv$[rsp], xmm0

; 84   :   _mm_store_si128((__m128i*)DestA, cav);

	mov	rax, QWORD PTR DestA$[rsp]
	movdqa	xmm0, XMMWORD PTR cav$[rsp]
	movdqu	XMMWORD PTR [rax], xmm0

; 85   :   _mm_store_si128((__m128i*)DestB, cbv);

	mov	rax, QWORD PTR DestB$[rsp]
	movdqa	xmm0, XMMWORD PTR cbv$[rsp]
	movdqu	XMMWORD PTR [rax], xmm0

; 86   :   return;
; 87   : }

	add	rsp, 72					; 00000048H
	ret	0
Avx_AddS16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
ElemProcesesedCount$ = 0
Index$1 = 8
Index$2 = 16
SimdElemCount$ = 24
XVals$3 = 32
YVals$4 = 64
ZVals$5 = 96
x$ = 176
y$ = 184
Dest$ = 192
Count$ = 200
Avx_CalcZ PROC

; 52   : {

$LN7:
	mov	QWORD PTR [rsp+32], r9
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rbp
	sub	rsp, 160				; 000000a0H
	lea	rbp, QWORD PTR [rsp+32]
	and	rbp, -32				; ffffffffffffffe0H

; 53   :   uint64_t ElemProcesesedCount = 0;

	mov	QWORD PTR ElemProcesesedCount$[rbp], 0

; 54   :   uint64_t SimdElemCount = 8;

	mov	QWORD PTR SimdElemCount$[rbp], 8
$LN2@Avx_CalcZ:

; 55   :   while((Count-ElemProcesesedCount) >= SimdElemCount)

	mov	rax, QWORD PTR ElemProcesesedCount$[rbp]
	mov	rcx, QWORD PTR Count$[rsp]
	sub	rcx, rax
	mov	rax, rcx
	cmp	rax, QWORD PTR SimdElemCount$[rbp]
	jb	SHORT $LN3@Avx_CalcZ

; 56   :   {
; 57   :     uint64_t Index = ElemProcesesedCount;

	mov	rax, QWORD PTR ElemProcesesedCount$[rbp]
	mov	QWORD PTR Index$1[rbp], rax

; 58   :     //Begin Process via AVX
; 59   :     __m256 XVals =  _mm256_loadu_ps(&x[Index]);

	mov	rax, QWORD PTR x$[rsp]
	mov	rcx, QWORD PTR Index$1[rbp]
	lea	rax, QWORD PTR [rax+rcx*4]
	vmovups	ymm0, YMMWORD PTR [rax]
	vmovups	YMMWORD PTR XVals$3[rbp], ymm0

; 60   :     __m256 YVals =  _mm256_loadu_ps(&y[Index]);

	mov	rax, QWORD PTR y$[rsp]
	mov	rcx, QWORD PTR Index$1[rbp]
	lea	rax, QWORD PTR [rax+rcx*4]
	vmovups	ymm0, YMMWORD PTR [rax]
	vmovups	YMMWORD PTR YVals$4[rbp], ymm0

; 61   :     __m256 ZVals =  _mm256_add_ps(XVals, YVals);

	vmovups	ymm0, YMMWORD PTR XVals$3[rbp]
	vaddps	ymm0, ymm0, YMMWORD PTR YVals$4[rbp]
	vmovups	YMMWORD PTR ZVals$5[rbp], ymm0

; 62   :     _mm256_storeu_ps(&Dest[Index], ZVals);

	mov	rax, QWORD PTR Dest$[rsp]
	mov	rcx, QWORD PTR Index$1[rbp]
	lea	rax, QWORD PTR [rax+rcx*4]
	vmovups	ymm0, YMMWORD PTR ZVals$5[rbp]
	vmovups	YMMWORD PTR [rax], ymm0

; 63   :     //End Process via AVX
; 64   :     ElemProcesesedCount += SimdElemCount; //Batches of SimdElemCount

	mov	rax, QWORD PTR SimdElemCount$[rbp]
	mov	rcx, QWORD PTR ElemProcesesedCount$[rbp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR ElemProcesesedCount$[rbp], rax

; 65   :   }

	jmp	$LN2@Avx_CalcZ
$LN3@Avx_CalcZ:
$LN4@Avx_CalcZ:

; 66   :   //Process Remaining ElmCount which is less than SimdElemCount
; 67   :   while(ElemProcesesedCount < Count)

	mov	rax, QWORD PTR Count$[rsp]
	cmp	QWORD PTR ElemProcesesedCount$[rbp], rax
	jae	SHORT $LN5@Avx_CalcZ

; 68   :   {
; 69   :     uint64_t Index = ElemProcesesedCount;

	mov	rax, QWORD PTR ElemProcesesedCount$[rbp]
	mov	QWORD PTR Index$2[rbp], rax

; 70   :     //Begin Process via scalar
; 71   :     Dest[Index] = x[Index] + y[Index];

	mov	rax, QWORD PTR x$[rsp]
	mov	rcx, QWORD PTR Index$2[rbp]
	mov	rdx, QWORD PTR y$[rsp]
	mov	r8, QWORD PTR Index$2[rbp]
	movss	xmm0, DWORD PTR [rax+rcx*4]
	addss	xmm0, DWORD PTR [rdx+r8*4]
	mov	rax, QWORD PTR Dest$[rsp]
	mov	rcx, QWORD PTR Index$2[rbp]
	movss	DWORD PTR [rax+rcx*4], xmm0

; 72   :     //Begin Process via scalar
; 73   :     ElemProcesesedCount += 1; //1 at a time

	mov	rax, QWORD PTR ElemProcesesedCount$[rbp]
	inc	rax
	mov	QWORD PTR ElemProcesesedCount$[rbp], rax

; 74   :   }

	jmp	SHORT $LN4@Avx_CalcZ
$LN5@Avx_CalcZ:

; 75   :   return;
; 76   : }

	add	rsp, 160				; 000000a0H
	pop	rbp
	ret	0
Avx_CalcZ ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
i$1 = 0
x$ = 32
y$ = 40
Dest$ = 48
Count$ = 56
Scalar_CalcZ PROC

; 44   : {

$LN6:
	mov	QWORD PTR [rsp+32], r9
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 45   :   for(uint64_t i=0;i<Count;i++)

	mov	QWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@Scalar_Cal
$LN2@Scalar_Cal:
	mov	rax, QWORD PTR i$1[rsp]
	inc	rax
	mov	QWORD PTR i$1[rsp], rax
$LN4@Scalar_Cal:
	mov	rax, QWORD PTR Count$[rsp]
	cmp	QWORD PTR i$1[rsp], rax
	jae	SHORT $LN3@Scalar_Cal

; 46   :   {
; 47   :     Dest[i] = x[i]+y[i];

	mov	rax, QWORD PTR x$[rsp]
	mov	rcx, QWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR y$[rsp]
	mov	r8, QWORD PTR i$1[rsp]
	movss	xmm0, DWORD PTR [rax+rcx*4]
	addss	xmm0, DWORD PTR [rdx+r8*4]
	mov	rax, QWORD PTR Dest$[rsp]
	mov	rcx, QWORD PTR i$1[rsp]
	movss	DWORD PTR [rax+rcx*4], xmm0

; 48   :   }

	jmp	SHORT $LN2@Scalar_Cal
$LN3@Scalar_Cal:

; 49   :   return;
; 50   : }

	add	rsp, 24
	ret	0
Scalar_CalcZ ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
label$ = 112
a$ = 120
PrintsU16 PROC

; 35   : {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rbx
	push	rdi
	sub	rsp, 88					; 00000058H

; 36   :   printf("%s %8.hu %8.hu %8.hu %8.hu |"

	mov	eax, 2
	imul	rax, rax, 7
	mov	rcx, QWORD PTR a$[rsp]
	movsx	eax, WORD PTR [rcx+rax]
	mov	ecx, 2
	imul	rcx, rcx, 6
	mov	rdx, QWORD PTR a$[rsp]
	movsx	ecx, WORD PTR [rdx+rcx]
	mov	edx, 2
	imul	rdx, rdx, 5
	mov	r8, QWORD PTR a$[rsp]
	movsx	edx, WORD PTR [r8+rdx]
	mov	r8d, 2
	imul	r8, r8, 4
	mov	r9, QWORD PTR a$[rsp]
	movsx	r8d, WORD PTR [r9+r8]
	mov	r9d, 2
	imul	r9, r9, 3
	mov	r10, QWORD PTR a$[rsp]
	movsx	r9d, WORD PTR [r10+r9]
	mov	r10d, 2
	imul	r10, r10, 2
	mov	r11, QWORD PTR a$[rsp]
	movsx	r10d, WORD PTR [r11+r10]
	mov	r11d, 2
	imul	r11, r11, 1
	mov	rbx, QWORD PTR a$[rsp]
	movsx	ebx, WORD PTR [rbx+r11]
	mov	r11d, 2
	imul	r11, r11, 0
	mov	rdi, QWORD PTR a$[rsp]
	movsx	edi, WORD PTR [rdi+r11]
	mov	DWORD PTR [rsp+72], eax
	mov	DWORD PTR [rsp+64], ecx
	mov	DWORD PTR [rsp+56], edx
	mov	DWORD PTR [rsp+48], r8d
	mov	DWORD PTR [rsp+40], r9d
	mov	DWORD PTR [rsp+32], r10d
	mov	r9d, ebx
	mov	r8d, edi
	mov	rdx, QWORD PTR label$[rsp]
	lea	rcx, OFFSET FLAT:$SG26482
	call	printf

; 37   :          " %8.hu %8.hu %8.hu %8.hu\n", label,
; 38   :          a->vs16[0], a->vs16[1], a->vs16[2], a->vs16[3],
; 39   :          a->vs16[4], a->vs16[5], a->vs16[6], a->vs16[7]);
; 40   :   return;
; 41   : }

	add	rsp, 88					; 00000058H
	pop	rdi
	pop	rbx
	ret	0
PrintsU16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File F:\Dev\parallel-algos\test\simd_ex.c
_TEXT	SEGMENT
label$ = 112
a$ = 120
PrintsS16 PROC

; 27   : {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rbx
	push	rdi
	sub	rsp, 88					; 00000058H

; 28   :   printf("%s %8.d %8.d %8.d %8.d |"

	mov	eax, 2
	imul	rax, rax, 7
	mov	rcx, QWORD PTR a$[rsp]
	movsx	eax, WORD PTR [rcx+rax]
	mov	ecx, 2
	imul	rcx, rcx, 6
	mov	rdx, QWORD PTR a$[rsp]
	movsx	ecx, WORD PTR [rdx+rcx]
	mov	edx, 2
	imul	rdx, rdx, 5
	mov	r8, QWORD PTR a$[rsp]
	movsx	edx, WORD PTR [r8+rdx]
	mov	r8d, 2
	imul	r8, r8, 4
	mov	r9, QWORD PTR a$[rsp]
	movsx	r8d, WORD PTR [r9+r8]
	mov	r9d, 2
	imul	r9, r9, 3
	mov	r10, QWORD PTR a$[rsp]
	movsx	r9d, WORD PTR [r10+r9]
	mov	r10d, 2
	imul	r10, r10, 2
	mov	r11, QWORD PTR a$[rsp]
	movsx	r10d, WORD PTR [r11+r10]
	mov	r11d, 2
	imul	r11, r11, 1
	mov	rbx, QWORD PTR a$[rsp]
	movsx	ebx, WORD PTR [rbx+r11]
	mov	r11d, 2
	imul	r11, r11, 0
	mov	rdi, QWORD PTR a$[rsp]
	movsx	edi, WORD PTR [rdi+r11]
	mov	DWORD PTR [rsp+72], eax
	mov	DWORD PTR [rsp+64], ecx
	mov	DWORD PTR [rsp+56], edx
	mov	DWORD PTR [rsp+48], r8d
	mov	DWORD PTR [rsp+40], r9d
	mov	DWORD PTR [rsp+32], r10d
	mov	r9d, ebx
	mov	r8d, edi
	mov	rdx, QWORD PTR label$[rsp]
	lea	rcx, OFFSET FLAT:$SG26475
	call	printf

; 29   :          " %8.d %8.d %8.d %8.d\n", label,
; 30   :          a->vs16[0], a->vs16[1], a->vs16[2], a->vs16[3],
; 31   :          a->vs16[4], a->vs16[5], a->vs16[6], a->vs16[7]);
; 32   :   return;
; 33   : }

	add	rsp, 88					; 00000058H
	pop	rdi
	pop	rbx
	ret	0
PrintsS16 ENDP
_TEXT	ENDS
END
