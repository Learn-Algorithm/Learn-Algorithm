//
//  main.c
//  BPlusTree
//
//  Created by WolfLee on 4/1/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "b_plus_tree.h"

int main(int argc, const char * argv[])
{
    Node * root = NULL;

    root = Insert(root, 10, CreateRecord(10));
    root = Insert(root, 20, CreateRecord(20));
    root = Delete(root, 10);
    Lookup(root, 20);
    
    return 0;
}
