#include"splay_tree.h"
#include<stdio.h>

int main() {
	Node tree,*root;
	tree.parent = tree.lchild = tree.rchild = NULL;
	tree.item = 5;
	root = insert(&tree, 8);
	root = insert(root, 6);
	root = insert(root, 10);
	root = insert(root, 2);
	

	root = find(5,root);
	return 0;
}