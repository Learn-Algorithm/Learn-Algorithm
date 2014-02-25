//
//  main.c
//  BinarySearchTree
//
//  Created by Matthew Lu on 18/02/2014.
//  Copyright (c) 2014 Matthew Lu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct  biTNode
{
    ElementType data;
    struct  biTNode* Lchild;
    struct  biTNode* Rchild;
}BiTNode,*BiTree;


bool SearchBST(BiTree T,ElementType key,BiTree f,BiTree *p);
bool delete(BiTree *p);
bool InsertBST(BiTree *T,ElementType key);
bool DeleteBST(BiTree *T, ElementType key);

BiTNode* Create()
{
    ElementType ch;
    BiTNode *T;
    
    scanf("%d",&ch);
    

    if (ch == '#') {
        T = NULL;
    }
    else {
        T = (BiTNode*)malloc(sizeof(BiTNode));
        if(T==NULL) {
            printf("memory error");
        }
        
        T->data = ch;
        T->Lchild =  Create();
        T->Rchild =  Create();
    }
    return T;
}



BiTNode * CreateBST()
{
    ElementType ch;
    BiTree T = NULL;

    
    printf("Please input your code:\n");
    scanf("%d",&ch);
    while (ch != 0) {
       InsertBST(&T, ch);
       scanf("%d",&ch);
    }
    
    return T;
}

// 45,24,53,45,12,24,90
bool InsertBST(BiTree *T,ElementType key)
{
   // BiTree p = T;
    
    BiTree p,s;
  //p =SearchBST(T,key,NULL,*p);
    if(!SearchBST(*T,key,NULL,&p))
    {
     
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = key;
        s->Lchild = s->Rchild = NULL;
        
        if(!p)
        {
            *T=s;
            return T;
        }
        else if(key < p->data)
        {
            p->Lchild = s;
        }
        else
        {
            p->Rchild = s;
        }
        return true;
        
    }
    else
    {
    return false;
    }
}



//BiTNode* Search(BiTNode *T, ElementType key)
//{
//    if(!T || T->data == key)
//    {
//        return T;
//    }
//    else if(key <  T->data)
//    {
//        return(Search(T->Lchild,key)); // search in left child tree
//    }
//    else
//    {
//        return(Search(T->Rchild,key)); // search in right child tree
//
//    }
//}


//在根指针T所指的二叉排序树递归查找其关键字等于key的数据元素，
//如果查找成功，则指针p指向该数据元素的结点，并返回true
//否则指针p指向查找路径上访问的最后一个结点并返回false，指针f指向T的双亲，初始值为NULL
bool SearchBST(BiTree T,ElementType key,BiTree f,BiTree *p)
{
    
    if(!T)
    {
        *p=f; return false;      //search fail
    }
    else if (key == T->data)
    {
        *p=T; return true;       //search success
    }
    else if(key < T->data)
    {
        return SearchBST(T->Lchild,key,T,p);   //在左子树查找
    }
    else
    {
        return SearchBST(T->Rchild,key,T,p);   //在右子树查找
    }
}




// 若二叉排序树中存在关键字等于key的数据元素时，则删除改数据元素结点，
// 并返回TRUE, 否则返回false
bool DeleteBST(BiTree *T, ElementType key)
{
    //BiTree temp = *T;
    
    if (!T) {
        return false;
    }
    else
    {
        if ( (*T)->data == key) {
            return delete(T);
        }
        else if( (*T)->data < key )
        {
            return DeleteBST(&(*T)->Rchild, key);
        }
        else
        {
            return DeleteBST(&(*T)->Lchild, key);
        }
        
    }
}





// 从二叉排序树中删除节点p， 并且重接他的左或右子树
bool delete(BiTree *p)
{
    BiTree q;
    
    
    if (!(*p)->Rchild) {  //右子树空则只需要重接左子树
        q= *p; *p = (*p)->Lchild;free(q);
    }
    else if(!(*p)->Lchild)  //左子树空则只需要重接右子树
    {
        q=*p; *p = (*p)->Rchild; free(q);
    }
    else   // 左右都不为空
    {
        BiTree s;
        q=*p; s = (*p)->Lchild;
        while (s->Rchild) {  //转左， 然后向右到尽头
            q=s;s=s->Rchild;
        }
        
        (*p)->data = s->data;  // s 指向被删结点的前驱
        
        if (q!=(*p)) {         //重接*q的右子树
            q->Rchild = s ->Lchild;
        }
        else                //重接*q的左子树
        {
            q->Lchild = s->Lchild;
        }
        delete(&s);
    }
    
    return true;
    
}

void inOrder(BiTNode *T)
{
    if(T!=NULL)
    {
        inOrder(T->Lchild);
        printf("%d ",T->data);
        inOrder(T->Rchild);
    }
}


int main(int argc, const char * argv[])
{
//Example input is: 45,24,53,45,12,24,90

    BiTNode *biTree = NULL ;

    biTree = CreateBST();
    
    InsertBST(&biTree,32);
    
    DeleteBST(&biTree, 90);
    printf("Inorder is:\n");
    inOrder(biTree);
    
    

    return 0;
}

