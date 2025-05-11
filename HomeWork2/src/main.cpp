#include <iostream>
#include "csv_reader.h"
#include "gauss_solver.h"
#include "csv_writer.h"
#include <Eigen/Dense>

int main() {
    try {
        auto data = CSVReader::read("../data/input.csv");
        if (data.empty() || data[0].empty()) {
            throw std::runtime_error("Input file is empty or invalid");
        }

        int rows = data.size();
        int cols = data[0].size();
        Eigen::MatrixXd A(rows, cols - 1);
        Eigen::VectorXd b(rows);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols - 1; ++j) {
                A(i, j) = data[i][j];
            }
            b(i) = data[i][cols - 1];
        }

        Eigen::VectorXd x = GaussSolver::solve(A, b);

        std::vector<double> result(x.data(), x.data() + x.size());
        CSVWriter::write("../data/output.csv", result);

        std::cout << "Solution saved to output.csv" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}