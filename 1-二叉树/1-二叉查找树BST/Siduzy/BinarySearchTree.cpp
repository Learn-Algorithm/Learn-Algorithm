//
//  BinarySearchTree.cpp
//  LearnAlgorithm
//
//  Created by 张 乃潇 on 2/22/14.
//  Copyright (c) 2014 Siduzy. All rights reserved.
//

#include "BinarySearchTree.h"

BST::BST()
: m_pTree(NULL)
, m_fCmp(NULL)
, m_fCreate(NULL)
, m_fRemove(NULL)
{
    
}

BST::~BST()
{
    if (clear(m_pTree))
    {
        m_fCmp = NULL;
        m_fCreate = NULL;
        m_fRemove = NULL;
    }
}

bool BST::create(fCompare cmp, fCreate create, fRemove remove)
{
    if (cmp==NULL || create==NULL || remove==NULL)
    {
        return false;
    }
    if (m_pTree != NULL)
    {
        return true;
    }
    m_pTree = new(std::nothrow) Tree();
    if (m_pTree == NULL)
    {
        return false;
    }
    
    m_pTree->data = NULL;
    m_pTree->pLeft = NULL;
    m_pTree->pRight = NULL;
    
    m_fCmp = cmp;
    m_fCreate = create;
    m_fRemove = remove;
    return true;
}

bool BST::insertToTree(PTree *pTree, DATA data)
{
    if (*pTree == NULL)
    {
        *pTree = new(std::nothrow) Tree();
        (*pTree)->data = (*pTree)->pLeft = (*pTree)->pRight = NULL;
    }
    
    if ((*pTree)->data == NULL)
    {
        // return m_fCreate(&(*pTree)->data, data);
        m_fCreate(&(*pTree)->data, data);
        (*pTree)->val = *(int *)((*pTree)->data);
        return true;
    }
    
    int result = m_fCmp((*pTree)->data, data);
    if (result == 0)
    {
        return true;
    }
    else if (result > 0)
    {
        return insertToTree(&(*pTree)->pLeft, data);
    }
    else
    {
        return insertToTree(&(*pTree)->pRight, data);
    }
}

bool BST::insert(DATA data)
{
    return insertToTree(&m_pTree, data);
}


bool BST::search(PTree pTree, DATA data) const
{
    if (pTree == NULL)
    {
        return false;
    }
    if (pTree->data == NULL)
    {
        return false;
    }
    if (m_fCmp(pTree->data, data) == 0)
    {
        return true;
    }
    if (m_fCmp(pTree->data, data) > 0)
    {
        return search(pTree->pLeft, data);
    }
    if (m_fCmp(pTree->data, data) < 0)
    {
        return search(pTree->pRight, data);
    }
    return false;
}

bool BST::search(DATA data) const
{
    return search(m_pTree, data);
}

void BST::findMaxValue(PTree * toDel, PTree * toDelParent, PTree lessThanParent, PTree lessThan) const
{
    if (lessThan == NULL)
    {
        * toDel = NULL;
    }
    if (lessThan->pRight) {
        return findMaxValue(toDel, toDelParent, lessThan, lessThan->pRight);
    }
    else
    {
        * toDel = lessThan;
        * toDelParent = lessThanParent;
        return;
    }
}

bool BST::remove(PTree * pTree, DATA data)
{
    if (*pTree == NULL)
    {
        return false;
    }
    if ((*pTree)->data == NULL)
    {
        return false;
    }
    
    int result = m_fCmp((*pTree)->data, data);
    
    if (result == 0)
    {
        // No child, just delete
        if ((*pTree)->pLeft==NULL && (*pTree)->pRight==NULL)
        {
            return m_fRemove(&(*pTree)->data);
        }
        // No Left
        else if ((*pTree)->pLeft==NULL)
        {
            if (m_fRemove(&(*pTree)->data))
            {
                PTree pToDel = (*pTree);
                *pTree = (*pTree)->pRight;
                delete pToDel;
                return true;
            }
            return false;
            
        }
        // No right
        else if ((*pTree)->pRight == NULL)
        {
            if (m_fRemove(&(*pTree)->data))
            {
                PTree pToDel = (*pTree);
                *pTree = (*pTree)->pLeft;
                delete pToDel;
                return true;
            }
            return false;
            
        }
        else
        {
            if (m_fRemove(&(*pTree)->data))
            {
                PTree pToDel = NULL;
                PTree pToDelParent = NULL;
                
                findMaxValue(&pToDel, &pToDelParent, (*pTree), (*pTree)->pLeft);
                Tree temp = *(*pTree);
                pToDel->pRight = temp.pRight;
                pToDelParent->pRight = pToDel->pLeft;
                pToDel->pLeft = pToDel==temp.pLeft ? pToDel->pLeft : temp.pLeft;
                
                delete (*pTree);
                *pTree = pToDel;
                
                return true;
            }
            else
            {
//                return false;
            }
        }
    }
    else if (result > 0)
    {
        remove(&(*pTree)->pLeft, data);
    }
    else
    {
        remove(&(*pTree)->pRight, data);
    }
    
    return true;
}

bool BST::remove(DATA data)
{
    return remove(&m_pTree, data);
}

bool BST::inOrder(PTree pTree, fTraverse traverse, void * pUser) const
{
    bool ret = true;
    if (pTree->pLeft)
    {
        ret = ret && inOrder(pTree->pLeft, traverse, pUser);
    }
    if (pTree->data)
    {
        ret = ret && traverse(pTree->data, pUser);
    }
    if (pTree->pRight)
    {
        ret = ret && inOrder(pTree->pRight, traverse, pUser);
    }
    return ret;
}

bool BST::inOrder(fTraverse traverse, void * pUser) const
{
    return inOrder(m_pTree, traverse, pUser);
}

bool BST::clear(PTree pTree)
{
    bool ret = true;
    if (pTree->pLeft)
    {
        ret = ret && clear(pTree->pLeft);
    }
    if (pTree->data)
    {
        ret = ret && m_fRemove(&pTree->data);
    }
    if (pTree->pRight)
    {
        ret = ret && clear(pTree->pRight);
    }
    delete pTree;
    pTree->data = pTree->pLeft = pTree->pRight = NULL;
    return ret;
}