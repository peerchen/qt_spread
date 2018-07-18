#include "frmChangePswdDlg.h"
#include "HJGlobalFun.h"
#include "tradepacketandstruct.h"
#include "Global.h"
#include "TraderCpMgr.h"
#include <QMessageBox>

frmChangePswdDlg::frmChangePswdDlg(QWidget *parent)
	//: StyleSheetDialog(parent)
	:frmFramelessDialogBase(parent)
{
	ui.setupUi(this);

	m_bLogin = true;
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonCommit()));
	ui.lineEdit_new->setEchoMode(QLineEdit::Password);
	ui.lineEdit_old->setEchoMode(QLineEdit::Password);
	ui.lineEdit_confirm->setEchoMode(QLineEdit::Password);

	//this->setWindowTitle(QStringLiteral("��¼�����޸�"));
	
	//setCustomLayout();
	//QVBoxLayout* m_layout = new QVBoxLayout();//;
	//m_layout->setMargin(0);
	//m_layout->addLayout(ui.horizontalLayout);
	//m_layout->addLayout(ui.horizontalLayout_2);
	//m_layout->addLayout(ui.horizontalLayout_3);
	//m_layout->addLayout(ui.horizontalLayout_7);
	//����رհ�ť
	//setLayout(m_layout);
	//setDialogSize(325,312);

	//ui.widget->setFixedSize(220,220);//200,200
	setFixedSize(250, 220);
	ui.widget->setGeometry(0, 0, 250, 180);//170С������dialog�Ĵ�С200

	setContent(ui.widget);


	setMode(m_bLogin);

}

frmChangePswdDlg::~frmChangePswdDlg()
{
}


bool frmChangePswdDlg::CheckInput()
{
	//UpdateData(true);

	//#ifdef _VERSION_GF
	//	// ����ͨ�汾���루��¼���ʽ����룩ֻ��Ϊ6λ����
	//	if (m_strOld.GetLength() != 6 || m_strNew.GetLength() != 6 || m_strConfirm.GetLength() != 6)
	//	{
	//		AfxMessageBox("����ֻ��Ϊ6λ������");
	//		return false;
	//	}
	//#else
	if (ui.lineEdit_old->text().length() < 6 || ui.lineEdit_new->text().length() < 6 || ui.lineEdit_confirm->text().length() < 6)
	{
		//AfxMessageBox("���벻��С��6λ");
		QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("���벻��С�ڣ�"));
		return false;
	}
	//#endif

	if (ui.lineEdit_new->text() != ui.lineEdit_confirm->text())
	{
		//AfxMessageBox("������������벻һ�£�");
		QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("������������벻һ�£�"));
		return false;
	}

	// �������������벻����ͬ
	if (ui.lineEdit_old->text() == ui.lineEdit_new->text())
	{
		//AfxMessageBox("�����벻�ܺ;ɵ�������ͬ��");
		QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("�����벻�ܺ;ɵ�������ͬ��"));
		return false;
	}

	// ��������ֵĻ�������Ϊ����������
	if (CHJGlobalFun::IsNumber(ui.lineEdit_new->text()))
	{
		if (CHJGlobalFun::IsContinuousNumber(ui.lineEdit_new->text()))
		{
			//AfxMessageBox("���벻��Ϊ���������֣�");
				QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("���벻��Ϊ���������֣�"));	
				return false;
		}

		if (CHJGlobalFun::IsHasContinuousSameWord(ui.lineEdit_new->text(), 3))
		{
			//AfxMessageBox("���벻����������λ��ͬ�����֣�");
			QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("���벻����������λ��ͬ�����֣�"));
			return false;
		}
	}

	return true;
}

void frmChangePswdDlg::setMode(bool lgmode)
{
	m_bLogin = lgmode;

	if (!m_bLogin)
	{
		setWindowTitle(QStringLiteral("�ʽ������޸�"));
		//setCustomTitle(QStringLiteral("�ʽ������޸�"));
	}
	else
	{
		setWindowTitle(QStringLiteral("��¼�����޸�"));
		//setCustomTitle(QStringLiteral("��¼�����޸�"));
	}
}


void frmChangePswdDlg::OnBnClickedButtonCommit()
{
	//DestroyKeyBoard();

	if (CheckInput())
	{
		Req2022 req;
		req.oper_flag = 1;
		req.acct_no = CHJGlobalFun::qstr2str( g_Global.m_strUserID);

		string strOldPSW, strNewPSW;

		if (m_bLogin)
		{
			QByteArray ba = ui.lineEdit_old->text().toLatin1();
			strOldPSW = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetEncryptPSW(ba.data()));
			ba = ui.lineEdit_new->text().toLatin1();
			strNewPSW = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetEncryptPSW(ba.data())); //MD5::ToMD5(m_strNew, strlen(m_strNew)); // MD5����
		}
		else
		{
			bool bShortPsw = false;//��MD5 true   ,��MD5 FALSE
			QByteArray ba = ui.lineEdit_old->text().toLatin1();
			strOldPSW = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetEncryptPSW(ba.data(), bShortPsw));
			ba = ui.lineEdit_new->text().toLatin1();
			strNewPSW = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetEncryptPSW(ba.data(), bShortPsw)); //MD5::ToMD5(m_strNew, strlen(m_strNew)); // MD5����
		}

		if (m_bLogin) // ������޸ĵ�½����
		{
			req.old_exch_pwd = strOldPSW;
			req.exch_pwd = strNewPSW;
		}
		else // ������޸��ʽ�����
		{
			req.old_fund_pwd = strOldPSW;
			req.fund_pwd = strNewPSW;
		}

		Rsp2022 rsp;
		if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "2022"))
		{
			//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
			QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("CONSTANT_CONNECT_SERVER_FAIL_TIPS"));
			return;
		}

		//���ļ��
		if (g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
		{
			//AfxMessageBox("�޸�����ɹ���");
			QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral("�޸�����ɹ���"));

			ui.lineEdit_old->clear();
			ui.lineEdit_new->clear();
			ui.lineEdit_confirm->clear();


			close();
		}
	}
}
