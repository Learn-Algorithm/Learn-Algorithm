#include "hashtable.h"

#define BUF_LEN 4
#define ITEM_NUM 500000

int main(int argc, char const *argv[])
{
	HashTable* hash_table;
	int i;
	FILE *fp;
	char a[BUF_LEN];

	hash_table=ht_init(ITEM_NUM);

	if (argc<2)
	{
		printf("Setting Inputfile Please!\n");
		return 0;
	}

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("File Name Error.\n");
		return 0;
	}

	i=0;
	while(!feof(fp))
	{
		memset(a,0,BUF_LEN);
		if(fgets(a,BUF_LEN,fp))
		{
			i++;
			if (strcmp(a,"\n")!=0)
			{
				ht_insert(hash_table, a, create_node_string(a));
			}
		}else{
			break;
		}
	}

	printf("%d items hava read.\n", i);
	
	ht_print(hash_table);
	ht_destroy(hash_table);
	return 0;
}



