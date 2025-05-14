#include "csv_writer.h"
#include <fstream>

void CSVWriter::write(const std::string& filename, const std::vector<double>& data) {
    std::ofstream file(filename);
    for (const auto& value : data) {
        file << value << "\n";
    }
}