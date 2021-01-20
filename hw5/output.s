	.data
_g_dim: .word 4
_g_a: .space 64
_g_b: .space 64
_g_c: .space 64
	.text
_start_print:
	sd fp, -8(sp)
	sd ra, 0(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_print
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
	li t0, 0
	li t1, -4
	add t1, fp, t1
	sw t0, 0(t1)
L0:
	li t2, -4
	add t2, fp, t2
	lw t3, 0(t2)
	la t4, _g_dim
	lw t5, 0(t4)
	slt t6, t3, t5
	beqz t6, L3
	j L2
L1:
	li s2, -4
	add s2, fp, s2
	lw s3, 0(s2)
	li s4, 1
	add s5, s3, s4
	li s6, -4
	add s6, fp, s6
	sw s5, 0(s6)
	j L0
L2:
	li s7, 0
	li s8, -8
	add s8, fp, s8
	sw s7, 0(s8)
L4:
	li s9, -8
	add s9, fp, s9
	lw s10, 0(s9)
	la s11, _g_dim
	lw t0, 0(s11)
	slt t1, s10, t0
	beqz t1, L7
	j L6
L5:
	li t2, -8
	add t2, fp, t2
	lw t3, 0(t2)
	li t4, 1
	add t5, t3, t4
	li s2, -8
	add s2, fp, s2
	sw t5, 0(s2)
	j L4
L6:
	add s4, x0, x0
	li s5, -4
	add s5, fp, s5
	lw s6, 0(s5)
	add s4 s4 s6
	muli s4, s4, 4
	li s7, -8
	add s7, fp, s7
	lw s8, 0(s7)
	add s4 s4 s8
	la s3, _g_c
	slli s4, s4, 2
	add s3, s3, s4
	lw s9, 0(s3)
	mv a0, s9
	la s10, _write_int
	jalr 0(s10)
	la s11, _CONSTANT_0
	mv a0, s11
	la t0, _write_str
	jalr 0(t0)
	j L5
L7:
	la t2, _CONSTANT_1
	mv a0, t2
	la t3, _write_str
	jalr 0(t3)
	j L1
L3:
_end_print:
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
_frameSize_print:	.word	184
	.text
_start_arraymult:
	sd fp, -8(sp)
	sd ra, 0(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_arraymult
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
	li t4, 0
	li t5, -4
	add t5, fp, t5
	sw t4, 0(t5)
L8:
	li s2, -4
	add s2, fp, s2
	lw s3, 0(s2)
	la s4, _g_dim
	lw s5, 0(s4)
	slt s6, s3, s5
	beqz s6, L11
	j L10
L9:
	li s7, -4
	add s7, fp, s7
	lw s8, 0(s7)
	li s9, 1
	add s10, s8, s9
	li s11, -4
	add s11, fp, s11
	sw s10, 0(s11)
	j L8
L10:
	li t0, 0
	li t2, -8
	add t2, fp, t2
	sw t0, 0(t2)
L12:
	li t3, -8
	add t3, fp, t3
	lw t4, 0(t3)
	la t5, _g_dim
	lw s2, 0(t5)
	slt s3, t4, s2
	beqz s3, L15
	j L14
L13:
	li s4, -8
	add s4, fp, s4
	lw s5, 0(s4)
	li s7, 1
	add s8, s5, s7
	li s9, -8
	add s9, fp, s9
	sw s8, 0(s9)
	j L12
L14:
	li s10, 0
	li s11, -16
	add s11, fp, s11
	sw s10, 0(s11)
	li t0, 0
	li t2, -12
	add t2, fp, t2
	sw t0, 0(t2)
L16:
	li t3, -12
	add t3, fp, t3
	lw t4, 0(t3)
	la t5, _g_dim
	lw s2, 0(t5)
	slt s4, t4, s2
	beqz s4, L19
	j L18
L17:
	li s5, -12
	add s5, fp, s5
	lw s7, 0(s5)
	li s8, 1
	add s9, s7, s8
	li s10, -12
	add s10, fp, s10
	sw s9, 0(s10)
	j L16
L18:
	li s11, -16
	add s11, fp, s11
	lw t0, 0(s11)
	add t3, x0, x0
	li t4, -4
	add t4, fp, t4
	lw t5, 0(t4)
	add t3 t3 t5
	muli t3, t3, 4
	li s2, -12
	add s2, fp, s2
	lw s5, 0(s2)
	add t3 t3 s5
	la t2, _g_a
	slli t3, t3, 2
	add t2, t2, t3
	lw s7, 0(t2)
	add s9, x0, x0
	li s10, -12
	add s10, fp, s10
	lw s11, 0(s10)
	add s9 s9 s11
	muli s9, s9, 4
	li t2, -8
	add t2, fp, t2
	lw t3, 0(t2)
	add s9 s9 t3
	la s8, _g_b
	slli s9, s9, 2
	add s8, s8, s9
	lw t4, 0(s8)
	mul t5, s7, t4
	add s2, t0, t5
	li s5, -16
	add s5, fp, s5
	sw s2, 0(s5)
	j L17
L19:
	li s7, -16
	add s7, fp, s7
	lw s8, 0(s7)
	add s10, x0, x0
	li s11, -4
	add s11, fp, s11
	lw t0, 0(s11)
	add s10 s10 t0
	muli s10, s10, 4
	li t2, -8
	add t2, fp, t2
	lw t3, 0(t2)
	add s10 s10 t3
	la s9, _g_c
	slli s10, s10, 2
	add s9, s9, s10
	sw s8, 0(s9)
	j L13
L15:
	j L9
L11:
	la t4, _start_print
	jalr 0(t4)
	addi sp, sp, 0
_end_arraymult:
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
_frameSize_arraymult:	.word	192
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
	la t5, _CONSTANT_2
	mv a0, t5
	la s2, _write_str
	jalr 0(s2)
	li s5, 0
	li s7, -4
	add s7, fp, s7
	sw s5, 0(s7)
L20:
	li s8, -4
	add s8, fp, s8
	lw s9, 0(s8)
	la s10, _g_dim
	lw s11, 0(s10)
	slt t0, s9, s11
	beqz t0, L23
	j L22
L21:
	li t2, -4
	add t2, fp, t2
	lw t3, 0(t2)
	li t4, 1
	add t5, t3, t4
	li s2, -4
	add s2, fp, s2
	sw t5, 0(s2)
	j L20
L22:
	li s5, 0
	li s7, -8
	add s7, fp, s7
	sw s5, 0(s7)
L24:
	li s8, -8
	add s8, fp, s8
	lw s9, 0(s8)
	la s10, _g_dim
	lw s11, 0(s10)
	slt t2, s9, s11
	beqz t2, L27
	j L26
L25:
	li t3, -8
	add t3, fp, t3
	lw t4, 0(t3)
	li t5, 1
	add s2, t4, t5
	li s5, -8
	add s5, fp, s5
	sw s2, 0(s5)
	j L24
L26:
	la s7, _read_int
	jalr 0(s7)
	mv s8, a0
	add s10, x0, x0
	li s11, -4
	add s11, fp, s11
	lw t3, 0(s11)
	add s10 s10 t3
	muli s10, s10, 4
	li t4, -8
	add t4, fp, t4
	lw t5, 0(t4)
	add s10 s10 t5
	la s9, _g_a
	slli s10, s10, 2
	add s9, s9, s10
	sw s8, 0(s9)
	j L25
L27:
	j L21
L23:
	la s2, _CONSTANT_3
	mv a0, s2
	la s5, _write_str
	jalr 0(s5)
	li s7, 0
	li s8, -4
	add s8, fp, s8
	sw s7, 0(s8)
L28:
	li s9, -4
	add s9, fp, s9
	lw s10, 0(s9)
	la s11, _g_dim
	lw t3, 0(s11)
	slt t4, s10, t3
	beqz t4, L31
	j L30
L29:
	li t5, -4
	add t5, fp, t5
	lw s2, 0(t5)
	li s5, 1
	add s7, s2, s5
	li s8, -4
	add s8, fp, s8
	sw s7, 0(s8)
	j L28
L30:
	li s9, 0
	li s10, -8
	add s10, fp, s10
	sw s9, 0(s10)
L32:
	li s11, -8
	add s11, fp, s11
	lw t3, 0(s11)
	la t5, _g_dim
	lw s2, 0(t5)
	slt s5, t3, s2
	beqz s5, L35
	j L34
L33:
	li s7, -8
	add s7, fp, s7
	lw s8, 0(s7)
	li s9, 1
	add s10, s8, s9
	li s11, -8
	add s11, fp, s11
	sw s10, 0(s11)
	j L32
L34:
	la t3, _read_int
	jalr 0(t3)
	mv t5, a0
	add s7, x0, x0
	li s8, -4
	add s8, fp, s8
	lw s9, 0(s8)
	add s7 s7 s9
	muli s7, s7, 4
	li s10, -8
	add s10, fp, s10
	lw s11, 0(s10)
	add s7 s7 s11
	la s2, _g_b
	slli s7, s7, 2
	add s2, s2, s7
	sw t5, 0(s2)
	j L33
L35:
	j L29
L31:
	la t3, _start_arraymult
	jalr 0(t3)
	addi sp, sp, 0
	li t5, 0
	mv a0, t5
	la s2, _end_MAIN
	jr s2
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
_CONSTANT_0: .string " "
_CONSTANT_1: .string "\n"
_CONSTANT_2: .string "Enter matrix 1 of dim 4 x 4 : \n"
_CONSTANT_3: .string "Enter matrix 2 of dim 4 x 4 : \n"
