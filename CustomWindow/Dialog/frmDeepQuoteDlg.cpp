#include "frmDeepQuoteDlg.h"

frmDeepQuoteDlg::frmDeepQuoteDlg(QWidget *parent)
	: StyleSheetDialog(parent)
{
	ui.setupUi(this);

	//setAttribute(Qt::WA_DeleteOnClose);

	//ȥ���ʺ�
	this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);//FramelessWindowHint
}

frmDeepQuoteDlg::~frmDeepQuoteDlg()
{
}



void  frmDeepQuoteDlg::closeEvent(QCloseEvent *event)
{
	emit  setHide();
}