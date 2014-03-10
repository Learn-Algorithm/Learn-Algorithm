//
//  binary_search_tree.c
//  BinarySearchTree
//
//  Created by WolfLee on 2/22/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//

#include "binary_search_tree.h"

#include <stdio.h>
#include <stdlib.h>

void Visit(Tree node)
{
    if(node != NULL) printf("%d ", node->key);
}

Tree Minimum(Tree root)
{
    if (root == NULL) return NULL;

    while (root->lchild) {
        root = root->lchild;
    }
    return root;
}

Tree Maximum(Tree root)
{
    if (root == NULL) return NULL;

    while (root->rchild) {
        root = root->rchild;
    }
    return root;
}

void LinkToChild(Tree* node, Tree child)
{
    Tree tmp = *node;
    *node = child;
    free(tmp);
}

Tree CreateTree(KEY_TYPE key)
{
    Tree root = (Tree)malloc(sizeof(Node));
    root->key = key;
    root->lchild = root->rchild = NULL;

    return root;
}

Tree InsertNode(Tree root, KEY_TYPE value)
{
    if (root == NULL) {
        return CreateTree(value);
    } else {
        if (value < root->key) {
            root->lchild = InsertNode(root->lchild, value);
        } else if (value > root->key) {
            root->rchild = InsertNode(root->rchild, value);
        }
        return root;
    }
}

Tree SearchNode(Tree root, KEY_TYPE value)
{
    if (root == NULL) {
        printf("Not found, key: %d\n", value);
        return NULL;
    }

    if (root->key == value) {
        printf("Found the node, key: %d\n", root->key);
        return root;
    } else if (value > root->key) {
        return SearchNode(root->rchild, value);
    } else {
        return SearchNode(root->lchild, value);
    }
}

Tree DeleteNode(Tree root, KEY_TYPE value)
{
    if (root == NULL) {
        return NULL;
    }
    if (root->key == value) {
        if (root->lchild == NULL) {
            LinkToChild(&root, root->rchild);
        } else if (root->rchild == NULL) {
            LinkToChild(&root, root->lchild);
        } else {
            Tree maximum = Maximum(root->lchild);
            root->key = maximum->key;
            root->lchild = DeleteNode(root->lchild, root->key);
        }
    } else if (value < root->key) {
        root->lchild = DeleteNode(root->lchild, value);
    } else if (value > root->key) {
        root->rchild = DeleteNode(root->rchild, value);
    }
    return root;
}

void InOrderTraverse(Tree root)
{
    if (root == NULL) return;

    InOrderTraverse(root->lchild);
    Visit(root);
    InOrderTraverse(root->rchild);
}
