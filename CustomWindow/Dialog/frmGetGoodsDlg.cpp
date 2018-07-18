#include "frmGetGoodsDlg.h"
#include "app.h"
#include "Global.h"
#include "TraderCpMgr.h"
#include "HJGlobalFun.h"
#include  <QMessageBox>
#include "Macrodefs.h"
#include "Mgr/TiHuoMgr.h"
#include "HJConstant.h"

frmGetGoodsDlg::frmGetGoodsDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);

	//SetWindowText("���");
	m_vCity.clear();
	m_nTakeDayDis = 5;
	// �Ƿ���ʾ�����
	m_bShowTakeSheetDate = IsShowTakeSheetData();

	// ��ȡ����������
	//char cBuf[3] = { 0 };
	//::GetPrivateProfileString("info", "HJ.TakeDayDis", "5", cBuf, sizeof(cBuf), g_Global.GetSystemIniPath());
	//m_nTakeDayDis = atoi(cBuf);

	QString  buf;
	App::GetPriProfileString(g_Global.GetSystemIniPath(), QStringLiteral("info"), QStringLiteral("HJ.TakeDayDis"), buf);
	m_nTakeDayDis = buf.toInt();

	//CString csValueDis;
	//if( CIniMgr::GetStringValue( csValueDis, "info", "HJ.TakeDayDis", g_Global.GetSystemIniPath(), 3 ) )
	//	m_nTakeDayDis = atoi(csValueDis);

	// ��ʼ�����Ʒ�������˵�
	IniVarietyComboBox();

	// ��ʼ������������˵��������õ�һ����ѡ��
	//m_combperson.ResetContent();
	ui.comboBox_person->clear();
	for (size_t i = 0; i < g_Global.m_almTake_Man_List.size(); i++)
	{
		ArrayListMsg &aMsg = g_Global.m_almTake_Man_List.GetValue(i); // ��ȡ����ĵ�һ��������
		//ui.comboBox_person.InsertString(i, aMsg.GetStringEx(0).c_str());

		ui.comboBox_person->insertItem(i,CHJGlobalFun::str2qstr(aMsg.GetStringEx(0)));
	}
	QComboBox  test;
	test.setCurrentIndex(0);
	test.setEnabled(false);

	ui.comboBox_person->setCurrentIndex(0);

	if (ui.comboBox_person->count() < 2)
	{
		ui.comboBox_person->setEnabled(false);
		//m_combperson.EnableWindow(FALSE);
	}

	OnCbnSelchangeComboPerson();
	ui.lineEdit_pswd->setEchoMode(QLineEdit::Password);
	ui.lineEdit_ensure->setEchoMode(QLineEdit::Password);

	//m_ctlEditWeight.SetInt();
	//m_ctlEditPSW.SetMode(E_NUM);    
	//m_ctlEditCONPWD.SetMode(E_NUM);
	ui.label_info->setText("");
	//GetDlgItem(IDC_STATIC_INFO)->SetWindowText("");

	//GetDlgItem(IDC_STATIC_TAKE_DATE)->ShowWindow(m_bShowTakeSheetDate);
	//GetDlgItem(IDC_COMBO_TAKE_DATE)->ShowWindow(m_bShowTakeSheetDate);

	ui.comboBox_last_getgoods_day->setEnabled(m_bShowTakeSheetDate);
	if (m_bShowTakeSheetDate)
	{
		//m_cmbTakeDate.ResetContent();

		ui.comboBox_last_getgoods_day->clear();
		// �����ǰû�У���ӷ�������ȡ�ջ���
		if (((ArrayListMsg*)GetTakeShhetDate())->SizeEx2() < 1)
		{
			GetTakeSheetDateFromServer();
		}

		// ���˺Ϸ�������ռ��ص������������
		LoadTakeSheetDateToComBox();

		// ��������ںϷ�������գ�����ʾ
		if (ui.comboBox_last_getgoods_day->count() == 0)
		{
			//QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��ǰ��������գ��������"));

			//AfxMessageBox("��ǰ��������գ��������");
			//GetDlgItem(IDC_BUTTON_APPLYGOODS)->EnableWindow(FALSE);
			ui.pushButton_Apply->setEnabled(false);

			//m_cmbTakeDate.EnableWindow(FALSE);
			ui.comboBox_last_getgoods_day->setEnabled(false);
		}
		
	}

	// ��ѯ���----------------------------------------------------------------

	// �����б����
	//CHJGlobalFun::SetListCtrl(m_1list1);

	//���ú����list����
	//const int iCount = 19;
	//CString sTitle[iCount] = { "�����ˮ��","��������","���Ʒ��", "�������(��)","�������", "����ֿ�", 
	//	"���״̬", "�����������","�����������","�����֤��", "��������", "����ʱ��", "�������",
	//	"��������(��)","��������(��)","���������","֤������", "֤������", "������Ϣ" };//2
	//int iAlign[iCount] = { LVCFMT_LEFT,  LVCFMT_LEFT, LVCFMT_LEFT,LVCFMT_RIGHT,  LVCFMT_LEFT,LVCFMT_LEFT,LVCFMT_LEFT,LVCFMT_LEFT,   LVCFMT_LEFT,   LVCFMT_RIGHT, LVCFMT_LEFT,LVCFMT_LEFT,LVCFMT_LEFT,LVCFMT_RIGHT,  LVCFMT_RIGHT,  LVCFMT_LEFT, LVCFMT_LEFT,LVCFMT_LEFT,LVCFMT_LEFT };
	//int iWidth[iCount] = { 80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80 };
	//CHJGlobalFun::AddListColumn(m_1list1, iCount, sTitle, iAlign, iWidth);

	tableModel = new QStandardItemModel();

	//setWidgetStyleFromQssFile(ui.tableView, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\ordertable.css"));

	////������
	tableModel->setColumnCount(19);
	int columnIndex = 0;
	tableModel->setHeaderData(columnIndex, Qt::Horizontal, QStringLiteral("�����ˮ��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("���Ʒ��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�������(��)"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("����ֿ�"));

	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("���״̬"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�����������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�����������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�����֤��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("����ʱ��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��������(��)"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��������(��)"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("���������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("֤������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("֤������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("������Ϣ"));


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

	loadStore();

	// �������ļ���ȡ������Ϣ���ڴ�
	loadCityFromFile();

	// ��ʼ��������������˵�
	IniCityComboBox();

	ui.comboBox_city->setCurrentIndex(0);
	OnChangeCity("");
	OnChangeType("");
	// ���ÿ�ʼ�ͽ���ʱ��Ϊ��һ������
	//CTime ctime = CHJGlobalFun::TranslateDateStrToCTime(g_Global.m_strExchDate);

	QDateTime ctime = QDateTime::fromString(g_Global.m_strExchDate,"yyyyMMdd");
	if (!ctime.isNull())// ctime != NULL)
	{
		ui.dateEdit_st->setDateTime(ctime);
		ui.dateEdit_end->setDateTime(ctime);
		//m_timebegin.SetTime(&ctime);
		//m_timeend.SetTime(&ctime);
	}

	connect(ui.pushButton_Apply, SIGNAL(clicked()), this,SLOT(OnApplyGoods()));
	connect(ui.pushButton_search, SIGNAL(clicked()), this, SLOT(OnSearch()));
	connect(ui.pushButton_print, SIGNAL(clicked()), this, SLOT(OnPrint()));
	connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(OnCancel()));

	connect(ui.comboBox_city, SIGNAL(currentIndexChanged(QString)), this, SLOT(OnChangeCity(QString)));
	connect(ui.comboBox_type, SIGNAL(currentIndexChanged(QString)), this, SLOT(OnChangeType(QString)));


	setFixedSize(1001, 661);
	ui.widget->setGeometry(0, 0, 1001, 561);
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("���"));
}

frmGetGoodsDlg::~frmGetGoodsDlg()
{
}

void frmGetGoodsDlg::OnChangeType(QString city)
{
	//����ѡ��Ʒ�ֻ�ȡ��Ʒ����С��������������
	QString cstr;
	int min_pickup  = 0;
	int pickup_base = 0;

	cstr = ui.comboBox_type->currentText();//.GetLBText(m_combgoodstype.GetCurSel(), cstr);
	/*string str(cstr.GetBuffer());*/
	for (size_t i = 0; i < g_TraderCpMgr.m_vVariety.size(); i++)
	{
		if (cstr == g_TraderCpMgr.m_vVariety.at(i).name)
		{
			min_pickup = (int)g_TraderCpMgr.m_vVariety.at(i).min_pickup;
			pickup_base = (int)g_TraderCpMgr.m_vVariety.at(i).pickup_base;
			break;
		}
	}

	QString cstrTips = QStringLiteral("���������СΪ%1�ˣ���Ϊ%2����������").arg(min_pickup).arg(pickup_base);
	//cstrTips.Format("���������СΪ%d�ˣ���Ϊ%d����������", min_pickup, pickup_base);
	//GetDlgItem(IDC_STATIC_INFO)->SetWindowText(cstrTips);
	ui.label_info->setText(cstrTips);
}

void frmGetGoodsDlg::OnChangeCity(QString city)
{
	QString cstr;

	// �������еĲֿ���Ϣ���ڴ�
	if (m_vStore.size() == 0)
	{
		if (!loadStore())
		{
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("���زֿ���Ϣʧ��"));
		}
	}

	// ��ȡѡ�еĳ��д���
	int index = ui.comboBox_city->currentIndex();//.GetCurSel();
	QString citycode = m_vCity.at(index).city_code.c_str();

	// ��ղֿ������˵�

	ui.comboBox_db->clear();
	// �����ֿ��б����ڳ��еĲֿ���ӵ��ֿ��б�
	for (size_t i = 0; i < m_vStore.size(); i++)
	{
		cstr = CHJGlobalFun::str2qstr(m_vStore.at(i).city_code);//��õ�ǰ�ֿ�Ķ�Ӧ�ĳ���id�б��Զ��Ÿ�����ע��������԰������id��������⣩
		if (cstr.contains(citycode)  && m_vStore.at(i).is_take == "1")//�����������id�����������������ӵ��ֿ�������˵�
			ui.comboBox_db->addItem(  CHJGlobalFun::str2qstr(m_vStore.at(i).stor_name));
	}

}


