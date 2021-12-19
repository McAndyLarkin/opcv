#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/stitching.hpp"

class Laba2 {
public:
     static int start(string file) {
        Mat image, result;

        String imagePath(file);
        if (argc > 1){
            imagePath = argv[1];
        }
        image = imread(imagePath);

        if (image.empty())
        {
            std::cout << "Could not read the image: " << imagePath << std::endl;
            return 1;
        }

        Blur(image, result, 6);
        imshow("Blur", result);

        SobelGradient(image, result);
        imshow("Gradient", result);

        waitKey(0);

        return 0;
	}

private: 
    static uchar calculatePixel(const cv::Mat& image, const std::vector<std::vector<double>>& kernel, int i, int j) {
        int newPixel = 0;

        for (int offsetI = 0; offsetI < convolutionMatrix.size(); ++offsetI) {
            for (int offsetJ = 0; offsetJ < convolutionMatrix.size(); ++offsetJ) {
                newPixel += image.at<uchar>(i + offsetI, j + offsetJ) * convolutionMatrix[offsetI][offsetJ];
            }
        }

        return saturate_cast<uchar>(newPixel);
    }

    static void MatrixFilter(const cv::Mat& image, cv::Mat& result, const std::vector<std::vector<double>>& convolutionMatrix) {
        int border = convolutionMatrix.size() / 2;

        vector<Mat> colorChannels;
        split(image, colorChannels);
        vector<Mat> resultColorChannels = colorChannels;

        for (int i = border; i < image.rows - border; ++i) {
            for (int j = border; j < image.cols - border; ++j) {
                for (int k = 0; k < resultColorChannels.size(); k++) {
                    resultColorChannels[k].at<uchar>(i, j) = calculatePixel(colorChannels[k], convolutionMatrix, i, j);
                }
            }
        }
        merge(resultColorChannels, result);
    }

    static void Blur(const cv::Mat& image, cv::Mat& result, unsigned size) {
        image.copyTo(result);
        vector<vector<double> > convolutionMatrix(size, vector<double>(size, 1. / (size * size)));
        MatrixFilter(image, result, convolutionMatrix);
    }

    static void SobelGradient(const cv::Mat& image, cv::Mat& result) {
        image.copyTo(result);
        vector<vector<double> > convolutionMatrix = { 
            {-1, -2, -1},{0, 0, 0},{1, 2, 1} };
        MatrixFilter(image, result, convolutionMatrix);
    }
};

class Laba1 {
    int max_pic_in_row = 3;
    int max_pic_in_column = 2;
    int size = 300;
    int scale;
    int max;
    int width_pic;
    int height_pic;
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
        Mat image;
        cvtColor(picture, image, COLOR_RGB2GRAY);
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
    Laba2().start("");
    Laba1().start("");
    Laba4().start(2, "", "");
}