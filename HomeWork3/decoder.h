#ifndef SHANNON_DECODER_H
#define SHANNON_DECODER_H

#include <string>
#include <map>

class ShannonDecoder {
private:
    std::map<std::string, unsigned char> reverseCodes;
    
public:
    void loadDictionary(const std::string& dictFile);
    void decodeFile(const std::string& inputFile, const std::string& outputFile);
};

#endif