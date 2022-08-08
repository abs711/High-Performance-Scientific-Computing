#!/bin/bash -f

make test.exe

./test.exe opt
./test.exe par
./test.exe block
./test.exe dgemm
