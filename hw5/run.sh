#!/bin/bash
make
./parser $1
riscv64-unknown-linux-gnu-gcc -O0 -static main.S
qemu-riscv64 a.out
