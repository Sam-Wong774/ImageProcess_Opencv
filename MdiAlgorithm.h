#pragma once
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
/*
* @biref conver cv::Mat to QImage
* @param mat: must be CV_8UC3/CV_8UC1, color image must conver to RGB first!
* @param outqimage: the output QImage
* @param format: color - QImage::Format_RGB888; gray - QImage::Format_Grayscale8
* @param copyFlag: true - deep copy; false - shallow copy
* @return true - successful; false - failed
*/
bool Mat2QImage(const cv::Mat& mat, QImage& outqimage, QImage::Format format, bool copyFlag = true) noexcept;
/*
* @biref conver QImage to cv::Mat
* @param qimage: must be QImage::Format_RGB888 or QImage::Format_Grayscale8!
* @param outmat: the output cv::Mat
* @param format: color - CV_8UC3; gray - CV_8UC1
* @param copyFlag: true - deep copy; false - shallow copy
* @return true - successful; false - failed
*/
bool QImage2Mat(const QImage& qimage, cv::Mat& outmat, int type, bool copyFlag = true) noexcept;

/*
* @biref color to gray
* @param firstImage: input cvMat
* @return output cvMat
*/
cv::Mat Color2Gray(const cv::Mat& firstImage);
