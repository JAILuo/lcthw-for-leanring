#include <lcthw/DArray_algos.h>
#include <stdlib.h>
#include <stdio.h> 

// 合并两个有序数组
static void merge(void **array, int left, int mid, int right, void **temp, DArray_compare cmp)
{
	int i = left;		// 标记左半区第一个未排序的元素
	int j = mid + 1;	// 标记右半区第一个未排序的元素
	int k = 0;			// 临时数组的下标

	//合并
	while(i <= mid && j <= right)
	{
		if(cmp(array[i], array[j]) <= 0)
		{
			temp[k++] = array[i++];
		}else
		{
			temp[k++] = array[j++];
		}
	}

	// 合并左半区剩余元素
	while(i <= mid)
	{
		temp[k++] = array[i++];
	}

	// 合并右半区剩余元素
	while(j <= right)
	{
		temp[k++] = array[j++];
	}

	// 解放降临时数组合并后复制回原来的数组
	for(i = 0; i < k; i++)
	{
		array[left + i] = temp[i];
	}
}

// 归并排序
static void mergesort_helper(void **array, int left, int right, void **temp, DArray_compare cmp)
{
	if(left >= right)
	{
		return;
	}

	int mid = left + (right - left) / 2;
	mergesort_helper(array, left, right, temp, cmp);
	mergesort_helper(array, left, right, temp, cmp);
	merge(array, left, mid, right, temp, cmp);
}

void mergesort(void **array, int n, size_t size, DArray_compare cmp)
{
	void **temp = (void **)malloc(n * size);
	check_mem(temp);

	mergesort_helper(array, 0, n - 1, temp, cmp);
	free(temp);

error:
	if(temp != NULL)
	{
		free(temp);
		temp = NULL;
	}
}


// 调整堆
static void heapify(void **array, int n, int i, DArray_compare cmp)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if(left < n && cmp(array[left], array[largest]) > 0)
	{
		largest = left;
	}

	if(right < n && cmp(array[right], array[largest]) > 0)
	{
		largest = right;
	}

	if(largest != i)
	{
		void *temp = array[i];
		array[i] = array[largest];
		array[largest] = temp;
		heapify(array, n, largest, cmp);
	}
}

// 堆排序
void heapsort(void **array, int n, size_t size, DArray_compare cmp)
{
	int i = 0;
	for(i = n / 2 -1; i >= 0; i--)
	{
		heapify(array, n, i, cmp);
	}

	for(i = n - 1; i > 0; i--)
	{
		void *temp = array[0];
		array[0] = array[i];
		array[i] = temp;
		heapify(array, i, 0, cmp);
	}
}

int DArray_qsort(DArray *array, DArray_compare cmp)
{
	qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
	heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
 {
	mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}
