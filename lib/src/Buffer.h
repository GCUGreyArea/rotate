#ifndef ROTATE_H
#define ROTATE_H

#include "Base.h"
#include <iostream>
#include <fstream>

#include <memory>
#include <cstdint>
#include <cstring>

class Buffer : public Base {
public:
    Buffer(const char * inf, const char * outf);
    virtual ~Buffer();
    void rotate_left();
    void rotate_right();

    virtual void init();
    virtual uint8_t get_next_byte(); 
    virtual void write_next_byte(uint8_t byte);
    virtual unsigned int get_length() {return m_length;}
    virtual bool end();

private:
    // File names
    std::string m_in;
    std::string m_out;

    // Files
    std::ifstream m_in_file;
    std::ofstream m_out_file;
    unsigned int m_length;
    unsigned int m_pos;
};

#endif // !ROTATE_H