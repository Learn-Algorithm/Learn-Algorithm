//
//  b_plus_tree.c
//  BPlusTree
//
//  Created by WolfLee on 4/1/14.
//  Copyright (c) 2014 WolfLee. All rights reserved.
//

#include "b_plus_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

Node * FindLeaf(Node * root, int key);
Record * Find(Node * root, int key);
int Middle(int length);
Node * CreateNode(void);
Node * CreateLeaf(void);
int Left(Node * parent, Node * left);
Node * InsertLeaf(Node * leaf, int key, Record * record);
Node * InsertLeafAfterSplitting(Node * root, Node * leaf, int key, Record * record);
Node * InsertNode(Node * root, Node * parent, int left_index, int key, Node * right);
Node * InsertNodeAfterSplitting(Node * root, Node * parent, int left_index, int key, Node * right);
Node * InsertParent(Node * root, Node * left, int key, Node * right);
Node * InsertRoot(Node * left, int key, Node * right);
Node * CreateTree(int key, Record * record);
int Neighbor(Node * n);
Node * NewRoot(Node * root);
Node * JoinNodes(Node * root, Node * n, Node * neighbor, int neighbor_index, int k_prime);
Node * BalanceNodes(Node * root, Node * n, Node * neighbor, int neighbor_index, int k_prime_index, int k_prime);
Node * DeleteEntry(Node * root, Node * n, int key, void * pointer);

void Lookup(Node * root, int key)
{
    Record * record = Find(root, key);
    if (record == NULL) {
        printf("Record not found under key %d.\n", key);
    } else {
        printf("Record at %lx -- key %d, value %d.\n", (unsigned long)record, key, record->value);
    }
}

Node * FindLeaf(Node * root, int key)
{
    int i = 0;
    Node * c = root;
    if (c == NULL) {
        return c;
    }
    while (!c->is_leaf) {
        i = 0;
        while (i < c->num_keys) {
            if (key >= c->keys[i]) i++;
            else break;
        }
        c = (Node *)c->pointers[i];
    }
    return c;
}

Record * Find(Node * root, int key)
{
    int i = 0;
    Node * c = FindLeaf(root, key);
    if (c == NULL) return NULL;
    for (i = 0; i < c->num_keys; i++)
        if (c->keys[i] == key) break;
    if (i == c->num_keys)
        return NULL;
    else
        return (Record *)c->pointers[i];
}

int Middle(int length)
{
    return (length % 2 == 0) ? length / 2 : length / 2 + 1;
}

Record * CreateRecord(int value)
{
    Record * new_record = (Record *)malloc(sizeof(Record));
    assert(new_record);
    new_record->value = value;
    return new_record;
}


Node * CreateNode(void)
{
    Node * new_node;
    new_node = malloc(sizeof(Node));
    assert(new_node);
    new_node->keys = malloc((ORDER - 1) * sizeof(int));
    assert(new_node->keys);
    new_node->pointers = malloc(ORDER * sizeof(void *));
    assert(new_node->pointers);
    new_node->is_leaf = false;
    new_node->num_keys = 0;
    new_node->parent = NULL;
    new_node->next = NULL;
    return new_node;
}

Node * CreateLeaf(void)
{
    Node * leaf = CreateNode();
    leaf->is_leaf = true;
    return leaf;
}

int Left(Node * parent, Node * left)
{
    int left_index = 0;
    while (left_index <= parent->num_keys && parent->pointers[left_index] != left) {
        left_index++;
    }
    return left_index;
}

Node * InsertLeaf(Node * leaf, int key, Record * record)
{

    int i, insertion_point;

    insertion_point = 0;
    while (insertion_point < leaf->num_keys && leaf->keys[insertion_point] < key) {
        insertion_point++;
    }

    for (i = leaf->num_keys; i > insertion_point; i--) {
        leaf->keys[i] = leaf->keys[i - 1];
        leaf->pointers[i] = leaf->pointers[i - 1];
    }
    leaf->keys[insertion_point] = key;
    leaf->pointers[insertion_point] = record;
    leaf->num_keys++;
    return leaf;
}

