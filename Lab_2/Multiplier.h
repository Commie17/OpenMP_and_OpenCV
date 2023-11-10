#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

int matrixSize = 4096;
uint16_t** matrixA = new uint16_t * [matrixSize];
uint16_t** matrixB = new uint16_t * [matrixSize];
uint16_t** resultSingle = new uint16_t * [matrixSize];
uint16_t** resultOmp = new uint16_t * [matrixSize];

void FillMatrix()
{
	for (int i = 0;i < matrixSize;i++)
	{
		matrixA[i] = new uint16_t[matrixSize];
		matrixB[i] = new uint16_t[matrixSize];
		resultSingle[i] = new uint16_t[matrixSize];
		resultOmp[i] = new uint16_t[matrixSize];

		for (int j = 0;j < matrixSize;j++)
		{
			matrixA[i][j] = 1 + rand() % 10;
			matrixB[i][j] = 1 + rand() % 10;
			resultSingle[i][j] = 0;
			resultOmp[i][j] = 0;
		}
	}
};

class SingleMultiplier
{
public:
	void Compute()
	{
		cout << endl << "--------------------Single started---------------------" << endl;
		for (int iterator = 0;iterator < 10;iterator++)
		{
			auto start = chrono::high_resolution_clock::now();
			for (int i = 0;i < matrixSize;i++)
			{
				for (int j = 0;j < matrixSize;j++)
				{
					for (int k = 0;k < matrixSize;k++)
					{
						resultSingle[i][j] += (matrixA[i][k] + matrixB[k][j]);
					}
				}
			}
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, std::milli> dur = end - start;
			cout << endl << "iteration: " << iterator << " time: " << dur.count()<<endl;
		}
	}
};

class OmpMultiplier
{
public:
	void Compute()
	{
		cout << endl << "--------------------OMP started---------------------" << endl;
		for (int iterator = 0;iterator < 10;iterator++)
		{
			auto start = chrono::high_resolution_clock::now();
			#pragma omp parallel for num_threads(12)
			for (int i = 0;i < matrixSize;i++)
			{
				for (int j = 0;j < matrixSize;j++)
				{
					for (int k = 0;k < matrixSize;k++)
					{
						resultOmp[i][j] += (matrixA[i][k] + matrixB[k][j]);
					}
				}
			}
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, std::milli> dur = end - start;
			cout << endl << "iteration: " << iterator << " time: " << dur.count() << endl;
		}
	}
};

void ClearMatrix()
{
	for (int i = 0;i < matrixSize;i++)
	{
		delete[] matrixA[i];
		delete[] matrixB[i];
		delete[] resultSingle[i];
		delete[] resultOmp[i];
	}

	delete matrixA;
	delete matrixB;
	delete resultSingle;
	delete resultOmp;
};