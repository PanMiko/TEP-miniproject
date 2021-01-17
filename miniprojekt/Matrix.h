#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iomanip>

#include "ErrorsMessages.h"
#include "MyExcepiton.h"

#define DEFAULT_SIZE 5

//*****************************************************************************
//									HEADER
//*****************************************************************************
template<typename T>
class Matrix {
private:
	T** matrix;
	int rowsNumber;
	int colsNumber;

	void copyFields(const Matrix<T>& other);
	void deleteFields();
	void toMove(Matrix<T>& other);
	void initializeFields(int rows, int cols);

public:
//=============================================================================
//							CONSTRUCTORS & DESTRUCTOR
//=============================================================================
	// default constructor
	Matrix();

	// constructor with parameters
	Matrix(int rowsNumber, int colsNumber = 1, int* error = 0);

	// copy constructor 
	Matrix(const Matrix<T>& other);

	// move constructor
	Matrix(Matrix<T>&& other) noexcept;

	// destructor
	~Matrix();

//=============================================================================
//								   OPERATORS
//=============================================================================
	// operator=
	Matrix<T>& operator=(const Matrix<T>& other);

	// move operator=
	Matrix<T>& operator=(Matrix<T>&& other) noexcept;

	// operator+
	Matrix<T> operator+(const Matrix<T>& other);

	// operator-
	Matrix<T> operator-(const Matrix<T>& other);

	// operator* by number
	Matrix<T> operator*(const T number);

	// operator* by other matrix
	Matrix<T> operator*(const Matrix<T>& other);

	// operator()
	T operator()(int row, int col);

//=============================================================================
//									METHODS
//=============================================================================

	// adding two matrices and returning new Matrix / operator+
	Matrix<T> addByMatrix(const Matrix<T>& other, int* error = 0);

	// subtracting two matrices and returning new Matrix / operator-
	Matrix<T> substractByMatrix(const Matrix<T>& other, int* error = 0);

	// multiplying Matrix by number / operator* by number
	Matrix<T> multiplyByNumber(const T number, int* error = 0);
	
	// multiplying Matrix by number / operator* by number
	Matrix<T> multiplyByOtherMatrix(const Matrix<T>& other, int* error = 0);

	// getting element on [row][col] in matrix / operator()
	T getElementOn(int row, int col, int* error = 0);

	// setting element on [row][col] in matrix
	bool setElementOn(T newElement, int row, int col, int* error = 0);

	// creating and returning new Matrix based on a ROW, that will be a vector
	Matrix<T> createVectorFromRow(int row, int* error = 0);

	// creating and returning new Matrix based on a COLUMN, that will be a vector
	Matrix<T> createVectorFromColumn(int col, int* error = 0);

	// calculating the scalar product
	T scalarProduct(Matrix<T>& other, int* error = 0);

	// checking if matrix is a vector
	bool isVector();

	// matrix transposition
	Matrix<T>& transpose(int *error = 0);

	// square matrix => identity matrix
	Matrix<T>& modifyToIdentityMatrix(int *error = 0);

	// reading from file and saving it to Matrix
	Matrix<T>& readFromFileAndSave(std::string fileName, int* error = 0);

	//getters & helper methods
	int getRowsNumber();

	int getColsNumber();

	void print(int *error = 0);

	void fill(int* error = 0);
};


















//*****************************************************************************
//*****************************************************************************
//								IMPLEMENTATIONS
//*****************************************************************************
//*****************************************************************************





















//=============================================================================
//							CONSTRUCTORS & DESTRUCTOR
//=============================================================================

// default constructor
template<typename T>
Matrix<T>::Matrix() {
	initializeFields(DEFAULT_SIZE, DEFAULT_SIZE);
	/*rowsNumber = DEFAULT_SIZE;
	colsNumber = DEFAULT_SIZE;

	matrix = new T * [DEFAULT_SIZE];

	for (int i = 0; i < DEFAULT_SIZE; i++) {
		matrix[i] = new T[DEFAULT_SIZE];
	}*/
}

