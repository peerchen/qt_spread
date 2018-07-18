#pragma once

#include <QTabWidget>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
class QButtonTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	QButtonTabWidget(QWidget *parent);
	~QButtonTabWidget();

	//������QTabWidget��ǩ������Ʋ�����ť
	void paintEvent(QPaintEvent* event);

	
	//����ȷ����������жϵ��ʱ����Ƿ��ڻ��Ƶ�ͼ���ϣ���ͼ�����򷢳�һ���Զ����������ź�
	void mousePressEvent(QMouseEvent * event);

	
	//����ʵ������ƶ���������ť�Ϸ�ʱ��ִ��һЩ��ز������磺toolTip��ʾ�������ͣЧ���л��ȵ�
	void mouseMoveEvent(QMouseEvent * event);

	
	//����ʵ�ֵ���ǩ�����ı�ʱ��������ť��λ�øı�
	void resizeEvent(QResizeEvent * event);


private:
	QPushButton m_tablepic;
};
