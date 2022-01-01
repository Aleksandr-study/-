#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


double Gayss(double a, double b, int n);
	double f(double x){return (sin(x) * (x+1));}
	double I(double a,double b,int n,double y){return ((b-a)/(2*n)*y);}
int main() {
	int n;
	double a,b,y = 0,dy,In;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    if (a >= b)
    { 
        cout << "Wrong segment";
        return 0;
    }
    cout << "Enter n: ";
    cin >> n;
	dy=(b-a)/n;
	y += f(a) + f(b);
	for (int i=1; i<n; i++)
	{
		y+=2*(f(a+dy*i));
	}
	In=I(a,b,n,y);
	cout << fixed;
	cout.precision(6);
	cout << "Trapezium method:\n" << In << endl;
    cout << "Gaussian quadrature method:\n" << Gayss(a, b, n) << endl;  
}

double Gayss(double a, double b, int n)
{
    double Sum, PartSum;
    double h = (b - a) /  n;
    Sum = 0;
    for (int j = 0; j < n; j++)
    {
        PartSum = 0;
        for (int i = 0; i <= 1; i++)
            PartSum += f(a + h*(i + j));
        Sum += 0.5 * PartSum * h;
    }
    return Sum;
}