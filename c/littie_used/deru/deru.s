	.file	"deru.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"\345\207\272\343\202\213\343\201\213\343\201\252\357\274\237\357\274\237"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$.LC0, (%esp)
	call	printf
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.5 20101001 (Vine Linux 4.4.5-6vl6)"
	.section	.note.GNU-stack,"",@progbits
