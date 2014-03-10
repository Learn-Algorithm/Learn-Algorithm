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

bool Insert (trietree* root,  char* word);
int  Query  (trietree* root,  char* word);
bool Remove_not_free (trietree* root,  char* word);          // 删除单词，减少 count 值,但不free内存
bool Remove_whith_free (trietree* root,  char* word);        // 删除单词。减少 count 值,free内存（待完成）
trietree new_node (char key);

int main()
{
    trietree root = new_node ('#');
    int count, flag;
    char* word;

    while (true)
    {
        printf ("\n[0] exit    [1] insert    [2] remove    [3] query\n");
        printf ("option:");
        scanf ("%d",&flag);

        if (0 == flag) break;

        switch (flag )
        {
            case 1:

                printf ("\n输入待插入的单词，以空格分开（end with EOF）:");

                while (scanf("%s",word) != EOF)
                {
                    Insert (&root, word);
                }

                break;

            case 2:

                printf ("\n输入待删除的单词：");
                scanf ("%s",word);

                Remove_not_free(&root,word);

                break;

            case 3:

                printf ("\n输入待查询的单词：");
                scanf ("%s",word);

                count = Query (&root,word);

                if (!count)
                {
                    printf ("\n单词不存在！\n");
                }
                else
                {
                    printf ("\n%s 的引用共有 %d 个。\n",word,count);
                }

                break;

            default:

                printf ("Invalid option!\n");

                break;
        }
    }

    return 0;
}

bool Insert (trietree* root,  char* word)
{
    trietree tree = *root;

    while (1)
    {
        int index = *word - 'a';

        if (NULL == tree -> subtries[index])
        {
            tree -> subtries[index] = new_node(*word);
        }

        printf ("key=%c index=%d\n",*word, index);

        word++;

        if (!*word)
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

int  Query (trietree* root, char* word)
{
    trietree tree = *root;
    int count = 0;

    while (1)
    {

        int index = *word -'a';

        if (NULL == tree->subtries[index])
        {
            printf ("\nword does not exit!\n");
            return count;
        }

        printf ("word=%s\n",word);
        printf ("tree->count=%d\n",tree->count);

        word++;

        if(!*word)
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

bool Remove_not_free (trietree* root, char* word)
{
    trietree tree = *root;

    while (1)
    {
        int index = *word - 'a';

        printf ("remove--word:%s\n",word); 

        word++;

        if (!*word)                                        // 找到该单词的黄色节点，count--，不free节点。
        {
            if ( tree->count > 0)
            {
                printf ("remove--tree--from--count=%d\n",tree->count);
                tree->count--;   
                printf ("remove--tree--to----count=%d\n",tree->count);
                break;
            }
            else                                           // cout == 0, 说明单词已经被删除
            {
                printf ("your word does not exit !\n");   
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
        exit (1);
    }
    node->value = key;
    node->count = 0;

    for (int i = 0; i < MAX_NUM; i++)
    {
        node->subtries[i] = NULL;
    }

    return node;
}
