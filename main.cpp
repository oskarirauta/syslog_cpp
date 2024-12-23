#include <iostream>
#include "syslog.hpp"

int main(int argc, char **argv) {

	std::cout << "syslog test" << std::endl;

	syslog::info << "info message" << std::endl;
	syslog::error << "error message" << std::endl;

	std::cout << "cout message" << std::endl;

	return 0;

}
