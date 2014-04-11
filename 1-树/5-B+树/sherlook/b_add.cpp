#include <iostream>
using namespace std;

#define BOOL int
#define FALSE 0
#define TRUE 1
#define N 3
#define IsValid(count) (( (count) > N || ( (count) < N/2 + N%2  )) ? 0 : 1 )

struct Node;
typedef int KEY;

typedef struct Node
{
	KEY *keys;
	int keys_count;
	struct Node *children[N+1];
	struct Node *parent;
	BOOL isLeaf;
	struct Node *next;
}Node, *Tree;

Node* CreateNode()
{
	Node* n = new Node;
	n->isLeaf = TRUE;
	n->parent = NULL;
	n->keys = new int[N+1];
	for (int i=0; i<N+1; i++)
	{
		n->children[i] = NULL;
	}
	n->next = NULL;
	n->keys_count = 0;
	printf("create node(%p)\n", n);
	return n;
}

Node* InsertToParent(Node* parent, Node* left, Node* right);
void DeleteKey(Node* p, int deleteKey);

Node* Divide(Node *p)
{
	Node* l;
	Node* r;

	l = CreateNode();
	int divide = p->keys_count / 2;
	int i = 0, k = 0;
	for (; i < divide; ++i,++k)
	{
		l->keys[k] = p->keys[i];
		l->children[k] = p->children[i];
		if (l->children[k])
		{
			l->children[k]->parent = l;
		}
	}
	l->keys_count = k;
	l->isLeaf = p->isLeaf;
	

	k=0;
	for (; i < p->keys_count; ++i,++k)
	{
		p->keys[k] = p->keys[i];
		p->children[k] = p->children[i];
	}
	p->keys_count = k;
	r = p;
	
	
	if (p->parent)
	{
		p = InsertToParent(p->parent, l, r);
	}
	else
	{
		Node* new_root = CreateNode();
		new_root->keys = new KEY[N+1];
		new_root->keys[0] = l->keys[l->keys_count-1];
		new_root->children[0] = l;

		new_root->keys[1] = r->keys[r->keys_count-1];
		new_root->children[1] = r;
		new_root->keys_count = 2;
		l->parent = new_root;
		r->parent = new_root;
		new_root->isLeaf = FALSE;
		return new_root;
	}
	return p;
}

Node* InsertToParent(Node* parent, Node* left, Node* right)
{
	left->parent = parent;
	right->parent = parent;
	int k = left->keys[left->keys_count-1];
	int i = 0;
	for (; i < parent->keys_count; ++i)
	{
		if (parent->keys[i] > k)
		{
			break;
		}
	}
	for (int j = parent->keys_count-1; j >= i; --j)
	{
		parent->keys[j+1] = parent->keys[j];
		parent->children[j+1] = parent->children[j];
	}
	parent->keys[i] = k;
	parent->children[i] = left;
	parent->keys_count++;
	parent->isLeaf = FALSE;
	if (parent->keys_count > N)
	{
		parent = Divide(parent);
	}
	return parent;
}

Node* InsertKey(Node* p, int k)
{
	//if (p == NULL)//divie the root
	//{
	//	p = CreateNode();
	//	p->keys = new KEY[N+1];
	//	p->keys[0] = k;
	//	p->keys_count++;
	//	return p;
	//}
	int i = 0;
	for (; i < p->keys_count; ++i)
	{
		if (p->keys[i] > k)
		{
			break;
		}
	}
	int first_large = i;
	for (int j = p->keys_count-1; j >= first_large; --j)
	{
		p->keys[j+1] = p->keys[j];
	}
	p->keys[first_large] = k;
	p->keys_count++;
	
	Node* new_root = NULL;
	if (p->keys_count > N)
	{
		//divoice
		new_root = Divide(p);
	}
	else
	{
		new_root = p;
		while (new_root->parent)
		{
			new_root = new_root->parent;
		}
	}
	return new_root;
}

Node* Insert(Tree root, int k)
{
	if (!root) return NULL;
	Node *p = root;
	KEY *pKey = NULL;
	int i = 0;
	Node* new_root = NULL;
	while(p)
	{
		if (p->isLeaf) 
			break;
		pKey = p->keys;
		for (i = 0; i < p->keys_count; ++i)
		{
			if (k <= p->keys[i])
			{
				break;
			}
		}
		if (i == p->keys_count)
		{
			i--;
			p->keys[i] = k;
		}
		p = p->children[i];
	}
	new_root = InsertKey(p, k);
	if (new_root != root)
	{
		while(new_root->parent)
			new_root = new_root->parent;
	}
	return new_root;
}

Node* BorrowNode(Node* p, Node* left_brother, Node* right_brother)
{
	int i = 0;
	if (p->parent)
	{
		if ( left_brother && IsValid(left_brother->keys_count-1) )
		{
			p->keys[1] = p->keys[0];
			p->keys[0] = left_brother->keys[left_brother->keys_count-1];
			p->keys_count++;
			left_brother->keys_count--;
			for (i = 0; i < p->parent->keys_count; ++i)
			{
				if (p->parent->children[i] == left_brother)
				{
					p->parent->keys[i] = left_brother->keys[left_brother->keys_count-1];
				}
				if (p->parent->children[i] == p)
				{
					p->parent->keys[i] = p->keys[p->keys_count-1];
				}
			}
			return p;
		}
		else if (right_brother && IsValid(right_brother->keys_count-1))
		{
			p->keys[1] = right_brother->keys[0];
			p->keys_count++;
			for (i = 0; i < right_brother->keys_count-1; ++i)
			{
				right_brother->keys[i] = right_brother->keys[i+1];
			}
			right_brother->keys_count--;
			for (i = 0; i < p->parent->keys_count; ++i)
			{
				if (p->parent->children[i] == right_brother)
				{
					p->parent->keys[i] = right_brother->keys[right_brother->keys_count-1];
				}
				if (p->parent->children[i] == p)
				{
					p->parent->keys[i] = p->keys[p->keys_count-1];
				}
			}
			return p;
		}
		else
			return NULL;
	}
	return p;
}

