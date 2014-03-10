//
//  trie.h
//  Trie
//
//  Created by WolfLee on 14-3-8.
//  Copyright (c) 2014年 WolfLee. All rights reserved.
//

#ifndef Trie_trie_h
#define Trie_trie_h

#include <stdbool.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

#define ALPHABET_SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

typedef struct Trie {
    int count;
    char value;
    struct Trie* children[ALPHABET_SIZE];
}Trie;

Trie* Init(void);
Trie* Insert(Trie* root, char* word);
int Query(Trie* root, char* word);
Trie* Remove(Trie* root, char* word);
bool Exists(Trie* t, char* word);

#endif
