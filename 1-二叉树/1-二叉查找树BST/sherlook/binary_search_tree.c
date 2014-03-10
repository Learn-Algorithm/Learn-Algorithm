#include <stdio.h>
#include <malloc.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

typedef int KEY_TYPE;

typedef struct Node
{
	KEY_TYPE key;
	struct Node* left_child;
	struct Node* right_child;
} Node, *BST_Tree;

//help functions
Node* CreateNode(KEY_TYPE key)
{
	Node* n = (Node*)malloc(sizeof(Node) * 1);
	n->key = key;
	return n;
}

void PrintBST(BST_Tree tree_head)
{
	if ( tree_head )
	{
		PrintBST(tree_head->left_child);
		printf("%d,", tree_head->key);
		PrintBST(tree_head->right_child);
	}
}

//functions to complete this task
BST_Tree CreateBST()
{
	Node* tree_head =  (Node*)malloc(sizeof(Node) * 1);
	tree_head->left_child = NULL;
	tree_head->right_child = NULL;
}

BOOL InsertToBST(BST_Tree tree_head, KEY_TYPE key)
{
	Node* p = tree_head;
	if (key == tree_head->key) 
	{
		return FALSE;
	} 
	if ( key < tree_head->key )
	{
		if ( tree_head->left_child != NULL )
			return InsertToBST(tree_head->left_child, key);
		else
			tree_head->left_child = CreateNode(key);
	}
	if ( key > tree_head->key )
	{
		if (tree_head->right_child != NULL)
			return InsertToBST(tree_head->right_child, key);
		else
			tree_head->right_child = CreateNode(key);
	}
	return TRUE;
}

Node* SearchBST(BST_Tree tree_head, KEY_TYPE key)
{
	if (tree_head == NULL)
		return FALSE;
	if (tree_head->key == key)
	{
		return tree_head;
	}
	if ( tree_head->key > key )
	{
		return SearchBST(tree_head->left_child);
	}
	if( tree_head->key < key )
	{
		return SearchBST(tree_head->right_child);
	}
}

BOOL Delete(BST_Tree tree_head, KEY_TYPE key )
{
	if (tree_head == NULL)
		return FALSE;
	if (tree_head->key == key)
		DeleteNode(tree_head);
	if (tree_head->key < key)
		Delete(tree_head->right_child, key);
	if (tree_head->key > key)
		Delete(tree_head->left_child, key);
}

BOOL DeleteNode(Node* p)
{
	Node* q ;
	if (p->left_child)
	{
		q = p->left_child;
		while( q->right_child )
		{
			q = q->right_child;
		}
		p->key = q->key;
		free(q);
		q = NULL;
	}
	if (p->right_child)
	{
		q = p->right_child;
		while( q->left_child )
		{
			q = q->left_child;
		}
		p->key = q->key;
		free(q);
		q = NULL;
	}
	free(p);
	p = NULL;
}

void InOrder(BST_Tree tree_head)
{
	if ( tree_head )
	{
		PrintBST(tree_head->left_child);
		printf("%d,", tree_head->key);
		PrintBST(tree_head->right_child);
	}
}

const int LEN = 5;
int main()
{
	KEY_TYPE data[LEN] = {3, 1, 4, 2, 5};
	int i=0;
	//create
	BST_Tree tree_head = CreateBST();
	//insert
	for (; i<LEN; i++)
	{
		InsertToBST(tree_head, data[i]);
	}
	//search
	printf("The search result is %d\n", SearchBST(tree_head, 3));

	//delete
	Delete(tree_head, 2)

	//in order traversal
	PrintBST(tree_head);

	return 0;
}