// constructor with parameters
template<typename T>
Matrix<T>::Matrix(int rowsNumber, int colsNumber, int* error) {
	// error
	if (rowsNumber <= 0 || colsNumber <= 0) {
		matrix = nullptr;
		rowsNumber = -1;
		colsNumber = -1;

		if (error != nullptr) *error = MATRIX_ILLEGAL_ARGUMENTS;
	}

	// NO error
	else {
		initializeFields(rowsNumber, colsNumber);
		/*matrix = new T * [rowsNumber];
		this->rowsNumber = rowsNumber;
		this->colsNumber = colsNumber;

		for (int i = 0; i < rowsNumber; i++) {
			matrix[i] = new T[colsNumber];
		}*/
	}
}

// copy constructor 
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
	copyFields(other);
}


// move constructor
template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept {
	toMove(other);
}


// destructor
template<typename T>
Matrix<T>::~Matrix() {
	deleteFields();
}

//=============================================================================
//								   OPERATORS
//=============================================================================

// operator=
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
	if (this != &other) {
		deleteFields();
		
		copyFields(other);
	}

	return *this;
}

// move operator=
template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept {
	if (this != &other) {
		deleteFields();

		toMove(other);
	}

	return *this;
}

// operator+
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
	int error = 0;

	Matrix<T> result = addByMatrix(other, &error);

	if (error != 0 || result.matrix == nullptr || matrix == nullptr || other.matrix == nullptr) throw MyExcepiton();
	
	else return std::move(result);
}

// operator-
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
	int error = 0;

	Matrix<T> result = substractByMatrix(other, &error);

	if (error != 0 || result.matrix == nullptr || matrix == nullptr || other.matrix == nullptr) throw MyExcepiton();

	else return std::move(result);
}

// operator* by number
template<typename T>
Matrix<T> Matrix<T>::operator*(const T number) {
	int error = 0;

	Matrix<T> result = multiplyByNumber(number, &error);

	if (error != 0 || result.matrix == nullptr || matrix == nullptr) throw MyExcepiton();

	else return std::move(result);
}

// operator* by other matrix
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
	int error = 0;

	Matrix<T> result = multiplyByOtherMatrix(other, &error);

	if (error != 0 || result.matrix == nullptr || matrix == nullptr) throw MyExcepiton();

	return std::move(result);
}

// operator()
template<typename T>
T Matrix<T>::operator() (int row, int col) {
	int error = 0;

	if (row < 0 || col < 0 || row >= rowsNumber || col >= colsNumber || matrix == nullptr) throw MyExcepiton();

	T result = getElementOn(row, col, &error);

	if (error != 0) throw MyExcepiton();

	return result;
}

//=============================================================================
//									METHODS
//=============================================================================

// adding matrices
template<typename T>
Matrix<T> Matrix<T>::addByMatrix(const Matrix<T>& other, int* error) {
	Matrix<T> sum(rowsNumber, colsNumber);

	// error
	if (matrix == nullptr || other.matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		return *this;
	}
	// error
	else if (rowsNumber != other.rowsNumber || colsNumber != other.colsNumber) {
		if (error != nullptr) *error = MATRICES_DIFFRENT_DIMESIONS_FOR_ADD_OR_SUB;
		return *this;
	}
	// NO error
	else {
		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				sum.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
			}
		}

		return std::move(sum);
	}
}

// substracting matrices
template<typename T>
Matrix<T> Matrix<T>::substractByMatrix(const Matrix<T>& other, int* error) {
	Matrix<T> sub(rowsNumber, colsNumber);

	// error
	if (matrix == nullptr || other.matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		return *this;
	}
	// error
	else if (rowsNumber != other.rowsNumber || colsNumber != other.colsNumber) {
		if (error != nullptr) *error = MATRICES_DIFFRENT_DIMESIONS_FOR_ADD_OR_SUB;
		return *this;
	}
	// NO error
	else {
		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				sub.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
			}
		}

		return std::move(sub);
	}
}

// multyplying matrix by number
template<typename T>
Matrix<T> Matrix<T>::multiplyByNumber(const T number, int* error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		return *this;
	}

	// NO error
	for (int i = 0; i < rowsNumber; i++) {
		for (int j = 0; j < colsNumber; j++) {
			matrix[i][j] *= number;
		}
	}

	return *this;
}

