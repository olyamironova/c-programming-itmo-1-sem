#include "Hamming.h"

size_t CountControlBits(size_t len) {
    size_t counter = 1;
    while ((1 << counter) < len + counter + 1) {
        ++counter;
    }
    return counter;
}

std::vector<char> EncodeHam(const std::vector<char>& array) {
    std::vector<char> temp;
    for (unsigned char i : array) {
        temp.push_back(0);
    }
    size_t count_control = CountControlBits(array.size() * kByte);

    size_t current = 0;
    for (size_t i = 0; i < (array.size() * kByte) + count_control; ++i) {
        if (i / kByte >= temp.size()) {
            temp.push_back(0);
        }
        if (!((i + 1) & i)) {
            temp[i / kByte] &= ~(1 << (7 - i % kByte));
        } else {
            temp[i / kByte] |= ((array[current / kByte] >> (7 - current % kByte)) & 1) << (7 - i % kByte);
            ++current;
        }
    }

    for (size_t i = 0; i < count_control; ++i) {
        size_t sum = 0;
        for (size_t j = 1 << i; j < temp.size() * kByte; ++j) {
            if ((j + 1) & (1 << i)) {
                sum ^= (temp[j / kByte] >> (7 - j % kByte)) & 1;
            }
        }
        temp[((1 << i) - 1) / kByte] |= (sum << (7 - ((1 << i) - 1) % kByte));
    }

    return temp;
}

std::vector<char> DecodeHam(const std::vector<char>& array) {
    std::vector<uint8_t> temp_arr;
    size_t wrong_bit = 0;
    uint8_t control_bit = CountControlBits(array.size() * kByte);

    for (unsigned char i : array) {
        temp_arr.push_back(i);
    }

    for (size_t i = 0; i < control_bit; ++i) {
        size_t sum = 0;
        for (size_t j = 1 << i; j < temp_arr.size() * kByte; ++j) {
            if ((j + 1) & (1 << i)) {
                sum ^= (temp_arr[j / kByte] >> (7 - j % kByte)) & 1;
            }
        }
        if (sum != ((temp_arr[((1 << i) - 1) / kByte] >> (7 - ((1 << i) - 1) % kByte)) & 1)) {
            wrong_bit += 1 << i;
        }
    }
    if (wrong_bit) {
        --wrong_bit;
        temp_arr[wrong_bit / kByte] ^= (1 << (7 - wrong_bit % kByte));
    }

    std::vector<uint8_t> temp_res((array.size() * kByte - control_bit - (kByte - control_bit)) / kByte, 0);
    size_t current = 0;
    for (size_t i = 0; i < (array.size() * kByte) - (kByte - control_bit); ++i) {
        if (((i + 1) & i)) {
            temp_res[current / kByte] |= ((temp_arr[i / kByte] >> (7 - i % kByte)) & 1) << (7 - current % kByte);
            ++current;
        }
    }

    std::vector<char> result(temp_res.begin(), temp_res.end());
    return result;
}



