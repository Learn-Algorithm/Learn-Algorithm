//
//  bst.c
//
//  Created by zentorwie on 23-2-2014
//  Copyright (c) 2014 zentorwie. All rights reserved.

#include <stdio.h>
#include <stdlib.h>

typedef int KEY_TYPE;

typedef struct Node {
  KEY_TYPE key;
  struct Node* lChild;
  struct Node* rChild;
} Node;

Node* Create(KEY_TYPE x);            // Create a BST
Node* Insert(KEY_TYPE x, Node* T);   // Insert x into T
Node* Search(KEY_TYPE x, Node* T);   // Search x in T
Node* Delete(KEY_TYPE x, Node* T);   // Delete x in T
void inOrder(Node* T);

Node* FindMin(Node* T);  // Addition function to find minimum node


int main()
{
  Node* T;
  Node* tmpNode;
  printf("Create a BST and set the key of root as 3");
  T = Create(3);
  
  printf("In-order traverse:\n");
  inOrder(T);
  printf("\n");

  printf("Insert 5\n");
  Insert(5, T);

  printf("Insert 5\n");
  Insert(5, T);

  printf("Insert 6\n");
  Insert(6, T);
  
  printf("Insert 1\n");
  Insert(1, T);
  
  printf("Insert 2\n");
  Insert(2, T);

  printf("Insert 7\n");
  Insert(7, T);
  printf("Insert 19\n");
  Insert(19, T);
  printf("Insert 20\n");
  Insert(20, T);


  printf("In-order traverse:\n");
  inOrder(T);
  printf("\n");
  
  printf("Delete 5\n");
  T = Delete(5, T);

  printf("In-order traverse:\n");
  inOrder(T);
  printf("\n");
  
  printf("Delete 19\n");
  T = Delete(19, T);

  printf("In-order traverse:\n");
  inOrder(T);
  printf("\n");
  
  printf("Search 7\n");
  tmpNode =  Search(7, T);
  if (tmpNode)
    printf("%d found\nAddr: %X\n", tmpNode->key, tmpNode);
  else
    printf("7 not found\n");

  printf("Search 21\n");
  tmpNode =  Search(21, T);
  if (tmpNode)
    printf("%d found\nAddr: %X\n", tmpNode->key, tmpNode);
  else
    printf("21 not found\n");

  return 0;
}



//Create a BST whose root has key x
Node* Create(KEY_TYPE x)
{
  Node* T = (Node*)malloc(sizeof(Node));
  if (T == NULL) {
    printf("Creating BST failed: Out of space\n");
    exit(1);
  }
  T->key = x;
  T->lChild = T->rChild = NULL;
  return T;
}


//Insert a node whose key is x, if x exist, do nothing
Node* Insert(KEY_TYPE x, Node* T)
{
  if (T == NULL) {
    T = (Node*)malloc(sizeof(Node));
    if (T == NULL) {
      printf("Out of space!\n");
      exit(1); 
    }

    T->key = x;
    T->lChild = T->rChild = NULL;
  }
  else if (x < T->key) {
    T->lChild = Insert(x, T->lChild);
  }
  else if (x > T->key) {
    T->rChild = Insert(x, T->rChild);
  }
  // key exist already, do nothing
  
  return T;
}

//Search the node whose key is x 
Node* Search(KEY_TYPE x, Node* T)
{
  if (T == NULL)
    return NULL;
  else if (x < T->key) 
    return Search(x, T->lChild);
  else if (x > T->key)
    return Search(x, T->rChild);
  else
    return T;
}

//Delete the node whose key is x
Node* Delete(KEY_TYPE x, Node* T) 
{
  Node* tmpNode;
  
  if (T == NULL) {
    printf("Key not found!\n");
  }
  else if (x < T->key) {  // go to left to find x
    T->lChild = Delete(x, T->lChild);
  }
  else if (x > T->key) {  // go to right to find x
    T->rChild = Delete(x, T->rChild);
  }
  else if (T->lChild && T->rChild) {  // key found and 2-child case
    tmpNode = FindMin(T->rChild);
    T->key = tmpNode->key;
    T->rChild = Delete(tmpNode->key, T->rChild);
  }
  else {  // 1-child or non-child case
    tmpNode = T;

    if (T->lChild)
      T = T->lChild;
    else if (T->rChild)
      T = T->rChild;
    else  // non-child
      T = NULL;
    
    free(tmpNode);
  }
  return T;
}


//In-order traverse
void inOrder(Node* T)
{
  if (T == NULL)
    return;
  inOrder(T->lChild);
  printf("%d\n", T->key);
  inOrder(T->rChild);
}


//Find the minimum node in T
Node* FindMin(Node* T)
{
  if (T == NULL) {
    return NULL;
  }
  else if (T->lChild == NULL) {
    return T; //if T is a leaf, T is the smallest.
  }
  else 
    return FindMin(T->lChild);
}
