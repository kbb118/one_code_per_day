	.file	"sample.c"
	.text
	.comm	a,4,4
	.comm	b,4,4
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, a(%rip)
.L2:
	movl	a(%rip), %eax
	leal	1(%rax), %edx
	movl	b(%rip), %eax
	addl	%edx, %eax
	movl	%eax, b(%rip)
	movl	a(%rip), %eax
	addl	$1, %eax
	movl	%eax, a(%rip)
	movl	a(%rip), %eax
	cmpl	$10, %eax
	jle	.L2
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
