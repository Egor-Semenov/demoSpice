#include <iostream>
#include <vector>   //Использование контейнера библиотеки STL     
#include <iomanip>

using namespace std;

vector<vector<double>> MatrixMul(vector<vector<int>>& matrix1, vector<vector<double>>& matrix2) //Функция произведения целочисленной матрицы на матрицу вещественных значений
{
    int rows1 = matrix1.size();     //Получение количества рядов в первой матрице
    int columns1 = matrix1[0].size();   //Получение количества колонок в первой матрице
    int rows2 = matrix2.size();     //Получение количества рядов во второй матрице
    int columns2 = matrix2[0].size();   //Получение количества столбцов во второй матрице
    vector<vector<double>> matrix3(rows1, vector<double>(columns2));    //Создание результирующей матрицы
    if (columns1 != rows2)      //Проверка условия произведения матриц
    { 
        cout << "Error, matrix data cannot be multiplied!"; 
        return matrix3;
    }

    for (int i = 0; i < rows1; i++)     //Выполнение произведение матриц
    {
        for (int j = 0; j < columns2; j++)
        {
            matrix3[i][j] = 0;
            for (int h = 0; h < columns1; h++)
            {
                matrix3[i][j] += matrix1[i][h] * matrix2[h][j];
            }
        }
    }
    return matrix3;     //Возврат полученной матрицы
}

vector<vector<double>> MatrixMul(vector<vector<double>>& matrix1, vector<vector<int>>& matrix2)     //Функция произведения вещественной матрицы на матрицу целочисленных значений 
{
    int rows1 = matrix1.size();     //Получение количества рядов в первой матрице
    int columns1 = matrix1[0].size();   //Получение количества колонок в первой матрице
    int rows2 = matrix2.size();     //Получение количества рядов во второй матрице
    int columns2 = matrix2[0].size();   //Получение количества столбцов во второй матрице

    vector<vector<double>> matrix3(rows1, vector<double>(columns2));    //Создание результирующей матрицы
    if (columns1 != rows2)      //Проверка условия произведения матриц
    { 
        cout << "Error, matrix data cannot be multiplied!"; 
        return matrix3; 
    }

    for (int i = 0; i < rows1; i++)     //Выполнение произведение матриц
    {
        for (int j = 0; j < columns2; j++)
        {
            matrix3[i][j] = 0;
            for (int h = 0; h < columns1; h++)
            {
                matrix3[i][j] += matrix1[i][h] * matrix2[h][j];
            }
        }
    }

    return matrix3;     //Возврат полученной матрицы
}

vector<vector<double>> MatrixMul(vector<vector<double>>& matrix1, vector<vector<double>>& matrix2) 
{
    int rows1 = matrix1.size();     //Получение количества рядов в первой матрице
    int columns1 = matrix1[0].size();   //Получение количества колонок в первой матрице
    int rows2 = matrix2.size();     //Получение количества рядов во второй матрице
    int columns2 = matrix2[0].size();   //Получение количества столбцов во второй матрице

    vector<vector<double>> matrix3(rows1, vector<double>(columns2));    //Создание результирующей матрицы
    if (columns1 != rows2)      //Проверка условия произведения матриц
    {
        cout << "Error, matrix data cannot be multiplied!"; 
        return matrix3; 
    }

    for (int i = 0; i < rows1; i++)     //Выполнение произведение матриц
    {
        for (int j = 0; j < columns2; j++)
        {
            matrix3[i][j] = 0;
            for (int h = 0; h < columns1; h++)
            {
                matrix3[i][j] += matrix1[i][h] * matrix2[h][j];
            }
        }
    }
    return matrix3;     //Возврат полученной матрицы
}

template<typename T>
vector<vector<T>> MatrixInv(vector<vector<T>>& matrix1) //Функция создания обратной матрицы
{
    vector<vector<T>> matrix2(matrix1.size(), vector<T>(matrix1.size()));   //Создание обратной матрицы1

    float temp;
    int N = matrix1.size();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix2[i][j] = 0.0;

            if (i == j)
                matrix2[i][j] = 1.0;
        }
    }

    for (int k = 0; k < N; k++)
    {
        temp = matrix1[k][k];

        for (int j = 0; j < N; j++)
        {
            matrix1[k][j] /= temp;
            matrix2[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = matrix1[i][k];

            for (int j = 0; j < N; j++)
            {
                matrix1[i][j] -= matrix1[k][j] * temp;
                matrix2[i][j] -= matrix2[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = matrix1[i][k];

            for (int j = 0; j < N; j++)
            {
                matrix1[i][j] -= matrix1[k][j] * temp;
                matrix2[i][j] -= matrix2[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix1[i][j] = matrix2[i][j];
        }
    }
    return matrix2;
}

template<typename T>
vector<vector<T>> MatrixTransp(vector<vector<T>>& matrix1) // Функция создания транспонированной матрицы
{
    vector<vector<T>> matrix2(matrix1[0].size(), vector<T>(matrix1.size()));// Создание транспонированной матрицы 
    for (int i = 0; i < matrix1.size(); i++)
    {
        for (int j = 0; j < matrix1[0].size(); j++)
        {
            matrix2[j][i] = matrix1[i][j];
        }
    }
    return matrix2;
}

//Матрица 1 = матрица В, матрица 2 = матрица сопротивлений, матрица 3 = матрица напряженний
vector<vector<double>> MatrixRez(vector<vector<int>>& matrix1, vector<vector<double>>& matrix2, vector<vector<double>>& matrix3) {
    vector<vector<double>> matrix4(matrix1.size(), vector<double>(matrix1.size())); // Матрица контурных сопротивлений
    vector<vector<double>> matrix5(matrix1.size(), vector<double>(matrix3[0].size())); // Матрица контурных напряжений
    vector<vector<double>> matrix6(matrix5.size(), vector<double>(matrix5[0].size())); // Матрица контурных токов
    vector<vector<double>> matrix7(matrix1.size(), vector<double>(matrix1[0].size())); // Матрица В*Z
    vector<vector<int>> matrix8(matrix1[0].size(), vector<int>(matrix1.size())); // Транспонированная матрица В
    vector<vector<double>> matrix9(matrix4.size(), vector<double>(matrix4.size())); // Обратная матрица контурных сопротивлений
    vector<vector<double>> matrix10(matrix8.size(), vector<double>(matrix8[0].size())); // Матрица токов

    matrix8 = MatrixTransp(matrix1);
    matrix7 = MatrixMul(matrix1, matrix2);
    matrix4 = MatrixMul(matrix7, matrix8);
    matrix5 = MatrixMul(matrix1, matrix3);
    matrix9 = MatrixInv(matrix4);
    matrix6 = MatrixMul(matrix9, matrix5);
    matrix10 = MatrixMul(matrix8, matrix6);

    return matrix10;
}
