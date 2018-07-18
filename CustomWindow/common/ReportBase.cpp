
#include "ReportBase.h"
#include "HJGlobalFun.h"
#include "Global.h"
#include <QPainter>
#include <QtWidgets/QApplication>
#include <QFontMetrics>

#pragma execution_character_set("utf-8")

QReportBase::QReportBase( void )
{
	m_xRate = m_yRate = 1;
	m_xRate = (float)g_Global.m_ndpiX/DEFAULT_DPI_X;
	m_yRate = (float)g_Global.m_ndpiY/DEFAULT_DPI_Y;
	m_iMaxPage = 1;

	m_iStorage = 0;
	m_iForward = 0;
	m_iDefer = 0;
	m_iSurplus = 0;
	m_iMatchFlow = 0;
	m_iFundInOutFlow = 0;
	m_nPageHeight  = 2339;		
	m_nPageWidth   = 1654;	
}

QReportBase::~QReportBase( void )
{

}

/* ���ݳ�ʼ��******************************************************************************/
/*��ʼ���ͻ���Ϣ*/
void QReportBase::IniRisk( Rsp6007 &rsp )
{
	if(rsp.htm_AcctSettleRisk.size() != 0)
	{
		RptDataInfo stru;
		stru.isLeftAli = true;

		QString strTitle[6] = {"���ױ���", "�ͻ�����",  "�������",  "�����˺�",   "���ն�",     "׷���ʽ�"};
		string  strConID[6] = {"acct_no",  "cust_abbr", "branch_id", "account_no", "risk_index", "need_bal"};

		for(int i = 0; i < 6; i++)
		{
			stru.strTitle = strTitle[i];

			if(i != 5)
			{
				stru.strContent = CHJGlobalFun::str2qstr(rsp.htm_AcctSettleRisk.GetString(0, strConID[i]));
			}
			else //׷���ʽ������⴦��
			{
				stru.isLeftAli = false;
				stru.strContent = CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleRisk.GetString(0, strConID[i])));
			}

			m_vecRisk.push_back(stru);
		}

		//m_vecRisk.at(2).strContent = "���ɹ���������Ӫҵ�����Ժú�";
		int iTry = 2;
		int iAdjust;
		if(m_vecRisk.at(2).strContent.length() > 24)
			iAdjust = (m_vecRisk.at(2).strContent.length()-24) * iTry;
		else
			iAdjust = 0;

		// add by xiao
		int    iColumnPer[3] = { 33, 33 - iAdjust, 34 + iAdjust}; // { 33, 27, 40};
		Table1Info info;
		for(int j = 0; j < 3; j++)
		{
			info.iColumnPercent = iColumnPer[j];
			m_vecRiskColumn.push_back(info);
		}
	}
}

/*��ʼ���ʽ���Ϣ*/
void QReportBase::IniFund( Rsp6007 &rsp )
{
	if(rsp.htm_AcctSettleFund.size() != 0)
	{
		RptDataInfo stru;
		stru.isLeftAli = false;

		int iColIDPos;
		const int iCount = 14;
		QString sTitle[iCount];
		if(m_iType == E_DAY)
		{
			sTitle[0] = "�������"; sTitle[1] = "���ڳֱֲ�֤��"; sTitle[2] = "���֤��"; sTitle[3] = "�������"; sTitle[4] = "��̱�����"; sTitle[5] = "������֤��"; sTitle[6] = "���ڿ���";
			sTitle[7] = "����׼����"; sTitle[8] = "���ɶ���"; sTitle[9] = "�����֤��"; sTitle[10] = "�ִ���֤��"; sTitle[11] = "���ڳֱֲ�֤��"; sTitle[12] = "���������֤��"; sTitle[13] = "���ڲִ���֤��";
		}
		else
		{
			sTitle[0] = "�������"; sTitle[1] = "�������"; sTitle[2] = "���ڿ���"; sTitle[3] = "���ױ�֤��"; sTitle[4] = "��̱�����"; sTitle[5] = "����׼����"; sTitle[6] = "���֤��";
			sTitle[7] = "������֤��"; sTitle[8] = "���ɶ���"; sTitle[9] = "���ڳֱֲ�֤��"; sTitle[10] = "���������֤��"; sTitle[11] = "���ڲִ���֤��"; sTitle[12] = "�����֤��"; sTitle[13] = "�ִ���֤��";
		}

		string  strConID[14] = {"last_bal",         "margin",              "deli_margin", 
			"curr_bal",         "reserve",             "base_margin",
			"curr_can_use",     "deli_prepare",        "long_froz",
			"take_margin",      "stor_fare_froz",      "last_margin",
			"last_take_margin", "last_stor_fare_froz"};

		int iChange[14] = {0, 3, 6, 1, 4, 7, 2, 5, 8, 11, 12, 13, 9, 10};
		
        /*
		QString strTitle[14] = {"�������",       "���ڳֱֲ�֤��",     "���֤��",
			"�������",       "��̱�����",     "������֤��",
			"���ڿ���",       "����׼����",     "���ɶ���",
			"�����֤��",     "�ִ���֤��",     "���ڳֱֲ�֤��",
			"���������֤��", "���ڲִ���֤��"};
		*/

		for(int i = 0; i < 14; i++)
		{
			stru.strTitle   = sTitle[i];
			//stru.strContent = CHJGlobalFun::FormatFloat(rsp.htm_AcctSettleFund.GetString(0, strConID[i])).c_str();
			iColIDPos = m_iType == E_DAY ? i : iChange[i] ;
			stru.strContent = CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleFund.GetString(0, strConID[iColIDPos])));

			m_vecFund.push_back(stru);
		}

		//��ӿո�
		stru.strTitle   = "";
		stru.strContent = "";
		m_vecFund.push_back(stru);
	}
	else
	{
		return;
	}
}
/*��ʼ���ʽ�����ϸ*/
void QReportBase::IniFundDetail( Rsp6007 &rsp )
{
	if(rsp.htm_AcctSettleFundDetail.size() != 0)
	{
		double fTotalGaCha = 0.00;
		RptDataInfo stru;
		stru.isLeftAli = false;

		QString strTitle[21] = {"������",   "ת�����",   "������",
			"�������",   "����ӯ��",   "����������",
			"����������", "��Ѻ�ǼǷ�", "���ǼǷ�",
			"��̽��",   "Ʒ������ˮ", "��������ˮ",
			"Ʒ������ˮ", "�������ɽ�", "��������",
			"�ִ���",     "�˱���",     "���ڷ�",
			"���ӷ�",     "ΥԼ��",     "������Ϣ"};
		string strConID[21]  = {"in_bal",      "out_bal",      "buy_bal",
			"sell_bal",    "surplus",      "exch_fare",
			"deli_fare",   "impawn_fare",  "lend_fare",
			"diff_bal",    "variety_agio", "item_agio",
			"brand_agio",  "ag_late_fare", "ag_amerce",
			"storage_fee", "trans_fee",    "over_due_fee",
			"defer_fee",   "breach_fee",   "incr_inte"};
		for(int i = 0; i < 21; i++)
		{
			stru.strTitle   = strTitle[i];
			stru.strContent = CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleFundDetail.GetString(0, strConID[i])));
			m_vecFundDetail.push_back(stru);

			QString strContent = CHJGlobalFun::str2qstr(rsp.htm_AcctSettleFundDetail.GetString(0, strConID[i]));

			fTotalGaCha += strContent.toDouble();
		}

		QString strTemp;
		//strTemp.Format("%.2f", fTotalGaCha);
		strTemp.number(fTotalGaCha, 'f', 2);
		//string str(strTemp.GetBuffer()); //QString to string
		m_strGaCha = strTemp;
	}
	else
	{
		return;
	}
}

