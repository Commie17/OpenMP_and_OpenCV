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
    float** result1024 = new float* [768];
    float** result1280 = new float* [960];
    float** result2048 = new float* [1536];
    ofstream result_1024, result_1280, result_2048;

public:
    PictureHandler(string firstPath,string secondPath)
    {
        for (int i = 0;i < 1536;i++)
        {
            if (i < 768)
            {
                result1024[i] = new float[1024];
                result1280[i] = new float[1280];
                result2048[i] = new float[2048];
            }
            else if (i < 960)
            {
                result1280[i] = new float[1280];
                result2048[i] = new float[2048];
            }
            else
            {
                result2048[i] = new float[2048];
            }
        }

        Mat tmp;
        for (int i = 0;i < 3;i++)
        {
            tmp = imread(firstPath + to_string(i+1)+".jpg", IMREAD_COLOR);
            first.push_back(tmp);

            tmp = imread(secondPath + to_string(i+1)+".jpg", IMREAD_COLOR);
            second.push_back(tmp);

            if (second[i].empty() || first[i].empty())
            {
                cout << "\n Uncorrected path or image\n";
                break;
            }

            
        }
    }
    
    void OmpProcessImages(int pairNumber)
    {
        float tmp;

        cout << endl << "----------Omp images processing-----------" << endl;
        for (int iterator = 0;iterator < 10;iterator++)
        {
            auto start = chrono::high_resolution_clock::now();
            #pragma omp parallel for num_threads(12)
            for (int i = 0;i < first[pairNumber].rows;i++)
            {
                for (int j = 0;j < first[pairNumber].cols;j++)
                {
                    tmp = first[pairNumber].at<Vec3b>(i, j)[0] + second[pairNumber].at<Vec3b>(i, j)[0];
                    tmp += (first[pairNumber].at<Vec3b>(i, j)[1] + second[pairNumber].at<Vec3b>(i, j)[1]);
                    tmp += (first[pairNumber].at<Vec3b>(i, j)[2] + second[pairNumber].at<Vec3b>(i, j)[2]);
                    tmp /= 3;
                    tmp = 255 * tmp / 510;
                    switch (pairNumber) 
                    {
                    case 0:
                        result1024[i][j] = tmp;
                        break;
                    case 1:
                        result1280[i][j] = tmp;
                        break;
                    case 2:
                        result2048[i][j] = tmp;
                        break;
                    }
                }
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> dur = end - start;

            cout << endl << "iteration: " << iterator << " time: " << dur.count() << endl;
        }
    }

    void SingleProcessImages(int pairNumber)
    {
        float tmp;

        cout << endl << "----------Single images processing-----------" << endl;
        for (int iterator = 0;iterator < 10;iterator++)
        {
            auto start = chrono::high_resolution_clock::now();
            for (int i = 0;i < first[pairNumber].rows;i++)
            {
                for (int j = 0;j < first[pairNumber].cols;j++)
                {
                    tmp = first[pairNumber].at<Vec3b>(i, j)[0] + second[pairNumber].at<Vec3b>(i, j)[0];
                    tmp += (first[pairNumber].at<Vec3b>(i, j)[1] + second[pairNumber].at<Vec3b>(i, j)[1]);
                    tmp += (first[pairNumber].at<Vec3b>(i, j)[2] + second[pairNumber].at<Vec3b>(i, j)[2]);
                    tmp /= 3;
                    tmp = 255 * tmp / 510;
                    switch (pairNumber)
                    {
                    case 0:
                        result1024[i][j] = tmp;
                        break;
                    case 1:
                        result1280[i][j] = tmp;
                        break;
                    case 2:
                        result2048[i][j] = tmp;
                        break;
                    }
                }
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> dur = end - start;

            cout << endl << "iteration: " << iterator << " time: " << dur.count() << endl;
        }
    }

    void LoadResultToFile()
    {
        result_1024.open("D:/Images/result_1024.csv");
        result_1280.open("D:/Images/result_1280.csv");
        result_2048.open("D:/Images/result_2048.csv");
        result_1024.clear();
        result_1280.clear();
        result_2048.clear();
        #pragma omp parallel for num_threads(12)
        for (int i = 0;i < 1536;i++)
        {
            for (int j = 0;j < 2048;j++)
            {
                if (i < 768 && j < 1024)
                {
                    result_1024 << result1024[i][j] << ";";
                    result_1280 << result1280[i][j] << ";";
                    result_2048 << result2048[i][j] << ";";
                }
                else if (i < 960 && j < 1280)
                {
                    result_1280 << result1280[i][j] << ";";
                    result_2048 << result2048[i][j] << ";";
                }
                else
                {
                    result_2048 << result2048[i][j] << ";";
                }
            }
            result_1024 << endl;
            result_1280 << endl;
            result_2048 << endl;
        }

    }

    ~PictureHandler()
    {
        for (int i = 0;i < 1536;i++)
        {
            if (i < 768)
            {
                delete[] result1024[i];
                delete[] result1280[i];
                delete[] result2048[i];
            }
            else if (i < 960)
            {
                delete[] result1280[i];
                delete[] result2048[i];
            }
            else
            {
                delete[] result2048[i];
            }
        }
        delete[] result1024;
        delete[] result1280;
        delete[] result2048;
    }
};