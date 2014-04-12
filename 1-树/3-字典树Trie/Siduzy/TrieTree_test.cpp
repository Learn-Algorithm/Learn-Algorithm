//
//  TrieTree_test.cpp
//  LearnAlgorithm
//
//  Created by 张 乃潇 on 3/8/14.
//  Copyright (c) 2014 Siduzy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "TrieTree.h"

using namespace std;

int main()
{
    ifstream input;
    
    input.open("/Users/zhangnaixiao/Desktop/words.txt", ios::in);
    if (!input.good())
    {
        cout<< "Open file failed!" <<endl;
    }
    
    TrieTree tree;
    string line;
    while (getline(input, line))
    {
        tree.Insert(line.c_str());
    }
    
    tree.PrintAll();
    
    tree.Clear();
    tree.PrintAll();
    return 0;
}