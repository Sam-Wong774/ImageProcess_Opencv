#include "stdafx.h"
#include "ImageProcess.h"

ImageProcess::ImageProcess(QWidget *parent)
    : QMainWindow(parent), 
    ui(new Ui::ImageProcessClass()),
    m_pMdi(new QMultiMdi()),
    m_pVideo(new QVideoWin())
{
    ui->setupUi(this);
    Initialized();
}

ImageProcess::~ImageProcess()
{
    delete ui;
    delete m_pMdi;
    delete m_pVideo;
}

void ImageProcess::closeEvent(QCloseEvent* ev)
{
    m_pMdi->WriteSettings();
    return QMainWindow::closeEvent(ev);
}

void ImageProcess::Initialized()
{
    ui->tabWidget->setCurrentIndex(0);
    ChangeTabWidget(0);
    ui->listViewCutImage->setVisible(FALSE);
    Q_ASSERT(InitLayout() && InitConnection());
}

bool ImageProcess::InitLayout()
{
    if (!m_pMdi || !m_pVideo)
        return FALSE;
    static QHBoxLayout* mdiLayout = new QHBoxLayout(ui->MdiWindow);
    mdiLayout->setMargin(0);
    mdiLayout->addWidget(m_pMdi);
    static QHBoxLayout* videoLayout = new QHBoxLayout(ui->VideoFrame);
    videoLayout->setMargin(0);
    videoLayout->addWidget(m_pVideo);

    return TRUE;
}

bool ImageProcess::InitConnection()
{
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &ImageProcess::ChangeTabWidget);
    return TRUE;
}

void ImageProcess::SetMdiCtrlVisible(bool bVisible)
{
    ui->actionColor2Gray->setVisible(bVisible);


}

void ImageProcess::SetVideoCtrlVisible(bool bVisible)
{
    ui->actionOpenCamera->setVisible(bVisible);

}

void ImageProcess::ChangeTabWidget(int index)
{
    switch (index)
    {
    case 0:
    {
        SetMdiCtrlVisible(TRUE);
        SetVideoCtrlVisible(FALSE);
    }
        break;
    case 1:
    {
        SetVideoCtrlVisible(TRUE);
        SetMdiCtrlVisible(FALSE);
    }
        break;
    default:
        break;
    }
}

void ImageProcess::on_actionOpen_triggered()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        m_pMdi->OpenWindow();
    }
    else if (ui->tabWidget->currentIndex() == 1)
    {
        m_pVideo->OpenVideoStream(QVideoWin::VIDEOSTREAMWAY::_OPENCV);
    }
}

void ImageProcess::on_actionSave_triggered()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        m_pMdi->SaveWindow();
    }
    else if (ui->tabWidget->currentIndex() == 1)
    {
        m_pVideo->SaveVideo();
    }

}

void ImageProcess::on_actionColor2Gray_triggered()
{
    if (ui->tabWidget->currentIndex() != 0) return;
    REGISTER_FUNCTION(ui->actionColor2Gray->text(), Color2Gray, m_pMdi->m_funcOneMat);
    m_pMdi->SetFunctionTask(ui->actionColor2Gray->text(), FunctionTask::PTRONEMAT);
}

void ImageProcess::on_actionOpenCamera_triggered()
{
    if (ui->tabWidget->currentIndex() != 1) return;
    qDebug() << "ui->VideoFrame.size() : " << ui->VideoFrame->size();
    m_pVideo->OpenVideoStream(QVideoWin::VIDEOSTREAMWAY::_QCAMARA);
}

void ImageProcess::VideoStreamPath(const QString& path)
{
    ui->EditVideoStreamPath->setText(path);
}

void ImageProcess::VideoStreamHeight(int nHeight)
{
    ui->VideoHeight->setText(tr("¸ß£º%1").arg(nHeight));
}

void ImageProcess::VideoStreamWidth(int nWidth)
{
    ui->VideoWidth->setText(tr("¿í£º%1").arg(nWidth));
}
