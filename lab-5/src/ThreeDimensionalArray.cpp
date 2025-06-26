#include "ThreeDimensionalArray.h"

OneDimensionalArray::OneDimensionalArray(size_t size, size_t depth, size_t index, uint16_t* data, uint8_t* extra_bits)
	: size_(size)
	, depth_(depth)
	, index_(index)
	, data_(data)
	, extra_bits_(extra_bits)
{}
WrapperArray::WrapperArray(size_t size, size_t depth, size_t index, uint16_t* data, uint8_t* extra_bits)
	: size_(size)
	, depth_(depth)
	, index_(index)
	, data_(data)
	, extra_bits_(extra_bits)
{}

WrapperArray OneDimensionalArray::operator[](size_t index) const {
    return WrapperArray(size_, depth_, index_ + index, data_, extra_bits_);
}

WrapperArray& WrapperArray::operator=(int value) {
    assert(0 <= index_ && index_ < size_);
    extra_bits_[index_ / 8] &= ~(1 << (index_ % 8));
    data_[index_] = value & 0xFFFF;
	extra_bits_[index_ / 8] |= ((value & 1 << 16) >> 16) << (index_ % 8);
	return *this;
}

WrapperArray::operator int() const {
	assert(0 <= index_ && index_ < size_);
	int result = data_[index_] | (((extra_bits_[index_ / 8] & (1 << index_ % 8)) >> (index_ % 8)) << 16);
	return result;
}

ThreeDimensionalArray ThreeDimensionalArray::make_array(size_t height, size_t width, size_t depth) {
	return ThreeDimensionalArray(height, width, depth);
}

ThreeDimensionalArray::ThreeDimensionalArray(size_t width, size_t height, size_t depth)
	: width_(width)
	, height_(height)
	, depth_(depth)
	, data_(new uint16_t[width * height * depth])
	, extra_bits_(new uint8_t[width * height * depth / 8 + 1])
	, size_(width * height * depth)
{}

TwoDimensionalArray::TwoDimensionalArray(size_t size, size_t height, size_t depth, size_t index, uint16_t* data, uint8_t* data_extra_bits)
	: height_(height)
	, depth_(depth)
	, size_(size)
	, index_(index)
	, data_(data)
	, extra_bits_(data_extra_bits)
{}

OneDimensionalArray TwoDimensionalArray::operator[](size_t index) const {
	return OneDimensionalArray(size_, depth_, index_ + index * height_, data_, extra_bits_);
}

TwoDimensionalArray ThreeDimensionalArray::operator[](size_t index) const {
	assert(0 <= index && index < width_);
	return TwoDimensionalArray(size_, height_, depth_, index * width_ * height_, data_, extra_bits_);
}

ThreeDimensionalArray::ThreeDimensionalArray(const ThreeDimensionalArray& other)
    : height_(other.height_)
    , width_(other.width_)
    , depth_(other.depth_)
    , size_(other.size_)
    , data_(new uint16_t[other.size_])
    , extra_bits_(new uint8_t[other.size_ / 8 + 1])
{
    for (size_t i = 0; i < other.size_; ++i) {
        data_[i] = other.data_[i];
    }
    for (size_t i = 0; i < other.size_ / 8 + 1; ++i) {
        extra_bits_[i] = other.extra_bits_[i];
    }
}

ThreeDimensionalArray& ThreeDimensionalArray::operator=(const ThreeDimensionalArray& other) {
    if (this != &other) {
        delete[] data_;
        delete[] extra_bits_;
        height_ = other.height_;
        width_ = other.width_;
        depth_ = other.depth_;
        size_ = other.size_;
        data_ = new uint16_t[other.size_];
        extra_bits_ = new uint8_t[other.size_ / 8 + 1];
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
        for (size_t i = 0; i < other.size_ / 8 + 1; ++i) {
            extra_bits_[i] = other.extra_bits_[i];
        }
    }
    return *this;
}

size_t ThreeDimensionalArray::GetHeight() const {
	return height_;
}

size_t ThreeDimensionalArray::GetWidth() const {
	return width_;
}

size_t ThreeDimensionalArray::GetDepth() const {
	return depth_;
}

ThreeDimensionalArray::~ThreeDimensionalArray() {
	delete[] data_;
	delete[] extra_bits_;
}

std::istream& operator>>(std::istream& in, WrapperArray array) {
    int value;
    in >> value;
    array = value;
    return in;
}

ThreeDimensionalArray operator+(const ThreeDimensionalArray& array1, const ThreeDimensionalArray& array2) {
    assert(array1.GetWidth() == array2.GetWidth() && array1.GetHeight() == array2.GetHeight() && array1.GetDepth() == array2.GetDepth());
    ThreeDimensionalArray result(array1.GetWidth(), array1.GetHeight(), array1.GetDepth());
    for (int i = 0; i < array1.GetWidth(); ++i) {
        for (int j = 0; j < array1.GetHeight(); ++j) {
            for (int k = 0; k < array1.GetDepth(); ++k) {
                result[i][j][k] = array1[i][j][k] + array2[i][j][k];
            }
        }
    }
    return result;
}

ThreeDimensionalArray operator-(const ThreeDimensionalArray& array1, const ThreeDimensionalArray& array2) {
    assert(array1.GetWidth() == array2.GetWidth() && array1.GetHeight() == array2.GetHeight() && array1.GetDepth() == array2.GetDepth());
    ThreeDimensionalArray result(array1.GetWidth(), array1.GetHeight(), array1.GetDepth());
    for (int i = 0; i < array1.GetWidth(); ++i) {
        for (int j = 0; j < array1.GetHeight(); ++j) {
            for (int k = 0; k < array1.GetDepth(); ++k) {
                result[i][j][k] = array2[i][j][k] - array1[i][j][k];
            }
        }
    }
    return result;
}

ThreeDimensionalArray operator*(const ThreeDimensionalArray& array, int number) {
    ThreeDimensionalArray result(array.GetWidth(), array.GetHeight(), array.GetDepth());
    for (int i = 0; i < array.GetWidth(); ++i) {
        for (int j = 0; j < array.GetHeight(); ++j) {
            for (int k = 0; k < array.GetHeight(); ++k) {
                result[i][j][k] = array[i][j][k] * number;
            }
        }
    }
    return result;
}

ThreeDimensionalArray operator*(int number, const ThreeDimensionalArray& array) {
    return array * number;
}

std::ostream& operator<<(std::ostream& os, const ThreeDimensionalArray& array) {
	for (int i = 0; i < array.GetWidth(); ++i) {
		for (int j = 0; j < array.GetHeight(); ++j) {
			for (int k = 0; k < array.GetDepth(); ++k) {
				os << array[i][j][k] << " ";
			}
			os << '\n';
		}
	}
	return os;
}

std::istream& operator>>(std::istream& in, ThreeDimensionalArray& array) {
	for (int i = 0; i < array.GetWidth(); ++i) {
		for (int j = 0; j < array.GetHeight(); ++j) {
			for (int k = 0; k < array.GetDepth(); ++k) {
				in >> array[i][j][k];
			}
		}
	}
	return in;
}