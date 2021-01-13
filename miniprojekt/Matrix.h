#pragma once
#include <iostream>

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

public:
//=============================================================================
//							CONSTRUCTORS & DESTRUCTOR
//=============================================================================
	// default constructor
	Matrix();

	// constructor with parameters
	Matrix(int rowsNumber, int colsNumber = 1);

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

	// operator*
	// ?? operator[] / [][]

//=============================================================================
//									METHODS
//=============================================================================

	// adding two matrices and returning new Matrix
	Matrix<T> addByMatrix(const Matrix<T>& other);

	// subtracting two matrices and returning new Matrix
	Matrix<T> subByMatrix(const Matrix<T>& other);

	// creating and returning new Matrix based on a ROW, that will be a vector
	Matrix<T> createVectorFromRow(int row);

	// creating and returning new Matrix based on a COLUMN, that will be a vector
	Matrix<T> createVectorFromColumn(int col);

	int getRowsNumber() {
		return rowsNumber;
	};

	int getColsNumber() {
		return colsNumber;
	};

	void print();

	void fill() {
		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				matrix[i][j] = colsNumber * i + j + 1;
			}
		}
	};
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
	matrix = new T * [DEFAULT_SIZE];
	rowsNumber = DEFAULT_SIZE;
	colsNumber = DEFAULT_SIZE;

	for (int i = 0; i < DEFAULT_SIZE; i++) {
		matrix[i] = new T[DEFAULT_SIZE];
	}

	std::cout << "Konstruktor DOMYS\n";
}

// constructor with parameters
template<typename T>
Matrix<T>::Matrix(int rowsNumber, int colsNumber) {
	if (rowsNumber <= 0 || colsNumber <= 0) {}//raport error

	matrix = new T * [rowsNumber];
	this->rowsNumber = rowsNumber;
	this->colsNumber = colsNumber;

	for (int i = 0; i < rowsNumber; i++) {
		matrix[i] = new T[colsNumber];
	}

	std::cout << "Konstruktor PARAM\n";
}

// copy constructor 
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
	copyFields(other);

	std::cout << "Konstruktor KOP\n";
}


// move constructor
template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept {
	toMove(other);

	std::cout << "Konstruktor MOVE\n";
}


// destructor
template<typename T>
Matrix<T>::~Matrix() {
	deleteFields();

	std::cout << "DESTRUKTOR\n";
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

	std::cout << "op=\n";
	return *this;
}

// move operator=
template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept {
	if (this != &other) {
		deleteFields();

		toMove(other);
	}

	std::cout << "MOVE op=\n";
	return *this;
}

// operator+
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
	return std::move(addByMatrix(other));
}

// operator-
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
	return std::move(subByMatrix(other));
}

//=============================================================================
//									METHODS
//=============================================================================
template<typename T>
Matrix<T> Matrix<T>::addByMatrix(const Matrix<T>& other) {
	Matrix<T> sum(rowsNumber, colsNumber);

	if (matrix != nullptr && other.matrix != nullptr && rowsNumber == other.rowsNumber && colsNumber == other.colsNumber) {
		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				sum.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
			}
		}
		std::cout << "added\n";
	}
	else std::cout << "CANNOT ADD!\n";

	return std::move(sum);
}

template<typename T>
Matrix<T> Matrix<T>::subByMatrix(const Matrix<T>& other) {
	Matrix<T> sub(rowsNumber, colsNumber);

	if (matrix != nullptr && other.matrix != nullptr && rowsNumber == other.rowsNumber && colsNumber == other.colsNumber) {
		for (int i = 0; i < rowsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				sub.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
			}
		}
		std::cout << "substracted\n";
	}
	else std::cout << "CANNOT SUBSTRACT!\n";

	return std::move(sub);
}

template<typename T>
Matrix<T> Matrix<T>::createVectorFromRow(int row) {
	Matrix<T> result(1, colsNumber);

	for (int i = 0; i < colsNumber; i++) {
		result.matrix[0][i] = matrix[row - 1][i];
	}

	return std::move(result);
}

template<typename T>
Matrix<T> Matrix<T>::createVectorFromColumn(int col) {
	Matrix<T> result(1, rowsNumber);

	for (int i = 0; i < rowsNumber; i++) {
		result.matrix[0][i] = matrix[i][col - 1];
	}

	return std::move(result);
}

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

template<typename T>
void Matrix<T>::deleteFields() {
	if (matrix != nullptr) {
		std::cout << "DES cos usuwamy\n";
		for (int i = 0; i < rowsNumber; i++) {
			delete[] matrix[i];
		}

		delete[] matrix;
	}
}

template<typename T>
void Matrix<T>::toMove(Matrix<T>& other) {
	matrix = other.matrix;
	rowsNumber = other.rowsNumber;
	colsNumber = other.colsNumber;

	other.matrix = nullptr;
	other.rowsNumber = -1;
	other.colsNumber = -1;
}

template<typename T>
void Matrix<T>::print() {
	std::cout << "rows: " << rowsNumber << " | cols: " << colsNumber << "\n";
	
	for (int i = 0; i < rowsNumber; i++) {
		for (int j = 0; j < colsNumber; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}