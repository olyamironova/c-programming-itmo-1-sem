#include "linkedlist.h"

void LinkedList::push(int x, int y){
    Node* new_node = new Node(x, y, top);
    top = new_node;
    lenght++;
}

int* LinkedList::pop(){
    int* res = new int[2]{top->x, top->y};

    Node* temp = top;
    top = top->next;

    delete temp;
    lenght--;

    return res;
}