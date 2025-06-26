#pragma once

#include <iostream>
#include <cstdint>
#include <cassert>
#include <cstring>


class WrapperArray {
public:
    WrapperArray(size_t size, size_t depth, size_t index, uint16_t* array, uint8_t* extra_bits);
    operator int() const;
    WrapperArray& operator=(int value);
    friend std::istream& operator>>(std::istream& in, WrapperArray& array);

private:
    size_t depth_;
    size_t size_;
    size_t index_;
    uint16_t* data_;
    uint8_t* extra_bits_;
};

class OneDimensionalArray {
public:
    OneDimensionalArray(size_t size, size_t depth, size_t index, uint16_t* array, uint8_t* extra_bits);
    WrapperArray operator[](size_t index) const;

private:
    size_t depth_;
    size_t size_;
    size_t index_;
    uint16_t* data_;
    uint8_t* extra_bits_;
};

class TwoDimensionalArray {
public:
    TwoDimensionalArray(size_t size, size_t height, size_t depth, size_t index, uint16_t* array, uint8_t* data_extra_bitt);
    OneDimensionalArray operator[](size_t index) const;

private:
    int height_;
    int depth_;
    int size_;
    int index_;
    uint16_t* data_;
    uint8_t* extra_bits_;
};

class ThreeDimensionalArray {
public:
    static ThreeDimensionalArray make_array(size_t height, size_t width, size_t depth);

    ThreeDimensionalArray(size_t height, size_t width, size_t depth);
    ThreeDimensionalArray(const ThreeDimensionalArray& other);
    ~ThreeDimensionalArray();

    ThreeDimensionalArray& operator=(const ThreeDimensionalArray& other);
    friend std::istream& operator>>(std::istream& in, ThreeDimensionalArray& array);
    friend std::ostream& operator<<(std::ostream& os, const ThreeDimensionalArray& array);
    TwoDimensionalArray operator[](size_t index) const;

    size_t GetHeight() const;
    size_t GetWidth() const;
    size_t GetDepth() const;

private:
    uint16_t* data_;
    uint8_t* extra_bits_;
    size_t height_;
    size_t depth_;
    size_t size_;
    size_t width_;
};

ThreeDimensionalArray operator+(const ThreeDimensionalArray& array1, const ThreeDimensionalArray& array2);

ThreeDimensionalArray operator-(const ThreeDimensionalArray& array1, const ThreeDimensionalArray& array2);

ThreeDimensionalArray operator*(const ThreeDimensionalArray& array, int number);

ThreeDimensionalArray operator*(int number, const ThreeDimensionalArray& array);
