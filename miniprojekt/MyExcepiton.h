#pragma once
#include <exception>

class MyExcepiton : public std::exception {
public:
	const char* what() const throw() {
		return "\n\n>>>>>>>>>>>> EXCEPTION! <<<<<<<<<<<\n\n";
	}
};