/*��ʼ�������Ϣ*/
void QReportBase::IniStorage( Rsp6007 &rsp )
{
	QString cstrTitle[11] = {"����Ʒ��",  "���ڿ��","���ÿ��",    "������",    "��Ѻ���",  "������","��������","��������","���ڴ���","�������","�������"};
	string   strConID[11] = {"variety_id","last_amt","curr_can_use","app_froz_amt","impawn_amt","froz_amt","buy_amt", "sell_amt","in_amt",  "out_amt", "curr_amt"};

	//��ӱ���
	int i;
	for(i = 0; i < 11; i++)
	{
		m_arrayStorage.append(std::move(cstrTitle[i]));
	}
	//�������
	for(i = 0; i < rsp.htm_AcctSettleStorage.size(); i++)
	{
		for(int j = 0; j < 11; j++)
		{
			m_arrayStorage.append(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleStorage.GetString(i, strConID[j])));
		}
	}
	//�������������������⣩
	m_iStorage = rsp.htm_AcctSettleStorage.size();

	RptColumnInfo stru;
	for(i = 0; i < 11; i++)
	{
		stru.bReturn = false;
		stru.iReturnBegin = 0;
		stru.iColumnPercent = 0;

		m_vStorage.push_back(stru);
	}
}  

/*��*/
void QReportBase::IniForward( Rsp6007 &rsp )
{

}
/*���ڳֲ���Ϣ*/
void QReportBase::IniDefer( Rsp6007 &rsp )
{
	QString cstrTitle[10] = {"��Լ����", "�ֲַ���",  "���ڳֲ�","���ڿ���","����ƽ��","���ڽ���","�����ֽ���",  "���ڳֲ���","���־���",  "�ֲ־���"};
	string   strConID[10] = {"prod_code","long_short","last_amt","open_amt","cov_amt", "deli_amt","mid_deli_amt","curr_amt",  "open_price","hold_price"};
	int    iColumnPer[10] = { 12,         9,          9,        9,        9,        9,        9,            9,          13,          13};

	//��ӱ���
	int i;
	for(i = 0; i < 10; i++)
	{
		m_arrayDefer.append(std::move(cstrTitle[i]));
	}
	//�������
	for(i = 0; i < rsp.htm_AcctSettleDefer.size(); i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(j < 8)
			{
				m_arrayDefer.append(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleDefer.GetString(i, strConID[j])));
			}
			else
			{
				m_arrayDefer.append(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleDefer.GetString(i, strConID[j]))));
			}
		}
	}
	//�������������������⣩
	m_iDefer = rsp.htm_AcctSettleDefer.size();

	RptColumnInfo stru;
	for(i = 0; i < 10; i++)
	{
		if(i == 7 || i == 6)
		{
			stru.bReturn = true;
			stru.iReturnBegin = 8;
		}
		else
		{
			stru.bReturn = false;
			stru.iReturnBegin = 0;
		}
		stru.iColumnPercent = iColumnPer[i];
		m_vDefer.push_back(stru);
	}
}

/*����ӯ����Ϣ*/
void QReportBase::IniSurplus( Rsp6007 &rsp )
{
	const int iCount = 3;
	QString cstrTitle[iCount] = {"��Լ����", "���ڽ����",  "����ӯ��"};
	string   strConID[iCount] = {"prod_code","settle_price","market_surplus"};
	if(m_iType == E_MONTH)
	{
		cstrTitle[1] = "��ĩ�����";
	}
	
	//��ӱ���
	int i;
	for(i = 0; i < iCount; i++)
	{
		m_arraySurplus.append(cstrTitle[i]);
	}
	//�������
	for(i = 0; i < rsp.htm_AcctSettleSurplus.size(); i++)
	{
		for(int j = 0; j < iCount; j++)
		{
			if( j == 0) //��һ�У���Լ���룩���ø�ʽ��
			{
				m_arraySurplus.append(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleSurplus.GetString(i, strConID[j])));
			}
			else
			{
				m_arraySurplus.append(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleSurplus.GetString(i, strConID[j]))));
			}
		}
	}
	//�������������������⣩
	m_iSurplus = rsp.htm_AcctSettleSurplus.size();

	RptColumnInfo stru;
	for(i = 0; i < iCount; i++)
	{
		stru.bReturn = false;
		stru.iReturnBegin = 0;
		stru.iColumnPercent = 0;

		m_vSurplus.push_back(stru);
	}
}

/*�ɽ���ˮ*/
void QReportBase::IniMatchFlow( Rsp6007 &rsp )
{
	QString cstrTitle[8] = {"�ɽ����","������",  "��Լ����", "���׷���", "�ɽ��۸�",   "�ɽ�����", "�ɽ����", "������"};
	string   strConID[8] = {"match_no","order_no","prod_code","exch_code","match_price","match_amt","match_bal","exch_fare"};
	int    iColumnPer[8] = { 19,        12,        10,         14,         10,           7,         16,         12};
	//��ӱ���
	int i;
	for(i = 0; i < 8; i++)
	{
		m_arrayMatchFlow.append(cstrTitle[i]);
	}
	//�������
	for(i = 0; i < rsp.htm_AcctSettleMatchFlow.size(); i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(j == 6 || j == 7 || j == 4)
			{
				m_arrayMatchFlow.append(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleMatchFlow.GetString(i, strConID[j]))));
			}
			else
			{
				m_arrayMatchFlow.append(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleMatchFlow.GetString(i, strConID[j])));
			}
		}
	}
	//�������������������⣩
	m_iMatchFlow = rsp.htm_AcctSettleMatchFlow.size();
    
	RptColumnInfo stru;
	for(i = 0; i < 8; i++)
	{
		if(i == 5)
		{
			stru.bReturn = true;
			stru.iReturnBegin = 4;
		}
		else
		{
			stru.bReturn = false;
			stru.iReturnBegin = 0;
		}
		stru.iColumnPercent = iColumnPer[i];
		m_vMatchFlow.push_back(stru);
	}
}
/*�������ˮ*/
void QReportBase::IniFundInOutFlow( Rsp6007 &rsp )
{
	QString cstrTitle[6] = {"��������", "������ˮ��","��ȡ����",  "�������","��������","������ˮ��"};
	string   strConID[6] = {"exch_date","serial_no", "access_way","exch_bal","bk_date", "bk_seq_no"};
	int    iColumnPer[6] = { 15,         15,          15,          15,        15,        25};
	//��ӱ���
	int i;
	for(i = 0; i < 6; i++)
	{
		m_arrayFundInOutFlow.append(cstrTitle[i]);
	}
	//�������
	for(i = 0; i < rsp.htm_AcctSettleFundInOutFlow.size(); i++)
	{
		for(int j = 0; j < 6; j++)
		{
			if(j == 3)
			{
				m_arrayFundInOutFlow.append(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleFundInOutFlow.GetString(i, strConID[j]))));
			}
			else
			{
				m_arrayFundInOutFlow.append(CHJGlobalFun::str2qstr(rsp.htm_AcctSettleFundInOutFlow.GetString(i, strConID[j])));
			}
		}
	}
	//�������������������⣩
	m_iFundInOutFlow = rsp.htm_AcctSettleFundInOutFlow.size();

	RptColumnInfo stru;
	for(i = 0; i < 6; i++)
	{
		stru.bReturn = false;
		stru.iReturnBegin = 0;
		
		stru.iColumnPercent = iColumnPer[i];
		m_vFundInOutFlow.push_back(stru);
	}
}

