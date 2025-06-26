#include "ArgParser.h"


bool isNumeric(std::string const& str) {
    auto it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        it++;
    }
    return !str.empty() && it == str.end();
}

using namespace ArgumentParser;


bool ArgParser::Parse(std::vector<std::string> arguments) {
    
    for (int i = 1; i < arguments.size(); ++i) {
        std::string int_positional_key = GetPositionalIntKey();
        std::string string_positional_key = GetPositionalStringKey();
        size_t index_equally = arguments[i].find('=');
        std::string value = arguments[i].substr(index_equally + 1);
        std::string key;
        if (arguments[i].substr(0, 2) == "--") {
            key = arguments[i].substr(2, index_equally - 2);
        }
        else if (arguments[i][0] == '-') {
            key = ShortLongArgument[std::to_string(arguments[i][1])];
        }
        else {
            key = arguments[i];
        }
        if (std::find(help_arg.begin(), help_arg.end(), key) != help_arg.end() && size(help_arg) != 0) {
            std::cout << "dfs";
            is_add_help = true;
        }
        if (!(isNumeric(value))) {
            if (FlagValues.count(key) != 0) {
                FlagValues[key].is_used = true;
            }
            else if (key.substr(0, 5) != "param") {
                for (int j = 0; j < key.size(); ++j) {
                    FlagValues[&key[j]].is_used = true;
                }
            }
            else {
                if (StringValues.count(key) != 0) {
                    StringValues[key].string_argument_value = value;
                    std::cout << value;
                    StringValues[key].is_used = true;
                }
                if (StringValues[key].value_pointer != nullptr) {
                    *StringValues[key].value_pointer = StringValues[key].string_argument_value;
                }
            }
            
        }
        else if ((IntValues.count(key) > 0) || (int_positional_key != "0") && ((arguments[i][0]  == '-') || std::isdigit(arguments[i][0])) && FlagValues.count(key) == 0) {
            if (IntValues.count(key) == 0) {
                key = int_positional_key;
                value = arguments[i].substr();
            }
            
            if (IntValues[key].is_multivalue == false) {
                if (IntValues.count(key) != 0) {
                    IntValues[key].int_argument_value = std::stoi(value);
                    IntValues[key].is_used = true;
                }
                if (IntValues[key].value_pointer != nullptr) {
                    *IntValues[key].value_pointer = IntValues[key].int_argument_value;
                }
            }
            else if (IntValues[key].is_multivalue == true) {
                if (IntValues.count(key) != 0) {
                    IntValues[key].int_argument_values.push_back(std::stoi(value));
                    IntValues[key].is_used = true;
                }
                if (IntValues[key].values_pointer != nullptr) {
                    *IntValues[key].values_pointer = IntValues[key].int_argument_values;
                }
            }
        }
        
        
        if (IntValues[key].int_argument_values.size() < IntValues[key].MinimalValues) {
            return false;
        }
    }
    std::cout << is_add_help << '\n';
   if (is_add_help == true) {
       std::cout << is_add_help;
        return true;
    }
    for (const std::pair<std::string, StringArgument>& pair : StringValues) {
        StringArgument ArgString = pair.second;
        if (ArgString.is_used == false) {
            return false;
        }
    }

    for (const std::pair<std::string, FlagArgument>& pair : FlagValues) {
        FlagArgument FlagString = pair.second;
        if (FlagString.is_used == false) {
            return false;
        }
    }

    return true;
    
}

StringArgument& ArgParser::AddStringArgument(const std::string& fullname) {
    StringValues[fullname] = StringArgument();
    return StringValues[fullname];
}

StringArgument& ArgParser::AddStringArgument(const char& shortname, const std::string& fullname) {
    std::cout << "*";
    StringValues[fullname] = StringArgument();
    ShortLongArgument[std::to_string(shortname)] = fullname;
    return StringValues[fullname];
}

std::string ArgParser::GetStringValue(const std::string& fullname) {
    return StringValues[fullname].string_argument_value;

}

IntArgument& ArgParser::AddIntArgument(const std::string& fullname) {
    IntValues[fullname] = IntArgument();
    IntValues[fullname].positional_key = fullname;
    return IntValues[fullname];
}