void AdjustParentKey(Node *p)
{
	if (!p) return;
	int i = 0;
	while(p->parent)
	{
		for ( i = 0; i < p->parent->keys_count; ++i)
		{
			if (p->parent->children[i] == p)
			{
				p->parent->keys[i] = p->keys[p->keys_count-1];
				break;
			}
		}
		if (i == p->keys_count-1)
		{
			p = p->parent;
		}
		else
			break;
	}
}


void MergeNode(Node *p, Node *left_brother, Node *right_brother)
{
	int i=0;
	int toBeMerged;
	if (left_brother)
	{
		left_brother->keys[left_brother->keys_count] = p->keys[p->keys_count-1];
		left_brother->keys_count++;
		for ( i=0; i<p->parent->keys_count; ++i)
		{
			if (p->parent->children[i] == p)
				toBeMerged = i;
			if (p->parent->children[i] == left_brother)
				p->parent->keys[i] = left_brother->keys[left_brother->keys_count-1];

		}
		DeleteKey(p->parent, p->parent->keys[toBeMerged]);
	}
	else if (right_brother)
	{
		for ( i=right_brother->keys_count-1; i >= 0; --i )
		{
			right_brother->keys[i+1] = right_brother->keys[i];
		}
		right_brother->keys[0] = p->keys[p->keys_count-1];
		right_brother->keys_count++;
		for ( i=0; i<p->parent->keys_count; ++i)
		{
			if (p->parent->children[i] == p)
				toBeMerged = i;
			if (p->parent->children[i] = right_brother)
				p->parent->keys[i] = right_brother->keys[right_brother->keys_count-1];
		}
		DeleteKey(p->parent, p->parent->keys[i]);
	}
}

void DeleteKey(Node* p, int deleteKey)
{
	int i = 0;
	for (; i < p->keys_count; ++i)
	{
		if (p->keys[i] == deleteKey)
		{
			break;
		}
	}
	for (int j = i; j < p->keys_count; ++j)
	{
		p->keys[j] = p->keys[j+1];
	}
	p->keys_count--;

	if ( IsValid(p->keys_count) == 0 )
	{
		Node *left_brother = NULL;
		Node *right_brother = NULL;
		int i = 0;
		if (p->parent)
		{
			for (i = 0; i < p->parent->keys_count; ++i)
			{
				if (p->parent->children[i] == p)
					break;
			}
			if (i > 0)
			{
				left_brother = p->parent->children[i-1];
			}
			if (i < p->parent->keys_count-1)
			{
				right_brother = p->parent->children[i+1];
			}
		//尝试借节点
			if (BorrowNode(p, left_brother, right_brother) == NULL)
			{
				//借节点失败，向上合并
				MergeNode(p, left_brother, right_brother);
				delete p;
				p = NULL;
				return;
			}
		}
	}
	else
	{
		AdjustParentKey(p);
	}
}

Node* Delete(Tree root, int k)
{
	if (!root) return NULL;
	Node *p = root;
	KEY *pKey = NULL;
	int i = 0;
	Node* new_root = NULL;
	while(p)
	{
		if (p->isLeaf) 
			break;
		pKey = p->keys;
		for (i = 0; i < p->keys_count; ++i)
		{
			if (k <= p->keys[i])
			{
				break;
			}
		}
		if (i == p->keys_count)
		{
			i--;
			p->keys[i] = k;
		}
		p = p->children[i];
	}
	DeleteKey(p, k);
	//if (new_root != root)
	//{
	//	while(new_root->parent)
	//		new_root = new_root->parent;
	//}
	return root;
}


void PrintBTree(Tree root)
{
	if (root)
	{
		int i=0;
		printf("node(%p) has %d keys.parent is %p. ", root, root->keys_count, root->parent);
		for (; i<root->keys_count; ++i)
		{
			printf("%d %p,", root->keys[i], root->children[i]);
		}
		printf("\n");
		for (i = 0; i<root->keys_count; ++i)
		{
			PrintBTree(root->children[i]);
		}
	}
}

int main()
{
	//int data[] = {59,97,15,44,72};
	//int data[] = {51, 59, 63, 72, 15, 44, 97, 10, 21, 37, 85, 91};
	int data[] = {15, 59, 91, 97, 10, 51, 72, 63, 21, 44, 37, 85};
	Tree root = CreateNode();

	int i=0;
	int data_count = sizeof(data) / sizeof(data[0]);
	for (; i < data_count; ++i)
	{
		root = Insert(root, data[i]);
		//printf("after insert %d:\n", data[i]);
		//PrintBTree(root);
	}

	printf("The tree is:\n");
	PrintBTree(root);
	
	int deleteKey = 0;

	deleteKey= 51;
	printf("after delete %d:\n", deleteKey);
	Delete(root, deleteKey);
	PrintBTree(root);

	deleteKey = 59;
	Delete(root, deleteKey);
	printf("after delete %d:\n", deleteKey);
	PrintBTree(root);
	return 0;
}