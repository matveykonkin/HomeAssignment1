#pragma once
#include <Eigen/Dense>

class MatrixGenerator {
public:
    static Eigen::MatrixXd generate(int rows, int cols, int seed = 42);
};