#ifndef ROTATE_H
#define ROTATE_H

#include <memory>
#include <cstdint>
#include <cstring>
#include <iostream>

class Buffer {
public:
    Buffer(const char * inf, const char * outf) :
        m_byte(0),
        m_in(inf),
        m_out(outf) {}

    ~Buffer() {}

    void rotate_left();

    // Hold our digital data
    uint8_t  m_byte;
    std::string m_in;
    std::string m_out;
};

#endif // !ROTATE_H