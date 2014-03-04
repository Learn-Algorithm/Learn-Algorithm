//
//  main.cpp
//  AVL
//
//  Created by 代码家 on 14-2-24.
//  Copyright (c) 2014年 daimajia. All rights reserved.
//

#include <iostream>
#include <stdlib.h>

typedef int KEY_TYPE;
typedef struct AVL{
    KEY_TYPE key;
    int height;
    struct AVL* lchild;
    struct AVL* rchild;
}AVL,*AVLTree;

void RR_Rotate(AVLTree&);
void LL_Rotate(AVLTree&);
void LR_Rotate(AVLTree&);
void RL_Rotate(AVLTree&);

void Insert(AVLTree &root, KEY_TYPE key);
void InOrder(AVL* root);

void Create(AVLTree& root){
    int input;
    while (scanf("%d",&input) != EOF) {
        Insert(root, input);
    }
    rewind(stdin);
}

int max(int a,int b){
    return a>b?a:b;
}

int GetHeight(const AVLTree &root){
    return root==NULL?-1:root->height;
}


void LL_Rotate(AVLTree &root){
    AVLTree pivot = root->lchild;
    root->lchild = pivot->rchild;
    pivot->rchild = root;
    
    root->height = max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
    pivot->height = max(GetHeight(pivot->lchild), GetHeight(pivot->rchild)) + 1;
    
    root = pivot;
    printf("LL_Rotate\n");
}

void RR_Rotate(AVLTree &root){
    AVLTree pivot = root->rchild;
    root->rchild = pivot->lchild;
    pivot->lchild = root;
    
    root->height = max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
    pivot->height = max(GetHeight(pivot->rchild), GetHeight(pivot->lchild)) + 1;
    
    root = pivot;
    printf("RR_Rotate\n");
}

void LR_Rotate(AVLTree &root){
    RR_Rotate(root->lchild);
    LL_Rotate(root);
    printf("LR_Rotate\n");
}

void RL_Rotate(AVLTree &root){
    LL_Rotate(root->rchild);
    RR_Rotate(root);
    printf("RL_Rotate\n");
}

void Insert(AVLTree &root,KEY_TYPE key){
    if (root == NULL) {
        root = (AVL*)malloc(sizeof(AVL));
        root->key = key;
        root->lchild = NULL;
        root->rchild = NULL;
        root->height = 0;
        return;
    }else{
        if (root->key < key) {
            Insert(root->rchild, key);
        }else if(root->key > key){
            Insert(root->lchild, key);
        }
        root->height = max(GetHeight(root->lchild), GetHeight(root->rchild)) + 1;
        
        if (GetHeight(root->lchild) - GetHeight(root->rchild) == 2) {
            if (root->lchild->key < key) {
                LR_Rotate(root);
            }else{
                LL_Rotate(root);
            }
        }else if (GetHeight(root->rchild) - GetHeight(root->lchild) == 2) {
            if (root->rchild->key < key) {
                RR_Rotate(root);
            }else{
                RL_Rotate(root);
            }
        }
    }
}

void Delete(AVLTree &root,KEY_TYPE key){
    
    if (root == NULL) {
        return;
    }
    
    if (root->key == key) {
        AVLTree toFree = root;
        if (root->lchild == NULL && root->rchild == NULL) {
            root = NULL;
        }else if(root->lchild != NULL && root->rchild != NULL){
            AVLTree loop = root->rchild;
            while (loop->lchild != NULL) {
                loop = loop->lchild;
            }
            root->key = loop->key;
            Delete(root->rchild, loop->key);
        }else{
            if (root->lchild!=NULL) {
                root = root->lchild;
            }else{
                root = root->rchild;
            }
        }
        free(toFree);
    }else if(root->key < key){
        Delete(root->rchild, key);
    }else{
        Delete(root->lchild, key);
    }

    if(root==NULL){
        return;
    }
    
    root->height = max(GetHeight(root->lchild),GetHeight(root->rchild)) + 1;
  
    if (GetHeight(root->lchild) - GetHeight(root->rchild) == 2) {
        if (root->lchild->key < key) {
            LR_Rotate(root);
        }else{
            LL_Rotate(root);
        }
    }else if (GetHeight(root->rchild) - GetHeight(root->lchild) == 2) {
        if (root->rchild->key < key) {
            RR_Rotate(root);
        }else{
            RL_Rotate(root);
        }
    }

}

void InOrder(AVLTree root){
    if (root!=NULL) {
        InOrder(root->lchild);
        printf("%d ",root->key);
        InOrder(root->rchild);
    }
}


int main(int argc, const char * argv[])
{
    
    AVLTree tree = NULL;
    Create(tree);
    InOrder(tree);
    while (true) {
        int td;
        scanf("%d",&td);
        Delete(tree, td);
    }
    

    return 0;
}

