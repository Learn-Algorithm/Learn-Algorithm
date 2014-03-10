#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAX_NUM 26

typedef struct Trie_Node {
	int count;
	char value;
	struct Trie_Node* child[MAX_NUM];
} Node, *Trie;

// Create a new node
Node* createNewNode(char ch) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node -> value = ch;
	new_node -> count = 0;
	for(int i  = 0 ; i < MAX_NUM ; i++)
		new_node -> child[i] = NULL;
	return new_node;
}

// Initialize a new Trie
void initialization(Trie* root) {
	*root = createNewNode(' ');
}

// Method Function
int charToindex(char ch) {
	return ch - 'a';
}

// Insert a word to a Trie
void insert(const char word[], int len, Trie* root) {
	Node* ptr = *root;
	int i;
	for(i = 0 ; i < len ; i++) {
		int index = charToindex(word[i]);
		if(ptr -> child[index] == NULL) {
			ptr -> child[index] = createNewNode(word[i]);
		}
		ptr = ptr -> child[index];
	}
	ptr -> count += 1;
}

// Search a word from the Trie
int search(const char word[], int len, Trie* root) {
	Node* ptr = *root;
	int i = 0;
	for(i = 0  ; i < len ; i++) {
		int index = charToindex(word[i]);
		if (ptr -> child[index] == NULL)
			break;
		ptr = ptr -> child[index];
	}

	return ptr -> count;
}

// Delete a value from the Trie
void Delete(const char word[], int len, Trie* root) {
	Node* ptr = *root;
	int i = 0;
	for(i = 0 ; i < len ; i++) {
		int index = charToindex(word[i]);
		if (ptr -> child[index] == NULL)
			return;
		ptr = ptr -> child[index];
	}
        if(ptr -> count != 0)
	   ptr -> count -= 1;
}

int main() {

    Trie root;
    initialization(&root);
    insert("b", 1, &root);
    insert("abc", 3, &root);
    insert("abd", 3, &root);
    insert("bcd", 3, &root);
    insert("abcd", 4, &root);
    insert("efg", 3, &root);
    insert("hii", 3, &root);

    int count = search("hii", 3, &root);
    cout << count << endl;
    insert("hii", 3, &root);
    count = search("hii", 3, &root);
    cout << count << endl;
    Delete("hii", 3, &root);
    count = search("hii", 3, &root);
    cout << count << endl;

	return 0;
}
