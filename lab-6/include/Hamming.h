#pragma once

#include "string"
#include "iostream"
#include "cstdint"
#include "vector"
#include "bitset"

const int kByte = 8;

std::vector<char> EncodeHam(const std::vector<char>& array);

std::vector<char> DecodeHam(const std::vector<char>& array);

int CountControlBits(int len);