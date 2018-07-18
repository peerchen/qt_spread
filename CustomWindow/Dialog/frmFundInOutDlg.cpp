#include "frmFundInOutDlg.h"
#include "Macrodefs.h"
#include "Global.h"
#include "TradeHandler.h"
#include "DelayReqHandler.h"
#include "HJGlobalFun.h"
#include "TraderCpMgr.h"
#include "CustomInfoMgrEx.h"
#include <QMessageBox>
#include <QGridLayout>

#include "TradeHandler.h"
#include "app.h"

frmFundInOutDlg::frmFundInOutDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);

	
	tableModel = new QStandardItemModel();

	//setWidgetStyleFromQssFile(ui.tableView, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\ordertable.css"));

	////������
	tableModel->setColumnCount(7);
	int columnIndex = 0;
	tableModel->setHeaderData(columnIndex, Qt::Horizontal, QStringLiteral("������ˮ��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�����˺�"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��ȡ����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("����״̬"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��ע"));


	ui.tableView->horizontalHeader()->setFixedHeight(32);
	ui.tableView->verticalHeader()->hide();
	ui.tableView->verticalHeader()->setDefaultSectionSize(30);
	ui.tableView->setShowGrid(false);
	ui.tableView->setSortingEnabled(false);
	ui.tableView->setAlternatingRowColors(true);//���л�ɫ
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableModel->setSortRole(1);
	ui.tableView->setModel(tableModel);
	ui.tableView->setColumnWidth(0, 150);
	ui.tableView->setColumnWidth(1, 150);



//	//IniAccessButton();
//
//	//if (m_bPopup)
//	//{
//	//	SetWindowText("�����");
//	//}
//
//#if (defined _VERSION_JSZX) || (defined _VERSION_ZHLHY)
//	// ������Զ����������������Ƿ��Ƿ���Ҫ���Ϳ�����
//	if (g_Global.m_bAutoTransfer)
//	{
//		GetCheckCardPwdPara();
//	}
//#endif


	QString csResPath = g_Global.GetSystemPath() + "Trade\\res\\";
	
	//ˢ����ˮ
	connect(ui.pushButton_5, &QPushButton::clicked, this, &frmFundInOutDlg::slotCal);

	connect(ui.pushButton, &QPushButton::clicked, this, &frmFundInOutDlg::slotIn);//���
	connect(ui.pushButton_2, &QPushButton::clicked, this, &frmFundInOutDlg::slotOut);//����
	connect(ui.pushButton_3, &QPushButton::clicked, this, &frmFundInOutDlg::slotCapital);//�ʽ�
	connect(ui.pushButton_4, &QPushButton::clicked, this, &frmFundInOutDlg::slotCustomInfo);//�ͻ���Ϣ

    ui.lineEdit_pswd->setEchoMode(QLineEdit::Password);
	ui.label_3->setVisible(false);

	setFixedSize(800, 601);
	ui.widget->setGeometry(0, 0, 800, 501);
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("�����"));

}

frmFundInOutDlg::~frmFundInOutDlg()
{
}


//ˢ����ˮ
void frmFundInOutDlg::slotCal()
{
	//
	g_DelayReqHandler.RequestFundInfo();
	//m_list1.DeleteAllItems();
	tableModel->clear();

	Rsp3010 rsp3010;
	Req3010 req3010;
	if (g_TradeHandler.GetCushAccessFlow(rsp3010, req3010, e_TipsShowType_Fail, false) == 0)
	{
		const ArrayListMsg &alm = rsp3010.alm_custtype_list;
		for (int i = 0; i < alm.size(); i++)
		{
			tableModel->insertRow(i);
			tableModel->setItem(i, 0, new QStandardItem(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 0))));// ������ˮ�� 
			//m_list1.SetItemText(i, 1, alm.GetStringEx(i, 6).c_str());   
			tableModel->setItem(i, 1, new QStandardItem(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 6)))); // �����˺�
			
			//m_list1.SetItemText(i, 2, alm.GetStringEx(i, 7).c_str());    
			tableModel->setItem(i, 2, new QStandardItem(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 7))));// ��������
			
			//m_list1.SetItemText(i, 3, alm.GetStringEx(i, 4).c_str());    // ��ȡ����
			tableModel->setItem(i, 3, new QStandardItem(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 4))));

			//m_list1.SetItemText(i, 4, CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 5)))); // �������
			tableModel->setItem(i, 4, new QStandardItem(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 5)))));

			//m_list1.SetItemText(i, 5, g_TraderCpMgr.GetCheck_staName(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 8)))); // ����״̬ 
			tableModel->setItem(i, 5, new QStandardItem(g_TraderCpMgr.GetCheck_staName(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 8)))));

			//m_list1.SetItemText(i, 6, alm.GetStringEx(i, 13).c_str()); 	 
			tableModel->setItem(i, 6, new QStandardItem(CHJGlobalFun::str2qstr(alm.GetStringEx(i, 13))));// ��ע

		}
	}

}

