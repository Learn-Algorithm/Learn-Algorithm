#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"b+tree.h"

int _get_index_in_parent(Node* node) {
    int i;
    Node* p = node->parent;
    int count = p->count;
    for (i = 0; i < count; i++) {
        if(p->children[i] == node)
            return i;
    }
	return -1;
}

int _insert(int item, int **k, int count) {
    int *keys;
	int i;
    for (i = 0; i < count; i++) {
        if ((*k)[i] == item)
            return 0;
        if ((*k)[i] > item) {
            keys = (int *)calloc(count+1, sizeof(int));
            memcpy(keys, *k, sizeof(int)*i);
            keys[i] = item;
            memcpy(keys+i+1, *k+i+1, sizeof(int)*(count-i));
            free(*k);
            *k = keys;
            return 0;
        }
    }
    return -1;
}

/*
 *insert node into leaf's parent
 */
void _insert2parent(Node* leaf, Node* node) {
    Node **children;
    int index;
    Node * parent = leaf->parent;
    int count = parent->count;

    index = _get_index_in_parent(leaf);
    children = (Node**)calloc(count + 1, sizeof(Node*));
    memcpy(children, parent->children,  sizeof(Node*) * (index+1) );
    children[index+1] = node;
    memcpy(children+index+1+1, parent->children+index+1, count-index-1);
    free(parent->children);
    parent->children = children;
    
    _insert(leaf->keys[leaf->count-1], &parent->keys, parent->count);
	parent->count += 1;
}

void _split(Node* lleaf, BPtree*tree) {
    int i;
	int frends_count = 0;
    Node* new_parent, *tmp;

    int count = lleaf->count;

	//new node has half of orignal keys
    int half = count/2;
    Node* node = (Node*)calloc(1,sizeof(Node));
    node->keys = (int*)calloc(half, sizeof(int));
    node->count = half;
    node->next = lleaf->next;
    node->prev = lleaf;
    node->parent = lleaf->parent;

    for (i = 0; i < half; i++) {
        node->keys[i] = lleaf->keys[i+half];
    }

    lleaf->next = node;
	//just set count is ok
    lleaf->count = lleaf->count-half;

    if (lleaf->parent != NULL) {
        _insert2parent(lleaf, node);
        if (lleaf->parent->count > tree->m) 
			_split(lleaf->parent, tree);
    } else {
        new_parent = (Node*)calloc(1, sizeof(Node));
		tmp = lleaf;
		while(tmp != NULL) {
			frends_count += 1;
			tmp = tmp->next;
		}

        new_parent->count = frends_count;
        new_parent->children = (Node**)calloc(frends_count, sizeof(Node*));
        new_parent->keys = (int*)calloc(frends_count, sizeof(int));
		tmp = lleaf;
		i = 0;
		while(tmp != NULL) {
			new_parent->children[i] = tmp;
			tmp->parent = new_parent;
			tmp = tmp->next;
			i+=1;
		}
        tmp = lleaf;
		i = 0;
		while (tmp != NULL) {
			new_parent->keys[i] = tmp->keys[tmp->count - 1];
			i+=1;
			tmp = tmp->next;
		}
        tree->root = new_parent;
    }
}

void _append(int item, int **k, int count) {
	int real = count + 1;
    int * keys = (int*)calloc(real, sizeof(int));
    memcpy(keys, *k, sizeof(int)*count);
    keys[count] = item;
	if (*k != NULL)
		free(*k);
    *k = keys;
}

int insert(int item, BPtree* tree) {
    int min;
	int count;
	int index;
    Node * lleaf;
    lleaf = tree->lleaf;
    count = lleaf->count;

    if (tree->m%2 != 0)
        min = tree->m/2+1;

    while(1) {
		//TODO:this is a liner insert, change 2 tree insert
        if (_insert(item, &lleaf->keys, count) == 0) {
            lleaf->count+=1;
            break;
        }
		
		if (lleaf->next == NULL) {
			_append(item, &lleaf->keys, count);
			lleaf->count+=1;   
			if (lleaf->parent != NULL) {
				//update the max value in parent
				index = _get_index_in_parent(lleaf);
				lleaf->parent->keys[index] = item;
			}
			break;
		}
		lleaf = lleaf->next;

    }

    if (lleaf->count > tree->m) {
        _split(lleaf, tree);
    } else if(lleaf->count < min) {
        assert(lleaf == tree->root);
    }

    return 0;
}