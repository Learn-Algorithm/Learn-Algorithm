//
//  main.c
//  SplayTree
//
//  Created by WolfLee on 14-3-15.
//  Copyright (c) 2014年 WolfLee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "splay_tree.h"

int main(int argc, const char * argv[])
{
    Tree root = NULL;

    root = Insert(root, 13);
    root = Insert(root, 3);
    root = Insert(root, 21);
    root = Insert(root, 34);
    root = Insert(root, 5);
    root = Insert(root, 55);
    root = Insert(root, 2);
    root = Insert(root, 89);

    root = Splay(root, 3);

    InOrder(root);
    printf("\nKey of root now is: %d\n", root->key);

    return 0;
}
