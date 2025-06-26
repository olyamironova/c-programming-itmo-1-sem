#include <string>
#include <cstdint>

struct EnterArguments {
    std::string tsv_file_name;
    std::string path_to_directory;
    uint64_t max_iterations = -1;
    uint64_t frequency = 0;
};

EnterArguments GetInput(int argc, char** argv);