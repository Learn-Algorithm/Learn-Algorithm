//
//  TrieTree.cpp
//  LearnAlgorithm
//
//  Created by 张 乃潇 on 3/5/14.
//  Copyright (c) 2014 Siduzy. All rights reserved.
//

#include "TrieTree.h"

using namespace std;

TrieTree::TrieTree()
:m_pHead(NULL)
{
}

TrieTree::~TrieTree()
{
    Clear();
}

TrieTree::Node ** TrieTree::CreateSubTreeWith(const char *szWord)
{
    unsigned long ulLen = strlen(szWord);
    
    Node ** pSubTree = new Node * [2]; //extra one for null ptr
    if (pSubTree == NULL)
    {
        return NULL;
    }
    memset(pSubTree, 0, sizeof(*pSubTree) * 2);
    if (ulLen == 1)
    {
        *pSubTree = new Node(szWord[0], 1);
    }
    else
    {
        (*pSubTree) = new Node(szWord[0], 0);
        (*pSubTree)->pSubTree = CreateSubTreeWith(szWord+1);
    }
    return pSubTree;
}

TrieTree::Node * TrieTree::FindCharFromSubTree(char ch, Node ** pSubTree)
{
    if (pSubTree == NULL)
    {
        return NULL;
    }

    Node * pIdx = NULL;
    for (pIdx = *pSubTree; pIdx != NULL; pIdx = *(++pSubTree))
    {
        if ((pIdx->ch ^ ch) == 0)
        {
            return pIdx;
        }
    }
    return NULL;
}

bool TrieTree::CreateNewSubTreeWithOld(Node *** pSubTree, const char * szWord)
{
    unsigned long ulLen = strlen(szWord);
    
    Node ** pInsertPos = NULL;
    Node ** pIdx = NULL;
    for (pIdx = *pSubTree; *pIdx != NULL; pIdx = pIdx+1)
    {
        if ((*pIdx)->ch < szWord[0])
        {
            pInsertPos = pIdx;
        }
    }
    
    unsigned long ulCpySzie = pInsertPos == NULL ? 0 : pInsertPos - *pSubTree + 1;
    unsigned long ulElements = pIdx - *pSubTree + 1;
    Node ** pNewTree = new Node * [ulElements+1];
    if (pNewTree == NULL)
    {
        return false;
    }
    
    memcpy(pNewTree, *pSubTree, sizeof(*pNewTree) * ulCpySzie);
    *(pNewTree+ulCpySzie) = new Node(szWord[0], ulLen==1 ? 1 : 0);
    
    ((*(pNewTree+ulCpySzie))->pSubTree = ulLen==1 ? NULL : CreateSubTreeWith(szWord+1));
    memcpy(pNewTree+ulCpySzie+1, (*pSubTree)+ulCpySzie, sizeof(*pNewTree) * (ulElements-ulCpySzie));
    delete [] *pSubTree;
    *pSubTree = pNewTree;

    return true;
}

bool TrieTree::InsertToSubTree(Node *** pSubTree, const char *szWord)
{
    unsigned long ulLen = strlen(szWord);
    
    if (ulLen == 0)
    {
        return NULL;
    }
    
    if (*pSubTree == NULL)
    {
        return (*pSubTree = CreateSubTreeWith(szWord)) == NULL ? false : true;
    }
    
    Node * pTarget = FindCharFromSubTree(szWord[0], *pSubTree);
    if (pTarget != NULL)
    {
        if (ulLen == 1)
        {
            pTarget->count++;
            return true;
        }
        else if (pTarget->pSubTree)
        {
            return InsertToSubTree(&pTarget->pSubTree, szWord+1);
        }
        else
        {
            return (pTarget->pSubTree = CreateSubTreeWith(szWord+1)) == NULL ? false : true;
        }
    }
    
    return CreateNewSubTreeWithOld(pSubTree, szWord);
}

bool TrieTree::Insert(const char *szWord)
{
    return InsertToSubTree(&m_pHead, szWord);
}

int TrieTree::Query(const char *szWord)
{
    if (strlen(szWord) == 0)
    {
        return 0;
    }
    
    Node ** pIdx = NULL;
    int count = 0;
    for (pIdx = m_pHead; pIdx!=NULL && *pIdx != NULL; pIdx = pIdx+1)
    {
        if ((count= QueryFromNode(*pIdx, szWord)) != 0)
        {
            return count;
        }
    }
    return 0;
}

