#include "number.h"
#include <iostream>

int2023_t from_int(int32_t number) {
    bool is_negative = true;
    if (number < 0) {
        is_negative = true;
    } else {
        is_negative = false;
    }
    number = abs(number);
    int2023_t result;
    int counter = 0;
    while (number != 0) {
        result.number2023_t[252 - counter] = number % 256;
        number = number / 256;
        ++counter;
    }
    if (is_negative) {
        return add_code(result);
    } else {
        return result;
    }
}

int2023_t add_code(const int2023_t& value) {
    int2023_t code;
    for (int i = 0; i < 253; ++i) {
        code.number2023_t[i] = ~value.number2023_t[i];
    }
    return code + from_int(1);
}

int2023_t from_string(const char* buff) {
    int2023_t result;
    std::basic_string<char>str = buff;
    int size = 0;
    while (buff[size] != '\0') {
        ++size;
    }
    bool is_negative;
    if (buff[0] == '-') {
        is_negative = true;
    }
    else {
        is_negative = false;
    }
    for (int i = is_negative; i < size; ++i) {
        int2023_t temp_digit = from_int((int)(buff[i] - '0'));
        result = result * from_int(10);
        result = result + temp_digit;
    }
    if (is_negative) {
        return add_code(result);
    }
    else {
        return result;
    }
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
    int ost = 0;
    for (int i = 252; i >= 0; --i) {
        int sum = lhs.number2023_t[i] + rhs.number2023_t[i] + ost;
        if (sum >= 256) {
            result.number2023_t[i] = sum % 256;
            ost = sum / 256;
        } else {
            result.number2023_t[i] = sum;
            ost = 0;
        }
    }
    return result;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    return lhs + add_code(rhs);
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t first_number = lhs;
    int2023_t second_number = rhs;
    int2023_t result = from_int(0);
    bool is_add_code = false;
    int remainder_for_multiplication = 0;
    int remainder_for_addition = 0;
    int current_result = 0;
    int current_sum = 0;
    if (first_number.number2023_t[0] >= 128) {
        is_add_code = !(is_add_code);
        first_number = add_code(first_number);
    }
    if (second_number.number2023_t[0] >= 128) {
        is_add_code = !(is_add_code);
        second_number = add_code(second_number);
    }
    for (int i = 252; i >= 0; --i) {
        for (int j = 252; j >= 0; --j) {
            current_result = first_number.number2023_t[j] * second_number.number2023_t[i] + remainder_for_multiplication;
            if (current_result >= 256) {
                remainder_for_multiplication = current_result / 256;
                current_result = current_result % 256;
            } else {
                remainder_for_multiplication = 0;
            }
            if (i - (252 - j) >= 0) {
                current_sum = result.number2023_t[i - (252 - j)] + current_result + remainder_for_addition;
            } else {
                result.number2023_t[i] = result.number2023_t[i];
            }
            if (current_sum > 255) {
                remainder_for_addition = 1;
                current_sum = current_sum % 256;
            } else {
                remainder_for_addition = 0;
            }
            if (i - (252 - j) >= 0) {
                result.number2023_t[i - (252 - j)] = current_sum;
            } else {
                result.number2023_t[i] = result.number2023_t[i];
            }
        }
    }
    if (is_add_code) {
        return add_code(result);
    } else {
        return result;
    }
}

bool operator>(const int2023_t& lhs, const int2023_t& rhs) {
    if ((lhs.number2023_t[0] >= 128) && (rhs.number2023_t[0] < 128)) {
        return false;
    }
    if ((lhs.number2023_t[0] < 128) && (rhs.number2023_t[0] >= 128)) {
        return true;
    }
    for (int i = 0; i < 253; ++i) {
        if (lhs.number2023_t[i] > rhs.number2023_t[i]) {
            return true;
        }
        else if (lhs.number2023_t[i] != rhs.number2023_t[i]) {
            return false;
        }
    }
    return false;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = 0; i < 253; ++i) {
        if (lhs.number2023_t[i] != rhs.number2023_t[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    return !(lhs == rhs);
}

bool operator<(const int2023_t& lhs, const int2023_t& rhs) {
    if ((lhs.number2023_t[0] >= 128) && (rhs.number2023_t[0] < 128)) {
        return true;
    }
    if ((lhs.number2023_t[0] < 128) && (rhs.number2023_t[0] >= 128)) {
        return false;
    }
    for (int i = 0; i < 253; ++i) {
        if (lhs.number2023_t[i] < rhs.number2023_t[i]) {
            return true;
        }
        else if (lhs.number2023_t[i] != rhs.number2023_t[i]) {
            return false;
        }
    }
    return false;
}

int2023_t division_by_two(const int2023_t& divisible) {
    int2023_t result;
    int remains = 0;
    for (int i = 0; i < 253; ++i) {
        int current = remains * 256 + divisible.number2023_t[i];
        result.number2023_t[i] = current / 2;
        remains = current % 2;
    }
    return result;
}
int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {

    if (rhs == from_int(0))
    {
        exit(EXIT_FAILURE);
    }

    int2023_t divisible = lhs;
    int2023_t divider = rhs;

    bool lhs_negative = (lhs.number2023_t[0] >= 128);
    bool rhs_negative = (rhs.number2023_t[0] >= 128);

    if (lhs_negative) {
        divisible = add_code(divisible);
    }
    if (rhs_negative) {
        divider = add_code(divider);
    }
    if (divisible < divider) {
        return from_int(0);
    }

    int2023_t result;
    int2023_t temp_divisible = divisible;
    int2023_t temp_divider = divider;
    int2023_t counter = from_int(1);

    while ((temp_divisible > divider) || (temp_divisible == divider)) {
        temp_divider = divider;
        counter = from_int(1);
        while ((temp_divisible > (temp_divider + temp_divider)) || (temp_divisible == (temp_divider + temp_divider)))
        {
            temp_divider = temp_divider + temp_divider;
            counter = counter + counter;
        }
        temp_divisible = temp_divisible - temp_divider;
        result = result + counter;
    }

    if ((lhs_negative && !rhs_negative) || (!lhs_negative && rhs_negative)) {
        result = add_code(result);
    }

    return result;
}


std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    for (int i = 0; i < 253; ++i) {
        stream << (int)value.number2023_t[i] << " ";
    }
    return stream;
}
