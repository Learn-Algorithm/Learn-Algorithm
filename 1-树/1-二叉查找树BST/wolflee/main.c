//
//  main.c
//  BinarySearchTree
//
//  Created by WolfLee on 2/22/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"

int main(int argc, const char * argv[])
{

    Tree root = NULL;

    printf("Create a tree\n");
    root = CreateTree(0);

    printf("Insert some nodes: 13, 3, 21, 34, 5, 55, 2, 89, 8\n");
    InsertNode(root, 13);
    InsertNode(root, 3);
    InsertNode(root, 21);
    InsertNode(root, 34);
    InsertNode(root, 5);
    InsertNode(root, 55);
    InsertNode(root, 2);
    InsertNode(root, 89);
    InsertNode(root, 8);

    printf("Search some nodes: 21, 33\n");
    SearchNode(root, 21);
    SearchNode(root, 33);

    printf("Delete some nodes: 89, 21, 0\n");
    root = DeleteNode(root, 89);
    root = DeleteNode(root, 21);
    root = DeleteNode(root, 0);

    printf("Search some nodes: 21\n");
    SearchNode(root, 21);

    printf("In Order Display\n");
    InOrderTraverse(root);

    return 0;
}
