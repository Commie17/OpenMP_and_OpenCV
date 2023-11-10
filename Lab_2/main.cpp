#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "PicturesHandler.h"
#include "Multiplier.h"

using namespace std;

int main()
{
	PictureHandler handler("D:/Images/First/", "D:/Images/Second/");
	OmpMultiplier omp;
	SingleMultiplier single;

	cout << "Process images" << endl;
	handler.OmpProcessImages(0);
	handler.OmpProcessImages(1);
	handler.OmpProcessImages(2);
	handler.SingleProcessImages(0);
	handler.SingleProcessImages(1);
	handler.SingleProcessImages(2);
	handler.LoadResultToFile();

	cout << "Compute matrix" << endl;
	FillMatrix();
	omp.Compute();
	single.Compute();
	ClearMatrix();
}