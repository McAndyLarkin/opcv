#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

class Laba2 {
public:
     static int start(string file) {
        Mat image, result;
        image = imread(file);

        if (image.empty()){
            cout << "Input Error " << imagePath << endl;
            return 1;
        }

        get_blur(image, result, 6);
        imshow("Blur", result);

        get_gradient(image, result);
        imshow("Gradient", result);

        waitKey(0);

        return 0;
	}

private: 
    static uchar pixel(const Mat& image, const vector<vector<double>>& kernel, int i, int j) {
        int newPixel = 0;

        for (int offsetI = 0; offsetI < convolutionMatrix.size(); ++offsetI)
            for (int offsetJ = 0; offsetJ < convolutionMatrix.size(); ++offsetJ) 
                newPixel += image.at<uchar>(i + offsetI, j + offsetJ) * convolutionMatrix[offsetI][offsetJ];

        return saturate_cast<uchar>(newPixel);
    }

    static void get_blur(const Mat& image, Mat& result, unsigned size) {
        image.copyTo(result);
        vector<vector<double> > convolutionMatrix(size, vector<double>(size, 1. / (size * size)));
        int border = convolutionMatrix.size() / 2;

        vector<Mat> colorChannels;
        split(image, colorChannels);
        vector<Mat> resultColorChannels = colorChannels;

        for (int i = border; i < image.rows - border; ++i) 
            for (int j = border; j < image.cols - border; ++j) 
                for (int k = 0; k < resultColorChannels.size(); k++) 
                    resultColorChannels[k].at<uchar>(i, j) = pixel(colorChannels[k], convolutionMatrix, i, j);

        merge(resultColorChannels, result);
    }

    static void get_gradient(const Mat& image, Mat& result) {
        image.copyTo(result);
        vector<vector<double> > convolutionMatrix = { 
            {-1, -2, -1},{0, 0, 0},{1, 2, 1} };
        int border = convolutionMatrix.size() / 2;

        vector<Mat> colorChannels;
        split(image, colorChannels);
        vector<Mat> resultColorChannels = colorChannels;

        for (int i = border; i < image.rows - border; ++i) 
            for (int j = border; j < image.cols - border; ++j) 
                for (int k = 0; k < resultColorChannels.size(); k++) 
                    resultColorChannels[k].at<uchar>(i, j) = pixel(colorChannels[k], convolutionMatrix, i, j);
        merge(resultColorChannels, result);
    }
};

class Laba1 {
    Mat image;
public:
     static int start(string file) {
        image = imread(file, IMREAD_COLOR);
    
        if (image.empty()) {
            cout << "Input Error" << argv[i] << endl;
            return -1;
        }

        grey();
        hue();
        gauss();
        canny();
        negative();
     }

private:
    static void grey(){
        Mat picture;
        cvtColor(image, picture, COLOR_RGB2GRAY);
        namedWindow("grey");
        imshow("grey", image);
        waitKey(0);
    }

    static void hue(){  
        Mat hueimage;
        cvtColor(image, hueimage, COLOR_BGR2HSV);
        namedWindow("hueimage");
        imshow("hueimage", hueimage);
        waitKey(0);
    }

    static void gauss(){
        Mat gaussepic;
        GaussianBlur(image, gaussepic, Size(51, 51), 10);
        namedWindow("gaussepic");
        imshow("gaussepic", gaussepic);
        waitKey(0);
    }

    static void canny(){   
        Mat cannyimage;
        Canny(image, cannyimage, 10, 350);
        cvtColor(cannyimage, cannyimage, COLOR_GRAY2BGR);
        namedWindow("cannyimage");
        imshow("cannyimage", cannyimage);
        waitKey(0);
    }

    static void negative(){
        Mat negativeimage;
        negativeimage = 255 - image;
        namedWindow("negativeimage");
        imshow("negativeimage", negativeimage);
        waitKey(0);
    }
};

class Laba4 {
private:
    vector<Mat> images;
    Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);

public:
    void start(size_t number, string* images) }
        for (int i = 0; i < number; ++i){
            Mat image = imread(images[i]);
            if (image.empty()) {
                cout << "Input Error" << argv[i] << endl;
                return -1;
            }
            images.push_back(image);
        }
    
        Mat panorama = sew();
        if (panorama != nullptr){
            namedWindow("panorama");
            imshow("panorama", panorama);
            waitKey(0);
        }
        
        return 0;
    }
private:
    Mat sew() {
        Mat result;
        if (stitcher->stitch(images, result); == Stitcher::OK)
            return result;
        else
            return nullptr
    }
};

class Lab3{



int main(int argc, char** argv) {
    Laba2().start("piter.png");
    Laba1().start("piter.png");
    Laba4().start(3, "pan1.png", "pan2.png", "pan3.png");
}