bool frmGetGoodsDlg::IsShowTakeSheetData()
{
	/*char cBuf[2] = { 0 };
	::GetPrivateProfileString("info", "HJ.ShowTakeSheetDate", "0", cBuf, sizeof(cBuf), );*/
	//QString  strIniPath = g_Global.GetSystemPath() + CONSTANT_SYSTEM_INI_NAME;
	QString  buf;
	App::GetPriProfileString(g_Global.GetSystemIniPath(), QStringLiteral("info"), QStringLiteral("HJ.ShowTakeSheetDate"), buf);
	return buf.contains("1") ? true : false;
}



//��ʼ������Ʒ�������˵�
void frmGetGoodsDlg::IniVarietyComboBox()
{
	ui.comboBox_type->clear();
	//m_combgoodstype.ResetContent();

	int n = 0;
	for (size_t i = 0; i < g_TraderCpMgr.m_vVariety.size(); i++)
	{
		// ���ݽ���ͨ���Ե�Ҫ��ȥ����Ʒ��
		if (g_TraderCpMgr.m_vVariety.at(i).name != "Ag99.9")
		{
			ui.comboBox_type->insertItem(n, g_TraderCpMgr.m_vVariety.at(i).name);
			ui.comboBox_type->setItemData(n, QVariant::fromValue<int>(i));
			//m_combgoodstype.InsertString(n, g_TraderCpMgr.m_vVariety.at(i).name.c_str());
			//m_combgoodstype.SetItemData(n, (DWORD)i);

			n++;
		}
	}
}
// ����˸ı�ʱ�Ĵ����������ı�֤����ź�֤������
void frmGetGoodsDlg::OnCbnSelchangeComboPerson()
{
	int index = ui.comboBox_person->currentIndex();//.GetCurSel();

	if (index == -1 || g_Global.m_almTake_Man_List.size() == 0)
	{
		return;
	}

	// ��õ�ǰ����˵������Ϣ
	ArrayListMsg aMsg = g_Global.m_almTake_Man_List.GetValue(index);

	// ���õ�ǰ����˵�֤�����
	//m_editidcode = aMsg.GetStringEx(2).c_str();
	ui.lineEdit_seq->setText(CHJGlobalFun::str2qstr(aMsg.GetStringEx(2)));
	//UpdateData(false);

	// ��õ�ǰ����˵�֤������id�������ж�����ö��ŷָ���ע��һ������ô�����ж��id�أ���֣�
	QString cstr = CHJGlobalFun::str2qstr(aMsg.GetStringEx(1));

	QVector<QString> vec;
	CHJGlobalFun::SplitStrToVector(cstr, ",", vec);

	//m_combidtype.ResetContent();
	ui.comboBox_credit->clear();
	for (size_t i = 0; i < vec.size(); i++)
	{
		ui.comboBox_credit->insertItem(i, g_TraderCpMgr.GetIdTypeName(vec.at(i)));
		//m_combidtype.InsertString(i, g_TraderCpMgr.GetIdTypeName(CHJGlobalFun::CStringToString(vec.at(i))).c_str());
	}

	// ���õ�һ����ѡ��
	ui.comboBox_credit->setCurrentIndex(0);
	//m_combidtype.SetCurSel(0);
	if (ui.comboBox_credit->count() < 2)
	{
		//m_combidtype.EnableWindow(false);
		ui.comboBox_credit->setEnabled(false);
	}
}

