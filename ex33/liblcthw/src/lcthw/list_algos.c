#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

// Use inline to reduce the overhaed of function calls
void ListNode_swap(ListNode *a, ListNode *b)
{
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp)
{
    int sorted = 1;

    if (List_count(list) <= 1)
    {
        return 0; // already sorted
    }

    do
    {
        sorted = 1;
        LIST_FOREACH(list, first, next, cur)
        {
            if (cur->next) // The first time i wrote, i forgot about this check !!! causing enter the empty pointer and segmention fault
            {
                if (cmp(cur->value, cur->next->value) > 0)
                {
                    ListNode_swap(cur, cur->next);
                    sorted = 0;
                }
            }
        }
    } while (!sorted);

    return 0;
}

/* Version 1
 *
 * Implement basic functions.
 * Optimization of delasts is not taken into account.
 */

List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
    void *value = NULL;

    while (List_count(left) > 0 || List_count(right) > 0) // merge
    {
        if (List_count(left) > 0 && List_count(right) > 0)
        {
            if (cmp(List_first(left), List_first(right)) <= 0)
            {
                value = List_shift(left);
            }
            else
            {
                value = List_shift(right);
            }
            List_push(result, value);
        }
        else if (List_count(left) > 0) // merge the remaining elements in the left half
        {
            value = List_shift(left);
            List_push(result, value);
        }
        else if (List_count(right) > 0) // merge the remaing elements in the right half
        {
            value = List_shift(right);
            List_push(result, value);
        }
    }

    return result;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    // only one element
    if (List_count(list) <= 1)
    {
        return list;
    }

    List *left = List_create();
    List *right = List_create();
    // Find the middle point
    int mid = List_count(list) / 2;

    // Spilt the left(right) list
    LIST_FOREACH(list, first, next, cur)
    {
        if (mid > 0)
        {
            List_push(left, cur->value); // Add elements to the left half
        }
        else
        {
            List_push(right, cur->value); // Add elements to the right half
        }

        mid--;
    }

    // Constant recursive split
    // Recursively divides the left half
    List *sort_left = List_merge_sort(left, cmp);
    // Recursively divides the right half
    List *sort_right = List_merge_sort(right, cmp);

    // Avoid memory leaks
    if (sort_left != left)
        List_destroy(left);
    if (sort_right != right)
        List_destroy(right);

    // Sort and merge
    return List_merge(sort_left, sort_right, cmp);
}

/* Version 2
 *
 * Make simple optimizations.
 *
 */
// List *List_merge(List *left, List *right, List_compare cmp)
// {
//     List *result = List_create();
//     ListNode *result_last = NULL;

//     while (left != NULL && right != NULL) // merge
//     {
//         if (cmp(List_first(left), List_first(right)) <= 0)
//         {
//             if (result_last == NULL)
//             {
//                 result->first = left->first;
//             }
//             else
//             {
//                 result_last->next = left->first;
//             }
//             result_last = left->last;
//             left = left->last->next;
//         }
//         else
//         {
//             if (result_last == NULL)
//             {
//                 result->first = right->first;
//             }
//             else
//             {
//                 result_last->next = right->first;
//             }
//             result_last = right->last;
//             right = right->last->next;
//         }
//     }

//     if (left != NULL)
//     {
//         if (result_last == NULL)
//         {
//             result = left;
//         }
//         else
//         {
//             result_last->next = left->first;
//             result_last = left->last;
//         }
//     }
//     if (right != NULL)
//     {
//         if (result_last == NULL)
//         {
//             result = right;
//         }
//         else
//         {
//             result_last->next = right->first;
//             result_last = right->last;
//         }
//     }

//     return result;
// }

// List *List_merge_sort(List *list, List_compare cmp)
// {
//     if (list == NULL || list->first == NULL || list->first->next == NULL)
//     {
//         return list;
//     }

//     ListNode *slow = list->first;
//     ListNode *fast = list->first->next;

//     while (fast != NULL)
//     {
//         fast = fast->next;
//         if (fast != NULL)
//         {
//             slow = slow->next;
//             fast = fast->next;
//         }
//     }

//     List *left = List_create();
//     List *right = List_create();
//     left->first = list->first;
//     left->last = slow;
//     right->first = slow->next;
//     right->last = list->last;
//     slow->next = NULL;

//     left = List_merge_sort(left, cmp);
//     right = List_merge_sort(right, cmp);

//     return List_merge(left, right, cmp);
// }
