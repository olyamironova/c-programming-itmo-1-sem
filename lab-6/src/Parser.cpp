#include <cstring>
#include <iostream>
#include "Parser.h"

UserArguments UserParse(int argc, char** argv) {
    UserArguments user_input;
    user_input.Create = false;
    user_input.PrintListOfFilesInArchive = false;
    user_input.ExtractFilesInArchive.first = false;
    user_input.AppendFileToArchive.first = false;
    user_input.DeleteFileToArchive.first = false;
    user_input.MergeTwoArchive.first = false;
    for (int i = 2; i < argc; ++i) {
        char *arg = argv[i];
        std::cout << argv[i] << std::endl;
        std::string string_arg = arg;
        if ((std::strcmp(arg, "-c") == 0) || (std::strcmp(arg, "--create") == 0)) {
            user_input.Create = true;
        } else if (std::strcmp(arg, "-f") == 0) {
            std::string next_string_arg = argv[i + 1];
            user_input.FileWithArchive = next_string_arg;
        } else if (string_arg.substr(0, 7) == "--file=") { // --file=
            user_input.FileWithArchive = string_arg.substr(7, 1000);
        } else if ((std::strcmp(arg, "-l") == 0) || (std::strcmp(arg, "--list") == 0)) {
            user_input.PrintListOfFilesInArchive = true;
        } else if ((std::strcmp(arg, "-x") == 0) || (std::strcmp(arg, "--extract") == 0)) {
            user_input.ExtractFilesInArchive.first = true;
        } else if ((std::strcmp(arg, "-a") == 0) || (std::strcmp(arg, "--append") == 0)) {
            user_input.AppendFileToArchive.first = true;
        } else if ((std::strcmp(arg, "-d") == 0) || (std::strcmp(arg, "--delete") == 0)) {
            user_input.DeleteFileToArchive.first = true;
        } else if ((std::strcmp(arg, "-A") == 0) || (std::strcmp(arg, "--concatenate") == 0)) {
            user_input.MergeTwoArchive.first = true;
        } else {
            user_input.FileNames.push_back(string_arg);
        }
    }
    return user_input;
}