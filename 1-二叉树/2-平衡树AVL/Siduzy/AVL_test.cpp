#include <iostream>
#include "AVLTree.h"
using namespace std;

void testInsert(AVL *pAVL)
{
    cout<<"10--------------------"<<endl;
    pAVL = Insert(pAVL, 10);
    printInOrder(pAVL);
    cout<<"11--------------------"<<endl;
    pAVL = Insert(pAVL, 11);
    printInOrder(pAVL);
    cout<<"8--------------------"<<endl;
    pAVL = Insert(pAVL, 8);
    printInOrder(pAVL);
    cout<<"3--------------------"<<endl;
    pAVL = Insert(pAVL, 3);
    printInOrder(pAVL);
    cout<<"4--------------------"<<endl;
    pAVL = Insert(pAVL, 4);
    printInOrder(pAVL);
    cout<<"7--------------------"<<endl;
    pAVL = Insert(pAVL, 7);
    printInOrder(pAVL);
    cout<<"2--------------------"<<endl;
    pAVL = Insert(pAVL, 2);
    printInOrder(pAVL);
    cout<<"6--------------------"<<endl;
    pAVL = Insert(pAVL, 6);
    printInOrder(pAVL);
    cout<<"5--------------------"<<endl;
    pAVL = Insert(pAVL, 5);
    printInOrder(pAVL);
    cout<<"1--------------------"<<endl;
    pAVL = Insert(pAVL, 1);
    cout<<"-1--------------------"<<endl;
    pAVL = Insert(pAVL, -1);
    printInOrder(pAVL);
}

int main()
{
    AVL * pAVL = Create();
    testInsert(pAVL);
    
    
    
    return 0;
}