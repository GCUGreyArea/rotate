#ifndef __ARGS__
#define __ARGS__
/**
 * @file Args.h
 * @author Barry Robinson (barry.w.robinson64@gmail.com)
 * @brief Provide a simple class for argument extraction and manipulation
 * @version 1.0
 * @date 11-10-2022
 *
 * @copyright Copyright (C) 2022
 */

#include <map>
#include <string>
#include <cstddef>
#include <unordered_set>

class Args {
public:
    Args(int argc, char ** argv);
    ~Args();
    void add_string_value(std::string idxName, std::string altName, std::string def = "");
    void add_int_value(std::string idxName, std::string altName, int def);
    void add_key(std::string key, std::string alt);
    int get_int_value(std::string key);
    std::string get_string_value(std::string key);
    bool is_key_present(std::string key);
    unsigned int get_size() {return mArgs.size();}

private:
    char ** mArgv;
    int mArgc;
    std::map<std::string,int> mIntArgs;
    std::map<std::string,std::string>mStrArgs;
    std::unordered_set<std::string>mArgs;
};

#endif//__ARGS__