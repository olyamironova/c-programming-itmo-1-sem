#pragma once

#include <cstdint>

struct Node {
    int x;
    int y;
    Node* next;

    Node(int x, int y, Node* next=nullptr){
        this->x = x;
        this->y = y;
        this->next = next;
    }

};

struct LinkedList {
    Node* top = nullptr;
    uint64_t lenght = 0;


    int* pop();
    void push(int x, int y);
};
