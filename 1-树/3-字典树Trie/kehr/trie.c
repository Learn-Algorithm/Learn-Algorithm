/*************************************************************************
 * @File Name:    trie.c
 * @Author:       kehr
 * @Mail:         kehr.china@gmail.com
 * @Created Time: Sun 09 Mar 2014 07:54:34 PM CST
 * @Copyright:    GPL 2.0 applies
 * @Description:                     
 *************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUM 26

typedef struct trie
{
    int  count;                         // count 如果为0，则代表非黄色点，count>0代表是黄色点，同时表示出现次数;
    char value;                         // 单词的字母            
    struct trie *subtries[MAX_NUM];     // 子树
}trie,*trietree;

bool Insert (trietree* root,  char* world);
int  Query  (trietree* root,  char* world);
bool Remove_not_free (trietree* root,  char* world);          // 删除单词，减少 count 值,但不free内存
bool Remove_whith_free (trietree* root,  char* world);        // 删除单词。减少 count 值,free内存（待完成）
trietree new_node (char key);

int main()
{
    trietree root = new_node('#');
    int count;

    printf("\n-------------------insert start\n");
    Insert(&root,"a");
    Insert(&root,"ab");
    Insert(&root,"abc");
    Insert(&root,"abc");
    Insert(&root,"abcd");
    Insert(&root,"abcd");
    Insert(&root,"abcde");
    Insert(&root,"abcdef");

    printf("\n-------------------query start\n");
    count = Query(&root,"abcdef");
    printf ("count=%d\n",count);

    printf("\n-------------------remove start\n");
    Remove_not_free(&root,"abcdef");

    printf("\n-------------------remove start\n");
    Remove_not_free(&root,"abcdef");

    printf("\n-------------------query start\n");
    count = Query(&root,"abcdef");
    printf ("count=%d\n",count);

    return 0;
}

bool Insert (trietree* root,  char* world)
{
    trietree tree = *root;

    while (1)
    {
        int index = *world - 'a';

        if (NULL == tree -> subtries[index])
        {
            tree -> subtries[index] = new_node(*world);
        }

        printf ("key=%c index=%d\n",*world, index);

        world++;

        if (!*world)
        {
            tree->count += 1;                           // 标记完整单词（黄色节点），即单词最后一个节点。
            break;
        }
        else
        {
            tree = tree->subtries[index];
        }
    }

    return true;
}

int  Query (trietree* root, char* world)
{
    trietree tree = *root;
    int count = 0;

    while (1)
    {

        int index = *world -'a';

        if(NULL == tree->subtries[index])
        {
            printf("count=%d\n",count);
            return count;
        }

        printf ("word=%s\n",world);
        printf("tree->count=%d\n",tree->count);

        world++;

        if(!*world)
        {
            count = tree->count;
            break;
        }
        else
        {
            tree = tree->subtries[index];
        }

    }

    return count;
}

bool Remove_not_free (trietree* root, char* world)
{
    trietree tree = *root;

    while (1)
    {
        int index = *world - 'a';

        printf ("remove--world:%s\n",world); 

        world++;

        if (!*world)                                        // 找到该单词的黄色节点，count--，不free节点。
        {
            if ( tree->count > 0)
            {
                printf("remove--tree--from--count=%d\n",tree->count);
                tree->count--;   
                printf("remove--tree--to----count=%d\n",tree->count);
                break;
            }
            else                                           // cout == 0, 说明单词已经被删除
            {
                printf("your world does not exit !\n");   
                return false;
            }
        }
        else
        {
            tree = tree->subtries[index];
        }
    }

    return true;
}

trietree new_node (char key)
{
    trietree node;
    if (NULL == (node = (trietree) malloc (sizeof(trie))))
    {
        exit(1);
    }
    node->value = key;
    node->count = 0;

    for (int i = 0; i < MAX_NUM; i++)
    {
        node->subtries[i] = NULL;
    }

    return node;
}
