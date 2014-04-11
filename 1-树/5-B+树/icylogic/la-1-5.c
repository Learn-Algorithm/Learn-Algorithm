#include "stdio.h"
#include "stdlib.h"
#define ORDER 4

typedef char Value;
typedef enum {false, true} bool;

typedef struct BPTree {
    int keyNum;
    int keys[ORDER]; //+1 for temp key
    bool isLeaf;
    Value values[ORDER]; //+1 for temp value
    struct BPTree *parent;
    struct BPTree *next;
    struct BPTree *childs[ORDER + 1]; //+1 for temp child
}BPTree;

bool isSplited = false;

BPTree* makeNewTree(int, Value);
BPTree* insertIntoLeaf(BPTree*, int, Value);
BPTree* insertIntoNode(BPTree*, int, Value);
BPTree* split(BPTree*);
BPTree* insert(BPTree*, int, Value);
Value find(BPTree*, int);
void printTree(BPTree*);

BPTree* makeNewTree(int key, Value value){
    BPTree* newTree = malloc(sizeof(BPTree));
    newTree->keyNum = 1;
    newTree->keys[0] = key;
    if (value != NULL){
        newTree->values[0] = value; //make a leaf or global root
        newTree->isLeaf = true;
    } else newTree->isLeaf = false;
    newTree->next = NULL;
    newTree->parent = NULL;
    return newTree;
}

BPTree* insertIntoLeaf(BPTree* leaf, int key, Value value){
    int i,j;
    for (i = 0; i < leaf->keyNum; i++){
        if (key == (leaf->keys)[i]) return leaf;
        if (key < (leaf->keys)[i]) break;
    }
    for (j = leaf->keyNum; j > i; j--){
        (leaf->keys)[j] = (leaf->keys)[j - 1];
        (leaf->values)[j] = (leaf->values)[j - 1];
    }
    (leaf->keys)[i] = key;
    (leaf->values)[i] = value;
    (leaf->keyNum)++;
    return leaf;
}

BPTree* insertIntoNode(BPTree* tree, int key, Value value){
    int i,j;
    BPTree* newChild;
    for (i = 0; i < tree->keyNum; i++){
        if (key < (tree->keys)[i]) break;
    }

    newChild = insert((tree->childs)[i], key, value);
    if (isSplited){ //if child is splited
        for (j = tree->keyNum; j > i; j--){
            (tree->childs)[j + 1] = (tree->childs)[j];
            (tree->keys)[j] = (tree->keys)[j - 1];
        }
        (tree->childs)[i + 1] = newChild->next;
        if (newChild->isLeaf) (tree->keys)[i] = newChild->keys[(newChild->keyNum) - 1];  //record max of child's keys
        else (tree->keys)[i] = (newChild->childs[newChild->keyNum])->keys[ (newChild->childs[newChild->keyNum])->keyNum - 1];  //max of left tree, var in () is right child of newchild
        (tree->keyNum)++;
    }
    (tree->childs)[i] = newChild;
    return tree;
}

BPTree* split(BPTree* tree){
    int i;
    BPTree *newRoot;
    BPTree *newTree = malloc(sizeof(BPTree));
    newTree->keyNum = (tree->keyNum)/2;

    for (i = 1; i <= newTree->keyNum; i++){
        newTree->keys[newTree->keyNum - i] = tree->keys[tree->keyNum - i];
        tree->keys[tree->keyNum - i] = NULL;
    }

    if (tree->isLeaf){ //split leaf
        for (i = 1; i <= newTree->keyNum; i++){
            newTree->values[newTree->keyNum - i] = tree->values[tree->keyNum - i];
            tree->values[tree->keyNum - i] = NULL;
        }
        newTree->isLeaf = true;
        tree->isLeaf = true;
    } else {  //split inner node or global tree
        for (i = 0; i <= newTree->keyNum; i++){
            newTree->isLeaf = false;
            newTree->childs[newTree->keyNum - i] = tree->childs[tree->keyNum - i];
            tree->childs[tree->keyNum - i] = NULL;
        }
    }

    newTree->next = tree->next;
    tree->next = newTree;
    newTree->parent = tree->parent;
    tree->keyNum = tree->keyNum - newTree->keyNum;
    tree->keyNum = tree->keyNum - 1 + tree->isLeaf;

    if (tree->parent == NULL){ //split global tree
        newRoot = malloc(sizeof(BPTree));
        newRoot->keyNum = 1;
        newRoot->parent = NULL;
        newRoot->next = NULL;
        newRoot->keys[0] = tree->keys[tree->keyNum - tree->isLeaf];
        newRoot->isLeaf = false;
        tree->parent = newRoot;
        newRoot->childs[0] = tree;
        newTree->parent = newRoot;
        newRoot->childs[1] = newTree;
        return newRoot;
    }
    else return tree;
}

BPTree* insert(BPTree* tree, int key, Value value){
    if (tree == NULL) tree = makeNewTree(key, value);
    else if (tree->isLeaf) tree = insertIntoLeaf(tree, key, value);
    else tree = insertIntoNode(tree, key, value);

    isSplited = (tree->keyNum) == ORDER; //if tree needs to be splited
    if (isSplited) tree = split(tree);
    return tree;
}

Value find(BPTree* tree, int key){
    int i;
    for (i = 0; i <= tree->keyNum; i++){
        if (key == *(tree->keys + i)){
            if (tree->isLeaf) return (tree->values)[i];
            else return find((tree->childs)[i], key);
        }
        else if (key < *(tree->keys + i)) return find((tree->childs)[i], key);
    }
    return NULL;
}

void printTree(BPTree* tree, int level){
    int i;
    for (i = 0; i < tree->keyNum; i++) printf("%c;", (tree->keys)[i]);
    for (i = 0; i <= tree->keyNum; i++) {
        if (!tree->isLeaf) {
            printf("\nchilds of level %d, child %d: ", level, i);
            printTree(tree->childs[i], (level + 1));
        }
    }
}

//delete incomplete

int main(){
    BPTree* root = NULL;
    char testValues[] = "cngahekqmfwltzdprxys";
    int i;
    for (i = 0; i < 20; i++){
        root = insert(root, testValues[i], testValues[i]);
        printf("\n\nafter insert %c:\n", testValues[i]);
        printTree(root, 0);
    }
    return 0;
}

