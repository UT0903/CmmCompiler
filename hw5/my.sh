#!/bin/bash
make
input=$1
./parser $input
riscv64-unknown-linux-gnu-gcc -O0 -static main.S
qemu-riscv64 a.out > temp.output
diff temp.output ${input/".c"/".output"}
rm temp.output
