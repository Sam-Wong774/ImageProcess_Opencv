#pragma once
#include "QMultiLabel.h"
#include <qmdisubwindow.h>


class QMultiMdiSub : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit QMultiMdiSub(QWidget* parent = Q_NULLPTR);
    explicit QMultiMdiSub(const QString& absFilePath, QWidget* parent = Q_NULLPTR);
    explicit QMultiMdiSub(const cv::Mat& cvMat, QWidget* parent = Q_NULLPTR);
    virtual ~QMultiMdiSub();
    QString  GetAbsFilePath() const;
    QMultiLabel* GetLoadLabel() const;

private:
    QString         m_strAbsFilePath;
    QMultiLabel*    m_pMatLabel;

};



