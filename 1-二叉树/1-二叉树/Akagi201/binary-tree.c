
/*
 * @file binary-tree.c
 *  
 * @author Akagi201 
 * @date 2014/02/16 
 *  
 * binary tree C file 
 *
 */

#include "binary-tree.h"
#include <stdio.h>
#include <stdlib.h>

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
void make_tree(struct btnode **tree){
    char element;
    scanf("%c", &element);

    if ((' ' == element)) {
        *tree = NULL;
    }else{
        if ((*tree = (struct btnode *)malloc(sizeof(struct btnode))) == NULL) {
            printf("make_tree malloc failed.\n");
            exit(1);
        }

        (*tree)->data = element;

        printf("make_tree succeed with element:%c.\n", element);
        make_tree(&((*tree)->left));
        make_tree(&((*tree)->right));
    }

    return;
}

void pre_order(struct btnode *tree){
    if (tree != NULL) {
        printf("visited: %c.\n", tree->data);
        pre_order(tree->left);
        pre_order(tree->right);
    }

    return;
}

void in_order(struct btnode *tree){
    if (tree != NULL) {
        in_order(tree->left);
        printf("visited: %c.\n", tree->data);
        in_order(tree->right);
    }

    return;
}

void post_order(struct btnode *tree){
    if (tree != NULL) {
        post_order(tree->left);
        post_order(tree->right);
        printf("visited: %c.\n", tree->data);
    }

    return;
}

void level_order(struct btnode *tree){

}

int main(void){
    struct btnode *tree;
    make_tree(&tree);
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    level_order(tree);
    return 0;
}
