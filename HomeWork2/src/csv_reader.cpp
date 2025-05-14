#include "csv_reader.h"
#include <fstream>
#include <sstream>

std::vector<std::vector<double>> CSVReader::read(const std::string& filename) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<double> row;
        std::stringstream ss(line);
        std::string value;
        while (std::getline(ss, value, ',')) {
            row.push_back(std::stod(value));
        }
        data.push_back(row);
    }

    return data;
}