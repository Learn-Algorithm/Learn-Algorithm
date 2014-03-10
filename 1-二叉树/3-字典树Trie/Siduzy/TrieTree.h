//
//  TrieTree.h
//  LearnAlgorithm
//
//  Created by 张 乃潇 on 3/5/14.
//  Copyright (c) 2014 Siduzy. All rights reserved.
//

#ifndef __LearnAlgorithm__TrieTree__
#define __LearnAlgorithm__TrieTree__

#include <iostream>

class TrieTree
{
public:
    TrieTree();
    ~TrieTree();
    
    bool Insert(const char *szWord);
    void Remove(const char *szWord);
    int Query(const char *szWord);
    void PrintAll();
    void Clear();
    
private:
    TrieTree(const TrieTree&);
    TrieTree& operator= (const TrieTree&);
    
    typedef struct tagNode
    {
        char ch;
        int count;
        tagNode ** pSubTree;
        
        tagNode(char ch, int count)
        :ch(ch)
        ,count(count)
        ,pSubTree(NULL)
        {
        }
        ~tagNode()
        {
        }
    }Node;
    
    Node ** InitSubTreeWith(const char *szWord);
    Node * FindCharFromTree(char ch, Node ** pSubTree);
    bool InsertToTree(Node *** pNode, const char *szWord);
    bool InitNewSubTreeWithOld(Node *** pSubTree, const char * szWord);
    
    int QueryInNode(Node *pIdx, const char * szWord);
    
    void PrintNode(const Node* pNode, const char * szPrefix="");
    
    bool RemoveNode(Node ** pNode, const char *szWord);
    bool SearchAndRemvoeFromSubTree(Node *** pNode, const char *szWord);
    void ClearNode(Node ** pNode);
    void ClearSubTree(Node *** pNode);
    
    Node ** m_pHead;
};


#endif /* defined(__LearnAlgorithm__TrieTree__) */
