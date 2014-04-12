//
//  avl.h
//  AVLTree
//
//  Created by WolfLee on 2/28/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//

#ifndef AVLTree_avl_h
#define AVLTree_avl_h

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

AVL* Insert(AVL* root, KEY_TYPE key);
AVL* Delete(AVL* root, KEY_TYPE key);
void InOrder(AVL* root);

#endif
