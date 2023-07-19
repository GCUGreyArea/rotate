#ifndef DATA_H
#define DATA_H

#define MAX_INT_DIGITS 11

typedef struct kv_data
{
    char *key;
    char *value;
} kv_data_t;

typedef struct data
{
    kv_data_t *kv_ar; // The array of data items
    size_t size;      // The size of the array
    size_t index;     // The number of items added
    char *string;     // The rendered KV string
} data_t;

typedef enum error
{
    OK = 0,
    NOT_INITIALISED,
    WRITE_OUT_OF_BOUNDS
} data_err_t;

data_t *create_data(size_t items);
data_err_t add_int_kv_value(data_t *data, const char *key, const int value);
data_err_t add_str_kv_value(data_t *data, const char *key, const char *value);
data_err_t render(data_t *data);
void teardown(data_t *data);
const char * get_string_value_for_err(data_err_t err);

#endif // DATA_H