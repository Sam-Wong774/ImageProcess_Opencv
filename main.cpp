#include "stdafx.h"
#include "ImageProcess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Product By Sam Wong");
    QCoreApplication::setApplicationName("Image Process SoftWare v0.0.1");
    ImageProcess w;
    w.show();
    return a.exec();
}
