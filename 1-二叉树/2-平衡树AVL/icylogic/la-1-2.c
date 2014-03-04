#include "stdio.h"
#include "stdlib.h"

//statements
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

//self-defined functions
int getHeight(AVL* root){
    if (root == NULL){
        return -1;
    } else {
        return root->height;
    }
}

int setHeight(AVL* root){
    int lh = getHeight(root->lchild);
    int rh = getHeight(root->rchild);
    int h = (lh > rh ? lh : rh) + 1;
    return h;
}

AVL* Balance(AVL* root){
    if (root != NULL){
        if (getHeight(root->lchild) - 1 > getHeight(root->rchild)){
            if (getHeight(root->lchild->lchild) > getHeight(root->lchild->rchild)){
                root = LL_Rotate(root);
            } else {
                root = LR_Rotate(root);
            }
        } else if (getHeight(root->rchild) - 1 > getHeight(root->lchild)){
            if (getHeight(root->rchild->rchild) > getHeight(root->rchild->lchild)){
                root = RR_Rotate(root);
            } else {
                root = RL_Rotate(root);
            }
        } else {
        root->height = setHeight(root); 
        }
    }
    return root;
}

void clear(AVL* root){
    if ((root)!=NULL){
        clear((root)->lchild);
        clear((root)->rchild);
        free(root);
        root = NULL;
    }
}

//todo functions

AVL* RR_Rotate(AVL* k2){
    AVL* root = k2->rchild;
    k2->rchild = k2->rchild->lchild;
    k2->height = setHeight(k2);
    root->lchild = k2;
    root->height = setHeight(root);
    return root;
}

AVL* LL_Rotate(AVL* k2){
    AVL* root = k2->lchild;
    k2->lchild = k2->lchild->rchild;
    k2->height = setHeight(k2);
    root->rchild = k2;
    root->height = setHeight(root);
    return root;
}

AVL* LR_Rotate(AVL* k3){
    AVL* root = k3->lchild->rchild;

    k3->lchild->rchild = root->lchild;
    k3->lchild->height = setHeight(k3->lchild);
    root->lchild = k3->lchild;

    k3->lchild = root->rchild;
    k3->height = setHeight(k3);
    root->rchild = k3;

    root->height = setHeight(root);
    return root;
}
    
AVL* RL_Rotate(AVL* k3){
    AVL* root = k3->rchild->lchild;

    k3->rchild->lchild = root->rchild;
    k3->rchild->height = setHeight(k3->rchild);
    root->rchild = k3->rchild;

    k3->rchild = root->lchild;
    k3->height = setHeight(k3);
    root->lchild = k3;

    root->height = setHeight(root);
    return root;
}

AVL* Insert(AVL* root, KEY_TYPE key){
    if (root == NULL){
        root = (AVL*)malloc(sizeof(AVL));
		if (root == NULL){
            printf("out of memory");
			exit(0);
		}
        root->key = key;
        root->height = 0;
        root->lchild = root->rchild = NULL;
    } else if (key < root->key){
        root->lchild = Insert(root->lchild, key);
        root = Balance(root);
    } else if (key > root->key){
        root->rchild = Insert(root->rchild, key);
        root = Balance(root);
    }
    return root;
}

AVL* Delete(AVL* root, KEY_TYPE key){
    if (root != NULL){
        if (key == root->key){
            AVL* toFree = root;
            if (root->rchild == NULL){
                root = root->lchild;
                free(toFree);
            } else if (root->lchild == NULL){
                root = root->rchild;
                free(toFree);
            } else {
                AVL* minNode = root->rchild;
                while (minNode->lchild != NULL){
                    minNode = minNode->lchild;
                }
                root->key = minNode->key;
                root->rchild = Delete(root->rchild, root->key);
            }
        } else if (key < root->key){
            root->lchild = Delete(root->lchild, key);
        } else if (key > root->key){
            root->rchild = Delete(root->rchild, key);
        }
        root = Balance(root);
    }
    return root;
}
    
void InOrder(AVL* root){
    if (root != NULL){
        InOrder(root->lchild);
        printf("%d ", root->key);
        InOrder(root->rchild);
    }
}

int main(){
    AVL* root = NULL;
    while(1){
        int value;
        char action;
        printf("input a number and press Enter: ");
        scanf("%d", &value);
        printf("insert(i) or delete(d)?: ");
        getchar();
        scanf("%c", &action);
        if (action == 'i'){
            root = Insert(root, value);
            InOrder(root);
            printf("\n");
        } else if (action == 'd'){
            root = Delete(root, value);
            InOrder(root);
            printf("\n");
        } else printf("\nplease input i or d");
    }
    clear(root);
    root = NULL;
    return 0;
}

