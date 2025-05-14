#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <cassert>
#include <filesystem> 
#include <random>

#include "encoder.h"
#include "decoder.h"

using namespace std;
namespace fs = std::filesystem;

void runTests() {
    // Тест 1: Простая строка
    {
        string testData = "this is a test string for shannon coding algorithm";
        string inputFile = "test_input.bin";
        string compressedFile = "test_compressed.bin";
        string dictFile = "test_dict.txt";
        string outputFile = "test_output.bin";
        
        ofstream out(inputFile, ios::binary);
        out.write(testData.data(), testData.size());
        out.close();
        
        ShannonEncoder encoder;
        encoder.encodeFile(inputFile, compressedFile, dictFile);
        
        ShannonDecoder decoder;
        decoder.loadDictionary(dictFile);
        decoder.decodeFile(compressedFile, outputFile);
        
        ifstream original(inputFile, ios::binary);
        ifstream decoded(outputFile, ios::binary);
        
        assert(equal(
            istreambuf_iterator<char>(original),
            istreambuf_iterator<char>(),
            istreambuf_iterator<char>(decoded)
        ));
        
        original.close();
        decoded.close();
        
        fs::remove(inputFile);
        fs::remove(compressedFile);
        fs::remove(dictFile);
        fs::remove(outputFile);
    }
    // Тест 2: Пустой файл
    {
        string inputFile = "empty_input.bin";
        string compressedFile = "empty_compressed.bin";
        string dictFile = "empty_dict.txt";
        string outputFile = "empty_output.bin";
        
        ofstream out(inputFile, ios::binary);
        out.close();
        
        ShannonEncoder encoder;
        encoder.encodeFile(inputFile, compressedFile, dictFile);
        
        ShannonDecoder decoder;
        decoder.loadDictionary(dictFile);
        decoder.decodeFile(compressedFile, outputFile);
        
        ifstream decoded(outputFile, ios::binary);
        assert(decoded.peek() == ifstream::traits_type::eof());
        decoded.close();
        
        fs::remove(inputFile);
        fs::remove(compressedFile);
        fs::remove(dictFile);
        fs::remove(outputFile);
    }
    
    // Тест 3: Случайные данные
    {
        const size_t size = 1024 * 1024; 
        string inputFile = "random_input.bin";
        string compressedFile = "random_compressed.bin";
        string dictFile = "random_dict.txt";
        string outputFile = "random_output.bin";
        
        ofstream out(inputFile, ios::binary);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned char> dist;
        
        for (size_t i = 0; i < size; ++i) {
            unsigned char byte = dist(gen);
            out.write(reinterpret_cast<char*>(&byte), 1);
        }
        out.close();
        
        ShannonEncoder encoder;
        encoder.encodeFile(inputFile, compressedFile, dictFile);
        
        ShannonDecoder decoder;
        decoder.loadDictionary(dictFile);
        decoder.decodeFile(compressedFile, outputFile);
        
        ifstream original(inputFile, ios::binary);
        ifstream decoded(outputFile, ios::binary);
        
        assert(equal(
            istreambuf_iterator<char>(original),
            istreambuf_iterator<char>(),
            istreambuf_iterator<char>(decoded)
        ));
        
        original.close();
        decoded.close();
        
        fs::remove(inputFile);
        fs::remove(compressedFile);
        fs::remove(dictFile);
        fs::remove(outputFile);
    }
    
    cout << "All tests passed successfully!" << endl;
}

int main() {
    runTests();
    return 0;
}