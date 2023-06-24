#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageProcess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ImageProcessClass; };
QT_END_NAMESPACE

class ImageProcess : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcess(QWidget *parent = nullptr);
    ~ImageProcess();

private:
    Ui::ImageProcessClass *ui;
};

template <size_t T>
constexpr size_t Sizeof(const char(&p)[T])
{
    return T;
}