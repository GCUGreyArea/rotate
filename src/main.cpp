#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include <librotate.h>

int main(int argc, char **argv)
{
    Buffer b("test.bin","test-out.bin");

    b.rotate_left();
    return 1;
}