int TrieTree::QueryFromNode(TrieTree::Node *pNode, const char * szWord)
{
    if (pNode->ch ^ szWord[0])
    {
        return 0;
    }
    else if (strlen(szWord)==1)
    {
        return pNode->count;
    }

    Node ** pIdx = NULL;
    int count = 0;
    for (pIdx = pNode->pSubTree; pIdx!= NULL && *pIdx != NULL; pIdx = pIdx+1)
    {
        if ((count = QueryFromNode(*pIdx, szWord+1 )) != 0)
        {
            return count;
        }
    }
    return 0;
}

void TrieTree::PrintAll()
{
    if (m_pHead == NULL)
    {
        return;
    }
    Node ** pIdx = NULL;
    for (pIdx = m_pHead; pIdx!=NULL && *pIdx != NULL; pIdx = pIdx+1)
    {
        PrintNode(*pIdx);
        cout<<"...................."<<endl;
    }
}

void TrieTree::PrintNode(const Node* pNode, const char * szPrefix)
{
    string strWord = szPrefix;
    strWord.insert(strWord.length(), 1, pNode->ch);
    if (pNode->count > 0)
    {
        cout<< strWord << "\t->" << pNode->count << endl ;
    }
    Node ** pIdx = NULL;
    for (pIdx = pNode->pSubTree; pIdx!= NULL && *pIdx != NULL; pIdx = pIdx+1)
    {
        PrintNode(*pIdx, strWord.c_str());
    }
}

void TrieTree::Remove(const char *szWord)
{
    if (m_pHead == NULL)
    {
        return;
    }
    if (strlen(szWord) == 0)
    {
        return;
    }
    
    RemoveFromSubTree(&m_pHead, szWord);
}

bool TrieTree::RemoveFromSubTree(Node *** pTree, const char *szWord)
{
    Node ** pIdx = NULL;
    Node ** pNodeToDel = NULL;
    for (pIdx = *pTree; pIdx!= NULL && *pIdx!=NULL; pIdx = pIdx+1)
    {
        if (((*pIdx)->ch ^ szWord[0]) == 0)
        {
            pNodeToDel = pIdx;
        }
    }
    
    unsigned long ulLenBefDel = pIdx - *pTree + 1;
    if (pNodeToDel != NULL)
    {
        unsigned long ulLenToCpy = pNodeToDel - *pTree;
        if (RemoveFromNode(pNodeToDel, szWord))
        {
            if (*pNodeToDel == NULL)
            {
                if (ulLenBefDel == 2)
                {
                    delete [] *pTree;
                    *pTree = NULL;
                }
                else
                {
                    Node ** pNewTree = new Node *[ulLenBefDel-1];
                    if (pNewTree == NULL)
                    {
                        cout<< "Critical Error! Exit" <<endl;
                        exit(-1);
                    }
                    
                    memcpy(pNewTree, *pTree, sizeof(*pNewTree) * ulLenToCpy);
                    memcpy(pNewTree+ulLenToCpy, *pTree+ulLenToCpy+1, sizeof(*pNewTree) * (ulLenBefDel - ulLenToCpy -1));
                    
                    delete [] *pTree;
                    *pTree = pNewTree;
                }
            }
            return true;
        }
        return false;
    }
    return true;
}

bool TrieTree::RemoveFromNode(Node ** pTree, const char *szWord)
{
    if (strlen(szWord) == 1 )
    {
        if ((*pTree)->pSubTree == NULL)
        {
            delete *pTree;
            *pTree = NULL;
        }
        else
        {
            (*pTree)->count = 0;
        }
        return true;
    }
    
    if (RemoveFromSubTree(&(*pTree)->pSubTree, szWord+1))
    {
        if ((*pTree)->count == 0 && (*pTree)->pSubTree == NULL)
        {
            delete *pTree;
            *pTree = NULL;
        }
        return true;
    }
    return false;
}

void TrieTree::ClearSubTree(Node *** pNode)
{
    if (*pNode == NULL)
    {
        return;
    }
    
    Node ** pIdx = NULL;
    for (pIdx = *pNode; pIdx!=NULL && (*pIdx)!=NULL; pIdx=pIdx+1)
    {
        ClearNode(pIdx);
    }
    delete [] *pNode;
    *pNode = NULL;
}

void TrieTree::ClearNode(Node ** pNode)
{
    ClearSubTree(&(*pNode)->pSubTree);
    delete *pNode;
    *pNode = NULL;
}

void TrieTree::Clear()
{
    ClearSubTree(&m_pHead);
}
