//
//  trie.c
//  Trie
//
//  Created by WolfLee on 14-3-8.
//  Copyright (c) 2014年 WolfLee. All rights reserved.
//

#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Trie* Create(char ch)
{
    Trie *node = (Trie *)malloc(sizeof(Trie));
    if (!node) {
        exit(-1);
    }
    node->count = 0;
    node->value = ch;
    for (int i = 0; i < ARRAY_SIZE(node->children); i++) {
        node->children[i] = NULL;
    }
    return node;
}

Trie* Init(void)
{
   return Create(' ');
}

Trie* Insert(Trie* t, char* word)
{
    Trie *cur = t;
    int len = (int)strlen(word);
    for (int i = 0; i < len; i++) {
        int index = CHAR_TO_INDEX(word[i]);
        if (cur->children[index] == NULL) {
            cur->children[index] = Create(word[i]);
        }
        cur = cur->children[index];
    }
    cur->count++;
    return t;
}

int Query(Trie* t, char* word)
{
    Trie* cur = t;
    int len = (int)strlen(word);
    for (int i = 0; i < len; i++) {
        int index = CHAR_TO_INDEX(word[i]);
        if (cur->children[index] == NULL) {
            break;
        }
        cur = cur->children[index];
    }
    return cur->count;
}

Trie* Remove(Trie* t, char* word)
{
    Trie* cur = t;
    int len = (int)strlen(word);
    for (int i = 0; i < len; i++) {
        int index = CHAR_TO_INDEX(word[i]);
        if (cur->children[index] == NULL) {
            return t;
        }
        cur = cur->children[index];
    }
    if (cur != NULL) {
        cur->count--;
    }
    return t;
}

bool Exists(Trie* t, char* word)
{
    return Query(t, word) > 0 ? true : false;
}
