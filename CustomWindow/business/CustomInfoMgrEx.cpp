#include "CustomInfoMgrEx.h"
#include "Const.h"
#include "TraderCpMgr.h"
#include "HJConstant.h"
#include "HJGlobalFun.h"
#include "HJCommon.h"
#include "Global.h"
#include "Struct.h"

CustomInfoMgrEx g_CusInfo;

CustomInfoMgrEx::CustomInfoMgrEx(void)
{
}

CustomInfoMgrEx::~CustomInfoMgrEx(void)
{
}

void CustomInfoMgrEx::UpdateCustomInfo( const Rsp1020 &stRsp, const Req1020& req1020 )
{
	m_csMutex.Lock();

	// �ֲ�
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr( req1020.qry_defer ))
	{
		RefreshPosi(stRsp.htm_td_info);
		m_rsp1020.htm_td_info = stRsp.htm_td_info;
	}

	// ���
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr(req1020.qry_storage ))
	{
		RefreshStore(stRsp.hlm_stor_info);
		m_rsp1020.hlm_stor_info = stRsp.hlm_stor_info;
	}

	// �ʽ���Ϣ
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr(req1020.qry_fund ))
	{
		m_rsp1020.CopyFundInfo(stRsp);
	}

	// ӯ����Ϣ
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr(req1020.qry_surplus ))
	{
		m_rsp1020.CopySurplus(stRsp);
	}

	// �ͻ���Ϣ
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr(req1020.qry_cust_info ))
	{
		m_rsp1020.CopyCusInfo(stRsp);
	}

	// ��������Ϣ
	m_rsp1020.htm_prod_group_info      =  stRsp.htm_prod_group_info;
	// ��߱�֤����Ϣ
	m_rsp1020.htm_acct_large_side_sum  =  stRsp.htm_acct_large_side_sum;


	m_csMutex.Unlock();

	// �ֲ�
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr(req1020.qry_defer ))
	{
		g_TraderCpMgr.m_mapBdr[E_CUSTOM_INFO_CHANGE].Broadcast(WM_REFRESH_POSI, 0, 0);
	}

	// ���
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr(req1020.qry_storage ))
	{
		g_TraderCpMgr.m_mapBdr[E_CUSTOM_INFO_CHANGE].Broadcast(WM_REFRESH_STORE, 0, 0);
	}

	// �ʽ���Ϣ
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr(req1020.qry_fund ))
	{
		g_TraderCpMgr.m_mapBdr[E_CUSTOM_INFO_CHANGE].Broadcast(WM_REFRESH_FUND, 0, 0);
	}

	// �ͻ���Ϣ
	if( gc_YesNo_Yes == CHJGlobalFun::str2qstr(req1020.qry_cust_info ))
	{
		g_TraderCpMgr.m_mapBdr[E_CUSTOM_INFO_CHANGE].Broadcast(WM_CUS_BASE_INFO, 0, 0);
	}

	g_TraderCpMgr.m_mapBdr[E_CUSTOM_INFO_CHANGE].Broadcast(WM_CUSTOM_INFO_CHANGE, 0, 0);
}

