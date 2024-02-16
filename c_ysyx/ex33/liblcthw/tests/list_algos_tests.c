#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>

char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS", "asds", "rqefd", "ASFBQ", "DASFQ", "DADVS", "FAKDF", "DASFWVG", "dafa","dafsdg", "iABJFDKA", "ASJ","DASDFAF", "SIOUAF", "GSIUSB", "ZUQE"};
#define NUM_VALUES 5

List *create_words()
{
    int len = sizeof(values) / sizeof(values[0]);
    int i = 0;
    List *words = List_create();

    for (i = 0; i < len; i++)
    {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur)
    {
        if (cur->next && strcmp(cur->value, cur->next->value) > 0)
        {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

// char *test_bubble_sort()
// {
//     double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

//     List *words = create_words();

//     // should work on a list that needs sorting
//     clock_t start = clock();
//     int rc = List_bubble_sort(words, (List_compare)strcmp);
//     clock_t end = clock();
//     double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
//     printf("%lf\n",time_taken);

//     mu_assert(rc == 0, "Bubble sort failed.");
//     mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

//     // should work on an already sorted list
//     rc = List_bubble_sort(words, (List_compare)strcmp);
//     mu_assert(rc == 0, "Bubble sort of already sorted failed.");
//     mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

//     List_destroy(words);

//     // should work on an empty list
//     words = List_create(words);
//     rc = List_bubble_sort(words, (List_compare)strcmp);
//     mu_assert(rc == 0, "Bubble sort failed on empty list.");
//     mu_assert(is_sorted(words), "Words should be sorted if empty.");

//     List_destroy(words);

//     return NULL;
// }

// char *test_merge_sort()
// {
//     List *words = create_words();

//     // should work on a list that needs sorting
//     clock_t start = clock();
//     List *res = List_merge_sort(words, (List_compare)strcmp);
//     clock_t end = clock();
//     double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
//     printf("%lf\n",time_taken);

//     mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

//     List *res2 = List_merge_sort(res, (List_compare)strcmp);
//     mu_assert(is_sorted(res), "Should still be sorted after merge sort.");
//     List_destroy(res2);
//     List_destroy(res);

//     List_destroy(words);
//     return NULL;
// }

char *test_bubble_sort()
{
    int num_iterations = 1000000; // 设置迭代次数
    double total_time_taken = 0.0;

    for (int i = 0; i < num_iterations; i++)
    {
        List *words = create_words();

        clock_t start = clock();
        int rc = List_bubble_sort(words, (List_compare)strcmp);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_time_taken += time_taken;

        mu_assert(rc == 0, "Bubble sort failed.");
        mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

        List_destroy(words);
    }

    printf("Total Bubble Sort Time: %lf seconds\n", total_time_taken);
    printf("Average Bubble Sort Time: %lf seconds\n", (double)total_time_taken / num_iterations);
    return NULL;
}

char *test_merge_sort()
{
    int num_iterations = 1000000; // 设置迭代次数
    double total_time_taken = 0.0;

    for (int i = 0; i < num_iterations; i++)
    {
        List *words = create_words();

        clock_t start = clock();
        List *res = List_merge_sort(words, (List_compare)strcmp);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_time_taken += time_taken;

        mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

        List_destroy(res);
        List_destroy(words);
    }

    printf("Total Merge Sort Time: %lf seconds\n", total_time_taken);
    printf("Average Merge Sort Time: %lf seconds\n", (double)total_time_taken / num_iterations);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);
