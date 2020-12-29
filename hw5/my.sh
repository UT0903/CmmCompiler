#!/bin/bash
$1 $2
riscv64-unknown-linux-gnu-gcc -O0 -static main.S
qemu-riscv64 a.out 