#include "Base.h"


Base::~Base() {}

void Base::rotate_left()
{
    // We need the first byte and to save it's msb
    uint8_t byte = get_next_byte();
    // mask out the left most bit (MSB)
    uint8_t save_bit = byte & 0x80;

    // Temp var
    uint8_t byte_swap = byte << 1;

    while (!end())
    {
        // now we get the next byte
        byte = get_next_byte();

        uint8_t b = byte_swap | (byte >> 7);
        write_next_byte(b);
        byte_swap = byte << 1;
    }

    byte = (byte_swap | (save_bit >> 7));

    write_next_byte(byte);
}

void Base::rotate_right()
{

    uint8_t byte = get_next_byte();
    uint8_t save_bit = byte & 0x1;

    uint8_t byte_swap = byte >> 1;
    uint8_t first_byte = byte;

    while (!end())
    {
        byte = get_next_byte();

        uint8_t b = byte_swap | (byte << 7);
        write_next_byte(b);
        byte_swap = byte >> 1;
    }

    byte = (byte_swap | (save_bit << 7));

    write_next_byte(byte);
    // write_first_byte()
}