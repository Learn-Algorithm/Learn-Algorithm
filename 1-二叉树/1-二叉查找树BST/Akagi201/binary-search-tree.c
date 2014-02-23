
/*
 * @file binary-search-tree.c
 *  
 * @author Akagi201
 * @date 2014/02/17
 *  
 * binary search tree C file 
 *
 */

#include "binary-search-tree.h"
#include <stdlib.h>
#include <stdio.h>

struct bstnode * get_bstnode(void){
	struct bstnode *p;
	p = (struct bstnode *)malloc(sizeof(struct bstnode));

	return p; // may be NULL
}

/*
 * @brief input pre-order -> make binary tree
 *  
 * pre-order, space
 *  
 * @param[in] tree: binary tree root node
 * @param[out] null
 * @return null
 * @sa 
 * @note 
 * @warning 
 */
struct bstnode* make_tree(T element){

	/* allocates and initializes node */
	struct bstnode *p;
	p = get_bstnode();
	if (p != NULL){
		p->data = element;
		p->left = NULL;
		p->right = NULL;

		return p;
	}else{
		printf("make_tree failed.\n");
		exit(1);
	}
}

void insert(struct bstnode *p_bstree, T element){
	struct bstnode *s = p_bstree;

	/* traverse tree */
	while (s != NULL){
		/* duplicate: BST cannot have duplicates */
		if (element == s->data){
			printf("skipping element:%d due to duplicate, ", element);
			return;
		}

		/* go to left */
		if (s->data > element){
			if (NULL == s->left){
				/* place node here */
				s->left = make_tree(element);
				return;
			}else{
				/* keep going */
				s = s->left;
			}
		}else{
			/* go to right */
			if (NULL == s->right){
				/* place node here */
				s->right = make_tree(element);
				return;
			}else{
				/* keep going */
				s = s->right;
			}

		}

	}

	return;
}

/* find node iteratively */
struct bstnode *find_iterative(struct bstnode *p_bstree, T element){
	while (p_bstree != NULL){
		if (p_bstree->data == element){
			/* node found */
			return p_bstree;
		}else if (element > p_bstree->data){
			/* go to right */
			p_bstree = p_bstree->right;
		}else if (element < p_bstree->data){
			/* go to left */
			p_bstree = p_bstree->left;
		}
	}

	/* not found. node will be pointing to NULL. */
	return p_bstree;
}

/* find node recursively */
struct bstnode *find_recursive(struct bstnode *p_bstree, T element){
	if ((NULL == p_bstree) || (element == p_bstree->data)){
		/* node NULL means it wasn't found. */
		return p_bstree;
	} else {
		if (element < p_bstree->data){
			/* go to left */
			return find_recursive(p_bstree->left, element);
		}else{
			/* go to right */
			return find_recursive(p_bstree->right, element);
		}
	}
}

void erase(struct bstnode **pp_bstree, T element){
	struct bstnode *p = NULL;
	p = *pp_bstree;
	struct bstnode *q = NULL;
	struct bstnode *f = NULL;
	struct bstnode *rp = NULL;
	struct bstnode *s = NULL;

	/* Search for the node with the element, set p to point to the node and q to its parent, if any. */
	while ((p != NULL) && (element != p->data)){
		q = p;
		if (element > p->data){
			p = p->right;
		}else{
			p = p->left;
		}
	}

	if (NULL == p){
		/* The element does not exists in the tree, leave the tree unchanged */
		printf("element %d is not in the tree", element);
		return;
	}

	if (NULL == p->left){
		rp = p->left;
	} else if (NULL == p->right){
		rp = p->right;
	} else {
		/* Set rp to the inorder successor of p and f to the parent of rp */
		f = p;
		rp = p->right;
		s = rp->left; /* s is left child of rp */
		while (s != NULL){
			f = rp;
			rp = s;
			s = rp->left;
		}

		if (f != p){
			/* at this point, rp is the inorder successor of p */
			f->left = rp->right; /* p is not parent of rp, set it to left(p)*/
			rp->right = p->right;
			/* remove node rp and replace */
		}

		rp->left = p->left; /* set left child of rp, rp takes place of p */
	}

	/* insert node(rp) into position formerly occupied by node(p) */
	if (NULL == q){
		/* node(p) was the root */
		*pp_bstree = rp;
	}else{
		if (p == q->left){
			q->left = rp;
		}else{
			q->right = rp;
		}
	}

	free(p);
	printf("node %d deleted.\n", element);

	return;
}

 
void inorder_recursive(struct bstnode *p_bstree)
{
    if (p_bstree != NULL)
    {
        inorder_recursive(p_bstree->left); /* traverse the left subtree */
        printf ("%d, ", p_bstree->data); /* visit the node */
        inorder_recursive(p_bstree->right); /* traverse the right subtree */
    } 
    return;
} 

int main(void){

	struct bstnode *p_bstree = NULL;

	// TODO: add test cases.

    return 0;
}
