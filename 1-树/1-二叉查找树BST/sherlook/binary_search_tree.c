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
	n->left_child = NULL;
	n->right_child = NULL;
	return n;
}


//functions to complete this task
BST_Tree CreateBST()
{
	return CreateNode(0);
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
		{
			tree_head->left_child = CreateNode(key);
			printf("insert node %p %d\n", tree_head->left_child, tree_head->left_child->key);
		}
			
	}
	if ( key > tree_head->key )
	{
		if (tree_head->right_child != NULL)
			return InsertToBST(tree_head->right_child, key);
		else
		{
			tree_head->right_child = CreateNode(key);
			printf("insert node %p %d\n", tree_head->right_child, tree_head->right_child->key);
		}
			
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
		return SearchBST(tree_head->left_child, key);
	}
	if( tree_head->key < key )
	{
		return SearchBST(tree_head->right_child, key);
	}
}

BOOL Delete(BST_Tree tree_head, KEY_TYPE key )
{
	Node* parent = tree_head;
	Node* p = tree_head;
	if (tree_head == NULL)
		return FALSE;
	while(p)
	{
		if (p->key == key)
			return DeleteNode(&parent, &p);
		else if (p->key < key)
		{
			parent = p;
			p = p->right_child;
		}
		else if (p->key > key)
		{
			parent = p;
			p = p->left_child;
		}
	}
	return FALSE;
}

BOOL DeleteNode(Node** parent, Node** toDelete)
{
	Node *leftMax, *rightMin, *p;
	if ((*toDelete)->right_child == NULL && (*toDelete)->left_child) //right child tree is empty,but left's not
	{
		if ( (*parent)->left_child == *toDelete)
		{
			(*parent)->left_child = (*toDelete)->left_child;
		}else if((*parent)->right_child == *toDelete )
		{
			(*parent)->right_child = (*toDelete)->left_child;
		}
		free(*toDelete);
		*toDelete = NULL;
		return TRUE;
	}
	if ( (*toDelete)->left_child == NULL && (*toDelete)->right_child) //left child tree is empty,but right's not
	{
		if ( (*parent)->left_child == *toDelete)
		{
			(*parent)->left_child = (*toDelete)->right_child;
		}else if((*parent)->right_child == *toDelete )
		{
			(*parent)->right_child = (*toDelete)->right_child;
		}
		free(*toDelete);
		*toDelete = NULL;
		return TRUE;
	}
	if ( (*toDelete)->left_child && (*toDelete)->right_child )
	{
		rightMin = (*toDelete)->right_child;
		while(rightMin->left_child)
		{
			rightMin = rightMin->left_child;
		}
		rightMin->left_child = (*toDelete)->left_child;
		if ( (*parent)->left_child == *toDelete)
		{
			(*parent)->left_child = (*toDelete)->right_child;
		}else if((*parent)->right_child == *toDelete )
		{
			(*parent)->right_child = (*toDelete)->right_child;
		}
		free(*toDelete);
		*toDelete = NULL;
		return TRUE;
	}
	return DeleteDeathNode(parent, toDelete);
}

BOOL DeleteDeathNode(Node** parent, Node** toDelete)
{
	printf("%p %d, %p %d\n", *parent, (*parent)->key, *toDelete, (*toDelete)->key);
	if ( (*parent)->left_child == *toDelete )
		(*parent)->left_child = NULL;
	else 
		(*parent)->right_child = NULL;

	printf("delete node %d %p\n", (*toDelete)->key, (*toDelete));
	free(*toDelete);
	*toDelete = NULL;
	return TRUE;
}

void InOrder(BST_Tree tree_head)
{
	if ( tree_head )
	{
		InOrder(tree_head->left_child);
		printf("%p %d,l:%p r:%p\n", tree_head, tree_head->key, tree_head->left_child, tree_head->right_child);
		InOrder(tree_head->right_child);
	}
}

#define LEN 6
int main()
{
	KEY_TYPE data[LEN] = { 1, 4, 0, 2, 5, -1};
	int i=0;
	KEY_TYPE k = 3;
	KEY_TYPE deleteKey = 1;
	//create head key is default to 0
	BST_Tree tree_head = CreateNode(3);
	printf("1.Create Binary Search Tree success!\n");
	//insert
	for (; i<LEN; i++)
	{
		InsertToBST(tree_head, data[i]);
		//printf("2.Insert to tree of %d\n", data[i]);
	}
	

	//search
	printf("Search 3 of the tree.\n");
	printf("The search result is %d\n", SearchBST(tree_head, k)->key);


	printf("Before delete in order traversal the tree:\n");
	InOrder(tree_head);
	printf("\n");
	//delete
	printf("Delete the key of %d.\n", deleteKey);
	Delete(tree_head, deleteKey);

	//in order traversal
	printf("After delete %d in order traversal the tree:\n", deleteKey);
	InOrder(tree_head);
	printf("\n");

	return 0;
}
