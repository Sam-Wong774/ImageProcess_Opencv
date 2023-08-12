#pragma once
#include <qlabel.h>
class QVideoLabel :
    public QLabel
{
    Q_OBJECT
public:
    explicit QVideoLabel(QWidget* parent = Q_NULLPTR);
    virtual ~QVideoLabel();
};

