#include "parser.h"

EnterArguments GetInput(int argc, char** argv) {
    EnterArguments enter_arguments;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-i" || arg == "--input") && i + 1 < argc) {
            enter_arguments.tsv_file_name = argv[i + 1];
        } else if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
            enter_arguments.path_to_directory = argv[i + 1];
        } else if ((arg == "-m" || arg == "--max-iter") && i + 1 < argc) {
            enter_arguments.max_iterations = std::stoull(argv[i + 1]);
        } else if ((arg == "-f" || arg == "--freq") && i + 1 < argc) {
            enter_arguments.frequency = std::stoull(argv[i + 1]);
        }
    }
    return enter_arguments;
}