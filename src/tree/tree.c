#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "../linked_list/linked_list.h"

TreeNode *initialize_tree_node(void *data, char *(*fmt_data)(void *to_be_printed), void (*drop_data)(void *data))
{
    TreeNode *tree_node = malloc(sizeof(TreeNode));
    void drop_tree_node(TreeNode * node);
    void print_tree_node(TreeNode* node, FILE* stream);
    tree_node->drop = *drop_tree_node;
    tree_node->print = *print_tree_node;
    tree_node->fmt_data = fmt_data;
    tree_node->data = data;
    tree_node->drop_data = drop_data;
    tree_node->parent = NULL;
    tree_node->children = initialize_list(fmt_data, tree_node->drop);
    return tree_node;
}

Tree *initialize_tree()
{
    Tree *tree = malloc(sizeof(Tree));
    TreeNode *insert_node_on_tree(Tree * self, TreeNode * node);
    void drop_tree(Tree *self);
    void print_tree(Tree *self, FILE* stream);
    tree->node = NULL;
    tree->insert_node = *insert_node_on_tree;
    tree->drop = *drop_tree;
    tree->print = *print_tree;
    return tree;
}

TreeNode *insert_node_on_tree(Tree *self, TreeNode *node)
{
    TreeNode *old_node = self->node;
    self->node = node;
    return old_node;
}

void print_tree_node(TreeNode *self, FILE* stream) {
    char* data_formatted = self->fmt_data(self->data);
    LinkedList* children = self->children;
    fprintf(stream, "(%s", data_formatted);
    if (children->count(children)) {
        fprintf(stream, "->{");
        void print_tree_node_child(TreeNode* child, int i, FILE* stream);
        children->for_each(children, print_tree_node_child, stream);
        fprintf(stream, "}");
    }
    free(data_formatted);
    fprintf(stream, ")");
}

void print_tree_node_child(TreeNode* child, int i, FILE* stream) {
    child->print(child, stream);
}

void print_tree(Tree* self, FILE* stream) {
    TreeNode *node = self->node;
    if (node != NULL) {
        node->print(node, stream);
    } else {
        fprintf(stream, "(nil)");
    }
    fprintf(stream, "\n");
}

void drop_tree_node(TreeNode *self)
{
    self->children->drop(self->children);
    if (self->drop_data != NULL) {
        self->drop_data(self->data);
    }
    free(self);
}

void drop_tree(Tree* self) {
    self->node->drop(self->node);
    free(self);
}