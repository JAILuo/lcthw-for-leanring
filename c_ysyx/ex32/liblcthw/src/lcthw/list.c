#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <assert.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur) 
    {
        if(cur->prev)
	{
	    free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}


void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur)
    {   
	free(cur->value);
    }
}


void List_clear_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur)
    {
	free(cur->value);
	if(cur->prev)
	{
	    free(cur->prev);
	}
    }

    free(list->last);
    free(list);
}


void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->last == NULL)
    {
	list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    assert(list && "List pointer is NULL"); //确保List *list不为NULL

    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL)
    {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    assert(list && "List pointer is NULL"); //确保List *list不为NULL

    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    assert(list && "List pointer is NULL");  // 断言：确保List *list不为NULL
    assert(list->count > 0 && "List count is less than or equal to 0");  // 断言：确保count大于0
    assert(node && "Node pointer is NULL");  // 断言：确保node不为NULL

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if(node == list->first && node == list->last)
    {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first)
    {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last)
    {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else 
    {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

