#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

# define M_PI 3.14159265358979323846

using namespace std::chrono;

double f(double x)
{
	return 6 / sqrt(x * (2 - x));
}

double left(double low, double high, int n = 100) {
	// std::cout << "left     ";
	// high_resolution_clock::time_point t1 = high_resolution_clock::now();
	const double h = (high - low) / n;
	double rightPart = 0;
	//#pragma loop(hint_parallel(12))
	// #pragma loop(no_vector)
	for (int i = 0; i <= n - 1; i++) {
		rightPart += f(low + h * i);
	}
	const double rez = h * rightPart;
	// high_resolution_clock::time_point t2 = high_resolution_clock::now();
	// duration<double> duration = (t2 - t1);
	// std::cout << n << "        " << rez << "      " << duration.count() << "    " << ((M_PI - abs(M_PI - rez)) * 100) / M_PI << std::endl;
	return rez;
}

double right(double low, double high, int n = 100) {
	// std::cout << "right    ";
	// high_resolution_clock::time_point t1 = high_resolution_clock::now();
	const double h = (high - low) / n;
	double rightPart = 0;
	// #pragma loop(hint_parallel(12))
	// #pragma loop(no_vector)
	for (int i = 1; i <= n; i++) {
		rightPart += f(low + h * i);
	}
	const double rez = h * rightPart;
	// high_resolution_clock::time_point t2 = high_resolution_clock::now();
	// duration<double> duration = (t2 - t1);
	// std::cout << n << "        " << rez << "      " << duration.count() << "    " << ((M_PI - abs(M_PI - rez)) * 100) / M_PI << std::endl;
	return rez;
}

int main()
{
#pragma region presetting
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout.precision(9);
	std::cout.setf(std::ios_base::fixed);
#pragma endregion
	// std::cout << "method | intervals\\   result  \\   duration (s)  \\   accuracy (%)   \\\n";
	high_resolution_clock::time_point g1 = high_resolution_clock::now();

	/* Parametrs Initialisation */
	const double low = 0.5;
	const double high = 1;
	int n = 100;

	/* Calculations */
	//#pragma loop(hint_parallel(12))
	//#pragma loop(no_vector)
	while (n <= 1000000) {
		// Thread
		/*
		std::thread lt(left, low, high, n);
		std::thread rt(right, low, high, n);
		lt.join();
		rt.join();
		*/


		// raw

		left(low, high, n);
		right(low, high, n);

		n *= 10;
	}
	high_resolution_clock::time_point g2 = high_resolution_clock::now();
	duration<double> duration = (g2 - g1);
	std::cout << "Сумарное время расчета значений (qpar): " << duration.count();
}
