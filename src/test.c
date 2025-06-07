#include <stdlib.h>
#include <string.h>   // for strcmp

typedef struct s_env {
    char         *key;
    char         *value;
    struct s_env *next;
}   t_env;

/*
 * Selection‐sort a singly linked list of t_env nodes by ASCII order of `key`.
 * After this, *env_head points to a brand‐new list in sorted order.
 */
void sort_list(t_env **env_head)
{
    t_env *orig_head = *env_head;  // “unsorted” portion
    t_env *sorted_head = NULL;       // “sorted” portion (we’ll build this up)
    t_env *sorted_tail = NULL;       // to append quickly
    t_env *min_node = NULL;
    t_env *min_prev = NULL;
    t_env *prev = NULL;
    t_env *curr = NULL;
    // Repeat until orig_head is empty
    while (orig_head != NULL)
    {
        // 1) Find the minimum‐key node in [orig_head ... end]
        min_node = orig_head;
        min_prev = NULL;

        prev = orig_head;
        curr = orig_head->next;
        while (curr != NULL)
        {
            if (strcmp(curr->key, min_node->key) < 0)// if curr is smaller
            {
                min_node = curr;
                min_prev = prev;
            }
            prev = curr;
            curr = curr->next;
        }
        // Now min_node points to the “smallest” key in the unsorted segment.
        // And min_prev is the node right before it (or NULL if min_node == orig_head).

        // 2) Unlink min_node from the orig_head list
        if (min_prev == NULL)
        {
            // min_node was at the very front
            orig_head = min_node->next;
        }
        else
        {
            // skip over min_node
            min_prev->next = min_node->next;
        }
        min_node->next = NULL;  // fully detach it

        // 3) Append min_node to the end of the “sorted” list
        if (sorted_head == NULL)
        {
            sorted_head = min_node;
            sorted_tail = min_node;
        }
        else
        {
            sorted_tail->next = min_node;
            sorted_tail = min_node;
        }
    }

    // All nodes are now in sorted_head. Replace the original head.
    *env_head = sorted_head;
}
