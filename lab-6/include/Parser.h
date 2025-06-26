#include <string>
#include <vector>

struct UserArguments {
    bool Create;
    std::string FileWithArchive;
    bool PrintListOfFilesInArchive;
    std::pair<bool, std::vector<std::string>> ExtractFilesInArchive;
    std::pair<bool, std::vector<std::string>> AppendFileToArchive;
    std::pair<bool, std::vector<std::string>> DeleteFileToArchive;
    std::pair<bool, std::vector<std::string>> MergeTwoArchive;
    std::vector<std::string> FileNames;
};

UserArguments UserParse(int argc, char** argv);