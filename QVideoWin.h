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
    QCamera*                    m_pQCamera;         //��������ͷָ�����
    QCameraViewfinder*          m_pViewfind;        //����ȡ����ָ�����
    QCameraImageCapture*        m_pImageCapture;    //��������ͷ��ǰ֡
    QList<QCameraInfo>          m_qlistCameras;     //�����������ͷ������Ϣ�б�

    cv::VideoCapture*           m_pCvCapture;       //opencv����ͷ����
    

};
#endif // !_VIDEOWINDOW_Q



