// Author  : Machao
// File    : AVL.C
// Date    : 2013-2-27
// Compile : gcc -o AVL AVL.c
// Run     : ./AVL


#include <stdio.h>
#include <stdlib.h>

#define MAX(A, B) ((((A) > (B)) ? (A) : (B)) + 1 )

typedef struct AVL {
   int data;
   int height;
   struct AVL *lchild;
   struct AVL *rchild;
} AVL_Node, *AVL;

void Inisit(AVL* T, int c) {
   *T = (AVL)malloc(sizeof(AVL_Node));
   (*T) -> data = c;
   (*T) -> rchild = (*T) -> lchild = NULL;
}

AVL_Node* search(AVL root, int x) {
    if (root == NULL) return NULL;
    else if (root -> data == x) return root;
    else if (root -> data > x) search(root -> lchild, x);
    else search(root -> rchild, x);
}

void searchValue(AVL root, int x) {
    AVL_Node* node = search(root, x);
    if (node == NULL) printf("There is no element %i.\n", x);
    else {
       printf("%i is exist !",x);
       if (node -> lchild == NULL) printf("Its left child is NULL");
       else printf("Left child is %i.", node -> lchild -> data);

       if (node -> rchild == NULL) printf("Its right child is NULL.\n");
       else printf("Right child is %i.\n", node -> rchild -> data);       
    }
}

void inOrder(AVL root) {
    if (root != NULL) {
       inOrder(root -> lchild);
       printf("%i ", root -> data);
       inOrder(root -> rchild);
    }	    
}

int Height(AVL T) {
    if (T) return T -> height;
    return -1;
}

AVL SingleLeft(AVL k1) {
   AVL k2;

   k2 = k1 -> rchild;
   k1 -> rchild = k2 -> lchild;
   k2 -> lchild = k1;

   k1 -> height = MAX(Height(k1->lchild), Height(k1->rchild));
   k2 -> height = MAX(Height(k2->rchild), Height(k1));

   return k2;
}

AVL SingleRight(AVL k1) {
   AVL k2;

   k2 = k1 -> lchild;
   k1 -> lchild = k2 -> rchild;

   k1 -> height = MAX(Height(k1->lchild), Height(k1->rchild));
   k2 -> height = MAX(Height(k2->lchild), Height(k1));

   return k2;
}

AVL RightLeft(AVL k1) {
   k1 -> rchild = SingleRight(k1 -> rchild);
   return SingleLeft(k1);
}

AVL LeftRight(AVL k1) {
   k1 -> lchild = SingleLeft(k1 -> lchild);
   return SingleRight(k1);
}

AVL Insert(AVL T, int c) {
   if (!T) {
      T = (AVL)malloc(sizeof(AVL_Node));
      if (!T) {
          return NULL; //ERROR
      }
      T -> lchild = T -> rchild = NULL;
      T -> data = c;
   }
   if (c > T -> data) {
      T -> rchild = Insert(T -> rchild, c);
      if (Height(T -> rchild) - Height(T -> lchild) == 2)
	  if (c > T->rchild->data)
		T = SingleLeft(T);  
          else T = RightLeft(T);
   }
   else if (c < T -> data) {
      T -> lchild = Insert(T->lchild, c);
      if (Height(T->lchild) - Height(T->rchild) == 2)
	  if (c < T -> lchild->data)
	      T = SingleRight(T);
          else
	      T = LeftRight(T);	  
   }

   T -> height = MAX(Height(T->lchild), Height(T->rchild));

   return T;
}

int main() {
 
   AVL T;
   int i;
   int s[] = {2, 6, 1, 3, 5, 7, 16, 15, 14, 13, 12, 11, 8, 9, 10};
   Inisit(&T, 4);

   for (i = 0 ; i < 15 ; i++)
      T = Insert(T, s[i]);   
   
   printf("The AVL is: ");
   inOrder(T);
   printf("\n");
   searchValue(T, 5);
   searchValue(T, 10);
   searchValue(T, 20);   
   return 0;
}

