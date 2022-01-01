#include <iostream>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <conio.h>
 
using namespace std;
 
double my_lagrange(double x, int n, double x_arr[], double y_arr[]);
double  y_ar(double x);
int BuildSpline();
double Interpolate(double z);
void SolveTriDiag(double** TDM, double* F);
int Load_Data(double* x_arr, double* y_arr);
class knot;
class vector;
knot* KnotArray;
double** Coef;
double* b;
int n = 5;
 
int main()
{
    double x_arr[5] = {3, 5, 7, 9, 11};
    double y_arr[5];
	cout  << "Function:" << endl;
    for (int i = 0; i < 5; i++)
    {
        y_arr[i] = (x_arr[i] / 2 * cos(x_arr[i] * 2));
        cout << "y(" << x_arr[i] << ") = " <<  y_arr[i] << endl;
    }
    cout << endl << "Lagrange polynomial:\tError:" << endl;
    for (double x = 3; x < 11; x += 0.3){
        cout << "P(" << x << ") = "
            << my_lagrange(x, n, x_arr, y_arr);
        cout << "\t\t" << "e = " << abs(my_lagrange(x, n, x_arr, y_arr) - y_ar(x))<< endl;
    }
	cout << endl;
	double z = 3;
	cout << endl << "Interpolation \nby cubic splines:\tError:" << endl;
	if (Load_Data(x_arr, y_arr) != -1)
	{
		BuildSpline();
		while (z<11.1)
		{
			cout << "P(" << z << ") = " << Interpolate(z)
				<< "\t\t" << "e = " << abs(Interpolate(z) - y_ar(z)) << endl;
			z += 0.3;
		}
	}
    return 0;
}

double y_ar(double x)
{
    return (x / 2 * cos(x * 2));
}
 
double my_lagrange(double x, int n, double x_arr[], double y_arr[]){
    //Пусть точки отсортированы по возрастанию координаты x
    
    if (n > 5)
        return (x <= x_arr[n/2]) ? my_lagrange(x, (n + 1)/2, x_arr, y_arr) : 
                                   my_lagrange(x, (n + 1)/2, &x_arr[n/2], &y_arr[n/2]);
    
    double sum = 0;
    for (int i = 0; i < n; ++i){
        
        double l = 1;
        for (int j = 0; j < n; ++j)
            if (j != i)
                l *= (x - x_arr[j]) / (x_arr[i] - x_arr[j]);
        sum += y_arr[i] * l;
    }
    
    return sum;
}

class knot {
public:
    double x, f;
    void Add(double arg, double func)
    {
        x = arg;
        f = func;
    }
    knot() {}
};

class vector {
public:
    double* x;
    void Add(int m)
    {
        x = new double[m];
    }
    vector()
    {
    }
};

//Решение системы уравнений с трехдиагональной матрицей
void SolveTriDiag(double** TDM, double* F)
{
	double* alph = new double[n - 1];
	double* beta = new double[n - 1];

	int i;

	alph[0] = -TDM[2][0] / TDM[1][0];
	beta[0] = F[0] / TDM[1][0];

	for (i = 1; i < n - 1; i++)
	{
		alph[i] = -TDM[2][i] / (TDM[1][i] + TDM[0][i] * alph[i - 1]);
		beta[i] = (F[i] - TDM[0][i] * beta[i - 1]) / (TDM[1][i] + TDM[0][i] * alph[i - 1]);
	}
	b[n - 1] = (F[n - 1] - TDM[0][n - 1] * beta[n - 2]) / (TDM[1][n - 1] + TDM[0][n - 1] * alph[n - 2]);

	for (i = n - 2; i > -1; i--)
	{
		b[i] = b[i + 1] * alph[i] + beta[i];
	}
}

//Построение таблицы коэффициентов кубического сплайна
int BuildSpline()
{
	double* a = new double[n - 1];
	double* c = new double[n - 1];
	double* d = new double[n - 1];
	double* delta = new double[n - 1];
	double* h = new double[n - 1];
	double** TriDiagMatrix = new double* [3];

	b = new double[n];

	TriDiagMatrix[0] = new double[n];
	TriDiagMatrix[1] = new double[n];
	TriDiagMatrix[2] = new double[n];

	double* f = new double[n];
	double x3, xn;
	int i;

	if (n < 3)
		return -1;

	x3 = KnotArray[2].x - KnotArray[0].x;
	xn = KnotArray[n - 1].x - KnotArray[n - 3].x;

	for (i = 0; i < n - 1; i++)
	{
		a[i] = KnotArray[i].f;
		h[i] = KnotArray[i + 1].x - KnotArray[i].x;
		delta[i] = (KnotArray[i + 1].f - KnotArray[i].f) / h[i];
		TriDiagMatrix[0][i] = i > 0 ? h[i] : x3;
		f[i] = i > 0 ? 3 * (h[i] * delta[i - 1] + h[i - 1] * delta[i]) : 0;
	}
	TriDiagMatrix[1][0] = h[0];
	TriDiagMatrix[2][0] = h[0];
	for (int i = 1; i < n - 1; i++)
	{
		TriDiagMatrix[1][i] = 2 * (h[i] + h[i - 1]);
		TriDiagMatrix[2][i] = h[i];
	}
	TriDiagMatrix[1][n - 1] = h[n - 2];
	TriDiagMatrix[2][n - 1] = xn;
	TriDiagMatrix[0][n - 1] = h[n - 2];


	i = n - 1;
	f[0] = ((h[0] + 2 * x3) * h[1] * delta[0] + powf(h[0], 2) * delta[1]) / x3;
	f[n - 1] = (powf(h[i - 1], 2) * delta[i - 2] + (2 * xn + h[i - 1]) * h[i - 2] * delta[i - 1]) / xn;

	SolveTriDiag(TriDiagMatrix, f);

	Coef = new double* [4];
	Coef[0] = new double[n - 1];
	Coef[1] = new double[n - 1];
	Coef[2] = new double[n - 1];
	Coef[3] = new double[n - 1];
	int j;
	for (j = 0; j < n - 1; j++)
	{
		d[j] = (b[j + 1] + b[j] - 2 * delta[j]) / (h[j] * h[j]);
		c[j] = 2 * (delta[j] - b[j]) / h[j] - (b[j + 1] - delta[j]) / h[j];

		Coef[j][0] = a[j];
		Coef[j][1] = b[j];
		Coef[j][2] = c[j];
		Coef[j][3] = d[j];
	}

}

//Подсчет значения интерполянты в заданной точке
double Interpolate(double z)
{
	//double result;
	int i = 0;

	while (KnotArray[i].x < z)
		i++;
	i--;

	if (z > 3 && z < 11)
	{
		return  Coef[i][0] + Coef[i][1] * (z - KnotArray[i].x) + Coef[i][2] * powf((z - KnotArray[i].x), 2) + Coef[i][3] * powf((z - KnotArray[i].x), 3);
	}
	else 
	{
		return (z / 2 * cos(z * 2));
	}
}
//Загрузка данных
int Load_Data(double* x_arr, double* y_arr)
{
	char FileName[20];
	int i = 0;
	double ii;
	double x, f;
	KnotArray = new knot[n];
	while (i != n)
	{
		KnotArray[i].Add(x_arr[i], y_arr[i]);
		i++;
		if (i == n + 1)
			return -1;
	}
	return 1;
}