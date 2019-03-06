#ifndef __tree_h
#define __tree_h

struct tree;

struct tree *create_tree();

void add_value(struct tree *atree, int value);

void print_tree(struct tree *atree);

#endif