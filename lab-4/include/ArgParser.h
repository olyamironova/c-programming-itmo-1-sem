#pragma once
#include <string>
#include <vector>
#include <map>
#include "StringArgument.h"
#include "FlagArgument.h"
#include "IntArgument.h"
#include "HelpArgument.h"
#include <iostream>

namespace ArgumentParser {

    class ArgParser {
        
    public:
        explicit ArgParser(const std::string& name) : parserName(name) {};
        std::string parser_name;
        bool Parse(std::vector<std::string> arguments);
        std::string GetStringValue(const std::string& fullname);
        StringArgument& AddStringArgument(const std::string& fullname);
        StringArgument& AddStringArgument(const char& shortname, const std::string& fullname);
        IntArgument& AddIntArgument(const std::string& fullname);
        int GetIntValue(const std::string& fullname);
        IntArgument& AddIntArgument(const char& shortname, const std::string& fullname);
        int GetIntValue(const std::string& fullname, int index);
        bool isParserMultivalue = false;
        FlagArgument& AddFlag(const char& shortname, const std::string& fullname);
        bool GetFlag(const std::string& fullname);
        std::string GetPositionalStringKey();
        std::string GetPositionalIntKey();
        void AddHelp(const char& param_name_char, const std::string& param_name_string, const std::string& param_name_description);
        bool Help();
        void HelpDescription();
        bool is_add_help = false;
        StringArgument& AddStringArgument(const char& param_name_char, const std::string& param_name_string, const std::string& param_name_description_string);
        FlagArgument& AddFlag(const char& param_name_char, const std::string& param_name_string, const std::string& param_name_description_string);
        IntArgument& AddIntArgument(const std::string& param_name_string, const std::string& param_name_description_string);


    private:
    std::map<std::string, StringArgument>StringValues;
    std::map<std::string, std::string> ShortLongArgument;
    std::map<std::string, IntArgument>IntValues;
    std::map<std::string, std::string> ShortLongIntArgument;
    std::map<std::string, FlagArgument>FlagValues;
    std::map<std::string, std::string> ShortLongFlagArgument;
    std::vector<std::string> HelpInformation;
    std::string parserName;
    std::vector<std::string> help_arg;
    std::string help_full_name = "";
    char help_short_name = '\0';
    std::string help_description = "";
};

}
    





// namespace ArgumentParser