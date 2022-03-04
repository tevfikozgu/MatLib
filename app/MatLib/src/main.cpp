/**
 * @brief   : Main code which executes program
 * @author  : Tevfik Özgü
 * @date    : 03.03.2022
 */


#include "../include/main.h"

// TODO: Update main.cpp file for testing.

int main() {

    Matrice<double> Matrice_1(5,4);
    Matrice<double> Matrice_2(4,4);

    double A[] = {1,2,3,4,
                  5,6,7,8,
                  5,6,7,8,
                  5,6,7,8,
                  5,6,9,1};

    double B[] = {2,4,1,8,
                  7,2,3,1,
                  5,6,7,8,
                  3,2,6,1};

    Matrice_1.init(A);
    Matrice_2.init(B);

    cout << "Summation: 1"                 << endl
         << "Difference: 2"                << endl
         << "Multiplication: 3"            << endl
         << "Copy Matrice: 4"              << endl
         << "Equalize Matrices: 5"         << endl
         << "Matrice Transpose: 6"         << endl
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
            case 4: /* Copy Constructor */
            {
                auto start = std::chrono::steady_clock::now();
                Matrice<double> New_Matrice = Matrice_1;
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << "Elapsed Time of Copy Constructor: " << elapsed_seconds.count() << "s\n";
                cout << New_Matrice;
                break;
            }
            case 5: /* Assigning Arrays */
            {
                Matrice<double> New_Matrice = Matrice_1;
                cout << "Old Matrice: "<< endl;
                cout << New_Matrice;
                auto start  = std::chrono::steady_clock::now();
                New_Matrice = Matrice_2;
                auto end    = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << "Elapsed Time of Equalization: " << elapsed_seconds.count() << "s\n";
                cout << "New Matrice: "<< endl;
                cout << New_Matrice;
                break;
            }
            case 6: /* Tranpose Operation */
            {
                cout << "Old Matrice: "<< endl;
                cout << Matrice_1;
                auto start  = std::chrono::steady_clock::now();
                Matrice<double> New_Matrice = Matrice_1.t();
                auto end    = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << "Elapsed Time of Transpose: " << elapsed_seconds.count() << "s\n";
                cout << "New Matrice: "<< endl;
                cout << New_Matrice;
                break;
            }
            case 7: /* Creating Identity Matrice */
            {
                auto start  = std::chrono::steady_clock::now();
                Matrice<double> New_Matrice = Matrice<double>::eye(5);
                auto end    = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << "Elapsed Time of Identity Creation: " << elapsed_seconds.count() << "s\n";
                cout << "New Matrice: "<< endl;
                cout << New_Matrice;
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
