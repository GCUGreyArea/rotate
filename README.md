# Rotate

![image](resources/hexegic.png)

Bitwise rotate the content of a file

## Dependancies

The test code uses the [Google Test](https://github.com/google/googletest) framework which requires `cmake` and `g++` to build.
You can install these by running `sudo apt install -y build-essential cmake git make`.
If you want to build `GTest` (or pull this repository) you will also need `git`.

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

If you would prefer not to polute the environment on you're machine, there is a docker build that can be built and executed by running 

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

## Help

```bash
        ./build/rotate [-i | --in-file] <infile.bin> [-o | --out-file] <outfile.bin> [-r | --rotate] [left | right]
        Take the content of infile.bin and rotate bits in '--rotate' direction, writing the output to outfile.bin

        ./build/rotate -s <HEX STRING> [-r | -rotate] [left | right]
        Take the HEX_STRING supplied as --string and rotate the bit values in the direction indicated by --rotate, then write the hex values to the console

Note:   If no value for for '--rotate' is supplied, left is assumed
        If the file specified by '--in-file' cannot be read, the program will terminate
```

## Design rational

The class hierachy is designed with Test Driven Development (TDD) in mide. The base class `Base` (unimaginatively named) implement the bit rotation logic, and the derived classes `HexString` and `ArrayBuffer` use those services by implementing the virtual methods to access the inderlying functionality.

All classes have been designed to whipe memory clean after use.

## Reseaerch lilnks / externaly sourced code segments

1. [split string](https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c)

## TODO

1. Fix the build system for dependancies and clean it up
2. Either remove docs folder or add code documentation

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

is the most signif‐
icant bit of the βirst byte of the input βile, and bN is the least signiβicant bit of the last byte of the input βile:

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

Please feel free to brows other projects on my GitHub account..

- [regex parse](https://github.com/GCUGreyArea/regex-parser)
- [python parser](https://github.com/GCUGreyArea/python-parser)
- [AlertLogic code chalange](https://github.com/GCUGreyArea/AlertLogic)
- [simple scanner](https://github.com/GCUGreyArea/simple-scanner)
- [ring buffer](https://github.com/GCUGreyArea/ring_buffer)
- [KV Creator](https://github.com/GCUGreyArea/kv_creator)