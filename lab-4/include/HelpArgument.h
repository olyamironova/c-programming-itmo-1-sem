#pragma once
#include <string>
#include <vector>
#include <map>

class HelpArgument {
public:
	HelpArgument() = default;
	char shortname;
	std::string fullname;
	std::string some_information;
	HelpArgument& AddHelp(const char* shortname, std::string fullname, std::string some_information);
	HelpArgument& StoreValue(std::string& value);
	std::string* value_pointer;


};
