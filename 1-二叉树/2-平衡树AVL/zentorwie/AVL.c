//
// AVL.c
// Created by zentorwie on 25-2-2014

#include <stdio.h>
#include <stdlib.h>

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
typedef int KeyType;
struct AvlNode {
  KeyType key;
  int height;
  AvlTree left;
  AvlTree right;
};

AvlTree RR_Rotate(AvlTree T);
AvlTree LL_Rotate(AvlTree T);
AvlTree LR_Rotate(AvlTree T);
AvlTree RL_Rotate(AvlTree T);

void InOrder(AvlTree T);
AvlTree Insert(KeyType X, AvlTree T);
AvlTree Delete(KeyType X, AvlTree T);

Position Find(KeyType X, AvlTree T);
int Max(int A, int B);
int Height(AvlTree T);
Position FindMin(AvlTree T);

int main()
{
  int n, i, t;
  char ch;
  AvlTree T = NULL, TT = NULL;
  srand((int)time(0));  // for random inserting and deleting test
  for (i = 0; i < 20; i++) {
    t = rand() % 10;
    if (t % 2) {
      t = rand() % 10;
      printf("Insert %d\n", t);
      T = Insert(t, T);
      printf("[ ");
      InOrder(T);
      printf("]\n\n");
    }
    else {
      t = rand() % 10;
      printf("Delete %d\n", t);
      T = Delete(t, T);
      printf("[ ");
      InOrder(T);
      printf("]\n\n");
    }
  }
  return 0;
}



AvlTree RR_Rotate(Position oldRoot)
{
  Position newRoot;
  // Rotate
  newRoot = oldRoot->right;
  oldRoot->right = newRoot->left;
  newRoot->left = oldRoot;
  // Update height
  oldRoot->height = Max(Height(oldRoot->left), Height(oldRoot->right)) + 1;
  newRoot->height = Max(Height(newRoot->left), Height(newRoot->right)) + 1;
  
  return newRoot;
}

AvlTree LL_Rotate(Position oldRoot)
{
  Position newRoot;
  // Rotate
  newRoot = oldRoot->left;
  oldRoot->left = newRoot->right;
  newRoot->right = oldRoot;
  // Update height
  oldRoot->height = Max(Height(oldRoot->left), Height(oldRoot->right)) + 1;
  newRoot->height = Max(Height(newRoot->left), Height(newRoot->right)) + 1;

  return newRoot;
}

AvlTree LR_Rotate(Position oldRoot) 
{
  Position newRoot;
  oldRoot->left = RR_Rotate(oldRoot->left);
  return LL_Rotate(oldRoot);
}

AvlTree RL_Rotate(Position oldRoot) 
{
  Position newRoot;
  oldRoot->right = LL_Rotate(oldRoot->right);
  return RR_Rotate(oldRoot);
}

void InOrder(AvlTree T)
{
  if (T == NULL) 
    return;
  InOrder(T->left);
  printf("%d ", T->key);
  InOrder(T->right);
}

AvlTree Insert(KeyType X, AvlTree T)
{
  if (T == NULL) {
    T = (AvlTree)malloc(sizeof(struct AvlNode));
    if (T == NULL) {
      printf("Error: Out of space!\n");
      exit(1);
    }
    T->key = X;
    T->left = T->right = NULL;
  }
  else if (X < T->key) {
    T->left = Insert(X, T->left);
    if (Height(T->left) - Height(T->right) == 2) {
      if (X < T->left->key)	
	T = LL_Rotate(T); 
      else
	T = LR_Rotate(T);
    }
  }
  else if (X > T->key) {
    T->right = Insert(X, T->right);
    if (Height(T->right) - Height(T->left) == 2) {
      if (X > T->right->key) 
	T = RR_Rotate(T);
      else
	T = RL_Rotate(T);
    }
  }
  T->height = Max(Height(T->left), Height(T->right)) + 1;
  return T;
}

AvlTree Delete(KeyType X, AvlTree T) 
{
  Position tmp;
  if (T == NULL) 
    printf("Key not found!\n");
  else if (X < T->key) {  // go to left
    T->left = Delete(X, T->left);
    if (Height(T->right) - Height(T->left) == 2)
      T = RR_Rotate(T);
    // After deleting a node in T->left, 
    // if imbalanced, it must be right-right case.
  }
  else if (X > T->key) {  // go to right
    T->right = Delete(X, T->right);
    if (Height(T->left) - Height(T->right) == 2) 
      T = LL_Rotate(T);  
    // After deleting a node in T->right, 
    // if imbalanced, it must be left-left case.
  }
  else if (T->left && T->right) {  // 2-child
    tmp = FindMin(T->right);
    T->key = tmp->key;
    T->right = Delete(tmp->key, T->right);
  }
  else {
    tmp = T;
    if (T->left) // left child only
      T = T->left;
    else if (T->right) // right child only
      T = T->right;
    else
      T = NULL;  // T is a leaf.
    free(tmp);
  }
  
  if (T != NULL)
    T->height = Max(Height(T->left), Height(T->right)) + 1;
  return T;
}

Position Find(KeyType X, AvlTree T)
{
  if (T == NULL) {
    printf("Key not found!\n");
    return NULL;
  }
  else if (X < T->key) 
    return Find(X, T->left);
  else if (X > T->key)
    return Find(X, T->right);
  else
    return T;
}

int Max(int A, int B)
{
  if (A > B)
    return A;
  else
    return B;
}

int Height(AvlTree T)
{
  if (T == NULL)
    return -1;
  else
    return T->height;
}

Position FindMin(AvlTree T)
{
  if (T == NULL) {
    printf("Key not found!\n");
    return NULL;
  }
  else if (T->right == NULL) 
    return T;
  else
    return FindMin(T->right);
}



