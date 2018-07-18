#include "TiHuoMgr.h"
#include "Global.h"
#include "TraderCpMgr.h"
#include "HJConstant.h"
#include "HJGlobalFun.h"
#include "TranMessage.h"

CTiHuoMgr::CTiHuoMgr(void)
{
}

CTiHuoMgr::~CTiHuoMgr(void)
{
}

CTiHuoMgr& CTiHuoMgr::GetInstance()
{
	static CTiHuoMgr theSingleton;
	return theSingleton;
}

void CTiHuoMgr::Initialize(  )
{
}

void CTiHuoMgr::QueryAll()
{
	// ��ѯ����������Ϣ
	Rsp5101 rsp5101;
	if( Query(rsp5101, "", "", "") )
	{
		HandleQueryResult(rsp5101);
	}
}

/*
�����û�������ѯ
rsp5101 ��ѯ�ṹ
*/
void CTiHuoMgr::HandleUserQuery( Rsp5101 &rsp5101 )
{
	// ���������ѯ���
	HandleQueryResult(rsp5101, false);

	// ˢ�µ��������֤�𶳽�
	RefreshTakeFroze();
}

void CTiHuoMgr::HandleTodayTrade()
{
	// ��ѯ����������Ϣ
	Rsp5101 rsp5101;
	if( Query(rsp5101, CHJGlobalFun::qstr2str(g_Global.m_strExchDate), CHJGlobalFun::qstr2str(g_Global.m_strExchDate), "") )
	{
		HandleQueryResult(rsp5101);
	}

	// ˢ�µ��������֤�𶳽�
	RefreshTakeFroze();
}

void CTiHuoMgr::HandleCancel( const string &sLocalSheetNo )
{
	// ��ȡ�����������Ϣ
	Rsp5101 rsp5101;
	if( g_TiHuoMgr.Query(rsp5101, "", "", sLocalSheetNo) )
	{
		
	}
}

bool CTiHuoMgr::Query( Rsp5101 &rsp, const string &sBegin, const string &sEnd, const string &sLocalSheetNo )
{
	Req5101 req; //��������

	req.oper_flag      = 1;
	req.local_sheet_no = sLocalSheetNo; //��������ţ��������������������룬��������û����ȡȫ��
	req.cust_id        = CHJGlobalFun::qstr2str(g_Global.m_strUserID); //�û�id
	req.start_date     = sBegin; // ��ʼʱ��
	req.end_date       = sEnd;   // ����ʱ��

	//���ͱ���
	if(0 != g_TraderCpMgr.HandlePacket(rsp,req,"5101", 20))
	{
		//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
		return false;	
	}
	else
	{
		return g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg));
	}
}

bool CTiHuoMgr::HandleCalculate( const string &sOrderNo, const string sInsID, int nWeight, bool bFroze )
{
	FrozeInfo st;
	st.nWeight = nWeight;
	st.sInsID = sInsID;

	if( bFroze )
	{
		//m_mapFroze.insert(map<string, FrozeInfo>::value_type(sOrderNo, st));
		m_mapFroze.insert(sOrderNo, st);
	}
	else
	{
		//map<string, FrozeInfo>::iterator it = m_mapFroze.find(sOrderNo);
		auto it = m_mapFroze.find(sOrderNo);
		if( it != m_mapFroze.end() ) // ���û�б������
		{
			m_mapFroze.erase(it);
		}
	}

	// ���ݺ�Լ�����ҵ��ñʿ��
	auto itStore = g_TraderCpMgr.m_QMapStoreInfo.find(CHJGlobalFun::str2qstr(st.sInsID));
	if( itStore != g_TraderCpMgr.m_QMapStoreInfo.end() )
	{
		// ���Ʒ�ֿ����Ϣ
		StoreInfo &stStore = itStore.value();
		if( bFroze )
			stStore.iUseFulAmt -= st.nWeight;
		else
			stStore.iUseFulAmt += st.nWeight;

		// ģ�ⷢ��һ���ֻ�����
		bitset<5> bitvec;
		g_TraderCpMgr.SetBitSet( bitvec, false, true );
		SpotOrder stOrder;
		stOrder.instID = st.sInsID;
		g_TraderCpMgr.m_mapBdr[E_ONRECVRTNSPOTORDER].Broadcast(MSG_RECV_SPOT_ORDER, (void *)&stOrder, (void *)&bitvec, FALSE);
	} 

	return true;
}

