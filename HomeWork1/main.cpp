#include "ascii85.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        bool decode = false;
        bool streamMode = false;
        
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-d" || arg == "--decode") {
                decode = true;
            } else if (arg == "-s" || arg == "--stream") {
                streamMode = true;
            } else if (arg == "-h" || arg == "--help") {
                std::cout << "Usage: " << argv[0] << " [options]\n"
                          << "Options:\n"
                          << "  -d, --decode   Decode input\n"
                          << "  -s, --stream   Process in streaming mode\n"
                          << "  -h, --help     Show this help message\n";
                return 0;
            } else {
                std::cerr << "Unknown option: " << arg << "\n";
                return 1;
            }
        }
        
        processInput(decode, streamMode, std::cin, std::cout);
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}