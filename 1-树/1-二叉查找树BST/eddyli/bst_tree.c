#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define SUCCESS 0
#define E_EXIST -1
#define MAX_COUNT 512

typedef struct Node{
    int item;
    struct Node* lchild;
    struct Node* rchild;
}Node;

int bst_insert(Node* node, int num) {
	Node **next_node = NULL;
	if (node->item == num) {
		return E_EXIST;
	}

	if (num < node->item) 
		next_node = &node->lchild;
	else
		next_node = &node->rchild;

	if (*next_node == NULL) {
		*next_node = (Node*)calloc(1, sizeof(Node));
		(*next_node)->item = num;
		return SUCCESS;
	} else {
		return bst_insert(*next_node, num);
	}
		
}

Node * create_bst_tree(int* num, int len) {
	int i = 1;
	Node * root = (Node*)calloc(1, sizeof(Node));
	if (root == NULL)
		return NULL;
	root->item = num[0];
	for (;i < len; i++) {
		bst_insert(root, num[i]);
	}
	return root;
}

Node* bst_search(Node * node , int item) {
	if (node == NULL)
		return NULL;

	if (node->item == item)
		return node;

	if( item > node->item)
		return bst_search(node->rchild, item);
	else
		return bst_search(node->lchild, item);
}

int get_nums_input(int *p, int max_len) {
	char str[MAX_COUNT] = { 0 };
	char* p_end = str;
	char* p_pre = NULL;
	int count = 0;
	int num;

	printf("please input some numbers separate by space \n>");
	if (fgets(str, max_len, stdin) == NULL) {
		printf("read input error!\n");
		return 0;
	}
	
	while( count < max_len ) {
		p_pre = p_end;
		num = strtol(p_end, &p_end, 10);
		if (p_end == p_pre)
			break;
		p[count] = num;
		count += 1;
	}

	return count;
}


void level_order_traverse(Node *T) {
	Node * node_list[MAX_COUNT] = { {0} };
	Node * node = T;
	int index = 0;
	int length = 1;
	int flag = 0;
	node_list[0] = T;
	
	while(index < MAX_COUNT) {
		Node * node = node_list[index];
		if (node != NULL) {

			printf("%d", node->item);
			if (node->lchild != NULL) {
				length = 2 * index + 1;
				node_list[2*index + 1] = node->lchild;
			}
			if (node->rchild != NULL) {
				length = 2 * index + 2;
				node_list[length] = node->rchild;
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
	int nums[MAX_COUNT];
	int count = 0;
	Node head, *node;
	int num;

	count = get_nums_input(nums, MAX_COUNT);
	head = *create_bst_tree(nums, count);
	level_order_traverse(&head);
	printf("\ninput a num to search\n>");
	scanf("%d", &num);
	node = bst_search(&head, num);
	if (node != NULL) {
		printf("IN!\n");
	} else {
		printf("NOT IN!\n");
	}
	return 0;
}