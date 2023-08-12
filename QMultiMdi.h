#pragma once
#include <qmdiarea.h>
#include "QMultiMdiSub.h"

static const QString SaveImgFilter("image(*.bmp);;image(*.jpg);;image(*.png);;image(*.tiff)");
static const QString OpenImgFilter("all files(*.*);;image(*.bmp);;image(*.jpg);;image(*.png);;image(*.tiff)");
static QString RecentlyOpenDir = QDir::currentPath();
static QString RecentlySaveDir = QDir::currentPath();
// define function pointer
#ifndef _REGISTER_FUNC_Q
#define _REGISTER_FUNC_Q
#include <functional>
#include <qpair.h>
#include <qmap.h>
#include <opencv2/core.hpp>

typedef std::function<cv::Mat(const cv::Mat&)>					ptrOneMat;
typedef QMap<QString, ptrOneMat>								mapFuncOneMat;
typedef std::function<cv::Mat(const cv::Mat&, const cv::Mat&)>	ptrTwoMat;
typedef QMap<QString, ptrTwoMat>								mapFuncTwoMat;
typedef std::function<QString(const cv::Mat&)>					ptrOneStr;
typedef QMap<QString, ptrOneStr>								mapOneStr;
typedef std::function<QString(const cv::Mat&, const cv::Mat&)>	ptrTwoStr;
typedef QMap<QString, ptrTwoStr>								mapTwoStr;

enum class FunctionTask {
    NONE,
    PTRONEMAT,
    PTRTWOMAT,
    PTRONESTR,
    PTRTWOSTR,
};

#define REGISTER_FUNCTION(name, func, mapFuncContainer)  {\
        if(mapFuncContainer.find(name) == mapFuncContainer.end())\
        mapFuncContainer.insert(name, func);}

#define CALLREGISTER_FUNCTION(name, mapFuncContainer)  mapFuncContainer[name];
#endif // !_REGISTER_FUNC_Q

class QMultiMdi :
    public QMdiArea
{
    Q_OBJECT

public:
    explicit QMultiMdi(QWidget* parent = Q_NULLPTR);
    virtual ~QMultiMdi();
    void OpenWindow();
    void SaveWindow();
    void ReadSettings();
    void WriteSettings();
    void Restricted(const QCursor& cursor);
    void Released();
    inline QCursor GetMyCursorA() { return QCursor(QPixmap(":/resource/bin64/resourse/pointA.cur")); }
    inline QCursor GetMyCursorB() { return QCursor(QPixmap(":/resource/bin64/resourse/pointB.cur")); }

#ifdef _REGISTER_FUNC_Q
    void SetFunctionTask(const QString& actionname, FunctionTask functionTask);
    mapFuncOneMat m_funcOneMat;
    mapFuncTwoMat m_funcTwoMat;
    mapOneStr	  m_funcOneStr;
    mapTwoStr	  m_funcTwoStr;
    FunctionTask  m_functionTask;
    QString       m_sActionName;
#endif // _REGISTER_FUNC_Q

protected:
    virtual void dragEnterEvent(QDragEnterEvent* ev) Q_DECL_OVERRIDE;
    virtual void dropEvent(QDropEvent* ev) Q_DECL_OVERRIDE;
    virtual bool eventFilter(QObject* obj, QEvent* ev) Q_DECL_OVERRIDE;

public slots:
    bool CreateSubWindow(const QString& path);
    bool CreateSubWindow(const QString& windowname, const cv::Mat& mat);
    inline QMultiMdiSub* ActiveSubWindow() Q_DECL_NOEXCEPT;
    void SaveWindowClosing();

private:

};



