#include "stdafx.h"
#include "QMultiMdi.h"
#include <qfiledialog.h>
#include <qstringlist.h>
#include <qexception.h>

QMultiMdi::QMultiMdi(QWidget* parent)
	: QMdiArea(parent)
{
	m_functionTask = FunctionTask::NONE;
	this->installEventFilter(this);
	connect(this, &QMultiMdi::destroyed, this, &QMultiMdi::SaveWindowClosing);
}

QMultiMdi::~QMultiMdi()
{

}

void QMultiMdi::dragEnterEvent(QDragEnterEvent* ev)
{
	ev->acceptProposedAction();
}

void QMultiMdi::dropEvent(QDropEvent* ev)
{
	QString filepath = ev->mimeData()->urls().first().toLocalFile();
	CreateSubWindow(filepath);
}

bool QMultiMdi::eventFilter(QObject* obj, QEvent* ev)
{
	if (ev->type() == QEvent::MouseButtonPress && ((QMouseEvent*)ev)->button() == Qt::RightButton && cursor().shape() != Qt::CursorShape::ArrowCursor)
	{
		Released();
		return TRUE;
	}
	if ((QMultiMdiSub*)obj == ActiveSubWindow() && ev->type() == QEvent::MouseButtonPress && ((QMouseEvent*)ev)->button() == Qt::LeftButton && 
		m_functionTask != FunctionTask::NONE	&& !m_sActionName.isEmpty())
	{
		QMultiMdiSub* m_pFirstWindow = ActiveSubWindow();
		Q_ASSERT(m_pFirstWindow != Q_NULLPTR);
		if (m_functionTask == FunctionTask::PTRONEMAT)
		{
			if (m_funcOneMat.find(m_sActionName) != m_funcOneMat.end())
			{
				ptrOneMat pFunc = CALLREGISTER_FUNCTION(m_sActionName, m_funcOneMat);
				cv::Mat mat = pFunc(m_pFirstWindow->GetLoadLabel()->GetMat());
				Q_ASSERT(CreateSubWindow(m_sActionName, mat));
			}				
			Released();
			return TRUE;
		}
		else if (m_functionTask == FunctionTask::PTRONESTR)
		{
			ptrOneStr pFunc = CALLREGISTER_FUNCTION(m_sActionName, m_funcOneStr);
			QString msg = pFunc(m_pFirstWindow->GetLoadLabel()->GetMat());
			QMessageBox::information(NULL, tr("Info"), msg);
			Released();
			return TRUE;
		}
		else if (m_functionTask == FunctionTask::PTRTWOMAT)
		{
			if (m_pFirstWindow == ActiveSubWindow())
			{
				QMessageBox::information(Q_NULLPTR, tr("Choose"), tr("please choose another image."));
				return FALSE;
			}
			QMultiMdiSub* m_pSecondWindow = ActiveSubWindow();
			ptrTwoMat pFunc = CALLREGISTER_FUNCTION(m_sActionName, m_funcTwoMat);
			cv::Mat mat = pFunc(m_pFirstWindow->GetLoadLabel()->GetMat(), m_pSecondWindow->GetLoadLabel()->GetMat());
			Q_ASSERT(CreateSubWindow(m_sActionName, mat));
			Released();
			return TRUE;
		}
		else if (m_functionTask == FunctionTask::PTRTWOSTR)
		{
			if (m_pFirstWindow == ActiveSubWindow())
			{
				QMessageBox::information(Q_NULLPTR, tr("Choose"), tr("please choose another image."));
				return FALSE;
			}
			QMultiMdiSub* m_pSecondWindow = ActiveSubWindow();
			ptrTwoStr pFunc = CALLREGISTER_FUNCTION(m_sActionName, m_funcTwoStr);
			QString msg = pFunc(m_pFirstWindow->GetLoadLabel()->GetMat(), m_pSecondWindow->GetLoadLabel()->GetMat());
			QMessageBox::information(NULL, tr("Info"), msg);
			Released();
			return TRUE;
		}
	}
	return FALSE;
}

