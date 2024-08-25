#include "Buffer.h"

Buffer::Buffer(const char *inf, const char *outf) : 
    m_in(inf),
    m_out(outf),
    m_pos(0) {}

Buffer::Buffer(std::string inf,std::string outf) : 
    m_in(inf),
    m_out(outf),
    m_pos(0) {}

/**
 * @brief Destroy the Buffer object insuring that all 
 * memory is whiped clean before exiting.
 * 
 */
Buffer::~Buffer()
{
    // Zero out the memory used by the filenames
    memset((void*)m_in.data(),'\0',m_in.length());
    memset((void*)m_out.data(),'\0',m_out.length());
    m_in_file.close();
    m_out_file.close();
}

/**
 * @brief Initialise the Buffer object
 * @note This is a bad bit of architecture that 
 * needs rethinking. The idea of init is muduled 
 * as it was also used to reset the file point to 
 * the start of the file, and this is not really it's
 * function. 
 * 
 */
void Buffer::init()
{
    m_in_file.open(m_in, std::ios::binary | std::ios::in);
    m_out_file.open(m_out, std::ios::binary | std::ios::out);

    // Get the length in bytes
    m_in_file.seekg(0, m_in_file.end);
    m_length = m_in_file.tellg();
    m_in_file.seekg(0, m_in_file.beg);
}

/**
 * @brief Get the next byte in the stream as a uint8_t.
 * 
 * @return uint8_t 
 */
uint8_t Buffer::get_next_byte()
{
    uint8_t byte;
    m_in_file.read((char *)&byte, 1);
    m_pos++;

    return byte;
}

/**
 * @brief Write the next byte into the stream
 * 
 * @param byte 
 */
void Buffer::write_next_byte(uint8_t byte)
{
    m_out_file.write((char *)&byte, 1);
}

/**
 * @brief Write the first byte of the stream, 
 * regardless of where we are in the write 
 * sequence.
 * 
 * @param byte 
 */
void Buffer::write_first_byte(uint8_t byte) {
    auto pp = m_out_file.tellp();
    m_out_file.seekp(0, m_out_file.beg);
    m_out_file.write((char *)&byte, 1);
    m_out_file.seekp(pp);
}

/**
 * @brief Test if we have reached the end of the file
 * 
 * @return true 
 * @return false 
 */
bool Buffer::end()
{
    return m_length == m_pos;
}

/**
 * @brief Rotate the byte rignt by calling the underlying implimentation.
 * 
 * @return * void 
 */
void Buffer::rotate_left()
{
    Base::rotate_left();
}

/**
 * @brief Rotate the byte left by calling the underlying implementation.
 * 
 */
void Buffer::rotate_right()
{
    Base::rotate_right();
}