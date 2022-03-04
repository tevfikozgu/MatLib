#include <Eigen/Dense>
#include <iostream>

using namespace std;
using Eigen::MatrixXd;

int main()
{
    MatrixXd m1(4,4);
    MatrixXd m2(4,4);

    m1 <<   1,2,3,4,
            5,6,7,8,
            5,6,7,8,
            5,6,7,8;

    m2 <<   2,4,1,8,
            7,2,3,1,
            5,6,7,8,
            3,2,6,1;

    /* */
    auto start = std::chrono::steady_clock::now();

    MatrixXd m3 = m1 * m2;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "elapsed time EIGEN: " << elapsed_seconds.count() << "s\n";
    cout << m3;
    /* */

    return 0;
}
