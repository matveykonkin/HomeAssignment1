#pragma once
#include <vector>
#include <string>

class CSVReader {
public:
    static std::vector<std::vector<double>> read(const std::string& filename);
};