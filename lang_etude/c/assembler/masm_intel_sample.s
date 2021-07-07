	.file	"sample.c"
	.intel_syntax noprefix
	.text
	.comm	a,4,4
	.comm	b,4,4
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	DWORD PTR a[rip], 0
.L2:
	mov	eax, DWORD PTR a[rip]
	lea	edx, 1[rax]
	mov	eax, DWORD PTR b[rip]
	add	eax, edx
	mov	DWORD PTR b[rip], eax
	mov	eax, DWORD PTR a[rip]
	add	eax, 1
	mov	DWORD PTR a[rip], eax
	mov	eax, DWORD PTR a[rip]
	cmp	eax, 10
	jle	.L2
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
