#!/bin/bash
for filename in ./testdata/*.c; do
    echo $filename
    cp $filename test.c
    ./run.sh ./parser test.c
    make test > tmp.txt
    diff ${filename/".c"/".output"} tmp.txt