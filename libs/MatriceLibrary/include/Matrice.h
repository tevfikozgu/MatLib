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
    int r{}, c{};
    int r_curr{}, c_curr{};
public:

    Matrice();
    Matrice(int, int);
    Matrice(const Matrice<T>&);

    ~Matrice() = default;

    void init(T arr[]);

    Matrice<T>  operator*(const Matrice &);
    Matrice<T>  operator+(const Matrice &);
    Matrice<T>  operator-(const Matrice &);
    Matrice<T>& operator<<(T);
    Matrice<T>& operator,(T);

private:
    void row_col_mul(Matrice<T>&, Matrice<T>, int, int);
    void row_row_sum(Matrice<T>&, Matrice<T>, int);
    void row_row_diff(Matrice<T>&, Matrice<T>, int);
    void row_T(Matrice<T>&, int);

public:
    Matrice<T>        t();
    static Matrice<T> eye(int);
    Matrice<T>        inv();
    T                 det();
private:

    T          determinant(Matrice<T>&, int);
    Matrice<T> adjoint();
    void       get_cofactor(Matrice<T> &,Matrice<T>&, int, int, int);

public:
    friend ostream & operator << (ostream &out, const Matrice<T>& Mat)
    {
        for (int i=0;i<Mat.r;i++)
        {
            for(int j=0;j<Mat.c;j++)
                out << Mat.array[i][j] << "\t";
            out << endl;
        }
        return out;
    }

};


#endif