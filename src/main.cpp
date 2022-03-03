#include <iostream>
#include "Matrice.h"
#include "Matrice.cpp"

using namespace std;

int main() {

    Matrice<double> Matrice_1(4,4);
    Matrice<double> Matrice_2(4,4);

    double A[] = {1,2,3,4,
                  5,6,7,8,
                  5,6,7,8,
                  5,6,7,8};

    double B[] = {2,4,1,8,
                  7,2,3,1,
                  5,6,7,8,
                  3,2,6,1};

    Matrice_1.init(A);
    Matrice_2.init(B);

    auto start = std::chrono::steady_clock::now();

    Matrice<double> Matrice_3 = Matrice_1 * Matrice_2;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
