#pragma once
#include <Eigen/Dense>

class GaussSolver {
public:
    static Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
};