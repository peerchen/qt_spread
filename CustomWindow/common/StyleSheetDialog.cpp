#include "StyleSheetDialog.h"
#include <QPainter>
#include <QStyleOption>
#include "macrodefs.h"
StyleSheetDialog::StyleSheetDialog(QWidget *parent)
	: QDialog(parent)
{

	//���ô������������
	setWindowFlags(Qt::FramelessWindowHint);// | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
	setAttribute(Qt::WA_TranslucentBackground);
	//this->setWindowFlags( Qt::WindowCloseButtonHint);
	
	//this->setProperty("Form", true);
	//this->setProperty("CanMove", true);

	//setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\dialog.css"));


	m_layout = new QVBoxLayout();
	m_layout->setMargin(0);
	m_layout->setSpacing(0);
	m_layout->setContentsMargins(0, 0, 0, 0);

}

StyleSheetDialog::~StyleSheetDialog()
{
	delete m_layout;
}

void StyleSheetDialog::setCustomLayout()
{
	//�������
	dialogTitle = new DialogTitle(this);
	connect(dialogTitle, SIGNAL(buttonClick(DialogTitle::ButtonStatus)), this, SLOT(titleButtonClick(DialogTitle::ButtonStatus)));
	m_layout->addWidget(dialogTitle);


}


//ϵͳ��ť��Ӧ
void StyleSheetDialog::titleButtonClick(DialogTitle::ButtonStatus status)
{
	switch (status) {
	//case WindowTitle::ButtonMin:
	//	this->showMinimized();
	//	break;

	//case WindowTitle::ButtonMax:
	//	this->showMaximized();
	//	break;

	//case WindowTitle::ButtonRestore:
	//	this->showNormal();
	//	break;

	case DialogTitle::ButtonClose:
		this->close();
		break;

	default:
		//assert(false);
		break;
	}
}


void StyleSheetDialog::setCustomTitle(QString & title)
{
	dialogTitle->setCustomTitle(title);
}


//Ϊ���ܹ�ʹ����ʽ������ҪΪ�Զ���Widget�ṩpaintEvent�¼�
void StyleSheetDialog::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QStyleOption opt;
	opt.init(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
