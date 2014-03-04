//
//  main.c
//  AVLTree
//
//  Created by WolfLee on 2/28/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int main(int argc, const char * argv[])
{
    AVL* root = NULL;
    printf("Inserting some nodes ...\n");
    root = Insert(root, 0);
    root = Insert(root, 13);
    root = Insert(root, 3);
    root = Insert(root, 21);
    root = Insert(root, 34);
    root = Insert(root, 5);
    root = Insert(root, 55);
    root = Insert(root, 2);
    root = Insert(root, 89);

    printf("Now the tree is like: \n");
    InOrder(root);

    printf("\nDeleting some nodes ...\n");
    root = Delete(root, 89);
    root = Delete(root, 22);
    root = Delete(root, 0);

    printf("Now the tree is like: \n");
    InOrder(root);

    return 0;
}

