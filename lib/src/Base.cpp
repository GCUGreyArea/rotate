#include "Base.h"

Base::~Base() {}

/**
 * @brief Implement the rotation algorithm that all derived classes will use.
 * 
 */
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

/**
 * @brief Implement the rotate right algorithm that all derived classes wil use.
 * 
 */
void Base::rotate_right()
{
    // This time we need to save the first byte so we 
    // can rewrite the first byte of the output file 
    uint8_t byte = get_next_byte();

    // First we need to make the place holder in the file
    write_next_byte(byte);

    // Save the first byte as we need to rewrite it
    uint8_t first_byte = byte;
    uint8_t savebit = byte & 0x1;

    while (!end())
    {
        byte = get_next_byte();
        uint8_t b = byte >> 1 | savebit << 7;
        write_next_byte(b);
        savebit = byte & 0x1;
    }

    byte = first_byte >> 1 | savebit << 7;

    write_first_byte(byte);
}