#include <iostream>
#include "sandpile.h"
#include "parser.h"
#include "tsv_parser.h"
#include "bmp.h"

int main(int argc, char** argv) {

    EnterArguments arguments = GetInput(argc, argv);
    int* size = DefinitionSize(arguments.tsv_file_name);
    Sandpile sandpile(size[0], size[1]);
    FillingTheCells(arguments.tsv_file_name, sandpile);

    uint64_t iteration = 0;
    bool running = true;
    LinkedList changes;
    while (running && iteration != arguments.max_iterations) {

        Sandpile::Expansion(sandpile);
        running = Sandpile::NecessaryInExpansion(sandpile);
        Sandpile::CollectionOverflowCellsInOneIteration(sandpile, changes);
        Sandpile::LinkedListProcessing(sandpile, changes);

        iteration++;

        if (arguments.frequency != 0) {
            if (iteration % arguments.frequency == 0) {
                std::string temp = arguments.path_to_directory + std::to_string(iteration) + ".bmp";
                ExportImage(sandpile, temp);
            }
        }

    }

    if (arguments.frequency == 0) {
        std::string temp = arguments.path_to_directory + std::to_string(iteration) + ".bmp";
        ExportImage(sandpile, temp);
    }

    std::cout << "The sand pile model is built" << std::endl;
    return 0;
}