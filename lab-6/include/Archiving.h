#include <string>
#include <vector>

class Archive {
private:
    std::string archive_name;
    std::vector<std::string> file_names;
    int count_files;
public:
    Archive();
    Archive(const std::string& path);
    void AddFileToList(const std::string& file);
    void AddFilesToList(const std::vector<std::string>& files);
    void AddFileToArchive(const std::string& file);
    void Create();
    void WriteFileList();
    void Extract(const std::string& file);
    void ExtractAll();
    void DeleteFile(const std::string& file_name);
    void Concatenate(const std::string& name_arch1, const std::string& name_arch2);

};