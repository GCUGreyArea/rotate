#include "HexString.h"
#include <cstring>
#include <regex>
#include <exception>
#include <string>

/**
 * @brief Construct a new HexString object
 * In order to do this we first need to parse the 
 * hex string. If this is not in the correct format,
 * the we need to raise an exception and bail.
 * 
 * @param hex: Shoud be a string in the format
 * '0xNN','0xNN',...,'0xNN'  where NN is a valid hexidecimal 
 * numbe.
 */
HexString::HexString(const char * hex) :
    m_src(hex),
    m_dst(),
    m_rpos(0),
    m_wpos(0),
    m_arr(nullptr) {}

HexString::HexString(std::string hex) :
    m_src(hex),
    m_dst(),
    m_rpos(0),
    m_wpos(0),
    m_arr(nullptr) {}

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
    delete m_arr;
}

/**
 * @brief Internal function used to parse a string in the form
 * 0xAA,0xBB,...,0xDD into seperate bytes of 0xNN.
 * @note This function does not belong in this class
 * it shoul be moved out into it's own container as a 
 * static or simple function in a library.
 * 
 * @param s 
 * @param delimiter 
 * @return std::vector<std::string> 
 */
std::vector<std::string> HexString::split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

/**
 * @brief Trim leading spaces from a string. Used in parsing the hex string 
 * @note This function needs to be moved out into a seperate lkibrary.
 * 
 * @param str 
 * @param whitespace 
 * @return std::string 
 */
std::string HexString::trim(const std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

/**
 * @brief The initialisation frunction parses the hex string 
 * then creates a vector uint8_t values to create an instance 
 * of ArrayBuff. We use new, rather than std::shared_ptr so 
 * that we can closely control when it is destroyed, thereby 
 * cleaning up the memory used to store values.
 * 
 */
void HexString::init() {
    // Split the string into hex values
    std::vector<std::string> vec = split(m_src,",");
    // Place to put conveofrted values
    std::vector<uint8_t> bytes;

    std::regex rx("[ ]*0x[0-9A-Fa-f]{2}");
    std::smatch pieces_match;
    // verify each value is correctly formated
    for(auto a: vec) {
        if (!std::regex_match(a, pieces_match, rx)) {
            throw std::runtime_error("Bad hex value: " + a);
        }

        a = trim(a);
        
        uint8_t val = std::stoi(a.c_str(), 0, 16);
        bytes.push_back(val);
    }

    // Offload to the ArrayBuff class. We use new rather than std::shared_ptr so that we 
    // can cleanly control the destructor.
    m_arr = new ArrayBuff(bytes);
    m_arr->init();
}

/**
 * @brief Fulfil the interface by calling ArrayBuff to get the next byte
 * 
 * @return uint8_t 
 */
uint8_t HexString::get_next_byte() {
    return m_arr->get_next_byte();
} 


/**
 * @brief Fulfill the interface by calling ArrayBuff to write the next byte
 * 
 * @param byte 
 */
void HexString::write_next_byte(uint8_t byte) {
    m_arr->write_next_byte(byte);
}

/**
 * @brief Fulfill the interface by calling ArrayBuff tp write the first byte
 * 
 * @param byte 
 */
void HexString::write_first_byte(uint8_t byte) {
    m_arr->write_first_byte(byte);
}

/**
 * @brief Fulfill the interface by calling ArrayBuff to get the length of the buffer
 * 
 * @return unsigned int 
 */
unsigned int HexString::get_length() {
    return m_arr->get_length();
}

/**
 * @brief Fulfill the interface by calling ArrayBuff to tell if its the end of the buffer
 * 
 * @return true 
 * @return false 
 */
bool HexString::end() {
    return m_arr->end();
}

/**
 * @brief While this looks counter intuative, Base::rotate_left() will call the functions 
 * implement in this class, which wil. route the calls to the correct place, in this instance 
 * m_arr (the ArrayBuff object)
 * 
 */
void HexString::rotate_left() {
    Base::rotate_left();
}

/**
 * @brief Route the call to Base so that calls routed above are called correctly. 
 * See comment for previous function.
 * 
 */
void HexString::rotate_right() {
    Base::rotate_right();
}


/**
 * @brief Render the rotated result back into a string 
 * 
 * @return std::string 
 */
std::string HexString::render() {
    uint8_t * arr = m_arr->get_output(); 
    unsigned int size = m_arr->size();
    std::string str;
    for(unsigned int i=0;i<size;i++) {
        std::stringstream ss;
        ss << std::hex << (int) arr[i]; // int decimal_value
        std::string res ( ss.str() );
        std::transform(res.begin(), res.end(), res.begin(), ::toupper);
        str += "0x" + res;
        if(i+1 < size) {
            str+= ",";
        }
    }

    return str;
} 

