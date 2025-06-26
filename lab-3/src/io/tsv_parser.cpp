#include <cstdint>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "sandpile.h"
#include "tsv_parser.h"

int* DefinitionSize(const std::string& file_name) {
    std::string line;
    int* temporary_coordinates = new int[2]{INT_MIN, INT_MIN};
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Couldn't open the file");
    }
    std::string str;
    while (std::getline(file, str)) {
        int x = std::atoi(str.substr(0, str.find('\t')).c_str());
        int y = std::atoi(str.substr(str.find('\t') +  1).c_str());
        temporary_coordinates[0] = std::max(temporary_coordinates[0], x);
        temporary_coordinates[1] = std::max(temporary_coordinates[1], y);
    }
    file.close();
    return temporary_coordinates;
}

void FillingTheCells(const std::string& file_name, Sandpile& sandpile) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Couldn't open the file");
    }
    std::string str;
    while (std::getline(file, str)) {
        int x = std::atoi(str.substr(0, str.find('\t')).c_str());
        int y = std::atoi(str.substr(str.find('\t') + 1, str.find('\t', str.find('\t') + 1) - str.find('\t') - 1).c_str());
        uint64_t grains = std::atoi(str.substr(str.find('\t', str.find('\t') + 1) + 1).c_str());
        if ((x < 0) || (y < 0)) {
            throw std::invalid_argument("The coordinates can't be negative.");
        }
        sandpile.grid[y - 1][x - 1] = grains;
    }
}