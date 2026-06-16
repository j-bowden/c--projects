#include <iostream>
#include <cmath>

// This program implements the Fermat factorisation algorithm for a predetermined number of attempts.


bool isInteger(double num) {
	return num == std::floor(num);
}

int main() {
	int N = 2911;
	int att = 100;

	if (att < 1) {
		std::cout << "Error: you must specify a positive number of attempts." << std::endl;
		return 0;
	}
	else if (N % 2 == 0) {
		std::cout << N << " is an even integer. It is divisible by two." << std::endl;
		return 0;
	}
	else {
		double sq = std::sqrt(N);
		int r_init = std::floor(sq) + 1;
		int r = r_init;

		while (r < r_init + att) {
			double test = std::sqrt((r * r) - N);
			if (isInteger(test)) {
				int fac1 = r + test;
				int fac2 = r - test;
				std::cout << N << " is composite, and can be factorised as " << fac1 << " times " << fac2 << "." << std::endl;
				return 0;
			}
			r += 1;
		}

		std::cout << N << " could not be factorised in only " << att << " attempts." << std::endl;
		std::cout << "It is yet to be seen whether " << N << " is prime or composite." << std::endl;
		return 0;
	}
}