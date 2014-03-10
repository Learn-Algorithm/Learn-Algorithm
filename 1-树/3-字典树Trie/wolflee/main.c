//
//  main.c
//  Trie
//
//  Created by WolfLee on 14-3-8.
//  Copyright (c) 2014年 WolfLee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "trie.h"

int main(int argc, const char * argv[])
{
    Trie *t = Init();

    //Insert some words
    t = Insert(t, "foo");
    t = Insert(t, "foo");
    t = Insert(t, "foo");
    t = Insert(t, "foobar");
    t = Insert(t, "bar");
    t = Insert(t, "bar");
    t = Insert(t, "baz");

    //Remove some words
    t = Remove(t, "bak");
    t = Remove(t, "bar");

    //Check for existence
    printf("'foo' is in the trie: %s\n",    Exists(t, "foo") ? "yes" : "no" );
    printf("'cars' is in the trie: %s\n",   Exists(t, "cars") ? "yes" : "no" );

    //Query words
    printf("number of 'foo' is in the trie: %d\n",    Query(t, "foo") );
    printf("number of 'foob' is in the trie: %d\n",   Query(t, "foob"));
    printf("number of 'foobar' is in the trie: %d\n", Query(t, "foobar"));
    printf("number of 'bar' is in the trie: %d\n",    Query(t, "bar"));
    printf("number of 'cars' is in the trie: %d\n\n", Query(t, "cars"));

    return 0;
}
