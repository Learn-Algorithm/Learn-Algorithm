
/*
 * @file binary-tree.h 
 *  
 * @author Akagi201 
 * @date 2014/02/16 
 *  
 * binary tree header file 
 *
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

/*
 * @struct btnode
 *  
 * @brief definition of binary tree 
 *  
 * using pointer 
 *  
 * @author Akagi201 
 * @date 2014/02/16 
 */
struct btnode{
    char data;
    struct btnode *left;
    struct btnode *right;
};

void make_tree(struct btnode **tree);

void pre_order(struct btnode *tree);

void in_order(struct btnode *tree);

void post_order(struct btnode *tree);

void level_order(struct btnode *tree);

#endif
