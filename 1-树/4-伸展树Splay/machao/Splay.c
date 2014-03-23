/*
 file:    Splay.c
 author:  machao
 date:    2014-3-14
 compile: gcc -o Splay Splay.c
 run:     ./splay
 */

#include <stdio.h>
#include <stdlib.h>

typedef int KEY_TYPE;

typedef struct Splay_Node {
	KEY_TYPE element;
	struct Splay_Node * Lchild;
	struct Splay_Node * Rchild;
	struct Splay_Node * Parent;
} Splay_Node, *Splay;


//Global variable, easy to use
Splay root;


void inOrder(Splay root) {
	if (root != NULL) {
		inOrder(root -> Lchild);
		printf("%i ", root -> element);
		inOrder(root -> Rchild);
	}
}

void preOrder(Splay root) {
	if(root != NULL) {
		printf("%i ", root -> element);
		preOrder(root -> Lchild);
		preOrder(root -> Rchild);
	}
}


void Right_Rotate(Splay_Node* node) {
    Splay_Node* ptr = node -> Parent;
    ptr -> Lchild = node -> Rchild;
    node -> Rchild = ptr;
    node -> Parent = ptr -> Parent;
    if(ptr -> Parent != NULL) {
      if(ptr -> Parent -> Lchild == ptr) ptr->Parent->Lchild = node;
      else if(ptr -> Parent -> Rchild == ptr) ptr -> Parent -> Rchild = node;
    }
    ptr -> Parent = node; 
}

void Left_Rotate(Splay_Node* node) {
	Splay_Node* ptr = node -> Parent;
	ptr -> Rchild = node -> Lchild;
	node -> Lchild = ptr;
	node -> Parent = ptr->Parent;
	if(ptr->Parent != NULL) {
	  if(ptr -> Parent -> Rchild == ptr) ptr->Parent->Rchild = node;
	  else if(ptr -> Parent -> Lchild == ptr) ptr->Parent->Lchild = node;
    }
	ptr -> Parent = node;
}

void SplayTree(Splay_Node* node) {
	//Rotate until node become root;
	while(1) {
		if(node -> Parent == NULL) {
			root = node;
			//preOrder(node);
			//printf("\n");
			break;
		}
		// Parent is root
		else if(node -> Parent -> Parent == NULL) {
			//Right_Rotate
		    if(node -> Parent -> Lchild == node) {Right_Rotate(node);}
		    //Left_Rotate
		    else if(node -> Parent -> Rchild == node){Left_Rotate(node);}
		}
		//Parent is not root
		else if(node -> Parent -> Parent != NULL) {
            //Right_Right
			if(node -> Parent -> Lchild == node && 
				node -> Parent -> Parent -> Lchild == node -> Parent) {
				Right_Rotate(node->Parent);
			    Right_Rotate(node);
			}
		    //Left_Left
		    else if(node -> Parent -> Rchild == node &&
		    	     node -> Parent -> Parent -> Rchild == node -> Parent) {
		    	Left_Rotate(node->Parent);
		        Left_Rotate(node);
		    }
		    //Right_Left
		    else if(node -> Parent -> Lchild == node && 
		    	     node -> Parent -> Parent -> Rchild == node -> Parent) {
		    	Right_Rotate(node);
		        Left_Rotate(node);
		    }
		    //Left_Right
		    else if(node -> Parent -> Rchild == node &&
		             node -> Parent -> Parent -> Lchild == node -> Parent ) {
		    	Left_Rotate(node);
		        Right_Rotate(node);
		    } 
		}
	}
}


void initial(Splay* root, KEY_TYPE x) {
    (*root) = (Splay)malloc(sizeof(Splay_Node));
    (*root) -> element = x;
    (*root) -> Lchild = NULL;
    (*root) -> Rchild = NULL;
    (*root) -> Parent = NULL;
}

void insert(Splay* root, KEY_TYPE x, int bo) {
	if((*root) -> element == x) return;
	else if((*root) -> element < x && (*root) -> Rchild != NULL) {
		insert(&((*root) -> Rchild), x, bo);
	}
	else if((*root) -> element > x && (*root) -> Lchild != NULL) {
		insert(&((*root) -> Lchild), x, bo);
	}
	else {
		Splay_Node* node = (Splay)malloc(sizeof(Splay_Node));
		node -> element = x;
		node -> Lchild = NULL;
		node -> Rchild = NULL;
		node -> Parent = *root;
		if((*root) -> element < x && (*root) -> Rchild == NULL) 
			(*root) -> Rchild = node;
		else if((*root) -> element > x && (*root) -> Lchild == NULL)
			(*root) -> Lchild = node;
		if(bo == 1)
		  SplayTree(node);
	}
}

int search(Splay root, KEY_TYPE x) {
	if(root == NULL) return -1;
	else if(root -> element == x) {
		int element = root->element;
		SplayTree(root);
		return element;
	}
	else if(root -> element > x) search(root -> Lchild, x);
	else if(root -> element < x) search(root -> Rchild, x);
}

Splay_Node* delete(Splay* root, KEY_TYPE x) {
   if ((*root) == NULL) return NULL;
   else if (x < (*root) -> element) (*root)->Lchild = delete(&((*root)->Lchild), x);
   else if (x > (*root) -> element) (*root)->Rchild = delete(&((*root)->Rchild), x);
   else if ((*root) -> Lchild == NULL) {
      Splay q = (*root) -> Lchild;
      free((*root));
      return q;
   }
   else if ((*root) -> Lchild->Rchild == NULL) {
      Splay q = (*root) -> Lchild;
      q -> Rchild = (*root) -> Rchild;
      free((*root));
      return q;
   }
   else {
      Splay q;
      for (q = (*root)->Lchild ; q->Rchild->Rchild != NULL ; q = q->Rchild);
      Splay r = q -> Rchild;
      q -> Rchild = r -> Rchild;
      r -> Lchild = (*root) -> Lchild;
      r -> Rchild = (*root) -> Rchild;
      free((*root));
      return r;
   }
   return (*root);
}

void printInfo(int v) {
	if(v == -1) printf("Node is not exists! \n");
	else printf("Node is exists, the element is %i .\n", v);
	preOrder(root);
	printf("\n");
}

void createSplay(Splay* root, KEY_TYPE array[], int len) {
	printf("Create Splay:..");
	initial(root, array[0]);
	int i;
	for(i = 1 ; i < len ; i++)
       insert(root, array[i], 0);
    preOrder(*root);
	printf("\n");
}

int main() {
    
    // Splay1
    int array1[5] = {5, 3, 6, 2, 4};
    createSplay(&root, array1, 5);
    int v1 = search(root, 3);
    printInfo(v1);

    printf("insert 10 to root1.\n");
    insert(&root, 10, 1);
    preOrder(root);
    printf("\n");

    printf("Delete 2 from root1.\n");
    delete(&root, 2);
    preOrder(root);
    printf("\n");

	return 0;
}