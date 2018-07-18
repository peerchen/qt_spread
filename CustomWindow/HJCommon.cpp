#include "HJCommon.h"
#include "Global.h"
#include "TraderCpMgr.h"
#pragma execution_character_set("utf-8")

CHJCommon::CHJCommon(void)
{
}

CHJCommon::~CHJCommon(void)
{
}
// ����������־��ȡ�ֻ��Ľ�������ID
QString CHJCommon::GetSpotId( const QString &sBuySellFlag )
{
	return sBuySellFlag == "b" ? CONSTANT_EXCH_CODE_SPOT_BUY : CONSTANT_EXCH_CODE_SPOT_SELL;
}
// ����������־��ȡԶ�ڵĽ�������ID
QString CHJCommon::GetForwardId( const QString &sBuySellFlag  )
{
	return sBuySellFlag == "b" ? CONSTANT_EXCH_CODE_FORWARD_LONG : CONSTANT_EXCH_CODE_FORWARD_SHORT;
}
// ���ݿ�ƽ��������־��ȡ���ڵĽ�������ID "0"��ʾ���� "b"��ʾ���
QString CHJCommon::GetDeferId( const QString &sOffFlag, const QString &sBuySellFlag )
{
	return sOffFlag == "0" ? (sBuySellFlag == "b" ? CONSTANT_EXCH_CODE_DEFER_OPEN_LONG : CONSTANT_EXCH_CODE_DEFER_OPEN_SHORT) : (sBuySellFlag == "b" ? CONSTANT_EXCH_CODE_DEFER_COV_SHORT : CONSTANT_EXCH_CODE_DEFER_COV_LONG);
}
// ����������־��ȡ���ڽ��յĽ�������ID
QString CHJCommon::GetDDAOrderId( const QString &sBuySellFlag )
{
	return sBuySellFlag == "b" ? CONSTANT_EXCH_CODE_DELIVERY_LONG : CONSTANT_EXCH_CODE_DELIVERY_SHORT;
}
// ����������־��ȡ���������ֵĽ�������ID
QString CHJCommon::GetMAOrderId( const QString &sBuySellFlag )
{
	return sBuySellFlag == "b" ? CONSTANT_EXCH_CODE_MIDD_DELIVERY_LONG : CONSTANT_EXCH_CODE_MIDD_DELIVERY_SHORT;
}

bool CHJCommon::IsLongPosition( const QString &sBuySellFlag )
{
	return sBuySellFlag == "b" ? true : false;
}


QString CHJCommon::GetDDAMatchId( const QString &sMiddleFlag, const QString &sBuySellFlag )
{
	return sMiddleFlag == "0" ? (sBuySellFlag == "b" ? "4045" : "4046") : (sBuySellFlag == "b" ? "4047" : "4048");
}

// ���ݱ���״̬��δ�ɽ������ж�һ�ʱ����Ƿ���Ч
bool CHJCommon::CheckEntrFlowIsInvalidate( const QString &sState, int iRemainAmount )
{
	// ���״̬����"�����걨","�ѱ���","���ֳɽ�"��"��Ч"��һ�֣���Ϊ��Ч����
	if(sState != "1" && sState != "o" && sState != "p" && sState != "2")
	{
		return true;
	}

	// ���״̬��Ч������δ�ɽ�����������0����Ϊ��Ч����
	if(iRemainAmount <= 0)
	{
		return true;
	}

	return false;
}

QString CHJCommon::GetOrderType( const QString &sLocalOrderNo, const QString &sStateId )
{
	if(sStateId == "2")
	{
		return QString("ʧ�ܱ���");
	}
	else
	{
		//char  ch  = sLocalOrderNo.at[sLocalOrderNo.length()-2];
		//return ch == '8'? QString("ǿƽ����"): QString("��������");
		QString str1 = "ǿƽ����";
		QString str2 = "��������";
		return sLocalOrderNo.at(sLocalOrderNo.length() - 2) == '8'? str1:str2 ;

	}
}
// ����ĳһ��Ʒ����n������Ҫ��������
double CHJCommon::CalculateFare( const QString &sProdCode, double fUnite, double fPrice, const FareInfo &fi, int iHand /*= 1*/ )
{
	if (fi.fare_value.isEmpty())
	{
		return 0;
	}

	double fFare_Value = fi.fare_value.toFloat()*iHand;

	if (fi.fare_mode_id == CONSTANT_CT_FARE_MODE_BAL) // �����ģʽ���㱣֤��
	{
		if (sProdCode == "Ag99.9" || sProdCode == CONSTANT_AGTD) // ����ǰ���
		{
			return fFare_Value * fPrice * fUnite / 1000.0;
		}
		else
		{
			return fFare_Value * fPrice * fUnite;
		}
	}
	else if (fi.fare_mode_id == CONSTANT_CT_FARE_MODE_WEIGHT) // ����(Ԫ/��)
	{
		return fFare_Value * fUnite;
	}
	else if (fi.fare_mode_id == CONSTANT_CT_FARE_MODE_HAND) // ����(Ԫ/��)
	{
		return fFare_Value;
	}
	else
	{
		return 0;
	}
}



