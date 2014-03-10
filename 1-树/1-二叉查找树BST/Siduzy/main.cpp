//
//  main.cpp
//  LearnAlgorithm
//
//  Created by 张 乃潇 on 2/22/14.
//  Copyright (c) 2014 Siduzy. All rights reserved.
//

#include <iostream>
#include "BinarySearchTree.h"

int Compare(DATA data1, DATA data2)
{
    int d1 = *(int *)data1;
    int d2 = *(int *)data2;
    if (d1 > d2)
    {
        return 1;
    }
    else if (d1 == d2)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

bool Remove(DATA * toDelete)
{
    if (toDelete != NULL)
    {
        delete (int *)*toDelete;
        *toDelete = NULL;
    }
    return true;
}

bool Create(DATA * toInsert, DATA data)
{
    *toInsert = (void *) new (std::nothrow) int(*(int *)data);
    return (*toInsert != NULL);
}

bool Traverse(DATA data, void *pData)
{
    std::cout<<*(int *)data <<std::endl;
    return true;
}

int main(int argc, const char * argv[])
{

    // insert code here...
    BST bst;
    bst.create(Compare, Create, Remove);
    
    int aryInt[] = {11, 17, 9, 15, 13, 18, 20, 7, 5, 1, 2, 3, 4, 6};
    int nSize = sizeof(aryInt) / sizeof(int);
    for (int i = 0; i < nSize; ++i) {
        bst.insert(aryInt+i);
    }

    bst.inOrder(Traverse, NULL);
    aryInt[nSize++] = 6;
    for (int i = 0; i < nSize; ++i) {
        if (bst.search(aryInt+i))
        {
            std::cout<< "find element "<< *(aryInt+i) << std::endl;
        }
        else
        {
            std::cout<< "Can't find element "<< *(aryInt+i) << std::endl;
        }
    }
    bst.inOrder(Traverse, NULL);
    for (int i = 0; i < nSize/2; ++i) {
        if (bst.remove(aryInt+i))
        {
            std::cout<< "Remove element "<< *(aryInt+i) << std::endl;
        }
        else
        {
            std::cout<< "Can't Remove element "<< *(aryInt+i) << std::endl;
        }
    }
    bst.inOrder(Traverse, NULL);
    return 0;
}

