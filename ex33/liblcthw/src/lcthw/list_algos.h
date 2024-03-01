#ifndef _lcthw_List_algos_h
#define _lcthw_List_algos_h

#include <lcthw/list.h>

/*
 * The use of function pointer aims to allows flexibilty in sorting types of data,
 * not just limited to strings and not limited to using "strcmp()" only.
 *
 * Besides, void * is more universal as a parameter type because void can point an type fo data,
 * not just char type(i wrote char *first).
 * It can provide greater flexibility and generality.
 */
typedef int (*List_compare)(const void *str1, const void *str2);

void ListNode_swap(ListNode *a, ListNode *b);
int List_bubble_sort(List *list, List_compare cmp);

List *List_merge(List *left, List *right, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

#endif
