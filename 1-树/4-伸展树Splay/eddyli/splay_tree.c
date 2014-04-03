#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"splay_tree.h"


Node* _insert(Node* tree, int item) {
	assert(tree != NULL);

	if (tree->item == item) {
		splay(tree);
		return tree;
	} else if ( tree->item > item) {
		if (tree->lchild == NULL) {
			tree->lchild = (Node*)calloc(1,sizeof(Node));
			tree->lchild->item = item;
			tree->lchild->parent = tree;
			return tree->lchild;
		} else {
			return _insert(tree->lchild, item);
		}
	} else {
		if (tree->rchild == NULL) {
			tree->rchild = (Node*)calloc(1,sizeof(Node));
			tree->rchild->item = item;
			tree->rchild->parent = tree;
			return tree->rchild;
		} else {
			return _insert(tree->rchild, item);
		}
	}	
}

Node* insert(Node* tree, int item) {
	Node * node;
	node = _insert(tree, item);
	splay(node);
	return node;
}


Node* find(int item,Node* tree) {
	Node *n;
	n = tree;
	while(n != NULL && n->item != item) {
		if (item > n->item) {
			n = n->rchild;
		} else {
			n = n->lchild;	
		}
	}
	if (n != NULL && n->item == item)
		splay(n);

	return n;
}

void zig(Node *tree) {
	Node tmp,*x;
	assert(tree->lchild != NULL);

	tmp = *(tree->lchild);
	x = tree->lchild;
	
	tree->lchild = tmp.rchild;
	if (tree->lchild)
		tree->lchild->parent = tree;

	tmp.rchild = tree;
	tmp.parent = tree->parent;
	if (tmp.parent) {
		if (tmp.parent->lchild == tree)
			tmp.parent->lchild = x;
		else
			tmp.parent->rchild = x;
	}
	tree->parent = x;
	*x = tmp;
}

void zag(Node* tree) {
	Node tmp,*x;
	assert(tree->rchild != NULL);

	tmp = *(tree->rchild);
	x = tree->rchild;

	tree->rchild = tmp.lchild;
	if (tree->rchild)
		tree->rchild->parent = tree;

	tmp.lchild = tree;
	tmp.parent = tree->parent;

	if (tmp.parent) {
		if (tmp.parent->lchild == tree)
			tmp.parent->lchild = x;
		else
			tmp.parent->rchild = x;
	}

	tree->parent = x;
	*x = tmp;
}

//rorate x to root
void splay(Node* x) {
	while(x->parent) {
		if (x->parent->parent == NULL) {
			if (x == x->parent->lchild)
				zig(x->parent);
			else 
				zag(x->parent);
		} else if (x->parent->lchild == x && x->parent->parent->lchild == x->parent) {
			zig(x->parent->parent);
			zig(x->parent);
		} else if (x->parent->rchild == x && x->parent->parent->rchild == x->parent) {
			zag(x->parent->parent);
			zag(x->parent);
		} else if (x->parent->lchild == x && x->parent->parent->rchild == x->parent) {
			zig(x->parent);
			zag(x->parent);
		} else if (x->parent->rchild == x && x->parent->parent->lchild == x->parent) {
			zag(x->parent);
			zig(x->parent);
		}
	}
}



