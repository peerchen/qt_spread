//#include "stdafx.h"
#include "HJQueryBase.h"
//#include "HJSetColumnDlg.h"
//#include "excel.h"
#include "MyExcel.h"
//#include "Option.h"
#include "HJConstant.h"
#include "Global.h"
#include "HJGlobalFun.h"
#include "app.h"
#include "inifilesmanager.h"
#include <QMessageBox>


#pragma execution_character_set("utf-8")


struct PageNumST
{
    char Name[32];
    int Num;
};

const PageNumST PAGENUMS[] = {
    {"ÿҳ10����¼", 10},
    {"ÿҳ20����¼", 20},
    {"ÿҳ50����¼", 50},
    {"ÿҳ100����¼", 100}
};

// ���뷽ʽ��1������룩 3���Ҷ��룩

CHJQueryBase::CHJQueryBase( void )
{
	//ui->tableView->setModel(m_tableModle);
}

CHJQueryBase::~CHJQueryBase( void )
{

}

void CHJQueryBase::InitPage()
{
	int num = m_cmbPage->count();
	for (int i = num-1; i >= 0; num--)
	{
		m_cmbPage->removeItem(num);
	}
	//m_cmbPage->clear();
	m_cmbPage->insertItem(0, ("��1ҳ"));
	//m_cmbPage->setItemData();//.AddString("��1ҳ");
	m_cmbPage->setCurrentIndex(0);
}

int CHJQueryBase::GetCurPage()
{
	int iPage = m_cmbPage->currentIndex();//.GetCurSel(); //��ȡ��ǰҳ��
	iPage++;
	if (iPage <= 0)
		iPage = 1;
	return iPage;
}

void CHJQueryBase::InitPageNum()
{

    for(int i = 0; i < (sizeof(PAGENUMS)/sizeof(PAGENUMS[0])); i++)
    {

        m_cmbNum->insertItem(i, PAGENUMS[i].Name);

    }
	
	m_cmbNum->setCurrentIndex(0);
}

int CHJQueryBase::GetPageNum()
{
	int index = m_cmbNum->currentIndex();
	if(index == -1) index = 0;
    // mod by Jerry Lee, �޸�Ϊ���ع̶��ļ�¼����, 2013-3-5
	//return atoi(g_TraderCpMgr.m_vPageInfo.at(index).code_id.c_str());
    return PAGENUMS[index].Num;
	/*
	switch(index)
	{
	case 0: return 10;
	case 1: return 20;
	case 2: return 50;
	}

	return 10;
	*/
}

void CHJQueryBase::SetComboxCurPage( EPageBtnType ePagebtnType )
{
	int cursel;
	if(ePagebtnType == E_FIRST) // ��ҳ
	{
		m_cmbPage->setCurrentText(0);
		return;
	}
	else if(ePagebtnType == E_LAST)  // ���һҳ
	{
		int count = m_cmbPage->count();//.GetCount();
		cursel = --count;
	}
	else // typeΪ2����3
	{
		cursel = m_cmbPage->currentIndex();//.GetCurSel();
		if(ePagebtnType == E_FORWARD) // ��һҳ
		{
			cursel--;
		}
		else // ��һҳ
		{
			cursel++;
		}
	}

	m_cmbPage->setCurrentIndex(cursel);
}

void CHJQueryBase::ResetComboxPage( const int &iTotal, int &iCurPage )
{
	int atemp = m_cmbPage->count();
	
    for (; atemp >= 0; atemp--)
	{
		m_cmbPage->removeItem(atemp);
		// cb->setItemText (atemp, "ddd");
	 }

	//m_cmbPage->removeItem   clear();// ResetContent();
	QString cstr;
	for(int i = 0 ; i < iTotal; i++)
	{
		cstr =  QString(("��%1ҳ")).arg(i+1);
		//cstr.sprintf(QStringLiteral("��%dҳ"), i+1);
		m_cmbPage->insertItem(i, cstr);
	}
	
	m_cmbPage->setCurrentIndex(--iCurPage);

}

void CHJQueryBase::OnButtonFirst()
{
	if(m_tableModle->rowCount()/* .GetItemCount()*/ != 0)
	{
		if(m_cmbPage->currentIndex()/* GetCurSel()*/ == 0)
		{
			//AfxMessageBox("�Ѿ�����ҳ");
			QMessageBox::information(nullptr, ("ϵͳ��ʾ"), ("�Ѿ�����ҳ!"));
		}
		else
		{
			// ����Ϊ��ҳ
			SetComboxCurPage(E_FIRST);
			OnButtonQuery();
		}
	}
}

