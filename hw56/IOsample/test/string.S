	.file	"string.S"
	.option nopic
	.text
	.section	.rodata
	.align	3
.LC6:
	.string	"Hello Compiler!\n"
	.text
	.align	1
	.globl	_start_MAIN
	.type	_start_MAIN, @function
_start_MAIN:
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	lui	a5,%hi(.LC6)
	addi	a0,a5,%lo(.LC6)
	call	_write_str
	li	a5,0
	mv	a0,a5
	ld	ra,8(sp)
	ld	s0,0(sp)
	addi	sp,sp,16
	jr	ra
	.size	_start_MAIN, .-_start_MAIN
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
