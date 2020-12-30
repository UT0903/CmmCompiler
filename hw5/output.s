	.data
_g_a: .word 0
_g_b: .word 0
_g_c: .word 0
_g_d: .word 0
_g_e: .word 0
_g_f: .word 0
	.text
_start_A:
	sd ra, 0(sp)
	sd fp, -8(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_A
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
	la t0, _g_a
	lw t1, 0(t0)
	mv a0, t1
	j _end_A
_end_A:
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
_frameSize_A:	.word	176
	.text
_start_B:
	sd ra, 0(sp)
	sd fp, -8(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_B
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
	la t2, _g_b
	lw t3, 0(t2)
	mv a0, t3
	j _end_B
_end_B:
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
_frameSize_B:	.word	176
	.text
_start_C:
	sd ra, 0(sp)
	sd fp, -8(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_C
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
	la t4, _g_c
	lw t5, 0(t4)
	mv a0, t5
	j _end_C
_end_C:
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
_frameSize_C:	.word	176
	.text
_start_D:
	sd ra, 0(sp)
	sd fp, -8(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_D
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
	la t6, _g_d
	lw s2, 0(t6)
	mv a0, s2
	j _end_D
_end_D:
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
_frameSize_D:	.word	176
	.text
_start_E:
	sd ra, 0(sp)
	sd fp, -8(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_E
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
	la s3, _g_e
	lw s4, 0(s3)
	mv a0, s4
	j _end_E
_end_E:
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
_frameSize_E:	.word	176
	.text
_start_F:
	sd ra, 0(sp)
	sd fp, -8(sp)
	addi fp, sp, -8
	addi sp, sp, -16
	la ra, _frameSize_F
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
	la s5, _g_f
	lw s6, 0(s5)
	mv a0, s6
	j _end_F
_end_F:
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
_frameSize_F:	.word	176
	.text
_start_MAIN:
	sd ra, 0(sp)
	sd fp, -8(sp)
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
	li s7, 4
	la s8, _g_a
	sw s7, 0(s8)
	li s9, 3
	la s10, _g_b
	sw s9, 0(s10)
	li s11, 2
	la t0, _g_c
	sw s11, 0(t0)
	li t1, 1
	la t2, _g_d
	sw t1, 0(t2)
	li t3, 5
	la t4, _g_e
	sw t3, 0(t4)
	li t5, 6
	la t6, _g_f
	sw t5, 0(t6)
	la s2, _g_a
	lw s3, 0(s2)
	la s4, _g_b
	lw s5, 0(s4)
	add s6, s3, s5
	la s7, _g_c
	lw s8, 0(s7)
	add s9, s6, s8
	la s10, _g_d
	lw s11, 0(s10)
	add t0, s9, s11
	la t1, _g_e
	lw t2, 0(t1)
	add t3, t0, t2
	la t4, _g_f
	lw t5, 0(t4)
	add t6, t3, t5
	mv a0, t6
	jal _write_int
	la s2, _CONSTANT_0
	mv a0, s2
	jal _write_str
	la s3, _g_a
	lw s4, 0(s3)
	la s5, _g_b
	lw s6, 0(s5)
	la s7, _g_c
	lw s8, 0(s7)
	add s9, s6, s8
	mul s10, s4, s9
	la s11, _g_d
	lw t0, 0(s11)
	la t1, _g_e
	lw t2, 0(t1)
	mul t3, t0, t2
	la t4, _g_f
	lw t5, 0(t4)
	div t6, t3, t5
	la s2, _g_f
	lw s3, 0(s2)
	mul s4, t6, s3
	add s5, s10, s4
	li s6, 123
	add s7, s5, s6
	mv a0, s7
	jal _write_int
	la s8, _CONSTANT_1
	mv a0, s8
	jal _write_str
	la s9, _g_a
	lw s10, 0(s9)
	la s11, _g_b
	lw t0, 0(s11)
	la t1, _g_c
	lw t2, 0(t1)
	add t3, t0, t2
	and t4, s10, t3
	la t5, _g_d
	lw t6, 0(t5)
	la s2, _g_e
	lw s3, 0(s2)
	add s4, t6, s3
	and s5, t4, s4
	la s6, _g_f
	lw s7, 0(s6)
	or s8, s5, s7
	mv a0, s8
	jal _write_int
	la s9, _CONSTANT_2
	mv a0, s9
	jal _write_str
	la s10, _g_b
	lw s11, 0(s10)
	la t0, _g_b
	lw t1, 0(t0)
	div t2, s11, t1
	la t3, _g_a
	lw t4, 0(t3)
	mul t5, t2, t4
	mv a0, t5
	jal _write_int
	la t6, _CONSTANT_3
	mv a0, t6
	jal _write_str
	la s2, _g_a
	lw s3, 0(s2)
	la s4, _g_b
	lw s5, 0(s4)
	div s6, s3, s5
	la s7, _g_c
	lw s8, 0(s7)
	div s9, s6, s8
	la s10, _g_d
	lw s11, 0(s10)
	div t0, s9, s11
	la t1, _g_e
	lw t2, 0(t1)
	div t3, t0, t2
	la t4, _g_f
	lw t5, 0(t4)
	div t6, t3, t5
	mv a0, t6
	jal _write_int
	la s2, _CONSTANT_4
	mv a0, s2
	jal _write_str
	la s3, _g_a
	lw s4, 0(s3)
	la s5, _g_b
	lw s6, 0(s5)
	and s7, s4, s6
	la s8, _g_c
	lw s9, 0(s8)
	la s10, _g_a
	lw s11, 0(s10)
	la t0, _g_d
	lw t1, 0(t0)
	la t2, _g_e
	lw t3, 0(t2)
	add t4, t1, t3
	la t5, _g_f
	lw t6, 0(t5)
	add s2, t4, t6
	mul s3, s11, s2
	li s4, 5
	div s5, s3, s4
	add s6, s9, s5
	or s7, s7, s6
	mv a0, s7
	jal _write_int
	la s8, _CONSTANT_5
	mv a0, s8
	jal _write_str
	jal _start_A
	mv s9, a0
	jal _start_B
	mv s10, a0
	add s11, s9, s10
	jal _start_C
	mv t0, a0
	add t1, s11, t0
	jal _start_D
	mv t2, a0
	add t3, t1, t2
	jal _start_E
	mv t4, a0
	add t5, t3, t4
	jal _start_F
	mv t6, a0
	add s2, t5, t6
	mv a0, s2
	jal _write_int
	la s3, _CONSTANT_6
	mv a0, s3
	jal _write_str
	jal _start_A
	mv s4, a0
	jal _start_B
	mv s5, a0
	jal _start_C
	mv s6, a0
	add s7, s5, s6
	mul s8, s4, s7
	jal _start_D
	mv s9, a0
	jal _start_E
	mv s10, a0
	mul s11, s9, s10
	jal _start_F
	mv t0, a0
	div t1, s11, t0
	jal _start_F
	mv t2, a0
	mul t3, t1, t2
	add t4, s8, t3
	li t5, 123
	add t6, t4, t5
	mv a0, t6
	jal _write_int
	la s2, _CONSTANT_7
	mv a0, s2
	jal _write_str
	jal _start_A
	mv s3, a0
	jal _start_B
	mv s4, a0
	jal _start_C
	mv s5, a0
	add s6, s4, s5
	and s7, s3, s6
	jal _start_D
	mv s8, a0
	jal _start_E
	mv s9, a0
	add s10, s8, s9
	and s11, s7, s10
	jal _start_F
	mv t0, a0
	or t1, s11, t0
	mv a0, t1
	jal _write_int
	la t2, _CONSTANT_8
	mv a0, t2
	jal _write_str
	jal _start_B
	mv t3, a0
	jal _start_B
	mv t4, a0
	div t5, t3, t4
	jal _start_A
	mv t6, a0
	mul s2, t5, t6
	mv a0, s2
	jal _write_int
	la s3, _CONSTANT_9
	mv a0, s3
	jal _write_str
	jal _start_A
	mv s4, a0
	jal _start_B
	mv s5, a0
	div s6, s4, s5
	jal _start_C
	mv s7, a0
	div s8, s6, s7
	jal _start_D
	mv s9, a0
	div s10, s8, s9
	jal _start_E
	mv s11, a0
	div t0, s10, s11
	jal _start_F
	mv t1, a0
	div t2, t0, t1
	mv a0, t2
	jal _write_int
	la t3, _CONSTANT_10
	mv a0, t3
	jal _write_str
	jal _start_A
	mv t4, a0
	jal _start_B
	mv t5, a0
	and t6, t4, t5
	jal _start_C
	mv s2, a0
	jal _start_A
	mv s3, a0
	jal _start_D
	mv s4, a0
	jal _start_E
	mv s5, a0
	add s6, s4, s5
	jal _start_F
	mv s7, a0
	add s8, s6, s7
	mul s9, s3, s8
	li s10, 5
	div s11, s9, s10
	add t0, s2, s11
	or t1, t6, t0
	mv a0, t1
	jal _write_int
	la t2, _CONSTANT_11
	mv a0, t2
	jal _write_str
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
_frameSize_MAIN:	.word	176
_CONSTANT_0: .string "\n"
_CONSTANT_1: .string "\n"
_CONSTANT_2: .string "\n"
_CONSTANT_3: .string "\n"
_CONSTANT_4: .string "\n"
_CONSTANT_5: .string "\n"
_CONSTANT_6: .string "\n"
_CONSTANT_7: .string "\n"
_CONSTANT_8: .string "\n"
_CONSTANT_9: .string "\n"
_CONSTANT_10: .string "\n"
_CONSTANT_11: .string "\n"
