#include "Buffer.h"

Buffer::Buffer(const char *inf, const char *outf) : 
    m_in(inf),
    m_out(outf),
    m_pos(0) {}

Buffer::Buffer(std::string inf,std::string outf) : 
    m_in(inf),
    m_out(outf),
    m_pos(0) {}

Buffer::~Buffer()
{
    m_in_file.close();
    m_out_file.close();
}

void Buffer::init()
{
    m_in_file.open(m_in, std::ios::binary | std::ios::in);
    m_out_file.open(m_out, std::ios::binary | std::ios::out);

    // Get the length in bytes
    m_in_file.seekg(0, m_in_file.end);
    m_length = m_in_file.tellg();
    m_in_file.seekg(0, m_in_file.beg);
}

uint8_t Buffer::get_next_byte()
{
    uint8_t byte;
    m_in_file.read((char *)&byte, 1);
    m_pos++;

    return byte;
}

void Buffer::write_next_byte(uint8_t byte)
{
    m_out_file.write((char *)&byte, 1);
}

void Buffer::write_first_byte(uint8_t byte) {
    auto pp = m_out_file.tellp();
    m_out_file.seekp(0, m_out_file.beg);
    m_out_file.write((char *)&byte, 1);
    m_out_file.seekp(pp);
}

bool Buffer::end()
{
    return m_length == m_pos;
}

void Buffer::rotate_left()
{
    Base::rotate_left();
}

void Buffer::rotate_right()
{
    Base::rotate_right();
}