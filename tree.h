#ifndef __tree_h
#define __tree_h

struct _tree;

typedef struct _tree *tree;

tree create_tree();

void add_value(tree atree, int value);

void print_tree(tree atree);

#endif