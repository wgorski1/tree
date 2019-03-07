#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

// node type
struct _node;

typedef struct _node *node;

struct _node {
    int value;
    node left;
    node right;
    node parent;
    unsigned char position;
};

const unsigned char POS_LEFT = 'l';
const unsigned char POS_RIGHT = 'r';

const size_t NODE_SIZE = sizeof(struct _node);

// tree type
struct _tree {
    node head;
    unsigned long count;
};

const size_t TREE_SIZE = sizeof(struct _tree);

// FUNC

static node create_node(int value, node parent, unsigned char position) {
    node anode = malloc(NODE_SIZE);
    anode->left = anode->right = NULL;
    anode->value = value;
    anode->parent = parent;
    anode->position = position;
    
    return anode;
}

/*
 * a
 *   b
 *     c
 * 
 * becomes
 * 
 *   b
 * a   c
 * 
 * topnode is a
 */
static void rotate_straight_left(tree atree, node topnode) {
    node newtopnode = topnode->right;
    
    if (topnode->position == POS_LEFT) {
        newtopnode->position = POS_LEFT;
        topnode->parent->left = newtopnode;
    } else if (topnode->position == POS_RIGHT) {
        topnode->parent->right = newtopnode;
    } else {
        newtopnode->position = 0;
        atree->head = newtopnode;
    }
    
    newtopnode->parent = topnode->parent;
    
    newtopnode->left = topnode;
    
    topnode->right = NULL;
    
    topnode->parent = newtopnode;
    
    topnode->position = POS_LEFT;
}

/*
 *     a
 *   b
 * c
 * 
 * becomes
 * 
 *   b
 * c   a
 * 
 * topnode is a
 */
static void rotate_straight_right(tree atree, node topnode) {
    node newtopnode = topnode->left;
    
    if (topnode->position == POS_LEFT) {
        topnode->parent->left = newtopnode;
    } else if (topnode->position == POS_RIGHT) {
        newtopnode->position = POS_RIGHT;
        topnode->parent->right = newtopnode;
    } else {
        newtopnode->position = 0;
        atree->head = newtopnode;
    }
    
    newtopnode->parent = topnode->parent;
    
    newtopnode->right = topnode;
    
    topnode->left = NULL;
    
    topnode->parent = newtopnode;
    
    topnode->position = POS_RIGHT;
}

static void rebalance_tree(tree atree, node bad_node) {
    printf("Rebalancing\n");
    
    // direct parent must have only one child, since the tree was balanced before
    // jump straight to grandparent
    node parent = bad_node->parent;
    node grandparent = parent->parent;
    
    // easiest scenario - grandparent has empty slot
    if (bad_node->position == POS_LEFT && parent->position == POS_LEFT && !grandparent->right) {
        rotate_straight_right(atree, grandparent);
    } else if (bad_node->position == POS_RIGHT && parent->position == POS_RIGHT && !grandparent->left) {
        rotate_straight_left(atree, grandparent);
    }
}

extern tree create_tree() {
    tree atree = malloc(TREE_SIZE);
    atree->head = NULL;
    atree->count = 0;
    
    return atree;
}

extern void add_value(tree atree, int value) {
    node prev_node = NULL;
    node *cur_node = &atree->head;
    unsigned short level = 1;
    unsigned char position = 0;
    
    while(*cur_node) {
        prev_node = *cur_node;
        
        if (value < (*cur_node)->value) {
            cur_node = &(*cur_node)->left;
            position = POS_LEFT;
        } else {
            cur_node = &(*cur_node)->right;
            position = POS_RIGHT;
        }
        
        level++;
    }
    
    *cur_node = create_node(value, prev_node, position);
    
    atree->count++;
    
    if (!(atree->count >> (level - 1))) {
        rebalance_tree(atree, *cur_node);
    }
}

static void print_node(node anode, const char *dir, short level) {
    if (anode->left) {
        print_node(anode->left, "l", level + 1);
    }
    
    printf("%s%i value %i\n", dir, level, anode->value);
    
    if (anode->right) {
        print_node(anode->right, "r", level + 1);
    }
}

extern void print_tree(tree atree) {
    print_node(atree->head, "c", 1);
    printf("Count %lu\n", atree->count);
}

