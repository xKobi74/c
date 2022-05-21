    .intel_syntax noprefix
    .text
    .globl  foo
    .type   foo, @function
foo:
    endbr64
    mov edx, 1
    mov eax, 3
    imul    eax, edi
    lea ecx, [rdx+rax]
    mov eax, edi
    imul    eax, eax
    mov edx, eax
    mov eax, 7
    imul    eax, edx
    add ecx, eax
    mov eax, edi
    imul    eax, eax
    imul    eax, edi
    mov edx, eax
    mov eax, 2
    imul    eax, edx
    add eax, ecx
    ret
    .size   foo, .-foo