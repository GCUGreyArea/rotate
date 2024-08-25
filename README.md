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

```bash
        ./build/rotate [-i | --in-file] <infile.bin> [-o | --out-file] <outfile.bin> [-r | --rotate] [left | right]
        Take the content of infile.bin and rotate bits in '--rotate' direction, writing the output to outfile.bin

        ./build/rotate -s <HEX STRING> [-r | -rotate] [left | right]
        Take the HEX_STRING supplied as --string and rotate the bit values in the direction indicated by --rotate, then write the hex values to the console

Note:   If no value for '--rotate' is supplied, left is assumed
        If the file specified by '--in-file' cannot be read, the program will terminate
```

## Design rational

The class hierarchy is designed with Test Driven Development (TDD) in mind. The base class `Base` (unimaginatively named) implement the bit rotation logic, and the derived classes `HexString` and `ArrayBuffer` use those services by implementing the virtual methods to access the underlying functionality.

All classes have been designed to wipe memory clean after use.

- [Class hierarch](https://gcugreyarea.github.io/rotate/html/inherits.html)
- [Classes](https://gcugreyarea.github.io/rotate/html/annotated.html)

## Code documentation

[Code docs](https://gcugreyarea.github.io/rotate/html/) are created through [Doxygen](https://www.doxygen.nl/). This generates `HTML` content that can be hosted in a `GitHub` repository. Click the link to view the documentation for this project.

The `HTML` generated in the `doc` folder by `doxygen` under `doc/output/html` is moved into the `docs` folder so that they can be hosted on the [git repo](https://github.com/GCUGreyArea/rotate/html/). This is the configured folder use to host the `HTML` content for this repo.

## Research links / externally sourced code segments

1. [split string](https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c)

## Issues

1. There is an issue displaying source files from the code documentation when hosted on `github`

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