Node * InsertLeafAfterSplitting(Node * root, Node * leaf, int key, Record * record)
{
    Node * new_leaf;
    int * temp_keys;
    void ** temp_pointers;
    int insertion_index, split, new_key, i, j;

    new_leaf = CreateLeaf();

    temp_keys = malloc(ORDER * sizeof(int));
    assert(temp_keys);
    temp_pointers = malloc(ORDER * sizeof(void *));
    assert(temp_pointers);
    insertion_index = 0;
    while (insertion_index < ORDER - 1 && leaf->keys[insertion_index] < key) {
        insertion_index++;
    }

    for (i = 0, j = 0; i < leaf->num_keys; i++, j++) {
        if (j == insertion_index) j++;
        temp_keys[j] = leaf->keys[i];
        temp_pointers[j] = leaf->pointers[i];
    }

    temp_keys[insertion_index] = key;
    temp_pointers[insertion_index] = record;
    leaf->num_keys = 0;
    split = Middle(ORDER - 1);

    for (i = 0; i < split; i++) {
        leaf->pointers[i] = temp_pointers[i];
        leaf->keys[i] = temp_keys[i];
        leaf->num_keys++;
    }

    for (i = split, j = 0; i < ORDER; i++, j++) {
        new_leaf->pointers[j] = temp_pointers[i];
        new_leaf->keys[j] = temp_keys[i];
        new_leaf->num_keys++;
    }

    free(temp_pointers);
    free(temp_keys);

    new_leaf->pointers[ORDER - 1] = leaf->pointers[ORDER - 1];
    leaf->pointers[ORDER - 1] = new_leaf;

    for (i = leaf->num_keys; i < ORDER - 1; i++) {
        leaf->pointers[i] = NULL;
    }
    for (i = new_leaf->num_keys; i < ORDER - 1; i++) {
        new_leaf->pointers[i] = NULL;
    }

    new_leaf->parent = leaf->parent;
    new_key = new_leaf->keys[0];

    return InsertParent(root, leaf, new_key, new_leaf);
}

Node * InsertNode(Node * root, Node * n, int left_index, int key, Node * right)
{
    int i;

    for (i = n->num_keys; i > left_index; i--) {
        n->pointers[i + 1] = n->pointers[i];
        n->keys[i] = n->keys[i - 1];
    }
    n->pointers[left_index + 1] = right;
    n->keys[left_index] = key;
    n->num_keys++;
    return root;
}

Node * InsertNodeAfterSplitting(Node * root, Node * old_node, int left_index, int key, Node * right)
{

    int i, j, split, k_prime;
    Node * new_node, * child;
    int * temp_keys;
    Node ** temp_pointers;

    temp_pointers = malloc((ORDER + 1) * sizeof(Node *));
    assert(temp_pointers);
    temp_keys = malloc(ORDER * sizeof(int));
    assert(temp_pointers);

    for (i = 0, j = 0; i < old_node->num_keys + 1; i++, j++) {
        if (j == left_index + 1) j++;
        temp_pointers[j] = old_node->pointers[i];
    }

    for (i = 0, j = 0; i < old_node->num_keys; i++, j++) {
        if (j == left_index) j++;
        temp_keys[j] = old_node->keys[i];
    }

    temp_pointers[left_index + 1] = right;
    temp_keys[left_index] = key;

    split = Middle(ORDER);
    new_node = CreateNode();
    old_node->num_keys = 0;
    for (i = 0; i < split - 1; i++) {
        old_node->pointers[i] = temp_pointers[i];
        old_node->keys[i] = temp_keys[i];
        old_node->num_keys++;
    }
    old_node->pointers[i] = temp_pointers[i];
    k_prime = temp_keys[split - 1];
    for (++i, j = 0; i < ORDER; i++, j++) {
        new_node->pointers[j] = temp_pointers[i];
        new_node->keys[j] = temp_keys[i];
        new_node->num_keys++;
    }
    new_node->pointers[j] = temp_pointers[i];
    free(temp_pointers);
    free(temp_keys);
    new_node->parent = old_node->parent;
    for (i = 0; i <= new_node->num_keys; i++) {
        child = new_node->pointers[i];
        child->parent = new_node;
    }

    return InsertParent(root, old_node, k_prime, new_node);
}

