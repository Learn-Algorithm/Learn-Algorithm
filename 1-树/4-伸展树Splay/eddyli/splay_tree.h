typedef struct Node{
    int item;
	struct Node* parent;
    struct Node* lchild;
    struct Node* rchild;
} Node;

Node * insert(Node*,int);
void splay(Node*);
void zig(Node*);
void zag(Node*);