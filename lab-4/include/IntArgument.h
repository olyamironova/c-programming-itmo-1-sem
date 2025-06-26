#pragma once
#include <string>
#include <vector>
#include <map>

class IntArgument {
public:
	IntArgument() = default;
	int int_argument_value;
	bool is_used = false;
	IntArgument& Default(int default_value);
	IntArgument& StoreValue(std::string& value);
	IntArgument& StoreValues(std::vector<int>& values);
	std::string* value_pointer;
	std::vector<int>* values_pointer;
	std::vector<int> int_argument_values;
	IntArgument& MultiValue();
	bool is_multivalue = false;
	IntArgument& MultiValue(size_t MinArgsCount);
	int MinimalValues = 0;
	IntArgument& Positional();
	std::string positional_key;
	bool is_positional = false;
	std::string help_full_name = "";
	std::string help_description = "";
private:
};