/**
 * @file lib.h
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SRC_BINARY_TREE_LIB_H_
#define SRC_BINARY_TREE_LIB_H_

#include <stdio.h>
#include <stdlib.h>


unsigned int lookup_table_netmask[] = {
    0x00000000, 0x80000000, 0xC0000000, 0xE0000000, 0xF0000000, 0xF8000000, 0xFC000000, 0xFE000000,
    0xFF000000, 0xFF800000, 0xFFC00000, 0xFFE00000, 0xFFF00000, 0xFFF80000, 0xFFFC0000, 0xFFFE0000,
    0xFFFF0000, 0xFFFF8000, 0xFFFFC000, 0xFFFFE000, 0xFFFFF000, 0xFFFFF800, 0xFFFFFC00, 0xFFFFFE00,
    0xFFFFFF00, 0xFFFFFF80, 0xFFFFFFC0, 0xFFFFFFE0, 0xFFFFFFF0, 0xFFFFFFF8, 0xFFFFFFFC, 0xFFFFFFFE,
    0xFFFFFFFF
};

struct Node {
    unsigned char value;  // 6 MSB - mask, 1 LSB - value
    struct Node *zero;
    struct Node *one;
    struct Node *parent;
    char needed_prefix;  // END of prefix
};

Node *node;

Node* createNode(Node* parent, unsigned char data, unsigned char mask = 0) {
    Node* node = (Node*)malloc(sizeof(Node));  // NOLINT
    node->value = data | mask << 2;
    node->zero = NULL;
    node->one = NULL;
    node->parent = parent;
    node->needed_prefix = 0;
    return node;
}

int insert(Node** root, unsigned int base, char mask) {
    int network = base & lookup_table_netmask[(unsigned char)mask];
    if (*root == NULL) {
        *root = createNode(NULL, 0, 0);
    }
    Node* current = *root;
    for (int i = 31; i >= 32 - mask; i--) {
        if ((network >> i) & 1) {  // bit 1
            if (current->one == NULL) {
                current->one = createNode(current, 1, 32 - i);
            }
            current = current->one;
        } else {  // bit 0
            if (current->zero == NULL) {
                current->zero = createNode(current, 0, 32 - i);
            }
            current = current->zero;
        }
    }
    if (current->needed_prefix) {
        return -1;
    }
    current->needed_prefix = 1;
    return 0;
}


Node* search(Node* root, unsigned int data) {
    if (root == NULL) {
        return NULL;
    }
    int i = 31;
    Node* current = root;
    Node* last_match = NULL;
    while (i >= 0 && current != NULL) {
        int val = (data >> i) & 1;
        if (current->needed_prefix) {
            last_match = current;
        }
        if (val) {
            current = current->one;
        } else {
            current = current->zero;
        }
        i--;
    }
    return last_match;
}

void drop_trie(Node* root) {
    if (root == nullptr) {
        return;
    }
    drop_trie(root->zero);
    drop_trie(root->one);
    free(root);
}

int add(unsigned int base, char mask) {
    return insert(&node, base, mask);
}
int del(unsigned int base, char mask) {
    if (node == NULL) {
        return -1;
    }
    int network = base & lookup_table_netmask[(unsigned char)mask];
    Node* current = node;
    for (int i = 31; i >= 32 - mask && current != NULL; i--) {
        if ((network >> i) & 1) {  // bit 1
            current = current->one;
        } else {  // bit 0
            current = current->zero;
        }
    }
    if (current == NULL || !current->needed_prefix) {
        return -1;
    }
    current->needed_prefix = 0;
    while (current->parent != NULL && current->zero == NULL && current->one == NULL && !current->needed_prefix) {
        Node* parent = current->parent;
        if (parent->zero == current) {
            parent->zero = NULL;
        } else if (parent->one == current) {
            parent->one = NULL;
        }
        free(current);
        current = parent;
    }
    return 0;
}


char check(unsigned int ip) {
    Node* val = search(node, ip);
    if (val == NULL) {
        return -1;
    }
    char res = (val->value >> 2);
    if (res == 0) {
        return -1;
    }
    return res;
}

#endif  // SRC_BINARY_TREE_LIB_H_