void CHJQueryBase::OnButtonPrev()
{
	if(m_tableModle->rowCount() != 0)
	{
		if(m_cmbPage->currentIndex() == 0)
		{
			QMessageBox::information(nullptr, ("ϵͳ��ʾ"), ("�Ѿ�����ҳ!"));
		}
		else
		{
			SetComboxCurPage(E_FORWARD); // ����Ϊ��һҳ
			OnButtonQuery();
		}
	}
}

void CHJQueryBase::OnButtonNext()
{
	if(m_tableModle->rowCount() != 0)
	{
		int count = m_cmbPage->count();//.GetCount(); // ��ȡѡ����ܸ���
		count--;
		if(count == m_cmbPage->currentIndex())
		{
			QMessageBox::information(nullptr, ("ϵͳ��ʾ"), ("�Ѿ���ĩҳ!"));
			return;
		}
		else
		{
			SetComboxCurPage(E_NEXT);// ����Ϊ��һҳ
			OnButtonQuery();
		}
	}
}

void CHJQueryBase::OnButtonLast()
{
	if(m_tableModle->rowCount() != 0)
	{
		if(m_cmbPage->count() == m_cmbPage->currentIndex() + 1)
		{
			QMessageBox::information(nullptr, ("ϵͳ��ʾ"), ("�Ѿ���ĩҳ!"));
			return;
		}
		else
		{
			SetComboxCurPage(E_LAST);// ����Ϊ���һҳ
			OnButtonQuery();
		}
	}
}

void CHJQueryBase::OnButtonQuery()
{
	Req6002 stReq6002;
	Rsp6002 stRsp6002;

	/*
	if(m_bHistory)
	{
		CTime timeBegin,timeEnd;
		((CDateTimeCtrl*)GetDlgItem(DATETIME_BEGIN_CONTROL_ID))->GetTime(timeBegin);  // ��ȡ��ʼ���ںͽ�������
		((CDateTimeCtrl*)GetDlgItem(DATETIME_END_CONTROL_ID))->GetTime(timeEnd);      // ��ȡ��������

		if(timeBegin > timeEnd)
		{
			AfxMessageBox(CONSTANT_BEGIN_DATE_BIGGER);
			return;
		}
	}
	*/

	//m_tableModle->clear();//.DeleteAllItems(); //���list�ؼ�

	m_tableModle->removeRows(0, m_tableModle->rowCount());

	// ��ȡ����Ĳ�ѯ����
	QVector< pair<QString, QString> >  vecPara;
	GetQueryPara(vecPara);

	// ��ȡ��ǰѡ�е�ҳ����ÿҳ��
	int iCurPage = GetCurPage();   
	int iPageNum = GetPageNum();

	// ��������ύ��ѯ����
    stRsp6002.page_count = 1;
    stRsp6002.curr_page  = 1;

	if (Query(GetQueryID(), vecPara, iPageNum, iCurPage, stReq6002, stRsp6002))
	{
		ShowQueryResult(stReq6002, stRsp6002);
	}

	// ���¼���ҳ�������˵��͵�ǰѡ��ҳ��
	//ResetComboxPage(stRsp6002.page_count, stRsp6002.curr_page);
}

void CHJQueryBase::OnButtonQuery( QDateTime &dtBegin, QDateTime &dtEnd )
{
	QDate timeBegin,timeEnd;
	dtBegin.setDate(timeBegin);
	dtEnd.setDate(timeEnd);

	if(timeBegin > timeEnd)
	{		
		QMessageBox::information(nullptr, ("ϵͳ��ʾ"), (CONSTANT_BEGIN_DATE_BIGGER));
		return;
	}
	else
	{
		OnButtonQuery();
	}
}

