#include "StringArgument.h"
StringArgument& StringArgument::Default(const std::string default_value) {
	string_argument_value = default_value;
	is_used = true;
	return *this;
}
StringArgument& StringArgument::StoreValue(std::string& value) {
	value_pointer = &value;
	return *this;
}

StringArgument& StringArgument::MultiValue(size_t MinArgsCount) {
	is_multivalue = true;
	MinimalValues = MinArgsCount;
	return *this;
}
