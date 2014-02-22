#define MAX_COUNT 512

#include<malloc.h>
#include<stdlib.h>
#include"base-tree.h"

BitNode * get_next_node(BitNode* node_list[], 
						int current_index, 
						int total_length);

BitNode ** create_bit_tree(BitNode ** T) {
	BitNode* tree = (BitNode*)calloc(1, sizeof(BitNode));
	char str[MAX_COUNT] = { 0 };
	int nums[MAX_COUNT] = { 0 };
	char* p_end = str;
	char* p_pre = NULL;
	int count = 0;
	int num;
	int i;
	BitNode ** node_list; 

	if (tree == NULL)
		return NULL;

	printf("please input some numbers separate by space \n>");
	fgets(str, MAX_COUNT, stdin);
	
	while( count < MAX_COUNT ) {
		p_pre = p_end;
		num = strtol(p_end, &p_end, 10);
		if (p_end == p_pre)
			break;
		nums[count] = num;
		count += 1;
	}
	node_list = (BitNode **)calloc(count, sizeof(BitNode *));
	node_list[0] = tree;
	tree->item = nums[0];
	for (i = 1; i < count; i++) {
		BitNode * node = get_next_node(node_list, i-1, MAX_COUNT);
		if (node != NULL) {
			node->item = nums[i];
		} else {
			// error handle;
		}
	}

	*T = tree;
	return node_list;
}

BitNode * get_next_node(BitNode* node_list[], 
						int current_index, 
						int total_length) {

	BitNode * node = (BitNode*)calloc(1, sizeof(BitNode));
	BitNode * parent;
	int parent_index = current_index / 2;
	if (parent_index < 0 || parent_index >= total_length)
		return NULL;
	parent = node_list[parent_index];
	if (parent->lChild == NULL)
		parent->lChild = node;
	else if (parent->rChild == NULL)
		parent->rChild = node;
	else
		//error log
		return NULL;
	node_list[current_index + 1] = node;
	return node;
}

void level_order_traverse(BitNode *T) {
	BitNode * node_list[MAX_COUNT] = { {0} };
	BitNode * node = T;
	int index = 0;
	int flag = 2 * index + 2;
	node_list[0] = T;
	printf("%d ", node_list[index]->item);
	printf("\n");
	
	while(index < MAX_COUNT) {
		int parent_index = index/ 2;
		if (node_list[parent_index]->lChild == NULL)
			break;
		index += 1;
		node_list[index] = node_list[parent_index]->lChild;
		printf("%d ", node_list[index]->item);
		index += 1;
		if (node_list[parent_index]->rChild == NULL)
			break;
		node_list[index] = node_list[parent_index]->rChild;
		printf("%d ", node_list[index]->item);
		if ( index == flag ) {
			printf("\n");
			flag = 2 * index + 2;
		}
	}
}

int main() {
	BitNode ** head = (BitNode **)calloc(1, sizeof(BitNode *));
	BitNode ** node_list = create_bit_tree(head);
	level_order_traverse(*head);
	//free memery
}