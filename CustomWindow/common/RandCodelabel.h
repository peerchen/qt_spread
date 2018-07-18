#ifndef RANDCODELABEL_H
#define RANDCODELABEL_H

#include <QLabel>
#include "CreateVerificationCode.h"

class RandCodeLabel : public QLabel
{
	Q_OBJECT

public:

	RandCodeLabel( QWidget * parent );
	~RandCodeLabel();
	
	qint16  generateRandom(qint16 paramLow, qint16 paramHigh);
	void    sleepNow(quint32 paramMilsecond);
	QColor  generateRandomBgColor();
signals:

	void clicked();

public slots:
	void ShowCode();

public:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent * event);


	CCreateVerificationCode * m_pVerificationCode;    // ����������֤��Ķ���ָ��

	QString m_FontArray[23];                          // ��������
	uint  *m_backPixel;                              // ���һ����Ӧ��С�ı���,��������ɫ���и���
	int   m_width, m_height;                            // ��֤�뱳����С

	QString  m_strCode;
};

#endif 