void CHJQueryBase::LoadList()
{
	m_vecColumnIndexs.clear();

	// ��ȡ�����ļ���·��
	QString strPath;
	string strQueryID = GetQueryID(); // ???????ID,????????????

#ifdef _WIN32
	strPath = QString("%1QueryConfig\\%2.ini").arg(g_Global.GetSystemPath()).arg(CHJGlobalFun::str2qstr(strQueryID));

#else
    strPath = QString("%1QueryConfig/%2.ini").arg(g_Global.GetSystemPath()).arg(CHJGlobalFun::str2qstr(strQueryID));
#endif

	QString strValue;
	QString strAligns;
	size_t i;
	QVector<QString> vecAllNames;
	QVector<int>     vecAllWidths;
	QVector<int>     vecAllAligns;
	QVector<QString> vecUserName;
	QVector<int>     vecUserWidths;
	QVector<int>     vecUserAligns;

	//char buf[2000] = {0};

	// ��ȡ�û�ѡ���е�ID�����ҷָvector
	//::GetPrivateProfileString("Info", "UserColumnIndexs", "", buf, sizeof(buf), strPath);
	//strValue = buf;

	App::GetPriProfileString(strPath, ("Info"), ("UserColumnIndexs"), strValue);
	CHJGlobalFun::SplitStrToVector(strValue, (QUERY_INI_SPLITER), m_vecColumnIndexs);

	// ��ȡȫ���ֶ����ƣ����ָvector
	//::GetPrivateProfileString("Info", "AllColumnNames", "", buf, sizeof(buf), strPath);
	App::GetPriProfileString(strPath, ("Info"), ("AllColumnNames"), strValue);

	//strValue = buf;
	CHJGlobalFun::SplitStrToVector(strValue, (QUERY_INI_SPLITER), vecAllNames);

	// ��ȡȫ���ֶο�ȣ����ָvector
	//::GetPrivateProfileString("Info", "AllColumnWidths", "", buf, sizeof(buf), strPath);
	//strValue = buf;
	App::GetPriProfileString(strPath, ("Info"), ("AllColumnWidths"), strValue);
	CHJGlobalFun::SplitStrToVector(strValue, (QUERY_INI_SPLITER), vecAllWidths);

	// ��ȡȫ���ֶζ��䷽ʽ�����ָvector
	//::GetPrivateProfileString("Info", "AllColumnAligns", "", buf, sizeof(buf), strPath);
	//strValue = buf;
	App::GetPriProfileString(strPath, ("Info"), ("AllColumnAligns"), strValue);

	CHJGlobalFun::SplitStrToVector(strValue, (QUERY_INI_SPLITER), vecAllAligns);

	// ����λ���ֶΣ���ȡ�û�ѡ���ÿһ�еĶ�Ӧ����Ϣ���п����뷽ʽ��
	for(i = 0; i < m_vecColumnIndexs.size(); i++)
	{
		// ���ر�������
		int iPos = m_vecColumnIndexs.at(i);
		vecUserName.push_back(vecAllNames.at(iPos));

		// ���ض��䷽ʽ
		int iAlign;
		if(vecAllAligns.at(iPos) == 1)
		{
			iAlign = Qt::AlignLeft;//LVCFMT_LEFT;
		}
		else if(vecAllAligns.at(iPos) == 3)
		{
			iAlign = Qt::AlignRight;
		}
		else
		{
			iAlign = Qt::AlignCenter;
		}
		vecUserAligns.push_back(iAlign);

		// �����п�
		vecUserWidths.push_back(vecAllWidths.at(iPos));
	}


	// ���ر��⵽list
	m_tableModle->setColumnCount(vecUserName.size());
	for(i = 0; i < vecUserName.size(); i++)
	{
		m_tableModle->setHeaderData(i, Qt::Horizontal, vecUserName.at(i));

		//m_list->column(i, vecUserName.at(i), vecUserAligns.at(i), vecUserWidths.at(i));

	}

	// ��ȡ�û�ѡ����ֶ�ID����¼��ArraylistMsg
	GetUserColumnIDs(strPath);
}

void CHJQueryBase::GetUserColumnIDs( const QString &strPath )
{
	QVector<QString> vecAllColumnIDs;
	QString strValue;
	//char buf[2000] = {0};
	// ��ȡȫ���ֶ����ƣ����ָvector
	//::GetPrivateProfileString("Info", "AllColumnIDs", "", buf, sizeof(buf), strPath);
	//strValue = buf;

	App::GetPriProfileString(strPath, ("Info"), ("AllColumnIDs"), strValue);

	CHJGlobalFun::SplitStrToVector(strValue, (QUERY_INI_SPLITER), vecAllColumnIDs);

	QString strUserColumnIDs  = "";

	// ����λ���ֶ�
	for(size_t i = 0; i < m_vecColumnIndexs.size(); i++)
	{
		int iPos = m_vecColumnIndexs.at(i);

		// ���һ���ֶ�ID
		strUserColumnIDs += vecAllColumnIDs.at(iPos) + (QUERY_INI_SPLITER);
	}

	// ����
	m_almUserColumnIDs.clear();
	m_almUserColumnIDs.Parse(CHJGlobalFun::qstr2str(strUserColumnIDs));
}

