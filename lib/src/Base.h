#ifndef BASE_H
#define BASE_H

/**
 * @file Base.h
 * @author Barry Robinson (barry.w.robinson@gemail.com)
 * @brief The base class for the rotation system.  
 * Base implements the bit rotation algorythm.
 * We do it like this so that 
 * 1. We can build unit tests to validate the functionality
 * 2. We can addapt the system to use other formats without having to repeat code
 * 
 * @version 0.1
 * @date 2024-08-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include <iostream>
#include <bitset>

class Base {
public:
    virtual ~Base();
    virtual void init() = 0;
    virtual uint8_t get_next_byte() = 0; 
    virtual void write_next_byte(uint8_t byte) = 0;
    virtual void write_first_byte(uint8_t byte) = 0;
    virtual unsigned int get_length() = 0;
    virtual bool end() = 0;

    virtual void rotate_left();
    virtual void rotate_right();
};

#endif//BASE_H