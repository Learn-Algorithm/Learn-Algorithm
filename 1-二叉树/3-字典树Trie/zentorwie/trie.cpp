//
// trie.cpp
// Created by zentorwie on 10-03-2014
#include <cstdio>
#include <string.h>

#define MAX 26

struct Trie {
  int cnt;  
  int end_cnt;  
  struct Trie* next[MAX];
};

Trie* NewTrie()
{
  Trie* T = new Trie;
  T->cnt = 1;
  T->end_cnt = 0;
  for (int i = 0; i < MAX; i++) 
    T->next[i] = NULL;
}

void Insert(Trie* T, char* s);
void Remove(Trie* T, char* s);
int Query(Trie* T, char* s);
int main()
{
  Trie* T = NewTrie();
  int cnt = 0;

  Insert(T, "happy");
  Insert(T, "peter");
  Insert(T, "ate");
  Insert(T, "ok");
  Insert(T, "happy");
  if (cnt = Query(T, "ok"))
    printf("\"ok\" appears %d times\n", cnt);
  else
    printf("Not found\n");

  if (cnt = Query(T, "happy"))
    printf("\"happy\" appears %d times\n", cnt);
  else
    printf("Not found\n");

  if (cnt = Query(T, "legal"))
    printf("\"legal\" appears %d times\n", cnt);
  else
    printf("\"legal\" not found\n");

    
  return 0;
}

void Insert(Trie* T, char* s)
{
  Trie* p = T;
  int len = strlen(s); 
  int idx;
  for (int i = 0; i < len; i++) {
    idx = s[i] - 'a';
    if (p->next[idx] == NULL) { p->next[idx] = NewTrie(); }
    else p->next[idx]->cnt++;
    p = p->next[idx];
  }
  p->end_cnt++;
}

// This function is not so perfect. It can only remove those words that exist.
void Remove(Trie* T, char* s)
{
  Trie* p = T;
  int len = strlen(s), idx;
  for (int i = 0; i < len-1; i++) {
    idx = s[i] - 'a';
    p->next[idx]->cnt--;
    p = p->next[idx];
  }
  idx = s[len-1] - 'a';
  p->next[idx]->cnt--;
  p->next[idx]->end_cnt--;

  if (p->next[idx]->cnt == 0) {
    Trie* tmp = p->next[idx];
    p->next[idx] = NULL;
    delete(tmp);
  }
}

int Query(Trie* T, char* s)
{
  Trie* p = T;
  int len = strlen(s), idx;
  for (int i = 0; i < len; i++) {
    idx = s[i] - 'a';
    if (p->next[idx] == NULL) { return 0; }
    p = p->next[idx];
  }
  return p->end_cnt;
}

