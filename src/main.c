#include <stdio.h>
#include <string.h>
#include "linked_list/linked_list.h"
#include "tree/tree.h"

char *fmt_str(void *data)
{
    char *str = malloc(strlen(data) + 1);
    strcpy(str, data);
    return str;
}

void checking_list()
{
    LinkedList *list = initialize_list(fmt_str, NULL);
    list->push(list, "Hello");
    list->push(list, "World");
    list->print(list, stdout);
    list->drop(list);
}

void checking_tree()
{
    Tree *tree = initialize_tree();
    tree->print(tree, stdout);
    tree->insert_node(tree, initialize_tree_node("Hello", fmt_str, NULL));
    tree->print(tree, stdout);
    TreeNode *node = tree->node;
    TreeNode *worldNode = initialize_tree_node("World", fmt_str, NULL);
    worldNode->children->push(worldNode->children, initialize_tree_node("WorldLeaf", fmt_str, NULL));
    TreeNode *personNode = initialize_tree_node("Person", fmt_str, NULL);
    node->children->push(node->children, worldNode);
    node->children->push(node->children, personNode);
    FILE* tree_print_file = fopen("treeOutput", "w");
    tree->print(tree, stdout);
    tree->print(tree, tree_print_file);
    fclose(tree_print_file);
    tree->drop(tree);
}

int main()
{
    checking_list();
    checking_tree();
    return 0;
}