void QMultiMdi::Restricted(const QCursor& cursor)
{
	RECT rect;
	QPoint gloPoint = this->mapToGlobal(QPoint(0, 0));
	rect.left = this->geometry().left() + gloPoint.x();// -ui->groupBox_ImageInfo->geometry().width();
	rect.right = this->geometry().right() + gloPoint.x();// -ui->groupBox_ImageInfo->geometry().width();
	rect.top = this->geometry().top() + gloPoint.y();
	rect.bottom = this->geometry().bottom() + gloPoint.y();
	ClipCursor(&rect);
	SetCapture(GetCapture());
	setCursor(cursor);
}

void QMultiMdi::Released()
{
	ClipCursor(NULL);
	ReleaseCapture();
	m_functionTask = FunctionTask::NONE;
	setCursor(Qt::CursorShape::ArrowCursor);
}

void QMultiMdi::SetFunctionTask(const QString& actionname, FunctionTask functionTask)
{
	m_sActionName = actionname;
	m_functionTask = functionTask;
	Restricted(GetMyCursorA());
}

bool QMultiMdi::CreateSubWindow(const QString& path)
{
	// find already exist window
	foreach(QMdiSubWindow * windOW, this->subWindowList())
	{
		if (qobject_cast<QMultiMdiSub*>(windOW)->GetAbsFilePath() == path)
		{
			this->setActiveSubWindow(windOW);
			return TRUE;
		}
	}
	QMultiMdiSub* subWindow = new QMultiMdiSub(path, this);
	this->addSubWindow(subWindow);
	subWindow->setWindowTitle(QFileInfo(subWindow->GetAbsFilePath()).fileName());
	subWindow->show();
	return TRUE;
}

bool QMultiMdi::CreateSubWindow(const QString& windowname, const cv::Mat& mat)
{
	QMultiMdiSub* subWindow = new QMultiMdiSub(mat, this);
	this->addSubWindow(subWindow);
	subWindow->setWindowTitle(windowname);
	subWindow->show();
	return TRUE;
}

inline QMultiMdiSub* QMultiMdi::ActiveSubWindow() Q_DECL_NOEXCEPT
{
	if (auto activeSub = this->activeSubWindow())
	{
		return static_cast<QMultiMdiSub*>(activeSub);
	}
	return Q_NULLPTR;
}

void QMultiMdi::SaveWindowClosing()
{
	if (g_mdiParam.bSaveByClosing)
	{
		foreach(auto subwindow, subWindowList())
		{
			QMultiMdiSub* child = qobject_cast<QMultiMdiSub*>(subwindow->widget());
			Q_ASSERT(child);
			if (!child->GetLoadLabel()->Empty() && QMessageBox::Ok == QMessageBox::information(NULL, tr("Save Image"), tr("would you save %1£¿").arg(child->windowTitle()), QMessageBox::Ok | QMessageBox::Cancel))
			{
				SaveWindow();
			}
		}
	}
	else
	{
		closeAllSubWindows();
	}	
}

void QMultiMdi::OpenWindow()
{
	// support multi-files
	QStringList filePathList = QFileDialog::getOpenFileNames(this, tr("Open Files"), RecentlyOpenDir, OpenImgFilter);
	foreach(QString filepath, filePathList)
	{
		Q_ASSERT(CreateSubWindow(filepath));
		RecentlyOpenDir = QFileInfo(filepath).dir().path();
	}
}

void QMultiMdi::SaveWindow()
{
	auto actWindow = ActiveSubWindow();
	if (actWindow != nullptr)
	{
		QString savepath = QFileDialog::getSaveFileName(this, tr("Save Image"), RecentlySaveDir, SaveImgFilter);
		if (savepath.isEmpty() || savepath.isNull()) return;
		RecentlySaveDir = QFileInfo(savepath).dir().path();
		Q_ASSERT(actWindow->GetLoadLabel()->SaveMat(savepath));
	}
}

void QMultiMdi::ReadSettings()
{
	QSettings setting(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	const QString recentPath = setting.value("openpath", QString()).toString();
	if (!recentPath.isEmpty())
		RecentlyOpenDir = recentPath;
	const QString savePath = setting.value("savepath", QString()).toString();
	if (!savePath.isEmpty())
		RecentlySaveDir = savePath;
}

void QMultiMdi::WriteSettings()
{
	QSettings setting(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	setting.setValue("openpath", RecentlyOpenDir);
	setting.setValue("savepath", RecentlySaveDir);
}

