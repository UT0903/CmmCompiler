#!/bin/bash
for filename in ./testdata/*.c; do
    echo $filename
    cat ./link.cpp > temp.cpp
    cat $filename >> temp.cpp
    g++ temp.cpp
    ./a.out > ${filename/".c"/".output"} < input.txt
done
for filename in ./pattern_hw6/*.c; do
    echo $filename
    cat ./link.cpp > temp.cpp
    cat $filename >> temp.cpp
    g++ temp.cpp
    ./a.out > ${filename/".c"/".output"} < input.txt
done
for filename in ./testcase_hw6/*.c; do
    echo $filename
    cat ./link.cpp > temp.cpp
    cat $filename >> temp.cpp
    g++ temp.cpp
    ./a.out > ${filename/".c"/".output"} < input.txt
done
rm a.out temp.cpp