//count must in {[m/2], m};
typedef struct Node {
    int count;
    int *keys;
    struct Node **children;
    struct Node *next;
    struct Node *prev;
    struct Node *parent;
} Node;

typedef struct BPtree {
    int m;
    Node *root;
    Node *lleaf;
} BPtree;

int insert(int, BPtree*);