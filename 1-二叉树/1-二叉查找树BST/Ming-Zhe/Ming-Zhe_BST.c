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
        if(key < T->data)      
            T = T->lchild;
        else if(key > T->data) 
            T = T->rchild;
        else                   
            return T;
    }
    return NULL; 
}

bool insertNode(int key, bst_node *root){
    bst_node* pre;
    bst_node* curr;
    
    curr = root;
    
    while(curr != NULL) {
        if(key < curr->data) { 
            pre = curr;
            curr = curr->lchild;
        }
        else if(key > curr->data) { 
            pre = curr;
            curr = curr->rchild;
        }
        else 
            return false;
    }
    
    curr = malloc(sizeof(bst_node)); 
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
        if(key < T->data) { 
            par = T;
            T = T->lchild;
        }
        else if(key > T->data) { 
            par = T;
            T = T->rchild;
        }
        else { 
            if(NULL==T->lchild && NULL==T->rchild) {
                if(par == NULL) { 
                    free (T);
                    T = NULL;
                }
                else { 
                    (par->lchild==T)?(par->lchild=NULL):(par->rchild=NULL);
                    free(T);
                    T = NULL;
                }
            }
            else if(NULL!=T->lchild && NULL==T->rchild) { 
                if(par == NULL) { 
                    tmp = T;
                    T = T->lchild;
                    free(tmp);
                }
                else { 
                    (par->lchild==T)?(par->lchild=T->lchild):(par->rchild=T->lchild);
                    free(T);
                }
            }
            else if(NULL!=T->rchild && NULL==T->lchild) { 
                if(par == NULL) { 
                    tmp = T;
                    T = T->rchild;
                    free(tmp);
                }
                else { 
                    (par->lchild==T)?(par->lchild=T->rchild):(par->rchild=T->rchild);
                    free(T);
                }
            }
            else { 
                bst_node* leftNode = T;
                while(leftNode->rchild != NULL) {
                    par = leftNode;
                    leftNode = leftNode->rchild;
                }
                
                int swapValue = leftNode->data;
                leftNode->data = T->data;
                T->data = swapValue;
               
                (par->lchild==T)?(par->lchild=NULL):(par->rchild=NULL);
                free(T);
            }
        }
    }
    return false; 
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

