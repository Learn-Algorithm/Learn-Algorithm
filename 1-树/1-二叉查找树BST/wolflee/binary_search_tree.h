//
//  binary_search_tree.h
//  BinarySearchTree
//
//  Created by WolfLee on 2/22/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//

#ifndef BinarySearchTree_binary_search_tree_h
#define BinarySearchTree_binary_search_tree_h

typedef int KEY_TYPE;
typedef struct Node{
    KEY_TYPE key;
    struct Node* lchild;
    struct Node* rchild;
}Node, *Tree;

Tree CreateTree(KEY_TYPE value);
Tree InsertNode(Tree root, KEY_TYPE value);
Tree SearchNode(Tree root, KEY_TYPE value);
Tree DeleteNode(Tree root, KEY_TYPE value);
void InOrderTraverse(Tree root);

#endif
