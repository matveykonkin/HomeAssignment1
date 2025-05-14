#include "gauss_solver.h"

Eigen::VectorXd GaussSolver::solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) {
    return A.colPivHouseholderQr().solve(b);
}