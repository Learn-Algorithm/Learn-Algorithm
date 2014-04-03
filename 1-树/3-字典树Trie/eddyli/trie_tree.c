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

int char2index(char p, Trie* node) {
	int i = 0;
	/*
		since we support all char not only a-z
		so we must find the char
		this cause the insert and query
		method's best time complexity
		is o(logn) worst Time complexity is o(n)
		TODO:we should use a map to do char2index
		so the Time complexity should always be o(logn)
	*/
	for (; i < node->childcount; i++) {
		if (node->subtries[i]->value == p)
			return i;
	}
	return -1;
}

Trie *_insert(char p, Trie* node) {
	int index;
	int count;
	index = char2index(p, node);
	count = node->childcount;
	if (index == -1) {
		node->subtries = (Trie**)realloc(
			node->subtries,
			(count+1) * sizeof(Trie*)
		);
		node->subtries[count] = (Trie*)calloc(1, sizeof(Trie));
		node->subtries[count]->value = p;
		index = node->childcount;
		node->childcount += 1;
	}
	return node->subtries[index];
}

Trie *Insert(char *p, int count, Trie* node) {
	int i;
	Trie * tnode = node;
	if (p == NULL || node == NULL || count <= 0)
		return NULL;
	for(i = 0; i < count; i++) {
		tnode = _insert(p[i], tnode);
	}
	tnode->count += 1;
	return tnode;
}

int Query(char *p, int count, Trie* node) {
	int i;
	int index = 0;
	Trie * _node = node;
	for (i = 0; i < count; i++) {
		index = char2index(p[i], _node);
		if (index == -1)
			return -1;
		else
			_node = _node->subtries[index];
	}
	return 0;
}


int Delete(char *p, int count, Trie* node) {
	int i;
	int index = 0;
	Trie * _node = node;
	for (i = 0; i < count; i++) {
		index = char2index(p[i], _node);
		if (index == -1)
			return -1;
		else
			_node = _node->subtries[index];
	}
	if (_node->count == 0)
		return -1;
	_node->count -= 1;
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
	Delete("你好",6,&node);
	printf("%d",Query("你好",6,&node));
}
