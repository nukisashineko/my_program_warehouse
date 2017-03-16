	.file	"HelloWorld.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"hello world !\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$.LC0, (%esp)
	call	puts
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.5 20101001 (Vine Linux 4.4.5-6vl6)"
	.section	.note.GNU-stack,"",@progbits
