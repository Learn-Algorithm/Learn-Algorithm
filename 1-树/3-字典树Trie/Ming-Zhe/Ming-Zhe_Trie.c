//
//  main.c
//  Trie
//
//  Created by Ming-Zhe on 14-3-9.
//  Copyright (c) 2014年 Ming-Zhe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTER 26

typedef struct Trie{
    int count;
    char value;
    struct Trie* next[MAX_LETTER];
}DNode,*DTree;

DTree creat()
{
    int i;
    DTree tree = (DTree)malloc(sizeof(DNode));
    tree->value = ' ';
    tree->count = 0;
    for (i = 0; i < MAX_LETTER; i++) {
        tree->next[i] = NULL;
    }
    return tree;
}

DTree insert(char *str, DTree tree)
{
    unsigned long len = strlen(str);
    char string[30];
    strcpy(string, str);
    
    DNode* node = tree;
    for (int i = 0; i < len; i++) {
        if (node->next[string[i] - 'a'] != NULL) {
            node = node->next[string[i] - 'a'];
            if (i==len - 1) {
                node->count++;
                printf("\"%s\" insert over\n",str);
            }
        }else{
            node->next[string[i] - 'a'] = (DNode *)malloc(sizeof(DNode));
            node = node->next[string[i] - 'a'];
            node->value = string[i];
            for (int j = 1; j < MAX_LETTER; j++) {
                node->next[j] = NULL;
            }
            if (i == len - 1) {
                node->count++;
                printf("\"%s\" insert over\n",str);
            }
        }
    }
    return tree;
}

int find(char* str, DTree tree)
{
    unsigned long len = strlen(str);
    char string[30];
    strcpy(string, str);
    DNode* node = tree;
    
    for (int i = 0; i < len; i++) {
        if (node->next[string[i]-'a'] == NULL) {
            //printf("find return 0\n");
            return 0;
        }
        if (node->next[string[i]-'a']->value == string[i]) {
            node = node->next[string[i]-'a'];
        }else{
            //printf("find return 0\n");
            return 0;
        }
        if (i==len - 1) {
            //printf("find return node->count\n");
            return node->count;
        }
    }
    //printf("find return 0\n");
    return 0;
}

DTree remove_str(char* str, DTree tree)
{
    unsigned long len = strlen(str);
    char string[30];
    strcpy(string, str);
    
    DNode* node = tree;
    DTree origin = tree;
    
    for (int i = 0; i < len; i++) {
        if (node->next[string[i] - 'a'] != NULL) {
            if (node->next[string[i]-'a']->value == string[i]) {
                node = node->next[string[i]-'a'];
            }else{
                break;
            }
            if (i==len - 1) {
                node->count--;
                printf("\"%s\" Delete over\n",str);
            }
        }else{
            break;
        }
    }
    
    return origin;
}

int main(int argc, const char * argv[])
{

    // insert code here...
    DTree tree= creat();
    tree = insert("asdf", tree);
    tree = insert("sdfg", tree);
    tree = insert("xcbf", tree);
    tree = insert("aszxc", tree);
    tree = insert("asdf", tree);
    
    int a = find("sdfg", tree);
    printf("%d words to find\n",a);
    
    tree = remove_str("sdfg", tree);
    
    a = find("sdfg", tree);
    printf("%d words to find\n",a);
    return 0;
}


