#pragma once
#include<vector>

vector<vector<double>> MatrixMul(vector<vector<int>>& matrix1, vector<vector<double>>& matrix2);
vector<vector<double>> MatrixMul(vector<vector<double>>& matrix1, vector<vector<int>>& matrix2);
vector<vector<double>> MatrixMul(vector<vector<double>>& matrix1, vector<vector<double>>& matrix2);
template<typename T>
vector<vector<T>> MatrixInv(vector<vector<T>>& matrix1);
template<typename T>
vector<vector<T>> MatrixTransp(vector<vector<T>>& matrix1);
vector<vector<double>> MatrixRez(vector<vector<int>>& matrix1, vector<vector<double>>& matrix2, vector<vector<double>>& matrix3);

