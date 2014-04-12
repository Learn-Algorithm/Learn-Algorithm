/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "ds.h"

typedef struct HashNode HashNode;

/**
 * @brief hashtable node
 * @details [long description]
 * 
 */
struct HashNode
{
	///the key of node
    char* sKey;
    ///the value of node
    Node* pValue;
    ///node type
    etype type;
    ///next node
    HashNode* pNext;
} ;

typedef struct HashTable HashTable;

///hashtable struct
struct HashTable
{
	///hashtable current size
	int ht_size;
    ///hashtable max size
    int ht_max_size;
	///the hashtable nodes array
	HashNode** table;
};

/**
 * @brief initial the hashtable
 * @details this function not alloc memory for HashTable pointer
 * 
 * @param HashTable the pointer of hashtable
 */
HashTable* ht_init(int size);

/**
 * @brief insert key-value into hash table
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey key
 * @param nvalue value
 */
int ht_insert(HashTable* hash_table, const char* skey, Node* pvalue);

/**
 * @brief remove the hash node from hashtable
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey the key of hashtable you'll remove
 */
void ht_remove(HashTable* hash_table, const char* skey);

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param HashTable [description]
 * @param skey [description]
 * @return [description]
 */
Node* ht_lookup(HashTable* hash_table, const char* skey);

/**
 * @brief destroy the hashtable
 * @details [long description]
 * 
 * @param hash_table the hashtable
 */
void ht_destroy(HashTable* hash_table);

//========================================================

/**
 * @brief print hashtable
 * @details [long description]
 * 
 * @param hash_table [description]
 */
void ht_print(HashTable* hash_table);


#endif
