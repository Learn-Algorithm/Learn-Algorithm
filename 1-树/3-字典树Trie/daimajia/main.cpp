//
//  main.cpp
//  Trie
//
//  Created by 代码家 on 14-3-6.
//  Copyright (c) 2014年 daimajia. All rights reserved.
//

#include <iostream>

#define MAX_LEN 26

struct Trie
{
    int count;  //count 如果为0，则代表非黄色点，count>0代表是黄色点，同时表示出现次数;
    char value; //字符
    struct Trie* next[MAX_LEN]; //子树
};
void Insert(Trie **trees,char* str);

void Create(Trie **tree){
    char string[MAX_LEN];
    while (scanf("%s",string) != EOF) {
        Insert(tree, string);
    }
    rewind(stdin);
}

void Insert(Trie **trees,char* str){
    
    if (*str == '\0') {
        (*trees)->count += 1;
        return;
    }
    
    Trie **next = (*trees)->next;
    int distance = *str - 97;
    
    if (next[distance] == NULL) {
        next[distance] = (Trie*)malloc(sizeof(Trie));
        next[distance]->value = *str;
    }
    return Insert(&next[distance], str+1);
}

void Remove(Trie **tree,char* str){
    
    if (*str == '\0') {
        (*tree)->count = 0;
        return;
    }
    
    Trie** next = (*tree)->next;
    int distance = *str - 97;
    if (next[distance] != NULL) {
        return Remove(&next[distance], str+1);
    }
}

void Query(Trie **trees,char* word){
    
    if (*word == '\0') {
        if ((*trees)->count > 0) {
            printf("存在\n");
        }else{
            printf("不存在\n");
        }
        return;
    }
    
    Trie **next = (*trees)->next;
    int distance = *word - 97;
    
    if (next[distance] != NULL) {
        return Query(&next[distance], word+1);
    }else{
        printf("单词不存在\n");
    }
}

int main(int argc, const char * argv[])
{
    Trie* tree = (Trie*)malloc(sizeof(Trie));
    Create(&tree);
    
    char query[MAX_LEN];
    printf("输入一个查询串:");
    while (scanf("%s",query) != EOF) {
        Query(&tree, query);
    }

    rewind(stdin);
    
    char toDelete[MAX_LEN];
    printf("输入一个删除串:");
    while (scanf("%s",toDelete) != EOF) {
        Remove(&tree, toDelete);
    }
    
    return 0;
}

