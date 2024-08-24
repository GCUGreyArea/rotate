#include "HexString.h"
#include <cstring>

HexString::HexString(const char * hex) :
    m_src(hex),
    m_dst(),
    m_rpos(0),
    m_wpos(0) {
        
    }

/**
 * @brief Destroy the HexString object. Before we leave
 * we need to zero out all memory that has been used. 
 * std::string only guareties that the memory will be 
 * reclaimed. Not that it will be whiped.
 * 
 */
HexString::~HexString() {
    std::memset((void*)m_src.data(),'\0',m_src.length());
    std::memset((void*)m_dst.data(),'\0',m_dst.length());
}