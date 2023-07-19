#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memfailure.h"

#include "data.h"
/**
 * @brief Create a data object. This is the first thing that must happen
 *
 * @param size
 * @return data_t*
 */
data_t *create_data(size_t size)
{
    data_t *data = (data_t *)malloc(sizeof(data_t));
    if (data == NULL)
    {
        mem_failure();
    }

    data->kv_ar = (kv_data_t *)malloc(sizeof(kv_data_t) * size);
    if (data->kv_ar == NULL)
    {
        mem_failure();
    }

    for (size_t cnt = 0; cnt < size; cnt++)
    {
        data->kv_ar[cnt].key = NULL;
        data->kv_ar[cnt].value = NULL;
    }

    // Setup members
    data->size = size;
    data->index = 0;
    data->string = NULL;

    return data;
}

data_err_t add_str_kv_value(data_t *data, const char *key, const char *value)
{
    if (data == NULL)
    {
        return NOT_INITIALISED;
    }

    size_t key_len = strlen(key);
    size_t val_len = strlen(value);

    if (data->index >= data->size)
    {
        return WRITE_OUT_OF_BOUNDS;
    }

    size_t cnt = data->index++;

    data->kv_ar[cnt].key = (char *)malloc(sizeof(char) * (key_len + 1));
    if (data->kv_ar[cnt].key == NULL)
    {
        mem_failure();
    }

    data->kv_ar[cnt].value = (char *)malloc(sizeof(char) * (val_len + 1));
    if (data->kv_ar[cnt].value == NULL)
    {
        mem_failure();
    }

    strcpy(data->kv_ar[cnt].key, key);
    strcpy(data->kv_ar[cnt].value, value);

    return OK;
}

data_err_t add_int_kv_value(data_t *data, const char *key, const int value)
{
    if (data == NULL)
    {
        return NOT_INITIALISED;
    }

    char v_arr[MAX_INT_DIGITS + 1];

    sprintf(v_arr, "%d", value);

    return add_str_kv_value(data, key, v_arr);
}

data_err_t render(data_t *data)
{
    if (data == NULL)
    {
        return NOT_INITIALISED;
    }

    int total_key_len = 0;
    int total_data_len = 0;
    for (size_t i = 0; i < data->index; i++)
    {
        total_key_len += strlen(data->kv_ar[i].key) + 1;
        total_data_len += strlen(data->kv_ar[i].value) + 1;
    }

    // We need to alocate enough space for all keys and values
    // pluss a comman and equals sign for each entry, -1 for the last command
    // which is not added
    int total_len = total_key_len + total_data_len + (data->index * 2) - 1;

    data->string = (char *)malloc(total_len * sizeof(char));

    size_t idx = 0;
    for (size_t cnt = 0; cnt < data->index; cnt++)
    {
        // The base address of for the start of the nex sequence
        char *str = &(data->string[idx]);
        size_t klen = strlen(data->kv_ar[cnt].key);
        size_t vlen = strlen(data->kv_ar[cnt].value);
        if (cnt != data->index - 1)
        {
            sprintf(str, "%s=%s,", data->kv_ar[cnt].key, data->kv_ar[cnt].value);
            idx += klen + vlen + 2;
        }
        else
        {
            sprintf(str, "%s=%s", data->kv_ar[cnt].key, data->kv_ar[cnt].value);
        }
    }

    return OK;
}

void teardown(data_t *data)
{
    if (data->string)
    {
        memset(data->string, 0, strlen(data->string));
        free(data->string);
    }

    for (size_t cnt = 0; cnt < data->index; cnt++)
    {
        memset(data->kv_ar[cnt].key, '\0', strlen(data->kv_ar[cnt].key));
        free(data->kv_ar[cnt].key);

        memset(data->kv_ar[cnt].value, '\0', strlen(data->kv_ar[cnt].value));
        free(data->kv_ar[cnt].value);
    }

    memset(data->kv_ar, 0, sizeof(kv_data_t) * data->size);
    free(data->kv_ar);

    data->size = 0;
    data->index = 0;

    free(data);
}

const char *get_string_value_for_err(data_err_t err)
{
    switch (err)
    {
    case OK:
        return "OK";
    case NOT_INITIALISED:
        return "NOT_INITIALISED";
    case WRITE_OUT_OF_BOUNDS:
        return "NOT_INITIALISED";
    default:
        break;
    }

    return "UNKNOWN";
}
