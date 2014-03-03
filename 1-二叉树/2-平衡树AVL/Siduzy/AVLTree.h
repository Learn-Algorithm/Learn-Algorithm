//
//  AVLTree.h
//  LearnAlgorithm
//
//  Created by 张 乃潇 on 3/2/14.
//  Copyright (c) 2014 Siduzy. All rights reserved.
//

#ifndef __LearnAlgorithm__AVLTree__
#define __LearnAlgorithm__AVLTree__

typedef int KEY_TYPE;
typedef struct AVL{
    KEY_TYPE key;
    int height;
    struct AVL* lchild;
    struct AVL* rchild;
}AVL;

AVL* RR_Rotate(AVL* k2);
AVL* LL_Rotate(AVL* k2);
AVL* LR_Rotate(AVL* k3);
AVL* RL_Rotate(AVL* k3);

AVL* Create();
AVL* Insert(AVL* root, KEY_TYPE key);
AVL* Delete(AVL* root, KEY_TYPE key);
void InOrder(AVL* root); 
void printInOrder(AVL * root);

void AddHeight(AVL *from, AVL *to);

#endif /* defined(__LearnAlgorithm__AVLTree__) */
