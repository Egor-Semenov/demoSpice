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


//vector<vector<float>> MatrixMul(vector<vector<float>>&, vector<vector<float>>&);
//vector<vector<float>> MatrixInv(vector<vector<float>>&);
//vector<vector<float>> MatrixTransp(vector<vector<float>>&);
//vector<vector<float>> MatrixRez(vector<vector<float>>& matrix1, vector<vector<float>>& matrix2, vector<vector<float>>& matrix3);
