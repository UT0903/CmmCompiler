#!/bin/bash
for filename in ./testdata/*.c; do
    echo $filename
    cat ./testdata/link.cpp > temp.cpp
    cat $filename >> temp.cpp
    g++ temp.cpp
    ./a.out > ${filename/".c"/".output"}
done
rm a.out temp.cpp