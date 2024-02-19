#include <lcthw/DArray_algos.h>
#include <stdio.h>
#include <stdlib.h>


/*
 * The details of heapsort and mergesort have not yet been implemented.
 * If you need to use it, please write relevant code by yourself.
 * */

int DArray_qsort(DArray *array, DArray_compare cmp)
{
	qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
	return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
	return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}
