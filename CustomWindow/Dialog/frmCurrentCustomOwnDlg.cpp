#include "frmCurrentCustomOwnDlg.h"
#include "mainWindow.h"
frmCurrentCustomOwnDlg::frmCurrentCustomOwnDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);

	ui.tabWidget->addTab(((mainWindow *)parent)->capitalWidget, QStringLiteral("�ʽ�"));
	ui.tabWidget->addTab(((mainWindow *)parent)->storeWidget, QStringLiteral("���"));
	ui.tabWidget->addTab(((mainWindow *)parent)->posiWidget, QStringLiteral("�ֲ�"));
}

frmCurrentCustomOwnDlg::~frmCurrentCustomOwnDlg()
{
}