ArrayListMsg* frmGetGoodsDlg::GetTakeShhetDate()
{
	return &m_alm_take_sheet_date;

}



void frmGetGoodsDlg::GetTakeSheetDateFromServer()
{
	Req5041 req; //��������
	req.oper_flag = 1;
	req.branch_id = g_HeaderReq.branch_id;
	req.is_search_usefull = CONSTANT_YES_NO_YES;
	req.search_num = "10";

	Rsp5041 rsp; //Ӧ������
	if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "5041"))
	{
		//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral(CONSTANT_CONNECT_SERVER_FAIL_TIPS));
		return;
	}

	if (g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
	{
		//g_Global.m_alm_take_sheet_date = rsp.alm_take_sheet_date;
		*(ArrayListMsg*)GetTakeShhetDate() = rsp.alm_take_sheet_date;
	}
}


void frmGetGoodsDlg::LoadTakeSheetDateToComBox()
{
	ArrayListMsg* pALM = GetTakeShhetDate();

	// ��ȡ����յĸ���
	size_t iSize = pALM->size();

	// ��ȡ����Ŀ�ʼ����
	//QTime cTakeBegin = CHJGlobalFun::TranslateDateStrToCTime(g_Global.m_strExchDate);
	QDateTime cTakeBegin =  QDateTime::fromString(g_Global.m_strExchDate, "yyyy-MM-dd");
	if (!cTakeBegin.isNull())//cTakeBegin != NULL)
	{
		// ��ȡ��������
		QDateTime cTakeEnd = cTakeBegin;
		cTakeEnd.addDays(m_nTakeDayDis);// += QDateSpan(m_nTakeDayDis, 0, 0, 0);

		// ����
		for (size_t i = 0; i < iSize; i++) //�������ؽ��
		{
			//ArrayListMsg aMsg = pALM->GetValue(i); //��ȡ����ĵ�һ��������
			string sDate = pALM->GetStringEx(i);

			// �ж������Ƿ��ڿ�ʼ���ںͽ�������֮��
			//CTime cCmp = CHJGlobalFun::TranslateDateStrToCTime(sDate);
			QDateTime cCmp = QDateTime::fromString(g_Global.m_strExchDate, "yyyy-MM-dd");
			if (!cCmp.isNull() && cCmp >= cTakeBegin && cCmp <= cTakeEnd)
			{
				//m_cmbTakeDate.InsertString(i, sDate.c_str());
				ui.comboBox_last_getgoods_day->insertItem(i, CHJGlobalFun::str2qstr(sDate));
			}
		}
	}
}