//���㶳����
double CustomInfoMgrEx::CalculateFrozenCapital(const QString & ProdCode, const QString & ExchId ,double  orderCapital)
{
	double  dRet  = -1;
	bool    bFind = false;
	string  groupId;
	// ����
	for (size_t nPosInHtm = 0; nPosInHtm < m_rsp1020.htm_prod_group_info.size(); nPosInHtm++)
	{
		// ��Լ����
		string sInsID = m_rsp1020.htm_prod_group_info.GetString(nPosInHtm, "td_prod_code");
		if (sInsID == ExchId.toStdString())
		{
			bFind = true;
			groupId = m_rsp1020.htm_prod_group_info.GetString(nPosInHtm, "group_id");
		}
	}
	
	if (!bFind)
		return dRet = -1;


	// ����
	for (size_t nPosInHtm = 0; nPosInHtm < m_rsp1020.htm_acct_large_side_sum.size(); nPosInHtm++)
	{
		string	Id = m_rsp1020.htm_acct_large_side_sum.GetString(nPosInHtm, "group_id");

		if (groupId == Id)
		{
			double sBigVal   = stod(m_rsp1020.htm_acct_large_side_sum.GetString(nPosInHtm, "long"));
			double sSmallVal = stod(m_rsp1020.htm_acct_large_side_sum.GetString(nPosInHtm, "short"));

			if (sBigVal >= sSmallVal && sBigVal <= sSmallVal)
				return  dRet;

			if (sBigVal >= sSmallVal)
			{
				//���
				if (ExchId == CONSTANT_EXCH_CODE_DEFER_OPEN_LONG || ExchId == CONSTANT_EXCH_CODE_MIDD_DELIVERY_SHORT)
				{
					//ͬ���
					dRet = orderCapital;
					return  dRet;
				}
				//С��
				else  if (ExchId == CONSTANT_EXCH_CODE_DEFER_OPEN_SHORT || ExchId == CONSTANT_EXCH_CODE_MIDD_DELIVERY_LONG)
				{
					if (sSmallVal + orderCapital <= sBigVal)
						return 0;
					else
						return sSmallVal + orderCapital - sBigVal;
				}
			}
			else
			{
				//���
				if (ExchId == CONSTANT_EXCH_CODE_DEFER_OPEN_SHORT || ExchId == CONSTANT_EXCH_CODE_MIDD_DELIVERY_LONG)
				{
					//ͬ���
					dRet = orderCapital;
					return  dRet;
				}
				//С��
				else if (ExchId == CONSTANT_EXCH_CODE_DEFER_OPEN_LONG || ExchId == CONSTANT_EXCH_CODE_MIDD_DELIVERY_SHORT)
				{
					if (sSmallVal + orderCapital <= sBigVal)
						return 0;
					else
						return sSmallVal + orderCapital - sBigVal;
				}

			}
		}
	}


	//if (ExchId == CONSTANT_EXCH_CODE_DEFER_OPEN_LONG)// ���ڿ����/����
	//{

	//}
	//else if(ExchId == CONSTANT_EXCH_CODE_DEFER_OPEN_SHORT)// ���ڿ��ղ�/����
	//{

	//}
	//else if (ExchId == CONSTANT_EXCH_CODE_MIDD_DELIVERY_LONG) // �����������ս�
	//{

	//}
	//else if (ExchId == CONSTANT_EXCH_CODE_MIDD_DELIVERY_SHORT) // ���������ֽ���
	//{

	//}

	return  dRet;

}
// �Ѿ����ⲿ����
void CustomInfoMgrEx::RefreshPosi( const HashtableMsg &hsmPosi )
{

	m_mapDeferPosi.clear();

	// ����
	for( size_t nPosInHtm = 0; nPosInHtm < hsmPosi.size(); nPosInHtm++ )
	{
		// ��Լ����
		string sInsID = hsmPosi.GetString(nPosInHtm, "td_prod_code");
		if( !sInsID.empty() )
		{
			// �ֲ���Ϣ
			DeferPosi &stInfo = m_mapDeferPosi[sInsID];

			// ��¼��Լ����
			if( stInfo.sProdCode.isEmpty() )
			{
				stInfo.sProdCode = CHJGlobalFun::str2qstr(sInsID);
			}

			// ������λ
			if( CHJGlobalFun::IsDoubleZero(stInfo.dUnite) )
			{
				// ��ȡ��Ʒ�ֵļ�����λ����ÿ�ֵĿ�����
				ProdCodeInfo info;
				if( g_TraderCpMgr.GetProdeCode(info, CHJGlobalFun::str2qstr(sInsID) ))
				{
					stInfo.dUnite = CHJCommon::HandToGram(CHJGlobalFun::str2qstr(sInsID), info.measure_unit);
				}
			}

			// ������
			DeferPosiInfo &infoLong = stInfo.infoLong;
			infoLong.iCurrAllAmt = hsmPosi.GetUInt(nPosInHtm, "td_long_amt");                   // �ֲܳ�
			infoLong.iUsefulAmt = hsmPosi.GetUInt(nPosInHtm, "td_can_use_long");                // ���ò�
			infoLong.dAvgOpenPosPrice = hsmPosi.GetDouble(nPosInHtm, "td_long_open_avg_price"); // ���־���
			infoLong.dAvgPosPrice = hsmPosi.GetDouble(nPosInHtm, "td_long_posi_avg_price");     // �ֲ־���
			infoLong.dTotalFare = hsmPosi.GetDouble(nPosInHtm, "td_long_margin");               // �ֱֲ�֤��

			infoLong.iTodayAmt = hsmPosi.GetUInt(nPosInHtm, "td_day_open_long");                // ��֣���һ��׼ȷ
			//infoLong.iYesAmt = infoLong.iCurrAllAmt - infoLong.iTodayAmt;                       // ��֣���һ��׼ȷ
			int iTodayCuvAmt = hsmPosi.GetUInt(nPosInHtm, "td_day_cov_long");                // ��ƽ��

			//kenny 20180403
			infoLong.iYesAmt = infoLong.iCurrAllAmt - (infoLong.iTodayAmt - iTodayCuvAmt);                       // �ܳ�-(���-ƽ��)
			// ����ղ�
			DeferPosiInfo &infoShort = stInfo.infoShort;
			infoShort.iCurrAllAmt = hsmPosi.GetUInt(nPosInHtm, "td_short_amt");                   // �ֲܳ�
			infoShort.iUsefulAmt = hsmPosi.GetUInt(nPosInHtm, "td_can_use_short");                // ���ò�
			infoShort.dAvgOpenPosPrice = hsmPosi.GetDouble(nPosInHtm, "td_short_open_avg_price"); // ���־���
			infoShort.dAvgPosPrice = hsmPosi.GetDouble(nPosInHtm, "td_short_posi_avg_price");     // �ֲ־���
			infoShort.dTotalFare = hsmPosi.GetDouble(nPosInHtm, "td_short_margin");               // �ֱֲ�֤��

			infoShort.iTodayAmt = hsmPosi.GetUInt(nPosInHtm, "td_day_open_short");                // ��֣���һ��׼ȷ

			iTodayCuvAmt = hsmPosi.GetUInt(nPosInHtm, "td_day_cov_short");                // ��ƽ��
			infoShort.iYesAmt = infoShort.iCurrAllAmt - (infoShort.iTodayAmt - iTodayCuvAmt);
			//infoShort.iYesAmt = infoShort.iCurrAllAmt - infoShort.iTodayAmt;                      // ��֣���һ��׼ȷ

			// ����ֲ�ӯ��
			const QUOTATION& stQuotation = g_TraderCpMgr.m_QMapQuotation[sInsID];
			CalculateSurplus(stInfo,stQuotation.GetCalSurplusPrice());
		}
	}
}

