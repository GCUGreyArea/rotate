TARGET = rotate

PWD 	   = $(shell pwd)
BUILD	   = build
TESTDIR    = test
LIBDIR     = lib
DOXYDIR	   = doc

TESTTARGET = $(TESTDIR)/$(BUILD)/test_$(TARGET)
LIBTARGET  = $(LIBDIR)/$(BUILD)/lib$(TARGET).so
DOCTARGET  = $(DOXYDIR)/generated

SOURCEDIR = src

SRC = $(wildcard $(SOURCEDIR)/*.c)
SRC += $(wildcard $(SOURCEDIR)/*.cpp)

OBJ := $(patsubst %.cpp,$(BUILD)/%.o,$(SRC))

UNAME := $(shell uname)

INC = -I$(PWD)/$(LIBDIR)/src -I$(PWD)/$(LIBDIR)

LNK = -L$(PWD)/$(LIBDIR)/build \
	  -Wl,-rpath,$(PWD)/$(LIBDIR)/build
    
LIBRARIES = -lbenchmark -lbenchmark_main -lgtest
CFLAGS   = -std=c11 -Wall -g -I $(INC)
CXXFLAGS = -std=c++17 -Wall -g $(INC)

CC = gcc
CXX = g++

export CXXFLAGS
export CFLAGS
export LNK
export LIBRARIES
export CC
export GXX

ARGS =

all: $(LIBTARGET) $(TARGET)

$(TARGET) : build $(LIBTARGET) $(OBJ)
	cd lib && make
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BUILD)/$(TARGET) $(LNK) -l$(TARGET)

build :
	mkdir -p "$(BUILD)/src"


$(LIBTARGET) :  
	cd lib && make 

$(TESTTARGET) : $(LIBTARGET)
	cd $(TESTDIR) && make

$(DOCTARGET) :
	cd $(DOXYDIR) && make

$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

clean:
	cd $(DOXYDIR) && make clean
	cd $(TESTDIR) && make clean
	cd $(LIBDIR) && make clean
	rm -rf $(BUILD)

valgrind: $(TARGET)
	valgrind --leak-check=full ./build/$(TARGET) -s 0xAA,0xAA,0xAA,0xAA
	valgrind --leak-check=full ./build/$(TARGET) ./test/resources/output.bin left ./test/resources/out.bin

docs: $(DOCTARGET)
	rm -rf docs
	cd $(DOXYDIR) && doxygen Doxyfile

test: $(TESTTARGET)
	cd $(LIBDIR) && make
	cd $(TESTDIR) && make
	./$(TESTTARGET)

project:
	cd $(LIBDIR) && make
	cd $(TESTDIR) && make
	cd $(BENCHDIR) && make
	make
	./$(TESTTARGET)

docker:
	docker build . -t rotate
	docker run -ti rotate

check:
	cppcheck src 
	cppcheck lib/src
	cppcheck test/src

help:
	@echo "\n\n"
	@echo "============================================================================================="
	@echo "Run: 'make' to build the project"
	@echo "Run: 'make test' to build unit tests"
	@echo "Run: 'make docs' to build doxygen documentation"
	@echo "Run  'make check' to run cppcheck against code base"
	@echo "Run: 'make valgrind' to run the program with valgrind against various tests"
	@echo "This project depends on:"
	@echo "\tGoogles test framework availible at https://github.com/google/googletest"
	@echo "============================================================================================="
	@echo "\n\n"

