#include <iostream>
#include "Matrix.h"

void addTest();
void substractTest();
void multiplyTest();
void operatorGetAndSetTest();
void creatingVectorFromRowAndColumnTest();
void scalarProductTest();
void transposeTest();
void toIdendityTest();
void readFromFileTest();

int main()
{
	std::cout << "\n\n========== ADDING TEST ==========\n\n";
	//addTest();

	std::cout << "\n\n========== SUBSTRACTING TEST ==========\n\n";
	//substractTest();

	std::cout << "\n\n========== MULITPLYING TEST ==========\n\n";
	//multiplyTest();

	std::cout << "\n\n========== OPERATOR() AND SETTER TEST ==========\n\n";
	//operatorGetAndSetTest();

	std::cout << "\n\n========== CREATING VECTOR FROM ROW AND COLUMN + MATRIX<DOUBLE> TEST ==========\n\n";
	//creatingVectorFromRowAndColumnTest();

	std::cout << "\n\n========== SCALAR PRODUCT + MATRIX<FLOAT> TEST ==========\n\n";
	//scalarProductTest();

	std::cout << "\n\n========== TRANSPOSE TEST ==========\n\n";
	//transposeTest();

	std::cout << "\n\n========== SQUARE => IDENTITY TEST ==========\n\n";
	//toIdendityTest();

	std::cout << "\n\n========== READ FROM FILE TEST ==========\n\n";
	readFromFileTest();

	//std::cout << "\n\n===== PLIKI ======\n\n";
	//Matrix<double> plik;

	//plik.readFromFileAndSave("wsad_double.txt");

	//plik.print();

	std::cout << "\n\n@@@@@@@@@@@@@@@@\n\n\n";
}

void addTest() {
	int error = 0;

	Matrix<int> m1(3, 3);
	m1.fill();
	m1.print();

	Matrix<int>m2(3, 3);
	m2.fill();
	m2.print();

	Matrix<int>m3(2, 3);
	m3.fill();
	m3.print();

	Matrix<int> sum;

	std::cout << ">>> Added without error!\n";
	try {
		sum = m1 + m2;
	}
	catch (MyExcepiton& ex) {
		std::cout << ex.what();
	}
	sum.print();

	std::cout << ">>> Added with ERROR!\n";
	try {
		sum = m1 + m3;
	}
	catch (MyExcepiton& ex) {
		std::cout << ex.what();
	}
	sum.print();

	std::cout << ">>> Added without error!\n";
	sum = m1.addByMatrix(m2, &error);
	std::cout << "!!! error status: " << error << '\n';
	sum.print();

	std::cout << ">>> Added with ERROR!\n";
	sum = m1.addByMatrix(m3, &error);
	std::cout << "!!! error status: " << error << '\n';
	sum.print();

	std::cout << "\n>>> Check of matices\n";
	m1.print();
	m2.print();
	m3.print();
}

void substractTest() {
	int error = 0;

	Matrix<int> m1(3, 3);
	m1.fill();
	m1.print();

	Matrix<int>m2(3, 3);
	m2.fill();
	m2.print();

	Matrix<int>m3(2, 3);
	m3.fill();
	m3.print();

	Matrix<int> sub;

	std::cout << ">>> Substracted without error!\n";
	try {
		sub = m1 - m2;
	}
	catch (MyExcepiton& ex) {
		std::cout << ex.what();
	}
	sub.print();

	std::cout << ">>> Substracted with ERROR!\n";
	try {
		sub = m1 - m3;
	}
	catch (MyExcepiton& ex) {
		std::cout << ex.what();
	}
	sub.print();

	std::cout << ">>> Substracted without error!\n";
	sub = m1.substractByMatrix(m2, &error);
	std::cout << "!!! error status: " << error << '\n';
	sub.print();

	std::cout << ">>> Substracted with ERROR!\n";
	sub = m1.substractByMatrix(m3, &error);
	std::cout << "!!! error status: " << error << '\n';
	sub.print();

	std::cout << "\n>>> Check of matices\n";
	m1.print();
	m2.print();
	m3.print();
}

void multiplyTest() {
	int error = 0;

	Matrix<int> m1(2, 2);
	m1.fill();
	m1.print();

	std::cout << "\n\n >>> BY NUMBER <<<\n\n";
	Matrix<int> mul;

	try {
		mul = m1 * 2 * (-1);
	}
	catch (MyExcepiton& ex) {
		std::cout << ex.what();
	}
	mul.print();
	m1.print();

	mul = m1.multiplyByNumber(2).multiplyByNumber(-1);
	mul.print();
	
	std::cout << "\n\n>>> BY OTHER MATRIX <<<\n\n";
	Matrix<int> m2(2, 3);
	m2.fill();

	Matrix<int> m3(3, 4);
	m3.fill();
	
	Matrix<int>m4(4, 4);
	m4.fill();

	std::cout << ">>> Mulityplying without error!\n";
	try {
		mul = m2 * m3;
	}
	catch(MyExcepiton& ex) {
		std::cout << ex.what();
	}
	mul.print();
	m2.print();
	m3.print();

	std::cout << ">>> Mulityplying with ERROR!\n";
	try {
		mul = m2 * m4;
	}
	catch (MyExcepiton& ex) {
		std::cout << ex.what();
	}
	mul.print();

	std::cout << ">>> Mulityplying without error!\n";
	mul = m2.multiplyByOtherMatrix(m3, &error);
	std::cout << "!!! error status: " << error << '\n';
	mul.print();

	m2.print();
	m3.print();

	std::cout << ">>> Mulityplying with ERROR!\n";
	mul = m2.multiplyByOtherMatrix(m4, &error);
	std::cout << "!!! error status: " << error << '\n';
	mul.print();

	m2.print();
	m3.print();
	m4.print();
}

