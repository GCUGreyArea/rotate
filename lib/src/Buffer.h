#ifndef ROTATE_H
#define ROTATE_H

#include <memory>
#include <cstdint>
#include <cstring>

class Buffer {
    Buffer(size_t size) :
        m_buff(new uint8_t[size]),
        m_len(size) {}

    ~Buffer() {
        // Whipe everything out when we are done
        std::memset(m_buff,0,m_len);
        delete [] m_buff;
        m_buff = nullptr;
    }

    void rotate_left();

    // Hold our digital data
    uint8_t * m_buff;
    size_t m_len;  
};

#endif // !ROTATE_H