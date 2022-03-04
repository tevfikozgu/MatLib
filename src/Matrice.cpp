/**
 * @Brief: This Source Code Includes Operations of Matrice Library with Multithreading.
 * @Writer: Tevfik Özgü
 * @Data: 03.03.2022
 */

#include "Matrice.h"

template<typename T>
Matrice<T>::Matrice(int row, int column)
{
    r = row;
    c = column;
    vector<vector<T> > vec(row, vector<T> (column, 0));
    array = vec;
}


template<typename T>
void Matrice<T>::init(T arr[])
{
    for (int i = 0; i<r;i++)
    {
        for (int j = 0; j<c;j++)
        {
            int index   = i * c + j;
            array[i][j] = arr[index];
        }
    }
}


template<typename T>
Matrice<T> Matrice<T>::operator*(const Matrice &Matrice_2)
{
    Matrice <T> multiplicated(this->r, Matrice_2.c);
    vector<std::thread> mul_threads(multiplicated.r * multiplicated.c);

    for (int i = 0; i<r;i++)
        for (int j = 0; j<Matrice_2.c;j++)
            mul_threads[i * Matrice_2.c + j] = thread(&Matrice<T>::row_col_mul, this,
                                               ref(multiplicated), Matrice_2, i, j);

    for (thread &t: mul_threads)
        if (t.joinable())
            t.join();

    return multiplicated;
}
template<typename T>
void Matrice<T>::row_col_mul(Matrice<T>& M1, Matrice<T> M2, int row_idx, int col_idx)
{
    T multip_final = 0;
    for (int i=0;i<M2.r;i++)
        multip_final += this->array[row_idx][i] * M2.array[i][col_idx];
    M1.array[row_idx][col_idx] = multip_final;
}


template<typename T>
Matrice<T> Matrice<T>::operator+(const Matrice &Matrice_2)
{
    Matrice <T> sum_array(this->r, this->c);
    vector<std::thread> sum_threads(r);

    for (int i = 0; i<r;i++)
        sum_threads[i] = thread(&Matrice<T>::row_row_sum, this, ref(sum_array), Matrice_2, i);
    for (thread &t: sum_threads)
        if (t.joinable())
            t.join();
    return sum_array;
}
template<typename T>
void Matrice<T>::row_row_sum(Matrice<T>& M1, Matrice<T> M2, int row_idx)
{
    std::transform(this->array[row_idx].begin(), this->array[row_idx].end(),
                   M2.array[row_idx].begin(), M1.array[row_idx].begin(), std::plus<T>());
}


template<typename T>
Matrice<T> Matrice<T>::operator-(const Matrice &Matrice_2)
{
    Matrice <T> diff_array(this->r, this->c);
    vector<std::thread> diff_threads(r);
    for (int i = 0; i<r;i++)
        diff_threads[i] = thread(&Matrice<T>::row_row_diff, this, ref(diff_array), Matrice_2, i);

    for (thread &t: diff_threads)
        if (t.joinable())
            t.join();

    return diff_array;
}
template<typename T>
void Matrice<T>::row_row_diff(Matrice<T>& M1, Matrice<T> M2, int row_idx)
{
    std::transform(this->array[row_idx].begin(), this->array[row_idx].end(),
                   M2.array[row_idx].begin(), M1.array[row_idx].begin(), std::minus<T>());
}

