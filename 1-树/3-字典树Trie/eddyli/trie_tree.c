#include <stdio.h>
#include <stdlib.h>

struct Trie
{
  int count;  //count 如果为0，则代表非黄色点，count>0代表是黄色点，同时表示出现次数;
  char value; //字符
  int childcount; //子树长度
  struct Trie ** subtries; //子树
};

typedef struct Trie Trie;

int char2index(char p, Trie* Node) {
	int i = 0;
	for (; i < Node->childcount; i++) {
		if (Node->subtries[i]->value == p)
			return i;
	}
	return -1;
}

Trie *_insert(char p, Trie* Node) {
	int index;
	int count;
	index = char2index(p, Node);
	count = Node->childcount;
	if (index == -1) {
		Node->subtries = (Trie**)realloc(
			Node->subtries,
			(count+1) * sizeof(Trie*)
		);
		Node->subtries[count] = (Trie*)calloc(1, sizeof(Trie));
		Node->subtries[count]->value = p;
		index = Node->childcount;
		Node->childcount += 1;
	}
	return Node->subtries[index];
}

Trie *Insert(char *p, int count, Trie* Node) {
	int i;
	Trie * tnode = Node;
	if (p == NULL || Node == NULL || count <= 0)
		return NULL;
	for(i = 0; i < count; i++) {
		tnode = _insert(p[i], tnode);
	}
	tnode->count += 1;
	return tnode;
}

int Query(char *p, int count, Trie* Node) {
	int i;
	int index = 0;
	Trie * node = Node;
	for (i = 0; i < count; i++) {
		index = char2index(p[i], node);
		if (index == -1)
			return -1;
		else
			node = node->subtries[index];
	}
	return 0;
}

int main() {
	Trie node;
	node.value = ' ';
	node.childcount = 0;
	node.count = 0;
	node.subtries = NULL;

	Insert("hello", 5, &node);
	Insert("hi", 2, &node);
	Insert("how", 2, &node);
	Insert("howmany", 7, &node);
	Query("hi",2,&node);
	Query("how",3,&node);
	Insert("你好", 6, &node);
	Query("你好",6,&node);
}
