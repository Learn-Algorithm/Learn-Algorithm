#include <iostream>
#include<algorithm>
#include <cstdlib>
#include<stdio.h>
using namespace std;
typedef struct trie{
	int count;
	char value;
	struct trie *subtires[26];
}node,*Tnode;
void Insert(Tnode root,char *str,int len)
{
	trie *p=root,*q;
	for(int i=0;i<len;i++)
	{
		int id;
		if(str[i]>64&&str[i]<90)
			id=str[i]-'A';
		else
			id=str[i]-'a';
		if(p->subtires[id]==NULL)
		{
			q=new trie();
			q->count=0;
			q->value=str[i];
			for(int j=0;j<26;j++)
				q->subtires[j]=NULL;
			p->subtires[id]=q;
			p=q;
			//cout<<p->value<<endl;
		}
		else
			p=p->subtires[id];
	}
	p->count++;
	//cout<<p->count<<endl;
}
void Remove(Tnode root,char *str,int len)
{
	int b=0,i;
	trie *p=root,*q,*a=root;
	for(i=0;i<len-1;i++)
	{
		int id;
		if(str[i]>64&&str[i]<90)
			id=str[i]-'A';
		else
			id=str[i]-'a';
		if(p->subtires[id]==NULL)
		{
			cout<<"this word isn't in tire\n";
			break;
		}
		else{
			if(i==len-1)
			{
				if(p->count>1)
					p->count--;
				else{
					for(int j=b;j<len;j++)
					{
						int id2;
						trie *qm;
						if(str[j]>64&&str[j]<90)
							id2=str[i]-'A';
						else
							id2=str[i]-'a';
						if(j==b)
							a=a->subtires[id2];
						else{
							qm=a->subtires[id2];
							delete[]a;
							a=qm;
						}
					}
				}
			}
			int num=0;
			for(int j=0;j<26;j++)
				if(p->subtires[j]!=NULL)
					num++;
			if(num>1||(p->count>0&&p->count>-1))
			{
				a=p;
				b=i;
			}
			p=p->subtires[id];
		}
	}
}
int Query(Tnode root,char *str,int len)
{
	trie *p=root;
	for(int i=0;i<len;i++)
	{
		int id;
		if(str[i]>64&&str[i]<90)
			id=str[i]-'A';
		else
			id=str[i]-'a';
		if(p->subtires[id]==NULL)
			return 0;
		else{
			p=p->subtires[id];
			if(i==len-1)
			{
				cout<<p->value<<endl;
				cout<<p->count<<endl;
				return (p->count);
			}
		}
	}
}
int main()
{
	char s[30];
	int i;
	for(i=0;i<30;i++)
	{
		char c=getchar();
		if(c=='\n')
			break;
		s[i]=c;
	}
	Tnode root=NULL;
	root=new node();
	root->count=-1;
	for(int j=0;j<26;j++)
		root->subtires[j]=NULL;
	Insert(root,s,i);
	Query(root,s,i);
	Remove(root,s,i);
	return 0;
}