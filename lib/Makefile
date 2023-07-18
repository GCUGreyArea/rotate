
NAME  = data

CXSRC = $(shell find src -name *.cpp)
CSRC  = $(shell find src -name *.c)
UNAME = $(shell uname)

OBJ := $(patsubst %.cpp,$(BUILD)/%.o,$(CXSRC)) $(patsubst %.c,$(BUILD)/%.o,$(CSRC))

BUILD = build
LIBDIR = .

TARGET  = lib$(NAME).so
LIBDIR  =  .

OBJ    := $(patsubst %.cpp,$(BUILD)/%.o,$(CXSRC)) $(patsubst %.c,$(BUILD)/%.o,$(CSRC))

ifeq ($(UNAME), Darwin)
CC       = cc
CXX      = c++
else
CC     = gcc
CXX    = g++
endif

CFLAGS += -fPIC

all: build $(TARGET)

build:
	mkdir -p build/src

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -shared -o $(BUILD)/$(TARGET)

$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILD)
