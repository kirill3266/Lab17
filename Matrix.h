#ifndef Matrix_h
#define Matrix_h

#include <stdexcept>
#include <iostream>
#include <math.h>
#include <memory>


template<class T>
class matrix {
private:
    T **data;
    size_t rows;
    size_t cols;
public:
    matrix(size_t, size_t);

    matrix(const matrix &);

    size_t get_rows() { return rows; };

    size_t get_cols() { return cols; };

    T get_data(size_t i, size_t j) { return data[i][j]; }

    void set(size_t, size_t, T);

    T &get(size_t, size_t);

    matrix<T> &operator+=(const matrix<T> &);

    matrix<T> &operator=(const matrix<T> &);

    T *operator[](size_t j);

    const T *operator[](size_t j) const;

    ~matrix() {
        if (!data || !data[0]) return;
        delete[] data[0];
        data[0] = nullptr;
        delete[] data;
        data = nullptr;
    };
};

template<class T>
matrix<T>::matrix(size_t r, size_t c):rows(r), cols(c) {
    data = new T *[r];
    data[0] = new T[r * c];
    for (auto i = 1; i < r; ++i) {
        data[i] = &data[0][i * r];
    }

    for(auto i=0;i<r;++i)
        for(auto j=0;j<c;++j)
        data[i][j] = 0;
}

template<class T>
matrix<T>::matrix(const matrix<T> &m) {
    rows = m.rows;
    cols = m.cols;
    data = new T *[rows];
    data[0] = new T[rows * cols];
    for (auto i = 1; i < rows; ++i) {
        data[i] = &data[0][i * rows];
    }
    for (auto i = 0; i < rows * cols; ++i) {
        data[0][i] = m.data[0][i];
    }
}

template<class T>
void matrix<T>::set(size_t r, size_t c, T d) {
    if (r >= rows || c >= cols) {
        throw (std::out_of_range("Invalid index"));
    }
    data[r][c] = d;
}

template<class T>
T &matrix<T>::get(size_t r, size_t c) {
    if (r >= rows || c >= cols) {
        throw (std::out_of_range("Invalid index"));
    }
    return data[r][c];
}

template<class T>
inline matrix<T> &matrix<T>::operator=(const matrix<T> &m) {
    if (this == &m) return *this;
    delete[] data[0];
    delete[] data;
    rows = m.rows;
    cols = m.cols;
    data = new T *[rows];
    data[0] = new T[rows * cols];
    for (auto i = 1; i < rows; ++i) {
        data[i] = &data[0][i * rows];
    }
    for (auto i = 0; i < rows * cols; ++i) {
        data[0][i] = m.data[0][i];
    }
}

template<class T>
inline matrix<T> &matrix<T>::operator+=(const matrix<T> &m) {
    if (rows != m.rows || cols != m.cols)
        throw (std::invalid_argument("Invalid index"));
    for (auto i = 0; i < rows * cols; ++i) {
        data[0][i] += m.data[0][i];
    }
    return *this;
}

template<class T>
inline matrix<T> operator+(matrix<T> l, matrix<T> &r) {
    return l += r;
}

template<class T>
T *matrix<T>::operator[](size_t j) {
    return data[j];
}

template<class T>
const T *matrix<T>::operator[](size_t j) const {
    return data[j];
}

template<class T>
inline std::ostream &operator<<(std::ostream &out, matrix<T> &m) {
    for (auto i = 0; i < m.get_rows(); ++i) {
        for (auto j = 0; j < m.get_cols(); ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return out;
}

template<class T>
inline std::istream &operator>>(std::istream &out, matrix<T> &m) {
    for (auto i = 0; i < m.get_rows(); ++i) {
        for (auto j = 0; j < m.get_cols(); ++j) {
            std::cin >> m[i][j];
        }
    }
    return out;
}

template<class T>
matrix<T> transpose( matrix<T> mat) {
    matrix<T> n = mat;
    for (int i = 0; i < mat.get_rows(); ++i)
        for (int j = 0; j < mat.get_cols(); ++j)
            n[i][j] = mat[j][i];
    return n;
}

template<class T>
int findDet(matrix<T> mat, int n) {
    if (n == 1)
        return mat[0][0];
    else if (n == 2)
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    else {
        T d = 0;
        for (int k = 0; k < n; k++) {
            matrix<T> b(n - 1, n - 1);
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == k)
                        continue;
                    else if (j < k)
                        b[i - 1][j] = mat[i][j];
                    else
                        b[i - 1][j - 1] = mat[i][j];
                }
            }
            d += pow(-1, k + 2) * mat[0][k] * findDet(b, n - 1);
        }
        if(d==0) throw std::invalid_argument("Determinant is zero!\n");
        return d;
    }
}

template<class T>
matrix<T> Minor(matrix<T> mat) {
    size_t r = mat.get_rows();
    size_t c = mat.get_cols();
    //создание выходной матрицы
matrix<T> out(r,r);

    size_t tmp_col = 0;
    size_t tmp_row = 0;
    matrix<T>* tmp;
    //row's and cols of perebor
    for (int row = 0; row < r; ++row)
        for (int col = 0; col < c; ++col) {
            //создание матрицы миноров
            tmp = new matrix<T>(r - 1, r - 1);
            tmp_col = 0;
            tmp_row = 0;
            //перебор матрицы для того, чтобы впихнуть значения в матрицу миноров
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++) {
                    if (j == col) continue;
                    if (i == row) break;
                    tmp->set(tmp_row,tmp_col++,mat[i][j]);
                    if (tmp_col == r-1) {
                        tmp_row++;
                        tmp_col = 0;
                    }
                }
//            std::cout <<"Tmp is:\n" << *tmp;
//                std::cout << "TmpDet is:\n" << findDet(*tmp,r-1) << std::endl;
            //счёт определителей и запихивание их в матрицу алгебраических дополнений
            out.set(row,col,pow(-1,row+col+2)*findDet(*tmp,r-1));
                delete tmp;
        }
    std::cout << "Minor is:\n" << out;
    return out;
}

template<class T>
void findBack(matrix<T> mat) {
    size_t r = mat.get_rows();
    size_t c = mat.get_cols();
    if (c != r || r < 2) throw (std::invalid_argument("mat.Rows!=mat.Cols || mat.Rows<2!"));
    matrix<double> out(mat.get_rows(),mat.get_cols());
    matrix<T> tmp = transpose(Minor(mat));;
    double det = (double)1/findDet(tmp,out.get_rows());
    for(auto i=0;i<out.get_rows();++i)
        for(auto j=0;j<out.get_cols();++j) {
            out.set(i, j, tmp.get(i, j) * det);
        }
    std::cout << "Backward is: \n" << out;
}

#endif
