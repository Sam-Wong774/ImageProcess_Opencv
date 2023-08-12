#include "stdafx.h"
#include "QVideoWin.h"

QVideoWin::QVideoWin(QWidget* parent)
	: QWidget(parent)
{
	m_qlistCameras	= QCameraInfo::availableCameras();
	m_pQCamera		= Q_NULLPTR;
	m_pImageCapture = Q_NULLPTR;
	m_pViewfind		= Q_NULLPTR;
	m_pCvCapture	= Q_NULLPTR;
}

QVideoWin::~QVideoWin()
{
	CloseVideoStream(VIDEOSTREAMWAY::_OPENCV);
	
}

BOOL QVideoWin::OpenVideoStream(VIDEOSTREAMWAY openWay)
{
	if (VIDEOSTREAMWAY::_OPENCV == openWay)
	{
		CloseVideoStream(_QCAMARA);
		m_pCvCapture = new cv::VideoCapture(0);
		if (m_pCvCapture->isOpened())
		{
			qDebug() << "宽度：" << m_pCvCapture->get(cv::CAP_PROP_FRAME_WIDTH);
		}
		else
		{
			return FALSE;
		}
		while (TRUE)
		{
			cv::Mat frame;
			*m_pCvCapture >> frame;
			if (frame.empty())
				break;
			cv::imshow("video", frame);
			cv::waitKey(1000/m_pCvCapture->get(cv::CAP_PROP_FPS));
		}
	}
	else if (VIDEOSTREAMWAY::_QCAMARA)
	{
		CloseVideoStream(_OPENCV);
		if (m_qlistCameras.isEmpty())
		{
			QMessageBox::warning(NULL, tr("警告"), tr("暂无可用摄像头资源！"));
			return FALSE;
		}
		if (m_pQCamera)
		{
		}
		m_pQCamera = new QCamera(m_qlistCameras[0]);						//可选择序号显示摄像头
		
		m_pQCamera->setCaptureMode(QCamera::CaptureMode::CaptureVideo);		//设置捕获方式	
		m_pViewfind = new QCameraViewfinder(this);							//关联取景器
		m_pViewfind->resize(this->size());
		qDebug() << "this->size() :" << this->size();
		m_pViewfind->show();
		
		m_pQCamera->setViewfinder(m_pViewfind);								//相机匹配取景器

		m_pImageCapture = new QCameraImageCapture(m_pQCamera);				//关联捕获器
		m_pQCamera->start();
	}
	return 0;
}

BOOL QVideoWin::SaveVideo()
{
	return 0;
}

void QVideoWin::resizeEvent(QResizeEvent* event)
{
	if (m_pViewfind) m_pViewfind->resize(this->size());
}

void QVideoWin::ReadFarme()
{

}

void QVideoWin::CloseVideoStream(VIDEOSTREAMWAY openWay)
{
	switch (openWay)
	{
	case _OPENCV:
	{

	}
		break;
	case _QCAMARA:
	{
		if (m_pImageCapture)
			m_pImageCapture->destroyed();
		if (m_pViewfind)
		{
			m_pViewfind->close();
			m_pViewfind->destroyed();
		}
		if (m_pQCamera)
			m_pQCamera->destroyed();	
	}
		break;
	default:
		break;
	}
}

void QVideoWin::GetSnap()
{

}

void QVideoWin::StopVideoStream()
{
}