double CHJCommon::HandToGram( const QString &sProdCode, double dMeasureUnit )
{
	if (sProdCode == "Ag99.9" || sProdCode == "Ag(T+D)")
	{
		// ����ǰ��� ��ǧ�˼���
		dMeasureUnit = dMeasureUnit / 1000.00;
	}
	
	return dMeasureUnit;
}

double CHJCommon::CalculateFareEx( const QString &sProdCode, double fUnite, double dExchBal, const FareInfo &fi, int iHand, bool bMatch /*= false*/ )
{
	if (fi.fare_value.isEmpty())
	{
		return 0;
	}

	// ��ʼ���ܶ�Ϊ��������ȡ�ı���
	double fFare_Value = fi.fare_value.toFloat();

	if (fi.fare_mode_id == CONSTANT_CT_FARE_MODE_BAL) // �����ģʽ���㱣֤��
	{
		fFare_Value = dExchBal * fFare_Value; 
	}
	else if (fi.fare_mode_id == CONSTANT_CT_FARE_MODE_WEIGHT) // ����(Ԫ/��)
	{
		fFare_Value = iHand * fUnite * fFare_Value;
	}
	else if (fi.fare_mode_id == CONSTANT_CT_FARE_MODE_HAND) // ����(Ԫ/��)
	{
		fFare_Value = iHand * fFare_Value;
	}
	else
	{
		fFare_Value = 0.00;
	}

	// ������������ȵ����� 876.82499999999993
	//if(bMatch) fFare_Value += 0.00000001;
	fFare_Value += 0.00000001;

	return CHJGlobalFun::DoubleFormat(fFare_Value);
}

ExchFare CHJCommon::GetExchFareValueByExchBal( const QString &sProdCode, double dUnite, double dExchBal, int iHand, const FareInfo &fiBourse, const FareInfo &fiMember, bool bMatch /*= false*/)
{
	ExchFare exch_fare;
	exch_fare.iVolume = iHand;

	// ���㽻��������
	exch_fare.dBourseFare = CalculateFareEx(sProdCode, dUnite, dExchBal, fiBourse, iHand, bMatch);

	// �����Ա�յ��ܷ��÷���
	exch_fare.dMemberFare = CalculateFareEx(sProdCode, dUnite, dExchBal, fiMember, iHand, bMatch);

	// �ж����õĻ�Ա�����Ƿ�������������ʣ��ݲ�������

	// ����
	return exch_fare;
}


//#include "ScrollEditEx.h"
#include "Mgr/QuotationMgr.h"
bool CHJCommon::SetPriceControl( CScrollEditEx &editCtl, const QString &sInsID )
{
	const QUOTATION* pQT  = g_QuoMgr.GetQuotation(sInsID);
	return SetPriceControl( editCtl, sInsID, pQT );
}

bool CHJCommon::SetPriceControl( CScrollEditEx &editCtl, const QString &sInsID, const QUOTATION* pQT )
{
	if( pQT != NULL )
	{
		//if( sInsID == "Ag99.9" || sInsID == "Ag(T+D)" )
			//editCtl.IniInt(CNumCommn::e_both, 2, pQT->m_uiLowLimit/g_Global.m_dQTFactor, pQT->m_uiHighLimit/g_Global.m_dQTFactor, false);
            //editCtl.IniInt(CNumCommn::e_both, 2, 0, 100000, false);
		//else
			//editCtl.IniFloat(CNumCommn::e_both, 2, 0.01, 2, pQT->m_uiLowLimit/g_Global.m_dQTFactor, pQT->m_uiHighLimit/g_Global.m_dQTFactor, false);
            //editCtl.IniFloat(CNumCommn::e_both, 2, 0.01, 2, 0, 100000, false);

		return true;
	}
	else
	{
		return false;
	}
}

bool CHJCommon::IsDefer( const QString &sInst )
{
	const ProdCodeInfo* pInfo = NULL;
	for(size_t i = 0; i < g_TraderCpMgr.m_vProdCode.size(); i++)
	{
		pInfo = &g_TraderCpMgr.m_vProdCode.at(i);
		if( pInfo->prod_code == sInst )
		{
			if( pInfo->market_id == CONSTANT_B_MARKET_ID_DEFER )
				return true;
		}	
	}

	return false;
}