void CTiHuoMgr::SetDay_take_margin( const string &sDay_take_margin )
{
	m_sDay_take_margin = sDay_take_margin;
}

void CTiHuoMgr::HandleQueryResult( Rsp5101 &rsp5101, bool bCancel )
{
	// ����
	QString sToday = CHJGlobalFun::GetCurDateFormat();
	for(size_t i = 0; i < rsp5101.htm_take_sheet_detail.size(); i++)
	{
		// ��ȡ���״̬
		string sState = rsp5101.htm_take_sheet_detail.GetString(i, "stat");
		// ��ȡ�������
		string sOrderNo = rsp5101.htm_take_sheet_detail.GetString(i, "local_sheet_no");

		// �ж��Ƿ�ǰ
		QString sApp_exch_date = CHJGlobalFun::str2qstr(rsp5101.htm_take_sheet_detail.GetString(i, "app_exch_date"));
		if( sApp_exch_date == g_Global.m_strExchDate )
		{
			// �жϸõ����Ƿ���
			auto it = m_mapFroze.find(sOrderNo);
			if( it == m_mapFroze.end() ) // ���û�б������
			{
				// ���������ɹ���������
				if( CONSTANT_TIHUO_SUS == sState )
				{
					HandleCalculate( 
						sOrderNo,
						CHJGlobalFun::qstr2str(g_TraderCpMgr.GetVarietyName(CHJGlobalFun::str2qstr(rsp5101.htm_take_sheet_detail.GetString(i, "variety_id")))),
						rsp5101.htm_take_sheet_detail.GetInt(i, "app_amount"),
						true);
				}
			}
			else
			{
				// ����ǳ�������ɹ�������ⶳ
				if( CONSTANT_TIHUO_CANCEL_TODAY == sState )
				{
					HandleCalculate( 
						sOrderNo,
						CHJGlobalFun::qstr2str(g_TraderCpMgr.GetVarietyName(CHJGlobalFun::str2qstr(rsp5101.htm_take_sheet_detail.GetString(i, "variety_id")))),
						rsp5101.htm_take_sheet_detail.GetInt(i, "app_amount"),
						false);
				}
			}
		}
		else
		{
			// ����ǻ�Ա���ճ����ҳ��������ǽ���
			if( sState == "4" && rsp5101.htm_take_sheet_detail.GetString(i, "cancel_exch_date") == CHJGlobalFun::qstr2str(g_Global.m_strExchDate ))
			{
                // mod by Jerry Lee, 2013-3-24, ������ÿ��һֱ�ۼӵ�����
                if (bCancel)
                {
                    HandleCalculate( 
                        sOrderNo,
						CHJGlobalFun::qstr2str(g_TraderCpMgr.GetVarietyName(CHJGlobalFun::str2qstr(rsp5101.htm_take_sheet_detail.GetString(i, "variety_id")))),
                        rsp5101.htm_take_sheet_detail.GetInt(i, "app_amount"),
                        false);
                }
			}
		}
	}
}

void CTiHuoMgr::RefreshTakeFroze()
{
	// ��ȡ���µ����������Ϣ�����
	Rsp1020 rsp1020;
	if(CTranMessage::Handle1020(rsp1020, '0', '1', '0', '0', '0', '0', true) == 0)
	{
		if( rsp1020.f_take_margin != m_sDay_take_margin )
		{
			g_TraderCpMgr.m_stFundInfo.dUseFulBal += atof(rsp1020.f_take_margin.c_str())-atof(m_sDay_take_margin.c_str());
			m_sDay_take_margin = rsp1020.f_take_margin;
			g_TraderCpMgr.m_mapBdr[E_REFRESHFUND].Broadcast(WM_REFRESH_FUND, 0, 0);
		}
	}
}


