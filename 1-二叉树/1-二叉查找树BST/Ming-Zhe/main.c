//
//  main.c
//  BST
//
//  Created by Ming-Zhe on 14-2-21.
//  Copyright (c) 2014年 Ming-Zhe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bst_node{
    int data;
    struct bst_node* lchild;
    struct bst_node* rchild;
}bst_node,*bstree;

bst_node *create(int key) {
    bst_node *newnode;
    newnode = malloc(sizeof(bst_node));
    if( newnode == NULL) {
    return NULL;
    }
    newnode->data = key;
    newnode->rchild = newnode->lchild = NULL;
    return newnode;
}

bst_node* searchNode(int key, bstree T){
    while(T != NULL) {
        if(key < T->data)      // 向左
            T = T->lchild;
        else if(key > T->data) // 向右
            T = T->rchild;
        else                   // 找到
            return T;
    }
    return NULL; // 失败
}

bool insertNode(int key, bst_node *root){
    bst_node* pre;
    bst_node* curr;
    
    curr = root;
    
    while(curr != NULL) {
        if(key < curr->data) { // 向左
            pre = curr;
            curr = curr->lchild;
        }
        else if(key > curr->data) { // 向右
            pre = curr;
            curr = curr->rchild;
        }
        else // 失败 
            return false;
    }
    
    curr = malloc(sizeof(bst_node)); // 插入
    curr->data = key;
    curr->lchild = curr->rchild = NULL;
    if(pre == NULL)
        root = curr;
    else{
        
        if (curr->data < pre->data) {
            pre->lchild=curr;
        }
        else{
            pre->rchild=curr;
        }
    }
    return true;
}

bool deleteNode(bstree T, int key){
    bst_node* par = NULL;
    bst_node* tmp;
    while(T != NULL) {
        if(key < T->data) { // 向左
            par = T;
            T = T->lchild;
        }
        else if(key > T->data) { // 向右
            par = T;
            T = T->rchild;
        }
        else { // 找到了
            if(NULL==T->lchild && NULL==T->rchild) { // 叶子结点
                if(par == NULL) { // 根结点
                    free (T);
                    T = NULL;
                }
                else { // 非根结点
                    (par->lchild==T)?(par->lchild=NULL):(par->rchild=NULL);
                    free(T);
                    T = NULL;
                }
            }
            else if(NULL!=T->lchild && NULL==T->rchild) { // 只有左孩子
                if(par == NULL) { // 根结点
                    tmp = T;
                    T = T->lchild;
                    free(tmp);
                }
                else { // 非根结点
                    (par->lchild==T)?(par->lchild=T->lchild):(par->rchild=T->lchild);
                    free(T);
                }
            }
            else if(NULL!=T->rchild && NULL==T->lchild) { // 只有右孩子
                if(par == NULL) { // 根结点
                    tmp = T;
                    T = T->rchild;
                    free(tmp);
                }
                else { // 非根结点
                    (par->lchild==T)?(par->lchild=T->rchild):(par->rchild=T->rchild);
                    free(T);
                }
            }
            else { // 既有左孩子也有右孩子
                bst_node* leftNode = T;
                while(leftNode->rchild != NULL) {
                    par = leftNode;
                    leftNode = leftNode->rchild;
                }
                // 交换leftNode与node
                int swapValue = leftNode->data;
                leftNode->data = T->data;
                T->data = swapValue;
                // 删除leftNode，parent肯定不为空 
                (par->lchild==T)?(par->lchild=NULL):(par->rchild=NULL);
                free(T);
            }
        }
    }
    return false; // 失败
}

void InOrder(bst_node *root) {
    if(root == NULL) {
        return; }
    InOrder(root->lchild);
    printf("%d\t",root->data);
    InOrder(root->rchild);
}

int main(int argc, const char * argv[])
{
    
    bst_node *root = NULL;
    bst_node *tmp = NULL;
    root = create(35);
    printf("Hello, World!\n");
    InOrder(root);
//    if(root != NULL){
//        root->lchild = create(22);
//    }
    
    // insert code here...
    
    insertNode(49, root);
    insertNode(12, root);
    printf("Hello, World!\n");
    InOrder(root);
    
    tmp = searchNode(12, root);
    printf("\n%d\n",tmp->data);
    
    deleteNode(root,49);
    InOrder(root);
    return 0;
}

