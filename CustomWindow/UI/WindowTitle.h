
#ifndef _WINDOW_TITLE_H_
#define _WINDOW_TITLE_H_

#include <QWidget>
#include <QMouseEvent>
#include <QAction>
#include "StyleSheetWidget.h"
#include <QMenuBar>

class QHBoxLayout;
class QPushButton;
//class QToolButton;


class WindowTitle : public StyleSheetWidget 
{
	Q_OBJECT
public:
	enum ButtonStatus {
		ButtonMin = 0,
		ButtonMax,
		ButtonRestore,
		ButtonClose
	};

	WindowTitle(QWidget *window);

	bool isCaption(int x, int y) const;

protected:
	virtual bool eventFilter(QObject* o, QEvent* e) override;

        void mouseDoubleClickEvent(QMouseEvent *e) override;
	void initButton();
	void initMenuButton();
	void initMenu();
signals:
	void buttonClick(WindowTitle::ButtonStatus status);

protected slots:
	void actionOneSlot();
	void actionTwoSlot();
	void actionThreeSlot();
	void actionFourSlot();

	void action2OneSlot();
	void action2TwoSlot();
	void action2ThreeSlot();
	void action2FourSlot();
	void action2FiveSlot();

	void action3OneSlot();
	void action3TwoSlot();
	void action3ThreeSlot();
	void action3FourSlot();
	void action3FiveSlot();

	//�����˵���Ӧ
	void action3Sixsub1Slot();
	void action3Sixsub2Slot();
	void action3Sixsub3Slot();
	void action3Sixsub4Slot();

	void action3Sevensub1Slot();
	void action3Sevensub2Slot();
	void action3Sevensub3Slot();
	void action3Sevensub4Slot();
	void action3Sevensub5Slot();
	void action3Sevensub6Slot();
	void action3Sevensub7Slot();


	void action4OneSlot();
	void action4TwoSlot();
	void action4ThreeSlot();
	void action4FourSlot();
	void action5OneSlot();


	void checkedAction();
private:
	QWidget* m_window;

	QHBoxLayout* m_layout;
	QPushButton* m_buttonMin;
	QPushButton* m_buttonMax;
	QPushButton* m_buttonRestore;
	QPushButton* m_buttonClose;

	//���ܰ�ť�˵�
	QPushButton* m_buttonSys;
	QPushButton* m_buttonOption;
	QPushButton* m_buttonQuery;
	QPushButton* m_buttonSet;
	QPushButton* m_buttonHelp;

	/////////////////////////////////�˵�///////////////////////////////////
	//ϵͳ
	QAction *m_actionOne;
	QAction *m_actionTwo;
	QAction *m_actionThree;
	QAction *m_actionFour;

	//����
	QAction *m_action2One;
	QAction *m_action2Two;
	QAction *m_action2Three;
	QAction *m_action2Four;
	QAction *m_action2Five;

	//���ݲ�ѯ
	QAction *m_action3One;
	QAction *m_action3Two;
	QAction *m_action3Three;
	QAction *m_action3Four;
	QAction *m_action3Five;
	//QAction *m_action3Six;
	//QAction *m_action3Seven;


	//
	QAction *m_action3Six_sub1 ;
	QAction *m_action3Six_sub2 ;
	QAction *m_action3Six_sub3 ;
	QAction *m_action3Six_sub4 ;

	QAction *m_action3Seven_sub1 ;
	QAction *m_action3Seven_sub2 ;
	QAction *m_action3Seven_sub3 ;
	QAction *m_action3Seven_sub4 ;
	QAction *m_action3Seven_sub5 ;
	QAction *m_action3Seven_sub6 ;
	QAction *m_action3Seven_sub7 ;

	//����
	QAction *m_action4One;
	QAction *m_action4Two;
	QAction *m_action4Three;
	QAction *m_action4Four;

	//����
	QAction *m_action5One;
	QAction *m_action5Two;


	QMenuBar* menuBar;
};


#endif