Node * InsertParent(Node * root, Node * left, int key, Node * right)
{
    int left_index;
    Node * parent;

    parent = left->parent;

    if (parent == NULL) return InsertRoot(left, key, right);

    left_index = Left(parent, left);
    if (parent->num_keys < ORDER - 1) return InsertNode(root, parent, left_index, key, right);

    return InsertNodeAfterSplitting(root, parent, left_index, key, right);
}

Node * InsertRoot(Node * left, int key, Node * right)
{

    Node * root = CreateNode();
    root->keys[0] = key;
    root->pointers[0] = left;
    root->pointers[1] = right;
    root->num_keys++;
    root->parent = NULL;
    left->parent = root;
    right->parent = root;
    return root;
}

Node * CreateTree(int key, Record * record)
{

    Node * root = CreateLeaf();
    root->keys[0] = key;
    root->pointers[0] = record;
    root->pointers[ORDER - 1] = NULL;
    root->parent = NULL;
    root->num_keys++;
    return root;
}

Node * Insert(Node * root, int key, Record * record)
{

    Node * leaf;

    if (Find(root, key) != NULL) return root;

    if (root == NULL) return CreateTree(key, record);

    leaf = FindLeaf(root, key);
    if (leaf->num_keys < ORDER - 1) {
        leaf = InsertLeaf(leaf, key, record);
        return root;
    }

    return InsertLeafAfterSplitting(root, leaf, key, record);
}

int Neighbor(Node * n)
{

    int i;

    for (i = 0; i <= n->parent->num_keys; i++) {
        if (n->parent->pointers[i] == n) return i - 1;
    }

    printf("Search for nonexistent pointer to node in parent.\n");
    printf("Node:  %#lx\n", (unsigned long)n);
    exit(-1);
}

Node * RemoveFromNode(Node * n, int key, Node * pointer)
{

    int i, num_pointers;

    i = 0;
    while (n->keys[i] != key) {
        i++;
    }
    for (++i; i < n->num_keys; i++) {
        n->keys[i - 1] = n->keys[i];
    }

    num_pointers = n->is_leaf ? n->num_keys : n->num_keys + 1;
    i = 0;
    while (n->pointers[i] != pointer) {
        i++;
    }
    for (++i; i < num_pointers; i++) {
        n->pointers[i - 1] = n->pointers[i];
    }

    n->num_keys--;

    if (n->is_leaf) {
        for (i = n->num_keys; i < ORDER - 1; i++) {
            n->pointers[i] = NULL;
        }
    } else {
        for (i = n->num_keys + 1; i < ORDER; i++) {
            n->pointers[i] = NULL;
        }
    }

    return n;
}

Node * NewRoot(Node * root)
{

    Node * new_root;

    if (root->num_keys > 0) return root;

    if (!root->is_leaf) {
        new_root = root->pointers[0];
        new_root->parent = NULL;
    } else {
        new_root = NULL;
    }

    free(root->keys);
    free(root->pointers);
    free(root);

    return new_root;
}

Node * JoinNodes(Node * root, Node * n, Node * neighbor, int neighbor_index, int k_prime)
{

    int i, j, neighbor_insertion_index, n_start, n_end, new_k_prime;
    Node * tmp;
    bool split;

    if (neighbor_index == -1) {
        tmp = n;
        n = neighbor;
        neighbor = tmp;
    }

    neighbor_insertion_index = neighbor->num_keys;

    split = false;

    if (!n->is_leaf) {
        neighbor->keys[neighbor_insertion_index] = k_prime;
        neighbor->num_keys++;

        n_end = n->num_keys;
        n_start = 0;

        if (n->num_keys + neighbor->num_keys >= ORDER) {
            split = true;
            n_end = Middle(ORDER) - 2;
        }

        for (i = neighbor_insertion_index + 1, j = 0; j < n_end; i++, j++) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_keys++;
            n->num_keys--;
            n_start++;
        }

        neighbor->pointers[i] = n->pointers[j];

        if (split) {
            new_k_prime = n->keys[n_start];
            for (i = 0, j = n_start + 1; i < n->num_keys; i++, j++) {
                n->keys[i] = n->keys[j];
                n->pointers[i] = n->pointers[j];
            }
            n->pointers[i] = n->pointers[j];
            n->num_keys--;
        }

        for (i = 0; i < neighbor->num_keys + 1; i++) {
            tmp = (Node *)neighbor->pointers[i];
            tmp->parent = neighbor;
        }
    } else {
        for (i = neighbor_insertion_index, j = 0; j < n->num_keys; i++, j++) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_keys++;
        }
        neighbor->pointers[ORDER - 1] = n->pointers[ORDER - 1];
    }

    if (!split) {
        root = DeleteEntry(root, n->parent, k_prime, n);
        free(n->keys);
        free(n->pointers);
        free(n);
    } else {
        for (i = 0; i < n->parent->num_keys; i++) {
            if (n->parent->pointers[i + 1] == n) {
                n->parent->keys[i] = new_k_prime;
                break;
            }
        }
    }

    return root;
}

