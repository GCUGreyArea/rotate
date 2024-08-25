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
	valgrind --leak-check=full ./$(TARGET)

docs: $(DOCTARGET)
	cd $(DOXYDIR) && doxygen Doxyfile
	rm -rf docs/output
	cp -r doc/output/html docs

test: $(TESTTARGET)
	cd $(LIBDIR) && make
	cd $(TESTDIR) && make

benchmark: $(BNCTARGET)
	cd $(LIBDIR) && make
	cd $(BENCHDIR) && make

project:
	cd $(LIBDIR) && make
	cd $(TESTDIR) && make
	cd $(BENCHDIR) && make
	make
	./$(TESTTARGET)
	./$(BNCTARGET)

docker:
	make clean 
	docker build . -t rotate
	docker run -ti rotate

help:
	@echo "\n\n"
	@echo "============================================================================================="
	@echo "Run: 'make' to build the project"
	@echo "Run: 'make test' to build unit tests"
	@echo "Run: 'make doxygen' to build doxygen documentation"
	@echo "This project depends on:"
	@echo "\tGoogles test framework availible at https://github.com/google/googletest"
	@echo "============================================================================================="
	@echo "\n\n"