// �������ļ����زֿ���Ϣ���ڴ�
bool frmGetGoodsDlg::loadStore()
{
	// ���������ļ�·��
	QString strIniPath = g_Global.GetSystemPath() + CONSTANT_DATA_INI_NAME;

	// ��ȡ�����ļ��еĲֿ���Ϣ
	//char buf[10000] = { 0 };
	//::GetPrivateProfileString("Info", "store_code", "", buf, sizeof(buf), strIniPath);
	QString buf;
	App::GetPriProfileString(strIniPath, QStringLiteral("Info"), QStringLiteral("store_code"), buf);
	int iLen = buf.toInt();//strlen(buf);

	if (buf.count() != 0)
	{
		string str = CHJGlobalFun::qstr2str(buf);
		// �����ַ��͵�hashtable
		HashtableMsg htmStore;
		if (htmStore.Parse(str) == 0)
		{
			IniStoreInfo(htmStore);
			return true;
		}
		else
		{
			//AfxMessageBox("���������ļ��вֿ���Ϣ����");
			return false;
		}
	}
	else // ��������ļ��вֿ���ϢΪ�գ�������������ͱ��ģ���ȡ�ֿ���Ϣ
	{
		Req1006 req;
		req.oper_flag = 1;

		Rsp1006 rsp;
		if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "1006"))
		{
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral(CONSTANT_CONNECT_SERVER_FAIL_TIPS));

			//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
			return false;
		}

		if (!g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
		{
			return false;
		}
		else
		{
			//��¼�ֿ���Ϣ
			IniStoreInfo(rsp.htm_stor_info);

			//д��ֿ���Ϣ���ļ�
			//::WritePrivateProfileString("Info", "store_code", rsp.htm_stor_info.ToString().c_str(), strIniPath);

			App::WritePriProfileString(strIniPath, "Info", "store_code", CHJGlobalFun::str2qstr(rsp.htm_stor_info.ToString()));
			return true;
		}
	}
}


// �������еĲֿ�
void frmGetGoodsDlg::IniStoreInfo(HashtableMsg &htm)
{
	for (size_t i = 0; i < htm.size(); i++)
	{
		StoreInfoEx storeinfo;
		storeinfo.stor_id = htm.GetString(i, "stor_id");
		storeinfo.stor_name = htm.GetString(i, "stor_name");
		storeinfo.addr = htm.GetString(i, "addr");
		storeinfo.tel = htm.GetString(i, "tel");
		storeinfo.fax = htm.GetString(i, "fax");
		storeinfo.link_man = htm.GetString(i, "link_man");
		storeinfo.zip_code = htm.GetString(i, "zip_code");
		storeinfo.use_variety_type = htm.GetString(i, "use_variety_type");
		storeinfo.is_take = htm.GetString(i, "is_take");
		storeinfo.city_code = htm.GetString(i, "city_code");

		m_vStore.push_back(storeinfo);
	}
}


// �������ļ����س�����Ϣ���ڴ�
bool frmGetGoodsDlg::loadCityFromFile()
{
	// ���������ļ�·��
	QString strIniPath = g_Global.GetSystemPath() + CONSTANT_DATA_INI_NAME;

	// ��������ļ��еĳ�����Ϣ��Ϊ�գ����ȡ
	//char buf[10000] = { 0 };
	//::GetPrivateProfileString("Info", "city_code", "", buf, sizeof(buf), strIniPath);

	QString buf;
	App::GetPriProfileString(strIniPath, QStringLiteral("Info"), QStringLiteral("city_code"), buf);


	if (buf.count() != 0)
	{
		//�����ַ��͵�hashtable
		string str = CHJGlobalFun::qstr2str(buf);
		HashtableMsg htmCity;
		if (htmCity.Parse(str) == 0)
		{
			// ��������ɹ�������س�����Ϣ���ڴ�
			IniCityInfo(htmCity);
			return true;
		}
		else
		{
			//AfxMessageBox("���������ļ��г�����Ϣ����");
			return false;
		}
	}
	else // ��������ļ��вֿ���ϢΪ�գ�������������ͱ��ģ���ȡ�ֿ���Ϣ
	{
		Req1007 req;
		req.oper_flag = 1;

		Rsp1007 rsp;
		if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "1007"))
		{
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral(CONSTANT_CONNECT_SERVER_FAIL_TIPS));

			//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
			return false;
		}

		if (!g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
		{
			return false;
		}
		else
		{
			// ���س�����Ϣ���ڴ�
			IniCityInfo(rsp.htm_code_list);

			// д�������Ϣ���ļ�
			//::WritePrivateProfileString("Info", "city_code", rsp.htm_code_list.ToString().c_str(), strIniPath);

			QString buf;
			App::WritePriProfileString(strIniPath, QStringLiteral("Info"), QStringLiteral("city_code"), CHJGlobalFun::str2qstr(rsp.htm_code_list.ToString()));




			return true;
		}
	}
}

