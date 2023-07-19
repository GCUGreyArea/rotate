#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include <libData.h>

/**
 * @brief Test the write kv module
 *
 * @todo
 * 1. Rename functions and structures to to avoid namespace polution.
 * 2. Extend the functionality so that the structre can be reset.
 *   1. This should allow the reuse of already allocated memory, so 
 *   must track what has been alocated as well as what has been used
 *   and reset other variable to point to the start of usable space.
 *   2. It will also need to clear existing entries so that their memory 
 *   footprint (their content) is erased.
 * 3. Extend the library so that the structure can be enlarged.
 * 4. Document structures and functions, this sould include (see example above `create_data`)
 *   1. required arguments
 *   2. return values
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
    if( argc == 1) {
        printf("Please supply some argument to convert to kv string\n");
        printf("./build/data \"name\", \"barry\",\"job\",\"lead cyber engineer\"\n");
        exit(0);
    }
    else if(argc == 2 && (strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"-h") == 0)) {
        printf("\nConstruct a key value string from individual arguments passed on the command line\n");
        printf("Usage:\n");
        printf("\t./build/data [-h | --help]: diplay this message\n");
        printf("\t./build/data <key value list>\n");
        printf("\tExample: ./build/data name \"Barry Robinson\" copany \"Northrup Grumman\" ocupation \"Lead cyber engineer\"\n");
        printf("\tThis wil product the string : name=Barry Robinson,company=Northrup Grumman,ocupation=Lead cyber engineer\n\n");
        exit(0);
    }
    else  if((argc-1) % 2 != 0) {
        printf("uneaven number of arguments. Key values must be supplied in pairs\n");
        exit(0);
    }

    data_t *data = create_data(argc-1 / 2);
    data_err_t err;
    for(int i=1; i < argc; i+=2) {
        char * key = argv[i];
        char * value = argv[i+1];
        err = add_str_kv_value(data,key,value);
        if(err != OK) {
            printf("ERROR: add_str_kv_value return \"%s\"", get_string_value_for_err(err));
            exit(0);
        }
    }

    err = render(data);
    if(err != OK) {
        printf("ERROR: Faiuled to render data \"$+%s\"\n", get_string_value_for_err(err));
        exit(0);
    } 

    printf("String: \"%s\"\n", data->string);

    teardown(data);
    exit(1);
}