void operatorGetAndSetTest() {
	int error = 0;

	Matrix<int> m1;
	m1.fill();
	m1.print();

	try {
		std::cout << "[0][0]: " << m1(1, 2) << " | " << m1.getElementOn(1, 2) << '\n';
		std::cout << "[9][9] (doesn't exist): " << m1(5, 5) << '\n';
	}
	catch (MyExcepiton& ex) {
		std::cout << ex.what();
	}

	std::cout << m1.getElementOn(9, 9, &error) << '\n';
	std::cout << "!!! error status: " << error << '\n';

	m1.print();
	
	error = 0;
	m1.setElementOn(999, 0, 0, &error);
	std::cout << "!!! error status: " << error << '\n';

	error = 0;
	m1.setElementOn(-1, -1, -1, &error);
	std::cout << "!!! error status: " << error << '\n';

	error = 0;
	m1.setElementOn(-1, 5, 5, &error);
	std::cout << "!!! error status: " << error << '\n';

	m1.setElementOn(888, 1, 1);
	m1.setElementOn(777, 2, 2);
	m1.setElementOn(666, 3, 3);
	m1.setElementOn(555, 4, 4);

	m1.print();
}

void creatingVectorFromRowAndColumnTest() {
	int error = 0;

	Matrix<double> m1;
	m1.fill();
	m1.print();

	Matrix<double> m2;
	m2.fill();
	m2.print();

	Matrix<double> result;
	
	std::cout << "\n >>> FROM ROW <<<\n\n";

	result = m1.createVectorFromRow(0, &error);
	std::cout << "!!! error status: " << error << '\n';
	result.print();
	m1.print();

	result = m1.createVectorFromRow(-1, &error);
	std::cout << "!!! error status: " << error << '\n';
	result.print();

	result = m1.createVectorFromRow(5, &error);
	std::cout << "!!! error status: " << error << '\n';

	std::cout << "\n >>> FROM COLUMN <<<\n\n";

	error = 0;

	result = m2.createVectorFromColumn(0, &error);
	std::cout << "!!! error status: " << error << '\n';
	result.print();
	m2.print();

	result = m2.createVectorFromRow(-1, &error);
	std::cout << "!!! error status: " << error << '\n';
	result.print();

	result = m2.createVectorFromRow(5, &error);
	std::cout << "!!! error status: " << error << '\n';
}

void scalarProductTest() {
	int error = 0;

	Matrix<float> m1(4);
	m1.fill();
	m1.print();

	Matrix<float> m2(4);
	m2.fill();
	m2.print();

	Matrix<float> m3(1, 4);
	m3.fill();
	m3.print();

	Matrix<float> m4(1, 3);
	m4.fill();
	m4.print();

	Matrix<float> m5(2, 2);
	m5.fill();
	m5.print();

	std::cout << "\n>>> Scalar product: " << m1.scalarProduct(m2, &error) << '\n';
	std::cout << "!!! error status: " << error << '\n';

	std::cout << "\n>>> Scalar product: " << m1.scalarProduct(m3, &error) << '\n';
	std::cout << "!!! error status: " << error << '\n';

	std::cout << "\n>>> Scalar product: " << m1.scalarProduct(m4, &error) << '\n';
	std::cout << "!!! error status: " << error << '\n';

	std::cout << "\n>>> Scalar product: " << m1.scalarProduct(m5, &error) << '\n';
	std::cout << "!!! error status: " << error << '\n';
}

void transposeTest() {
	int error = 0;

	Matrix<int> m1(2, 3);
	m1.fill();
	m1.print();

	m1.transpose(&error);
	std::cout << "!!! error status: " << error << '\n';
	m1.print();
}

void toIdendityTest() {
	int error = 0;

	Matrix<int> m1(3, 3);
	m1.fill();
	m1.print();

	Matrix<int> m2(3, 4);
	m2.fill();
	m2.print();

	m1.modifyToIdentityMatrix(&error);
	m1.print();
	std::cout << "!!! error status: " << error << '\n';

	m2.modifyToIdentityMatrix(&error);
	m2.print();
	std::cout << "!!! error status: " << error << '\n';
}

void readFromFileTest() {

}
