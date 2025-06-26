#include "FlagArgument.h"
FlagArgument& FlagArgument::Default(bool flag) {
	flag_argument_value = flag;
	return *this;
}
FlagArgument& FlagArgument::StoreValue(bool& value) {
	value_pointer = &value;
	return *this;
}
bool FlagArgument::GetFlag(const std::string& fullname) {
	return flag_argument_value;
}