void CHJQueryBase::ClearList()
{
	// ���list����
	m_tableModle->clear();

	m_tableModle->columnCount();
	// ��ȡ�еĸ���
	int nColumnCount = m_tableModle->columnCount();//m_list->verticalHeader()->count();//.GetHeaderCtrl()->GetItemCount();
	// �����
	m_tableModle->removeColumns(0, nColumnCount);

}

bool CHJQueryBase::Query( const string &strQueryTag, QVector< pair<QString,QString> > & vecPara, const int &iPageNum/*ÿҳ������*/, const int &iCurPage/*��ǰ�����ҳ��*/, Req6002 &stReq6002, Rsp6002 &stRsp6002 )
{
	HEADER_RSP stHeaderRsp;

	stReq6002.login_branch_id = g_HeaderReq.branch_id;
	stReq6002.login_teller_id = CHJGlobalFun::qstr2str(g_Global.m_strUserID);
	stReq6002.oper_flag       = 1;  //����
	stReq6002.paginal_num     = iPageNum;  //��ҳ��
	stReq6002.curr_page       = iCurPage;   //��ǰҳ��
	stReq6002.query_id        = strQueryTag; //��ѯ����
	stReq6002.alm_view_field  = m_almUserColumnIDs;

	g_HeaderReq.SetExchCode("6002");
	g_HeaderReq.SetSeqNo(g_SeqNo ++);

	if ( 0 != g_TraderCpMgr.Tran6002Handle(g_HeaderReq, stReq6002, stHeaderRsp, stRsp6002, vecPara, 20)) //����6002�����ز�ѯ��Ϣ
	{
		//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
		QMessageBox::information(nullptr, ("ϵͳ��ʾ"), (CONSTANT_CONNECT_SERVER_FAIL_TIPS));

		return false;
	}

	return true;
}

void CHJQueryBase::ShowQueryResult( const Req6002 &stReq6002, const Rsp6002 &stRsp6002 )
{
	if(stRsp6002.alm_result.size() == 0)
	{
		//AfxMessageBox(CONSTANT_QUERY_NO_RECORD);
		QMessageBox::information(nullptr, ("ϵͳ��ʾ"), (CONSTANT_QUERY_NO_RECORD));

		return;
	}
	size_t i;

	//���ݲ�ѯ���������������list�ؼ�
	for(i = 0; i < stRsp6002.alm_result.size(); i++) //�������ؽ��
	{  
		const ArrayListMsg &aMsg = stRsp6002.alm_result.GetValue(i); //��ȡ����ĵ�һ��������
		size_t count = m_almUserColumnIDs.size();  //aMsg.size();//��ȡÿ�����ݵ��ֶ���
		for(size_t j = 0; j < count; j++) //������е�������
		{
			string titleid  =  m_almUserColumnIDs.GetStringEx(j);//����ֶ�id
			QString value = CHJGlobalFun::str2qstr( aMsg.GetStringEx(j) );//����ֶ�ֵ
			if(titleid == "exch_date" || titleid == "bk_plat_date" || titleid == "stor_date")//����ʱ��
				value = CHJGlobalFun::FormatDate(value);
			else if(titleid == "market_id")//�����г�
				value = g_TraderCpMgr.GetMarketName(value);
			else if(titleid == "exch_code")//��������
				value = g_TraderCpMgr.GetExchName(value);
			else if(titleid == "offset_flag")//��ƽ��־
				value = g_TraderCpMgr.GetOffset_flagName(value);
			else if(titleid == "deli_flag")//���ձ�־��������
				value = g_TraderCpMgr.GetDeli_flagName(value);
			else if(titleid == "bs")//��������
				value = g_TraderCpMgr.GetBuySellName(value);
			else if(titleid == "entr_stat")//ί��״̬
				value = g_TraderCpMgr.GetEntr_statName(value);
			else if(titleid == "cancel_flag")//������־
				value = g_TraderCpMgr.GetCancel_flagName(value);
			else if(titleid == "access_way")//��������
				value = g_TraderCpMgr.GetAccessWayName(value);
			else if(titleid == "check_stat1" || titleid == "check_stat2")//����״̬
				value = g_TraderCpMgr.GetCheck_staName(value);
			else if(titleid == "in_account_flag")//�Ƿ�ɹ�
				value = g_TraderCpMgr.GetIn_account_flagName(value);
			else if(titleid == "long_short")//�ֲַ���
				value = g_TraderCpMgr.GetLongShortName(value);
			else if(titleid == "e_term_type" || titleid == "c_term_type" || titleid == "term_type" || titleid == "o_term_type")//ί������,��������,������Դ
				value = g_TraderCpMgr.GetTerm_typeName(value);
			else if(/*titleid == "market_id" || */titleid == "accept_time" || titleid == "e_exch_time" || titleid == "c_exch_time" ||titleid == "exch_time" ||titleid == "stor_time")//����ʱ��
				value = CHJGlobalFun::FormatTime(value);
			else if(IsFloatTitle(titleid,stReq6002.query_id))//ί�м۸�
				value = CHJGlobalFun::FormatFloat(value);

			if(j == 0)
			{
				//m_list.InsertItem(i, value.c_str()); //����ÿһ�еĵ�һ��

				m_tableModle->insertRow(i);
				m_tableModle->setItem(i, 0, new QStandardItem(value));
			}
			else
			{
				//m_list.SetItemText(i, j, value.c_str()); //��list�ؼ����������	
				m_tableModle->setItem(i, j, new QStandardItem(value));
			}
		}
	}

	QueryReserver(stReq6002, stRsp6002);
}

