	.data
_g_delta: .word 1065353216
	.text
_start_floor:
	sd fp, -8(sp)
	sd ra, 0(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_floor
	lw ra, 0(ra)
	sub sp, sp, ra
	sd t0, 8(sp)
	sd t1, 16(sp)
	sd t2, 24(sp)
	sd t3, 32(sp)
	sd t4, 40(sp)
	sd t5, 48(sp)
	sd t6, 56(sp)
	sd s2, 64(sp)
	sd s3, 72(sp)
	sd s4, 80(sp)
	sd s5, 88(sp)
	sd s6, 96(sp)
	sd s7, 104(sp)
	sd s8, 112(sp)
	sd s9, 120(sp)
	sd s10, 128(sp)
	sd s11, 136(sp)
	fsw ft0, 144(sp)
	fsw ft1, 148(sp)
	fsw ft2, 152(sp)
	fsw ft3, 156(sp)
	fsw ft4, 160(sp)
	fsw ft5, 164(sp)
	fsw ft6, 168(sp)
	fsw ft7, 172(sp)
	li t0, 16
	add t0, fp, t0
	flw ft0, 0(t0)
	li t1, -4
	add t1, fp, t1
	fcvt.w.s t2, ft0
	sw ft0, 0(t1)
	li t3, -4
	add t3, fp, t3
	lw t4, 0(t3)
	mv a0, t4
	la t5, _end_floor
	jr t5
_end_floor:
	ld t0, 8(sp)
	ld t1, 16(sp)
	ld t2, 24(sp)
	ld t3, 32(sp)
	ld t4, 40(sp)
	ld t5, 48(sp)
	ld t6, 56(sp)
	ld s2, 64(sp)
	ld s3, 72(sp)
	ld s4, 80(sp)
	ld s5, 88(sp)
	ld s6, 96(sp)
	ld s7, 104(sp)
	ld s8, 112(sp)
	ld s9, 120(sp)
	ld s10, 128(sp)
	ld s11, 136(sp)
	flw ft0, 144(sp)
	flw ft1, 148(sp)
	flw ft2, 152(sp)
	flw ft3, 156(sp)
	flw ft4, 160(sp)
	flw ft5, 164(sp)
	flw ft6, 168(sp)
	flw ft7, 172(sp)
	ld ra, 8(fp)
	addi sp, fp, 8
	ld fp, 0(fp)
	jr ra
	.data
_frameSize_floor:	.word	180
	.text
_start_ceil:
	sd fp, -8(sp)
	sd ra, 0(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_ceil
	lw ra, 0(ra)
	sub sp, sp, ra
	sd t0, 8(sp)
	sd t1, 16(sp)
	sd t2, 24(sp)
	sd t3, 32(sp)
	sd t4, 40(sp)
	sd t5, 48(sp)
	sd t6, 56(sp)
	sd s2, 64(sp)
	sd s3, 72(sp)
	sd s4, 80(sp)
	sd s5, 88(sp)
	sd s6, 96(sp)
	sd s7, 104(sp)
	sd s8, 112(sp)
	sd s9, 120(sp)
	sd s10, 128(sp)
	sd s11, 136(sp)
	fsw ft0, 144(sp)
	fsw ft1, 148(sp)
	fsw ft2, 152(sp)
	fsw ft3, 156(sp)
	fsw ft4, 160(sp)
	fsw ft5, 164(sp)
	fsw ft6, 168(sp)
	fsw ft7, 172(sp)
	li t6, 16
	add t6, fp, t6
	flw ft1, 0(t6)
	li s2, 0
	fcvt.s.w ft2, s2
	flt.s s3, s2, ft1
	bnez s3, _L0
	la s4, _L1
	jr s4
_L0:
	li s5, 16
	add s5, fp, s5
	flw ft3, 0(s5)
	la s6, _g_delta
	flw ft4, 0(s6)
	fadd.s ft5, ft3, ft4
	li s7, -4
	add s7, fp, s7
	fcvt.w.s s8, ft5
	sw ft5, 0(s7)
	la s9, _L2
	jr s9
_L1:
	li s10, 16
	add s10, fp, s10
	flw ft6, 0(s10)
	la s11, _g_delta
	flw ft7, 0(s11)
	fsub.s ft0, ft6, ft7
	li t0, -4
	add t0, fp, t0
	fcvt.w.s t1, ft0
	sw ft0, 0(t0)
_L2:
	li t2, -4
	add t2, fp, t2
	lw t3, 0(t2)
	mv a0, t3
	la t4, _end_ceil
	jr t4
_end_ceil:
	ld t0, 8(sp)
	ld t1, 16(sp)
	ld t2, 24(sp)
	ld t3, 32(sp)
	ld t4, 40(sp)
	ld t5, 48(sp)
	ld t6, 56(sp)
	ld s2, 64(sp)
	ld s3, 72(sp)
	ld s4, 80(sp)
	ld s5, 88(sp)
	ld s6, 96(sp)
	ld s7, 104(sp)
	ld s8, 112(sp)
	ld s9, 120(sp)
	ld s10, 128(sp)
	ld s11, 136(sp)
	flw ft0, 144(sp)
	flw ft1, 148(sp)
	flw ft2, 152(sp)
	flw ft3, 156(sp)
	flw ft4, 160(sp)
	flw ft5, 164(sp)
	flw ft6, 168(sp)
	flw ft7, 172(sp)
	ld ra, 8(fp)
	addi sp, fp, 8
	ld fp, 0(fp)
	jr ra
	.data
_frameSize_ceil:	.word	184
	.text
_start_MAIN:
	sd fp, -8(sp)
	sd ra, 0(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_MAIN
	lw ra, 0(ra)
	sub sp, sp, ra
	sd t0, 8(sp)
	sd t1, 16(sp)
	sd t2, 24(sp)
	sd t3, 32(sp)
	sd t4, 40(sp)
	sd t5, 48(sp)
	sd t6, 56(sp)
	sd s2, 64(sp)
	sd s3, 72(sp)
	sd s4, 80(sp)
	sd s5, 88(sp)
	sd s6, 96(sp)
	sd s7, 104(sp)
	sd s8, 112(sp)
	sd s9, 120(sp)
	sd s10, 128(sp)
	sd s11, 136(sp)
	fsw ft0, 144(sp)
	fsw ft1, 148(sp)
	fsw ft2, 152(sp)
	fsw ft3, 156(sp)
	fsw ft4, 160(sp)
	fsw ft5, 164(sp)
	fsw ft6, 168(sp)
	fsw ft7, 172(sp)
	la t5, _CONSTANT_0
	mv a0, t5
	la t6, _write_str
	jalr 0(t6)
	la s2, _read_float
	jalr 0(s2)
	fmv.s ft1, fa0
	li s3, -4
	add s3, fp, s3
	fsw ft1, 0(s3)
	li s4, -4
	add s4, fp, s4
	flw ft2, 0(s4)
	fsd ft2, 0(sp)
	addi sp, sp, -8
	la s5, _start_ceil
	jalr 0(s5)
	addi sp, sp, 8
	mv s6, a0
	mv a0, s6
	la s7, _write_int
	jalr 0(s7)
	la s8, _CONSTANT_1
	mv a0, s8
	la s9, _write_str
	jalr 0(s9)
	li s10, -4
	add s10, fp, s10
	flw ft3, 0(s10)
	fsd ft3, 0(sp)
	addi sp, sp, -8
	la s11, _start_floor
	jalr 0(s11)
	addi sp, sp, 8
	mv t0, a0
	mv a0, t0
	la t1, _write_int
	jalr 0(t1)
	la t2, _CONSTANT_2
	mv a0, t2
	la t3, _write_str
	jalr 0(t3)
	li t4, -4
	add t4, fp, t4
	flw ft4, 0(t4)
	fsd ft4, 0(sp)
	addi sp, sp, -8
	la t5, _start_ceil
	jalr 0(t5)
	addi sp, sp, 8
	mv t6, a0
	li s2, -4
	add s2, fp, s2
	flw ft5, 0(s2)
	fsd ft5, 0(sp)
	addi sp, sp, -8
	la s3, _start_floor
	jalr 0(s3)
	addi sp, sp, 8
	mv s4, a0
	add s5, t6, s4
	la s6, _CONSTANT_3
	flw ft6, 0(s6)
	fcvt.s.w ft0, s5
	fdiv.s ft7, s5, ft6
	li s7, -8
	add s7, fp, s7
	fsw ft7, 0(s7)
	li s8, -8
	add s8, fp, s8
	flw ft1, 0(s8)
	fmv.s fa0, ft1
	la s9, _write_float
	jalr 0(s9)
	la s10, _CONSTANT_4
	mv a0, s10
	la s11, _write_str
	jalr 0(s11)
	li t0, 0
	mv a0, t0
	la t1, _end_MAIN
	jr t1
_end_MAIN:
	ld t0, 8(sp)
	ld t1, 16(sp)
	ld t2, 24(sp)
	ld t3, 32(sp)
	ld t4, 40(sp)
	ld t5, 48(sp)
	ld t6, 56(sp)
	ld s2, 64(sp)
	ld s3, 72(sp)
	ld s4, 80(sp)
	ld s5, 88(sp)
	ld s6, 96(sp)
	ld s7, 104(sp)
	ld s8, 112(sp)
	ld s9, 120(sp)
	ld s10, 128(sp)
	ld s11, 136(sp)
	flw ft0, 144(sp)
	flw ft1, 148(sp)
	flw ft2, 152(sp)
	flw ft3, 156(sp)
	flw ft4, 160(sp)
	flw ft5, 164(sp)
	flw ft6, 168(sp)
	flw ft7, 172(sp)
	ld ra, 8(fp)
	addi sp, fp, 8
	ld fp, 0(fp)
	jr ra
	.data
_frameSize_MAIN:	.word	184
_CONSTANT_0: .string "Enter number :"
_CONSTANT_1: .string "\n"
_CONSTANT_2: .string "\n"
_CONSTANT_3: .word 1073741824
_CONSTANT_4: .string "\n"
