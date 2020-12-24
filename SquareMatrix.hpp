#pragma once

#include <stdexcept>

template<typename T>
class SquareMatrix {
private:
    T** ptr;
    size_t _size;

public:
    //default constructor
    SquareMatrix();
    //big five
    ~SquareMatrix();
    SquareMatrix(const SquareMatrix& matrix);
    SquareMatrix(SquareMatrix&& matrix);
    SquareMatrix& operator=(const SquareMatrix& rhs);
    SquareMatrix& operator=(SquareMatrix&& rhs);
    //methods
    void resize(size_t new_size);
    bool operator==(const SquareMatrix& rhs);
    SquareMatrix& operator+(const SquareMatrix& rhs);
    T& at(size_t row, size_t column);
    size_t size() const;
};

//default constructor
template<typename T>
SquareMatrix<T>::SquareMatrix() : ptr(nullptr), _size(0) {}

//destructor
template<typename T>
SquareMatrix<T>::~SquareMatrix() {
    for (int i{ 0 }; i < _size; i++) {
        delete[] ptr[i];
    }
    delete[] ptr;
}

//copy constructor
template<typename T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& matrix):
    ptr(matrix.ptr), _size(matrix._size) {
    //exit if the copied matrix is empty
    if (matrix.ptr == nullptr) {
        return;
    }
    //fill the matrix with the values from the copied matrix
    ptr = new T*[_size];
    for (int i{ 0 }; i < _size; i++) {
        ptr[i] = new T[_size];
        for (int j{ 0 }; j < _size; j++) {
            ptr[i][j] = matrix.ptr[i][j];
        }
    }
}

//move constructor
template<typename T>
SquareMatrix<T>::SquareMatrix(SquareMatrix<T>&& matrix):
    ptr(matrix.ptr), _size(matrix._size) {
    //free the pointer of the copied matrix
    matrix.ptr = nullptr;
    matrix._size = 0;
}

//assignment operator
template<typename T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix<T>& rhs) {
    //exit if the the matrices are the same matrix
    if (this == &rhs) {return *this;}
    //destroy content of lhs and release all memory
    if (ptr != nullptr) {
        for (int i{ 0 }; i < _size; i++) {
            delete[] ptr[i];
        }
        delete[] ptr;
    }
    //assignment new value to lhs from rhs
    ptr = new T*[rhs._size];
    _size = rhs._size;
    for (int i{ 0 }; i < _size; i++) {
        ptr[i] = new T[_size];
        for (int j{ 0 }; j < _size; j++) {
            ptr[i][j] = rhs.ptr[i][j];
        }
    }
    return *this;
}

//move assignment operator
template<typename T>
SquareMatrix<T>& SquareMatrix<T>::operator=(SquareMatrix<T>&& rhs) {
    //exit if the the matrices are the same matrix
    if (ptr == rhs.ptr) {return *this;}
    //destroy content of lhs and release all memory
    if (ptr != nullptr) {
        for (int i{ 0 }; i < _size; i++) {
            delete[] ptr[i];
        }
        delete[] ptr;
    }
    //take the matrix from rhs directly and free the ptr of rhs
    ptr = rhs.ptr;
    _size = rhs._size;
    rhs.ptr = nullptr;
    rhs._size = 0;
    return *this;
}

//resize
template<typename T>
void SquareMatrix<T>::resize(size_t new_size) {
    //destroy all the original content and release memory
    for (int i{ 0 }; i < _size; i++) {
        delete[] ptr[i];
    }
    delete[] ptr;
    //resize the matrix and fill it with random values
    _size = new_size;
    ptr = new T*[_size];
    for (int i{ 0 }; i < _size; i++) {
        ptr[i] = new T[_size];
        for (int j{ 0 }; j < _size; j++) {
            T element;
            ptr[i][j] = element;
        }
    }
}

//comparison with ==
template<typename T>
bool SquareMatrix<T>::operator==(const SquareMatrix<T>& rhs) {
    //return false if the sizes are different
    if (_size != rhs._size) {return false;}
    //compare the values of every element
    for (int i{ 0 }; i < _size; i++) {
        for (int j{ 0 }; j < _size; j++) {
            if (ptr[i][j] != rhs.ptr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

//+ operator
template<typename T>
SquareMatrix<T>& SquareMatrix<T>::operator+(const SquareMatrix<T>& rhs) {
    //create a new matrix and fill it with the sum of the two matrices
    static SquareMatrix<T> newMatrix;
    newMatrix.ptr = new T*[_size];
    newMatrix._size = _size;
    for (int i{ 0 }; i < _size; i++) {
        newMatrix.ptr[i] = new T[_size];
        for (int j{ 0 }; j < _size; j++) {
            newMatrix.ptr[i][j] = ptr[i][j] + rhs.ptr[i][j];
        }
    }
    //return a reference to the new matrix
    return newMatrix;
}

//at method
template<typename T>
T& SquareMatrix<T>::at(size_t row, size_t column) {
    //throw error if out of bound
    if (row >= _size || column >= _size) {
        throw std::out_of_range("The given position is out of range.");
    } else {
    //return reference to the element at the given position
        return ptr[row][column];
    }
}

//size method
template<typename T>
size_t SquareMatrix<T>::size() const {
    return _size;
}
