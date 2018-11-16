#include <iostream>

#include "FibonacciHeap.h"
#include "FrequencyCounter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Input file not provided" << std::endl;
    }
    {
        std::string inputFile(argv[1]);
        FrequencyCounter fCounter(inputFile, "output_file.txt");
        fCounter.analyze();
        fCounter.printAllItems();
    }

    return 0;
}


