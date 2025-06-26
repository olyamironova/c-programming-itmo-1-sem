#pragma once
#include <cstdint>
#include <string>
#include "linkedlist.h"

class Sandpile {
public:
    uint64_t** grid;
    int height;
    int width;

    Sandpile(int width, int height);
    ~Sandpile();

    static bool NecessaryInExpansion(Sandpile& sandpile);
    static void CollectionOverflowCellsInOneIteration(const Sandpile& sandpile, LinkedList& list);
    static void LinkedListProcessing(Sandpile& sandpile, LinkedList& changes);
    static void Expansion(Sandpile &sandpile);
    static void FillindTheCells(const std::string& file_name, Sandpile& sandpile);
    static int* DefinitionSize(const std::string& file_name);
};