bool CHJQueryBase::IsFloatTitle( const string &strID, const string &sQueryID /*= ""*/ )
{
	if( sQueryID == "AcctFundHis" )
	{
		if( strID == "curr_can_use" || strID == "last_can_use" || strID == "curr_can_get")
		{
			return true;
		}
	}

	const int iCount = 53;
	/*
	ȥ��last_long_froz,last_can_use,curr_can_use,curr_can_get
    modify by xrs 20130204 ���diff_storage����������������unclea r_diff��δ���������̣������ֶΣ��ڽ���ͨ���Ի���չʾΪ-.9����ʽ
	*/
	string title[iCount] = {
		"entr_price", "match_price", "exch_bal", "exch_fare", "margin", "long_open_avg_price", "short_open_avg_price", "long_posi_avg_price", "short_posi_avg_price", "last_settle_price", 
		"day_settle_price", "storage_cost", "last_bal", "curr_bal", "last_margin", "last_reserve", "out_bal","in_bal","real_buy","real_sell",
		"real_reserve","real_margin","base_margin","last_base_margin","deli_prepare","last_deli_prepare","deli_margin","last_deli_margin","real_exch_fare","other_fare",
		"pay_breach","take_breach","cov_surplus","mark_surplus","float_surplus","day_long_froz ","last_forward_froz","day_forward_froz","inte_integral","puni_integral",
		"wait_incr_inte","wait_incr_inte_tax","day_incr_inte","day_incr_inte_tax","last_take_margin","day_take_margin","last_stor_fare_froz", "day_stor_fare_froz", "stor_price", "price", 
		"fee_value",    "diff_storage", "unclear_diff" };//
	// "last_can_use","curr_can_use","curr_can_get",

	for(int i = 0; i < iCount; i++)
	{
		if(title[i] == strID)
		{
			return true;
		}
	}
	return false;
}

void CHJQueryBase::OnBtnSetshowcolumn(QString strNodeDate /*= ""*/)
{
// 	CHJSetColumnDlg dlg;
// 	dlg.SetFileName(GetQueryID().c_str());
	//COption dlg(strNodeDate);
	//if(dlg.DoModal() == IDOK)
	{
// 		ClearList();
// 
// 		LoadList();
	}
}
/*
��ʼ����Լ����
marketidĬ��Ϊ�գ�Ϊ�յ�ʱ��ȡȫ��������ȡ��Ӧmarketid��Ʒ��
marketid 00Ϊ  01Ϊ 02Ϊ
*/
void CHJQueryBase::IniProdCode(QComboBox& comb,string marketid )
{
	string str;
	QString cstr;

	comb.clear();
	comb.addItem( (""));
	for( size_t i = 0; i < g_TraderCpMgr.m_vProdCode.size(); i++)
	{
		const ProdCodeInfo &prodecode = g_TraderCpMgr.m_vProdCode.at(i);
		bool add = true;
		if(marketid != "")//�����Ϊ�գ������������ȡ
		{
			if (prodecode.market_id == CHJGlobalFun::str2qstr(marketid))
				add = true;
			else
				add = false;
		}

		if(add)//�����Ҫ���
		{
			if( prodecode.active_flag == "1" )
			{
				//str  = CHJGlobalFun::qstr2str(prodecode.prod_code);
				cstr = prodecode.prod_code;
				comb.addItem(cstr);
			}
		}
	}
}
// ��ȡ��Լ�����Ӧ��id�������б��ֵ������Ҫ��ȡ�ģ���ֱ��ȡֵ����
string CHJQueryBase::GetProdCode(QComboBox& comb)
{
	int index;
	QString cstr;

	index = comb.currentIndex();
	if(index < 0)//���ѡ��Ϊ�գ��򷵻ؿ�ֵ
		return "";


	return CHJGlobalFun::qstr2str(comb.itemText(index));
}

