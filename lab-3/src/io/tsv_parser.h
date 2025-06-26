#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include "sandpile.h"

int* DefinitionSize(const std::string& file_name);
void FillingTheCells(const std::string& file_name, Sandpile& sandpile);