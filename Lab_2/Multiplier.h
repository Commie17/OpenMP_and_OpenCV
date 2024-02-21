#include <iostream>
#include <omp.h>
#include <fstream>
#include <chrono>

using namespace std;

class Multiplier
{
	float** matrixA;
	float** matrixB;
	float** result;
	float** resultM;
	int matrixSize;
public:

	Multiplier(int matrixSize)
	{
		this->matrixSize = matrixSize;
		matrixA = new float* [matrixSize];
		matrixB = new float* [matrixSize];
		result = new float* [matrixSize];
		resultM = new float* [matrixSize];
		for (int i = 0;i < matrixSize;i++)
		{
			matrixA[i] = new float[matrixSize];
			matrixB[i] = new float[matrixSize];
			result[i] = new float[matrixSize];
			resultM[i] = new float[matrixSize];

			for (int j = 0;j < matrixSize;j++)
			{
				matrixA[i][j] = 1 + rand() % 10;
				matrixB[i][j] = 1 + rand() % 10;
				result[i][j] = 0;
				resultM[i][j] = 0;
			}
		}

	}

	void SingleCompute()
	{
		cout << endl << "--------------------Single started---------------------" << endl;
		for (int iterator = 0;iterator < 1;iterator++)
		{
			auto start = chrono::high_resolution_clock::now();
			for (int i = 0;i < matrixSize;i++)
			{
				for (int j = 0;j < matrixSize;j++)
				{
					for (int k = 0;k < matrixSize;k++)
					{
						result[i][j] += (matrixA[i][k] + matrixB[k][j]);
					}
				}
			}
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, std::milli> dur = end - start;
			cout << endl << "iteration: " << iterator + 1 << " time: " << dur.count() << endl;
		}
	}

	void OmpCompute()
	{
		cout << endl << "--------------------OMP started---------------------" << endl;
		for (int iterator = 0;iterator < 3;iterator++)
		{
			auto start = chrono::high_resolution_clock::now();
			#pragma omp parallel for num_threads(6)
			for (int i = 0;i < matrixSize;i++)
			{
				for (int j = 0;j < matrixSize;j++)
				{
					for (int k = 0;k < matrixSize;k++)
					{
						resultM[i][j] += (matrixA[i][k] * matrixB[k][j]);
					}
				}
			}
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, std::milli> dur = end - start;
			cout << endl << "iteration: " << iterator + 1 << " time: " << dur.count() << endl;
		}
	}

	~Multiplier()
	{
		for (int i = 0;i < matrixSize;i++)
		{
			delete[] matrixA[i];
			delete[] matrixB[i];
			delete[] result[i];
			delete[] resultM[i];
		}

		delete matrixA;
		delete matrixB;
		delete result;
		delete resultM;
	}
};

class SingleMultiplier
{
	ofstream results;
	int matrixSize;
public:
	float** matrixA;
	float** matrixB;
	float** result;

	SingleMultiplier(int sizeOfMatrix)
	{
		srand(1);
		matrixSize = sizeOfMatrix;
		matrixA = new float* [matrixSize];
		matrixB = new float* [matrixSize];
		result = new float* [matrixSize];
		for (int i = 0;i < matrixSize;i++)
		{
			matrixA[i] = new float[matrixSize];
			matrixB[i] = new float[matrixSize];
			result[i] = new float[matrixSize];

			for (int j = 0;j < matrixSize;j++)
			{
				matrixA[i][j] = 1 + rand() % 10;
				matrixB[i][j] = 1 + rand() % 10;
				result[i][j] = 0;
			}
		}
	}

	void Compute()
	{
		results.open("Results.csv");
		cout << endl << "--------------------OMP started---------------------" << endl;
		for (int iterator = 0;iterator < 1;iterator++)
		{
			auto start = chrono::high_resolution_clock::now();
			#pragma omp parallel for num_threads(12)
			for (int i = 0;i < matrixSize;i++)
			{
				for (int j = 0;j < matrixSize;j++)
				{
					for (int k = 0;k < matrixSize;k++)
					{
						result[i][j] += (matrixA[i][k] * matrixB[k][j]);
					}
				}
			}
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, std::milli> dur = end - start;
			results << dur.count() << ";";
			cout << endl << "iteration: " << iterator + 1 << " time: " << dur.count() << endl;
		}
	}

	~SingleMultiplier()
	{
		for (int i = 0;i < matrixSize;i++)
		{
			delete[] matrixA[i];
			delete[] matrixB[i];
			delete[] result[i];
		}

		delete matrixA;
		delete matrixB;
		delete result;
	}
};

class OmpMultiplier
{
	ofstream results;
	int matrixSize;
public:
	float** matrixA;
	float** matrixB;
	float** result;

	OmpMultiplier(int sizeOfMatrix)
	{
		srand(1);
		matrixSize = sizeOfMatrix;
		matrixA = new float* [matrixSize];
		matrixB = new float* [matrixSize];
		result = new float* [matrixSize];
		for (int i = 0;i < matrixSize;i++)
		{
			matrixA[i] = new float[matrixSize];
			matrixB[i] = new float[matrixSize];
			result[i] = new float[matrixSize];

			for (int j = 0;j < matrixSize;j++)
			{
				matrixA[i][j] = 1 + rand() % 10;
				matrixB[i][j] = 1 + rand() % 10;
				result[i][j] = 0;
			}
		}
	}
	void Compute()
	{
		results.open("Results.csv");
		cout << endl << "--------------------OMP started---------------------" << endl;
		for (int iterator = 0;iterator < 1;iterator++)
		{
			auto start = chrono::high_resolution_clock::now();
			#pragma omp parallel for num_threads(12)
			for (int i = 0;i < matrixSize;i++)
			{
				for (int j = 0;j < matrixSize;j++)
				{
					for (int k = 0;k < matrixSize;k++)
					{
						result[i][j] += (matrixA[i][k] * matrixB[k][j]);
					}
				}
			}
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, std::milli> dur = end - start;
			results << dur.count() << ";";
			cout << endl << "iteration: " << iterator + 1 << " time: " << dur.count() << endl;
		}
	}

	~OmpMultiplier()
	{
		for (int i = 0;i < matrixSize;i++)
		{
			delete[] matrixA[i];
			delete[] matrixB[i];
			delete[] result[i];
		}

		delete matrixA;
		delete matrixB;
		delete result;
	}
};