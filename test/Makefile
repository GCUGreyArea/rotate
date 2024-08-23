NAME	= rotate
TARGET  = test_$(NAME)

CXXSRC = $(wildcard src/*.cpp)
CSRC   = $(wildcard src/*.c)

LIB     = lib$(NAME).so
BUILD   = build
LIBDIR  = ../lib
LIBDEP  = $(LIBDIR)/$(BUILD)/$(LIB)

CXXOBJ    := $(patsubst %.cpp,$(BUILD)/%.o,$(CXXSRC))
COBJ      := $(patsubst %.c,$(BUILD)/%.o,$(CSRC))
PWD       := $(shell pwd)
LINK      := -lgtest -lglog -lpthread

ifeq ($(UNAME), Darwin)
CC       = cc
CXX      = c++
else 
CC     = gcc
CXX    = g++
endif

CXXFLAGS += -g

all: $(TARGET) $(OBJ) $(COBJ) $(LIBDEP)

$(TARGET) : build $(CXXOBJ) $(COBJ)
	$(CXX) $(CXXFLAGS) -I$(LIBDIR) $(CXXOBJ) $(COBJ) -o $(BUILD)/$(TARGET) -l$(NAME) $(LINK) $(LNK)

build:
	mkdir -p "$(BUILD)/src"

$(LIBDEP) :
	cd $(LIBDIR) && make

$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

run:
	./$(BUILD)/$(TARGET)

clean:
	rm -rf $(BUILD)

