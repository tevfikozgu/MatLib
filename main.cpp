#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

template <typename T>
class Matrice
{
private:
    vector<vector<T>> array;
    int r,c;
public:
    Matrice(int, int);
    void init(T arr[]);
    Matrice<T> operator*(const Matrice&);
    void row_col_mul(Matrice<T>&, Matrice<T>,int, int);
};

template<typename T>
Matrice<T>::Matrice(int row, int column)
{
    r = row;
    c = column;
    vector<vector<T>> vec(row, vector<T> (column, 0));
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
    vector<std::thread> mul_threads;

    for (int i = 0; i<r;i++)
        for (int j = 0; j<Matrice_2.c;j++)
            mul_threads.push_back(thread(&Matrice<T>::row_col_mul, this,
                                  ref(multiplicated), Matrice_2, i, j));

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
