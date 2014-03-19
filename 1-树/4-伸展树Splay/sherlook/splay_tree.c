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
} Node, *Splay_tree;

int GetTreeHeight(Splay_tree tree, int height)
{
	int l_height = 0, r_height = 0;
	if (tree)
	{
		height = height + 1;
		l_height = GetTreeHeight(tree->left_child, height);
		r_height = GetTreeHeight(tree->right_child, height);
		if (l_height >= r_height)
			height = l_height;
		else
			height = r_height;
	}
	return height;
}

Node* Splay(Node* parent, Node* child)
{
	//if ((*parent)->left_child == child)
	//{
	//	(*parent)->left_child = (*child)->right_child;
	//	(*child)->right_child = *parent;
	//	(*child)->left_child = NULL;
	//	return *child;
	//}
	if(parent->right_child == child)
	{
		parent->right_child = child->left_child;
		child->left_child = parent;
		child->right_child = NULL;
		return child;
	}
}

Node* CreateNode(KEY_TYPE key)
{
	Node* n = (Node*)malloc(sizeof(Node) * 1);
	n->key = key;
	n->left_child = NULL;
	n->right_child = NULL;
	return n;
}

Splay_tree merge(Splay_tree L, Splay_tree R, Splay_tree M)
{
	Node* p;
	if(L)
	{
		p = L;
		while( p->right_child)
			p = p->right_child;
		p->right_child = M->left_child;
		M->left_child = L;
		
	}
	if(R)
	{	
		p = R;
		while(p->left_child)
			p = p->left_child;
		p->left_child = M->right_child;
		M->right_child = R;
	}
	return M;
}

void Insert(Splay_tree tree, KEY_TYPE key)
{
	Node* p = tree;
	if (p == NULL)
	{
		return;
	}
	if ( key < p->key )
	{
		if ( p->left_child != NULL )
			return Insert(p->left_child, key);
		else
		{
			p->left_child = CreateNode(key);
			printf("insert node %p %d\n", p->left_child, p->left_child->key);
		}
			
	}
	if ( key > p->key )
	{
		if (p->right_child != NULL)
			return Insert(p->right_child, key);
		else
		{
			p->right_child = CreateNode(key);
			printf("insert node %p %d\n", p->right_child, p->right_child->key);
		}
			
	}
}

Node* FindMostRight(Splay_tree tree)
{
	while(tree->right_child)
		tree = tree->right_child;
	return tree;
}

Node* FindMostLeft(Splay_tree tree)
{
	while (tree->left_child)
		tree = tree->left_child;
	return tree;
}

Node* Search(Splay_tree tree, KEY_TYPE key)
{
	Node* left_tree = NULL; //(Splay_tree)malloc(sizeof(Splay_tree) * 1);
	Node* right_tree = NULL; //(Splay_tree)malloc(sizeof(Splay_tree) * 1);
	Node* left_tree_right_most = left_tree;
	Node* right_tree_left_most = right_tree;
	Node* p = tree;
	Node* m_tree = tree;
	Node* tmp = p;
	Node* q = NULL;
	Node* splay_root = NULL;
	
	while (p)
	{
		m_tree = p;
		if (p->key == key)
		{
			tree = merge(left_tree, right_tree, m_tree);
			return tree;
		}
		else if (p->key < key && p->right_child) 
		{
			if (p->right_child->key == key)
			{
				m_tree = p->right_child;
				if(left_tree == NULL)
				{
					left_tree = p;
				}
				else
				{
					left_tree_right_most = FindMostRight(left_tree);
					p->right_child = NULL;
					left_tree_right_most->right_child = p;
				}
				tree = merge(left_tree, right_tree, m_tree);
				return tree;
			}
			else if (p->right_child->key < key) //zig-zig
			{
				tmp = p->right_child->right_child;
				splay_root = Splay(p, p->right_child);
				if (left_tree == NULL) 
				{
					left_tree = splay_root;
				}
				else
				{
					left_tree_right_most = FindMostRight(left_tree);
					left_tree_right_most->right_child =  splay_root;
				}
				p = tmp;
			}
			else if (p->right_child->key > key) //zig-zag
			{
				tmp = p->right_child;
				q = tmp->left_child;
				p->right_child = NULL;
				if (left_tree == NULL)
				{	
					left_tree = p;
				}
				else
				{
					left_tree_right_most = FindMostRight(left_tree);
					left_tree_right_most->right_child = p;
				}

				tmp->left_child = NULL;
				if(right_tree == NULL)
				{
					right_tree = tmp;
				}
				else
				{
					right_tree_left_most = FindMostLeft(right_tree);
					right_tree_left_most->left_child = tmp;
				}
				p = q;
				
			}
			
		}
		else if (p->key > key)
		{
			if(p->left_child && p->left_child->key > key) //zig-zig
			{
				//right_tree-> Splay(p, p->left_child );
			}
		}
	}
	return NULL;
}

void PrintTree(Splay_tree tree)
{
	if ( tree )
	{
		if (tree->left_child && !tree->right_child)
		{
			printf("node(%d,%p) has left(%d,%p),\n", tree->key, tree, tree->left_child->key, tree->left_child);
		}
		else if (tree->right_child && !tree->left_child)
		{
			printf("node(%d,%p) has right(%d,%p),\n", tree->key, tree, tree->right_child->key, tree->right_child);
		}
		else if (tree->left_child && tree->right_child)
		{
			printf("node(%d,%p) has left(%d,%p),has right(%d,%p),\n", tree->key, tree,tree->left_child->key, tree->left_child, tree->right_child->key, tree->right_child);
		}
		
		PrintTree(tree->left_child);
		PrintTree(tree->right_child);
	}
}

#define LEN 6

int main()
{
	Splay_tree tree = CreateNode(10);
	int data[LEN] = {5, 20, 15, 30, 40 , 50};
	int key, searchKey ;
	int height = 0;
	int i = 0;
	Node* n = NULL;
	//while(scanf("%d", &key) != EOF)
	//{
	//	Insert(tree, key);
	//}
	for (; i<LEN; i++)
		Insert(tree, data[i]);
	printf("the tree is:\n");
	PrintTree(tree);
	searchKey = 15;
	n = Search(tree, searchKey);
	if (n)
	{
		printf("find %d result is node(%p)\n", searchKey, n);
		PrintTree(n);
	}
	return 0;
}