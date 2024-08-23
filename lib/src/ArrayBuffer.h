#ifndef ARRAY_BUFFER_H
#define ARRAY_BUFFER_H

#include "Base.h"

class ArrayBuff : Base {
public:
    virtual ~ArrayBuff() {
        delete [] m_out;
    }

    ArrayBuff(uint8_t * ar, unsigned int size) : 
        m_arr(ar),
        m_out(new uint8_t[size]),
        m_size(size),
        m_place(0) {}

    virtual void init() {
        m_place = 0;
        m_out_place = 0;
    }

    virtual uint8_t get_next_byte() {
        if(m_place < m_size) {
            return m_arr[m_place++];
        }  else {
            std::cerr << "Out of bounds" << std::endl; 
            abort();
        }
    } 
    
    virtual void write_next_byte(uint8_t byte) {
        m_out[m_out_place++] = byte;
    }

    virtual void write_first_byte(uint8_t byte) {
        m_out[0] = byte;
    }

    virtual unsigned int get_length() {
        return m_size;
    }

    virtual void rotate_left() {
        Base::rotate_left();
    }

    virtual void rotate_right() {
        Base::rotate_right();
    }

    virtual bool end() {
        return m_place == m_size;
    }

    uint8_t get_rotate_byte() {
        return m_out[m_out_place++];
    }

private:
    uint8_t * m_arr;
    uint8_t * m_out;
    unsigned int m_size;
    unsigned int m_place;
    unsigned int m_out_place;
};

#endif//ARRAY_BUFFER_H