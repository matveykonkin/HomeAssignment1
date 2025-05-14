#include "decoder.h"
#include <fstream>
#include <iostream>
#include <string>

void ShannonDecoder::loadDictionary(const std::string& dictFile) {
    std::ifstream dictStream(dictFile);
    if (!dictStream) {
        std::cerr << "Cannot open dictionary file: " << dictFile << std::endl;
        return;
    }
    
    reverseCodes.clear();
    std::string line;
    while (std::getline(dictStream, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            int byteValue = std::stoi(line.substr(0, colonPos));
            std::string code = line.substr(colonPos + 1);
            reverseCodes[code] = static_cast<unsigned char>(byteValue);
        }
    }
    dictStream.close();
}

void ShannonDecoder::decodeFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inStream(inputFile, std::ios::binary);
    std::ofstream outStream(outputFile, std::ios::binary);
    if (!inStream || !outStream) {
        std::cerr << "Cannot open files for decoding" << std::endl;
        return;
    }
    
    std::string currentCode;
    unsigned char byte;
    
    while (inStream.read(reinterpret_cast<char*>(&byte), 1)) {
        for (int i = 7; i >= 0; i--) {
            char bit = (byte & (1 << i)) ? '1' : '0';
            currentCode += bit;
            
            if (reverseCodes.find(currentCode) != reverseCodes.end()) {
                outStream.write(reinterpret_cast<const char*>(&reverseCodes[currentCode]), 1);
                currentCode.clear();
            }
        }
    }
    
    inStream.close();
    outStream.close();
}