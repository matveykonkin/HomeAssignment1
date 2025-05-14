#include "encoder.h"
#include <fstream>
#include <algorithm>
#include <iostream>

bool ShannonEncoder::SymbolComparator::operator()(const Symbol& a, const Symbol& b) {
    return a.frequency > b.frequency;
}

void ShannonEncoder::buildCodesRecursive(std::vector<Symbol>& symbols, int start, int end, std::string code) {
    if (start == end) {
        codes[symbols[start].byte] = code;
        return;
    }
    
    int total = 0;
    for (int i = start; i <= end; i++) {
        total += symbols[i].frequency;
    }
    
    int sum = 0;
    int split = start;
    for (int i = start; i <= end; i++) {
        sum += symbols[i].frequency;
        if (sum >= total / 2) {
            split = i;
            break;
        }
    }
    
    buildCodesRecursive(symbols, start, split, code + "0");
    buildCodesRecursive(symbols, split + 1, end, code + "1");
}

void ShannonEncoder::analyzeFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
    
    frequencies.clear();
    unsigned char byte;
    while (file.read(reinterpret_cast<char*>(&byte), 1)) {
        frequencies[byte]++;
    }
    file.close();
}

void ShannonEncoder::buildCodes() {
    std::vector<Symbol> symbols;
    for (const auto& pair : frequencies) {
        symbols.push_back({pair.first, pair.second});
    }
    
    std::sort(symbols.begin(), symbols.end(), SymbolComparator());
    
    codes.clear();
    if (!symbols.empty()) {
        buildCodesRecursive(symbols, 0, symbols.size() - 1, "");
    }
}

void ShannonEncoder::encodeFile(const std::string& inputFile, const std::string& outputFile, const std::string& dictFile) {
    analyzeFile(inputFile);
    buildCodes();
    
    std::ofstream dictStream(dictFile);
    if (!dictStream) {
        std::cerr << "Cannot create dictionary file: " << dictFile << std::endl;
        return;
    }
    
    for (const auto& pair : codes) {
        dictStream << static_cast<int>(pair.first) << ":" << pair.second << "\n";
    }
    dictStream.close();
    
    std::ifstream inStream(inputFile, std::ios::binary);
    std::ofstream outStream(outputFile, std::ios::binary);
    if (!inStream || !outStream) {
        std::cerr << "Cannot open files for encoding" << std::endl;
        return;
    }
    
    unsigned char buffer = 0;
    int bitCount = 0;
    unsigned char byte;
    
    while (inStream.read(reinterpret_cast<char*>(&byte), 1)) {
        std::string code = codes[byte];
        for (char bit : code) {
            if (bit == '1') {
                buffer |= (1 << (7 - bitCount));
            }
            bitCount++;
            
            if (bitCount == 8) {
                outStream.write(reinterpret_cast<char*>(&buffer), 1);
                buffer = 0;
                bitCount = 0;
            }
        }
    }
    
    if (bitCount > 0) {
        outStream.write(reinterpret_cast<char*>(&buffer), 1);
    }
    
    inStream.close();
    outStream.close();
}