void QReportBase::IniAllData( Rsp6007 &rsp )
{
	IniRisk(rsp);/*��ʼ���ͻ���Ϣ*/
	IniFund(rsp);/*��ʼ���ʽ���Ϣ*/
	IniFundDetail(rsp);/*��ʼ���ʽ�����ϸ*/
	IniStorage(rsp);/*��ʼ�������Ϣ*/
	IniForward(rsp);/**/
	IniDefer(rsp);/*���ڳֲ���Ϣ*/
	IniSurplus(rsp);/*����ӯ����Ϣ*/
	IniMatchFlow(rsp);/*�ɽ���ˮ*/
	IniFundInOutFlow(rsp);/*�������ˮ*/
}
/* ���ݳ�ʼ��******************************************************************************/
//
void QReportBase::Draw( QPainter* pDC , PrintInfo* pInfo)
{
	// ��������
	QFont oldfont  = qApp->font();
	QFont *newfont = nullptr;
	newfont = new QFont("����", 10);

	pDC->setFont(*newfont);
	if(m_iType == E_DAY || m_iType == E_MONTH) // ������սᵥ��ӡ�����½ᵥ��ӡ
	{
		int iLeftTopy=0;  // ������Ͻǵ�yֵ�����ֱ����

		// �����ǰҳ�ǵ�һҳ
		if(pInfo->m_nCurPage == 1)
		{
			// �����ҳ��Ϊ1�����ӡȫ��
			//if(m_printInfo.GetMaxPage() == 1 )
			if(pInfo->m_MaxPage == 1) // modify by xiao�����m_printInfo.GetMaxPage()���ش��������
			{
				DrawPart1(iLeftTopy, pDC);
				DrawPart2(iLeftTopy, pDC);
			}
			else // �����ҳ����2�����ӡ��һ����
			{
				DrawPart1(iLeftTopy, pDC);
			}
		}
		else // �����ǰ�ǵڶ�ҳ�����ӡ�ڶ�����
		{
			iLeftTopy = GetY(TABLE_PAGE2_BEGIN_Y);
			DrawPart2(iLeftTopy, pDC);
		}
	}
	else if(m_iType == E_TIHUO) // ������������ӡ
	{
		DrawTiHuo(pDC);
	}
	else
	{
	}

	// д��ҳ����Ϣ
	WritePage(pDC, pInfo);

	pDC->setFont(oldfont);// > SelectObject(pOldFont);
}
//�����ܵ�ҳ����
void QReportBase::SetPage(PrintInfo* pInfo, int& nHeight)
{
	int iTemp = TABLE_LINE_HEIGHT;
	nHeight  = GetY(TABLE_BEGIN_Y + (CUS_INFO_LINE_COUNT + FUN_INFO_LINE_COUNT + FUN_DETAIL_LINE_COUNT + 1)*TABLE_LINE_HEIGHT);
	nHeight += GetY((TABLE_TITLE_HEIGHT + TABLE_TO_TITLE_DIS)*2); //�ʽ�����ϸ���ĵײ���yֵ

	//��������Ϣ��Ϊ��
	if(m_iStorage != 0)
	{
		//��ÿ����Ϣ���ĵײ���yֵ
		nHeight += GetY(TABLE_TO_TITLE_DIS + TABLE_TITLE_HEIGHT + TABLE2_TITLE_HEIGHT + TABLE_LINE_HEIGHT*m_iStorage);
	}

	//���
	if(m_iForward != 0)
	{

	}

	//������ڳֲ���Ϣ��Ϊ��
	if(m_iDefer != 0)
	{
		nHeight += GetY(TABLE_TO_TITLE_DIS + TABLE_TITLE_HEIGHT + TABLE2_TITLE_HEIGHT + TABLE_LINE_HEIGHT*m_iDefer);
	}

	//�������ӯ����Ϣ��Ϊ��
	if(m_iSurplus != 0)
	{
		nHeight += GetY(TABLE_TO_TITLE_DIS + TABLE_TITLE_HEIGHT + TABLE2_TITLE_HEIGHT + TABLE_LINE_HEIGHT*m_iSurplus);
	}

	//����ɽ���ˮ��Ϊ��
	if(m_iMatchFlow != 0)
	{
		nHeight += GetY(TABLE_TO_TITLE_DIS + TABLE_TITLE_HEIGHT + TABLE2_TITLE_HEIGHT + TABLE_LINE_HEIGHT*m_iMatchFlow);
	}

	//����������ˮ��Ϊ��
	if(m_iFundInOutFlow != 0)
	{
		nHeight += GetY(TABLE_TO_TITLE_DIS + TABLE_TITLE_HEIGHT + TABLE2_TITLE_HEIGHT + TABLE_LINE_HEIGHT*m_iFundInOutFlow);
	}

	// ����Ǵ�ӡģʽ��������Ҫ��ʾ�ĸ߶�����������ҳ
	if(m_eShowMode == E_PRINT && nHeight > (GetY(PAGE_BEGIN_Y-100)))
	{
		// ���Ҫ���Ƶı�����ײ����ڰ�ȫ���ڣ���ҳ
		pInfo->m_MaxPage = 2;//(2);
		m_iMaxPage = 2;
	}
	else
	{
		pInfo->m_MaxPage = 1;
		m_iMaxPage = 1;
	}
}
//
void QReportBase::DrawPart1(int &iLeftTopy, QPainter* pDC)
{
	//������
	DrawTitle(pDC);

	/*д��ͻ���Ϣ*/
	//iLeftTopy = DrawTable(pDC, GetY(TABLE_BEGIN_Y), CUS_INFO_LINE_COUNT,   TABLE1_LINE_TITLE_COUNT, GetX(CUS_INFO_COL_TITLE_WIDTH),   m_vecRisk, "�ͻ���Ϣ", "���:Ԫ");
	iLeftTopy = DrawTableEx(pDC, GetY(TABLE_BEGIN_Y), CUS_INFO_LINE_COUNT,   TABLE1_LINE_TITLE_COUNT, GetX(CUS_INFO_COL_TITLE_WIDTH),   m_vecRisk, "�ͻ���Ϣ", "���:Ԫ", m_vecRiskColumn);
	 
	/*д���ʽ���Ϣ*/
	if(m_vecFund.size() != 0)
	{
		iLeftTopy = DrawTable(pDC, iLeftTopy,     FUN_INFO_LINE_COUNT,   TABLE1_LINE_TITLE_COUNT, GetX(FUN_INFO_COL_TITLE_WIDTH),   m_vecFund, "�ʽ���Ϣ", "��λ:Ԫ");
	}

	/*д���ʽ�����ϸ*/
	if(m_vecFundDetail.size() != 0)
	{
		iLeftTopy = DrawTable(pDC, iLeftTopy,     FUN_DETAIL_LINE_COUNT, TABLE1_LINE_TITLE_COUNT, GetX(FUN_DETAIL_COL_TITLE_WIDTH), m_vecFundDetail, "�ʽ�����ϸ", "��λ:Ԫ");
		iLeftTopy = DrawFunDetail(pDC, iLeftTopy, "����", m_strGaCha);
	}

	/*д������Ϣ*/
	if(m_iStorage != 0)
	{
		iLeftTopy = DrawTable2(pDC, iLeftTopy, m_iStorage, STORE_INFO_COLUME_COUNT,   m_arrayStorage, "�����Ϣ",     "��λ:��",          m_vStorage, 1);
	}

	/*д�����ڳֲ���Ϣ*/
	if(m_iDefer != 0)
	{
		iLeftTopy = DrawTable2(pDC, iLeftTopy, m_iDefer,   CHICANG_INFO_COLUME_COUNT, m_arrayDefer,   "���ڳֲ���Ϣ", "����:��  ���:Ԫ", m_vDefer, 2, false);
	}
}

