//
//  main.c
//  BalancedBinaryTree
//
//  Created by Matthew Lu on 25/02/2014.
//  Copyright (c) 2014 Matthew Lu. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LH +1 // 左高
#define EH 0 // 等高
#define RH -1 //右高


typedef int KEY_TYPE;



typedef struct BSTNode
{
    KEY_TYPE key;
    int height;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
}BSTNode,*BSTree;

//AVL* RR_Rotate(AVL* k2);
//AVL* LL_Rotate(AVL* k2);
//AVL* LR_Rotate(AVL* k3);
//AVL* RL_Rotate(AVL* k3);


//AVL* Insert(AVL* root,KEY_TYPE key);
//AVL* Delete(AVL* root,KEY_TYPE key);

int InsertAVL(BSTree *T,KEY_TYPE e, bool *taller);
void InOrder(BSTNode *root);

void LeftBalance(BSTree *T);
void RightBalance(BSTree *T);

void R_Rotate(BSTree *p);
void L_Rotate(BSTree *p);


int Height(BSTree p)
{
    return  p == NULL ? -1 : p->height;
}

int Max(KEY_TYPE a,KEY_TYPE b)
{
    return (a > b ? a : b);
}

void R_Rotate(BSTree *p)
{
    //对以*p为根的二叉排序树做右旋处理，处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点
    BSTree lc = (*p)->lchild;      //lc 指向*p的左子树根结点
    (*p)->lchild = lc->rchild;   //lc的右子树挂接为*p的左子树
    lc->rchild = *p;
    *p=lc;  // p 指向新的根结点
}


void L_Rotate(BSTree *p)
{
    //对以*p为根的二叉排序树做左旋处理，处理之后p指向新的树根结点，即旋转处理之前的右字数的根结点
    
    BSTree rc = (*p)->rchild;
    (*p)->rchild = rc->lchild;
    rc->lchild = *p; *p=rc;
}



int InsertAVL(BSTree *T,KEY_TYPE e, bool *taller)
{
    //若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素为e的新结点
    //并返回1，否则返回0，若因插入而使二叉排序树失去平衡，则做平衡旋转处理，布尔变量taller 反映T长高与否
    
    if (!(*T)) { // 插入新的结点， 树长高，设置taller 为 true
        (*T)= (BSTree)malloc(sizeof(BSTNode));
        (*T)->key = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->height = EH;
        taller = (bool *)true;
    }
    else
    {
        if (e == (*T)->key) {  // 树中已存在和e有相同关键字的结点，不再插入
            taller = (bool*)false;return 0;
        }
        
        if (e < (*T)->key) {  //应继续在*T的左子树进行搜索
            if (!InsertAVL( &((*T)->lchild), e, taller)) {
                return 0; //没插入
            }
            
            if (taller) { //已插入到*T的左子树中且左子数的 长高
                
                switch ((*T)->height) {  //检查*T的平衡度
                    case LH:
                        LeftBalance(T);taller = (bool*)false;  break; // 原本左子树比右子树高，需要做左平衡处理
                    case EH:
                        (*T)->height = LH;taller = (bool*)true;break;// 原本左右子树等高，现因左子树增高而使树增高
                    case RH:
                        (*T)->height = EH;taller = (bool*)false;break; //原本右子树比左子树高， 现左右子树等高
                }
            }
        }
        else //继续在*T的右子树中进行搜索
        {
            if (!InsertAVL( &((*T)->rchild), e, taller)) {
                return  0;  //没插入
            }
            
            if (taller) { //已插入到*T的右子树中且右子数的 长高
                
                switch ((*T)->height) {  //检查*T的平衡度
                    case LH:
                        (*T)->height = EH; taller = (bool*)false;  break; // 原本右子树比左子树高，需要做左平衡处理
                    case EH:
                        (*T)->height = RH;taller = (bool*)true;break;// 原本左右子树等高，现因右子树增高而使树增高
                    case RH:
                        RightBalance(T) ;taller = (bool*)false;break; //原本右子树比左子树高， 现左右子树等高
                }
            }
        }
        
    }
    
    return 1;
}


