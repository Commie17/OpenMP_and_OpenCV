#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <omp.h>
#include <fstream>
#include "PicturesHandler.h"
#include "Multiplier.h"

using namespace std;

const int matSize = 4096;

int main()
{

	//PictureHandler handler("D:/Images/First/", "D:/Images/Second/");
	Multiplier multiplier(matSize);

	/*cout << "Process images" << endl;
	for (int i = 0;i < 6;i++)
	{
		if (i < 3)
			handler.OmpProcessImages(i);
		else
			handler.SingleProcessImages(i % 3);
	}*/

	cout << "Compute matrix" << endl;
	//multiplier.SingleCompute();
	multiplier.OmpCompute();
	return 0;
}