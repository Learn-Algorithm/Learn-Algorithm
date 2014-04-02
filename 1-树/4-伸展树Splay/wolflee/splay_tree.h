//
//  splay_tree.h
//  SplayTree
//
//  Created by WolfLee on 14-3-15.
//  Copyright (c) 2014年 WolfLee. All rights reserved.
//

#ifndef SplayTree_splay_tree_h
#define SplayTree_splay_tree_h

typedef int KEY_TYPE;

typedef struct Node {
    struct Node *lchild, *rchild;
    KEY_TYPE key;

}Node, *Tree;

Node * Splay(Node *root, KEY_TYPE key);
Node * Insert(Node *root, KEY_TYPE key);
Node * Delete(Node *root, KEY_TYPE key);
void InOrder(Tree root);
#endif
