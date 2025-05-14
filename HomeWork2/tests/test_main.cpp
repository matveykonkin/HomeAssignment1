#include <gtest/gtest.h>
#include "gauss_solver.h"
#include <Eigen/Dense>

TEST(GaussSolverTest, SimpleSystem) {
    Eigen::MatrixXd A(2, 2);
    A << 1, 1, 2, -1;
    Eigen::VectorXd b(2);
    b << 3, 0;
    Eigen::VectorXd x = GaussSolver::solve(A, b);
    EXPECT_NEAR(x(0), 1.0, 1e-6);
    EXPECT_NEAR(x(1), 2.0, 1e-6);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}