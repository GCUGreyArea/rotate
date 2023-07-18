# C base KV render function

## Functionality 

This is a simple library that tokens as `key` `value` pairs to be added into a structure, then rendered into a `KV` string. 

Currently the library supports `int` and `char *` values, and nhas the following functions.

```c
data_t * create_data(size_t items);
error_t add_int_kv_value(data_t *data, char *key, int value);
error_t add_str_kv_value(data_t *data, char *key, char* value);
error_t render(data_t * data);
void teardown(data_t * data);
```

Extending supported types in a matter of implementing a function to convert the type to a string, then call `add_str_kv_value` on the `data` object.

## Using the library

```c
data_t * data = create_data(3);
error_t err = add_int_kv_value(data,"key",123);
assert(err == OK);
err = add_str_kv_value(data,"other_key","some value");
assert(err == OK);

err = add_int_kv_value(data,"key_1234",564092345);
assert(err == OK);

err = render(data);
assert(err == OK);
```

In this instance, `render` will fill out the `data->string` with the value `"key=123,other_key=some value,key_1234=564092345"`. 


At the end of the life of the object `teardown` must be called to free memory alocated by the library.

## TODO

1. Rename functions and structures to to avoid namespace polution.
2. Extend the functionality so that the structre can be reset.
   1. This should allow the reuse of already allocated memory, so 
   must track what has been alocated as well as what has been used
   and reset other variable to point to the start of usable space.
   2. It will also need to clear existing entries so that their memory 
   footprint (their content) is erased.
3. Extend the library so that the structure can be enlarged.
4. Document structures and functions, this sould include (see example above `create_data`)
   1. required arguments
   2. return values
