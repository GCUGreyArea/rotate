#include <gtest/gtest.h>

#include <stdlib.h>
#include <stdio.h>

#include <libData.h>


TEST(data_tests,test_that_data_works) {
    data_t *data = create_data(3);

    ASSERT_TRUE(data);
    ASSERT_TRUE(data->kv_ar);
    ASSERT_TRUE(data->index == 0);
    ASSERT_TRUE(data->size == 3);

    ASSERT_TRUE(add_int_kv_value(data, "key", 123) == OK);
    ASSERT_TRUE(add_str_kv_value(data, "other_key", "some value") == OK);
    ASSERT_TRUE(add_int_kv_value(data, "key_1234", 564092345) == OK);
    ASSERT_TRUE(add_str_kv_value(data, "no key here", "no other value") == WRITE_OUT_OF_BOUNDS);

    ASSERT_TRUE(strcmp(data->kv_ar[0].key, "key") == 0);
    ASSERT_TRUE(strcmp(data->kv_ar[1].key, "other_key") == 0);
    ASSERT_TRUE(strcmp(data->kv_ar[2].key, "key_1234") == 0);

    ASSERT_TRUE(strcmp(data->kv_ar[0].value, "123") == 0);
    ASSERT_TRUE(strcmp(data->kv_ar[1].value, "some value") == 0);
    ASSERT_TRUE(strcmp(data->kv_ar[2].value, "564092345") == 0);

    ASSERT_TRUE(render(data) == OK);

    ASSERT_TRUE(strcmp(data->string, "key=123,other_key=some value,key_1234=564092345") == 0);

    teardown(data);

}