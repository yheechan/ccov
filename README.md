# ccov

This repository demonstrates an implementation of [LLVM Pass](https://github.com/yheechan/ccov/blob/master/hw4-llvm/ccov/ccov-pass.cpp) that instruments target C/C++ source code in order to measure the coverage in [LLVM IR](https://llvm.org/docs/LangRef.html) (Intermediate Representation) level. It utilizes a [runtime module](https://github.com/yheechan/ccov/blob/master/hw4-llvm/ccov/ccov-rt.c) during coverage measurement.

## Prerequisites
1. Clang/LLVM, developed on version 13.0.1, not tested on other versions.
```
$ wget https://apt.llvm.org/llvm.sh
$ chmod +x llvm.sh
$ sudo ./llvm.sh <version number> all
```

## Reproducing Project (target subject: test/grep/grep.c)
This repository selects [grep](https://github.com/yheechan/ccov/tree/master/hw4-llvm/test/grep) as the target subject to measure coverage. To reproduce testing on grep, execute the following commands.
```
$ make ccov_grep
$ cd test/grep/
$ test1.sh
$ test2.sh
$ test3.sh
```
Each test script has its own unique command of executing **grep** executable file. At each execution, the coverage results are updated on [Coverage.dat](https://github.com/yheechan/ccov/blob/master/hw4-llvm/test/grep/Coverage.dat).

## Reproducing Project (target subject: test/example.c)
Following build command produces an executable which is built from an instrumented example.c. Executing **example-ccov** produces a [Coverage.dat](https://github.com/yheechan/ccov/blob/master/hw4-llvm/test/Coverage.dat) file which shows the results of coverage.
```
$ make ccov_test
$ cd test/
$ ./example-ccov
```

## Comparison
ccov can be compared against [kcov](https://github.com/yheechan/kcov), which measures coverage at source-code level instead of LLVM IR level.
