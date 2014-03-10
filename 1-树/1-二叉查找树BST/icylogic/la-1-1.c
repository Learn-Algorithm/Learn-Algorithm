#include "stdio.h"
#include "stdlib.h"

//types
typedef int KEY_TYPE;

typedef struct Node{
    KEY_TYPE key;
    struct Node* lchild;
    struct Node* rchild;
}Node;

Node* create(KEY_TYPE key){
    Node* root = (Node*)malloc(sizeof(Node));
    root->key = key;
    root->lchild = root->rchild = NULL;
    return root;
}

Node* insert(Node* parent, KEY_TYPE childKey){
    if (parent == NULL){
        parent = (Node*)malloc(sizeof(Node));   //may out of memory
        parent->key = childKey;
        parent->lchild = parent->rchild = NULL;
    } else if (childKey < parent->key){
        parent->lchild = insert(parent->lchild, childKey);
    } else if (childKey > parent->key){
        parent->rchild = insert(parent->rchild, childKey);
    }
    return parent;
    //if key already exists: do nothing
}

Node* search(Node* parent, KEY_TYPE childKey){
    if (parent == NULL || parent->key == childKey){
        return parent;
    } else if (childKey < parent->key){
        return search(parent->lchild, childKey);
    } else {
        return search(parent->rchild, childKey);
    }
}

Node* searchMin(Node* parent){
    if (parent->lchild != NULL)     //need to ensure if parent is NULL
        return searchMin(parent->lchild);
    else
        return parent;
}

Node* delete(Node* parent, KEY_TYPE childKey){
    if (parent->key == childKey){   //exit of recursion
        if (parent->lchild == NULL){
            Node* deleteNode = parent;
            parent = parent->rchild;
            free(deleteNode);
        } else if (parent->rchild == NULL){
            Node* deleteNode = parent;
            parent = parent->lchild;
            free(deleteNode);
        } else {
            Node* minNode = searchMin(parent->rchild);
            parent->key = minNode->key;
            parent->rchild = delete(parent->rchild, parent->key);
        }
    } else if (childKey < parent->key){
        parent->lchild = delete(parent->lchild, childKey);
    } else if (childKey > parent->key){
        parent->rchild = delete(parent->rchild, childKey);
    }
    return parent;
}

void inOrder(Node* parent){
    if (parent != NULL){
        inOrder(parent->lchild);
        printf("%d ", parent->key);
        inOrder(parent->rchild);
    }
}


int main(){
    Node* root = create(0);
    printf("create root, key of root = 0\n");

    insert(root, 1);
    insert(root, 3);
    insert(root, 2);
    insert(root, 4);
    printf("insert 0, 1, 3, 2, 4\n");
    
    Node* node = search(root, 3);
    printf("search 3: lchild %d, rchild %d\n", node->lchild->key, node->rchild->key);

    printf("in order: ");
    inOrder(root);

    delete(root, 3);
    printf("\ndelete 3: ");
    inOrder(root);

    free(root);
}