//对已指针T所指结点为根的二叉树做左平衡旋转处理，本算法结束时，指针T指向新的根结点
void LeftBalance(BSTree *T)
{

    BSTree lc = (*T)->lchild; // lc 指向*T的左子树根结点
    
    switch (lc->height) { // 检查*T的左子树的平衡度，并作相应的平衡处理
        case LH:
            (*T)->height = lc->height = EH; // 新的结点插入在*T的左孩子的左子树上，要作单右旋处理
            R_Rotate(T);
            break;
        case RH:    //新的结点插入在*T的左孩子的右子树上，要作双旋处理
        {
            BSTree rd =  lc->rchild;  //rd 指向*T的左孩子的右子树根
            switch (rd->height) { //修改*T及其左孩子的平衡因子
                case LH: (*T)->height = RH;lc ->height = EH; break;
                case EH: (*T)->height = lc ->height = EH; break;
                case RH: (*T)->height = EH;lc ->height = LH; break;
            }
            
            rd ->height = EH;
            L_Rotate( &((*T)->lchild));  //对*T的左子树作左旋平衡处理
            R_Rotate(T);          //对*T作右旋平衡处理
        }
    }
}


void RightBalance(BSTree *T)
{
    BSTree rc = (*T)->rchild;
    
    switch (rc->height) {
      case RH:
            (*T)->height = rc->height = EH;
            L_Rotate(T); break;
        case LH:
        {
            BSTree ld = rc->lchild;
            switch (ld->height) {
                case LH: (*T)->height = EH;rc ->height = RH; break;
                case EH: (*T)->height = rc ->height = EH; break;
                case RH: (*T)->height = LH;rc ->height = RH; break;
            }
            ld ->height = EH;
            R_Rotate(&((*T)->rchild));
            L_Rotate(T);
        }
    }
}



BSTree getMaxNode(BSTree T)
{
    if (!T) {
        return NULL;
    }
    
    BSTree tempNode = T;
    while (tempNode->rchild) {
        tempNode = tempNode->rchild;
    }
    return  tempNode;
}

BSTree getMinNode(BSTree T)
{
    if (!T) {
        return NULL;
    }
    
    BSTree tempNode = T;
    while (tempNode ->lchild) {
        tempNode = tempNode ->lchild;
    }
    return tempNode;
}



BSTree Delete(BSTree T,KEY_TYPE X)
{
    if ( T == NULL ) {
        return NULL;
    }
    
    if ( T->key > X ) {
        T->lchild = Delete(T->lchild,X);
        
        if ( Height( T->rchild ) - Height( T->lchild ) == 2 ) {
            
            if ( Height( T->rchild->lchild ) > Height( T->rchild->lchild ) ) {
                LeftBalance(&T);
            } else {
                L_Rotate(&T);
            }
        }
    } else if ( T->key < X ) {
        T->rchild = Delete(T->rchild ,X);
        
        if ( Height( T->lchild ) - Height( T->rchild ) == 2 ) {
            
            if ( Height( T->lchild->rchild ) > Height( T->lchild->rchild ) ) {
                 RightBalance(&T);
            } else {
                R_Rotate(&T);
            }
        }
    } else {
        struct BSTNode * Temp;
        
        if ( T->lchild == NULL ) {
            Temp = T;
            T = Temp->rchild;
        } else if ( T->rchild == NULL ) {
            Temp = T;
            T = Temp->lchild;
        } else {
            Temp = getMinNode( T->rchild);
            T->key = Temp->key;
            T->rchild = Delete(T->rchild, T->key );
            if ( Height( T->lchild ) - Height( T->rchild ) == 2 ) {
                if ( Height( T->lchild->rchild ) > Height( T->lchild->lchild) ) {
                    RightBalance(&T);
                } else {
                    R_Rotate(&T);
                }
            }
        }
       // free( Temp );
    }
    
    if ( T != NULL ) {
        T->height = Max( Height( T->lchild ), Height( T->rchild ) ) + 1 ;
    }
    return T;
}


void InOrder(BSTNode *root)
{
    if (root != NULL) {
        InOrder(root->lchild);
        printf("%d ",root->key);
        InOrder(root->rchild);
    }
}

int main(int argc, const char * argv[])
{

    // insert code here...
    printf("Data input!\n");
    int a[] = {3,2,1,4,5,6,7,10,9,8};
    
    
   // AVL tree;
    BSTNode *avlTree = NULL;
    
    bool taller;
    
    for (int i =0 ; i < sizeof(a)/sizeof(int) ; i++) {
          InsertAVL(&avlTree, a[i], &taller);
    }
             InOrder(avlTree);
    
    BSTNode *deletedTree = Delete(avlTree, 8);
        printf("\n");
         InOrder(deletedTree);
    

  //  Delete(&tree, 5);
    
   // InOrder(&tree);
  
    
    return 0;
}

