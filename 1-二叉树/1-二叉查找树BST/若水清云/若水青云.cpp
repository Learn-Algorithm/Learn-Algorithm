#include <iostream>
#include<algorithm>
#include <cstdlib>
#include<math.h>
#include<stdio.h>
#include<cstring>
#include<queue>
using namespace std;
typedef struct Node{
    int key;
    struct Node* lchild;
    struct Node* rchild;
}Node;
void insert(Node *T,int key);
void creat(Node *T,int *num,int len)
{
	if(len==0)
		return;
	T->key=num[0];
	T->lchild=T->rchild=NULL;
	for(int i=1;i<len;i++)
		insert(T,num[i]);
}
void insert(Node *T,int key)
{
	if(T==NULL)
		return;
	else if(T->key>=key&&T->lchild!=NULL)
		insert(T->lchild,key);
	else if(T->key>=key&&T->lchild==NULL)
	{
		Node *p=new Node();
		p->key=key;
		p->lchild=p->rchild=NULL;
		T->lchild=p;
	}
	else if(T->key<key&&T->rchild!=NULL)
		insert(T->rchild,key);
	else if(T->key<key&&T->rchild==NULL)
	{
		Node *p=new Node();
		p->key=key;
		p->lchild=p->rchild=NULL;
		T->rchild=p;
	}
}
bool search(Node *T,int key,Node **p,Node **q)
{
	if(T==NULL)
	{
		*q=*p;
		return false;
	}
	if(T->key==key)
	{
		*p=T;
		return true;
	}
	else if(T->key>key)
	{
		*q=T;
		return search(T->lchild,key,p,q);
	}
	else if(T->key<key)
	{
		*q=T;
		return search(T->rchild,key,p,q);
	}
}
bool del(Node *T,int key)
{
	Node *pp=new Node(),*qq=new Node();
	Node **p=&pp,**q=&qq;
	if(!search(T,key,p,q))
		return false;
	if((*p)->lchild==NULL&&(*p)->rchild==NULL)
		delete (*p);
	else if(!((*p)->lchild!=NULL&&(*p)->rchild!=NULL))
	{
		if((*p)->lchild==NULL)
		{
			if(*p==(*q)->rchild)
				(*q)->rchild=(*p)->rchild;
			else
				(*q)->lchild=(*p)->rchild;
		}
		else{
			if(*p==(*q)->rchild)
				(*q)->rchild=(*p)->lchild;
			else
				(*q)->lchild=(*p)->lchild;
		}
		delete (*p);
	}
	else{
		Node *m=*p,*n=(*p)->lchild;
		while(n->rchild!=NULL)
		{
			m=n;
			n=n->rchild;
		}
		(*p)->key=n->key;
		if(m!=*p)
			m->lchild=n->lchild;
		else
			m->lchild=n->lchild;
		delete n;
	}
}
void inOrder(Node *T)
{
	if(T!=NULL)
	{
		inOrder(T->lchild);
		printf("%d ",T->key);
		inOrder(T->rchild);
	}
}
int main()
{
	int len=8,num[8]={4,3,5,1,2,6,7,8};
	Node *T=new Node(),*pp=new Node(),*qq=new Node();
	Node **p=&pp,**q=&qq;
	creat(T,num,len);
	cout<<"inOrder:";
	inOrder(T);
	cout<<endl<<"insert 9:";
	insert(T,9);
	inOrder(T);
	cout<<endl<<"search 6:";
	search(T,6,p,q);
	cout<<(*p)->key;
	cout<<endl<<"delete 6:";
	del(T,6);
	inOrder(T);
	return 0;
}
