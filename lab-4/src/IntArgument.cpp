#include "IntArgument.h"
IntArgument& IntArgument::Default(int default_value) {
	int_argument_value = default_value;
	is_used = true;
	return *this;
}
IntArgument& IntArgument::StoreValue(std::string& value) {
	value_pointer = &value;
	return *this;
}

IntArgument& IntArgument::StoreValues(std::vector<int>& values) {
	values_pointer = &values;
	if (MinimalValues != 0) {
		int_argument_values.reserve(MinimalValues);
	}
	return *this;
}

IntArgument& IntArgument::MultiValue() {
	is_multivalue = true;
	return *this;
}

IntArgument& IntArgument::MultiValue(size_t MinArgsCount) {
	is_multivalue = true;
	MinimalValues = MinArgsCount;
	return *this;
}

IntArgument& IntArgument::Positional() {
	is_positional = true;
	return *this;
}