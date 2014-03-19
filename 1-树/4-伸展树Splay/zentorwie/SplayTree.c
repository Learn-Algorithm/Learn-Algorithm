//
//  SplayTree.c
//  Created by zentorwie on 2014-03-17

#include <stdio.h>
#include <stdlib.h>

#define KEY_TYPE int

struct SplayNode {
  KEY_TYPE Key;
  struct SplayNode* Left;
  struct SplayNode* Right;
};

typedef struct SplayNode* SplayTree;
SplayTree Initialize(void);
SplayTree Insert(KEY_TYPE x, SplayTree T);
SplayTree Remove(KEY_TYPE x, SplayTree T);
SplayTree Splay(int x, SplayTree Root);
SplayTree Find(KEY_TYPE x, SplayTree T);
SplayTree FindMin(SplayTree T);
SplayTree FindMax(SplayTree T);
SplayTree RotateWithLeft(SplayTree T);
SplayTree RotateWithRight(SplayTree T);
void InOrder(SplayTree T);
static KEY_TYPE Retrieve(SplayTree Node);

static SplayTree NullNode = NULL;

int main()
{
  SplayTree T = Initialize();

  T = Insert(1, T);

  T = Insert(2, T);
  T = Insert(3, T);
  T = Insert(4, T);
  T = Insert(9, T);
  T = Insert(8, T);

  InOrder(T);
  puts("haha");
  T = Find(4, T);

  InOrder(T);
  return 0;
}

SplayTree Initialize(void) 
{
  if (NullNode == NULL) {
    NullNode = (SplayTree)malloc(sizeof(struct SplayNode));
    if (NullNode == NULL) {
      printf("Out of space!\n");
      exit(1);
    }
    NullNode->Left = NullNode->Right = NullNode;
  }
  return NullNode;
}

SplayTree Insert(KEY_TYPE x, SplayTree T)
{
  static SplayTree NewNode = NULL;
  
  if (NewNode == NULL) {
    NewNode = (SplayTree)malloc(sizeof(struct SplayNode));
    if (NewNode == NULL) {
      printf("Out of space!\n");
      exit(1);
    }
  }
  T->Key = x;
  
  if (T == NullNode) {
    NewNode->Left = NewNode->Right = NullNode;
    T = NewNode;
  }
  else {
    T = Splay(x, T);
    if (x < T->Key) {
      NewNode->Left = T->Left;
      NewNode->Right = T;
      T->Left = NullNode;
      T = NewNode;
    }
    else if (x > T->Key) {
      NewNode->Right = T->Right;
      NewNode->Left = T;
      T->Right = NullNode;
      T = NewNode;
    }
    else 
      return T;
  }
  
  NewNode = NULL;
  return T;
}


SplayTree Remove(KEY_TYPE x, SplayTree T)
{
  SplayTree NewTree;

  if (T != NullNode) {
    T = Splay(x, T);
    if (x == T->Key) {
      if (T->Left == NullNode) 
	NewTree = T->Right;
      else {
	NewTree = T->Left;
	NewTree = Splay(x, NewTree);
	NewTree->Right = T->Right;
      }
      free(T);
      T = NewTree;
    }
  }
  return T;
}

SplayTree Splay(KEY_TYPE x, SplayTree Root)
{
  static struct SplayNode Header;
  SplayTree LeftTreeMax, RightTreeMin;

  Header.Left = Header.Right = NullNode;
  LeftTreeMax = RightTreeMin = &Header;
  NullNode->Key = x;
  
  while(x != Root->Key) {
    if (x < Root->Key) {
      if (x < Root->Left->Key)
	Root = RotateWithLeft(Root);
      if (Root->Left == NullNode) 
	break;
      RightTreeMin->Left = Root;
      RightTreeMin = Root;
      Root = Root->Left;
    }
    else {
      if (x > Root->Key) 
	Root = RotateWithRight(Root);
      if (Root->Right == NullNode)
	break;
      LeftTreeMax->Right = Root;
      LeftTreeMax = Root;
      Root = Root->Right;
    }
  } /* while (x != Root->Key) */

  /* Reassemble */
  LeftTreeMax->Right = Root->Left;
  RightTreeMin->Left = Root->Right;
  Root->Left = Header.Right;
  Root->Right = Header.Left;

  return Root;
}

SplayTree Find(KEY_TYPE X, SplayTree T)
{
  SplayTree Target;
  Target = Splay(X, T);
  if (T == NULL || Target->Key != X) {
    printf("Not found!\n");
    return NULL;
  }
  else
    return T;
}

SplayTree FindMin(SplayTree T)
{
  if (T == NULL)
    return NULL; // Not found.
  if (T->Left == NULL)
    return T;
  else
    return FindMin(T->Left);
}

SplayTree FindMax(SplayTree T)
{
  if (T == NULL)
    return NULL; // Not found
  if (T->Right == NULL)
    return T;
  else
    return FindMax(T->Right);
}

SplayTree RotateWithLeft(SplayTree T)
{
  SplayTree NewRoot;

  NewRoot = T->Left;
  T->Left = NewRoot->Right;
  NewRoot->Right = T;

  return NewRoot;
}

SplayTree RotateWithRight(SplayTree T)
{
  SplayTree NewRoot;
  NewRoot = T->Right;
  T->Right = NewRoot->Left;
  NewRoot->Left = T;

  return NewRoot;
}


void InOrder(SplayTree T)
{
  if (T == NullNode)
    return;
  InOrder(T->Left);
  printf("%d\n", T->Key);
  InOrder(T->Right);
}

static KEY_TYPE Retrieve(SplayTree Node)
{
  return Node->Key;
}
