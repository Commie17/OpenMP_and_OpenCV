#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <omp.h>
#include <fstream>

using namespace cv;
using namespace std;

class PictureHandler
{
    std::vector<Mat> first;
    std::vector<Mat> second;
    std::vector<Mat> result;
    Mat tmp;
public:
    PictureHandler(string firstPath, string secondPath);
    void OmpProcessImages(int pairNumber);
    void SingleProcessImages(int pairNumber);
    void LoadResultToFile(string type);
};