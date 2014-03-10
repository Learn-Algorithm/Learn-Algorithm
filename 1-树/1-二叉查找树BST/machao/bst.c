// file name : BST.c
// Author    : Ma Caho
// Update Date: 2012-2-19
// Compiler: gcc -o BST BST.c
// Run : ./BST
// input: 5 2 1 -1 -1 4 3 -1 -1 -1 7 6 -1 -1 8 -1 -1

#include <stdio.h>
#include <stdlib.h>

// Struct of BST
typedef int KEY_TYPE;

typedef struct BST_Node {
     KEY_TYPE element;
     struct BST_Node * LChild;
     struct BST_Node * RChild;     
} BST_Node, *BST;

// Create a BST
void create(BST * node) {
   int key;
   scanf("%i",&key);
   if (key == -1) {
      *node  = NULL;
   } else {
      *node = (BST)malloc(sizeof(BST_Node));
      (*node) -> element = key;
      create(&((*node) -> LChild));
      create(&((*node) -> RChild));
   }       
}

//Inert a value into BST
void insert(BST * root, int x) {
  if ((*root) -> element == x) printf("The insert value has existed!\n");
  else if((*root) -> element < x && (*root) -> RChild != NULL) {
     insert(&((*root) -> RChild), x);
  }
  else if((*root) -> element > x && (*root) -> LChild != NULL) {
     insert(&((*root) -> LChild), x);
  }
  else {
     BST node = (BST)malloc(sizeof(BST_Node));
     node -> element = x;
     node -> LChild = NULL;
     node -> RChild = NULL;
     if ((*root) -> element < x && (*root) -> RChild == NULL)
          (*root) -> RChild = node;
     else if ((*root) -> element > x && (*root) -> LChild == NULL)
          (*root) -> RChild = node;   
  }
}

//Search value from BST
BST_Node* search(BST root, int x) {
   if (root == NULL) return NULL;
   else if (root -> element == x) return root;
   else if (root -> element > x) search(root -> LChild, x);
   else search(root -> RChild, x);
}

void searchValue(BST root, int x) {
   BST_Node * node = search(root, x);
   if (node == NULL) printf("There is no element %i.\n",x);
   else {
      printf("%i is exist ! ", x);
      if (node -> LChild == NULL) printf("Its Left Chils is NULL.");
      else printf("Left Child is %i.", node -> LChild->element);

      if (node -> RChild == NULL) printf("Its Right Chils is NULL.\n");
      else printf("Right Chils is %i.\n", node -> RChild->element);
   }
}

//Remove a value from BST
BST_Node * delete(BST *root, int x) {
   if ((*root) == NULL) return NULL;
   else if (x < (*root) -> element) (*root)->LChild = delete(&((*root)->LChild), x);
   else if (x > (*root) -> element) (*root)->RChild = delete(&((*root)->RChild), x);
   else if ((*root) -> LChild == NULL) {
      BST q = (*root) -> LChild;
      free((*root));
      return q;
   }
   else if ((*root) -> LChild->RChild == NULL) {
      BST q = (*root) -> LChild;
      q -> RChild = (*root) -> RChild;
      free((*root));
      return q;
   }
   else {
      BST q;
      for (q = (*root)->LChild ; q->RChild->RChild != NULL ; q = q->RChild);
      BST r = q -> RChild;
      q -> RChild = r -> RChild;
      r -> LChild = (*root) -> LChild;
      r -> RChild = (*root) -> RChild;
      free((*root));
      return r;
   }
   return (*root);
}


//Inorder 
void inOrder(BST root) {
   if (root != NULL) {
       inOrder(root -> LChild);
       printf("%i ", root -> element);
       inOrder(root -> RChild);
   }
}

void main() {
   BST root;
   create(&root);
   printf("The BST is : ");
   inOrder(root);
   printf("\n");
   searchValue(root, 4);
   searchValue(root, 10);
   int insertValue = 11;
   insert(&root, insertValue);
   printf("After insert %i :", insertValue);
   inOrder(root);
   printf("\n");
   int deleteValue = 11;
   delete(&root, deleteValue);
   printf("After delete value %i :",deleteValue);
   inOrder(root);
   printf("\n");
   deleteValue = 7;
   delete(&root, deleteValue);
   printf("After delete value %i :", deleteValue);
   inOrder(root);
   printf("\n");   
}