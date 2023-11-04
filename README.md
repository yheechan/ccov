# ccov

## About
This repository demonstrates an implementation of [LLVM Pass](https://github.com/yheechan/ccov/blob/master/hw4-llvm/ccov/ccov-pass.cpp) that instruments target C/C++ source code in order to measure the coverage in [LLVM IR](https://llvm.org/docs/LangRef.html) (Intermediate Representation) level. It utilizes a [runtime module](https://github.com/yheechan/ccov/blob/master/hw4-llvm/ccov/ccov-rt.c) during coverage measurement.

## Reproducing Project (target project: test/grep/grep.c)
This repository selects [grep](https://github.com/yheechan/ccov/tree/master/hw4-llvm/test/grep) as the target subject to measure coverage. To reproduce testing on grep, execute the following commands.
```
$ make ccov_grep
$ cd test/grep/
$ test1.sh
$ test2.sh
$ test3.sh
```
Each test script has its own unique command of executing ***grep*** executable file. At each execution, the coverage results are updated on [Coverage.dat](https://github.com/yheechan/ccov/blob/master/hw4-llvm/test/grep/Coverage.dat).

## Reproducing Project (target project: test/example.c)
```
$ make ccov_test
$ cd test/
$ ./example-ccov
```