//
void QReportBase::DrawPart2(int &iLeftTopy, QPainter* pDC)
{
	/*д�뱾��ӯ����Ϣ*/
	if(m_iSurplus != 0)
	{
		iLeftTopy = DrawTable2(pDC, iLeftTopy, m_iSurplus, YINGKUI_INFO_COLUME_COUNT, m_arraySurplus, "����ӯ����Ϣ", "��λ:Ԫ",          m_vSurplus, 1);
	}

	/*д��ɽ���ˮ��Ϣ*/
	if(m_iMatchFlow != 0)
	{
		iLeftTopy = DrawTable2(pDC, iLeftTopy, m_iMatchFlow, MATCHFLOW_COLUME_COUNT, m_arrayMatchFlow, "�ɽ���ˮ", "����:��  ���:Ԫ",          m_vMatchFlow, 1, false);
	}

	/*д��������ˮ��Ϣ*/
	if(m_iFundInOutFlow != 0)
	{
		iLeftTopy = DrawTable2(pDC, iLeftTopy, m_iFundInOutFlow, FUNINOUTFLOW_COLUME_COUNT, m_arrayFundInOutFlow, "�������ˮ", "",          m_vFundInOutFlow, 1, false);
	}
}

//
//���սᵥ����
void QReportBase::DrawTitle(QPainter* pDC )
{
	QFont oldfont = qApp->font();
	QFont *font = new QFont("����", 20);
	//CFont *pOldFont;
	//CFont DataFont;
	//DataFont.CreatePointFont(200, "����", pDC); 
	//pOldFont = pDC->SelectObject(&DataFont);

	pDC->setFont(*font);
	pDC->drawText(GetX(TITLE_BEGIN_X), GetY(TITLE_BEGIN_Y), m_strTitle);
	//pDC->TextOut(GetX(TITLE_BEGIN_X), GetY(TITLE_BEGIN_Y), m_strTitle);

	//pDC->MoveTo();
	//pDC->LineTo();

	//pDC->SelectObject (pOldFont);
	pDC->setFont(oldfont);
	pDC->drawLine(GetX(LEFT_X), GetY(LINE_Y), GetX(RIGHT_X), GetY(LINE_Y));
}
/*
���սᵥ�ĵ�һ�ֱ��
iLeftTopY �滭������㣨�����Ͻǵ�y���꣩
iLineCount �������������˱�������
iTitleCount ��������
iTitleWid ���Ŀ��
vec װ�ر�������
strLTitle ������Ͻǵı���
strRTitle ������Ͻǵĵ�λ
*/
int QReportBase::DrawTable(QPainter* pDC, int iLeftTopY, int iLineCount, int iTitleCount, int iTitleWid, const vector<RptDataInfo> &vec, QString strLTitle, QString strRTitle)
{
	int x1,y1;
	int x2,y2;
	int i;
	int iContentWid;

	//������
	//QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
	//option.setWrapMode(QTextOption::WordWrap);

	y1 = iLeftTopY - GetY(TABLE_TITLE_HEIGHT);

	pDC->drawText(LEFT_X + TEXT_DISTANCE_X, y1, pDC->fontMetrics().width(strLTitle), pDC->fontMetrics().height(), Qt::AlignLeft, strLTitle);

	pDC->drawText(GetX(RIGHT_X - TEXT_DISTANCE_X)-pDC->fontMetrics().width(strRTitle), y1, pDC->fontMetrics().width(strRTitle), pDC->fontMetrics().height(), Qt::AlignLeft, strRTitle);


	//������table�ľ���
	x1 = GetX(LEFT_X);
	y1 = iLeftTopY;
	x2 = GetX(RIGHT_X);
	y2 = y1 + GetY(TABLE_LINE_HEIGHT)*iLineCount;
	//pDC->Rectangle(x1, y1, x2, y2); 
	pDC->drawRect(x1, y1,x2-x1, GetY(TABLE_LINE_HEIGHT)*iLineCount);
	//����
	for(i = 1; i < iLineCount; i++)
	{
		y1 += GetY(TABLE_LINE_HEIGHT);
		//pDC->MoveTo(GetX(LEFT_X), y1);
		//pDC->LineTo(GetX(RIGHT_X), y1);
		pDC->drawLine(GetX(LEFT_X), y1, GetX(RIGHT_X), y1);
	}

	//����
	x1 = GetX(LEFT_X);
	y1 = iLeftTopY; //ÿһ���������yֵ
	y2 = iLeftTopY + GetY(TABLE_LINE_HEIGHT)*iLineCount;//ÿһ���ߵ������yֵ
	iContentWid = GetX(TABLE_WIDTH)/iTitleCount - iTitleWid; //�����еĿ��
	for(i = 1; i < iTitleCount*2; i++)
	{
		if(i%2 == 1)
		{
			x1 += iTitleWid;
		}
		else
		{
			x1 += iContentWid;
		}

		//pDC->MoveTo(x1, y1);
		//pDC->LineTo(x1, y2);

		pDC->drawLine(x1, y1, x1, y2);
	}


	//д�����ݣ���������ݣ�
	for(i = 0; i < iLineCount*iTitleCount; i++)
	{
		if(i == 0)
		{
			x1 = GetX(LEFT_X);
			y1 = iLeftTopY;
		}
		else if(i%iTitleCount == 0) //�������һ��
		{
			x1  = GetX(LEFT_X);
			y1 += GetY(TABLE_LINE_HEIGHT);
		}
		else
		{
			x1 += GetX(TABLE_WIDTH)/iTitleCount;
		}
		QString str1 = vec.at(i).strTitle;
		//pDC->TextOut(x1 + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), vec.at(i).strTitle);
		pDC->drawText(x1 + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(vec.at(i).strTitle), pDC->fontMetrics().height(), Qt::AlignLeft, vec.at(i).strTitle);

		if(vec.at(i).isLeftAli)
		{
			//pDC->TextOut(x1 + iTitleWid + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), vec.at(i).strContent);	

			pDC->drawText(x1 + iTitleWid + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(vec.at(i).strContent), pDC->fontMetrics().height(), Qt::AlignLeft, vec.at(i).strContent);
		}
		else
		{
			//pDC->SetTextAlign(TA_RIGHT);
			//pDC->TextOut(x1 + GetX(TABLE_WIDTH)/iTitleCount - GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), vec.at(i).strContent);
			pDC->drawText(x1 + GetX(TABLE_WIDTH) / iTitleCount - GetX(TEXT_DISTANCE_X)-pDC->fontMetrics().width(vec.at(i).strContent), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(vec.at(i).strContent), pDC->fontMetrics().height(), Qt::AlignRight, vec.at(i).strContent);
		}


	}

	return iLeftTopY + GetY(iLineCount*TABLE_LINE_HEIGHT + TABLE_TITLE_HEIGHT + TABLE_TO_TITLE_DIS);
}