// ��ʼ����������
void CHJQueryBase::IniExchCode(QComboBox& comb)
{
	comb.clear();

	comb.insertItem( 0, "");
    // mod by Jerry Lee, ����Զ�ڿ���ֺ�Զ�ڿ��ղ�
    int n = 1;
	for(size_t i = 0; i < g_TraderCpMgr.m_vExchCode.size(); i++)
	{
        if(g_TraderCpMgr.m_vExchCode.at(i).code_id != CONSTANT_EXCH_CODE_FORWARD_LONG
            && g_TraderCpMgr.m_vExchCode.at(i).code_id != CONSTANT_EXCH_CODE_FORWARD_SHORT)
        {
            //comb.InsertString(n, g_TraderCpMgr.m_vExchCode.at(i).code_desc.c_str());

			comb.insertItem(0, g_TraderCpMgr.m_vExchCode.at(i).code_desc);

            n++;        
        }


	}
}

// ��ȡ��������
QString CHJQueryBase::GetExchCode(QComboBox& comb)
{
	int iPos;
	QString cstr;
	//��õ�ǰѡ����
	iPos = comb.currentIndex();//.GetCurSel();
	if(iPos < 1)
		return "";
	
	QString str = comb.itemText(iPos);
	//����vec����ø����Ӧ��idf
	for(size_t i = 0; i < g_TraderCpMgr.m_vExchCode.size(); i++)
	{
		if(g_TraderCpMgr.m_vExchCode.at(i).code_desc == str)
			return g_TraderCpMgr.m_vExchCode.at(i).code_id;
	}

	return "";
}

// ��ʼ����ƽ��־
void CHJQueryBase::IniOffsetFlag(QComboBox& comb)
{
	comb.clear();

	comb.insertItem(0, "");
	for(size_t i = 0; i < g_TraderCpMgr.m_vOffsetFlag.size(); i++)
	{
		comb.insertItem(i+1, g_TraderCpMgr.m_vOffsetFlag.at(i).code_desc);
	}
}
// ��ȡ��ƽ��־
string CHJQueryBase::GetOffsetFlag(QComboBox& comb)
{
	QString text = "";
	int index = comb.currentIndex();
	if(index > 0)
		return CHJGlobalFun::qstr2str(g_TraderCpMgr.m_vOffsetFlag.at(index-1).code_id);
	else//���ûѡ����ѡ�е�һ��
		return "";

}
// ��ʼ���ֲַ���
void CHJQueryBase::IniLongShort(QComboBox& comb)
{
	comb.clear();

	comb.insertItem(0, "");
	for(size_t i = 0; i < g_TraderCpMgr.m_vLongShort.size(); i++)
	{
		//QString cstr = g_TraderCpMgr.m_vLongShort.at(i).code_desc.c_str();
		comb.insertItem(i+1, g_TraderCpMgr.m_vLongShort.at(i).code_desc);
	}
}

