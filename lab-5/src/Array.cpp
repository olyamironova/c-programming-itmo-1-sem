#include <iostream>
#include <cstdint>
#include <cassert>

class Array {
public:
    static Array make_array(uint32_t x, uint32_t y, uint32_t z);
    ~Array();
    friend std::ostream& operator<<(std::ostream& os, const Array& arr);
    friend std::istream& operator>>(std::istream& is, Array& arr);
    Array operator*(int32_t scalar) const;
    Array operator+(const Array& other) const;
    Array operator-(const Array& other) const;

    // Array access operator
    class Access {
    public:
        Access operator[](uint32_t index) const;  // Marked as const
        uint32_t getValue() const;  // New method to get the value
        void setValue(uint32_t value);  // New method to set the value

    private:
        friend class Array;
        Access(uint32_t* data, uint32_t mask) : data_(data), mask_(mask) {}
        uint32_t* data_;
        uint32_t mask_;
    };

    Access operator[](uint32_t index) const;

private:
    Array(uint32_t x, uint32_t y, uint32_t z);

    uint32_t x_;
    uint32_t y_;
    uint32_t z_;
    uint32_t* data_;
    uint32_t xMask_;
    uint32_t yMask_;
    uint32_t zMask_;

    static const uint32_t size_of_elements = 17;
    static const uint32_t bits_in_uint32 = 32;
    static const uint32_t binary_mask = (1 << size_of_elements) - 1;

    static const uint32_t BLOCK_SIZE = bits_in_uint32 / size_of_elements;
};

Array::Array(uint32_t x, uint32_t y, uint32_t z)
        : x_(x), y_(y), z_(z), xMask_(binary_mask), yMask_(xMask_ << size_of_elements), zMask_(yMask_ << size_of_elements) {
    data_ = new uint32_t[x * y * z];
    // Additional initialization if needed
}

// Destructor to free allocated memory
Array::~Array() {
    delete[] data_;
}

Array Array::make_array(uint32_t x, uint32_t y, uint32_t z) {
    Array arr(x, y, z);
    return arr;
}

Array::Access Array::Access::operator[](uint32_t index) const {  // Marked as const
    return Access(data_ + index * mask_, mask_);
}

uint32_t Array::Access::getValue() const {
    return *data_;
}

void Array::Access::setValue(uint32_t value) {
    *data_ = value;
}

Array::Access Array::operator[](uint32_t index) const {  // Marked as const
    return Access(data_ + index * y_ * z_, yMask_);
}

// Overloaded operator<< for Array::Access
std::ostream& operator<<(std::ostream& os, const Array::Access& Access) {
    os << Access.getValue();
    return os;
}

// Overloaded operator>> for Array::Access
std::istream& operator>>(std::istream& is, Array::Access& Access) {
    uint32_t value;
    is >> value;
    // Update the underlying data with the new value
    Access.setValue(value);
    return is;
}
