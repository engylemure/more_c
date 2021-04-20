#ifndef LIB_TREE_H
#define LIB_TREE_H

#include "../linked_list/linked_list.h"

typedef struct treeNode
{
    void *data;
    struct treeNode *parent;
    LinkedList *children;
    void (*drop_data)(void *data);
    void (*drop)(struct treeNode *self);
    char *(*fmt_data)(void *data);
    void (*print)(struct treeNode *self, FILE* stream);
} TreeNode;

typedef struct tree
{
    TreeNode *node;
    TreeNode *(*insert_node)(struct tree *self, TreeNode *node);
    void (*drop)(struct tree *self);
    void (*print)(struct tree *self, FILE* stream);
} Tree;

TreeNode *initialize_tree_node(void *data, char *(*fmt_data)(void *to_be_printed), void (*drop_data)(void *data));
Tree *initialize_tree();

#endif