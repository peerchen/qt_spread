#pragma once
#include <QObject>
#include <QPoint>
//////////////////////////////////////////////////////////////////
//��Ҫ֧�������Ľ��棬���ԴӴ�������
//
///////////////////////////////////////////////////////////////////



class AppInit : public QObject
{
	Q_OBJECT
public:
	explicit AppInit(QObject *parent = 0);

	void installEventFilter(QObject *parent);

	void Init();
	void Load();
	//int  countFlag(QPoint p, int row);
	//void setCursorType(int flag);
	//int  countRow(QPoint p);

	////֧�ֽ��������
private:
	QPoint mousePoint;    //����϶�ʱ������
	bool   mousePressed;  //����Ƿ���

protected:
	bool eventFilter(QObject *obj, QEvent *evt);

	QObject* m_widget;
};

