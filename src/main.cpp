/**
 * @file main.cpp
 * @author Barry Robinson(barry.w.robinson64@gmail.com)
 * @brief Create a program to rotate the bits in a file either 
 * left or right by one bit. 
 * @version 0.1
 * @date 2024-08-25
 * 
 * @copyright Copyright (c) 2024
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include <filesystem>

#include <librotate.h>

static inline void do_help() {
    std::cout << "Help" << std::endl;
	std::cout << "\t./build/rotate [-i | --in-file] <IN_FILE_NAME> [-o | --out-file] <OUT_FILE_NAME> [-r | --rotate] [left | right]" << std::endl;
    std::cout << "\tTake the content of IN_FILE_NAME and rotate bits in '--rotate' direction, writing the output to OUT_FILE_NAME" << std::endl;
    std::cout << "\n\t./build/rotate -s <HEX STRING> [-r | -rotate] [left | right]" << std::endl;
    std::cout << "\tTake the HEX_STRING supplied as --string and rotate the bit values in the direction indicated by --rotate, then write the hex values to the console" << std::endl;
    std::cout << "\n\t./build/rotate -m <OUT_FILE_NAME> -s <HEX_STRING>" << std::endl;
    std::cout << "\tTake the HEX_STRING supplied by --string and write it as bytes to the OUT_FILE_NAME supplied by --make" << std::endl;
    std::cout << "\n\t./build/rotate -d <IN_FILE_NAME>" << std::endl;
    std::cout << "\tDump the hexidecimal values from IN_FILE_NAME to the terminal" << std::endl;
    std::cout << "\nNote:\tIf no value for '--rotate' is supplied for a rotate function, left is assumed" << std::endl;
    std::cout << "\tIf the file specified by '--in-file' or `--dump` cannot be read, the program will terminate" << std::endl;
}

static bool check_file_exists(std::string & ifl) {
    if(!std::filesystem::exists(ifl)) {
        std::cout << std::endl;
        std::cout << "Please make sure you provide a complete and correct path" << std::endl;
        std::cout << "Coult not find file: " << ifl << std::endl;
        std::cout << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    Args * args = new Args(argc,argv);

    args->add_key("-h","--help");

    args->add_string_value("-r","--rotate","left");
    args->add_string_value("-i","--in-file","");
    args->add_string_value("-o","--out-file","");
    args->add_string_value("-s","--string","");
    args->add_string_value("-m","--make","output.bin");
    args->add_string_value("-d","--dump","");

    if(args->is_key_present("-h")) {
        do_help();
        delete args;
        return 0;
    }

    std::string rdir = args->get_string_value("-r");
    std::string str  = args->get_string_value("-s");
    std::string ifl  = args->get_string_value("-i");
    std::string ofl  = args->get_string_value("-o");
    std::string mf   = args->get_string_value("-m");
    std::string df   = args->get_string_value("-d");

    delete args;

    if(str != "") {
        // Make a binary file using the supplied string [-s | --string] 
        // and the argument to [-m | --make]
        if(mf != "") {
                HexString * b = new HexString(str);
                b->init();

                ArrayBuff * arr = b->get_array_buff();
                uint8_t * bytes = arr->get_source();

                std::cout << "Making binary file " << mf << std::endl;
                std::ofstream of(mf,  std::ios::binary | std::ios::out);
                for(unsigned int i=0;i<arr->size();i++) {
                    std::cout << "Writing: " << std::hex << (int) bytes[i] << std::endl;
                    of.write((const char*) &bytes[i],sizeof(uint8_t));
                }
                of.close();
        } 
        // Otherwise use the string argument to rotate
        else {
            // Do rotation on the hex string
            HexString * b = new HexString(str);

            try {
                b->init();

                if(rdir == "left") {
                    b->rotate_left();
                }
                else {
                    b->rotate_right();
                }
            }
            catch(std::runtime_error& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
                delete b;

                return -1; 
            }

            b->reset();

            std::string out = b->render();
            delete b;

            std::cout << "Rotated string " << rdir << ": " << out << std::endl;
        }
    }
    // Use [-i | --in-file] and [-o | --out-file] to do a bit rotation
    // o the file contents 
    else if(ifl != "" && ofl != "") {
        // If the input file does exist that ='s a problem 
        if(!check_file_exists(ifl)) {
            do_help();
            return -1;
        }

        Buffer * b  = new Buffer(ifl,ofl);
        b->init();

        if(rdir == "left") {
            b->rotate_left();
        }
        else {
            b->rotate_right();
        }

        delete b;
    }
    // Dump the content of a binary file has hex 
    // Hexdump on my system messes up the byt order?
    else if(df != "") {
        if(!check_file_exists(df)) {
            do_help();
            return -1;
        }

        std::ifstream in(df,std::ios::binary | std::ios::in);

        in.seekg(0, in.end);
        unsigned int len = in.tellg();
        in.seekg(0, in.beg);

        int count = 0;
        int row = 0;
        uint8_t byte;
        for(unsigned int i=0; i<len;i++) {
            in.read((char*)&byte,1);
            if(count == 0) {
                std::cout << "\n" << std::setfill('0') << std::setw(4) << row << "\t";
            }
            std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) byte << " ";
            count++; 
            if(count == 8) {
                count = 0;
                row++;
            }
        }
        std::cout << std::endl;
 
    }
    else {
        std::cout << "Incorect arguments used" << std::endl;
        std::cout << "please follow instructions on the following help screen" << std::endl;
        std::cout << std::endl;

        do_help();
    }

    return 1;
}
