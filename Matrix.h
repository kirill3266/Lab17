#ifndef Matrix_h
#define Matrix_h
#include <stdexcept>
#include <iostream>


template <class T>
class matrix {
private:
	T** data;
	size_t rows;
	size_t cols;
public:
	matrix(size_t,size_t);
	matrix(const matrix&);
	size_t get_rows() { return rows; };
	size_t get_cols() { return cols; };
	void set(size_t, size_t, T);
	T& get(size_t, size_t);
	matrix<T>& operator+=(const matrix<T>&);
	matrix<T>& operator=(const matrix<T>&);
    class RowClass:public matrix<T>{ matrix<T>* operator[](const size_t j) {  return matrix<T>::RowClass::data[j];} };
    T operator[](const RowClass& m);
	~matrix() { if (!data || !data[0]) return;
	delete[] data[0];
	data[0] = nullptr;
	delete[] data;
	data = nullptr;
	};
};


template <class T>
matrix<T>::matrix(size_t r,size_t c):rows(r),cols(c){
	data = new T * [r];
	data[0] = new T[r * c];
	for (auto i = 1; i < r; ++i) {
		data[i] = &data[0][i * r];
	}
}

template <class T>
matrix<T>::matrix(const matrix<T>& m) {
	rows = m.rows;
	cols = m.cols;
	data = new T * [rows];
	data[0] = new T[rows * cols];
	for (auto i = 1; i < rows; ++i) {
		data[i] = &data[0][i * rows];
	}
	for (auto i = 0; i < rows * cols; ++i) {
		data[0][i] = m.data[0][i];
	}
}

template <class T>
void matrix<T>::set(size_t r, size_t c, T d) {
	if (r >= rows || c >= cols) {
		throw(std::out_of_range("Invalid index"));
	}
}

template <class T>
T& matrix<T>::get(size_t r, size_t c) {
	if (r >= rows || c >= cols) {
		throw(std::out_of_range("Invalid index"));
	}
	return data[r][c];
}

template <class T>
inline matrix<T>& matrix<T>::operator=(const matrix<T>& m) {
	if (this == &m) return *this;
	delete[] data[0];
	delete[] data;
	rows = m.rows;
	cols = m.cols;
	data = new T * [rows];
	data[0] = new T[rows * cols];
	for (auto i = 1; i < rows; ++i) {
		data[i] = &data[0][i * rows];
	}
	for (auto i = 0; i < rows * cols; ++i) {
		data[0][i] = m.data[0][i];
	}
}

template <class T>
inline matrix<T>& matrix<T>::operator+=(const matrix<T>& m) {
	if (rows != m.rows || cols != m.cols)
		throw (std::invalid_argument("Invalid index"));
	for (auto i = 0; i < rows*cols; ++i) {
		data[0][i] += m.data[0][i];
	}
	return *this;
}

template<class T>
T matrix<T>::operator[](const matrix::RowClass& m) {
    return m.data[i];
}

template <class T>
inline matrix<T> operator+(matrix<T> l, matrix<T>& r) {
	return l += r;
}

template <class T>
inline std::ostream& operator <<(std::ostream& out, matrix<T>& m) {
	for (auto i = 0; i < m.get_rows(); ++i) {
		for (auto j = 0; j < m.get_cols(); ++j) {
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return out;
}

template <class T>
inline std::istream& operator >>(std::istream& out, matrix<T>& m) {
	for (auto i = 0; i < m.get_rows(); ++i) {
		for (auto j = 0; j < m.get_cols(); ++j) {
			std::cin >> m[i][j];
		}		
	}
	return out;
}

#endif
