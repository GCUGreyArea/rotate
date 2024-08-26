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
	std::cout << "\t./build/rotate [-i | --in-file] <infile.bin> [-o | --out-file] <outfile.bin> [-r | --rotate] [left | right]" << std::endl;
    std::cout << "\tTake the content of infile.bin and rotate bits in '--rotate' direction, writing the output to outfile.bin" << std::endl;
    std::cout << std::endl;
    std::cout << "\t./build/rotate -s <HEX STRING> [-r | -rotate] [left | right]" << std::endl;
    std::cout << "\tTake the HEX_STRING supplied as --string and rotate the bit values in the direction indicated by --rotate, then write the hex values to the console" << std::endl;
    std::cout << std::endl;
    std::cout << "Note:\tIf no value for '--rotate' is supplied, left is assumed" << std::endl;
    std::cout << "\tIf the file specified by '--in-file' cannot be read, the program will terminate" << std::endl;
}

int main(int argc, char **argv)
{
    Args * args = new Args(argc,argv);

    args->add_key("-h","--help");

    args->add_string_value("-r","--rotate","left");
    args->add_string_value("-i","--in-file","");
    args->add_string_value("-o","--out-file","");
    args->add_string_value("-s","--string","");

    if(args->is_key_present("-h")) {
        do_help();
        delete args;
        exit(1);
    }

    std::string rdir = args->get_string_value("-r");
    std::string str  = args->get_string_value("-s");
    std::string ifl  = args->get_string_value("-i");
    std::string ofl  = args->get_string_value("-o");

    delete args;

    if(str != "") {
        // Do rotation on the hex string
        HexString * b = new HexString(str);

        try {
            b->init();
        }
        catch(std::runtime_error& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            delete b;

            return -1; 
        }


        if(rdir == "left") {
            b->rotate_left();
        }
        else {
            b->rotate_right();
        }
        b->reset();

        std::string out = b->render();
        delete b;

        std::cout << "Rotated string " << rdir << ": " << out << std::endl;
    }
    else if(ifl != "" && ofl != "") {
        if(!std::filesystem::exists(ifl)) {
            std::cout << std::endl;
            std::cout << "file " << ifl << " can not be opened" << std::endl;
            std::cout << "please make sure you provide a complete path to the file" << std::endl;
            std::cout << std::endl;
            do_help();
            exit(0);
        }

        Buffer b(ifl,ofl);
        b.init();

        if(rdir == "left") {
            b.rotate_left();
        }
        else {
            b.rotate_right();
        }
    }
    else {
        std::cout << "Incorect arguments used" << std::endl;
        std::cout << "please follow instructions on the following help screen" << std::endl;
        std::cout << std::endl;

        do_help();
    }

    return 1;
}
