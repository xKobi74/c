	.intel_syntax noprefix
	.text
	.globl	sortfn
	.type	sortfn, @function
sortfn:
	endbr64
	cmp	esi, 1
	jle	.L1
	lea	r9d, -2[rsi]
	add	r9, 2
	mov	r8d, 1
	jmp	.L6
.L3:
	movsx rdx, edx

	mov ecx, DWORD PTR [rdi+r8*4-4]

	lea rax, [rdi+rdx*4]
	mov edx, DWORD PTR [rax]
	mov DWORD PTR [rax], ecx

	mov DWORD PTR [rdi+r8*4-4], edx
	
	add r8, 0x1
	cmp r8, r9
    je	.L1
.L6:
	lea	edx, -1[r8]
	cmp	esi, r8d
	jle	.L3
	mov	rax, r8
.L5:
	movsx	rcx, edx
	mov	ecx, DWORD PTR [rdi+rcx*4]
	cmp	DWORD PTR [rdi+rax*4], ecx
	cmovl	edx, eax
	add	rax, 1
	cmp	esi, eax
	jg	.L5
	jmp	.L3
.L1:
	ret
	.size	sortfn, .-sortfn
  .intel_syntax noprefix
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LMC0:
	.string	"%d"
.LMC1:
	.string	"%d "
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
	endbr64
	push	r12
	xor	eax, eax
	lea	rdi, .LMC0[rip]
	push	rbp
	push	rbx
	sub	rsp, 16
	lea	rsi, 12[rsp]
	call	__isoc99_scanf@PLT
	dec	eax
	je	.LM2
.LM3:
	call	abort@PLT
.LM2:
	movsx	rdi, DWORD PTR 12[rsp]
	xor	ebp, ebp
	lea	r12, .LMC0[rip]
	sal	rdi, 2
	call	malloc@PLT
	mov	rbx, rax
	test	rax, rax
	je	.LM3
.LM4:
	mov	esi, DWORD PTR 12[rsp]
	cmp	esi, ebp
	jle	.LM13
	lea	rsi, [rbx+rbp*4]
	xor	eax, eax
	mov	rdi, r12
	inc	rbp
	call	__isoc99_scanf@PLT
	dec	eax
	je	.LM4
	jmp	.LM3
.LM13:
	mov	rdi, rbx
	xor	ebp, ebp
	lea	r12, .LMC1[rip]
	call	sortfn@PLT
.LM6:
	cmp	DWORD PTR 12[rsp], ebp
	jle	.LM14
	mov	edx, DWORD PTR [rbx+rbp*4]
	mov	rsi, r12
	mov	edi, 1
	xor	eax, eax
	inc	rbp
	call	__printf_chk@PLT
	jmp	.LM6
.LM14:
	mov	edi, 10
	call	putchar@PLT
	add	rsp, 16
	xor	eax, eax
	pop	rbx
	pop	rbp
	pop	r12
	ret
	.size	main, .-main
