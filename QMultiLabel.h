#pragma once
#include <qlabel.h>
#include <qimage.h>
#include "MdiAlgorithm.h"                           //  include mdi algorithm in lowest class

#ifndef _MAT_QLABEL_Q
#define _MAT_QLABEL_Q

typedef struct MdiParam {
    //  all mdirean parameters
    bool                bNormalizeFlag;             //  nromlization flag
    cv::ImreadModes     cvImreadModesFlags;         //  imread model flag
    bool                bSaveByClosing;             //  save window by closing

    //  default construct
    MdiParam() :
        bNormalizeFlag(TRUE),
        cvImreadModesFlags(cv::ImreadModes::IMREAD_UNCHANGED),
        bSaveByClosing(FALSE)
    {}
    void Default()
    {
        bNormalizeFlag = TRUE;
        cvImreadModesFlags = cv::ImreadModes::IMREAD_UNCHANGED;
        bSaveByClosing = FALSE;
    }
    virtual ~MdiParam() {};
}MdiParam;
static MdiParam g_mdiParam;

class QMultiLabel :
    public QLabel
{
   // Q_OBJECT
public:
    explicit QMultiLabel(QWidget* parent = Q_NULLPTR);
    virtual ~QMultiLabel();
    bool Empty() const;
    cv::Mat   GetMat() const;
    cv::Mat   GetMatClone();
    QImage    GetShowQimage() const;
    /*
    * @brief read matrix from filepath!
    * @param absolutedFilepath
    * @return TRUE - successful
    */
    bool SetMat(const QString& absolutedFilepath);
    
    /*
    * @brief read matrix from other matrix!
    * @param cvMat: other matrix
    * @return TRUE - successful
    */
    bool SetMat(const cv::Mat& cvMat);

    /*
    * @brief save the matrix
    * @param absolutedFilepath: saving path(include name!)
    */
    bool SaveMat(QString absolutedFilepath);

protected:
    QMultiLabel(const QMultiLabel&)             = delete;   //Copy construction has been prohibited
    QMultiLabel& operator=(const QMultiLabel&)  = delete;   //Assignment construction has been prohibited
    QMultiLabel& operator!=(const QMultiLabel&) = delete;   //The unequal operator has been prohibited
    QMultiLabel& operator==(const QMultiLabel&) = delete;   //The equality operator has been prohibited
    QMultiLabel& operator<(const QMultiLabel&)  = delete;   //The less than operator has been prohibited
    QMultiLabel& operator>(const QMultiLabel&)  = delete;   //The greater-than operator has been prohibited

private:
    cv::Mat     m_cvMat;
    QImage      m_showQImage;
};

#endif // !_MAT_QLABEL_Q

