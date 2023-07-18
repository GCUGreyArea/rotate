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
 *      1. modular name space for functions and structures.
 *      2. extend the functionality so that the structre can be reset
 *         this should allow the reuse of already allocated memory, so 
 *         must track what has been alocated as well as what has been used.
 *      3. Extend the library so that the structure can be enlarged.
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char ** argv) {
    data_t * data = create_data(3);

    assert(data);
    assert(data->kv_ar);
    assert(data->index == 0);
    assert(data->size == 3);

    assert(add_int_kv_value(data,"key",123) == OK);
    assert(add_str_kv_value(data,"other_key","some value") == OK);
    assert(add_int_kv_value(data,"key_1234",564092345) == OK);
    assert(add_str_kv_value(data,"no key here","no other value") == WRITE_OUT_OF_BOUNDS);

    assert(strcmp(data->kv_ar[0].key,"key") == 0);
    assert(strcmp(data->kv_ar[1].key,"other_key") == 0);
    assert(strcmp(data->kv_ar[2].key,"key_1234") == 0);

    assert(strcmp(data->kv_ar[0].data,"123") == 0);
    assert(strcmp(data->kv_ar[1].data,"some value") == 0);
    assert(strcmp(data->kv_ar[2].data,"564092345") == 0);

    assert(render(data) == OK);

    assert(strcmp(data->string,"key=123,other_key=some value,key_1234=564092345") == 0);
    teardown(data);
}

