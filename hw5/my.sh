#!/bin/bash
make
for filename in ./pattern/*.c; do
    echo $filename
    ./parser $filename
    riscv64-unknown-linux-gnu-gcc -O0 -static main.S
    qemu-riscv64 a.out > temp.output
    diff temp.output ${filename/".c"/".output"}
done
rm temp.output
