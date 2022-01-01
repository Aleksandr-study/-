#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int n, i, j, k;
	double c, d, e;
	cout << "Введiть кiлькiсть столпцiв:\n";
	cin >> n;
	double** a = new double* [n];
	double** a1 = new double* [n];
	for (i = 0; i <= n; i++)
	{
		a1[i] = new double[n];
		a[i] = new double[n];
	}
	double* b = new double[n];
	double* x = new double[n];
	cout << "\nВведiть елементи\n";
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cout << "A[" << i << ";" << j << "] = ";
			cin >> a[i][j];
			a1[i][j] = a[i][j];
		}
		cout << "B[" << i << "] = ";
		cin >> b[i];
	}
	cout << "\nВиведення матрицi\n";
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j < n; j++)
		{
			cout << a[i][j] << "*x"<< j << " + ";
		}
		cout << a[i][n] << "*x" << j << " = " << b[i] << endl;
	}
	cout << "\nВирiшуемо СЛАР, змiнюючи елементи\n";
	for (k = 1; k <= n; k++) // прямий хід
	{
		for (j = k + 1; j <= n; j++)
		{
			c = a[j][k] / a[k][k]; // рахую частку від ділення рідків
			for (i = k; i <= n; i++)
			{
				e = a[j][i];
				a[j][i] = a[j][i] - c * a[k][i]; // рахую  елементи матриці, віднімаючи головний рядок, повторюючи до останньго рядка
				cout << "A[" << j << ";" << i << "] = " << e << " - ((" << c << ") * (" << a[k][i] << ")) = " << a[j][i] << endl;
			}
			e = b[j];
			b[j] = b[j] - c * b[k]; // так само рахую вектор правої частини 
			cout << "B[" << j << "] = " << e << " - ((" << c << ") * (" << b[k] << ")) = "<< b[j] << endl;
		}
	}
	cout << "\nРахуемо невiдомi змiннi:\n";
	for (k = n; k >= 1; k--) // зворотній хід
	{
		c = 0;
		for (j = k + 1; j <= n; j++)
		{
			//рахуємо множники для визначення коренів
			d = a[k][j] * x[j]; 
			c = c + d; 
		}
		x[k] = (b[k] - c) / a[k][k]; //визначаемо невідомі корені рівняння
		cout << "x[" << k << "] = (" << b[k] << " - (" << c << ")) / " << a[k][k] << endl;
	}
	cout << "\nКоренi рiвняння:\n" << endl;//виводимо корені
	for (i = 1; i <= n; i++)
	{
		cout << "x[" << i << "]=" << x[i] << " " << endl;
	}
	return 0;
}