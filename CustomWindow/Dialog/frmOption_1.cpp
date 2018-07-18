#include "frmOption_1.h"
#include "Global.h"
#include "app.h"
#include  "mainWindow.h"


#pragma execution_character_set("utf-8")

frmOption_1::frmOption_1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	LoadFromIni();

	//connect(this, SIGNAL(triggered()), m_mainwindow, SLOT(ResetLayoutSlot()));
}

frmOption_1::~frmOption_1()
{
}
void frmOption_1::saveIni()
{
	if (!CheckInput())
		return;

	QString sfile = g_Global.GetUserIniPath();
	QString str;

	QString buf;
	App::WritePriProfileString(sfile, ("Display"), ("ScreenTimeout"), ui.lineEdit->text());
	g_Global.m_TimeOutScreen = ui.lineEdit->text().toInt();

	//WritePrivateProfileString("Display", "ScreenTimeout", m_strScreenTimeout, sfile);
	//g_Global.m_TimeOutScreen = atoi(m_strScreenTimeout);

	m_bCommitLeftOld = g_Global.m_bCommitLeft; // ���¾ɵ��Ա�Ƚ�
	bool test = ui.radioButton->isChecked();
	g_Global.m_bCommitLeft = (ui.radioButton->isChecked()) ? true : false;
	str.sprintf("%d", g_Global.m_bCommitLeft ? 1 : 0);//g_Global.m_bCommitLeft  ѡ�е�һ��radio�� true�� ������INI��1

	//WritePrivateProfileString("Display", "OrderPosition", str, sfile);
	App::WritePriProfileString(sfile, ("Display"), ("OrderPosition"), str);


	m_iInterfaceStyleOld = g_Global.m_iInterfaceStyle;
	g_Global.m_iInterfaceStyle = ui.comboBox->currentIndex();//.GetCurSel();
	str.sprintf("%d", g_Global.m_iInterfaceStyle);
	//WritePrivateProfileString("Display", "UIStyle", str, sfile);
	App::WritePriProfileString(sfile, ("Display"), ("UIStyle"), str);


	if (g_Global.m_bCommitLeft != m_bCommitLeftOld)
	{
		//CGDTradeForm2Dlg *pWnd = ((CGDTradeForm2Dlg*)AfxGetMainWndEx());
		//pWnd->m_MainPanel.m_dlgUpPanel.m_Splitter.InvertSplitter();
		//��������λ��
	}
	if (g_Global.m_iInterfaceStyle != m_iInterfaceStyleOld)
	{
		//CGDTradeForm2Dlg *pWnd = ((CGDTradeForm2Dlg*)AfxGetMainWndEx());
		//pWnd->m_MainPanel.ResetStyle();

		//�л�����   ��������ջ���	
		((mainWindow *)m_mainwindow)->classiclayout = m_iInterfaceStyleOld;
		((mainWindow *)m_mainwindow)->ResetLayoutSlot();

	}


}


void frmOption_1::LoadFromIni()
{
	m_strScreenTimeout = QString::number(g_Global.m_TimeOutScreen);
	ui.lineEdit->setText(m_strScreenTimeout);
	m_radioOrderPosition = g_Global.m_bCommitLeft ? 0 : 1;
	if (m_radioOrderPosition == 0)
		ui.radioButton->setChecked(true);
	else
		ui.radioButton_2->setChecked(true);

	ui.comboBox->clear();
	ui.comboBox->addItem("����");
	ui.comboBox->addItem("��ͳ");
	ui.comboBox->setCurrentIndex(g_Global.m_iInterfaceStyle);

}

void frmOption_1::setMainWin(QWidget *win)
{
	m_mainwindow = win;
}



bool frmOption_1::CheckInput()
{

	if (m_strScreenTimeout.isEmpty())
	{

		QMessageBox::information(nullptr, "ϵͳ��ʾ", "�Զ�����ʱ�䲻��Ϊ�գ�");


		return false;
	}

	if (m_strScreenTimeout.toInt() > 9999)
	{
		QMessageBox::information(nullptr, ("ϵͳ��ʾ"), "�Զ�����ʱ�䲻��Ϊ�գ�");
		return false;
	}

	return  true;

}