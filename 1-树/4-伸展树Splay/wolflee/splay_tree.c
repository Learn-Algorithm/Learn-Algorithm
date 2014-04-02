//
//  splay_tree.c
//  SplayTree
//
//  Created by WolfLee on 14-3-15.
//  Copyright (c) 2014年 WolfLee. All rights reserved.
//

#include "splay_tree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void Visit(Node* node)
{
    if(node != NULL) printf("%d ", node->key);
}

Node * Create(KEY_TYPE key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    assert(node);
    node->key = key;
    node->lchild = node->rchild = NULL;
    return node;
}

Node * Splay (Node *root, KEY_TYPE key)
{
    if (!root) return root;

    Node *temp, *left, *right, swap_node;
    swap_node.lchild = swap_node.rchild = NULL;
    left = right = &swap_node;

    for (;;) {
        if (key < root->key) {
            if (!root->lchild) break;

            if (key < root->lchild->key) {
                temp = root->lchild;
                root->lchild = temp->rchild;
                temp->rchild = root;
                root = temp;
                if (!root->lchild) break;
            }
            right->lchild = root;
            right = root;
            root = root->lchild;

        } else if (key > root->key) {
            if (!root->rchild) break;

            if (key > root->rchild->key) {
                temp = root->rchild;
                root->rchild = temp->lchild;
                temp->lchild = root;
                root = temp;
                if (!root->rchild) break;
            }
            left->rchild = root;
            left = root;
            root = root->rchild;
        } else {
            break;
        }
    }
    left->rchild = root->lchild;
    right->lchild = root->rchild;
    root->lchild = swap_node.rchild;
    root->rchild = swap_node.lchild;

    return root;
}

Node * Insert(Node *root, KEY_TYPE key)
{
    if (root != NULL) {
        root = Splay(root, key);
        if (root->key == key) {
            return root;
        }
    }

    Node *new_node = Create(key);
    if (!root) {
        return new_node;
    } else if (key < root->key) {
        new_node->lchild = root->lchild;
        new_node->rchild = root;
        root->lchild = NULL;
    } else if (key > root->key) {
        new_node->rchild = root->rchild;
        new_node->lchild = root;
        root->rchild = NULL;
    } else {
        free(new_node);
        return root;
    }

    return new_node;
}

Node * Delete(Node *root, KEY_TYPE key)
{
    Node *new_root;
    if (!root) return NULL;
    root = Splay(root, key);

    if (root->key == key) {
        if (!root->lchild) {
            new_root = root->rchild;
        } else {
            new_root = Splay(root->lchild, key);
            new_root->rchild = root->rchild;
        }
        free(root);
        return new_root;
    }

    return root;
}

void InOrder(Tree root)
{
    if (!root) return;

    InOrder(root->lchild);
    Visit(root);
    InOrder(root->rchild);
}
