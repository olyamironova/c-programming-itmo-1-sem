#pragma once
#include <string>
#include <vector>
#include <map>

class FlagArgument {
public:
	FlagArgument() = default;
	bool flag_argument_value = true;
	bool is_used = false;
	bool* value_pointer;
	FlagArgument& Default(bool flag);
	FlagArgument& StoreValue(bool& value);
	bool GetFlag(const std::string& fullname);
	FlagArgument& AddFlag(size_t MinArgsCount);
	bool is_multivalue = false;
	int MinimalValues;
	std::string help_full_name = "";
	char help_short_name = '\0';
	std::string help_description = "";
};

