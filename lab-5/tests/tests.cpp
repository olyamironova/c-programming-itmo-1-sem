#include <ThreeDimensionalArray.h>
#include <gtest/gtest.h>
#include <string>

void FillArray(ThreeDimensionalArray& array, int number) {
	for (int i = 0; i < array.GetWidth(); ++i) {
		for (int j = 0; j < array.GetHeight(); ++j) {
			for (int k = 0; k < array.GetDepth(); ++k) {
				array[i][j][k] = number;
			}
		}
	}
}

void ValidValue(ThreeDimensionalArray& array, int value) {
	for (int i = 0; i < array.GetWidth(); ++i) {
		for (int j = 0; j < array.GetHeight(); ++j) {
			for (int k = 0; k < array.GetDepth(); ++k) {
				EXPECT_EQ(array[i][j][k], value);
			}
		}
	}
}

TEST(ArrayTests, FillArray) {
	ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(10, 10, 10);

	FillArray(arr1, 10);

	ValidValue(arr1, 10);
}

TEST(ArrayTests, Addition) {
	ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(12, 12, 12);
	ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(12, 12, 12);

	FillArray(arr1, 10);
	FillArray(arr2, 10);

	ThreeDimensionalArray arr3 = arr1 + arr2;

	ValidValue(arr3, 20);
}

TEST(ArrayTests, Subtraction) {
	ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(12, 12, 12);
	ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(12, 12, 12);

	FillArray(arr1, 10);
	FillArray(arr2, 10);

	ThreeDimensionalArray arr3 = arr1 - arr2;

	ValidValue(arr3, 0);
}

TEST(ArrayTests, Multiplication) {
	ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(12, 12, 12);

	FillArray(arr1, 10);

	ThreeDimensionalArray arr3 = arr1 * 3;

	ValidValue(arr3, 30);
}

TEST(ArrayTests, DifferentSizes) {
	ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(12, 12, 12);
	ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(11, 11, 11);

	FillArray(arr1, 10);
	FillArray(arr2, 11);

	ThreeDimensionalArray arr3 = arr1 + arr2;
}

TEST(ArrayTests, CopyArray) {
	ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(12, 12, 12);
	FillArray(arr1, 10);

	ThreeDimensionalArray arr2 = arr1;

	arr2[0][1][2] = 3;

	ASSERT_TRUE(arr2[0][1][2] != arr1[0][1][2]);
}

TEST(ArrayTests, OperatorOutputInputArray) {
	ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(2, 2, 2);
	std::cout << "Array size 2x2x2\n";

	std::string output = "1 1 1 1 1 1 1 1";
	std::istringstream in(output);
	in >> arr1;

	std::ostringstream os;
	os << arr1;
}
