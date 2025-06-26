#pragma once
#include <string>
#include <vector>
#include <map>

class StringArgument {
public:
	StringArgument() = default;
	std::string string_argument_value;
	bool is_used = false;
	StringArgument& Default(const std::string default_value);
	StringArgument& StoreValue(std::string& value);
	std::string* value_pointer;
	bool is_positional = false;
	std::vector<std::string> help_arg;
	std::string help_full_name = "";
	char help_short_name = '\0';
	std::string help_description = "";
	StringArgument& MultiValue(size_t MinArgsCount);
	bool is_multivalue = false;
	int MinimalValues;

};