int QReportBase::DrawFunDetail(QPainter* pDC, int iLeftTopY, QString strTitle, QString strContetn)//���ʽ�����ϸ�����һ��
{
	int iReturn = iLeftTopY + GetY(TABLE_LINE_HEIGHT); //����©����һ�еĸ߶�
	iLeftTopY -= GetY(TABLE_TITLE_HEIGHT + TABLE_TO_TITLE_DIS); //��ȡ�ʽ���ϸ�ı����������yֵ��û�л�©�����е�ʱ��

	//����һ������
	//pDC->MoveTo(GetX(LEFT_X), iLeftTopY);
	//pDC->LineTo(GetX(LEFT_X), iLeftTopY  + GetY(TABLE_LINE_HEIGHT));
	pDC->drawLine(GetX(LEFT_X), iLeftTopY, GetX(LEFT_X), iLeftTopY + GetY(TABLE_LINE_HEIGHT));
	//���ڶ�������
	//pDC->MoveTo(GetX(LEFT_X + FUN_DETAIL_COL_TITLE_WIDTH), iLeftTopY);
	//pDC->LineTo(GetX(LEFT_X + FUN_DETAIL_COL_TITLE_WIDTH), iLeftTopY + GetY(TABLE_LINE_HEIGHT));
	pDC->drawLine(GetX(LEFT_X + FUN_DETAIL_COL_TITLE_WIDTH), iLeftTopY, GetX(LEFT_X + FUN_DETAIL_COL_TITLE_WIDTH), iLeftTopY + GetY(TABLE_LINE_HEIGHT));


	//������������,-1������У��ƫ��������������������
	//pDC->MoveTo(GetX(RIGHT_X-1), iLeftTopY); //������5�޷����룬������������һ���ٻ��˼�����
	//pDC->LineTo(GetX(RIGHT_X-1), iLeftTopY  +  GetY(TABLE_LINE_HEIGHT));
	pDC->drawLine(GetX(RIGHT_X - 1), iLeftTopY, GetX(RIGHT_X - 1), iLeftTopY + GetY(TABLE_LINE_HEIGHT));

	//���ײ��ĺ���
	//pDC->MoveTo(GetX(LEFT_X), iLeftTopY + GetY(TABLE_LINE_HEIGHT));
	//pDC->LineTo(GetX(RIGHT_X), iLeftTopY + GetY(TABLE_LINE_HEIGHT));
	pDC->drawLine(GetX(LEFT_X), iLeftTopY + GetY(TABLE_LINE_HEIGHT), GetX(RIGHT_X), iLeftTopY + GetY(TABLE_LINE_HEIGHT));

	//д������
	pDC->drawText(GetX(LEFT_X + TEXT_DISTANCE_X), iLeftTopY + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(strTitle), pDC->fontMetrics().height(), Qt::AlignLeft, strTitle);

	/*pDC->TextOut(GetX(LEFT_X + TEXT_DISTANCE_X), iLeftTopY + GetY(TEXT_DISTANCE_Y), strTitle);
	pDC->SetTextAlign(TA_RIGHT);
	pDC->TextOut(GetX(RIGHT_X - TEXT_DISTANCE_X), iLeftTopY + GetY(TEXT_DISTANCE_Y), strContetn);*/
	pDC->drawText(GetX(RIGHT_X - TEXT_DISTANCE_X) - pDC->fontMetrics().width(strContetn), iLeftTopY + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(strContetn), pDC->fontMetrics().height(), Qt::AlignRight, strContetn);

	return iReturn;
}


int QReportBase::DrawTable2( QPainter* pDC, int iLeftTopY, int iLineCount, int iColCount, const QStringList &strArray, QString strLTitle, QString strRTitle, const vector<RptColumnInfo> &vColumnInfo , int iLAliBegin /*= 0*/,  bool bColumnEven /*= true*/)
{
	int x1,y1;
	int x2,y2;
	int i;
	int iColWid;

	//������
	//pDC->SetTextAlign(TA_LEFT);
	y1 = iLeftTopY - GetY(TABLE_TITLE_HEIGHT);
	//pDC->TextOut(GetX(LEFT_X + TEXT_DISTANCE_X), y1, strLTitle);

	pDC->drawText(GetX(LEFT_X + TEXT_DISTANCE_X), y1, pDC->fontMetrics().width(strLTitle), pDC->fontMetrics().height(), Qt::AlignLeft, strLTitle);


	//pDC->SetTextAlign(TA_RIGHT);
	//pDC->TextOut(GetX(RIGHT_X - TEXT_DISTANCE_X), y1, strRTitle);
	//pDC->SetTextAlign(TA_LEFT);
	pDC->drawText(GetX(RIGHT_X - TEXT_DISTANCE_X)- pDC->fontMetrics().width(strRTitle), y1, pDC->fontMetrics().width(strRTitle), pDC->fontMetrics().height(), Qt::AlignRight, strRTitle);

	//������table�ľ���
	x1 = GetX(LEFT_X);
	y1 = iLeftTopY;
	x2 = GetX(RIGHT_X);
	y2 = y1 + GetY(TABLE_LINE_HEIGHT)*iLineCount + GetY(TABLE2_TITLE_HEIGHT);
	//pDC->Rectangle(x1, y1, x2, y2); 
	pDC->drawRect(x1, y1, x2-x1, y2-y1);
	//����
	for(i = 0; i < iLineCount; i++)
	{
		if(i == 0) //��һ��Ϊ�����У��߶Ȳ�ͬ
		{
			y1 += GetY(TABLE2_TITLE_HEIGHT);
		}
		else
		{
			y1 += GetY(TABLE_LINE_HEIGHT);
		}

		//pDC->MoveTo(GetX(LEFT_X), y1);
		//pDC->LineTo(GetX(RIGHT_X), y1);
		pDC->drawLine(GetX(LEFT_X), y1, GetX(RIGHT_X), y1);
	}

	//����
	x1 = GetX(LEFT_X);
	y1 = iLeftTopY; //ÿһ���������yֵ
	iColWid = GetX(TABLE_WIDTH) / iColCount; //�����еĿ��
	for(i = 1; i < iColCount; i++)
	{
		if(bColumnEven)
		{
			x1 += iColWid;
		}
		else
		{
			int iTemp = (int)(((float)vColumnInfo.at(i-1).iColumnPercent)/100.0*GetX(TABLE_WIDTH));
			x1 += iTemp;
		}

		//
		//pDC->MoveTo(x1, y1);
		//pDC->LineTo(x1, y2); //y2���������ֵ

		pDC->drawLine(x1,y1,x1,y2);
	}

	//д�����ݣ���������ݣ�
	for(i = 0; i < (iLineCount+1)*iColCount; i++)
	{
		// x1�ǵ�ǰ�е���ߵĿ�ʼλ��
		// ��õ�ǰ�еĿ��
		int iCurColumnWid;
		if(bColumnEven)
		{
			iCurColumnWid = iColWid;
		}
		else
		{
			iCurColumnWid = (int)(((float)vColumnInfo.at(i%iColCount).iColumnPercent)/100.0*GetX(TABLE_WIDTH));
		}
		 
		if(i == 0)
		{
			x1 = GetX(LEFT_X);
			y1 = iLeftTopY;
		}
		else if(i%iColCount == 0) //�������һ�У���պû�����һ�еĵ�һ��
		{
			x1  = GetX(LEFT_X);
			if(i == iColCount) // ����պ��ǵڶ��еĵ�һ��
			{
				y1 += GetY(TABLE2_TITLE_HEIGHT);
			}
			else //
			{
				y1 += GetY(TABLE_LINE_HEIGHT);
			}
		}
		else
		{
			// ������ǵ�һ�У������һ�еĿ��
			if(bColumnEven)
			{
				x1 += iColWid;
			}
			else
			{
				x1 += (int)(((float)vColumnInfo.at(i%iColCount-1).iColumnPercent)/100.0*GetX(TABLE_WIDTH));
			}
		}

		// ����ǵ�һ�У���������������
		if(i < iColCount || i%iColCount < iLAliBegin)
		{
			//pDC->SetTextAlign(TA_LEFT);
			QString str = strArray[i];
			if(i < iColCount) // ����ǵ�һ��
			{
				int iDisX,iDisY;

				int len = str.length(); //�����ֵ���2��
                int iReturnBegin = vColumnInfo.at(i%iColCount).iReturnBegin;
				if(vColumnInfo.at(i%iColCount).bReturn && len > iReturnBegin) // ������еı�����Ҫ���У����Ҹ����Ѿ����ڻ��еĸ���
				{
					// ��һ��x����ʼ��λ��
					iDisX = (iCurColumnWid - iReturnBegin/2*GetY(MY_FONT_SIZE))/2;
					//pDC->TextOut(x1 + iDisX, y1 + GetY(TEXT_DISTANCE_Y), str.left(iReturnBegin));
					pDC->drawText(x1 + iDisX, y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(str.left(iReturnBegin)), pDC->fontMetrics().height(), Qt::AlignLeft, str.left(iReturnBegin));


					QString str2 = str.mid(iReturnBegin);
					iDisX = (iCurColumnWid - str2.length()/2*GetY(MY_FONT_SIZE))/2;
					//pDC->TextOut(x1 + iDisX, y1 + GetY(TEXT_DISTANCE_Y + MY_FONT_SIZE), str2);
					pDC->drawText(x1 + iDisX, y1 + GetY(TEXT_DISTANCE_Y + MY_FONT_SIZE), pDC->fontMetrics().width(str2), pDC->fontMetrics().height(), Qt::AlignLeft, str2);

				}
				else
				{
					// һ�о�����ʾ
					iDisY = GetY(TABLE2_TITLE_HEIGHT - MY_FONT_SIZE)/2;
					iDisX = (iCurColumnWid - (len/2)*GetY(MY_FONT_SIZE))/2;
					//pDC->TextOut(x1 + iDisX, y1 + iDisY, str);
					//2018-1-5  15����
					pDC->drawText(x1 + iDisX-15, y1 + iDisY, pDC->fontMetrics().width(str), pDC->fontMetrics().height(), Qt::AlignLeft, str);
				}
			}
			else // �������������
			{
				//pDC->TextOut(x1 + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), str);	
				pDC->drawText(x1 + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(str), pDC->fontMetrics().height(), Qt::AlignLeft, str);
			}	
		}
		else
		{

			// ����Ǵ�ӡģʽ�����һ�У������ӡʱ�����һ�е�����ƫ����������
			if(m_eShowMode == E_PRINT && i%iColCount == iColCount -1) 
			{
				// 20��У׼ֵ
				//pDC->TextOut(GetX(RIGHT_X)-20, y1 + GetY(TEXT_DISTANCE_Y), strArray.GetAt(i));
				pDC->drawText(GetX(RIGHT_X) - 20- pDC->fontMetrics().width(strArray.at(i)), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(strArray.at(i)), pDC->fontMetrics().height(), Qt::AlignRight, strArray.at(i));
			
			}
			else
			{
				//pDC->TextOut(x1 + iCurColumnWid - GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), strArray.GetAt(i));
				pDC->drawText(x1 + iCurColumnWid - GetX(TEXT_DISTANCE_X)- pDC->fontMetrics().width(strArray.at(i)), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(strArray.at(i)), pDC->fontMetrics().height(), Qt::AlignRight, strArray.at(i));

			}
		}	
	}

	return iLeftTopY + GetY(TABLE2_TITLE_HEIGHT) + GetY(TABLE_LINE_HEIGHT)*iLineCount 
		+ GetY(TABLE_TO_TITLE_DIS) + GetY(TABLE_TITLE_HEIGHT);
}

