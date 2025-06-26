#include <functional>
#include <lib/ArgParser.h>

#include <iostream>
#include <numeric>
#include <sstream>

std::vector<std::string> SplitString(const std::string& str) {
    std::istringstream iss(str);

    return { std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>() };
}

int main() {
    ArgumentParser::ArgParser parser("My Parser");
    parser.AddHelp('h', "help", "Some Description about program");
    parser.AddStringArgument('i', "input", "File path for input file").MultiValue(1);
    parser.AddFlag('s', "flag1", "Use some logic").Default(true);
    parser.AddFlag('p', "flag2", "Use some logic");
    parser.AddIntArgument("numer", "Some Number");
    // parser.Parse(SplitString("app"));
    // (parser.GetStringValue("param1"));
    parser.HelpDescription();
}