bool frmFundInOutDlg::HandleTransferByHand(const QString &accessWay)
{
	Req3010 req3010;
	//������ʶ
	req3010.oper_flag = 1;
	//��ȡ��ʽ
	req3010.access_way = CHJGlobalFun::qstr2str(accessWay);
	//�������
	req3010.exch_bal = ui.lineEdit->text().toFloat();
	//�ʽ�����
	QByteArray ba = ui.lineEdit_pswd->text().toLatin1();
	req3010.fund_pwd = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetEncryptPSW(ba.data(), false));//true
	Rsp1020 rsp1020 = g_CusInfo.Get1020();
	req3010.account_no = rsp1020.c_account_no;
	req3010.open_bank_name = rsp1020.c_open_bank_name;
	req3010.remark = "";
	//��Ա���
	req3010.o_teller_id = CHJGlobalFun::qstr2str(g_Global.m_strUserID);
	//����������
	req3010.branch_id = g_HeaderReq.branch_id;
	//����ͻ�
	req3010.acct_no = CHJGlobalFun::qstr2str(g_Global.m_strUserID);

	Rsp3010 rsp3010;
	if (0 == g_TraderCpMgr.HandlePacket(rsp3010, req3010, "3010"))
	{
		if (strcmp(rsp3010.rsp_code.c_str(), RSP_SUCCESS_CODE) == 0)
		{
			return true;
		}
		else
		{
			//AfxMessageBox(rsp3010.rsp_msg.c_str());
			//QMessageBox::Information(CHJGlobalFun::str2qstr(rsp3010.rsp_msg));
			if (strcmp(rsp3010.rsp_code.c_str(), "HJ2002  ") == 0)
				rsp3010.rsp_msg = "�ʽ����벻��ȷ��";

			QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), CHJGlobalFun::str2qstr(rsp3010.rsp_msg));
		}
	}
	else
	{
		//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS, MB_TOPMOST);
		QMessageBox::information(nullptr, QStringLiteral("ϵͳ��ʾ"), QStringLiteral(CONSTANT_CONNECT_SERVER_FAIL_TIPS));
	}

	return false;
}


//�����������Ƿ���ȷ�������Ŀؼ����ý���
bool frmFundInOutDlg::CheckInput()
{
	//�������
	if ( ui.lineEdit->text() == QStringLiteral(""))
	{

		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��������Ϊ��"), QMessageBox::Ok);

		ui.lineEdit->setFocus();
		return false;
	}
	//if (0)
	//	//if(!IsNumber(m_editbal))
	//{

	//	QMessageBox::information(nullptr, "��ʾ", QStringLiteral("���������������"), QMessageBox::Ok);
	//	GetDlgItem(IDC_EDIT_BALANCE)->SetFocus();
	//	return false;
	//}

	//�ʽ�����
	if (ui.lineEdit_pswd->text() == QStringLiteral(""))
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�ʽ����벻��Ϊ��"), QMessageBox::Ok);
		ui.lineEdit_pswd->setFocus();
		return false;
	}

	return true;
}

