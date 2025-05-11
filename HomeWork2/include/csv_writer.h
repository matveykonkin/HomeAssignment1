#pragma once
#include <vector>
#include <string>

class CSVWriter {
public:
    static void write(const std::string& filename, const std::vector<double>& data);
};