/*��ӡ������**************************************************************************************************************/
void QReportBase::DrawTiHuo(QPainter* pDC)
{
	//������
	int i;
	//CFont *pOldFont;
	//CFont DataFont;

	QFont oldFont  = qApp->font();
	QFont *newFont = new QFont("����",20);
	newFont->setBold(true);
	int nFontHeight = GetY(130);
 	//DataFont.CreateFont(
 	//	nFontHeight,
 	//	0,
 	//	0,
 	//	900,
 	//	FW_HEAVY, // ����
 	//	0,
 	//	0,
 	//	0,
 	//	DEFAULT_CHARSET,
 	//	OUT_DEFAULT_PRECIS,
 	//	CLIP_DEFAULT_PRECIS,
 	//	DEFAULT_QUALITY,
 	//	FF_DONTCARE,
 	//	_T("����") 
 	//	);;
	//pOldFont = pDC->SelectObject(&DataFont);
	pDC->setFont(*newFont);

	QString strCnTitle = "�Ϻ��ƽ����������";

	QFontMetrics fm(*newFont);
	QRect rec = fm.boundingRect(strCnTitle);
	//�ַ�����ռ�����ؿ��,�߶�  
	int textWidth = rec.width();
	int textHeight = rec.height();
	//CSize sizeCnTitle = pDC->GetTextExtent(strCnTitle);
	

	TIHUO_TITLE_BEGIN_X = (m_nPageWidth - textWidth)/2;
	//pDC->TextOut(TIHUO_TITLE_BEGIN_X, GetY(TIHUO_TITLE_BEGIN_Y), strCnTitle);
	pDC->drawText(TIHUO_TITLE_BEGIN_X, GetY(TIHUO_TITLE_BEGIN_Y), pDC->fontMetrics().width(strCnTitle), pDC->fontMetrics().height(), Qt::AlignLeft, strCnTitle);


	QString strEnTitle = "Shanghai Gold Exchange Lading Application Form";
	QRect rec2      = fm.boundingRect(strEnTitle);
	//textWidth = rec.width();
	//textHeight = rec.height();
	//CSize sizeTitle = pDC->GetTextExtent(strEnTitle);
	//pDC->TextOut((m_nPageWidth - textWidth)/2,GetY(TIHUO_TITLE_BEGIN_Y )+ sizeTitle.cy, strEnTitle);
	pDC->drawText((m_nPageWidth - textWidth) / 2, GetY(TIHUO_TITLE_BEGIN_Y) + rec2.height(),  pDC->fontMetrics().width(strEnTitle),pDC->fontMetrics().height(), Qt::AlignLeft, strEnTitle);

	
	//pDC->SelectObject (pOldFont);
	pDC->setFont(oldFont);
	//������Ĳ��֣�title����ģ�
	QString strTitle[17] = {"��������(Bill of lading No.)", "��������(Application date)", 
		"��Ա���(Member account No.)",     "��Ա����(Member name)",     "�ͻ�����(Client account No.)", 
		"�ͻ�����(Client name)", 
		"�ֿ����(Vault Code)",   "�ֿ�����(Vault name)", "�ֿ��ַ(Vault address)",  "��ϵ��(Vault contacts)",
		"��ϵ�绰(Vault Tel No.)", "���������(Lading person)",
		"֤������(Lading person's certificate type)",   "֤����(Lading person's certificate No.)",   
		"�����ʼ����(Starting date of lading)", "�����ֹ����(Ending date of lading)", "����״̬(Application Status)"};

	QString strWords;
	int x,y;
	y = GetY(TIHUO_TITLE_BEGIN_Y + TITLE_TOP_DISTANCE) + rec2.height();
	//CSize sizeLeft = pDC->GetTextExtent(strTitle[12]);
	QFontMetrics fm1(oldFont);
	QRect sizeLeft = fm1.boundingRect(strTitle[12]);
	//CSize sizeRight(0,0);
	QRect sizeRight(0, 0, 0, 0);
	//m_strTiHuoTop[8] = "�����ʼ����(Starting date of lading)�����ʼ����(Starting date of lading)";
	for(i = 0; i < 17; i++)
	{
		//CSize sizeValue = pDC->GetTextExtent(m_strTiHuoTop[i]);

		QRect rec4 = fm1.boundingRect(m_strTiHuoTop[i]);
		if (sizeLeft.width() > sizeRight.width())
		{
			sizeRight = rec4;
		}
	}

	if (sizeLeft.width() + sizeRight.width() < m_nPageWidth)
	{
		TOP_BEGIN_X = (m_nPageWidth - sizeLeft.width() - sizeRight.width())/3;//��ʼλ��,Ҳ�����ƺ�ֵ�ļ��
	}

	TOP_TITLE_WIDTH = sizeLeft.width() + TOP_BEGIN_X;
	int nValueWidth = m_nPageWidth - TOP_BEGIN_X*3 - sizeLeft.width();
	for(i = 0; i < 17; i++)
	{
// 		if(i % 2 == 0)
// 		{
			//����ǵ�һ�У����ʼ��xֵ��������yֵ
			x = TOP_BEGIN_X;
			y += GetY(TOP_LINE_HEIGHT);
// 		}
// 		else
// 		{
// 			//����ǵڶ��У�������yֵ
// 			x += GetX(TOP_CONTENT_EIDTH);
// 		}
		//д����
		//pDC->TextOut(x, y, strTitle[i]);
		pDC->drawText(x,y, pDC->fontMetrics().width(strTitle[i]), pDC->fontMetrics().height(), Qt::AlignLeft, strTitle[i]);

		//д����
		x = x + TOP_TITLE_WIDTH;
		//CSize sizeValue = pDC->GetTextExtent(m_strTiHuoTop[i]);

		QRect sizeValue = fm1.boundingRect(m_strTiHuoTop[i]);
		if (sizeValue.width() > nValueWidth)
		{
			int nLine = sizeValue.width() / nValueWidth + 1;
			QRect rcValue(x, y, x + (nValueWidth), y + (nFontHeight * nLine));
			
			//pDC->DrawText(m_strTiHuoTop[i],rcValue, DT_LEFT|DT_WORDBREAK);
			pDC->drawText(rcValue, m_strTiHuoTop[i]);
			//(x, y, pDC->fontMetrics().width(), pDC->fontMetrics().height(), Qt::AlignLeft, strTitle[i]);

			y += (nFontHeight* (nLine-1));//GetY(rcValue.Height()) - GetY(TOP_LINE_HEIGHT);
		}
		else
			//pDC->TextOut(x, y, m_strTiHuoTop[i]);
		    pDC->drawText(x, y, pDC->fontMetrics().width(strTitle[i]), pDC->fontMetrics().height(), Qt::AlignLeft, strTitle[i]);
	}

	y += GetY(TOP_MIDDLE_DISTANCE + TOP_LINE_HEIGHT);

	int x1,y1;
	//�����ĺ���
	MIDDLE_COLUMN_WIDTH = (m_nPageWidth - TOP_BEGIN_X*2)/2;
	MIDDLE_BEGIN_X = TOP_BEGIN_X;
	x1 = MIDDLE_BEGIN_X + 2*(MIDDLE_COLUMN_WIDTH); //�յ��xֵ
	y1 = y;
	for(i = 0; i < 4; i++)
	{
		//pDC->MoveTo((MIDDLE_BEGIN_X), y1); //���
		//pDC->LineTo(x1, y1);             //�յ�
		pDC->drawLine((MIDDLE_BEGIN_X), y1,x1, y1);
		y1 += GetY(MIDDLE_LINE_HEIGTH);
		if (i == 0)
		{
			y1 +=  nFontHeight+GetY(10);//��һ������һ�����ֵĸ߶�
		}
	}
	//����������
	x1 = (MIDDLE_BEGIN_X);
	y1 = y + 3*GetY(MIDDLE_LINE_HEIGTH) + nFontHeight+GetY(10); //�յ��yֵ
	for(i = 0; i< 3; i ++)
	{
		//pDC->MoveTo(x1, y);
		//pDC->LineTo(x1, y1);
		pDC->drawLine(x1, y, x1, y1);

		x1 += (MIDDLE_COLUMN_WIDTH); //xÿ������һ����Ԫ��Ŀ��
	}

	//TEXTMETRIC textmetric;
	//pDC->GetTextMetrics(&textmetric);
	//д�����
	y1 = y - GetY(MIDDLE_LINE_HEIGTH);
	QString strTable[8] = {"����Ʒ��", "��׼�������(kg)", "Delivery variety",
		"Standard weight(Kg)",
		m_strVarietyId, m_strAmount, "�ϼ�  In Total", m_strAmount};
	for(i = 0; i < 8; i++)
	{
		if( i %2 == 0)
		{
			x1  = (MIDDLE_BEGIN_X);
			if (i == 2)
			{
				y1 += nFontHeight+GetY(10);//��һ��2������ 
			} 
			else
			{
				y1 += GetY(MIDDLE_LINE_HEIGTH);
			}
			
		}
		else
		{
			x1 += (MIDDLE_COLUMN_WIDTH);
		}
		//������ֵĸ������������־���
		int len = strTable[i].length(); //�����ֵ���2��
		//���д�����ֵĿ�ʼ��
		int iDisX = ((MIDDLE_COLUMN_WIDTH) - (len/2)*GetY(MY_FONT_SIZE))/2;
		//pDC->TextOut(x1+iDisX, y1 + GetY(MIDDLE_TEXT_DISTANCE_Y),  strTable[i]);

		pDC->drawText(x1 + iDisX, y1 + GetY(MIDDLE_TEXT_DISTANCE_Y), pDC->fontMetrics().width(strTable[i]), pDC->fontMetrics().height(), Qt::AlignLeft, strTable[i]);

	}

	y += 3*GetY(MIDDLE_LINE_HEIGTH) + sizeLeft.height();
	y += GetY(MIDDLE_LINE_HEIGTH);

	//д�׶�����
	QString strBottom[4] = {"�Ƶ�(Tabulator):", m_strTradeName, "����(Approver):", ""};
	y1 = y;
	x1 = TOP_BEGIN_X;
	//pDC->TextOut(x1, y1, strBottom[0]);

	QRect si = fm1.boundingRect(strTitle[12]);
	//CSize si = pDC->GetTextExtent(strBottom[0]);


	//pDC->TextOut(x1 + (si.cx), y1, strBottom[1]);	
	pDC->drawText(x1 + (si.width()), y1 , pDC->fontMetrics().width(strBottom[1]), pDC->fontMetrics().height(), Qt::AlignLeft, strBottom[1]);


	x1 = (TOP_BEGIN_X*2 + sizeLeft.width() + MIDDLE_BEGIN_X + MIDDLE_COLUMN_WIDTH)/2;//value��ʼλ���������ߵ��м�λ��
	//pDC->TextOut(x1, y1, strBottom[2]);
	pDC->drawText(x1 , y1 , pDC->fontMetrics().width(strBottom[2]), pDC->fontMetrics().height(), Qt::AlignLeft, strBottom[2]);

	x1 += BOTTOM_TITLE_WIDTH;
	//pDC->TextOut(x1 , y1, strBottom[3]);
	pDC->drawText(x1 , y1 , pDC->fontMetrics().width(strBottom[3]), pDC->fontMetrics().height(), Qt::AlignLeft, strBottom[3]);

}