void CustomInfoMgrEx::RefreshStore( const HashtableMsg &htmStore )
{
	m_mapStoreInfo.clear();

	// ����
	for( size_t nPosInHtm = 0; nPosInHtm < htmStore.size(); nPosInHtm++ )
	{
		// ��Լ����
		QString sInsID(g_TraderCpMgr.GetVarietyName(CHJGlobalFun::str2qstr(htmStore.GetString(nPosInHtm, "s_variety_id"))));
		StoreInfo &stInfo = m_mapStoreInfo[CHJGlobalFun::qstr2str(sInsID)];

		// ����
		stInfo.iAllAmt = htmStore.GetInt(nPosInHtm, "s_curr_amt");          // �ܿ��
		stInfo.iUseFulAmt = htmStore.GetInt(nPosInHtm, "s_can_use_amt");    // ���ÿ��
		stInfo.iExchFreeze = htmStore.GetInt(nPosInHtm, "s_entr_sell_amt"); // ���׶���
	}
}

void CustomInfoMgrEx::HandleRecvQuotation( const QUOTATION& stQuotation )
{
	DeferPosi stDeferPosiPara;

	m_csMutex.Lock();

	// ��ȡ��Ʒ�ֵĳֲ���Ϣ������ֲ�ӯ��
	//map<string, DeferPosi>::iterator it = m_mapDeferPosi.find(stQuotation.instID);
	unordered_map<string,DeferPosi>::iterator it = m_mapDeferPosi.find(stQuotation.instID);
	if( it != m_mapDeferPosi.end() )
	{
		// ��ȡ����Ʒ�ֶ�Ӧ�ĳֲ���Ϣ
		DeferPosi &stDeferPosi = it->second;

		// ��ȡ��������¼�
		UINT uiLast = stQuotation.GetCalSurplusPrice();

		// �ж��Ƿ���Ҫ����ӯ����Ϣ
		bool bReCalulate = ( stDeferPosi.uiLastPrice != uiLast ? true : false );
		if( bReCalulate  )
		{
			CalculateSurplus(stDeferPosi,uiLast);
		}

		// �Ƿ�����Ϣ
		if( bReCalulate )
		{
			if( stDeferPosi.infoLong.iCurrAllAmt > 0 || stDeferPosi.infoShort.iCurrAllAmt > 0 )
			{
				stDeferPosiPara = stDeferPosi;
			}
		}
	}

	m_csMutex.Unlock();

	// �Ƿ�㲥��Ϣ
	if( !stDeferPosiPara.sProdCode.isEmpty() )
	{
		g_TraderCpMgr.m_mapBdr[E_SURPLUS_CHANGE].Broadcast(WM_TOTAL_SURPLUS_CHANGE, 0, 0);
		g_TraderCpMgr.m_mapBdr[E_SURPLUS_CHANGE].Broadcast(WM_SURPLUS_CHANGE, (void *)&stDeferPosiPara,0, FALSE );
	}
}

