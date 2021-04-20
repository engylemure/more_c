#ifndef LIB_LINKED_LIST_H
#define LIB_LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>

#define true 1;
#define false 0;

typedef struct listNode
{
    void *data;
    struct listNode *previous;
    struct listNode *next;
} ListNode;

typedef struct linkedList
{
    ListNode *head;
    ListNode *tail;
    int (*delete_node)(struct linkedList *list, void *to_be_deleted);
    int (*cmp)(const void *self, const void *other);
    char* (*fmt_node_data)(void *data);
    void (*print_node)(struct linkedList *list, void *to_be_printed, FILE* stream);
    void (*print)(struct linkedList *list, FILE* stream);
    void (*push)(struct linkedList *list, void *to_be_pushed);
    void *(*pop)(struct linkedList *list);
    void (*drop)(struct linkedList *list);
    void (*for_each)(struct linkedList *list, void (*cb)(void *data, int i, void* aux_arg), void* aux_arg);
    void (*drop_data)(void* data);
    int (*count)(struct linkedList *list);

} LinkedList;

LinkedList *initialize_list(char* (*fmt_data)(void *to_be_printed), void (*drop_data)(void* data));
ListNode* initialize_list_node(void *data);

void drop_list(LinkedList *list);

#endif