// ���س�����Ϣ���ڴ�
void frmGetGoodsDlg::IniCityInfo(HashtableMsg &htm)
{
	for (size_t i = 0; i < htm.size(); i++)
	{
		CityInfo cityinfo;
		cityinfo.all_stor_id = htm.GetString(i, "all_stor_id");
		cityinfo.city_code = htm.GetString(i, "city_code");
		cityinfo.city_name = htm.GetString(i, "city_name");
		cityinfo.stor_id_default = htm.GetString(i, "stor_id_default");

		// added by Jerry Lee, 2013-6-27, ���˵�û������ֿ�ĳ���
		for (int j = 0; j < m_vStore.size(); j++)
		{
			if (m_vStore[j].city_code.find(cityinfo.city_code) != string::npos)
			{
				m_vCity.push_back(cityinfo);
				break;
			}
		}
	}
}


// ��ʼ��������������˵�
void frmGetGoodsDlg::IniCityComboBox()
{
	ui.comboBox_city->clear();
	//m_combcity.ResetContent();
	for (size_t i = 0; i < m_vCity.size(); i++)
	{
		//m_combcity.InsertString(i, m_vCity.at(i).city_name.c_str());
		ui.comboBox_city->insertItem(i, CHJGlobalFun::str2qstr( m_vCity.at(i).city_name));
	}

}


bool frmGetGoodsDlg::CheckInput()
{
	//�ж�combo�ؼ��Ƿ�ѡ��

	int index;

	//�Ƿ�ѡ�����
	index = ui.comboBox_city->currentIndex();
	if (index == -1)
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��ѡ���������"));

		//AfxMessageBox("��ѡ���������");
		//GetDlgItem(IDC_COMBO_CITY)->SetFocus();
		ui.comboBox_city->setFocus();
		return false;
	}

	//�Ƿ�ѡ������ֿ�
	//index = m_combbarn.GetCurSel();
	index = ui.comboBox_db->currentIndex();


	if (index == -1)
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��ѡ������ֿ�"));
		//AfxMessageBox("��ѡ������ֿ�");
		//GetDlgItem(IDC_COMBO_BARN)->SetFocus();
		ui.comboBox_db->setFocus();
		return false;
	}

	//�Ƿ�ѡ�������
	//index = m_combperson.GetCurSel();
	index = ui.comboBox_person->currentIndex();

	if (index == -1)
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��ѡ�������"));
		//AfxMessageBox("��ѡ�������");
		//GetDlgItem(IDC_COMBO_PERSON)->SetFocus();
		ui.comboBox_person->setFocus();
		return false;
	}

	///�Ƿ�ѡ���������
	//index = m_combidtype.GetCurSel();
	index = ui.comboBox_credit->currentIndex();

	if (index == -1)
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��ѡ��֤������"));

		//AfxMessageBox("��ѡ��֤������");
		///GetDlgItem(IDC_COMBO_IDTYPE)->SetFocus();
		ui.comboBox_credit->setFocus();
		return false;
	}

	//�Ƿ�ѡ��Ʒ��
	//index = m_combgoodstype.GetCurSel();
	index = ui.comboBox_type->currentIndex();

	if (index == -1)
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��ѡ�񽻸�Ʒ��"));

		//AfxMessageBox("��ѡ�񽻸�Ʒ��");
		//GetDlgItem(IDC_COMBO_GOODSTYPE)->SetFocus();
		ui.comboBox_type->setFocus();
		return false;
	}

	//�ж���������Ƿ���ȷ
	if (!IsWeightRight())
	{
		//GetDlgItem(IDC_EDIT_WEIGHT)->SetFocus();

		ui.lineEdit_weight->setFocus();
		return false;
	}

	//֤�����У��
	if (!CheckIDCard())
	{
		//GetDlgItem(IDC_EDIT_IDCODE)->SetFocus();
		ui.lineEdit_seq->setFocus();
		return false;
	}

	//������֤
	if (!CheckPassword())
	{
		//GetDlgItem(IDC_EDIT_PSW)->SetFocus();
		ui.lineEdit_pswd->setFocus();
		return false;
	}

	//

	// 
	if (m_bShowTakeSheetDate)
	{
		if (ui.comboBox_last_getgoods_day->currentIndex() == -1)
		{
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("��ѡ�������"));

			//AfxMessageBox("��ѡ�������");
			//GetDlgItem(IDC_COMBO_TAKE_DATE)->SetFocus();
			ui.comboBox_last_getgoods_day->setFocus();

			return false;
		}
	}

	return true;
}


