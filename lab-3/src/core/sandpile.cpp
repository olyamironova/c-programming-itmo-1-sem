#include "sandpile.h"
#include "linkedlist.h"
#include <iostream>




Sandpile::Sandpile(int width, int height) : width(width), height(height) {
    grid = new uint64_t*[height];
    for (int i = 0; i < height; ++i) {
        grid[i] = new uint64_t[width]();
    }
}

Sandpile::~Sandpile() {
    for (int i =  0; i < height; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}



bool Sandpile::NecessaryInExpansion(Sandpile& sandpile) {
    bool necessary = false;
    for (int y = 0; y < sandpile.height; ++y) {
        for (int x = 0; x < sandpile.width; ++x) {
            if (sandpile.grid[y][x] > 3) {
                necessary = true;
                break;
            }
        }
    }
    return necessary;
}

void Sandpile::CollectionOverflowCellsInOneIteration(const Sandpile& sandpile, LinkedList& list) {
    for (int y = 0; y < sandpile.height; ++y) {
        for (int x = 0; x < sandpile.width; ++x) {
            if (sandpile.grid[y][x] > 3) {
                list.push(x, y);
            }
        }
    }
}

void Sandpile::LinkedListProcessing(Sandpile& sandpile, LinkedList& changes) {
    uint64_t size = changes.lenght;
    for (uint64_t i = 0; i < size; ++i) {
        int *current = changes.pop();
        sandpile.grid[current[1]][current[0]] -= 4;

        sandpile.grid[current[1] - 1][current[0]]++;

        sandpile.grid[current[1] + 1][current[0]]++;

        sandpile.grid[current[1]][current[0] - 1]++;

        sandpile.grid[current[1]][current[0] + 1]++;

        delete[] current;
    }
}

void Sandpile::Expansion(Sandpile &sandpile) {
    bool left = false;
    bool right = false;
    bool top = false;
    bool bottom = false;

    for (int x =  0; x < sandpile.width; ++x) {
        if (sandpile.grid[0][x] > 3) {
            top = true;
            break;
        }
    }

    for (int x =  0; x < sandpile.width; ++x) {
        if (sandpile.grid[sandpile.height - 1][x] > 3) {
            bottom = true;
            break;
        }
    }

    for (int y =  0; y < sandpile.height; ++y) {
        if (sandpile.grid[y][0] > 3) {
            left = true;
            break;
        }
    }

    for (int y = 0; y < sandpile.height; ++y) {
        if (sandpile.grid[y][sandpile.width - 1] > 3) {
            right = true;
            break;
        }
    }

    if (!top && !bottom && !left && !right) {
        return;
    }

    uint64_t** new_table = new uint64_t*[sandpile.height + top + bottom];
    for (int y = 0; y < sandpile.height + top + bottom; ++y) {
        new_table[y] = new uint64_t[sandpile.width + left + right]{0};
    }

    for (int y = 0; y < sandpile.height; ++y) {
        for (int x = 0; x < sandpile.width; ++x) {
            new_table[y + top][x + left] = sandpile.grid[y][x];
        }
    }

    for (int y = 0; y < sandpile.height; ++y) {
        delete[] sandpile.grid[y];
    }
    delete[] sandpile.grid;

    sandpile.width += left + right;
    sandpile.height += top + bottom;
    sandpile.grid = new_table;
}