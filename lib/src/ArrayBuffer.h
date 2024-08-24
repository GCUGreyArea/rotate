#ifndef ARRAY_BUFFER_H
#define ARRAY_BUFFER_H

#include <cstring>
#include <vector>
#include "Base.h"

class ArrayBuff : Base {
public:
    virtual ~ArrayBuff() {
        // remove all data before deleting
        memset(m_out,0,m_size);
        memset(m_arr,0,m_size);
        delete [] m_out;
        delete [] m_arr;
    }

    ArrayBuff(uint8_t * ar, unsigned int size) : 
        m_arr(new uint8_t[size]),
        m_out(new uint8_t[size]),
        m_size(size),
        m_place(0) {
            memcpy(m_arr,ar,size*sizeof(uint8_t));
            memset(m_out,0,size);
        }

    ArrayBuff(std::vector<uint8_t> ar) : 
        m_arr(new uint8_t[ar.size()]),
        m_out(new uint8_t[ar.size()]),
        m_size(ar.size()),
        m_place(0) {
            int i=0;
            for(auto n : ar) {
                m_arr[i++] = n;
            }

            memset(m_out,0,m_size);
        }

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

    std::vector<uint8_t> get_buffer_vector() {
        std::vector<uint8_t> vec;
        vec.reserve(m_size);
        for(unsigned int i=0;i<m_size;i++) {
            vec.push_back(m_out[i]);
        }

        return vec;
    }

    uint8_t * get_output() {
        return m_out;
    }

    unsigned int size() {
        return m_size;  
    }


private:
    uint8_t * m_arr;
    uint8_t * m_out;
    unsigned int m_size;
    unsigned int m_place;
    unsigned int m_out_place;
};

#endif//ARRAY_BUFFER_H