void frmGetGoodsDlg::OnApplyGoods()
{
	if (CheckInput())
	{
		if (QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("ȷʵҪ���������?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) //����ȷ�ϴ���
		{
			Req5101 req; //��������

			//ҵ������
			req.oper_flag = 2;
			req.app_record = CHJGlobalFun::qstr2str(g_Global.m_strUserID);
			req.acct_no = CHJGlobalFun::qstr2str(g_Global.m_strUserID);
			req.cust_id = CHJGlobalFun::qstr2str(g_Global.m_strUserID);

			//�󶨿ؼ���Ϣ

			int index;
			QString text;

			// ������д���
			index = ui.comboBox_city->currentIndex();
			req.city_code = m_vCity.at(index).city_code;

			// ����ֿ���� 
			index = ui.comboBox_db->currentIndex();
			text = ui.comboBox_db->currentText();

			req.stor_id = GetStoreId(CHJGlobalFun::qstr2str(text));

			//���Ʒ��id
			index = ui.comboBox_db->currentIndex();

			int nIndex = ui.comboBox_type->itemData(index).toInt();//(int)m_combgoodstype.GetItemData(index);
			req.variety_id = CHJGlobalFun::qstr2str(g_TraderCpMgr.m_vVariety.at(nIndex).variety_id);
			//�����������
			req.app_amount = CHJGlobalFun::qstr2str(ui.lineEdit_weight->text());

			//�����
			index = ui.comboBox_person->currentIndex();
			//index = m_combperson.GetCurSel();
			//m_combperson.GetLBText(index, text);
			req.take_man = CHJGlobalFun::qstr2str(ui.comboBox_person->currentText());

			//֤������
			index = ui.comboBox_credit->currentIndex();
			//m_combidtype.GetLBText(index, text);
			req.cert_type_id = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetIdTypeId(ui.comboBox_credit->currentText()));

			//֤�����
			req.cert_num = CHJGlobalFun::qstr2str(ui.lineEdit_seq->text());
		
			//����  
			req.app_pwd = CHJGlobalFun::qstr2str(ui.lineEdit_pswd->text());

			if (m_bShowTakeSheetDate)
			{

				index = ui.comboBox_last_getgoods_day->currentIndex();
				//m_cmbTakeDate.GetLBText(index, text);
				req.take_date = CHJGlobalFun::qstr2str(ui.comboBox_last_getgoods_day->currentText());
			}

			Rsp5101 rsp; //Ӧ������
			if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "5101"))
			{
				QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral(CONSTANT_CONNECT_SERVER_FAIL_TIPS));
				//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
				return;
			}

			if (g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
			{
				QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("������������������룬�����Ե����ѯ��ť���²�ѯ��������б�"));
				//AfxMessageBox("������������������룬�����Ե����ѯ��ť���²�ѯ��������б�");
			}
		}
	}
}




// ���ݲֿ����ƻ�ȡ�ֿ�id
string frmGetGoodsDlg::GetStoreId(const string &sName)
{
	for (size_t i = 0; i < m_vStore.size(); i++)
	{
		if (m_vStore.at(i).stor_name == sName)
			return m_vStore.at(i).stor_id;
	}

	return sName;
}








// �ж��û��������������Ƿ���ȷ
bool frmGetGoodsDlg::IsWeightRight()
{
	int min_pickup=0;
	int pickup_base=0;
	int input=0;
	QString cstr;

	//����ѡ��Ʒ�ֻ�ȡ��Ʒ����С��������������
	//m_combgoodstype.GetLBText(m_combgoodstype.GetCurSel(), cstr);
	cstr = ui.comboBox_type->currentText();
	//string str = CHJGlobalFun::qstr2str(cstr);
	for (size_t i = 0; i < g_TraderCpMgr.m_vVariety.size(); i++)
	{
		if (cstr == g_TraderCpMgr.m_vVariety.at(i).name)
		{
			min_pickup = (int)g_TraderCpMgr.m_vVariety.at(i).min_pickup;
			pickup_base = (int)g_TraderCpMgr.m_vVariety.at(i).pickup_base;
			break;
		}
	}

	input = ui.lineEdit_weight->text().toInt();//atoi(m_editweight);
	if (input < min_pickup)//�Ƿ�������С�����
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�����������С����С�������"));

		//AfxMessageBox("");
		return false;
	}
	else
	{
		if ((input - min_pickup) % pickup_base != 0)//�Ƿ������������
		{
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("����������������㲽��Ҫ��"));

			//AfxMessageBox("");
			return false;
		}
	}
	return true;
}
//��������������ȷ��
bool frmGetGoodsDlg::CheckPassword()
{
	//�ж������Ƿ�������ȷ������ʾ���Ƿ������֣�
	if (ui.lineEdit_pswd->text() == "")
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("���벻��Ϊ��"));

		//AfxMessageBox("");
		//GetDlgItem(IDC_EDIT_PSW)->SetFocus();
		ui.lineEdit_pswd->setFocus();
		return false;
	}
	if (!CHJGlobalFun::IsNumber(ui.lineEdit_pswd->text()))
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�������Ϊ����"));

		//AfxMessageBox("");
		//GetDlgItem(IDC_EDIT_PSW)->SetFocus();
		ui.lineEdit_pswd->setFocus();
		return false;
	}

	//�ж������Ƿ�������ȷ������ʾ���Ƿ������֣�
	if (ui.lineEdit_ensure->text() == "")
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("ȷ�����벻��Ϊ��"));

		//AfxMessageBox("");
		//GetDlgItem(IDC_EDIT_CONPWD)->SetFocus();
		ui.lineEdit_ensure->setFocus();
		return false;
	}
	if (!CHJGlobalFun::IsNumber(ui.lineEdit_ensure->text()))
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("ȷ���������Ϊ����"));

		//AfxMessageBox("ȷ���������Ϊ����");
		//GetDlgItem(IDC_EDIT_CONPWD)->SetFocus();

		ui.lineEdit_ensure->setFocus();
		return false;
	}

	//�ж�ȷ�������Ƿ���ȷ��������Ƚϣ�
	if (ui.lineEdit_pswd->text() != ui.lineEdit_ensure->text())
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�����������벻һ��"));

		//AfxMessageBox("�����������벻һ��!");
		//GetDlgItem(IDC_EDIT_CONPWD)->SetFocus();
		ui.lineEdit_ensure->setFocus();
		return false;
	}

	return true;
}

