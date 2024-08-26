#ifndef HEX_STRING_H
#define HEX_STRING_H

/**
 * @file HexString.h
 * @author Barry Robinson (barry.w.robinson64@gmail.com)
 * @brief Create a class for rotating the binary values of 
 * strings where the values are represengted as hexidecimal 
 * in the form "0xAB,0xAC,0xBB,...,0x01"
 * @version 0.1
 * @date 2024-08-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include <string>
#include <memory>
#include <vector>
#include "Base.h"
#include "ArrayBuffer.h"


class HexString : public Base {
public:
    HexString(std::string str);
    HexString(const char * str);
    virtual ~HexString();
    virtual void init();
    virtual uint8_t get_next_byte(); 
    virtual void write_next_byte(uint8_t byte);
    virtual void write_first_byte(uint8_t byte);
    virtual unsigned int get_length();
    virtual bool end();

    virtual void rotate_left();
    virtual void rotate_right();

    
    uint8_t get_rotate_byte() {
        return m_arr->get_rotate_byte();
    }

    void reset() {
        m_arr->init();
    }
    
    std::string render();

    ArrayBuff * get_array_buff() {return m_arr;}

private:
    std::string m_src;      //! source string
    std::string m_dst;      //! Destination rotated string
    unsigned int m_rpos;    //! read position
    unsigned int m_wpos;    //! write position

    //! The array buffer object that will rotate the values
    ArrayBuff * m_arr;
};

#endif//HEX_STRING_H