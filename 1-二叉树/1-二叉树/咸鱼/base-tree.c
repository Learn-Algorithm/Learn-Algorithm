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
	int length = 1;
	int flag = 0;
	node_list[0] = T;
	
	while(index < MAX_COUNT) {
		BitNode * node = node_list[index];
		if (node != NULL) {

			printf("%d", node->item);
			if (node->lChild != NULL) {
				length = 2 * index + 1;
				node_list[2*index + 1] = node->lChild;
			}
			if (node->rChild != NULL) {
				length = 2 * index + 2;
				node_list[length] = node->rChild;
			}
			
		} 
		printf(" ");
		if (index == length)
				break;

		if ( index == flag ) {
			printf("\n");
			flag = 2 * index + 2;
		}
		index += 1;
	}
}

int main() {
	BitNode ** head = (BitNode **)calloc(1, sizeof(BitNode *));
	BitNode ** node_list = create_bit_tree(head);
	level_order_traverse(*head);
	//free memery
}