//
//  avl.c
//  AVLTree
//
//  Created by WolfLee on 2/28/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//

#include "avl.h"

#include <stdio.h>
#include <stdlib.h>


void Visit(AVL* node)
{
    if(node != NULL) printf("%d ", node->key);
}

AVL* Minimum(AVL* node)
{
    if (!node) return NULL;

    while (node->lchild) {
        node = node->lchild;
    }
    return node;
}

AVL* Maximum(AVL* node)
{
    if (!node) return NULL;

    while (node->rchild) {
        node = node->rchild;
    }
    return node;
}

int Height(AVL* node)
{
    return !node ? -1 : node->height;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

int BumpHeight(AVL* node)
{
    return Max(Height(node->lchild), Height(node->rchild)) + 1;
}

AVL* LL_Rotate(AVL* k2)
{
    AVL* k1 = k2->lchild;
    k2->lchild = k1->rchild;
    k1->rchild = k2;
    k2->height = BumpHeight(k2);
    k1->height = BumpHeight(k1);
    return k1;
}

AVL* RR_Rotate(AVL* k2)
{
    AVL* k1 = k2->rchild;
    k2->rchild = k1->lchild;
    k1->lchild = k2;
    k2->height = BumpHeight(k2);
    k1->height = BumpHeight(k1);
    return k1;
}

AVL* LR_Rotate(AVL* k3)
{
    k3->lchild = RR_Rotate(k3->lchild);
    return LL_Rotate(k3);
}

AVL* RL_Rotate(AVL* k3)
{
    k3->rchild = LL_Rotate(k3->rchild);
    return RR_Rotate(k3);
}

AVL* Insert(AVL* root, KEY_TYPE key)
{
    if (!root) {
        root = (AVL *)malloc(sizeof(AVL));
        root->lchild = root->rchild = NULL;
        root->key = key;
    } else if (key < root->key) {
        root->lchild = Insert(root->lchild, key);
        if (Height(root->lchild) - Height(root->rchild) == 2) {
            if (key < root->lchild->key) {
                root = LL_Rotate(root);
            } else {
                root = LR_Rotate(root);
            }
        }
    } else if (key > root->key) {
        root->rchild = Insert(root->rchild, key);
        if (Height(root->rchild) - Height(root->lchild) == 2) {
            if (key > root->rchild->key) {
                root = RR_Rotate(root);
            } else {
                root = RL_Rotate(root);
            }
        }
    }
    root->height = BumpHeight(root);
    return root;
}

AVL* Delete(AVL* root, KEY_TYPE key)
{
    if (root == NULL) return NULL;
    if (key < root->key) {
        root->lchild = Delete(root->lchild, key);
        if (Height(root->rchild) - Height(root->lchild) == 2) {
            if (Height(root->rchild->lchild) > Height(root->rchild->rchild)) {
                root = RL_Rotate(root);
            } else {
                root = RR_Rotate(root);
            }
        } else {
            root->height = BumpHeight(root);
        }
    } else if (key > root->key) {
        root->rchild = Delete(root->rchild, key);
        if (Height(root->lchild) - Height(root->rchild) == 2) {
            if (Height(root->lchild->rchild) > Height(root->lchild->lchild)) {
                root = LR_Rotate(root);
            } else {
                root = LL_Rotate(root);
            }
        } else {
            root->height = BumpHeight(root);
        }
    } else {
        if (root->lchild && root->rchild) {
            if (Height(root->lchild)) {
                root->key = Maximum(root->lchild)->key;
                root->lchild = Delete(root->lchild, root->key);
            } else {
                root->key = Minimum(root->rchild)->key;
                root->rchild = Delete(root->rchild, root->key);
            }
        } else {
            AVL* node_to_delete = root;
            root = root->lchild ? root->lchild : root->rchild;
            free(node_to_delete);
        }
    }
    return root;
}

void InOrder(AVL* root)
{
    if (!root) return;

    InOrder(root->lchild);
    Visit(root);
    InOrder(root->rchild);
}
