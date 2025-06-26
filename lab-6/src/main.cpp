#include <iostream>
#include "Parser.h"
#include "Archiving.h"

int main(int argc, char** argv) {
    UserArguments user_input = UserParse(argc, argv);
    if ((!user_input.FileNames.empty()) && (user_input.PrintListOfFilesInArchive || user_input.ExtractFilesInArchive.first || user_input.AppendFileToArchive.first || user_input.DeleteFileToArchive.first || user_input.MergeTwoArchive.first)) {
        Archive archive(user_input.FileWithArchive);
        if (user_input.PrintListOfFilesInArchive) {
            archive.WriteFileList();
        }
        if (user_input.ExtractFilesInArchive.first) {
            if (user_input.FileNames.empty()) {
                archive.ExtractAll();
            } else {
                for (int i = 0; i < user_input.FileNames.size(); ++i) {
                    archive.Extract(user_input.FileNames[i]);
                }
            }
        }
        if (user_input.AppendFileToArchive.first) {
            for (int i = 0; i < user_input.FileNames.size(); ++i) {
                archive.Extract(user_input.FileNames[i]);
            }
        }
        if (user_input.DeleteFileToArchive.first) {
            for (int i = 0; i < user_input.FileNames.size(); ++i) {
                archive.DeleteFile(user_input.FileNames[i]);
            }
        }
        if (user_input.MergeTwoArchive.first) {
            archive.Concatenate(user_input.FileNames[0], user_input.FileNames[1]);
        }
    }
    if (user_input.Create) {
        std::cout << user_input.FileNames.size();
        Archive archive(user_input.FileWithArchive);
        for (const auto& name : user_input.FileNames) {
            archive.AddFileToList(name);
        }
        archive.Create();
    }
    return 0;
}