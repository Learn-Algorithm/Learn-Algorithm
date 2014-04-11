#include"b+tree.h"
#include<string.h>

int main() {

    BPtree tree;
    Node node;
    memset(&node, 0, sizeof(node));
    tree.m = 3;
    tree.root = tree.lleaf = &node;
    insert(1, &tree);
    insert(3, &tree);
    insert(5, &tree);
    insert(7, &tree);
    insert(9, &tree);
    insert(2, &tree);
    insert(4, &tree);
    insert(6, &tree);
    insert(8, &tree);
    insert(10, &tree);
}