#include "StyleSheetWidget.h"
#include <QPainter>
#include <QStyleOption>
//#include "macrodefs.h"




//Ϊ���ܹ�ʹ����ʽ������ҪΪ�Զ���Widget�ṩpaintEvent�¼�
void StyleSheetWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QStyleOption opt;
	opt.init(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