//ȷ����ת�ˣ���ť�Ĵ�������
void frmFundInOutDlg::OnBnClickedButtonTransfer(QString accessWay)
{
	
	//g_SysParaMgr.HideKeyBoard();
	if (CheckInput())
	{
		// ��ȡ��������
		QString notifyMsg;
		notifyMsg = QStringLiteral("    ת�˽��Ϊ��");
		notifyMsg += ui.lineEdit->text();//.GetBuffer();
		//ToDaXie();
		notifyMsg += QStringLiteral(", �� ");
		notifyMsg += ui.label_daxie->text();
		notifyMsg += QStringLiteral(", ȷʵҪת����?");

		if(QMessageBox::information(nullptr, QStringLiteral("��ʾ"), notifyMsg, QMessageBox::Yes | QMessageBox::No)  == QMessageBox::Yes)
		//if (MessageBox(notifyMsg.GetBuffer(), "��ʾ", MB_YESNO | MB_ICONINFORMATION) == IDYES) //����ȷ�ϴ��� 
		{
			bool bSus = false; // �Ƿ��������ݳɹ�
			bool bTips = true; // �Ƿ���Ҫ��ʾ
			//char *psw;
			//psw = m_editpsw.GetBuffer(m_editpsw.GetLength());


			bSus = HandleTransferByHand(accessWay);

			//m_editpsw.ReleaseBuffer();
			if (bSus)
			{
				if (bTips)
				{
					//AfxMessageBox("ת�˳ɹ���");
					QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("ת�˳ɹ���"), QMessageBox::Ok);
				}

				// �����ɹ��󴥷�ˢ�°�ť��[ˢ���ʽ���Ϣ]
				slotCal();

				ui.lineEdit->setText(QStringLiteral(""));
				ui.label_daxie->setText(QStringLiteral(""));
				ui.lineEdit_pswd->setText(QStringLiteral(""));
			
			
			}
		}

	}
}


void frmFundInOutDlg::slotIn()
{
	if (2 != g_TraderCpMgr.m_vAccessWay.size())
	{
		return;
	}
	else
	{
		OnBnClickedButtonTransfer(g_TraderCpMgr.m_vAccessWay.at(0).code_id);
	}
}
void frmFundInOutDlg::slotOut()
{
	if (2 != g_TraderCpMgr.m_vAccessWay.size())
	{
		return;
	}
	else
	{
		OnBnClickedButtonTransfer(g_TraderCpMgr.m_vAccessWay.at(1).code_id);
	}

}

