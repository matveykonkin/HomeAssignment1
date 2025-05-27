#ifndef SHANNON_ENCODER_H
#define SHANNON_ENCODER_H

#include <string>
#include <map>
#include <vector>

class ShannonEncoder {
private:
    struct Symbol {
        unsigned char byte;
        int frequency;
    };

    struct SymbolComparator {
        bool operator()(const Symbol& a, const Symbol& b);
    };

    std::map<unsigned char, int> frequencies;
    std::map<unsigned char, std::string> codes;
    
    void buildCodesRecursive(std::vector<Symbol>& symbols, int start, int end, std::string code);
    
public:
    void analyzeFile(const std::string& filename);
    void buildCodes();
    void encodeFile(const std::string& inputFile, const std::string& outputFile, const std::string& dictFile);
};

#endif