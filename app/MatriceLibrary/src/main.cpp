#include <iostream>
#include "include/Matrice.h"
#include "src/Matrice.cpp"

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

    cout << "Summation: 1"                 << endl
         << "Difference: 2"                << endl
         << "Multiplication: 3"            << endl
         << "Exit: -1"                     << endl
         << "Operation You Want to Make: ";

    int selection = 0;

    while (true) {

        cin >> selection;
        if (selection == -1)
            break;

        switch (selection) {
            case 1: /* Summation Operations */
            {
                auto start = std::chrono::steady_clock::now();
                Matrice<double> Matrice_Sum = Matrice_1 + Matrice_2;
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << "Elapsed Time of Summation: " << elapsed_seconds.count() << "s\n";
                cout << Matrice_Sum;
                break;
            }
            case 2: /* Difference Operations */
            {
                auto start = std::chrono::steady_clock::now();
                Matrice<double> Matrice_Diff = Matrice_1 - Matrice_2;
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << "Elapsed Time of Difference: " << elapsed_seconds.count() << "s\n";
                cout << Matrice_Diff;
                break;
            }
            case 3: /* Multiplication Operations */
            {
                auto start = std::chrono::steady_clock::now();
                Matrice<double> Matrice_Mul = Matrice_1 * Matrice_2;
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << "Elapsed Time of Multiplication: " << elapsed_seconds.count() << "s\n";
                cout << Matrice_Mul;
                break;
            }
            default: {
                cout << "Wrong Selection" << endl;
                break;
            }
        }
        cout << endl << "Next Selection: ";
    }

    cout << "Exiting..." << endl;

    return EXIT_SUCCESS;
}
