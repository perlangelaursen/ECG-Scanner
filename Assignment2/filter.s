	.file	"filter.c"
	.local	lowpassArray
	.comm	lowpassArray,132,32
	.local	highpassArray
	.comm	highpassArray,20,16
	.local	derivativeNo
	.comm	derivativeNo,4,4
	.local	squaredArray
	.comm	squaredArray,124,32
	.text
	.globl	dataFilter
	.type	dataFilter, @function
dataFilter:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	%rdx, -24(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -28(%rbp)
	movl	-28(%rbp), %edx
	movl	-12(%rbp), %ecx
	movq	-8(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	lowPass
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	highPass
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	derivative
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	squared
	movl	-28(%rbp), %edx
	movl	-16(%rbp), %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	movingWindowIntegration
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	dataFilter, .-dataFilter
	.globl	lowPass
	.type	lowPass, @function
lowPass:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	%edx, -48(%rbp)
	movl	-48(%rbp), %eax
	movl	$33, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	calcIndex
	movl	%eax, %r13d
	movl	-48(%rbp), %eax
	movl	$33, %edx
	movl	$1, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	lowpassArray(,%rax,4), %eax
	leal	(%rax,%rax), %ebx
	movl	-48(%rbp), %eax
	movl	$33, %edx
	movl	$2, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	lowpassArray(,%rax,4), %eax
	subl	%eax, %ebx
	movl	%ebx, %r12d
	movl	-44(%rbp), %edx
	movl	-48(%rbp), %eax
	movl	$0, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ebx
	movl	-44(%rbp), %edx
	movl	-48(%rbp), %eax
	movl	$6, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	$0, %eax
	subl	%edx, %eax
	addl	%eax, %eax
	addl	%eax, %ebx
	movl	-44(%rbp), %edx
	movl	-48(%rbp), %eax
	movl	$12, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	addl	%ebx, %eax
	leal	31(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$5, %eax
	leal	(%r12,%rax), %edx
	movslq	%r13d, %rax
	movl	%edx, lowpassArray(,%rax,4)
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	lowPass, .-lowPass
	.globl	highPass
	.type	highPass, @function
highPass:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	$5, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	calcIndex
	movl	%eax, %r12d
	movl	-20(%rbp), %eax
	movl	$5, %edx
	movl	$1, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	highpassArray(,%rax,4), %ebx
	movl	-20(%rbp), %eax
	movl	$33, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	lowpassArray(,%rax,4), %eax
	leal	31(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$5, %eax
	subl	%eax, %ebx
	movl	-20(%rbp), %eax
	movl	$33, %edx
	movl	$16, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	lowpassArray(,%rax,4), %eax
	addl	%eax, %ebx
	movl	-20(%rbp), %eax
	movl	$33, %edx
	movl	$17, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	lowpassArray(,%rax,4), %eax
	subl	%eax, %ebx
	movl	-20(%rbp), %eax
	movl	$33, %edx
	movl	$32, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	lowpassArray(,%rax,4), %eax
	leal	31(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$5, %eax
	leal	(%rbx,%rax), %edx
	movslq	%r12d, %rax
	movl	%edx, highpassArray(,%rax,4)
	nop
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	highPass, .-highPass
	.globl	derivative
	.type	derivative, @function
derivative:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	$5, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	highpassArray(,%rax,4), %eax
	leal	(%rax,%rax), %ebx
	movl	-20(%rbp), %eax
	movl	$5, %edx
	movl	$1, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	highpassArray(,%rax,4), %eax
	addl	%eax, %ebx
	movl	-20(%rbp), %eax
	movl	$5, %edx
	movl	$3, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	highpassArray(,%rax,4), %eax
	subl	%eax, %ebx
	movl	-20(%rbp), %eax
	movl	$5, %edx
	movl	$4, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	highpassArray(,%rax,4), %edx
	movl	$0, %eax
	subl	%edx, %eax
	addl	%eax, %eax
	addl	%ebx, %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	movl	%eax, derivativeNo(%rip)
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	derivative, .-derivative
	.globl	squared
	.type	squared, @function
squared:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	$31, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	calcIndex
	movl	%eax, %ecx
	movl	derivativeNo(%rip), %edx
	movl	derivativeNo(%rip), %eax
	imull	%eax, %edx
	movslq	%ecx, %rax
	movl	%edx, squaredArray(,%rax,4)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	squared, .-squared
	.globl	movingWindowIntegration
	.type	movingWindowIntegration, @function
movingWindowIntegration:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	$0, -4(%rbp)
	movl	$1, -8(%rbp)
	jmp	.L7
.L8:
	movl	$30, %eax
	subl	-8(%rbp), %eax
	movl	%eax, %ecx
	movl	-32(%rbp), %eax
	movl	$31, %edx
	movl	%ecx, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	movl	squaredArray(,%rax,4), %eax
	addl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L7:
	cmpl	$30, -8(%rbp)
	jle	.L8
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	$0, %esi
	movl	%eax, %edi
	call	calcIndex
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rsi
	movl	-4(%rbp), %ecx
	movl	$-2004318071, %edx
	movl	%ecx, %eax
	imull	%edx
	leal	(%rdx,%rcx), %eax
	sarl	$4, %eax
	movl	%eax, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, (%rsi)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	movingWindowIntegration, .-movingWindowIntegration
	.ident	"GCC: (GNU) 5.1.1 20150618 (Red Hat 5.1.1-4)"
	.section	.note.GNU-stack,"",@progbits
