#include <stdio.h>

#include "tree.h"

void run(int *vals, int size) {
    struct tree *atree = create_tree();

    for (int i = 0; i < size; i++) {
        add_value(atree, vals[i]);
    
        print_tree(atree);
        printf("---------------\n");
    }
}

void test_straight_rotation() {
    int vals1[] = {4, 3, 2};
    
    run(vals1, 3);
    
    int vals2[] = {2, 3, 4};
    
    run(vals2, 3);
    
    int vals3[] = {5, 6, 7, 8, 9};
    
    run(vals3, 5);
    
    int vals4[] = {9, 8, 7, 6, 5};
    
    run(vals4, 5);
}

/*int vals[] = {5, 2, 8, 7, 3, 4, 1, 6};
run(vals, 8);*/

int main(void) {
    test_straight_rotation();
    
    return 0;
}