//��ʼ���������ӡ�������
void QReportBase::IniTiHuoData( Rsp5103 &rsp )
{
	#ifdef _VERSION_GF
	int iValuePoiter[17] = {1, 24, 7, 8, 2, 4, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27};
	#else
	int iValuePoiter[17] = {1, 22, 5, 6, 2, 4, 14, 15, 16, 17, 18, 19, 20, 21, 23, 24, 25};
	#endif
	ArrayListMsg aMsg = rsp.alm_take_sheet_detail.GetValue(0);
	for(int i = 0; i < 17; i++)
	{
		string value = aMsg.GetStringEx(iValuePoiter[i]);
		m_strTiHuoTop[i] = CHJGlobalFun::str2qstr(value);
	}

	//����Ʒ�ֺ��������
	#ifdef _VERSION_GF
	m_strVarietyId = CHJGlobalFun::str2qstr(aMsg.GetStringEx(10));
	m_strAmount = CHJGlobalFun::str2qstr(aMsg.GetStringEx(11));
	#else
	m_strVarietyId = CHJGlobalFun::str2qstr(aMsg.GetStringEx(8));
	m_strAmount = CHJGlobalFun::str2qstr(aMsg.GetStringEx(9));
	#endif
	double fAmout = m_strAmount.toDouble()/1000.0;
	//m_strAmount.Format("%.2f", fAmout);
	m_strAmount.number(fAmout,'f',2);
	//�Ƶ�
	m_strTradeName = CHJGlobalFun::str2qstr(aMsg.GetStringEx(3));
}

