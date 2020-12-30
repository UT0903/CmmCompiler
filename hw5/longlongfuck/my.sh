#!/bin/bash
riscv64-unknown-linux-gnu-gcc -O0 -static main.S
qemu-riscv64 a.out > temp.output
diff temp.output ../testdata/long-long-jump.output
rm temp.output