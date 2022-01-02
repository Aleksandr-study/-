#include <iostream>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#define e 0.005
using namespace std;
class Matr
{
private:
    int size;
    float a;
    float** mas;
    float* mas1;
public:
    Matr(int l)
    {
        size = l;
        mas = new float* [l];
        for (int i = 0; i < l; i++)
            mas[i] = new float[l];
        mas1 = new float[l];
    }
    void Add()
    {
        std::ifstream finA_C("C://diagonal_dominating.txt");
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                finA_C >> mas[i][j];
            }
        for (int i = 0; i < size; i++)
        {
            finA_C >> mas1[i];
        }
        finA_C.close();
    }
    void Print()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << setw(4) << mas[i][j] << " ";
            }
            cout << "\t" << mas1[i] << endl;
        }
    }
    void findResidualVector(float* b, float** a, float* x)
    {

        float* r = new float[size];
        float* Ax = new float[size];
        Ax = multMatrix(a, x);
        std::cout << std::endl;
        // находим вектор нев`язки
        for (int i = 0; i < size; i++)
        {
            *(r + i) = *(b + i) - *(Ax + i);
            std::cout << "r[" << i << "] = " << *(r + i) << std::endl; 
        }
        delete[] Ax;
    }

    float* multMatrix(float** a, float* b)
    {
        float* c = new float[size];
        for (int i = 0; i < size; i++)
        {
            c[i] = 0;
            for (int j = 0; j < size; j++)
            {
                c[i] += a[i][j] * b[j];
            }
        }
        return c;
    }

    void Iterations()
    {
        float** m = new float*[size];
        float* m1 = new float[size];
        for (int i = 0; i < size; i++)
            m[i] = new float[size];
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                m[i][j] = mas[i][j];
            }
            m1[i] = mas1[i];
        }
        float temp = 0;
        for (int k = 0; k < size; k++)
        {
            for (int i = 0; i < size; i++)
            {
                temp = mas[i][i] * (-1);
                mas1[i] /= temp;
                for (int j = 0; j <= size; j++)
                {
                    mas[i][j] /= temp;
                }
            }
        }
        for (int i = 0; i < size; i++)
        {
            mas1[i] *= -1;
            for (int j = 0; j < size; j++)
            {
                mas[i][i] = 0;
                if (mas[i][j] == -0)
                {
                    mas[i][j] = 0;
                }
            }
        }
        Print();
        cout << endl;
        cout << "Итерация №1:" << endl;
        for (int i = 0; i < size; i++)
        {

            cout << "x" << i + 1 << "=" << mas1[i];
            for (int j = 0; j < size; j++)
            {
                cout << "+(" << mas[i][j] << ")*(" << mas1[j] << ")";
            }
            cout << "=" << mas1[i] << " " << endl;
        }
        findResidualVector(m1, m, mas1);
        cout << endl << endl;
        float* x = new float[size];
        float* x0 = new float[size];
        for (int i = 0; i < size; i++)
        {
            x0[i] = mas1[i];
        }
        int counter = 1;
        do
        {
            cout << "Итерация №" << counter + 1  << ":" << endl;
            a = x[1];
            for (int i = 0; i < size; i++)
            {

                x[i] = mas1[i];
                cout << "x" << i + 1 << "=" << mas1[i];
                for (int j = 0; j < size; j++)
                {
                    x[i] += mas[i][j] * x0[j];
                    cout << "+(" << mas[i][j] << ")*(" << x0[j] << ")";
                }
                cout  << "=" << x[i] << " " << endl;
                x0[i] = x[i];
            }
            findResidualVector(m1, m, x);
            cout << endl << endl;
            if (abs(a - x[1]) < 0.0001)
            {
                break;
            }
            counter++;
        } while (abs(a - x[1]) > 0.0001);
        cout << endl << "Количество итераций: " << counter + 1 << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "x" << i + 1 << "=" << x[i] << " " << endl;
        }
        delete[] x;
        delete[] x0;
    }
};
int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    //передаємо кількість рівнянь у матриці:
    Matr a(5);
    //вводимо матрицю з діагональною перевагою з файлу:
    a.Add();
    cout << endl << "Расширенная матрица:" << endl;
    a.Print();
    cout << endl << "Преображенная матрица:";
    cout << endl;
    a.Iterations();
    cout << endl;
    system("pause");
    return 0;
}