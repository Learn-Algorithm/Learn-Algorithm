/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "hashtable.h"

/**
 * @brief initial the hashtable
 * @details this function not alloc memory for HashTable pointer
 * 
 * @param HashTable the pointer of hashtable
 */
HashTable* ht_init(int size){
    HashTable* ht_pointer;
    ht_pointer=(HashTable*)malloc(sizeof(HashTable));
    memset(ht_pointer, 0, sizeof(HashTable));
    ht_pointer->ht_max_size=size;
    ht_pointer->table=(HashNode**)malloc(sizeof(HashNode*)*ht_pointer->ht_max_size);
    memset(ht_pointer->table,0,sizeof(HashNode*)*ht_pointer->ht_max_size);
    ht_pointer->ht_size= 0;
    return ht_pointer;
}

/**
 * string hash function
 * @param  skey hash node key
 * @return      [description]
 */
unsigned int ht_hash_function(const char* skey)
{
    const signed char *p = (const signed char*)skey;
    unsigned int h = *p;

    if(h)
    {
        for(p += 1; *p != '\0'; ++p)
            h = (h << 5) - h + *p;
    }
    return h;
}

/**
 * @brief insert key-value into hash table
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey key
 * @param nvalue value
 */
int ht_insert(HashTable* hash_table, const char* skey, Node* pvalue){
	unsigned int pos;
	HashNode* pHead;
	HashNode* pNewNode;

    ///if hashtable size is over, return
    if(hash_table->ht_size >= hash_table->ht_max_size)
    {
        printf("out of hash table memory!\n");
        return -1;
    }
    ///caculate the position of hashnode list
    pos = ht_hash_function(skey) % hash_table->ht_max_size;
    ///set the head of node list
    pHead = *(hash_table->table+pos);
    while(pHead)
    {
        ///check whether the key is exist
        if(strcmp(pHead->sKey, skey) == 0)
        {
            printf("%s already exists!\n", skey);
            free(pvalue);
            return -1;
        }
        pHead = pHead->pNext;
    }
    pNewNode = (HashNode*)malloc(sizeof(HashNode));
    memset(pNewNode, 0, sizeof(HashNode));
    pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));
    strcpy(pNewNode->sKey, skey);
    pNewNode->pValue = pvalue;
    pNewNode->pNext = hash_table->table[pos];
    hash_table->table[pos] = pNewNode;
    hash_table->ht_size++;
    return 0;
}

/**
 * @brief remove the hash node from hashtable
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey the key of hashtable you'll remove
 */
void ht_remove(HashTable* hash_table, const char* skey){
    unsigned int pos = ht_hash_function(skey) % hash_table->ht_max_size;

    if(hash_table->table[pos])
    {
        HashNode* pHead = hash_table->table[pos];
        HashNode* pLast = NULL;
        HashNode* pRemove = NULL;
        while(pHead)
        {
            if(strcmp(skey, pHead->sKey) == 0)
            {
                pRemove = pHead;
                break;
            }
            pLast = pHead;
            pHead = pHead->pNext;
        }
        if(pRemove)
        {
            if(pLast)
                pLast->pNext = pRemove->pNext;
            else{
                free(hash_table->table[pos]->pValue);
                hash_table->table[pos] = NULL;
            }
                
            free(pRemove->sKey);
            free(pRemove);
        }
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param HashTable [description]
 * @param skey [description]
 * @return [description]
 */
Node* ht_lookup(HashTable* hash_table, const char* skey){
    HashNode* pHead;
    unsigned int pos = ht_hash_function(skey) % hash_table->ht_max_size;
    
    if(hash_table->table[pos])
    {
        pHead = hash_table->table[pos];
        while(pHead)
        {
            if(strcmp(skey, pHead->sKey) == 0){
                return hash_table->table[pos]->pValue;
            }else{
                pHead = pHead->pNext;
            }
            
        }
    }
    return NULL;
}

/**
 * @brief release the hashtable
 * @details [long description]
 * 
 * @param hash_table the hashtable
 */
void ht_destroy(HashTable* hash_table){
    int i;
    HashNode* pTemp;
    HashNode* pHead;

    for(i = 0; i < hash_table->ht_max_size; ++i)
    {
        if(hash_table->table[i])
        {
            pHead = hash_table->table[i];
            while(pHead)
            {
                pTemp = pHead;
                pHead = pHead->pNext;
                if(pTemp)
                {
                    free(pTemp->sKey);
                    free(pTemp->pValue);
                    free(pTemp);
                }
            }
        }
    }
    free(hash_table->table);
    free(hash_table);
    hash_table=NULL;
}

//========================================================

/**
 * @brief print hashtable
 * @details [long description]
 * 
 * @param hash_table [description]
 */
void ht_print(HashTable* hash_table){
    int i;

    printf("===========content of hash table=================\n");
    for (i = 0; i < hash_table->ht_max_size; ++i)
        if (hash_table->table[i])
        {
            HashNode *pHead = hash_table->table[i];
            printf("%d=>", i);
            while (pHead)
            {
                printf("%s:[%p]",pHead->sKey, pHead->pValue);
                if(inte==pHead->pValue->type){
                    printf("(%d)",(int)pHead->pValue->element.i);
                }else if(floate==pHead->pValue->type){
                    printf("(%f)",(float)pHead->pValue->element.f);
                }else if(doublee==pHead->pValue->type){
                    printf("(%lf)",(double)pHead->pValue->element.lf);
                }else if(stringe==pHead->pValue->type){
                    printf("(%s)",(char*)pHead->pValue->element.s);
                }else if(structe==pHead->pValue->type){
                    printf("(%p)",(void*)pHead->pValue->element.st);
                }
                pHead = pHead->pNext;
            }
            printf("\n");
        }
}