/*����**************************************************************************************************************/
// ������ʾ��ģʽ���Ǳ����Ǵ�ӡԤ��
void QReportBase::SetShowMode( EShowMode eShowMode )
{
	m_eShowMode = eShowMode;
}
// ��ҳ����Ϣ�����������д
void QReportBase::WritePage( QPainter* pDC, PrintInfo* pInfo )
{

}

int QReportBase::DrawTableEx( QPainter* pDC, int iLeftTopY, int iLineCount, int iTitleCount, int iTitleWid, const vector<RptDataInfo> &vec, QString strLTitle, QString strRTitle, const vector<Table1Info> &vColumnInfo )
{
	int x1,y1;
	int x2,y2;
	int i;

	QFont* font = new QFont("����", 10);
	pDC->setFont(*font);
	//������
	y1 = GetY(iLeftTopY - TABLE_TITLE_HEIGHT);
	//pDC->TextOut(GetX(LEFT_X + TEXT_DISTANCE_X), y1, strLTitle);
	pDC->drawText(GetX(LEFT_X + TEXT_DISTANCE_X), y1, pDC->fontMetrics().width(strLTitle), pDC->fontMetrics().height(), Qt::AlignLeft, strLTitle);


	//pDC->SetTextAlign(TA_RIGHT);
	//pDC->TextOut(GetX(RIGHT_X - TEXT_DISTANCE_X), y1, strRTitle);
	pDC->drawText(GetX(RIGHT_X - TEXT_DISTANCE_X)- pDC->fontMetrics().width(strRTitle), y1, pDC->fontMetrics().width(strRTitle), pDC->fontMetrics().height(), Qt::AlignRight, strRTitle);

	//pDC->SetTextAlign(TA_LEFT);


	//������table�ľ���
	x1 = GetX(LEFT_X);
	y1 = GetY(iLeftTopY);
	x2 = GetX(RIGHT_X);
	y2 = y1 + GetY(TABLE_LINE_HEIGHT)*iLineCount;
	//pDC->Rectangle(x1, y1, x2, y2); 
	pDC->drawRect(x1, y1, x2-x1, y2-y1);
	//����
	for(i = 1; i < iLineCount; i++)
	{
		y1 += GetY(TABLE_LINE_HEIGHT);
		//pDC->MoveTo(GetX(LEFT_X), y1);
		//pDC->LineTo(GetX(RIGHT_X), y1);
		pDC->drawLine(GetX(LEFT_X), y1, GetX(RIGHT_X), y1);
	}

	//����
	x1 = GetX(LEFT_X);
	y1 = GetY(iLeftTopY); //ÿһ���������yֵ
	y2 = GetY(iLeftTopY) + GetY(TABLE_LINE_HEIGHT)*iLineCount;//ÿһ���ߵ������yֵ
	//iContentWid = GetX(TABLE_WIDTH)/iTitleCount - iTitleWid; //�����еĿ��
	int iContentAllWid = GetX(TABLE_WIDTH) - iTitleCount*iTitleWid;
	for(i = 1; i < iTitleCount*2; i++)
	{
		if(i%2 == 1)
		{
			// �����ұߵ���
			x1 += iTitleWid;
		}
		else
		{
			// �����ұߵ���
			x1 += (int)(((float)vColumnInfo.at(i/2-1).iColumnPercent)/100.0*iContentAllWid);
		}

		//pDC->MoveTo(x1, y1);
		//pDC->LineTo(x1, y2);

		pDC->drawLine(x1, y1, x1, y2);
	}

	 
	//д�����ݣ���������ݣ�
	for(i = 0; i < iLineCount*iTitleCount; i++)
	{ 
		if(i == 0)
		{
			x1 = GetX(LEFT_X);
			y1 = GetY(iLeftTopY);
		}
		else if(i%iTitleCount == 0) //�������һ��
		{
			x1  = GetX(LEFT_X);
			y1 += GetY(TABLE_LINE_HEIGHT);
		}
		else
		{
			//x1 += GetX(TABLE_WIDTH)/iTitleCount;
			x1 += iTitleWid + (int)(((float)vColumnInfo.at((i-1)%iTitleCount).iColumnPercent)/100.0*iContentAllWid);
		}
		QString str1 = vec.at(i).strTitle;
		//pDC->TextOut(x1 + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), vec.at(i).strTitle);
		pDC->drawText(x1 + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(vec.at(i).strTitle), pDC->fontMetrics().height(), Qt::AlignLeft, vec.at(i).strTitle);



		if(vec.at(i).isLeftAli)
		{
			//pDC->TextOut(x1 + iTitleWid + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), vec.at(i).strContent);	
		pDC->drawText(x1 + iTitleWid + GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(vec.at(i).strContent), pDC->fontMetrics().height(), Qt::AlignLeft, vec.at(i).strContent);


		}
		else
		{
			//pDC->SetTextAlign(TA_RIGHT);
			int iNextBColumn = (int)(((float)vColumnInfo.at((i)%iTitleCount).iColumnPercent)/100.0*iContentAllWid);
			//pDC->TextOut(x1  + iTitleWid + iNextBColumn - GetX(TEXT_DISTANCE_X), y1 + GetY(TEXT_DISTANCE_Y), vec.at(i).strContent);
		pDC->drawText(x1 + iTitleWid + iNextBColumn - GetX(TEXT_DISTANCE_X)- pDC->fontMetrics().width(vec.at(i).strContent), y1 + GetY(TEXT_DISTANCE_Y), pDC->fontMetrics().width(vec.at(i).strContent), pDC->fontMetrics().height(), Qt::AlignRight, vec.at(i).strContent);


		}

		//pDC->SetTextAlign(TA_LEFT);
	}

	return GetY(iLeftTopY) + GetY(iLineCount*TABLE_LINE_HEIGHT + TABLE_TITLE_HEIGHT + TABLE_TO_TITLE_DIS);
}

/*
int QReportBase::GetX( int x )
{
	return x*m_xRate;
}

int QReportBase::GetY( int y )
{
	return y*m_yRate;
}
*/



