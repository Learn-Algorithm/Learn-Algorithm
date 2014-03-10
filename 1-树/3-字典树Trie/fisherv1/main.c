//
//  main.c
//  TireTree
//
//  Created by Matthew Lu on 7/03/2014.
//  Copyright (c) 2014 Matthew Lu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNT 26

typedef struct Trie
{
    int count;
    char value;
    struct Trie *subtries[MAX_COUNT];
}*TrieTree,Trie;



void InitTrieRoot(Trie **pRoot)
{
    *pRoot = NULL;
}



Trie *CreateTrie()
{
    int i;
    Trie *p;
    
    p= (Trie*)malloc(sizeof(Trie));
    p->count = 1;
    
    for (i=0; i<MAX_COUNT; i++) {
        p->subtries[i] = NULL;
    }
    
    return p;
}


void InsertTrie(Trie **pRoot,char *s)
{
    int i,k;
    Trie *p;
    
    if (!(p = *pRoot)) {
        p = *pRoot = CreateTrie();
    }
    
    i =0;
    
    while (s[i]) {
        k = s[i++] - 'a';
        if (p->subtries[k]) {
            p->subtries[k]->count++;
        }
        else
        {
            p->subtries[k] = CreateTrie();
        }
        p=p->subtries[k];
    }
    
}


void RemoveTrie(Trie **pRoot,char *s)
{
    Trie *p = *pRoot;
    
    const char *w = s;
    while (*w) {
        char c = tolower(*w);
        
        if (c == -1) {
            return;
        }
        
        int index = c  -'a';
        
        if (!p->subtries[index]) {
            return;
        }
        
        p = p->subtries[index];
        ++w;
    }
    
    if (p->count >0) {
        --p->count;
        return;
    }
    return;
}

int SearchTrie(Trie **pRoot,char *s)
{
    Trie *p;
    int i,k;
    
    if (!(p = *pRoot)) {
        return 0;
    }
    
    i = 0;
    while (s[i]) {
        k= s[i++] - 'a';
        if (p->subtries[k] == NULL) {
            return  0;
        }
        
        p=p->subtries[k];
        
    }
    return p->count;
}


int main(int argc, const char * argv[])
{

    // insert code here...
    printf("Hello, World!\n");
    
    char *str[5]= {"tree","car","bus","happy","business"};
    
    Trie *T = NULL;
    InitTrieRoot(&T);
    
    for(int i=0;i< sizeof(str)/sizeof(char *);i++)
    {
        char *strWord = str[i];
        
        while (gets(strWord) && strWord[0] ) {
            InsertTrie(&T, strWord);
        }
    }
    
    
    char *removeWord = "Tree";
    RemoveTrie(&T, removeWord);
    
    
    return 0;
}

