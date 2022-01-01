#include <iostream>
#include <cmath>
#include<cstdlib>
using namespace std;
double eps = 0.0005;
double F(double x, int a0, int a1, int a2, int a3, int a4, int a5) {
	return (10 * a5*pow(x, 5) + a4*pow(x, 4) + a3*pow(x, 3) + a2 * pow(x, 2) +a1*x  +2 * a0);
}

double Bisection(int a0, int a1, int a2, int a3, int a4, int a5, double a, double b) {
	double c = a, aa = a, bb = b;
	while (abs(b - a)> eps)
	{
		c = (a + b) / 2;
		if ((F(a, a0, a1, a2, a3, a4, a5) * F(c, a0, a1, a2, a3, a4, a5)) > 0) a = c;
		else b = c;
	}
	return c;
}
double Dot(int a0, int a1, int a2, int a3, int a4, int a5, double x0) {
	double x = x0, df, h = 0.00001;
	df = (F(x + h, a0, a1, a2, a3, a4, a5) - F(x, a0, a1, a2, a3, a4, a5)) / h;
	while(abs(F(x, a0, a1, a2, a3, a4, a5))> eps)
		x = x - F(x, a0, a1, a2, a3, a4, a5) / df;
	return x;
}

double Horda(int a0, int a1, int a2, int a3, int a4, int a5, double a, double b) {
	float c = 0, d= 1;
	while (abs(F(c, a0, a1, a2, a3, a4, a5)) > 0.005) {
		d = c;
		c = (F(b, a0, a1, a2, a3, a4, a5) * a - F(a, a0, a1, a2, a3, a4, a5) * b) / (F(b, a0, a1, a2, a3, a4, a5) - F(a, a0, a1, a2, a3, a4, a5));
		if ((F(a, a0, a1, a2, a3, a4, a5) * F(c, a0, a1, a2, a3, a4, a5)) > 0) a = c;
		else b = c;
	}
	return c;
}
int main() 
{
	setlocale(LC_ALL, "Russian");
	double a0 = -3, a1 = 0, a2 = 7, a3 = 0, a4 = -3, a5 =1, a = 0.5, b = 2;
	cout << "a0 = " << a0 << "\na1 = " << a1 << "\na2 = " << a2 << "\na3 = " << a3 << "\na4 = " << a4 << "\na5 = " << a5;
	cout << "\nIнтервал:\nНижня межа = "<<a << "\nВерхня межа = " << b << endl;
	cout << "Метод половинного дiлення:\tx = " << Bisection(a0, a1, a2, a3, a4, a5, a, b) << endl;
	cout << "Метод дотичних:\t\t\tx = " << Dot(a0, a1, a2, a3, a4, a5, b) << endl;
	cout << "Метод хорд:\t\t\tx = " << Horda(a0, a1, a2, a3, a4, a5, a, b) << endl;
	return 0;
}