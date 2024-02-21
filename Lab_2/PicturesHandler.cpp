#include "PicturesHandler.h"

void PictureHandler::OmpProcessImages(int pairNumber)
{
    float tmp = 0;

    cout << endl << "OMP, Pair number is " << pairNumber + 1 << endl;
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
                tmp /= 6;
                result[pairNumber].at<uchar>(i, j) = tmp;
            }
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> dur = end - start;

        cout << endl << "iteration: " << iterator + 1 << " time: " << dur.count() << endl;
    }

    LoadResultToFile("OMP");
}

PictureHandler::PictureHandler(string firstPath, string secondPath)
{
    for (int i = 0;i < 3;i++)
    {
        tmp = imread(firstPath + to_string(i + 1) + ".jpg", IMREAD_COLOR);
        first.push_back(tmp);

        tmp = imread(secondPath + to_string(i + 1) + ".jpg", IMREAD_COLOR);
        second.push_back(tmp);

        tmp = Mat::zeros(first[i].rows,first[i].cols,CV_8UC1);
        result.push_back(tmp);

        if (second[i].empty() || first[i].empty())
        {
            cout << "\n Uncorrected path or image\n";
            break;
        }
    }
}

void PictureHandler::LoadResultToFile(string type)
{
    imwrite(type+"_pair_1.jpg", result[0]);
    imwrite(type+"_pair_2.jpg", result[1]);
    imwrite(type+"_pair_3.jpg", result[2]);
}

void PictureHandler::SingleProcessImages(int pairNumber)
{
    float tmp = 0;

    cout << endl << "Single processing, Pair number is " << pairNumber + 1 << endl;

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
                tmp /= 6;
                result[pairNumber].at<uchar>(i, j) = tmp;
            }
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> dur = end - start;

        cout << endl << "iteration: " << iterator + 1 << " time: " << dur.count() << endl;
    }

    LoadResultToFile("Single");
}