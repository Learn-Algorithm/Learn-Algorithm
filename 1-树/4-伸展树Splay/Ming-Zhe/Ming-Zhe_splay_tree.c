//
//  main.c
//  SplayTree
//
//  Created by Ming-Zhe on 14-3-17.
//  Copyright (c) 2014年 Ming-Zhe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* pre;
    struct node* lchild;
    struct node* rchild;
    int value;
}node,*Tree;

Tree zig(Tree tree);
Tree zag(Tree tree);
Tree to_right_zigzig(Tree tree);
Tree to_left_zigzig(Tree tree);
Tree to_right_double_zigzag(Tree tree);
Tree to_left_double_zigzag(Tree tree);

Tree find_item(Tree tree, int key);
Tree move_to_top(Tree tree, int key);

Tree zig(Tree tree)
{
    Tree newRoot, parent;
    parent  = tree->pre;
    newRoot = tree->lchild;
    
    if (newRoot->rchild != NULL){
        newRoot->rchild->pre = tree;
        tree->lchild = newRoot->rchild;
    }
    
    newRoot->rchild = tree;
    newRoot->pre = parent;
    if (parent != NULL) {
        if (parent->lchild == tree) {
            parent->lchild = newRoot;
        }
        else {
            parent->rchild = newRoot;
        }
    }
    tree->pre = newRoot;
    return newRoot;
}
Tree zag(Tree tree)
{
    Tree newRoot, parent;
    parent  = tree->pre;
    newRoot = tree->rchild;

    if (newRoot->lchild != NULL){
        newRoot->lchild->pre = tree;
        tree->rchild = newRoot->lchild;
    }
    
    newRoot->lchild = tree;
    newRoot->pre = parent;
    if (parent != NULL) {
        if (parent->lchild == tree) {
            parent->lchild = newRoot;
        }
        else {
            parent->rchild = newRoot;
        }
    }
    tree->pre = newRoot;
    return newRoot;
}
Tree to_right_zigzig(Tree tree)
{
    tree->pre = zig(tree->pre->pre);
    return zig(tree->pre);
}
Tree to_left_zigzig(Tree tree)
{
    tree->pre = zag(tree->pre->pre);
    return zag(tree->pre);
}
Tree to_right_double_zigzag(Tree tree)
{
    tree = zag(tree->pre);
    return zig(tree->pre);
}
Tree to_left_double_zigzag(Tree tree)
{
    tree = zig(tree->pre);
    return zag(tree->pre);
}

Tree find_item(Tree tree, int key)
{
    if (tree == NULL) {
        return NULL;
    }
    if (tree->value == key) {
        return tree;
    }else if (key > tree->value){
        return find_item(tree->rchild, key);
    }else{
        return find_item(tree->lchild, key);
    }
}

Tree move_to_top(Tree tree , int key)
{
    Tree toMove;
    toMove = find_item(tree, key);
    if (toMove == NULL) {
        printf("not exist!\n");
        return toMove;
    }else if (toMove->pre == NULL){
        printf("already on the top\n");
        return toMove;
    }
    while (toMove->pre != NULL){
        if (toMove->pre->pre == NULL) {
            if (toMove == toMove->pre->lchild) {
                toMove = zig(toMove->pre);
            }else{
                toMove = zag(toMove->pre);
            }
        }else{
            if (toMove->pre == toMove->pre->pre->lchild) {
                if (toMove == toMove->pre->lchild) {
                    toMove = to_right_zigzig(toMove);
                }else{
                    toMove = to_right_double_zigzag(toMove);
                }
            }else{
                if (toMove == toMove->pre->lchild) {
                    toMove = to_left_double_zigzag(toMove);
                }else{
                    toMove = to_left_zigzig(toMove);
                }
            }
        }
    }
    return toMove;
}

void insert_node_to_nonempty_tree(Tree tree, node* np)
{
    /* insert the node */
    if(np->value < tree->value) {
        if (tree->lchild == NULL) {
            /* then tr->lchild is the proper place */
            tree->lchild = np;
            np->pre = tree;
            return;
        }
        else {
            insert_node_to_nonempty_tree(tree->lchild, np);
        }
    }
    else if(np->value > tree->value) {
        if (tree->rchild == NULL) {
            tree->rchild = np;
            np->pre = tree;
            return;
        }
        else {
            insert_node_to_nonempty_tree(tree->rchild, np);
        }
    }
}

Tree insert_value(Tree tree, int key)
{
    node* np;
    /* prepare the node */
    np = (Tree) malloc(sizeof(node));
    np->value = key;
    np->pre  = NULL;
    np->lchild  = NULL;
    np->rchild  = NULL;
    
    if (tree == NULL) tree = np;
    else {
        insert_node_to_nonempty_tree(tree, np);
    }
    return tree;
}

void InOrder(node *root) {
    //printf("test\n");
    if(root == NULL) {
        return; }
    InOrder(root->lchild);
    printf("%d\t",root->value);
    InOrder(root->rchild);
}


int main(int argc, const char * argv[])
{

    // insert code here...
    Tree tree;
    
    tree = insert_value(tree, 10);
    tree = insert_value(tree, 8);
    tree = insert_value(tree, 9);
    tree = insert_value(tree, 7);
    tree = insert_value(tree, 6);
    tree = insert_value(tree, 12);
    tree = insert_value(tree, 13);
    tree = insert_value(tree, 11);
    
//    printf("%d\n",tree->lchild->value);
//    printf("%d\n",tree->lchild->lchild->value);
//    printf("%d\n",tree->lchild->lchild->lchild->value);
//    printf("%d\n",tree->lchild->rchild->value);
    
//    test = find_item(tree, 7);
////    printf("%d\n",test->value);
////    printf("%d\n",test->lchild->value);
////    printf("%d\n",test->rchild->value);
//    
//    test = to_right_zigzig(test);
//    printf("%d\n",test->value);
//    printf("%d\n",test->lchild->value);
//    printf("%d\n",test->rchild->value);
//    printf("%d\n",test->rchild->rchild->lchild->value);
    
    tree = move_to_top(tree, 7);
    printf("%d\n",tree->lchild->value);
    printf("%d\n",tree->rchild->rchild->lchild->value);
    printf("%d\n",tree->rchild->rchild->rchild->lchild->value);
    //printf("%d\n",tree->rchild->rchild->value);

    return 0;
}


















