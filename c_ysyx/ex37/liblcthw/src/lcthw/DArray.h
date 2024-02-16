#ifndef _DArray_H
#define _DArray_H

#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

typedef struct DArray
{
    int end;                // 数组的当前大小，数组中元素的数量
    int max;                // 数组的最大容量
    size_t element_size;    // 数组中每个元素的大小
    size_t expand_rate;     // 数组扩展时的扩展速率
    void **contents;        // 一个指向void*类型的指针数组，用于存储元素的实际数据
                            // void **允许我们在同一个数组中存储不同的数据类型
} DArray;

// 创建一个新的动态数组
extern DArray *DArray_create(size_t element_size, size_t initial_max);

// 销毁动态数组
extern void DArray_destroy(DArray *array);

// 清空动态数组
extern void DArray_clear(DArray *array);

// 扩展动态数组
extern int DArray_expand(DArray *array);

// 收缩动态数组
extern int DArray_contract(DArray *array);

// 将元素追加到动态数组的末尾
extern int DArray_push(DArray *array, void *el);

// 从动态数组中移除并返回最后一个元素
extern void *DArray_pop(DArray *array);

// 清空并销毁动态数组
extern void DArray_clear_destroy(DArray *array);

// 从动态数组中取得最后一个元素
#define DArray_last(A) ((A)->contents[(A)->end - 1])

// 从动态数组中取得第一个元素
#define DArray_first(A) ((A)->contents[0])

// 取得动态数组中的元素数量
#define DArray_end(A) ((A)->end)

// 取得动态数组中的元素数量
#define DArray_count(A) DArray_end(A)

// 取得动态数组的最大容量
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

// 在动态数组的特定索引位置设置一个元素
static inline void DArray_set(DArray *array, int i, void *el)
{
    check(i < array->max, "DArray attempt to set past max.");
    if (i > array->end)
    {
        array->end = i;
    }
    array->contents[i] = el;
error:
    return;
}

// 从动态数组的特定索引位置取得一个元素
static inline void *DArray_get(DArray *array, int i)
{
    check(i < array->max, "DArray attempt to get past max.");
    return array->contents[i];

error:
    return NULL;
}

// 从动态数组的特定索引位置移除一个元素
static inline void *DArray_remove(DArray *array, int i)
{
    void *el = array->contents[i];
    array->contents[i] = NULL;
    return el;
}

// 为动态数组中的一个新元素分配内存
static inline void *DArray_new(DArray *array)
{
    check(array->element_size > 0, "Can't use DArray_new on 0 size arrays.");
    return calloc(1, sizeof(array->element_size));

error:
    return NULL;
}

// 释放为一个元素分配的内存
#define DArray_free(E) free((E))

#endif