// ��ȡ�ֲַ���
string CHJQueryBase::GetLongShort(QComboBox& comb)
{
	int index = comb.currentIndex();
	if(index < 1)//���ûѡ����ѡ�е�һ��
		return "";
	else
		return CHJGlobalFun::qstr2str(g_TraderCpMgr.m_vLongShort.at(index-1).code_id);
}
// ��ʼ����ȡ����
void  CHJQueryBase::IniAccessWay(QComboBox& comb)
{
	comb.clear();

	comb.insertItem(0, "");
	for(size_t i = 0; i < g_TraderCpMgr.m_vAccessWay.size(); i++)
	{
		comb.insertItem(i+1, g_TraderCpMgr.m_vAccessWay.at(i).code_desc);
	}
}
// ��ȡ��ȡ����
string  CHJQueryBase::GetAccessWay(QComboBox& comb)
{
	int index = comb.currentIndex();
	if(index < 1)//���ûѡ����ѡ�е�һ��
		return "";
	else
		return CHJGlobalFun::qstr2str(g_TraderCpMgr.m_vAccessWay.at(index-1).code_id);
}
// ��ʼ������Ʒ�ִ���
void  CHJQueryBase::IniVarietyId(QComboBox& comb)
{
	comb.clear();

	comb.insertItem(0, "");
    int n = 1;
	for(size_t i = 0; i < g_TraderCpMgr.m_vVariety.size(); i++)
	{
		// ���ݽ���ͨ���Ե�Ҫ��ȥ����Ʒ��
		if( g_TraderCpMgr.m_vVariety.at(i).name != "Ag99.9" )
		{
			comb.insertItem(n, g_TraderCpMgr.m_vVariety.at(i).name);
            n++;
		}
	}
}
// ��ȡ����Ʒ�ִ���
string  CHJQueryBase::GetVarietyId(QComboBox& comb)
{
	int iPos;
	QString cstr;

	//��õ�ǰѡ����
	iPos=comb.currentIndex();

	//���ûѡ�л���ѡ���
	if(iPos<1)
		return "";


	QString str = comb.itemText(iPos);
	//����vec����ø����Ӧ��id
	for(size_t i=0; i < g_TraderCpMgr.m_vVariety.size(); i++)
	{
		if(g_TraderCpMgr.m_vVariety.at(i).name == str)
			return CHJGlobalFun::qstr2str(g_TraderCpMgr.m_vVariety.at(i).variety_id);
	}

	return "";
}
// ��ʼ�����ô��� ע����ǰ�������һ�����У���ȡ���ݵ�ʱ��Ҫ����ƶ�һλ��
void  CHJQueryBase::IniFeeCode(QComboBox& comb)
{
	comb.clear();

	comb.insertItem(0, "");
	for(size_t i = 0; i < g_TraderCpMgr.m_vFeeCode.size(); i++)
	{
		//QString cstr = g_TraderCpMgr.m_vFeeCode.at(i).code_desc.c_str();
		comb.insertItem(i+1, g_TraderCpMgr.m_vFeeCode.at(i).code_desc);
	}
}

// ��ȡ���ô���
string  CHJQueryBase::GetFeeCode(QComboBox& comb)
{
	string str = "";
	int index = comb.currentIndex();
	if(index > 0)
	{
		str = CHJGlobalFun::qstr2str(g_TraderCpMgr.m_vFeeCode.at(index-1).code_id);
	}
	return str;
}

// ��ȡ�ӷ��ô���
string  CHJQueryBase::GetSubFeeCode(QComboBox& comb)
{
	QString str2;
	QString cstr;

	int index=comb.currentIndex();

	if(index>0)
	{
		QString str1 = comb.itemText(index);
		for(size_t i=0;i<g_TraderCpMgr.m_vSubFeeCode.size();i++)
		{
			str2=g_TraderCpMgr.m_vSubFeeCode.at((i)).code_desc;
			if(str1==str2)
				return CHJGlobalFun::qstr2str(g_TraderCpMgr.m_vSubFeeCode.at((i)).code_id);	
		}
	}

	return "";
}

//���ô���仯ʱ�����ĺ�������ȡ��ǰ���ô����µ��ӷ��ô���
void CHJQueryBase::FeeCodeSelectChange( QComboBox& comb1,QComboBox& comb2 )
{
	int index;
	QString str1;
	QString str2;

	//����ӷ��ô����б�
	comb2.clear();
	//��÷��ô��뵱ǰѡ��Ķ�Ӧid
	index=comb1.currentIndex();
	if(index<1)//���ѡ��Ϊ��һ�����ûѡ��
		return;
	str1=g_TraderCpMgr.m_vFeeCode.at(index-1).code_id;
	// ���ݽ���ͨ��Ҫ��ȥ�������ô��롱Ϊ�������ѡ�ʱ������ʾ����Ա���Լ��������������ӷ��ô���
	if( str1 != "06" )
	{
		//���ӷ��ô����б����һ������
		comb2.addItem("");
		//�����ӷ��ô��룬���
		for(size_t i=0;i<g_TraderCpMgr.m_vSubFeeCode.size();i++)
		{
			str2=g_TraderCpMgr.m_vSubFeeCode.at((i)).code_id;
			str2=str2.mid(0,2);
			if(str2==str1)//����ִ�
				comb2.addItem(g_TraderCpMgr.m_vSubFeeCode.at((i)).code_desc);
		}
	}
}

