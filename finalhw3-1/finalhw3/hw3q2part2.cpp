#include <iostream>
#include <Eigen/Dense>

int main() {
    Eigen::Matrix3f A;
    Eigen::Vector3f b;
    A << 1, 2, 3, 4, 5, 6, 7, 8, 10;
    b << 3, 3, 4;

    Eigen::Vector3f x = A.colPivHouseholderQr().solve(b);

    std::cout << "The solution is:\n" << x << std::endl;
    return 0;
}
