#include <iostream>
#include "Matrix.h"

int main()
{
	Matrix<int> x(2);
	x.print();
	x.fill();
	x.print();

	Matrix<int> xx(std::move(x));

	xx.print();

	Matrix<int> m;
	m = xx;

	m.print();

	Matrix<int> s(3, 4);
	s.fill();
	s.print();

	Matrix<int> to(1, 1);
	to = std::move(s);

	to.print();

	std::cout << "\n\n===========\n\n";
	Matrix<int> m1(3, 3);
	m1.fill();
	m1.print();

	Matrix<int>m2(3, 3);
	m2.fill();
	m2.print();

	Matrix<int> sum;
	sum = xx + x; //cannot add
	sum.print();

	sum = m1 + m2 + m1; //added
	sum = sum.addByMatrix(m2);
	sum.print();

	std::cout << "\n\n===========\n\n";
	Matrix<int> sub;
	sub = xx - x; //cannot substract
	sub.print();

	sub = m1 - m2 - m1; //substracted
	sub = sub.subByMatrix(m2);
	sub.print();

	std::cout << "\n\n===========\n\n";

	sum = sum.createVectorFromRow(2);
	sum.print();

	sub = sub.createVectorFromColumn(3);
	sub.print();

	std::cout << "\n\n@@@@@@@@@@@@@@@@\n\n\n";
}