//�ʽ���Ϣ
void frmFundInOutDlg::slotCapital()
{
	QDialog* win          = new QDialog(this);//�ʽ���Ϣ
	QLabel* label_cur     = new QLabel(this);//��ǰ���
	QLabel* label_can_get = new QLabel(this);//�����ֽ�
	QLabel* label_can_use = new QLabel(this);//���ý��

	QLabel* label_cur_val = new QLabel(this);//��ǰ���
	QLabel* label_can_get_val = new QLabel(this);//�����ֽ�
	QLabel* label_can_use_val = new QLabel(this);//���ý��

	//
	QGridLayout *pLayout = new QGridLayout;
	pLayout->addWidget(label_cur, 0, 0, 1, 1);
	pLayout->addWidget(label_cur_val, 0, 1, 1, 2);
	pLayout->addWidget(label_can_get, 1, 0, 1, 1);
	pLayout->addWidget(label_can_get_val, 1, 1, 1, 2);
	pLayout->addWidget(label_can_use, 2, 0, 1, 1);
	pLayout->addWidget(label_can_use_val, 2, 1, 1, 2);

	pLayout->setMargin(0);
	pLayout->setHorizontalSpacing(10);//����ˮƽ���
	pLayout->setVerticalSpacing(10);
	pLayout->setContentsMargins(10, 10, 10, 10);//���ô�ֱ���
	// ��ʾ�����ʽ���Ϣ
	label_cur->setText(QStringLiteral("��ǰ��"));
	label_can_get->setText(QStringLiteral("������"));
	label_can_use->setText(QStringLiteral("������"));
	label_cur_val->setText(QStringLiteral(" "));
	label_can_get_val->setText(QStringLiteral(" "));
	label_can_use_val->setText(QStringLiteral(" "));
		
	Req1020 req;
	req.qry_fund = CHJGlobalFun::qstr2str(gc_YesNo_Yes);

	Rsp1020 rsp;
	if (g_TradeHandler.GetCustomInfo(rsp, req, e_TipsShowType_Fail) == 0)
	{
		Rsp1020 rsp1020 = g_CusInfo.Get1020();

		label_cur_val->setText(CHJGlobalFun::str2qstr(rsp1020.f_curr_bal));
		label_can_get_val->setText(CHJGlobalFun::str2qstr(rsp1020.f_can_get_bal));
		label_can_use_val->setText(CHJGlobalFun::str2qstr(rsp1020.f_can_use_bal));
	}

	win->setWindowTitle(QStringLiteral("�ʽ���Ϣ"));
	win->setLayout(pLayout);
	win->resize(300, 200);
	win->setModal(true);
	win->show();

}

//�ͻ���Ϣ
void frmFundInOutDlg::slotCustomInfo()
{
	QDialog* win = new QDialog(this);//�ʽ���Ϣ
	QLabel* label_code   = new QLabel(this);//���ױ���
	QLabel* label_acc    = new QLabel(this);//�����˻�
	QLabel* label_name   = new QLabel(this);//�ͻ�����
	QLabel* label_status = new QLabel(this);//�˻�״̬
	QLabel* label_branch = new QLabel(this);//�����������


	QLabel* label_code_val   = new QLabel(this);//���ױ���
	QLabel* label_acc_val    = new QLabel(this);//�����˻�
	QLabel* label_name_val   = new QLabel(this);//�ͻ�����
	QLabel* label_status_val = new QLabel(this);//�˻�״̬
	QLabel* label_branch_val = new QLabel(this);//�����������
												 //
	QGridLayout *pLayout = new QGridLayout;
	pLayout->addWidget(label_code, 0, 0, 1, 1);
	pLayout->addWidget(label_code_val, 0, 1, 1, 2);
	pLayout->addWidget(label_acc, 1, 0, 1, 1);
	pLayout->addWidget(label_acc_val, 1, 1, 1, 2);
	pLayout->addWidget(label_name, 2, 0, 1, 1);
	pLayout->addWidget(label_name_val, 2, 1, 1, 2);
	pLayout->addWidget(label_status, 3, 0, 1, 1);
	pLayout->addWidget(label_status_val, 3, 1, 1, 2);
	pLayout->addWidget(label_branch, 4, 0, 1, 1);
	pLayout->addWidget(label_branch_val, 4, 1, 1, 2);

	// ��ʾ�����ʽ���Ϣ
	label_code->setText(QStringLiteral("���ױ��룺"));
	label_acc->setText(QStringLiteral("�����˻���"));
	label_name->setText(QStringLiteral("�ͻ����ƣ�"));
	label_status->setText(QStringLiteral("�˻�״̬��"));
	label_branch->setText(QStringLiteral("�������������"));
	
	label_code_val->setText(QStringLiteral(""));
	label_acc_val->setText(QStringLiteral(""));
	label_name_val->setText(QStringLiteral(""));
	label_status_val->setText(QStringLiteral(""));
	label_branch_val->setText(QStringLiteral(""));


	Req1020 stReq;
	stReq.qry_cust_info = CHJGlobalFun::qstr2str(gc_YesNo_Yes);;

	Rsp1020 rsp;
	if (g_TradeHandler.GetCustomInfo(rsp, stReq, e_TipsShowType_Fail) == 0)
	{
		Rsp1020 rsp1020 = g_CusInfo.Get1020();
	
		label_code_val->setText(CHJGlobalFun::str2qstr(rsp1020.c_acct_no));
		label_acc_val->setText(CHJGlobalFun::str2qstr(rsp1020.c_account_no));
		label_name_val->setText(CHJGlobalFun::str2qstr(rsp1020.c_cust_abbr));
		label_status_val->setText(g_TraderCpMgr.GetAcct_statName(CHJGlobalFun::str2qstr(rsp1020.c_acct_stat)));
		label_branch_val->setText(CHJGlobalFun::str2qstr(GetBranchName(rsp1020.c_branch_id)));

	}
	

	win->setWindowTitle(QStringLiteral("�ͻ���Ϣ"));
	win->setLayout(pLayout);
	win->resize(300, 200);
	win->setModal(true);
	win->show();

}