//����û�id�������ȷ��
bool frmGetGoodsDlg::CheckIDCard()
{
	//�ж�֤������Ƿ���ȷ�������֤�����ʱ�������֤�����Ƿ���ȷ������ʾ��
	//int len = m_editidcode.GetLength();
	int len = ui.lineEdit_seq->text().count();
	if (len == 0)
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("������֤�����"));

		//AfxMessageBox("������֤�����");
		return false;
	}

	//�ж�������Ƿ�ֻ�������ֺ���ĸ���

	//�жϵ�ǰ�Ƿ�ѡ�������֤������ǣ����ж��Ƿ���15λ����18λ����������򷵻�false������ǣ���У�����֤�ĺϷ���

	return true;
}
//�ж�15Ϊ���֤�����Ƿ���ȷ
bool frmGetGoodsDlg::CheckIDCard15(QString Id)
{
	//�ж��Ƿ�ȫ��������
	if (!CHJGlobalFun::IsNumber(Id))
		return false;

	//�ж�ʡ���Ƿ���ȷ
	QString address = "11x22x35x44x53x12x23x36x45x54x13x31x37x46x61x14x32x41x50x62x15x33x42x51x63x21x34x43x52x64x65x71x81x82x91";
	if (!address.contains(Id.left(2)))
		return false;

	//�жϳ��������Ƿ���ȷ
	if (!IsRightDate("19" + Id.mid(6, 6)))
		return false;

	return true;
}
//�ж�18Ϊ���֤�����Ƿ���ȷ
bool frmGetGoodsDlg::CheckIDCard18(QString Id)
{
	//�ж��Ƿ�ȫ��������
	if (!CHJGlobalFun::IsNumber(Id.left(17)))
		return false;

	//�ж�ʡ���Ƿ���ȷ
	QString address = "11x22x35x44x53x12x23x36x45x54x13x31x37x46x61x14x32x41x50x62x15x33x42x51x63x21x34x43x52x64x65x71x81x82x91";
	if (!address.contains(Id.left(2)) )
		return false;

	//�жϳ��������Ƿ���ȷ
	if (!IsRightDate(Id.mid(6, 8)))
		return false;

	//�ж�У����
	int     Wi[17] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };//����ߵ�����17λ�Ķ�Ӧλ�ĳ���
	char fchar[11] = { '1','0','x','9','8','7','6','5','4','3','2' };//������Ӧ�Ĳ�����
	int sum = 0;
	for (int i = 0; i < 17; i++)
	{
		char mychar = Id.at(i).toLatin1();
		sum += (mychar - char('0')) * Wi[i];
	}
	sum = sum % 11;
	if (fchar[sum] != Id.at(17))
		return false;

	return true;
}
/*
�ж�һ�������Ƿ���ȷ���������֤�����ڵ�У��
input:datestr����ʽ��19850101)
*/
bool frmGetGoodsDlg::IsRightDate(QString datestr)
{
	int year, month, day;
	bool isloop;
	int loopyear[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };//������·�����
	int normalyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	//���int���͵�������
	year = datestr.left(4).toInt();
	month = datestr.mid(4, 2).toInt();
	day = datestr.mid(6, 2).toInt();

	//�ж��·ݺ����ڵĻ�����ȷ��
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	//�ж��Ƿ�������
	isloop = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	//���������Ƿ��ж�ÿ�µ������Ƿ���ȷ���·ݵı��벻���ڲ���
	if (isloop && loopyear[month - 1] < month)
		return false;
	if (!isloop && normalyear[month - 1] < month)
		return false;

	return true;
}





