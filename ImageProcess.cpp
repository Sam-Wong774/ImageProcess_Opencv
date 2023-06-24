#include "stdafx.h"
#include "ImageProcess.h"

ImageProcess::ImageProcess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageProcessClass())
{
    ui->setupUi(this);
}

ImageProcess::~ImageProcess()
{
    delete ui;
}