// ��������ID��sBranchID����HashtableMsg�����ȡ�������ƣ�sBranchName��
bool frmFundInOutDlg::GetBranchNameFromID(HashtableMsg &htmBranch, const string &sBranchID, string &sBranchName)
{
	// �ҵ�����ID��Ӧ�Ļ�������
	for (int i = 0; i < htmBranch.size(); i++)
	{
		if (htmBranch.GetString(i, "branch_id") == sBranchID)
		{
			sBranchName = htmBranch.GetString(i, "branch_name");
			return true;
		}
	}

	return false;
}

/*
ˢ����Ϣʱ���ݴ������id��ȡ�����������
input��sBranchID�������id
*/
string frmFundInOutDlg::GetBranchName(const std::string &sBranchID)
{
	HashtableMsg htmBranch;
	string sBranchName;
	bool bReload = true;

	//���������ļ�·��
	QString strIniPath = g_Global.GetSystemPath() + CONSTANT_DATA_INI_NAME;

	// ��������ļ��еô��������Ϣ��Ϊ�գ����ȡ�����ļ��еĴ��������Ϣ
	//char buf[10000] = { 0 };
	//::GetPrivateProfileString("Info", "Branch", "", buf, sizeof(buf), strIniPath);

	QString buf;
	App::GetPriProfileString(strIniPath, QStringLiteral("Info"), QStringLiteral(""), buf);

	if (buf.size() != 0)
	{

		// ��������ɹ��������ҵ���Ӧ�����ƣ�������
		if (htmBranch.Parse(CHJGlobalFun::qstr2str(buf)) != -1)
		{
			if (GetBranchNameFromID(htmBranch, sBranchID, sBranchName))
			{
				bReload = false;
			}
		}
	}

	if (bReload)
	{
		Req9010 req;
		req.oper_flag = 1;

		Rsp9010 rsp;
		if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "9010"))
		{
			
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral(CONSTANT_CONNECT_SERVER_FAIL_TIPS), QMessageBox::Ok);
			sBranchName = sBranchID;
		}

		if (!g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
		{
			sBranchName = sBranchID;
		}
		else
		{
			htmBranch = rsp.htm_branch_info;
			//д��ṹ��Ϣ���ļ�
			//::WritePrivateProfileString("Info", "Branch", htmBranch.ToString().c_str(), strIniPath);

			App::GetPriProfileString(strIniPath, QStringLiteral("Info"), QStringLiteral("Branch"), CHJGlobalFun::str2qstr(htmBranch.ToString()));

			if (!GetBranchNameFromID(htmBranch, sBranchID, sBranchName))
			{
				sBranchName = sBranchID;
			}
		}
	}

	return sBranchName;
}

