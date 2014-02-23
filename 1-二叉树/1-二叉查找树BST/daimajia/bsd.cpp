//
//  main.cpp
//  bst
//
//  Created by 代码家 on 14-2-22.
//  Copyright (c) 2014年 daimajia. All rights reserved.
//

#include <iostream>
#include <stdlib.h>


typedef struct Node{
    int key;
    struct Node* lchild = NULL;
    struct Node* rchild = NULL;
}Node,*Tree;

void insert(Tree*,int);

void create(Tree* tree){
    int input;
    while (scanf("%d",&input)!=EOF) {
        insert(tree, input);
    }
}

void insert(Tree* tree,int value){
    
    if(*tree == NULL){
        *tree = (Node*)malloc(sizeof(Node));
        (*tree)->key = value;
        return;
    }
    
    if((*tree)->key < value){
        //右子树
        if ((*tree)->rchild != NULL) {
            insert(&(*tree)->rchild, value);
        }else{
            Node* temp = (Node*)malloc(sizeof(Node));
            temp->key = value;
            (*tree)->rchild = temp;
        }
    }else{
        //左子树
        if((*tree)->lchild != NULL){
            insert(&(*tree)->lchild, value);
        }else{
            Node* temp = (Node*)malloc(sizeof(Node));
            temp->key = value;
            (*tree)->lchild = temp;
        }
    }
}

void inOrder(Tree tree){
    if(tree!=NULL){
        inOrder(tree->lchild);
        printf("%d ",tree->key);
        inOrder(tree->rchild);
    }
}

void Delete(Tree* tree,int value){
    if(tree == NULL){
        return;
    }
    if((*tree)->key < value){
        return Delete(&(*tree)->rchild, value);
    }else if((*tree)->key > value){
        return Delete(&(*tree)->lchild, value);
    }else if((*tree)->key == value){
        //左子树不为空，右子树为空
        if((*tree)->lchild != NULL && (*tree)->rchild == NULL){
            *tree = (*tree)->lchild;
            return;
        }
        //左子树为空，右子树不为空
        if((*tree)->lchild == NULL  && (*tree)->rchild != NULL){
            *tree = (*tree)->rchild;
            return;
        }
        //左右子树都不为空
        if((*tree)->lchild != NULL && (*tree)->rchild != NULL){
            Tree temp;
            temp = (*tree)->rchild;
            while (temp->lchild != NULL) {
                temp = temp->lchild;
            }
            temp->lchild = (*tree)->lchild;
            return;
        }
        //左右子树都不为空
        if((*tree)->lchild == NULL && (*tree)->rchild == NULL){
            *tree =  NULL;
        }
    }
    
}

bool search(Tree tree,int value){
    if(tree == NULL){
        return false;
    }
    if(tree->key == value){
        return true;
    }else if(tree->key < value){
        return search(tree->rchild, value);
    }else if(tree->key > value){
        return search(tree->lchild, value);
    }
    return false;
}

int main(int argc, const char * argv[])
{
    
    //每输入一个数，点击回车确定加入，以EOF符号结束(最好带有3或者4 用于下面的搜索测试)
    Tree tree = NULL;
    create(&tree);
    printf("排序:");
    inOrder(tree);
    if(search(tree, 3)){
        printf("find 3\n");
    }else{
        printf("does not find 3\n");
    }
    if(search(tree, 4)){
        printf("find 4\n");
    }else{
        printf("does not find 4\n");
    }
    Delete(&tree, 3);
    inOrder(tree);
    Delete(&tree, 4);
    inOrder(tree);
    return 0;
}