int ArgParser::GetIntValue(const std::string& fullname) {
    return IntValues[fullname].int_argument_value;
}

IntArgument& ArgParser::AddIntArgument(const char& shortname, const std::string& fullname) {
    IntValues[fullname] = IntArgument();
    ShortLongIntArgument[std::to_string(shortname)] = fullname;
    
    return IntValues[fullname];
}

int ArgParser::GetIntValue(const std::string& fullname, int index) {
    return IntValues[fullname].int_argument_values[index];
}

FlagArgument& ArgParser::AddFlag(const char& shortname, const std::string& fullname) {
    FlagValues[fullname] = FlagArgument();
    ShortLongFlagArgument[std::to_string(shortname)] = fullname;
    FlagValues[fullname].is_used = true;
    return FlagValues[fullname];
}

bool ArgParser::GetFlag(const std::string& fullname) {
    return FlagValues[fullname].flag_argument_value;
}

std::string ArgParser::GetPositionalIntKey() {
    for (const std::pair<std::string, IntArgument>& pair : IntValues) {
        IntArgument int_arguments = pair.second;
        if (int_arguments.is_positional == true) {
            return pair.first;
        }
    }
    return "";
};

std::string ArgParser::GetPositionalStringKey() {
    for (const std::pair<std::string, StringArgument>& pair : StringValues) {
        StringArgument string_arguments = pair.second;
        if (string_arguments.is_positional == true) {
            return pair.first;
        }
    }
    return "";
};
void  ArgParser::AddHelp(const char& param_name_char, const std::string& param_name_string, const std::string& param_name_description_string) {
    help_full_name = param_name_string;
    help_short_name = param_name_char;
    help_description = param_name_description_string;
    help_arg.push_back(std::to_string(param_name_char));
    help_arg.push_back(param_name_string);
}
bool  ArgParser::ArgParser::Help() {
    return is_add_help;
}

StringArgument& ArgParser::AddStringArgument(const char& param_name_char, const std::string& param_name_string, const std::string& param_name_description_string) {
    StringValues[param_name_string] = StringArgument();
    ShortLongArgument[std::to_string(param_name_char)] = param_name_string;
    StringValues[param_name_string].help_description = param_name_description_string;
    StringValues[param_name_string].help_short_name = param_name_char;
    StringValues[param_name_string].help_full_name = param_name_string;
    return StringValues[param_name_string];
}

FlagArgument& ArgParser::AddFlag(const char& param_name_char, const std::string& param_name_string, const std::string& param_name_description_string) {
    FlagValues[param_name_string] = FlagArgument();
    ShortLongFlagArgument[std::to_string(param_name_char)] = param_name_string;
    FlagValues[param_name_string].help_description = param_name_description_string;
    return FlagValues[param_name_string];
}

IntArgument& ArgParser::AddIntArgument(const std::string& param_name_string, const std::string& param_name_description_string) {
    IntValues[param_name_description_string] = IntArgument();
    ShortLongIntArgument[param_name_string] = param_name_description_string;
    IntValues[param_name_description_string].help_full_name = param_name_string;
    IntValues[param_name_description_string].help_description = param_name_description_string;
    return IntValues[param_name_description_string];
}

void ArgParser::HelpDescription() {
    // std::cout << HelpInformation[2] << '\n';
    std::cout << '\n';
    for (const std::pair<std::string, StringArgument>& pair : StringValues) {
        StringArgument ArgString = pair.second;
        std::cout << "-" << ArgString.help_short_name << " " << "--" << ArgString.help_full_name << "=<string>,  " << ArgString.help_description << " [repeated, min args = " << ArgString.MinimalValues << "]\n";
    }
    for (const std::pair<std::string, FlagArgument>& pair : FlagValues) {
        FlagArgument ArgFlag = pair.second;
        std::cout << "-" << ArgFlag.help_short_name << " " << "--" << ArgFlag.help_full_name << "=<string>,  " << ArgFlag.help_description << " [default = " << ArgFlag.flag_argument_value << "]\n";
    }
    for (const std::pair<std::string, IntArgument>& pair : IntValues) {
        IntArgument ArgInt = pair.second;
        std::cout << "     " << ArgInt.help_full_name << "=<int>,  " << ArgInt.help_description;
    }
    std::cout << '\n';s
}