double CustomInfoMgrEx::GetPosiSurplus( UINT uiLast, double dPosiAve, int iTotalHand, double dUnite,bool bLong )
{
	double dNewest = uiLast / g_Global.m_dQTFactor;

	// ��ȡӯ���ۣ�ע������ǿղֵĻ���ӯ���෴
	double dPriceDif = bLong ? (dNewest - dPosiAve) : (dPosiAve - dNewest);

	double dMoney = dPriceDif * iTotalHand * dUnite;

	// ����ղֵ�ʱ��ֲ�ӯ��Ϊ0��ʱ����ʾ-0.00������
	if(dMoney < 0.001 && dMoney > -0.001)
	{
		dMoney = 0.00;
	}

	return  dMoney;
}

double CustomInfoMgrEx::GetTotalPosiSurplus()
{
	double dTotalPosiMargin = 0.00;

	m_csMutex.Lock();
	for(auto it = m_mapDeferPosi.begin(); it != m_mapDeferPosi.end(); it++)
	{
		DeferPosi &stDeferPosi = (*it).second;
		if(stDeferPosi.infoLong.iCurrAllAmt > 0)
		{
			dTotalPosiMargin += stDeferPosi.infoLong.dPosi_PL;
		}
		if(stDeferPosi.infoShort.iCurrAllAmt > 0)
		{
			dTotalPosiMargin += stDeferPosi.infoShort.dPosi_PL;
		}
	}
	m_csMutex.Unlock();

	return dTotalPosiMargin;
}

unordered_map<string, DeferPosi> CustomInfoMgrEx::GetPosi()
{
	unordered_map<string, DeferPosi> mapPosi;

	m_csMutex.Lock();
	mapPosi = m_mapDeferPosi;
	m_csMutex.Unlock();

	return mapPosi;
}

FundInfoS CustomInfoMgrEx::GetFundInfoS()
{
	FundInfoS stFund;

	m_csMutex.Lock();
	stFund.sAllBalance = m_rsp1020.f_curr_bal;
	stFund.sUseFulBal = m_rsp1020.f_can_use_bal;
	stFund.sExchFrozeBal = m_rsp1020.f_exch_froz_bal;
	stFund.sPosiMargin = CHJGlobalFun::qstr2str(QString::number(GetTotalPosiSurplus()));
	m_csMutex.Unlock();

	return stFund;
}

