#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <vector>
#include <string>

class StringUtils {
public:
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
static std::vector<std::string> split(std::string s, std::string delimiter) {
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
static std::string trim(const std::string& str, const std::string& whitespace  = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}


};

#endif//STRING_UTILS_H