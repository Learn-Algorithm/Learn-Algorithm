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
} Node;

//help functions
Node* CreateNode(KEY_TYPE key)
{
	Node* n = (Node*)malloc(sizeof(Node) * 1);
	n->key = key;
	return n;
}

void PrintBST(Node* tree_head)
{
	if ( tree_head )
	{
		PrintBST(tree_head->left_child);
		printf("%d,", tree_head->key);
		PrintBST(tree_head->right_child);
	}
}


//functions to complete this task
Node* CreateBST()
{
	Node* tree_head =  (Node*)malloc(sizeof(Node) * 1);
	tree_head->left_child = NULL;
	tree_head->right_child = NULL;
}

BOOL InsertToBST(Node* tree_head, KEY_TYPE key)
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

int main()
{
	KEY_TYPE data[4] = {3, 1, 4, 2};
	int i=0;
	Node* tree_head = CreateBST();
	for (; i<4; i++)
	{
		InsertToBST(tree_head, data[i]);
	}
	PrintBST(tree_head);
	return 0;
}
