#include "minunit.h"
#include <lcthw/ringbuffer.h>
#include <assert.h>

static RingBuffer *buffer = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3

char *test_create()
{
    buffer = RingBuffer_create(100);
    mu_assert(buffer != NULL, "Failed to create RingBuffer.");

    return NULL;
}

char *test_destroy()
{
    mu_assert(buffer != NULL, "Failed to make RingBuffer #2.");
    RingBuffer_destroy(buffer);

    return NULL;
}

char *test_write_read()
{
    int i = 0;
    for(i = 0; i < NUM_TESTS; i++)
    {
        int result = RingBuffer_write(buffer, tests[i], strlen(tests[i]));
        mu_assert(result == (int)strlen(tests[i]), "Failed to write to RingBuffer.");

        char target[100];
        int read_result = RingBuffer_read(buffer, target, strlen(tests[i]));
        mu_assert(read_result == (int)strlen(tests[i]), "Failed to read from RingBuffer.");
        target[read_result] = '\0';
        mu_assert(strcmp(target, tests[i]) == 0, "Read data doesn't match written data.");
    }

    mu_assert(RingBuffer_available_data(buffer) == 0, "Available data after read should be 0.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_write_read);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
