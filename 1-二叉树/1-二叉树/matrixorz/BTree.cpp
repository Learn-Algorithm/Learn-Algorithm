#include <stdio.h>
#include <stdlib.h>
typedef struct BiTNode
{
  char data;
  struct BiTNode *lchild,*rchild;
 }BiTNode,*BiTree;
typedef struct QNode{
	BiTree data;
	QNode *next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front,rear;
};

 void CreateBiTree(BiTree &T)
 {
	 char c;
	 scanf("%c",&c);
	 if (c=='#')  //$ indicate the end of the tree
     {
		 T=NULL;
	 }
	 else
	 {
		 T=(BiTNode *)malloc(sizeof(BiTNode));
		 T->data=c;
		 CreateBiTree(T->lchild);
		 CreateBiTree(T->rchild);
	 }
 }

 void Visit(char data)
 {
	 printf("%c",data);
 }

 void PreOrderTraverse(BiTree T)
 {
	 if (T)
	 {
		 printf("enterd");
		 Visit(T->data);
		 PreOrderTraverse(T->lchild);
		 PreOrderTraverse(T->rchild);
	 }
 }

 void InOrderTraverse(BiTree T)
 {
	 if (T)
	 {
		 InOrderTraverse(T->lchild);
		 Visit(T->data);
		 InOrderTraverse(T->rchild);
	 }
 }

 void PostOrderTraverse(BiTree T)
 {
	 if (T)
	 {
		 PostOrderTraverse(T->lchild);
		 PostOrderTraverse(T->rchild);
		 Visit(T->data);
	 }
 }




void InitQueue(LinkQueue &Q)
 {
	 if (!(Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode))))
		 exit(0);
	 Q.front->next=NULL;
 }
int QueueEmpty(LinkQueue Q)
{
	if (Q.front==Q.rear)
		return 1;
	else
		return 0;
}
void EnQueue(LinkQueue &Q,BiTree e)
{
	QueuePtr p;
	if (!(p=(QueuePtr)malloc(sizeof(QNode))))
		exit(0);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}

void DeQueue(LinkQueue &Q,BiTree &e)
{
	QueuePtr p;
	if (Q.front==Q.rear)
		exit(0);
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if (Q.rear==p)
		Q.rear=Q.front;
	free(p);
}
 void LevelOrderTraverse(BiTree T)
 {
	 LinkQueue q;
	 BiTree a;
	 if (T)
	 {
		 InitQueue(q);
		 EnQueue(q,T);
		 while(!QueueEmpty(q))
		 {
			 DeQueue(q,a);
			 Visit(a->data);
			 if (a->lchild!=NULL)
				 EnQueue(q,a->lchild);
			 if (a->rchild!=NULL)
				 EnQueue(q,a->rchild);
		 }
	 }
 }

 int main()
 {
	 BiTree T;
     CreateBiTree(T);
     PreOrderTraverse(T);
     InOrderTraverse(T);
     PostOrderTraverse(T);	
     LevelOrderTraverse(T);
     return 0;

 }

