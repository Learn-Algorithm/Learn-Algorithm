//
//  AVLTree.cpp
//  LearnAlgorithm
//
//  Created by 张 乃潇 on 3/2/14.
//  Copyright (c) 2014 Siduzy. All rights reserved.
//

#include "AVLTree.h"
#include <iostream>

using namespace std;


void TurnTree(AVL ** pRoot, KEY_TYPE key);

AVL* RR_Rotate(AVL* k2)
{
    cout << "RR key: " << k2->key <<endl;
    AVL * pRoot = k2->rchild;
    pRoot->height = pRoot->rchild==NULL ? 1 : 0;
    k2->rchild = pRoot->lchild;
    if ((k2->lchild==NULL && k2->rchild==NULL) ||
        (k2->lchild!=NULL && k2->rchild!=NULL))
    {
        k2->height = 0;
    }
    else
    {
        k2->height = k2->lchild==NULL ? -1 : 1;
    }
    pRoot->lchild = k2;
    return pRoot;
}

AVL* LL_Rotate(AVL* k2)
{
    cout << "LL key: " << k2->key <<endl;
    AVL * pRoot = k2->lchild;
    pRoot->height = pRoot->lchild==NULL ? -1 :0;
    k2->lchild = pRoot->rchild;
    if ((k2->lchild==NULL && k2->rchild==NULL) ||
        (k2->lchild!=NULL && k2->rchild!=NULL))
    {
        k2->height = 0;
    }
    else
    {
        k2->height = k2->lchild==NULL ? -1 : 1;
    }
    pRoot->rchild = k2;
    return pRoot;
}

AVL* LR_Rotate(AVL* k3)
{
    return NULL;
}

AVL* RL_Rotate(AVL* k3)
{
    return NULL;
}


AVL* Create()
{
    AVL *pAVL = new AVL();
    pAVL->key = 0;
    pAVL->height = -1;
    pAVL->lchild = NULL;
    pAVL->rchild = NULL;
    return pAVL;
}

AVL * CreateNode(KEY_TYPE key)
{
    AVL * pAVL = new AVL();
    if (pAVL != NULL)
    {
        pAVL->lchild = NULL;
        pAVL->rchild = NULL;
        pAVL->height = 0;
        pAVL->key = key;
        return pAVL;
    }
    cout << "No enough memory" <<endl;
    exit(-1);
}

AVL* Insert(AVL* root, KEY_TYPE key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->height==-1 && root->rchild==NULL)
    {
        root->key = key;
        root->height = 0;
        return root;
    }
    AVL * pRet = root;
    AVL ** pRoot = &root;
    AVL ** pIdx = &root;
    bool bTurn = false;
    while (true)
    {
        pRoot = (*pIdx)->height==0 ? pRoot : pIdx;
        
        if ((*pIdx)->key > key)
        {
            bTurn = (*pIdx)->height>0 ? true : (*pIdx)->height<0 ? false : bTurn;
            
            if ((*pIdx)->lchild == NULL)
            {
                (*pIdx)->lchild = CreateNode(key);
                cout<<"New Node: "<< key << " Parent: "<< (*pIdx)->key <<endl;
                (*pIdx)->height += 1;
                break;
            }
            pIdx = &(*pIdx)->lchild;
        }
        else if ((*pIdx)->key < key)
        {
            bTurn = (*pIdx)->height<0 ? true : (*pIdx)->height>0 ? false : bTurn;
            if ((*pIdx)->rchild == NULL)
            {
                (*pIdx)->rchild = CreateNode(key);
                (*pIdx)->height -= 1;
                cout<<"New Node: "<< key << " Parent: "<< (*pIdx)->key <<endl;
                break;
            }
            pIdx = &(*pIdx)->rchild;
        }
        else
        {
            return root;
        }
    }
    
    if (bTurn)
    {
        // Ugly Here.
        if (*pRoot == pRet)
        {
            TurnTree(pRoot, key);
            return *pRoot;
        }
        TurnTree(pRoot, key);
    }
    else
    {
        AddHeight(*pRoot, *pIdx);
    }
    
    return pRet;
}

void TurnTree(AVL ** pRoot, KEY_TYPE key)
{
    AVL * pRet = *pRoot;
    if (pRet->key > key)
    {
        if (pRet->lchild->key < key)
        {
            pRet->lchild = RR_Rotate(pRet->lchild);
        }
        
        pRet = LL_Rotate(pRet);
        
    }
    else
    {
        if (pRet->rchild->key > key)
        {
            pRet->rchild = LL_Rotate(pRet->rchild);
        }
        pRet = RR_Rotate(pRet);
    }
    *pRoot = pRet;
}

void AddHeight(AVL *from, AVL *to)
{
    AVL * pNow = from;
    while (pNow != to)
    {
        if (pNow->key > to->key)
        {
            pNow->height += 1;
            pNow = pNow->lchild;
        }
        else
        {
            pNow->height -= 1;
            pNow = pNow->rchild;
        }
    }
}

void printInOrder(AVL * root)
{
    if (root->lchild != NULL)
    {
        printInOrder(root->lchild);
    }
    std::cout << root->key
    << " Height: " << root->height
    << " Left: "
    << (root->lchild ? root->lchild->key : NULL)
    << " Right "
    << (root->rchild ? root->rchild->key : NULL)
    << "\n";
    if (root->rchild != NULL)
    {
        printInOrder(root->rchild);
    }
}

AVL* Delete(AVL* root, KEY_TYPE key)
{

    return NULL;
}

void InOrder(AVL* root)
{
    
}