Node * BalanceNodes(Node * root, Node * n, Node * neighbor, int neighbor_index, int k_prime_index, int k_prime)
{
    int i;
    Node * tmp;

    if (neighbor_index != -1) {
        if (!n->is_leaf) n->pointers[n->num_keys + 1] = n->pointers[n->num_keys];
        for (i = n->num_keys; i > 0; i--) {
            n->keys[i] = n->keys[i - 1];
            n->pointers[i] = n->pointers[i - 1];
        }
        if (!n->is_leaf) {
            n->pointers[0] = neighbor->pointers[neighbor->num_keys];
            tmp = (Node *)n->pointers[0];
            tmp->parent = n;
            neighbor->pointers[neighbor->num_keys] = NULL;
            n->keys[0] = k_prime;
            n->parent->keys[k_prime_index] = neighbor->keys[neighbor->num_keys - 1];
        } else {
            n->pointers[0] = neighbor->pointers[neighbor->num_keys - 1];
            neighbor->pointers[neighbor->num_keys - 1] = NULL;
            n->keys[0] = neighbor->keys[neighbor->num_keys - 1];
            n->parent->keys[k_prime_index] = n->keys[0];
        }
    } else {
        if (n->is_leaf) {
            n->keys[n->num_keys] = neighbor->keys[0];
            n->pointers[n->num_keys] = neighbor->pointers[0];
            n->parent->keys[k_prime_index] = neighbor->keys[1];
        } else {
            n->keys[n->num_keys] = k_prime;
            n->pointers[n->num_keys + 1] = neighbor->pointers[0];
            tmp = (Node *)n->pointers[n->num_keys + 1];
            tmp->parent = n;
            n->parent->keys[k_prime_index] = neighbor->keys[0];
        }
        for (i = 0; i < neighbor->num_keys; i++) {
            neighbor->keys[i] = neighbor->keys[i + 1];
            neighbor->pointers[i] = neighbor->pointers[i + 1];
        }
        if (!n->is_leaf) neighbor->pointers[i] = neighbor->pointers[i + 1];
    }

    n->num_keys++;
    neighbor->num_keys--;

    return root;
}

Node * DeleteEntry(Node * root, Node * n, int key, void * pointer)
{

    int min_keys;
    Node * neighbor;
    int neighbor_index;
    int k_prime_index, k_prime;
    int capacity;

    n = RemoveFromNode(n, key, pointer);

    if (n == root) return NewRoot(root);

    min_keys = n->is_leaf ? Middle(ORDER - 1) : Middle(ORDER) - 1;

    if (n->num_keys >= min_keys) return root;

    neighbor_index = Neighbor(n);
    k_prime_index = neighbor_index == -1 ? 0 : neighbor_index;
    k_prime = n->parent->keys[k_prime_index];
    neighbor = neighbor_index == -1 ? n->parent->pointers[1] :
    n->parent->pointers[neighbor_index];

    capacity = n->is_leaf ? ORDER : ORDER - 1;

    if (neighbor->num_keys + n->num_keys < capacity) {
        return JoinNodes(root, n, neighbor, neighbor_index, k_prime);
    } else {
        return BalanceNodes(root, n, neighbor, neighbor_index, k_prime_index, k_prime);
    }
}

Node * Delete(Node * root, int key)
{
    Node * key_leaf;
    Record * key_record;

    key_record = Find(root, key);
    key_leaf = FindLeaf(root, key);
    if (key_record != NULL && key_leaf != NULL) {
        root = DeleteEntry(root, key_leaf, key, key_record);
        free(key_record);
    }
    return root;
}
