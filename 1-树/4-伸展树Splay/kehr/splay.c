/*************************************************************************
 * @File Name:    splay.c
 * @Author:       kehr
 * @Mail:         kehr.china@gmail.com
 * @Created Time: Tue 11 Mar 2014 04:04:26 PM CST
 * @Copyright:    GPL 2.0 applies
 * @Description:  第「一」期，第「四」题： splay tree
 *************************************************************************/
// zig 右转， zag 左转

#include <stdio.h>
#include <stdlib.h>
typedef int VALUE_TYPE;

typedef struct splay_node
{
    VALUE_TYPE value;
    struct splay_node* lchild;
    struct splay_node* rchild;
    struct splay_node* parent;

}splay_node,*splay_tree;



splay_tree zig (splay_tree node)        // 右转
{
    node->parent->lchild = node->rchild;
    node->rchild = node->parent;

    if (node->parent->parent == NULL)
    {
        node->parent = node->parent->parent;
        node->rchild->parent = node;
    }
    else
    {

        node->parent->parent->lchild = node;
        node->parent = node->parent->parent;
        node->rchild->parent = node;
    }
    return node;
}


splay_tree zag (splay_tree node)       // 左转
{
    node->parent->rchild = node->lchild;
    node->lchild = node->parent;

    if (node->parent->parent == NULL)
    {
        node->parent = node->parent->parent;
        node->lchild->parent = node;
    }
    else
    {

        node->parent->parent->rchild = node;
        node->parent = node->parent->parent;
        node->lchild->parent = node;
    }
    return node;
}

splay_tree splay (splay_tree node)
{
    while (node->parent != NULL)
    {
        if (node->parent->parent != NULL)
        {
            if (node->parent->parent->lchild == node->parent) // left
            {
                if (node->parent->lchild == node)  // left-left
                {
                   node->parent = zig(node->parent);
                   node = zig(node);
                }
                else                               // left-right
                {
                    node = zag(node);
                    node = zig(node);
                }
            }
            else                                   // right
            {
                if (node->parent->rchild == node)  // right-right
                {
                    node->parent = zag(node->parent);
                    node = zag(node);
                }
                else                               // right-left
                {
                    node = zig(node);
                    node = zag(node);
                }

            }
        }
        else
        {
            if (node->parent->lchild = node)  // left
            {
                node = zig(node);
            }
            else                               // right
            {
                node = zag(node);
            }
        }

    }

    return node;
}

splay_tree init (VALUE_TYPE value)
{
    splay_tree node;
    if (NULL == ( node = (splay_tree)malloc(sizeof(splay_node))))
    {
        fprintf(stderr,"创建节点失败！");
        exit(1);
    }

    node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;
    node->value = value;

    return node;
}
splay_tree insert (splay_tree root, VALUE_TYPE value)
{
    splay_tree node = init (value);

    if (NULL == root)
    {
        root = node;
    }
    else if (value < root->value)
    {
        if (root->lchild == NULL)
        {
            root->lchild = node;
            node->parent = root;
        }
        else
        {
           root->lchild = insert (root->lchild, value);
        }

    }
    else if (value > root->value)
    {
        if (root->rchild == NULL)
        {
            root->rchild = node;
            node->parent = root;
        }
        else
        {
           root->rchild =  insert (root->rchild, value);
        }
    }

    return root;
}
splay_tree create (splay_tree root)
{
    VALUE_TYPE value;

    printf("input your node value(end with EOF):");
    while (EOF != scanf("%d",&value))
    {
       root =  insert(root, value);
    }
    return root;
}

splay_tree search (splay_tree root, VALUE_TYPE value)
{
    if (NULL == root)
    {
        return NULL;
    }
    else
    {
        if (value < root->value)
        {
            search(root->lchild, value);
        }
        else if (value > root->value)
        {
            search (root->rchild, value);
        }
        else
        {
            printf("find it !\n");
            root = splay (root);
            return root;
        }
    }

}
splay_tree delete_node(splay_tree root, VALUE_TYPE value)
{
    if (root != NULL)
    {
        //find the node to be deleted bring it to the root.
        root = search(root,value);
        splay_tree ltree = root->lchild;
        splay_tree rtree = root->rchild;
        splay_tree sroot;
        free(root); // delete the node;

        if (ltree != NULL)
        {
            splay_tree temp;
            for ( temp = ltree->rchild; temp->rchild != NULL; temp = temp->rchild);
            ltree = splay(temp);
            ltree->rchild = rtree;
            sroot = ltree;

        }
        else
        {
            sroot = rtree;
        }

        return sroot;

    }
}
void inorder (splay_tree root)
{
    if (NULL != root)
    {
        inorder (root->lchild);
        if (root->parent!=NULL)
            printf ("parent:%d  node:%d\n",root->parent->value,root->value);
        else
            printf ("parent:root  node:%d\n",root->value);
        inorder (root->rchild);
    }
}

int main()
{
    splay_tree tree = NULL;
    //tree =  create(tree);
    tree =  insert(tree, 4);
    tree =  insert(tree, 2);
    tree =  insert(tree, 6);
    tree =  insert(tree, 1);
    tree =  insert(tree, 3);
    tree =  insert(tree, 5);
    tree =  insert(tree, 7);


    inorder(tree);
    printf("\n");
    printf ("root:%d\n",tree->value);

    tree = search(tree,1);
    printf ("root:%d\n",tree->value);

    inorder(tree);
    printf("\n");

    return 0;
}
