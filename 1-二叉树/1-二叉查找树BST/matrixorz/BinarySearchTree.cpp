#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <cstring>
#include <queue>

using namespace std;
typedef int KEY_TYPE;
typedef struct BSTNode{
KEY_TYPE key;
struct BSTNode* lchild;
struct BSTNode* rchild;
}BSTNode,*BSTree;
void insert(BSTree T,int key);
void create(BSTree T,int *num,int len){
    if (len==0)
       return;
    T->key=num[0];
    T->lchild=T->rchild=NULL;
    for(int i=1;i<len;i++)
    {

        insert(T,num[i]);
    }
}
void insert(BSTree T,int key)
{
   //左边小，右边大 
    if(T==NULL)
       return;
    else if (T->key>=key && T->lchild!=NULL)
       insert(T->lchild,key);
    else if(T->key>=key && T->lchild==NULL)
    {
        BSTNode *p=new BSTNode();
        p->key=key;
        p->lchild=p->rchild=NULL;
        T->lchild=p;
    }
    else if (T->key<key && T->rchild!=NULL)
        insert(T->rchild,key);
    else if (T->key<key && T->rchild==NULL)
    {
         BSTNode *p=new BSTNode();
         p->key=key;
         p->lchild=p->rchild=NULL;
         T->rchild=p;
    }
}

bool search(BSTree T,int key,BSTree *p,BSTree *q)
{
   if (T==NULL)
   {
    *q=*p;
    return false;
   }
   if (T->key==key)
   {
    *p=T;
    return true;
   }
   else if (T->key>key)
   {
      *q=T;
    return search(T->lchild,key,p,q);
   }
   else if (T->key<key)
  {
     *q=T;
     return search(T->rchild,key,p,q);
  } 
}

bool del(BSTree T,int key)
{
    BSTNode *pp=new BSTNode(),*qq=new BSTNode();
    BSTNode **p=&pp,**q=&qq;                    //p为待删除节点，q为父节点（前驱节点）
    if (!search(T,key,p,q))
       return false;
    if ((*p)->lchild==NULL &&(*p)->rchild==NULL)// 叶子节点
        delete (*p);
    else if(!((*p)->lchild != NULL &&(*p)->rchild !=NULL))
    {
       if ((*p)->lchild==NULL)
      {
                                               //右边子树不为空，左边子树为空
          if (*p==(*q)->rchild)                //p>q，待删除节点的右边子树->父节点的右边子树
              (*q)->rchild=(*p)->rchild;
          else
              (*q)->lchild=(*p)->rchild;       //p<=q，待删除节点的右边子树->父节点的左边子树
      }
      else 
      {
                                              //左边子树不为空，右边子树为空
          if (*p==(*q)->rchild)
              (*q)->rchild=(*p)->lchild;      //p>q,p的左边子树->父节点的右边子树
          else
              (*q)->lchild=(*p)->lchild;      //p<=q，p的左边子树->父节点的右边子树
      }
      delete (*p);
    }
    else
    {                                         //左右子树都不为空，寻找最接近的小值（大值），替换，删除key值
        BSTNode *m=*p,*n=(*p)->lchild;
        while (n->rchild!=NULL)
        {
              m=n;
              n=n->rchild;
         }
       (*p)->key=n->key;
       if (m!=*p)                             //m有移动，则将n的左子树  ----->   m的右边子树
       {
          m->rchild=n->lchild;
       }
       else                                   //m无移动,则将n的左边子树->   m的左边子树
          m->lchild=n->lchild;
       delete n;
    }
}

void inOrder(BSTree T)
{
   if (T!=NULL)
   {
       inOrder(T->lchild);
       printf("%d ",T->key);
       inOrder(T->rchild);
  }
}

int main()
{
    int len=8,num[8]={4,3,5,1,2,6,7,8};
    BSTree T=new BSTNode();
    BSTree pp=new BSTNode();
    BSTree qq=new BSTNode();
    BSTree *p=&pp,*q=&qq;
    create(T,num,len);
    printf("###%d ###",T->lchild->lchild->rchild->key);
    cout<<"inOrder:";
    inOrder(T);
    cout<<endl<<"insert 9:";
    insert(T,9);
    inOrder(T);
    cout<<endl<<"search 6:";
    search(T,6,p,q);
    cout<<endl<<"delete 6:";
    del(T,6);
    inOrder(T);
    return 0;
}