// multiplying matrix by other matrix
template<typename T>
Matrix<T> Matrix<T>::multiplyByOtherMatrix(const Matrix<T>& other, int* error) {
	// error
	if (matrix == nullptr || other.matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		return *this;
	}
	// error
	else if (colsNumber != other.rowsNumber) {
		if (error != nullptr) *error = MATRICES_DIFFRENT_DIMESIONS_FOR_MUL;
		return *this;
	}
	// NO error
	else {
		Matrix<T> result(rowsNumber, other.colsNumber);

		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < other.colsNumber; j++) {
				result.matrix[i][j] = 0;

				for (int k = 0; k < colsNumber; k++) {
					result.matrix[i][j] = (matrix[i][k] * other.matrix[k][j]) + result.matrix[i][j];
				}
			}
		}

		return std::move(result);
	}
}

// getting element on [row][col]
template<typename T>
T Matrix<T>::getElementOn(int row, int col, int *error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		return matrix[0][0];
	}
	// error
	else if (row < 0 || col < 0 || row >= rowsNumber || col >= colsNumber) {
		if (error != nullptr) *error = MATRIX_ILLEGAL_ARGUMENTS;
		return matrix[0][0];
	}
	// NO error
	return matrix[row][col];
}

// setting newElement on [row][col]
template<typename T>
bool Matrix<T>::setElementOn(T newElement, int row, int col, int *error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		return false;
	}
	// error
	else if (row < 0 || col < 0 || row >= rowsNumber || col >= colsNumber) {
		if (error != nullptr) *error = MATRIX_ILLEGAL_ARGUMENTS;
		return false;
	}
	// NO error
	matrix[row][col] = newElement;

	return matrix[row][col] == newElement;
}

// creating new vector-matrix from row
template<typename T>
Matrix<T> Matrix<T>::createVectorFromRow(int row, int* error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		return *this;
	}
	// error
	else if (row < 0 || row >= rowsNumber) {
		if (error != nullptr) *error = MATRIX_ILLEGAL_ARGUMENTS;
		return *this;
	}
	// NO error
	else {
		Matrix<T> result(1, colsNumber);

		for (int i = 0; i < colsNumber; i++) {
			result.matrix[0][i] = matrix[row][i];
		}

		return std::move(result);
	}
}

// creating new vector-matrix from column
template<typename T>
Matrix<T> Matrix<T>::createVectorFromColumn(int col, int* error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		return *this;
	}
	// error
	else if (col < 0 || col >= colsNumber) {
		if (error != nullptr) *error = MATRIX_ILLEGAL_ARGUMENTS;
		return *this;
	}
	// NO error
	else {
		Matrix<T> result(1, rowsNumber);

		for (int i = 0; i < rowsNumber; i++) {
			result.matrix[0][i] = matrix[i][col];
		}

		return std::move(result);
	}
}

// calculating scalar product of two matrices
template<typename T>
T Matrix<T>::scalarProduct(Matrix<T>& other, int* error) {
	T result = 0;

	// error
	if (matrix == nullptr || other.matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
	}
	// NO error
	else if (this->isVector() && other.isVector()) {
		bool changeOn1 = false;
		bool changeOn2 = false;

		if (colsNumber == 1) {
			this->transpose();
			changeOn1 = true;
		}

		if (other.colsNumber == 1) {
			other.transpose();
			changeOn2 = true;
		}

		//error
		if (colsNumber != other.colsNumber) {
			if (error != nullptr) *error = MATRICES_DIFFRENT_DIMESIONS_FOR_SCALAR_PRODUCT;
		}

		else {
			for (int i = 0; i < colsNumber; i++) {
				result += matrix[0][i] * other.matrix[0][i];
			}

			if (changeOn1) this->transpose();
			if (changeOn2) other.transpose();
		}
	}
	// error
	else {
		if (error != nullptr) *error = MATRICES_ARE_NOT_VECTORS;
	}
	
	return result;
}

