#include "stdafx.h"
#include "QMultiLabel.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

QMultiLabel::QMultiLabel(QWidget* parent) 
	: QLabel(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	setScaledContents(TRUE);
}

QMultiLabel::~QMultiLabel()
{

}

bool QMultiLabel::Empty() const
{
	return m_cvMat.empty();
}

cv::Mat QMultiLabel::GetMat() const
{
	return m_cvMat;
}

cv::Mat QMultiLabel::GetMatClone()
{
	return m_cvMat.clone();
}

QImage QMultiLabel::GetShowQimage() const
{
	return m_showQImage;
}

bool QMultiLabel::SetMat(const QString& absolutedFilepath)
{
	try
	{
		if (absolutedFilepath.isEmpty())
			return FALSE;
		cv::String path = absolutedFilepath.toLocal8Bit().constData();
		if (!SetMat(cv::imread(path, g_mdiParam.cvImreadModesFlags)))
			return FALSE;
	}
	catch (const cv::Exception& excep)
	{
		qDebug() << excep.what();
		return FALSE;
	}
	return TRUE;
}

bool QMultiLabel::SetMat(const cv::Mat& cvMat)
{
	try
	{
		if (cvMat.empty())
			return FALSE;
		m_cvMat = cvMat;				//	important, shadow copy!
		if (m_cvMat.channels() == 3)
		{
			m_cvMat.convertTo(m_cvMat, CV_8UC3);
			// imread the image matrix, default color-space is BGR
			cv::cvtColor(m_cvMat, m_cvMat, cv::ColorConversionCodes::COLOR_BGR2RGB);
			Mat2QImage(m_cvMat, m_showQImage, QImage::Format_RGB888, g_mdiParam.bNormalizeFlag);
		}
		else if (m_cvMat.channels() == 1)
		{
			m_cvMat.convertTo(cvMat, CV_8UC1);
			Mat2QImage(m_cvMat, m_showQImage, QImage::Format_Grayscale8, g_mdiParam.bNormalizeFlag);
		}
		else
		{
			qDebug() << "Temporarily unable to resolve image display issues for other channels";
			return FALSE;
		}

		if (g_mdiParam.bNormalizeFlag)
			cv::normalize(m_cvMat, m_cvMat, 0, 255, cv::NORM_MINMAX);

		setMinimumSize(m_cvMat.rows, m_cvMat.cols);
		return TRUE;
	}
	catch (const cv::Exception& excep)
	{
		qDebug() << excep.what();
		return FALSE;
	}
	return TRUE;
}

bool QMultiLabel::SaveMat(QString absolutedFilepath)
{
	try
	{
		if (m_cvMat.empty() || absolutedFilepath.isEmpty())
			return FALSE;

		QString suf = QFileInfo(absolutedFilepath).suffix().toUpper();
		if (suf == "PNG" || suf == "JPG" || suf == "TIFF")
			m_cvMat.convertTo(m_cvMat, CV_8U);

		// if matrix ColorConversionCodes is 3, we convert the color-space to BGR!
		if (m_cvMat.channels() == 3)
			cv::cvtColor(m_cvMat, m_cvMat, cv::COLOR_RGB2BGR);

		//	call cv::imwrite!
		if (!cv::imwrite(cv::String(absolutedFilepath.toLocal8Bit().toStdString().data()), m_cvMat))
			return FALSE;
	}
	catch (const cv::Exception& excep)
	{
		qDebug() << excep.what();
		return FALSE;
	}
	return TRUE;
}

