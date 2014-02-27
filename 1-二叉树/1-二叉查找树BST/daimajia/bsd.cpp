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
    
    Tree temp = *tree;
    Tree parent;
    while(temp != NULL && temp->key != value){
        parent = temp;
        if(temp->key < value){
            temp = temp->rchild;
        }else{
            temp = temp->lchild;
        }
    }
    if(temp == NULL){
        return;
    }
    Node* toFree;
    toFree = temp;
    if(temp->lchild != NULL && temp->rchild == NULL){
        //左子树不为空，右子树为空
        temp = temp->lchild;
    }else if(temp->lchild == NULL && temp->rchild !=NULL){
        //左子树为空，右子树不为空
        temp = temp->rchild;
    }else if(temp->lchild != NULL && temp->rchild != NULL){
        //左右子树均不为空
        Node* loop;
        loop = temp->rchild;
        while (loop->lchild!=NULL) {
            loop = loop->lchild;
        }
        loop->lchild = temp->lchild;
        temp = temp->lchild;
    }else{
        //左右子树均为空
        if(parent->lchild == temp){
            parent->lchild = NULL;
        }else if(parent->rchild == temp){
            parent->rchild = NULL;
        }
    }
    free(toFree);
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
    Delete(&tree, 8);
    inOrder(tree);
    Delete(&tree, 4);
    inOrder(tree);
    insert(&tree, 8);
    inOrder(tree);
    return 0;
}

