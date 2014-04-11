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

    // Insert 'Word' to Trie.
    bool Insert(const char *szWord);
    
    // Remove this 'Word' from TrieTree
    void Remove(const char *szWord);

    // Query this 'Word' from TrieTree
    int Query(const char *szWord);

    // Print All from the tree.
    void PrintAll();
    
    // Clear the tree
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
    
    // Find if a char in subtree's nodes
    Node * FindCharFromSubTree(char ch, Node ** pSubTree);

    // Insert the Word to subtree
    bool InsertToSubTree(Node *** pNode, const char *szWord);

    // Create a new subtree with an old one
    bool CreateNewSubTreeWithOld(Node *** pSubTree, const char * szWord);
    
    // Creat a new subtree with Word
    Node ** CreateSubTreeWith(const char *szWord);
    
    // Query the word from node
    int QueryFromNode(Node *pIdx, const char * szWord);
    
    // remove word from node
    bool RemoveFromNode(Node ** pNode, const char *szWord);
    
    // remove the word from subtree
    bool RemoveFromSubTree(Node *** pNode, const char *szWord);
    
    // Clear node and its subtree
    void ClearNode(Node ** pNode);
    
    // Clear the subtree
    void ClearSubTree(Node *** pNode);

    // Help to print
    void PrintNode(const Node* pNode, const char * szPrefix="");
    
    Node ** m_pHead;
};


#endif /* defined(__LearnAlgorithm__TrieTree__) */
