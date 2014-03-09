//trie tree by sherlook
//allow words that made from [a-z]
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MAX_LETTER_NUM 26
#define MAX_WORD_LEN 100

typedef struct Node
{
	int count;
	char value;
	struct Node* child[MAX_LETTER_NUM];
} Node, *Trie;

#define CHECK_KEY(key) if ( (key) < 0 || (key) > MAX_LETTER_NUM ) { return; }

Trie CreateTrie()
{
	Trie trie = (Trie)malloc(sizeof(Node) * 1);
	return trie;
}

Node* InsertWord(Trie trie, char* word)
{
	char* p = word;
	Node* t = trie;
	int child_key = 0;

	while(*p != '\0')
	{
		child_key = *p - 'a';
		CHECK_KEY(child_key);
		if ( t->child[child_key] == NULL)
		{
			t->child[child_key] = CreateTrie();
		}
		t = t->child[child_key];
		p++;
	}
	t->count++;
	return t;
}

BOOL Delete(Trie trie, char* word)
{
	char* p = word;
	Node* t = trie;
	Node* parent = trie;
	int child_key = 0;
	int i = 0;
	BOOL isLeaf = TRUE;

	while(*p != '\0')
	{
		child_key = *p - 'a';
		CHECK_KEY(child_key);
		if ( t->child[child_key] == NULL)
		{
			return FALSE;
		}
		parent = t;
		t = t->child[child_key];
		p++;
	}
	t->count--;
	for (; i < MAX_LETTER_NUM; ++i)
	{
		if (t->child[i])
		{
			isLeaf = FALSE; 
		}
	}
	if (isLeaf && t->count <= 0)
	{
		return DeleteNode(&parent, &t);
	}
	return FALSE;
}

BOOL DeleteNode(Node** parent, Node**t)
{
	int i=0;
	for (; i < MAX_LETTER_NUM; ++i)
	{
		if ((*parent)->child[i] == *t)
		{
			(*parent)->child[i] = NULL;
			free(*t);
			*t = NULL;
			return TRUE;
		} 
	}
}

int Query(Trie trie, char* word)
{
	char* p = word;
	Node* t = trie;
	Node* parent = trie;
	int child_key = 0;
	int i = 0;

	while(*p != '\0')
	{
		child_key = *p - 'a';
		CHECK_KEY(child_key);
		if ( t->child[child_key] == NULL)
		{
			return 0;
		}
		parent = t;
		t = t->child[child_key];
		p++;
	}
	return t->count;
}

void TraversalTrieTree(Trie trie)
{
	Node* p = trie;
	int i = 0;
	printf("node %p count %d has child:\n", p, p->count);
	for (; i < MAX_LETTER_NUM; ++i)
	{
		if(p->child[i])
		{
			printf("%c %p,", i+'a', p->child[i]);
		}
	}
	printf("\n");

	for (i = 0; i < MAX_LETTER_NUM; ++i)
	{
		if(p->child[i])
		{
			TraversalTrieTree(p->child[i]);
		}
	}
}



int main()
{
	char word[MAX_WORD_LEN];
	Trie trie_tree = CreateTrie();
	FILE* f_delete, *f_input, *f_query;

	char input_file[32] = "test_input";
	char query_file[32] = "test_query";
	char delete_file[32] = "test_delete";
	int nWordCount = 0;

	//test insert
	f_input = fopen(input_file, "r");
	if (!f_input) 
	{
		printf("%s open failed.", input_file);
		return;
	}
	while(fscanf(f_input, "%s", word) != EOF)
	{
		nWordCount++;
		printf("read a word %s\n", word);
		InsertWord(trie_tree, word);
	}
	printf("read word count:%d\n", nWordCount);
	//test query
	f_query = fopen(query_file, "r");
	if (!f_query)
	{
		printf("%s open failed", query_file);
	}
	else
	{
		while(fscanf(f_query, "%s", word) != EOF)
		{	
			printf("query word %s and result is %d\n", word, Query(trie_tree, word));
		}
	}
	
	//test delete
	f_delete = fopen(delete_file, "r");
	if (!f_delete)
	{
		printf("%s open failed", delete_file);
	}
	else
	{
		printf("\nbefore delete the trie tree is:\n");
		//TraversalTrieTree(trie_tree);
		while(fscanf(f_delete, "%s", word) != EOF)
		{
			printf("delete word %s\n", word);
			Delete(trie_tree, word);
		}
		printf("\nafter delete the trie tree is:\n");
		printf("query word an and result is %d\n", Query(trie_tree, "an"));
		printf("query word he and result is %d\n", Query(trie_tree, "he"));
		//TraversalTrieTree(trie_tree);
	}
    return 0; 
}