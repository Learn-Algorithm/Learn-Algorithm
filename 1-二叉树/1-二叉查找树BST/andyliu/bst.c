//andyliu create 2014-2-23
//Binary search tree  in C lanuage

#include <stdio.h>

typedef int KEY_TYPE ;

typedef struct Node{
	KEY_TYPE key ;
	struct Node* lchild ;
	struct Node* rchild ;
}Node,*TreeNode;

Node*  create(TreeNode T)
{
	if(T !=  NULL)
	{
		create( T->lchild );
		create( T->rchild );
		free(T);
	}
	return NULL ;
}

Node* insert(KEY_TYPE KEY,TreeNode T)
{
	if( T == NULL)
	{
		T = malloc(sizeof(Node));
		if( T == NULL )
		{
			printf("Null!");
			return  NULL;
		//	error()//
		}
		else {
			T->key = KEY ;
			T->lchild =T->rchild = NULL;
		}
	}
	else {
		if( T->key > KEY)
		{
			T->lchild = insert(KEY , T->lchild);
		}
		else if (T->key < KEY) {
			T->rchild = insert(KEY ,T->rchild);
		}
		
		return T ;
	}
}

Node* search(KEY_TYPE KEY,TreeNode T)
{
	if( T == NULL)
	{
		return NULL;
	}
	else if ( T->key > KEY) {
		return search(KEY,T->lchild);
	}
	else if ( T->key < KEY) {
		return search(KEY , T->rchild);		
	}
	else
	return  T ;
}

Node* delete(KEY_TYPE KEY,TreeNode T)
{
	Node *temp ;
	
	if(T == NULL)
	{
		printf("Null!");
		return NULL ;
	}
	else if (KEY < T->key) {
		T->lchild = delete(KEY,T->lchild);
	}else if (KEY > T->key) {
		T->rchild = delete(KEY,T->lchild);
	}else if (T->lchild && T->rchild) {
	    temp =findmin(T->rchild); 
		T->key = temp->key ;
		T->rchild = delete(T->key,T->rchild);
	}else {
		temp =T ;
		if( T -> lchild == NULL)
		  T = T->rchild;
		else if (T->rchild == NULL) {
		  T =T->lchild ;
		}
		free(temp);
	}
	
	return T ;
	
}

void inOrder(TreeNode T)
{
	if(!(T == NULL))
	{
		inOrder(T->lchild);
		printf("T->key is %d \n",T->key);
		inOrder(T->rchild);
	}
}
Node* findmin(KEY_TYPE KEY,TreeNode T)
{
	 
	if(T == NULL)
	   return NULL;
	else if (T->lchild == NULL) {
	   return T ;
	}else  
	   return findmin(T->lchild); 
	
}
int main(int argc, char *argv[]) {
//	printf("andy test\n");
}