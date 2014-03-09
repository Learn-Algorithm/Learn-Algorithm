#include "stdio.h"
#include "stdlib.h"

typedef struct Trie
{
  int count;
  char value;
  struct Trie** subtries;
}Trie;

Trie* Create(char* word){
    Trie* root = (Trie*)malloc(sizeof(Trie));
    root->value = *word;
    root->subtries = (Trie**)malloc(sizeof(Trie*));
	if (*(word + 1) == NULL){
		root->count = 1;
        *(root->subtries) = NULL;
	}
	else {
		root->count = 0;
		*(root->subtries) = Create(++word);
        *(root->subtries + 1) = NULL;
	}
    return root;
}

Trie* Insert (Trie* root, char* word){
    int i;
    for (i = 0; *(root->subtries + i) != NULL; i++){
        if ((*(root->subtries + i))->value == *word){
			if (*(word + 1) == NULL){
				(*(root->subtries + i))->count++;
			} else {
                *(root->subtries + i) = Insert(*(root->subtries + i), ++word);
			}
            return root;
        }
    }

    *(root->subtries + i + 1) = *(root->subtries + i);
	*(root->subtries + i) = Create(word);
    return root;
}

Trie* Remove (Trie* root, char* word){
    int i, oldCount;
	for (i = 0; *(root->subtries + i) != NULL; i++){
		if ((*(root->subtries + i))->value == *word){
			if (*(word + 1) == NULL){
				if ((*(root->subtries + i))->count > 0){    //do nothing when removing "ab" from {"abort", "about"}
					(*(root->subtries + i))->count--;
				}
            }
			else {
				*(root->subtries + i) = Remove(*(root->subtries + i), ++word);
			}
            if ((*(root->subtries + i))->subtries == NULL){
                    free(*(root->subtries + i));
                    *(root->subtries + i) = NULL;
            }
            return root;
        }
	}
    return root;
}

int Query (Trie* root, char* word){
	int i;
	for (i = 0; *(root->subtries + i) != NULL; i++){
		if ((*(root->subtries + i))->value == *word){
			if (*(++word) != NULL)
				return Query(*(root->subtries + i), word);
			else
				return (*(root->subtries + i))->count;
		}
	}
	return 0;
}


int main(){
    Trie* root = (Trie*)malloc(sizeof(Trie));
    root->value = NULL;
    root->count = 0;
	root->subtries = (Trie**)malloc(sizeof(Trie*));
	*(root->subtries) = NULL;

	root = Insert(root, "abnormal");
	root = Insert(root, "aa");
	root = Insert(root, "absent");
	root = Insert(root, "abnormal");
	root = Insert(root, "grab");
	root = Insert(root, "adsence");

	printf("%d\n", Query(root, "ab"));
	root = Remove(root, "ab");
	printf("%d\n", Query(root, "ab"));
	printf("%d\n", Query(root, "abnormal"));
	root = Remove(root, "abnormal");
	printf("%d\n", Query(root, "abnormal"));

    //Clear(root);
    root = NULL;
    return 0;
}
