#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ImageProcess.h"
#include "QMultiMdi.h"
#include "QVideoWin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ImageProcessClass; };
QT_END_NAMESPACE

class ImageProcess : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcess(QWidget *parent = nullptr);
    ~ImageProcess();

protected:
    virtual void closeEvent(QCloseEvent* ev) Q_DECL_OVERRIDE;
    void Initialized();
    bool InitLayout();
    bool InitConnection();
    void SetMdiCtrlVisible(bool bVisible);
    void SetVideoCtrlVisible(bool bVisible);

protected slots:
    void ChangeTabWidget(int index);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionColor2Gray_triggered();
    void on_actionOpenCamera_triggered();
    void VideoStreamPath(const QString& path);
    void VideoStreamHeight(int nHeight);
    void VideoStreamWidth(int nWidth);

private:
    Ui::ImageProcessClass*      ui;
    QMultiMdi*                  m_pMdi;
    QVideoWin*                  m_pVideo;
};