void CHJQueryBase::OnSelchangeComboNum()
{
	m_cmbPage->setCurrentIndex(0);
	OnButtonQuery();
}

void CHJQueryBase::OnSelchangeComboPage()
{
	OnButtonQuery();
}
/*
���ܣ���vector(v)���һ������ΪstrtitleֵΪstrvalue��pare(p)
v vector
p ������
strtitile ����
strvalue �����ֵ
*/
void CHJQueryBase::PairAdd(QVector< pair<QString,QString> > & v,QString strtitle,QString strvalue)
{
	pair<QString,QString> p;
	p.first=strtitle;
	p.second=strvalue;
	v.push_back(p);
}

#include "Mgr/CodeTableMgr.h"
#include "Mgr/ProdCodeMgr.h"
void CHJQueryBase::ProdCodeSelectChange( QComboBox& comb1,QComboBox& comb2 )
{
	// ��ս��������б�
	comb2.clear();

	// ��ȡ��ǰѡ��Ʒ�ֵ��г�
	MarketType eMarket = e_mk_Others;
	int iSel = comb1.currentIndex();
	if( iSel > 0 )
	{
		//QString cstr;
		//comb1.GetLBText(iSel,cstr);
		QString str = comb1.itemText(iSel);

		const ProdCodeInfo* pInfo = g_ProdCodeMgr.GetProdeCode(str);
		eMarket = pInfo != NULL ? ::GetMarketType(pInfo->market_id) : e_mk_Others;
	}

	// ��ȡ��ǰ�г��µ����н������� 
	QVector<const CodeValue*> vecCode;
	g_CodeTableMgr.GetExchTypeName( vecCode, eMarket );

	// ���ؽ��׷�ʽ�б�
	comb2.insertItem( 0, "" ); // �����������б����һ������
	for( size_t j = 0; j < vecCode.size(); j++ )
		comb2.insertItem( j+1, vecCode.at(j)->code_desc );
}

//
void CHJQueryBase::OnOutputToExce(QString csSheetName)
{
	// ��ȡ�����еĶ��뷽ʽ
	vector<int>  vecAlign;
	GetUserAlign(vecAlign);

	// ��ȡģ��·��
	QString sPath = QString("%1Trade\\report.xlsx").arg(g_Global.GetSystemPath());

	CMyExcel myExcel;
	myExcel.WriteListDataToExcel(*m_list, csSheetName, csSheetName, vecAlign, sPath);
}

void CHJQueryBase::GetUserAlign( vector<int> & vecAlign )
{
	// ��ȡ�����ļ���·��
	string strQueryID = GetQueryID(); // �Ӹ����ȡ��ѯID���Ӷ���ȡ�����ļ����ļ���
	QString   strPath = QString("%1QueryConfig\\%2.ini").arg(g_Global.GetSystemPath()).arg(CHJGlobalFun::str2qstr(strQueryID));

	QString strValue;
	size_t i;
	QVector<int>     vecAllAligns;

	//char buf[500] = {0};

	// ��ȡȫ���ֶζ��䷽ʽ�����ָvector
	//::GetPrivateProfileString("Info", "AllColumnAligns", "", buf, sizeof(buf), strPath);
	//strValue = buf;

	App::GetPriProfileString(strPath, ("Info"), ("AllColumnAligns"), strValue);
	CHJGlobalFun::SplitStrToVector(strValue, (QUERY_INI_SPLITER), vecAllAligns);

	// ����λ���ֶΣ���ȡ�û�ѡ���ÿһ�еĶ�Ӧ����Ϣ���п����뷽ʽ��
	for(i = 0; i < m_vecColumnIndexs.size(); i++)
	{
		// ���ض��䷽ʽ
		vecAlign.push_back(vecAllAligns.at(m_vecColumnIndexs.at(i)));
	}
}

void CHJQueryBase::QueryReserver( const Req6002 &stReq6002, const Rsp6002 &stRsp6002 )
{
}
