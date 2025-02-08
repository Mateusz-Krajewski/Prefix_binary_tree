/**
 * @file lib.h
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SRC_SORTED_LIST_LIB_H_
#define SRC_SORTED_LIST_LIB_H_

#include <stdlib.h>
#include <string.h>

#define INCREASE_SIZE 500

typedef struct {
    unsigned int base;
    char mask;
} data_t;

int data_lenght = 0;
int capacity = INCREASE_SIZE;
data_t *data = NULL;

unsigned int lookup_table_netmask[] = {
    0x00000000, 0x80000000, 0xC0000000, 0xE0000000, 0xF0000000, 0xF8000000, 0xFC000000, 0xFE000000,
    0xFF000000, 0xFF800000, 0xFFC00000, 0xFFE00000, 0xFFF00000, 0xFFF80000, 0xFFFC0000, 0xFFFE0000,
    0xFFFF0000, 0xFFFF8000, 0xFFFFC000, 0xFFFFE000, 0xFFFFF000, 0xFFFFF800, 0xFFFFFC00, 0xFFFFFE00,
    0xFFFFFF00, 0xFFFFFF80, 0xFFFFFFC0, 0xFFFFFFE0, 0xFFFFFFF0, 0xFFFFFFF8, 0xFFFFFFFC, 0xFFFFFFFE,
    0xFFFFFFFF
};

int resize_data(int increase_capacity) {
    capacity += increase_capacity;
    data_t *new_data = (data_t *)realloc(data, capacity * sizeof(data_t));
    if (new_data == NULL) {
        return -1;
    }
    data = new_data;
    return 0;
}
void init_data() {
    if (data == NULL) {
        data = (data_t *)malloc(capacity * sizeof(data_t));
    }
}

int add(unsigned int base, char mask) {
    init_data();
    for (int i = 0; i < data_lenght; i++) {
        if (data[i].base == base && data[i].mask == mask) {
            return -1;
        }
        if (data[i].mask < mask) {
            break;
        }
    }
    if (data_lenght >= capacity) {
        if (resize_data(INCREASE_SIZE) == -1) {
            return -1;
        }
    }

    int pos = data_lenght;
    while (pos > 0 && data[pos - 1].mask < mask) {
        data[pos] = data[pos - 1];
        pos -= 1;
    }
    data[pos].mask = mask;
    data[pos].base = base;
    data_lenght += 1;
    return 0;
}
int del(unsigned int base, char mask) {
    for (int i = 0; i < data_lenght; i++) {
        if (data[i].base == base && data[i].mask == mask) {
            data[i] = data[data_lenght-1];
            data_lenght -= 1;
            return 0;
        }
        if (data[i].mask < mask) {
            return -1;
        }
    }
    return -1;
}

char check_ip(unsigned int base, char mask, unsigned int ip) {
    unsigned int netmask = lookup_table_netmask[mask];
    if ((ip & netmask) == (base & netmask)) {
        return 0;
    }
    return -1;
}

char check(unsigned int ip) {
    for (int i =0; i < data_lenght; i++) {
        if (check_ip(data[i].base, data[i].mask, ip) == 0) {
            return data[i].mask;
        }
    }
    return -1;
}

#endif  // SRC_SORTED_LIST_LIB_H_
