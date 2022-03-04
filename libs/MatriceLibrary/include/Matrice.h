/*******************
 * @brief   : This file contains Class structure of MatLib
 * @author  : Tevfik Özgü
 * @date    : 03.03.2022
 *******************/


#ifndef MATRICE_LIBRARY
#define MATRICE_LIBRARY

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

template<typename T>
class Matrice {
private:
    vector<vector<T>> array;
    int r, c;
public:

    Matrice();
    Matrice(int, int);
    Matrice(const Matrice<T>&);

    ~Matrice(){};

    void init(T arr[]);

    Matrice<T> operator*(const Matrice &);
    Matrice<T> operator+(const Matrice &);
    Matrice<T> operator-(const Matrice &);

    void row_col_mul(Matrice<T>&, Matrice<T>, int, int);
    void row_row_sum(Matrice<T>&, Matrice<T>, int);
    void row_row_diff(Matrice<T>&, Matrice<T>, int);

    Matrice<T> t();
    void row_T(Matrice<T>&, int);

    static Matrice<T> eye(int);

    friend ostream & operator << (ostream &out, const Matrice<T>& Mat)
    {
        for (int i=0;i<Mat.r;i++)
        {
            for(int j=0;j<Mat.c;j++)
            {
                out << Mat.array[i][j] << "\t";
            }
            out << endl;
        }
        return out;
    }

};


#endif