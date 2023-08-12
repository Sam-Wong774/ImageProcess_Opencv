#include "stdafx.h"
#include "QMultiMdiSub.h"

QMultiMdiSub::QMultiMdiSub(QWidget* parent) 
    : QMdiSubWindow(parent), 
      m_pMatLabel(Q_NULLPTR)
{
    setAttribute(Qt::WA_DeleteOnClose);
    installEventFilter(this);
}

QMultiMdiSub::QMultiMdiSub(const QString& absFilePath, QWidget* parent)
    : QMdiSubWindow(parent)
{   
    m_strAbsFilePath = absFilePath;
    m_pMatLabel      = new QMultiLabel(this);
    if (!m_pMatLabel->SetMat(m_strAbsFilePath))
    {
        qDebug() << "QMultiMdiSub readMat failed!(filepath)";
        delete m_pMatLabel;
        m_pMatLabel = Q_NULLPTR;
        return;
    }
    setAttribute(Qt::WA_DeleteOnClose);
    installEventFilter(this);
    m_pMatLabel->setPixmap(QPixmap::fromImage(m_pMatLabel->GetShowQimage()));
    this->setWidget(m_pMatLabel);
}

QMultiMdiSub::QMultiMdiSub(const cv::Mat& cvMat, QWidget* parent)
    : QMdiSubWindow(parent)
{
    m_strAbsFilePath.clear();
    m_pMatLabel = new QMultiLabel(this);
    if (!m_pMatLabel->SetMat(cvMat))
    {
        qDebug() << "QMultiMdiSub readMat failed!(other cvMat)";
        delete m_pMatLabel;
        m_pMatLabel = Q_NULLPTR;
        return;
    }
    setAttribute(Qt::WA_DeleteOnClose);
    installEventFilter(this);
    m_pMatLabel->setPixmap(QPixmap::fromImage(m_pMatLabel->GetShowQimage()));
    setWidget(m_pMatLabel);
}

QMultiMdiSub::~QMultiMdiSub()
{
    if (m_pMatLabel) delete m_pMatLabel;
} 

QString QMultiMdiSub::GetAbsFilePath() const
{
    return m_strAbsFilePath;
}

QMultiLabel* QMultiMdiSub::GetLoadLabel() const
{
    return m_pMatLabel;
}

