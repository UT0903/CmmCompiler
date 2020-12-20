QEMU := /home/ntu/.local/riscv/bin/qemu-riscv64
CC   := /home/ntu/.local/riscv/bin/riscv64-unknown-linux-gnu-gcc
OBJDUMP := /home/ntu/.local/riscv/bin/riscv64-unknown-linux-gnu-objdump

test-int: main.S ./test/int.S
	@cp ./test/int.S ./output.s
	@printf "  LD\t$@\n"
	@$(CC) -static -o $@ main.S
	@printf "  RUN\t$@ (Type an integer, expected to be echoed back)\n"
	@$(QEMU) $@

test-float: main.S ./test/float.S
	@cp ./test/float.S ./output.s
	@printf "  LD\t$@\n"
	@$(CC) -static -o $@ main.S
	@printf "  RUN\t$@ (Type an floating-point number, expected to be echoed back)\n"
	@$(QEMU) $@

test-string: main.S ./test/string.S
	@cp ./test/string.S ./output.s
	@printf "  LD\t$@\n"
	@$(CC) -static -o $@ main.S
	@$(QEMU) $@

clean:
	@rm -rf output.s test-* *.dump
