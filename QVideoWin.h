#pragma once
#ifndef _VIDEOWINDOW_Q
#define _VIDEOWINDOW_Q
#include <qwidget.h>
#include <qtimer.h>
#include <qimage.h>
#include <qcamera.h>
#include <qcameraviewfinder.h>
#include <qcameraimagecapture.h>
#include <qcamerainfo.h>
#include <qsizepolicy.h>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include "QVideoLabel.h"

class QVideoWin :
    public QWidget
{
    Q_OBJECT

public:
    explicit QVideoWin(QWidget* parent = Q_NULLPTR);
    virtual ~QVideoWin();
    enum VIDEOSTREAMWAY {
        _OPENCV,
        _QCAMARA,
    };
    Q_ENUM(VIDEOSTREAMWAY)
    BOOL OpenVideoStream(VIDEOSTREAMWAY openWay);
    BOOL SaveVideo();

protected:
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

public slots:
    void ReadFarme();
    void CloseVideoStream(VIDEOSTREAMWAY openWay);
    void GetSnap();
    void StopVideoStream();

private:
    Q_DISABLE_COPY(QVideoWin)
    QCamera*                    m_pQCamera;         //定义摄像头指针对象
    QCameraViewfinder*          m_pViewfind;        //定义取景器指针对象
    QCameraImageCapture*        m_pImageCapture;    //定义摄像头当前帧
    QList<QCameraInfo>          m_qlistCameras;     //定义可用摄像头序列信息列表

    cv::VideoCapture*           m_pCvCapture;       //opencv摄像头捕获
    

};
#endif // !_VIDEOWINDOW_Q



