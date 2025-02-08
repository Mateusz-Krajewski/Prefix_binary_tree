/**
 * @file main.cc
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "lib.h"
void print_result(const char* test_name, int result) {
    printf("%s: %s\n", test_name, result == 0 ? "PASSED" : "FAILED");
}

int main() {
    printf("Testowanie funkcji drzewa binarnego:\n");

    int result = add(0xC0A80000, 24);  //  192.168.0.0/24
    print_result("Dodawanie podsieci 192.168.0.0/24", result);

    Node* found = search(node, 0xC0A80001);  // 192.168.0.1
    if (found != NULL && (found->value >> 2) == 24) {
        print_result("Wyszukiwanie 192.168.0.1", 0);
    } else {
        print_result("Wyszukiwanie 192.168.0.1", -1);
    }
    found = search(node, 0xC1A80001);  // 193.168.0.1
    if (found != NULL && (found->value >> 2) == 24) {
        print_result("Wyszukiwanie 193.168.0.1", -1);
    } else {
        print_result("Wyszukiwanie 193.168.0.1", 0);
    }

    result = del(0xC0A80000, 24);  // 192.168.0.0/24
    print_result("Usuwanie podsieci 192.168.0.0/24", result);

    found = search(node, 0xC0A80001);  //  192.168.0.1
    if (found == NULL) {
        print_result("Wyszukiwanie 192.168.0.1 po usunięciu", 0);
    } else {
        print_result("Wyszukiwanie 192.168.0.1 po usunięciu", -1);
    }

    drop_trie(node);

    printf("Testowanie zakończone.\n");
    return 0;
}