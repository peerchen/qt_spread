#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include "CreateVerificationCode.h"

class ClickLabel : public QLabel
{
	Q_OBJECT

public:

	ClickLabel( QWidget * parent );
	~ClickLabel();

signals:

	void clicked();
public slots:
	void slotClicked();

public:
	
	void mousePressEvent(QMouseEvent * event);


	bool mLastPriceMode;//trueΪ�����¼ۡ���falseΪ��ָ���ۡ�
};

#endif // MYLABEL_H
