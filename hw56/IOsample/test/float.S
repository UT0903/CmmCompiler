_start_MAIN:
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	call    _read_float
	call	_write_float
	li	a5,0
	mv	a0,a5
	ld	ra,8(sp)
	ld	s0,0(sp)
	addi	sp,sp,16
	jr	ra
    .size   _start_MAIN, .-_start_MAIN
    .globl  _start_MAIN
    .type   _start_MAIN, @function