void frmGetGoodsDlg::OnSearch()
{
	//���list�ؼ�
	//m_1list1.DeleteAllItems();
	tableModel->removeRows(0, tableModel->rowCount());
	Rsp5101 rsp; //Ӧ������


	//if (g_TiHuoMgr.Query(rsp,
	//	CHJGlobalFun::GetFormatTimeStr(m_timebegin),
	//	CHJGlobalFun::GetFormatTimeStr(m_timeend),
	//	""))

		if (g_TiHuoMgr.Query(rsp,
			CHJGlobalFun::qstr2str(ui.dateEdit_st->text()),
			CHJGlobalFun::qstr2str(ui.dateEdit_end->text()),
			""))
	{
		for (size_t i = 0; i < rsp.htm_take_sheet_detail.size(); i++)
		{
			string value[19];
			value[0] = rsp.htm_take_sheet_detail.GetString(i, "local_sheet_no");           // �����ˮ��
			value[1] = rsp.htm_take_sheet_detail.GetString(i, "sheet_no");                 // ��������
			value[2] = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetVarietyName(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "variety_id"))));   // ���Ʒ��
			value[3] = rsp.htm_take_sheet_detail.GetString(i, "app_amount");               // �������(��)
			value[4] = rsp.htm_take_sheet_detail.GetString(i, "city_code");                // �������
			value[5] = GetStoreName(rsp.htm_take_sheet_detail.GetString(i, "stor_id"));    // ����ֿ�
			value[6] = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetTake_statName(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "stat"))));   // ���״̬
			value[7] = CHJGlobalFun::qstr2str(CHJGlobalFun::FormatDate(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "app_date"))));     // �����������
			value[8] = CHJGlobalFun::qstr2str(CHJGlobalFun::FormatDate(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "app_end_date")))); // �����������
			value[9] = CHJGlobalFun::qstr2str(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "take_margin")))); // �����֤��
			value[10] = CHJGlobalFun::qstr2str(CHJGlobalFun::FormatDate(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "cancel_date"))));  // ��������
			value[11] = CHJGlobalFun::qstr2str(CHJGlobalFun::FormatTime(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "cancel_time"))));  // ����ʱ��
			value[12] = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetDraw_typeName(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "draw_type"))));  // �������
			value[13] = rsp.htm_take_sheet_detail.GetString(i, "self_draw");          // ��������(��)
			value[14] = rsp.htm_take_sheet_detail.GetString(i, "trade_draw");         // ��������(��)
			value[15] = rsp.htm_take_sheet_detail.GetString(i, "take_man");           // ���������
			value[16] = CHJGlobalFun::qstr2str(g_TraderCpMgr.GetIdTypeName(CHJGlobalFun::str2qstr(rsp.htm_take_sheet_detail.GetString(i, "cert_type_id")))); // ֤������
			value[17] = rsp.htm_take_sheet_detail.GetString(i, "cert_num");          // ֤������
			value[18] = rsp.htm_take_sheet_detail.GetString(i, "rsp_msg");           // ������Ϣ

			tableModel->insertRow(i);
			for (int j = 0; j < 19; j++)
				tableModel->setItem(i, j, new QStandardItem(CHJGlobalFun::str2qstr(value[j])));
			/*m_1list1.InsertItem(i, value[0].c_str());
			for (int j = 1; j < 19; j++)
				m_1list1.SetItemText(i, j, value[j].c_str());*/
		}
	}
}
void frmGetGoodsDlg::OnPrint()
{
	int index = ui.tableView->currentIndex().row();//m_1list1.GetSelectionMark();//
	if (index == -1)
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("����ѡ����"));
		//AfxMessageBox("����ѡ����");
	}
	else
	{
		QString strSheet_No = tableModel->item(index, 1)->text();//m_1list1.GetItemText(index, 1); //��ȡ��������
		if (strSheet_No == "")
		{
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�������û������ɹ������ܴ�ӡ"));
			//AfxMessageBox("�������û������ɹ������ܴ�ӡ");
			return;
		}

		// ���ȡѡ���е����״̬�����ƣ������״̬��Ϊ����ɹ����������ʾ
		QString  strState = tableModel->item(index, 6)->text();//m_1list1.GetItemText(index, 6); // ��ȡ�����״̬
		string strStateID =CHJGlobalFun::qstr2str( g_TraderCpMgr.GetTake_statID(strState));
		if (strStateID != CONSTANT_B_SHEET_STAT_SUCCESS)
		{
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�������û������ɹ������ܴ�ӡ"));
			//AfxMessageBox("�������û������ɹ������ܴ�ӡ");
			return;
		}

		//���ͱ���
		Req5103 req; //��������
		req.oper_flag = 1;
		req.sheet_no = CHJGlobalFun::qstr2str(strSheet_No);  //��������   ��������"TH201205210042"    

		Rsp5103 rsp; //Ӧ������
		if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "5103"))
		{
			QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("CONSTANT_CONNECT_SERVER_FAIL_TIPS"));
			//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
			return;
		}

		if (g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
		{
			/*CPrintFrame *pFrame = new CPrintFrame((CDialog*)AfxGetMainWnd());

			pFrame->m_pPrintView->m_iType = E_TIHUO;
			//��ʼ����ӡ����
			pFrame->m_pPrintView->IniTiHuoData(rsp);

			pFrame->DoPrintView();*/
		}
	}
}
void frmGetGoodsDlg::OnCancel()
{
	//int index = m_1list1.GetSelectionMark();
	int index = ui.tableView->currentIndex().row();
	if (index != -1)
	{
		if(QMessageBox::information(nullptr,QStringLiteral("��ʾ"),QStringLiteral("ȷʵҪ����������?"),QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes )
		//if (MessageBox("ȷʵҪ����������?", "��ʾ", MB_YESNO | MB_ICONINFORMATION) == IDYES) //����ȷ�ϴ���
		{
			Req5101 req; //��������
			req.oper_flag = 3;
			req.local_sheet_no = CHJGlobalFun::qstr2str(tableModel->item(0, 1)->text());//�����ˮ��
			req.acct_no = CHJGlobalFun::qstr2str(g_Global.m_strUserID);
			req.take_man = CHJGlobalFun::qstr2str(tableModel->item(0, 1)->text());//���������

			Rsp5101 rsp; //Ӧ������
			if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "5101"))
			{
				QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("CONSTANT_CONNECT_SERVER_FAIL_TIPS"));
				//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
				return;
			}

			if (g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr( rsp.rsp_msg)))
			{
				QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("�����������ͳ������룬���ɵ����ѯ��ť���²�ѯ��������б�"));
				
				//AfxMessageBox("�����������ͳ������룬���ɵ����ѯ��ť���²�ѯ��������б�");
			}
		}
	}
	else
	{
		QMessageBox::information(nullptr, QStringLiteral("��ʾ"), QStringLiteral("����ѡ����"));
		//AfxMessageBox("����ѡ����");
	}
}



// ���ݲֿ�ID��ȡ�ֿ�����
string frmGetGoodsDlg::GetStoreName(const string &sID)
{
	for (size_t i = 0; i < m_vStore.size(); i++)
	{
		if (m_vStore.at(i).stor_id == sID)
			return m_vStore.at(i).stor_name;
	}

	return sID;
}