#ifndef DATA_H
#define DATA_H

#define MAX_INT_DIGITS 11

typedef struct kv_data {
    char * key;
    char * data;
} kv_data_t;

typedef struct data {
    kv_data_t * kv_ar; // The array of data items
    size_t size;       // The size of the array
    size_t index;      // The number of items added
    char * string;     // The rendered KV string      
} data_t;

typedef enum error {
    OK = 0,
    NOT_INITIALISED,
    WRITE_OUT_OF_BOUNDS
} error_t;

data_t * create_data(size_t items);
error_t add_int_kv_value(data_t *data, char *key, int value);
error_t add_str_kv_value(data_t *data, char *key, char* value);
error_t render(data_t * keys);
void teardown(data_t * string);

#endif//DATA_H