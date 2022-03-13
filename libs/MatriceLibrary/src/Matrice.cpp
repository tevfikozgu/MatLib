/**
 * @brief   : This Source Code Includes Operations of Matrice Library with Multithreading.
 * @author  : Tevfik Özgü
 * @date    : 03.03.2022
 */

#include "../include/Matrice.h"

/**
 * @brief    : Default Constructor
 * @tparam T : Type of Matrice Elements
 */
template<typename T>
Matrice<T>::Matrice()
{
    r = 0;
    c = 0;
    vector<vector<T>> vec;
    array = vec;
}

/**
 * @brief         : Creates Zeros Matrice with dimension (size, size).
 * @tparam T      : Type of Matrice Elements
 * @param row     : Row dimension of Matrice,
 * @param column  : Column dimension of Matrice,
 */
template<typename T>
Matrice<T>::Matrice(int row, int column)
{
    r = row;
    c = column;
    vector<vector<T> > vec(row, vector<T> (column, 0));
    array = vec;
}

/**
 * @brief      : Copy Constructor that copies one matrice to another.
 * @tparam T   : Type of Matrice Elements
 * @param size : Right Matrice of = operator.
 */
template<typename T>
Matrice<T>::Matrice(const Matrice<T>& Matrice_Old)
{
    this->array = Matrice_Old.array;
    this->r     = Matrice_Old.r;
    this->c     = Matrice_Old.c;
}


/**
 * @brief           : Overloading of << operator.
 * @tparam T        : Type of Matrice Elements
 * @param value     : Value which will be assigned to indice.
 * @return          : Reference to current assigned matrice.
 */
template<typename T>
Matrice<T>& Matrice<T>::operator<<(T value)
{
    this->array[r_curr][c_curr] = value;
    return *this;
}


/**
 * @brief           : Overloading of , operator.
 * @tparam T        : Type of Matrice Elements
 * @param value     : Value which will be assigned to indice.
 * @return          : Reference to current assigned matrice.
 */
template<typename T>
Matrice<T>& Matrice<T>::operator,(T value)
{
    if (c_curr == c - 1) {
        r_curr += 1;
        c_curr = 0;
    } else{
        c_curr += 1;
    }
    this->array[r_curr][c_curr] = value;
    return *this;
}


/**
 * @brief      : Initializes array with given array
 * @tparam T   : Type of Matrice Elements
 * @param arr  : Array which is initalized to Matrice object.
 */
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


/**
 * @brief           : Overloading of * operator.
 * @note            : There is a multithreaded system.
 * @tparam T        : Type of Matrice Elements
 * @param Matrice_2 : Right Matrice of * operator.
 * @return          : Multiplication of 2 matrices which is a matrice.
 */
template<typename T>
Matrice<T> Matrice<T>::operator*(const Matrice &Matrice_2)
{

    if (this->c != Matrice_2.r)
    {
        std::cerr << " Column size of First matrice must be same with Row Size of Second Matrice! " << std::endl;
        abort();
    }

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


/**
 * @brief           : Overloading of + operator.
 * @note            : There is a multithreaded system.
 * @tparam T        : Type of Matrice Elements
 * @param Matrice_2 : Right Matrice of + operator.
 * @return          : Summation of 2 matrices which is a matrice.
 */
template<typename T>
Matrice<T> Matrice<T>::operator+(const Matrice &Matrice_2)
{

    if (this->r != Matrice_2.r || this->c != Matrice_2.c)
    {
        std::cerr << " Matrice Sizes Must Be Same! " << std::endl;
        abort();
    }

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


/**
 * @brief           : Overloading of - operator.
 * @note            : There is a multithreaded system.
 * @tparam T        : Type of Matrice Elements
 * @param Matrice_2 : Right Matrice of - operator.
 * @return          : Subtraction of 2 matrices which is a matrice.
 */
template<typename T>
Matrice<T> Matrice<T>::operator-(const Matrice &Matrice_2)
{
    if (this->r != Matrice_2.r || this->c != Matrice_2.c)
    {
        std::cerr << " Matrice Sizes Must Be Same! " << std::endl;
        abort();
    }

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

/**
 * @brief      : This function returns Transpose of Matrice
 * @note       : There is a multithreaded system.
 * @tparam T   : Type of Matrice Elements
 * @return     : Tranpose of Current Matrice
 */
template<typename T>
Matrice<T> Matrice<T>::t()
{
    Matrice <T> transpose(this->c, this->r);
    vector<std::thread> transpose_threads(r);
    for (int i = 0; i<r;i++)
        transpose_threads[i] = thread(&Matrice<T>::row_T, this, ref(transpose), i);

    for (thread &t: transpose_threads)
        if (t.joinable())
            t.join();
    return transpose;
}
template<typename T>
void Matrice<T>::row_T(Matrice<T>& M1, int row_idx)
{
    for (int c_idx=0; c_idx < this->c; c_idx++)
        M1.array[c_idx][row_idx] = this->array[row_idx][c_idx];
}


/**
 * @brief      : Creates Identity Matrice with dimension (size, size).
 * @note       : There is no multihread, because it is slower.
 * @tparam T   : Type of Matrice Elements
 * @param size : Dimensions of Matrice
 * @return     : Identity Matrice with dimension of (size, size)
 */
template<typename T>
Matrice<T> Matrice<T>::eye(int size)
{
    Matrice <T> M(size, size);
    for (int i = 0; i<size;i++)
        M.array[i][i] = 1;
    return M;
}


/*********** Functions For Finding Inverse Of A Matrice ****************/
template<typename T>
void Matrice<T>::get_cofactor(Matrice<T> &A,Matrice<T> &temp, int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp.array[i][j++] = A.array[row][col];
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

template<typename T>
T Matrice<T>::determinant(Matrice<T>& A, int n)
{

    T D = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return A.array[0][0];

    Matrice<T> temp_mat(r,c); // To store cofactors

    int sign = 1;  // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        get_cofactor(A, temp_mat, 0, f, n);

        D += sign * A.array[0][f] * determinant(temp_mat, n-1);
        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;

}

template<typename T>
Matrice<T> Matrice<T>::adjoint()
{
    Matrice<T> adjoint_mat(r,c);
    Matrice<T> temp_mat(r,c);
    if (r == 1)
    {
        adjoint_mat.array[0][0] = 1;
        return adjoint_mat;
    }

    // temp is used to store cofactors of A[][]
    int sign;

    for (int i=0; i<r; i++)
    {
        for (int j=0; j<c; j++)
        {
            // Get cofactor of A[i][j]
            get_cofactor(*this,temp_mat, i, j, r);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adjoint_mat.array[j][i] = (sign)*(determinant(temp_mat, r-1));
        }
    }
    return adjoint_mat;
}

template<typename T>
Matrice<T> Matrice<T>::inv() {

    if (r != c)
    {
        cout << " Cannot Take Inverse of a Non-Square Matrice! " << endl;
        abort();
    }

    T det = determinant(*this, r);
    if (det == 0)
    {
        cerr << "Singular matrix, can't find its inverse" << endl;
        abort();
    }

    Matrice<T> adjoint_mat = adjoint();

    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<r; i++)
        for (int j=0; j<c; j++)
            inverse_mat.array[i][j] = adjoint_mat.array[i][j] / float(det);

    return inverse_mat;
}
