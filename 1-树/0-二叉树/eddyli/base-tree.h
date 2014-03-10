#include<stdio.h>

typedef struct BitNode BitNode;
struct BitNode {
	long int item;
	struct BitNode* lChild;
	struct BitNode* rChild;
};

BitNode ** create_bit_tree(BitNode** T);
void level_order_traverse(BitNode *T);
