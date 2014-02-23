//
//  BinarySearchTree.h
//  LearnAlgorithm
//
//  Created by 张 乃潇 on 2/22/14.
//  Copyright (c) 2014 Siduzy. All rights reserved.
//

#ifndef __LearnAlgorithm__BinarySearchTree__
#define __LearnAlgorithm__BinarySearchTree__

#include <iostream>

typedef void * DATA;

class BST
{
    
public:
    BST();
    ~BST();
    typedef int (*fCompare) (DATA data1, DATA data2);
    typedef bool (*fCreate) (DATA * toInsert, DATA data);
    typedef bool (*fRemove) (DATA * toDelete);
    typedef bool (*fTraverse)(DATA data, void *pData);
    
    bool create(fCompare cmp, fCreate crate, fRemove remove);
    bool insert(DATA data);
    bool search(DATA data) const;
    bool remove(DATA data);
    bool inOrder(fTraverse traverse, void * pUser) const;

private:
    typedef struct tagTree
    {
        DATA data;
        tagTree * pLeft;
        tagTree * pRight;
    }Tree, *PTree;
    
    bool insertToTree(PTree *pTree, DATA data);
    bool inOrder(PTree pTree, fTraverse traverse, void * pUser) const;
    bool search(PTree pTree, DATA data) const;
    bool remove(PTree * pTree, DATA data);
    void findMaxValue(PTree * toDel, PTree * toDelParent, PTree lessThanParent, PTree lessThan) const;
    void findMinValue(PTree toDel, PTree toDelParent, PTree largerThan) const;
    bool clear(PTree pTree);

    PTree m_pTree;
    fCompare m_fCmp;
    fCreate m_fCreate;
    fRemove m_fRemove;
};


#endif /* defined(__LearnAlgorithm__BinarySearchTree__) */
