//
//  b_plus_tree.h
//  BPlusTree
//
//  Created by WolfLee on 4/1/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//

#ifndef BPlusTree_b_plus_tree_h
#define BPlusTree_b_plus_tree_h

#include <stdbool.h>

#define ORDER 3

typedef struct Record {
    int value;
} Record;

typedef struct Node {
    void ** pointers;
    int * keys;
    struct Node * parent;
    bool is_leaf;
    int num_keys;
    struct Node * next; // Used for queue.
} Node;

void Lookup(Node * root, int key);
Record * CreateRecord(int value);
Node * Insert(Node * root, int key, Record * record);
Node * Delete(Node * root, int key);

#endif
