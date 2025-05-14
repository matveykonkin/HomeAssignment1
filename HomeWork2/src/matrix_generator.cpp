#include "matrix_generator.h"
#include <random>

Eigen::MatrixXd MatrixGenerator::generate(int rows, int cols, int seed) {
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(-10.0, 10.0);
    Eigen::MatrixXd matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix(i, j) = distribution(generator);
        }
    }
    return matrix;
}