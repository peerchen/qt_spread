#include "frmUnlockDlg.h"
#include "TraderCpMgr.h"
#include <QEvent>
#include "mainWindow.h"



frmUnlockDlg::frmUnlockDlg(QWidget *parent)
	: StyleSheetDialog(parent)
{
	ui.setupUi(this);

	mListener = nullptr;

	//ֻ����С������
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

	connect(ui.pushButton_ok, SIGNAL(clicked()), this, SLOT(pushButton_ok()));
	connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(pushButton_cancel()));
	ui.lineEdit->setEchoMode(QLineEdit::Password);

	/*int width = QApplication::desktop()->width();
	int height = QApplication::desktop()->height();
	this->move((width - this->width()) / 2, (height - this->height()) / 2);*/
}

frmUnlockDlg::~frmUnlockDlg()
{
}


void frmUnlockDlg::SetListener(CUnlockListener* pListener)
{
	mListener = pListener;
}


void frmUnlockDlg::Unlock()
{
	int ret = g_TraderCpMgr.UnlockScreen(ui.lineEdit->text());

	if (YLINK_ERROR_NETWORK == ret)
	{
		QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("�������ݴ���ʧ�ܣ�������!"));
		return;
	}
	else if (YLINK_ERROR_BASECODE == ret)
	{
		QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("�������!"));
		return;
	}


	if (mListener != NULL)
	{
		mListener->OnSuccess();
	}

	close();

}


void frmUnlockDlg::changeEvent(QEvent *event)
{
	if (event->type() != QEvent::WindowStateChange) return;
	if (this->windowState() == Qt::WindowMaximized)
	{
		//int width  = QApplication::desktop()->width();
		//int height = QApplication::desktop()->height();
		//���
		((mainWindow *)mListener)->hide();
		


		//this->move((width - this->width()) / 2, (height - this->height()) / 2);
		this->showMaximized();
	}
	int width = QApplication::desktop()->availableGeometry().width();
	int height = QApplication::desktop()->availableGeometry().height();
	//�������²���
	this->move((width - this->width()) / 2, (height - this->height()) / 2);

}



void frmUnlockDlg::pushButton_ok()
{
	int ret = g_TraderCpMgr.UnlockScreen(ui.lineEdit->text());

	if (YLINK_ERROR_NETWORK == ret)
	{
		QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("�������ݴ���ʧ�ܣ�������!"));
		return;
	}
	else if (YLINK_ERROR_BASECODE == ret)
	{
		QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("�������!"));

		return;
	}


	if (mListener != NULL)
	{
		mListener->OnSuccess();
	}

	close();
}

void frmUnlockDlg::pushButton_cancel()
{
	//�˳�
	if (mListener != NULL)
	{
		mListener->OnFailure();
	}
	close();
}