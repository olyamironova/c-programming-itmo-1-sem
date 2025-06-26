
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

struct Arguments {
    std::string filename;
    uint64_t lines = 0;
    bool tail = false;
    char delimiter = '\n';
};

char ParseDel(char delim) {
    switch (delim) {
        case 'n': return '\n';
        case 't': return '\t';
        case 'r': return '\r';
        case 'a': return '\a';
        case 'b': return '\b';
        case 'f': return '\f';
        case 'v': return '\v';
        default: return delim;
    }
}

Arguments Parse(int argc, char** argv) {
    Arguments parser;
    for (size_t i = 0; i < argc; ++i) {
        std::string argument = argv[i];
        if (argument.starts_with("--lines=")) {
            if (argument.size() > 8){
                parser.lines = std::stoi(argument.substr(8));
            } else{
                std::cerr << "Invalid value for -l\n";
                exit(EXIT_FAILURE);
            }

        } else if (argument == "-l") {
            if (i + 1 < argc) {
                parser.lines = std::atoi(argv[i + 1]);
                if (!parser.lines) {
                    std::cerr << "Invalid value for -l\n";
                    exit(EXIT_FAILURE);
                }
                ++i;
            } else {
                std::cerr << "Set value of -l." << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (argument.starts_with("--delimiter")) {
            if (argument[12] == '\\') {
                char h = argument[13];
                parser.delimiter = ParseDel(h);
            } else {
                parser.delimiter = argument[12];
            }
        } else if (argument == "-d") {
            if (i + 1 < argc) {
                if (argv[i + 1][0] == '\\') {
                    char h = argv[i + 1][1];
                    parser.delimiter = ParseDel(h);
                } else {
                    parser.delimiter = argv[i + 1][0];
                }
                ++i;
            } else {
                std::cerr << "Set value of -d." << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (argument == "-t" || argument.starts_with("--tail")) {
            parser.tail = true;
        } else {
            parser.filename = argument;
        }
    }

    return parser;
}

void PrintParser(const Arguments& parser) {
    std::ifstream fin(parser.filename);
    int counter_of_lines = 0;
    char h;
    while (fin.get(h)) {
        if (h == parser.delimiter) {
            ++counter_of_lines;
        }
    }

    uint64_t print_lines = parser.lines;
    if (print_lines == 0) {
        print_lines = counter_of_lines;
    }

    fin.clear();
    fin.seekg(0);

    if (!parser.tail) {
        while (fin.get(h) && print_lines != 0) {
            std::cout << h;
            if (h == parser.delimiter) {
                --print_lines;
            }
        }
    } else {
        if (parser.lines < counter_of_lines) {
            print_lines = counter_of_lines - parser.lines;
        }
        if (parser.lines < counter_of_lines) {
            while (print_lines && fin.get(h)) {
                if (h == parser.delimiter) {
                    --print_lines;
                }
            }
        }

        while (fin.get(h)) {
            std::cout << h;
        }
    }
}

int main(int argc, char** argv) {
    Arguments parser = Parse(argc, argv);
    PrintParser(parser);
    return 0;
}