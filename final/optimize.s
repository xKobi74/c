	.intel_syntax noprefix
	.text
	.globl	foo
	.type	foo, @function
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
  