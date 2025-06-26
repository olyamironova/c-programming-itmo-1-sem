#include <iostream>
#include "ThreeDimensionalArray.h"
void FillArray(ThreeDimensionalArray& array, int number) {
    for (int i = 0; i < array.GetWidth(); ++i) {
        for (int j = 0; j < array.GetHeight(); ++j) {
            for (int k = 0; k < array.GetDepth(); ++k) {
                array[i][j][k] = number;
            }
        }
    }
}

int main() {
    ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(10, 10, 10);
    FillArray(arr, 10);
    arr[0][0][0] = 1;
    std::cout << arr[0][0][0] << '\n';
    return 0;
}