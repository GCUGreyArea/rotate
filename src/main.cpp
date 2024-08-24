#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include <librotate.h>

static inline void do_help() {
	std::cout << "./build/rotate -i <infile.bin> -o <outfile.bin> -r [left | right]" << std::endl;
    std::cout << "./build/rotate -s <HEX STRING>" << std::endl;
}

int main(int argc, char **argv)
{
    Args args(argc,argv);

    args.add_string_value("-r","--rotate","left");
    args.add_string_value("-i","--in-file","");
    args.add_string_value("-o","--out-file","");
    args.add_string_value("-s","--string","");


    std::string rdir = args.get_string_value("-r");
    std::string str  = args.get_string_value("-s");
    std::string ifl  = args.get_string_value("-i");
    std::string ofl  = args.get_string_value("-o");

    if(str != "") {
        // Do rotation on the hex string
        HexString b(str);
        b.init();

        if(rdir == "left") {
            b.rotate_left();
        }
        else {
            b.rotate_right();
        }
        b.reset();

        std::string out = b.render();

        std::cout << "Rotated string " << rdir << ": " << out << std::endl;

        exit(0);
    }
    else if(ifl != "" && ofl != "") {
        Buffer b(ifl,ofl);
        b.init();

        if(rdir == "left") {
            b.rotate_left();
        }
        else {
            b.rotate_right();
        }

    }

    return 1;
}
