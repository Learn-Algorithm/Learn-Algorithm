#include "stdio.h"
#include "stdlib.h"

typedef struct Trie
{
  int count;
  char value;
  struct Trie** subtries;
}Trie;

Trie* Insert (Trie* root, char* word){
	if (*word != NULL){
		int i;
		for (i = 0; *(root->subtries + i) != NULL; i++){
			if ((*(root->subtries + i))->value == *word){
				(*(root->subtries + i))->count++;
				*(root->subtries + i) = Insert(*(root->subtries + i), ++word);
				return root;
			}
		}

		*(root->subtries + i + 1) = *(root->subtries + i);
		Trie* subtrie = malloc(sizeof(Trie));
		subtrie->value = *word;
		subtrie->count = 1;
		subtrie->subtries = (Trie**)malloc(sizeof(Trie*));
		*(subtrie->subtries) = NULL;
		subtrie = Insert(subtrie, ++word);
		*(root->subtries + i) = subtrie;
	}
    return root;
}

int SubCountsSum (Trie* root){
    int i, sum = 0;
	for (i = 0; *(root->subtries + i) != NULL; i++){
        sum += (*(root->subtries + i))->count;
    }
    return sum;
}

Trie* Remove (Trie* root, char* word){
    int i, oldCount;
	for (i = 0; *(root->subtries + i) != NULL; i++){
		if ((*(root->subtries + i))->value == *word){
			if (*(++word) != NULL){
                oldCount = (*(root->subtries + i))->count;
                *(root->subtries + i) =  Remove(*(root->subtries + i), word);
                if (oldCount > (*(root->subtries + i))->count){
                    root->count--;
                }
            } else if ((*(root->subtries + i))->count > SubCountsSum(*(root->subtries + i))){		
                (*(root->subtries + i))->count--;    //nothing happens when Remove "ab" in {"abnormal","abort"}
				root->count--;
            }
		}
        return root;
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

	printf("%d", Query(root, "ab"));
    root = Remove(root, "ab");
	printf("%d", Query(root, "ab"));
    root = Remove(root, "abnormal");
	printf("%d", Query(root, "ab"));

    //Clear(root);
    root = NULL;
    return 0;
}