FundInfo CustomInfoMgrEx::GetFundInfo()
{
	FundInfo stFund;

	m_csMutex.Lock();
	stFund.dAllBalance = atof(m_rsp1020.f_curr_bal.c_str());
	stFund.dUseFulBal = atof(m_rsp1020.f_can_use_bal.c_str());
	stFund.dExchFrozeBal = atof(m_rsp1020.f_exch_froz_bal.c_str());
	stFund.dPosiMargin = GetTotalPosiSurplus();
	m_csMutex.Unlock();

	return stFund;
}

unordered_map<string, StoreInfo> CustomInfoMgrEx::GetStore()
{
	unordered_map<string, StoreInfo> mapStore;

	m_csMutex.Lock();
	mapStore = m_mapStoreInfo;
	m_csMutex.Unlock();

	return mapStore;
}

std::string CustomInfoMgrEx::GetCustomName()
{
	string sName;

	m_csMutex.Lock();
	sName = m_rsp1020.c_cust_abbr;
	m_csMutex.Unlock();
	
	return sName;
}

double CustomInfoMgrEx::GetUsefullBal()
{
	double dBal = 0.00;

	m_csMutex.Lock();
	dBal = atof(m_rsp1020.f_can_use_bal.c_str());
	m_csMutex.Unlock();

	return dBal;
}

int CustomInfoMgrEx::GetUsefulStore( const string& sInst )
{
	int nAmt = 0;

	m_csMutex.Lock();
	// �������
	auto itStore = m_mapStoreInfo.find(sInst);
	if( itStore != m_mapStoreInfo.end() )
	{
		nAmt = itStore->second.iUseFulAmt;
	}
	m_csMutex.Unlock();


	return nAmt;
}

int CustomInfoMgrEx::GetUsefulPosi( const string& sInst, bool bLong )
{
	int nAmt = 0;

	m_csMutex.Lock();
	// �������
	auto it = m_mapDeferPosi.find(sInst);
	if( it != m_mapDeferPosi.end() )
	{
		nAmt = (bLong ? it->second.infoLong.iUsefulAmt : it->second.infoShort.iUsefulAmt);
	}
	m_csMutex.Unlock();

	return nAmt;
}

bool CustomInfoMgrEx::GetPosiInfo( DeferPosi& stPosi, const string& sInst )
{
	bool bRet = false;

	m_csMutex.Lock();
	// �������
	auto it = m_mapDeferPosi.find(sInst);
	if( it != m_mapDeferPosi.end() )
	{
		stPosi = it->second;
		bRet = true;
	}
	m_csMutex.Unlock();

	return bRet;
}

Rsp1020 CustomInfoMgrEx::Get1020()
{
	Rsp1020 rsp1020;

	m_csMutex.Lock();
	rsp1020 = m_rsp1020;
	m_csMutex.Unlock();

	return rsp1020;
}

void CustomInfoMgrEx::CalculateSurplus( DeferPosi& stDeferPosi, UINT uiLast )
{
	// ��¼�µıȽϼ۸�
	stDeferPosi.uiLastPrice = uiLast;

	// ������ӯ��
	if( stDeferPosi.infoLong.iCurrAllAmt > 0 )
	{
		stDeferPosi.infoLong.dPosi_PL = GetPosiSurplus( uiLast, 
			stDeferPosi.infoLong.dAvgPosPrice,
			stDeferPosi.infoLong.iCurrAllAmt,
			stDeferPosi.dUnite,
			true);
	}

	// ����ղ�ӯ��
	if( stDeferPosi.infoShort.iCurrAllAmt > 0 )
	{
		stDeferPosi.infoShort.dPosi_PL = GetPosiSurplus( uiLast, 
			stDeferPosi.infoShort.dAvgPosPrice,
			stDeferPosi.infoShort.iCurrAllAmt,
			stDeferPosi.dUnite,
			false);
	}
}
