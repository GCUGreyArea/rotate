# Rotate

![image](resources/hexegic.png)

Bitwise rotate the content of a file. This code has been built and validated on `WSL2` `Ubuntu 22.04` and `Docker` `Ubuntu 22.04`.

## Dependancies

The test code uses the [Google Test](https://github.com/google/googletest) framework, which requires `cmake` and `g++` to build.
You can install these and other requirements by running `sudo apt install -y build-essential cmake git make doxygen cppcheck`.

```bash
git clone https://github.com/GCUGreyArea/rotate.git
```

If you want to build `GTest` you will need to run the following commands

```bash
git clone https://github.com/google/googletest.git
cd googletest
mkdir -p build 
cd build 
cmake .. 
cmake --build . 
sudo cmake --install . 
```

## Building the project

If you would prefer not to pollute the environment on your machine, there is a docker build that can be built and executed by running 

```bash
make docker
``` 

Otherwise, just run

```bash
make project  
OR
make
``` 

In order to set up the path for the program (rather than runing it from the local directory), you can run 

```bash
source settings.sh
OR 
. ./settings.sh
```

## Set up Docker

- [Setup docker on WSL2](https://docs.docker.com/desktop/wsl/)
- [setup docker on Ubuntu](https://docs.docker.com/engine/install/ubuntu/)

## Help

```
Help
        ./build/rotate [-i | --in-file] <IN_FILE_NAME> [-o | --out-file] <OUT_FILE_NAME> [-r | --rotate] [left | right]
        Take the content of IN_FILE_NAME and rotate bits in '--rotate' direction, writing the output to OUT_FILE_NAME

        ./build/rotate -s <HEX STRING> [-r | -rotate] [left | right]
        Take the HEX_STRING supplied as --string and rotate the bit values in the direction indicated by --rotate, then write the hex values to the console

        ./build/rotate -m <OUT_FILE_NAME> -s <HEX_STRING>
        Take the HEX_STRING supplied by --string and write it as bytes to the OUT_FILE_NAME supplied by --make

        ./build/rotate -d <IN_FILE_NAME>
        Dump the hexidecimal values from IN_FILE_NAME to the terminal

Note:   If no value for '--rotate' is supplied for a rotate function, left is assumed
        If the file specified by '--in-file' or `--dump` cannot be read, the program will terminate
```

## Building and running unit tests

The unit tests use the Google Test framework, which needs to be installed for the tests to build. The project has been built arround the [latest release](https://github.com/google/googletest) so it is preferable that `gtest` is built from source, rathert than installed through `apt`. Please see [dependacies](#Dependancies) for build instructions.

Tp run the unit tests, first run `source settings.sh` then run `test_rotate`

## Design rational

The class hierarchy is designed with Test Driven Development (TDD) in mind. The base class `Base` (unimaginatively named) implement the bit rotation logic, and the derived classes `HexString` and `ArrayBuffer` use those services by implementing the virtual methods to access the underlying functionality.

All classes have been designed to wipe memory clean after use.

- [Class hierarch](https://gcugreyarea.github.io/rotate/html/inherits.html)
- [Classes](https://gcugreyarea.github.io/rotate/html/annotated.html)

## Code documentation

[Code docs](https://gcugreyarea.github.io/rotate/html/) are created through [Doxygen](https://www.doxygen.nl/). This generates `HTML` content that can be hosted in a `GitHub` repository. Click the link to view the documentation for this project.

The `HTML` generated in the `doc` folder by `doxygen` under `doc/output/html` is moved into the `docs` folder so that they can be hosted on the [git repo](https://github.com/GCUGreyArea/rotate/html/). This is the configured folder use to host the `HTML` content for this repo.

## Research links / test / externally sourced code segments

1. [split string](https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c)
2. [Regex 101](https://regex101.com/)

## Issues

1. There is an issue displaying source files from the code documentation when hosted on `github`
2. While `valgrind --leak-check=full ./build/rotate ./test/resources/output.bin left ./test/resources/out.bin` works and creates output, `make valgrind` fails to create output in the test directory.


## Valgrind output 

```bash
valgrind --verbose -s --leak-check=full ./build/rotate ./test/resources/output.bin left ./test/resources/out.bin
==385762== Memcheck, a memory error detector
==385762== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==385762== Using Valgrind-3.15.0-608cb11914-20190413 and LibVEX; rerun with -h for copyright info
==385762== Command: ./build/rotate ./test/resources/output.bin left ./test/resources/out.bin
==385762== 
--385762-- Valgrind options:
--385762--    --verbose
--385762--    -s
--385762--    --leak-check=full
--385762-- Contents of /proc/version:
--385762--   Linux version 5.15.153.1-microsoft-standard-WSL2 (root@941d701f84f1) (gcc (GCC) 11.2.0, GNU ld (GNU Binutils) 2.37) #1 SMP Fri Mar 29 23:14:13 UTC 2024
--385762-- 
--385762-- Arch and hwcaps: AMD64, LittleEndian, amd64-cx16-lzcnt-rdtscp-sse3-ssse3-avx-avx2-bmi-f16c-rdrand
--385762-- Page sizes: currently 4096, max supported 4096
--385762-- Valgrind library directory: /usr/lib/x86_64-linux-gnu/valgrind
--385762-- Reading syms from /home/barry/workspace/rotate/build/rotate
--385762-- Reading syms from /usr/lib/x86_64-linux-gnu/ld-2.31.so
--385762--   Considering /usr/lib/debug/.build-id/db/0420f708b806cf03260aadb916c330049580b7.debug ..
--385762--   .. build-id is valid
--385762-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/memcheck-amd64-linux
--385762--    object doesn't have a symbol table
--385762--    object doesn't have a dynamic symbol table
--385762-- Scheduler: using generic scheduler lock implementation.
--385762-- Reading suppressions file: /usr/lib/x86_64-linux-gnu/valgrind/default.supp
==385762== embedded gdbserver: reading from /tmp/vgdb-pipe-from-vgdb-to-385762-by-barry-on-???
==385762== embedded gdbserver: writing to   /tmp/vgdb-pipe-to-vgdb-from-385762-by-barry-on-???
==385762== embedded gdbserver: shared mem   /tmp/vgdb-pipe-shared-mem-vgdb-385762-by-barry-on-???
==385762== 
==385762== TO CONTROL THIS PROCESS USING vgdb (which you probably
==385762== don't want to do, unless you know exactly what you're doing,
==385762== or are doing some strange experiment):
==385762==   /usr/lib/x86_64-linux-gnu/valgrind/../../bin/vgdb --pid=385762 ...command...
==385762== 
==385762== TO DEBUG THIS PROCESS USING GDB: start GDB like this
==385762==   /path/to/gdb ./build/rotate
==385762== and then give GDB the following command
==385762==   target remote | /usr/lib/x86_64-linux-gnu/valgrind/../../bin/vgdb --pid=385762
==385762== --pid is optional if only one valgrind process is running
==385762== 
--385762-- REDIR: 0x4022e20 (ld-linux-x86-64.so.2:strlen) redirected to 0x580c9ce2 (???)
--385762-- REDIR: 0x4022bf0 (ld-linux-x86-64.so.2:index) redirected to 0x580c9cfc (???)
--385762-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_core-amd64-linux.so
--385762--    object doesn't have a symbol table
--385762-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so
--385762--    object doesn't have a symbol table
==385762== WARNING: new redirection conflicts with existing -- ignoring it
--385762--     old: 0x04022e20 (strlen              ) R-> (0000.0) 0x580c9ce2 ???
--385762--     new: 0x04022e20 (strlen              ) R-> (2007.0) 0x0483f060 strlen
--385762-- REDIR: 0x401f600 (ld-linux-x86-64.so.2:strcmp) redirected to 0x483ffd0 (strcmp)
--385762-- REDIR: 0x4023380 (ld-linux-x86-64.so.2:mempcpy) redirected to 0x4843a20 (mempcpy)
--385762-- Reading syms from /home/barry/workspace/rotate/lib/build/librotate.so
--385762-- Reading syms from /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
--385762--    object doesn't have a symbol table
--385762-- Reading syms from /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
--385762--    object doesn't have a symbol table
--385762-- Reading syms from /usr/lib/x86_64-linux-gnu/libc-2.31.so
--385762--   Considering /usr/lib/debug/.build-id/07/02430aef5fa3dda43986563e9ffcc47efbd75e.debug ..
--385762--   .. build-id is valid
--385762-- Reading syms from /usr/lib/x86_64-linux-gnu/libm-2.31.so
--385762--   Considering /usr/lib/debug/.build-id/8d/2573eff281739f0e2b0eb710c860ce0b7261cf.debug ..
--385762--   .. build-id is valid
--385762-- REDIR: 0x4bd7480 (libc.so.6:memmove) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6780 (libc.so.6:strncpy) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd77b0 (libc.so.6:strcasecmp) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd60a0 (libc.so.6:strcat) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd67e0 (libc.so.6:rindex) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd8c50 (libc.so.6:rawmemchr) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bf3ce0 (libc.so.6:wmemchr) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bf3820 (libc.so.6:wcscmp) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd75e0 (libc.so.6:mempcpy) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd7410 (libc.so.6:bcmp) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6710 (libc.so.6:strncmp) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6150 (libc.so.6:strcmp) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd7540 (libc.so.6:memset) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bf37e0 (libc.so.6:wcschr) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6670 (libc.so.6:strnlen) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6230 (libc.so.6:strcspn) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd7800 (libc.so.6:strncasecmp) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd61d0 (libc.so.6:strcpy) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd7950 (libc.so.6:memcpy@@GLIBC_2.14) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bf4f50 (libc.so.6:wcsnlen) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bf3860 (libc.so.6:wcscpy) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6820 (libc.so.6:strpbrk) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6100 (libc.so.6:index) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6630 (libc.so.6:strlen) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bdfbb0 (libc.so.6:memrchr) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd7850 (libc.so.6:strcasecmp_l) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd73d0 (libc.so.6:memchr) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bf3930 (libc.so.6:wcslen) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd6ae0 (libc.so.6:strspn) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd7750 (libc.so.6:stpncpy) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd76f0 (libc.so.6:stpcpy) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd8c90 (libc.so.6:strchrnul) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4bd78a0 (libc.so.6:strncasecmp_l) redirected to 0x48331d0 (_vgnU_ifunc_wrapper)
--385762-- REDIR: 0x4cbf730 (libc.so.6:__strrchr_avx2) redirected to 0x483ea10 (rindex)
--385762-- REDIR: 0x4bd10e0 (libc.so.6:malloc) redirected to 0x483b780 (malloc)
--385762-- REDIR: 0x4cbf900 (libc.so.6:__strlen_avx2) redirected to 0x483ef40 (strlen)
--385762-- REDIR: 0x4cbbef0 (libc.so.6:__memcmp_avx2_movbe) redirected to 0x48421e0 (bcmp)
--385762-- REDIR: 0x4cbadf0 (libc.so.6:__strcmp_avx2) redirected to 0x483fed0 (strcmp)
--385762-- REDIR: 0x49e4b10 (libstdc++.so.6:operator new(unsigned long)) redirected to 0x483bdf0 (operator new(unsigned long))
--385762-- REDIR: 0x4cc2910 (libc.so.6:__memcpy_avx_unaligned_erms) redirected to 0x48429f0 (memmove)
--385762-- REDIR: 0x4cc2d90 (libc.so.6:__memset_avx2_unaligned_erms) redirected to 0x48428e0 (memset)
--385762-- REDIR: 0x49e2d60 (libstdc++.so.6:operator delete(void*)) redirected to 0x483cf50 (operator delete(void*))
--385762-- REDIR: 0x49e2d70 (libstdc++.so.6:operator delete(void*, unsigned long)) redirected to 0x483d160 (operator delete(void*, unsigned long))
--385762-- REDIR: 0x4cbb760 (libc.so.6:__memchr_avx2) redirected to 0x4840050 (memchr)
--385762-- REDIR: 0x4bd6fa0 (libc.so.6:__GI_strstr) redirected to 0x4843ca0 (__strstr_sse2)
--385762-- REDIR: 0x49e4b70 (libstdc++.so.6:operator new[](unsigned long)) redirected to 0x483c510 (operator new[](unsigned long))
--385762-- REDIR: 0x49e2d90 (libstdc++.so.6:operator delete[](void*)) redirected to 0x483d6e0 (operator delete[](void*))
--385762-- REDIR: 0x4bd16d0 (libc.so.6:free) redirected to 0x483c9d0 (free)
==385762== 
==385762== HEAP SUMMARY:
==385762==     in use at exit: 0 bytes in 0 blocks
==385762==   total heap usage: 21 allocs, 21 frees, 92,284 bytes allocated
==385762== 
==385762== All heap blocks were freed -- no leaks are possible
==385762== 
==385762== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TODO

1. Fix the build system for dependencies and clean it up.
2. Either remove docs folder or add code documentation, and find a fix for the file issue.

## Brief

Please write a command‐line program rotate that takes three arguments:

- the word left or right
- an input βilename
- an output βilename
to be run as e.g. rotate left in‐file out‐file or rotate right in‐file out‐file.
The program should write an output βile that contains the contents of the input βile rotated either one bit left, or
one bit right, depending on the βirst argument.
To clarify “rotated one bit”, if the input βile’s contents are a stream of bits b0

b1 ... bMbN, where b0

is the most significant bit of the βirst byte of the input βile, and bN is the least signiβicant bit of the last byte of the input βile:

- Rotated one bit left means that the output βile is b1 ... bMbNb0
- Rotated one bit right means that the output βile is bNb0
b1 ... bM.

Notes:

- Programming language: Rust, Go, C or C++, at your preference.
- Platform: Linux or Windows at your preference.
- Your implementation should embody your understanding of production‐quality, security‐critical code.
- Please don’t spend more than an hour or two on it.
- The above description is intended to be unambiguous and not be any sort of trick question: if you’re at all unclear about what we’re asking you to do then please ask.
- Although the role requires Rust and Go on Linux, please don’t let that bias your selection of language or platform, unless you’re conβident in your knowledge of those languages and/or platform.

## Other projects

Please feel free to browse other projects on my GitHub account.

- [regex parser](https://github.com/GCUGreyArea/regex-parser): A simple log parsing engine based on the Google's [RE2](https://github.com/google/re2) regex engine and [Hyperscan](https://github.com/intel/hyperscan), a fast `C` based regex engine.
- [python parser](https://github.com/GCUGreyArea/python-parser): A simple python message parsing framework using `Python`, with a [mongDB](https://www.mongodb.com/) backend storage, with `Docker` and `Docker compse` for auchestration, and [Flask](https://flask.palletsprojects.com/en/3.0.x/) to provide a `JSON` `REST` API.
- [AlertLogic code chalange](https://github.com/GCUGreyArea/AlertLogic): A basic work letter frequency scanner written in `C` as a code challenge for a position at `AlertLogic`
- [simple scanner](https://github.com/GCUGreyArea/simple-scanner): A very simple scanner to parse bespoke message formats.
- [ring buffer](https://github.com/GCUGreyArea/ring_buffer): A `ring buffer` implementation for lockless data transfer.
- [KV Creator](https://github.com/GCUGreyArea/kv_creator): Create basic `KV` tokens.
