
/*
 * @file binary-search-tree.h 
 *  
 * @author Akagi201 
 * @date 2014/02/17
 *  
 * binary search tree header file 
 *
 */

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

/*
 * @struct bstnode
 *  
 * @brief definition of binary search tree 
 *  
 * using pointer 
 *  
 * @author Akagi201 
 * @date 2014/02/17
 */
typedef int T;
struct bstnode{
    T data;
    struct bstnode *left;
    struct bstnode *right;
};

struct bstnode* make_tree(T element);

void insert(struct bstnode *p_bstree, T element);

struct bstnode *find_iterative(struct bstnode *p_bstree, T element);

struct bstnode *find_recursive(struct bstnode *p_bstree, T element);

void erase(struct bstnode **pp_bstree, T element);

void inorder_recursive(struct bstnode *p_bstree);

#endif