// checking if matrix is a vector 
template<typename T>
bool Matrix<T>::isVector() {
	return rowsNumber == 1 || colsNumber == 1;
}

// matrix transposition
template<typename T>
Matrix<T>& Matrix<T>::transpose(int *error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
	}
	// NO error
	else {
		Matrix<T> result(colsNumber, rowsNumber);

		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				result.matrix[j][i] = matrix[i][j];
			}
		}

		deleteFields();

		initializeFields(result.rowsNumber, colsNumber);

		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				matrix[i][j] = result.matrix[i][j];
			}
		}
	}

	return *this;
}

// square matrix => identity matrix
template<typename T>
Matrix<T>& Matrix<T>::modifyToIdentityMatrix(int *error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
	}
	else if (rowsNumber != colsNumber) {
		if (error != nullptr) *error = MATRIX_IS_NOT_SQUARE;
	}
	// NO error
	else {
		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				if (i == j) matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
		}
	}

	return *this;
}

// reading from file and saving it to Matrix
template<typename T>
Matrix<T>& Matrix<T>::readFromFileAndSave(std::string fileName, int* error) {
	std::string number;
	std::ifstream myFile(fileName);

	std::vector<double> nums;

	int rows = 0;
	int cols = 0;

	double x;

	// NO error
	if (myFile.is_open()) {
		while (std::getline(myFile, number)) {
			std::stringstream stream(number);
			while (stream >> x) {
				nums.push_back(x);
			}
			rows++;
		}
		myFile.close();

		cols = nums.size() / rows;

		deleteFields();

		initializeFields(rows, cols);

		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				matrix[i][j] = nums[colsNumber * i + j];
			}
		}
	}
	// error
	else {
		if (error != nullptr) *error = CANNOT_OPEN_FILE;
	}

	return *this;
}

// getter of rowsNumber
template<typename T>
int Matrix<T>::getRowsNumber() {
	return rowsNumber;
}

// getter of colsNumber
template<typename T>
int Matrix<T>::getColsNumber() {
	return colsNumber;
}

// private copying method
template<typename T>
void Matrix<T>::copyFields(const Matrix<T>& other) {
	rowsNumber = other.rowsNumber;
	colsNumber = other.colsNumber;

	matrix = new T * [rowsNumber];

	for (int i = 0; i < rowsNumber; i++) {
		matrix[i] = new T[colsNumber];
	}

	for (int i = 0; i < rowsNumber; i++) {
		for (int j = 0; j < colsNumber; j++) {
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

// private copying method
template<typename T>
void Matrix<T>::deleteFields() {
	if (matrix != nullptr) {
		for (int i = 0; i < rowsNumber; i++) {
			delete[] matrix[i];
		}

		delete[] matrix;
	}
}

// private copying method
template<typename T>
void Matrix<T>::toMove(Matrix<T>& other) {
	matrix = other.matrix;
	rowsNumber = other.rowsNumber;
	colsNumber = other.colsNumber;

	other.matrix = nullptr;
	other.rowsNumber = -1;
	other.colsNumber = -1;
}

// private initialize mehtod
template<typename T>
void Matrix<T>::initializeFields(int rows, int cols) {
	rowsNumber = rows;
	colsNumber = cols;

	matrix = new T * [rowsNumber];

	for (int i = 0; i < rowsNumber; i++) {
		matrix[i] = new T[colsNumber];
	}
}

// printing rowsNumber, colsNumber and matrix
template<typename T>
void Matrix<T>::print(int* error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
		std::cout << "\nMATRIX IS NULL!\n";
	}

	// NO error
	else {
		std::cout << "\nrows: " << rowsNumber << " | cols: " << colsNumber << '\n';

		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << '\n';
		}
	}
}

// filling matrix of init numbers
template<typename T>
void Matrix<T>::fill(int *error) {
	// error
	if (matrix == nullptr) {
		if (error != nullptr) *error = MATRIX_IS_NULL;
	}
	// NO error
	else {
		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				matrix[i][j] = (T)(colsNumber * i + j + 1);
			}
		}
	}
};