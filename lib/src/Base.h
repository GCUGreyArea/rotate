#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <bitset>

class Base {
public:
    virtual ~Base();
    virtual void init() = 0;
    virtual uint8_t get_next_byte() = 0; 
    virtual void write_next_byte(uint8_t byte) = 0;
    virtual unsigned int get_length() = 0;
    virtual bool end() = 0;

    virtual void rotate_left();
    virtual void rotate_right();
};

#endif//BASE_H