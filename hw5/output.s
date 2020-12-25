_start_MAIN:
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	li	t0, 1065353216
	sw	t0, -8(sp)
	flw fa0, -8(sp)
	call	_write_float
	ld	ra,8(sp)
	ld	s0,0(sp)
	addi	sp,sp,16
	jr	ra