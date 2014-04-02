#include <iostream>
#include<algorithm>
#include <cstdlib>
#include<stdio.h>
int size;
typedef struct tree_node
{
    tree_node *left;
	tree_node *right;
    int item;
}Tree;
Tree * splay (int i, Tree * t)
{
    Tree N, *l, *r, *y;
    if (t == NULL)
        return t;
    N.left = N.right = NULL;
    l = r = &N;
    for (;;)
    {
        if (i < t->item)
        {
            if (t->left == NULL)
            {
                break;
            }
            if (i < t->left->item)
            {
                y = t->left;
                t->left = y->right;
                y->right = t;
                t = y;
                if (t->left == NULL)
                {
                    break;
                }
            }
            r->left = t;
            r = t;
            t = t->left;
        }     
        else if (i > t->item)
        {    
            if (t->right == NULL)
            {
                break;
            }
            if (i > t->right->item)
            {
                y = t->right;
                t->right = y->left;
                y->left = t;
                t = y;
                if (t->right == NULL)
                {
                    break;
                }
            }
            l->right = t;
            l = t;
            t = t->right;
        }     
        else    
        {
            break;
        }
    }
    l->right = t->left;
    r->left = t->right;
    t->left = N.right;
    t->right = N.left;
    return t;
}
Tree * sedgewickized_splay (int i, Tree * t)
{
    Tree N, *l, *r, *y;
    if (t == NULL)
    {
        return t;
    }
    N.left = N.right = NULL;
    l = r = &N;
    for (;;)
    {
        if (i < t->item)
        {
            if (t->left != NULL && i < t->left->item)
            {
                y = t->left;
                t->left = y->right;
                y->right = t;
                t = y;
            }
            if (t->left == NULL)
            {
                break;
            }
            r->left = t;
            r = t;
            t = t->left;
        }
        else if (i > t->item)
        {
            if (t->right != NULL && i > t->right->item)
            {
                y = t->right;
                t->right = y->left;
                y->left = t;
                t = y;
            }
            if (t->right == NULL)
            {
                break;
            }
            l->right = t;
            l = t;
            t = t->right;
        }
        else
        {
            break;
        }
    }
    l->right=t->left;
    r->left=t->right;
    t->left=N.right;
    t->right=N.left;
    return t;
}
Tree * insert(int i, Tree * t)
{
    Tree* p;
    p = (Tree *) malloc (sizeof (Tree));
    if (p == NULL)
    {
        printf("Ran out of space\n");
        exit(1);
    }
    p->item = i;
    if (t == NULL)
    {
        p->left = p->right = NULL;
        size = 1;
        return p;
    }
    t = splay(i,t);
    if (i < t->item)
    {
        p->left = t->left;
        p->right = t;
        t->left = NULL;
        size ++;
        return p;
    }
    else if (i > t->item)
    {
        p->right = t->right;
        p->left = t;
        t->right = NULL;
        size++;
        return p;
    }
    else
    {
        free(p);
        return t;
    }
}
Tree * del(int i, Tree * t)
{
    Tree * x;
    if (t==NULL)
    {
        return NULL;
    }
    t = splay(i,t);
    if (i == t->item)
    {
        if (t->left == NULL)
        {
            x = t->right;
        }
        else
        {
            x = splay(i, t->left);
            x->right = t->right;
        }
        size--;
        free(t);
        return x;
    }
    return t;
}
int main()
{
	int tr[]={3,4,5,6,7,8,9,0,1,2};
    Tree * root;
    int i;
    root = NULL;
    size = 0;
    for (i = 0; i <10; i++)
    {
        root = insert(tr[i], root);
    }
    printf("%d\n", size);
    for (i = 0; i <10; i++)
    {
        root = del(tr[i], root);
    }
   printf("%d\n", size);
}