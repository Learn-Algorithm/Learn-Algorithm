#include "stdio.h"
#include "stdlib.h"

typedef int KEY_TYPE;
typedef struct SplayNode{
    KEY_TYPE key;
    struct SplayNode *lchild, *rchild, *parent;
}SplayNode;

SplayNode* resetParent(SplayNode* root){
    if (root != NULL){
        if (root->lchild != NULL) root->lchild->parent = root;
        if (root->rchild != NULL) root->rchild->parent = root;
    }
    return root;
}

SplayNode* leftZigZig(SplayNode* G, SplayNode* P, SplayNode* C){
    G->lchild = P->rchild;
    P->rchild = G;
    P->lchild = C->rchild;
    C->rchild = P;
    C->parent = G->parent;
    G = resetParent(G);
    P = resetParent(P);
    C = resetParent(C);
    return resetParent(C);
}

SplayNode* rightZigZig(SplayNode* G, SplayNode* P, SplayNode* C){
    G->rchild = P->lchild;
    P->lchild = G;
    P->rchild = C->lchild;
    C->lchild = P;
    C->parent = G->parent;
    G = resetParent(G);
    P = resetParent(P);
    C = resetParent(C);
    return resetParent(C);
}

SplayNode* leftZigZag(SplayNode* G, SplayNode* P, SplayNode* C){
    G->lchild = C->rchild;
    C->rchild = G;
    P->rchild = C->lchild;
    C->lchild = P;
    C->parent = G->parent;
    G = resetParent(G);
    P = resetParent(P);
    return resetParent(C);
}
    
SplayNode* rightZigZag(SplayNode* G, SplayNode* P, SplayNode* C){
    G->rchild = C->lchild;
    C->lchild = G;
    P->lchild = C->rchild;
    C->rchild = P;
    C->parent = G->parent;
    G = resetParent(G);
    P = resetParent(P);
    return resetParent(C);
}

SplayNode *Splay(SplayNode *G, SplayNode *P, SplayNode *C){
    if (P == NULL) return P;
    if (G == NULL){
        if (C->key < P->key){
            P->lchild = C->rchild;
            C->rchild = P;
        } else {
            P->rchild = C->lchild;
            C->lchild = P;
        }
        C->parent = P->parent;
        P = resetParent(P);
        return resetParent(C);
    }

    if (P->key < G->key){
        if (C->key < P->key) return leftZigZig(G, P, C);
        else return leftZigZag(G, P, C);
    }
    if (P->key > G->key){
        if (C->key > P->key) return rightZigZig(G, P, C);
        else return rightZigZag(G, P, C);
    }
}

SplayNode* Insert(SplayNode *root, KEY_TYPE key){
    SplayNode* parent = NULL;
    while (root){
        parent = root;
        if (key < root->key) root = root->lchild;
        else if (key > root->key) root = root->rchild;
        else break;
    }
    root = (SplayNode*)malloc(sizeof(SplayNode));
    root->key = key;
    root->lchild = root->rchild = NULL;
    root->parent = parent;
    while (root->parent){
        root = Splay(root->parent->parent, root->parent, root);
    }
    return root;
}

SplayNode* Search(SplayNode *root, KEY_TYPE key){
    SplayNode* parent = NULL;
    while (root){
        parent = root;
        if (key < root->key) root = root->lchild;
        else if (key > root->key) root = root->rchild;
        else break;
    }

    if (root){
        while (root->parent){
            root = Splay(root->parent->parent, root->parent, root);
        }
    }
    return root;
}

SplayNode* Remove(SplayNode* root, KEY_TYPE key){
    SplayNode* parent = NULL;
    SplayNode* lchild = NULL;
    while (root){
        parent = root;
        if (key < root->key) root = root->lchild;
        else if (key > root->key) root = root->rchild;
        else break;
    }

    if (root){
        while (root->parent){
            root = Splay(root->parent->parent, root->parent, root);
        }
        root->lchild->parent = NULL;
        lchild = root->lchild;
        while (lchild->rchild){
            lchild = lchild->rchild;
        }
        lchild->rchild = root->rchild;
        lchild->rchild->parent = lchild;
        lchild = root->lchild;
        free(root);
        root = NULL;
    }
    return lchild;
}

int main(){
    SplayNode* root = Insert(NULL, 1);
    root = Insert(root, 2);
    root = Insert(root, 3);
    root = Insert(root, 4);
    root = Insert(root, 5);
    root = Insert(root, 6);
    root = Insert(root, 7);

    root = Search(root, 1);
    root = Remove(root, 4);
    return 0;
}
