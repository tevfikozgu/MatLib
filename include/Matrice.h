//
// Created by Tevfik Özgü on 3.03.2022.
//

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
    vector<vector<T> > array;
    int r, c;
public:
    Matrice(int, int);

    void init(T arr[]);

    Matrice<T> operator*(const Matrice &);

    void row_col_mul(Matrice<T> &, Matrice<T>, int, int);

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