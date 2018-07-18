#include "AppInt.h"
#include "myHelper.h"
#include "mainWindow.h"


#define MARGIN 20   //�ĸ��ǵĳ���


AppInit::AppInit(QObject *parent) : QObject(parent)
{
	mousePressed = false;
	qApp->installEventFilter(this);
}

void AppInit::installEventFilter(QObject *parent)
{
	parent->installEventFilter(this);
	m_widget = parent;
}


bool AppInit::eventFilter(QObject *obj, QEvent *evt)
{
	try
	{

		QWidget *w = (QWidget *)obj;
		if (w->property("CanMove").toBool())
		{
			QMouseEvent *event = static_cast<QMouseEvent *>(evt);
			if (event->type() == QEvent::MouseButtonPress) {
				if (event->button() == Qt::LeftButton) {
					mousePressed = true;
					mousePoint = event->globalPos() - w->pos();
					return true;
				}
			}
			else if (event->type() == QEvent::MouseButtonRelease) {
				mousePressed = false;
				return true;
			}

			else if (event->type() == QEvent::MouseMove) {
				if (mousePressed && (event->buttons() && Qt::LeftButton)) {
					w->move(event->globalPos() - mousePoint);
					return true;
				}
			}
		}

	

	}
	catch (...)
	{

	}

	return QObject::eventFilter(obj, evt);
}



////�����������һ����һ��
//int AppInit::countFlag(QPoint p, int row)
//{
//	//auto p = (mainWindow *)m_widget;
//	if (p.y() < MARGIN)
//		return 10 + row;
//	else if (p.y() >  ((QWidget *)m_widget)->height() - MARGIN)
//		return 30 + row;
//	else
//		return 20 + row;
//}
//
//
////�����������λ�øı����ָ����״
//void AppInit::setCursorType(int flag)
//{
//	Qt::CursorShape cursor;
//	switch (flag)
//	{
//	case 11:
//	case 33:
//		cursor = Qt::SizeFDiagCursor;
//		break;
//	case 13:
//	case 31:
//		cursor = Qt::SizeBDiagCursor;
//		break;
//	case 21:
//	case 23:
//		cursor = Qt::SizeHorCursor;
//		break;
//	case 12:
//	case 32:
//		cursor = Qt::SizeVerCursor;
//		break;
//	default:
//		//�ָ����ָ����״
//		QApplication::restoreOverrideCursor();
//		break;
//	}
//	((QWidget *)m_widget)->setCursor(cursor);
//}
//
////��������һ��
//int AppInit::countRow(QPoint p)
//{
//
//	return (p.x()<MARGIN) ? 1 : ((p.x()>(((mainWindow *)m_widget)->width() - MARGIN) ? 3 : 2));
//}