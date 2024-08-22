#include "Buffer.h"
#include <iostream>
#include <fstream>

// Rotate the buffer left 1 bit
void Buffer::rotate_left() {
    // We first need the bit of the 
    std::ifstream in_file;
    std::ofstream out_file;

    in_file.open(m_in, std::ios::binary |  std::ios::in);
    out_file.open(m_out,std::ios::binary | std::ios::out | std::ios::app);

    uint8_t byte_1 = 0;
    uint8_t byte_2 = 0;

    // Read in teh first byte
    in_file.read((char*) &byte_1,1);

    // We need to save the most significant bit
    uint8_t bit_1 = byte_1 & 0xb10000000;
    // Now shift it up
    byte_1 = byte_1 << 1;

    // We will need to test that this is not a one byte file...
    in_file.read((char*) &byte_2,1);
    uint8_t bit_2 = byte_2 & 0xb10000000;

} 