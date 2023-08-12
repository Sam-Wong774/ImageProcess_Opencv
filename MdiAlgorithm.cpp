#include "stdafx.h"
#include "MdiAlgorithm.h"

bool Mat2QImage(const cv::Mat& mat, QImage& outqimage, QImage::Format format, bool copyFlag) noexcept
{
    if (mat.empty())
        return FALSE;
    if (copyFlag)
        outqimage = QImage((const uchar*)(mat.data), mat.cols, mat.rows, (int)mat.step, format).copy();
    else
        outqimage = QImage((const uchar*)(mat.data), mat.cols, mat.rows, (int)mat.step, format);
    return TRUE;
}

bool QImage2Mat(const QImage& qimage, cv::Mat& outmat, int type, bool copyFlag) noexcept
{
    if (qimage.isNull())
        return FALSE;
    if (copyFlag)
        outmat = cv::Mat(qimage.height(), qimage.width(), type, (uchar*)qimage.bits(), qimage.bytesPerLine()).clone();
    else
        outmat = cv::Mat(qimage.height(), qimage.width(), type, (uchar*)qimage.bits(), qimage.bytesPerLine());
    return TRUE;
}

cv::Mat Color2Gray(const cv::Mat& cvMat)
{
    if (cvMat.empty())
        return cv::Mat();
    cv::Mat gray = cvMat.clone();
    if (cvMat.channels() != 1)
        cv::cvtColor(gray, gray, cv::COLOR_RGB2GRAY);
    return gray;
}

