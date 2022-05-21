	.file	"2.c"
	.intel_syntax noprefix
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%lf\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
foo:
endbr64
	push	rbp
	mov	rbp, rsp
	mov	DWORD PTR -20[rbp], edi
	mov	DWORD PTR -16[rbp], 1
	mov	DWORD PTR -12[rbp], 3
	mov	DWORD PTR -8[rbp], 7
	mov	DWORD PTR -4[rbp], 2
	mov	edx, DWORD PTR -16[rbp]
	mov	eax, DWORD PTR -12[rbp]
	imul	eax, DWORD PTR -20[rbp]
	lea	ecx, [rdx+rax]
	mov	eax, DWORD PTR -20[rbp]
	imul	eax, eax
	mov	edx, eax
	mov	eax, DWORD PTR -8[rbp]
	imul	eax, edx
	add	ecx, eax
	mov	eax, DWORD PTR -20[rbp]
	imul	eax, eax
	imul	eax, DWORD PTR -20[rbp]
	mov	edx, eax
	mov	eax, DWORD PTR -4[rbp]
	imul	eax, edx
	add	eax, ecx
	pop	rbp
	ret
	.size	foo, .-foo
main:
.LFB39:
	.cfi_startproc
	endbr64
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	xor	edi, edi
	call	time@PLT
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, rax
	xor	eax, eax
	movsd	QWORD PTR 8[rsp], xmm1
	call foo
	.p2align 4,,10
	.p2align 3
.L2:
#APP
# 11 "2.c" 1
	 
# 0 "" 2
#NO_APP
	add	eax, 1
	cmp	eax, 1073741824
	jne	.L2
	xor	edi, edi
	call	time@PLT
	pxor	xmm0, xmm0
	mov	edi, 1
	lea	rsi, .LC0[rip]
	cvtsi2sd	xmm0, rax
	subsd	xmm0, QWORD PTR 8[rsp]
	mov	eax, 1
	call	__printf_chk@PLT
	xor	eax, eax
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
