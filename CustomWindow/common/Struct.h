#pragma once

#include "Def.h"
#include <string>
#include <QString>
using namespace std;

#include "HJGlobalFun.h"

struct FundInfoS
{
	string sAllBalance;    // �ܶ�
	string sUseFulBal;     // ���ý��
	string sExchFrozeBal;  // ���׶����ʽ�
	string sPosiMargin;    // �ֲ�ӯ��
	string sSurplus;       // ����ӯ��
};

// ���彻������
struct TradeType
{
	BSFLAG eBS;
	KPFLAG eKP;

	TradeType()
	{
		eBS = BS_UKNOWN;
		eKP = KPF_UKNOWN;
	}

	TradeType( BSFLAG eBST, KPFLAG eKPT ) : eBS(eBST), eKP(eKPT) {};

	void Set( BSFLAG eBST, KPFLAG eKPT)
	{
		eBS = eBST;
		eKP = eKPT;
	}

	// �Ƿ�ƽ��
	bool IsCov() const
	{
		if( eKP == KPF_PING || eKP == KPF_PT || eKP == KPF_PY || eKP == KPF_FP )
			return true;
		else
			return false;
	}

	bool IsLong( bool &bLong ) const
	{
		if( eKP == KPF_KAI )
		{
			bLong = (eBS == BS_BUY ? true : false);
			return true;
		}
		else if( KPF_PING == eKP || KPF_PT == eKP )
		{
			bLong = (eBS == BS_BUY ? false : true);
			return true;
		}
		return false;
	}

	bool IsLong() const
	{
		if( eKP == KPF_KAI )
		{
			return (eBS == BS_BUY ? true : false);
		}
		else//( eKP == KPF_PING ||  eKP == KPF_PT )
		{
			return (eBS == BS_BUY ? false : true);
		}
	}

	bool IsValide() const
	{
		if( eBS != BS_UKNOWN )
			return true;
		else
			return false;
	}

	void Opposite()
	{
		if( KPF_KAI == eKP )
			eKP = KPF_PING;
		else if( KPF_PING == eKP )
			eKP = KPF_KAI;
	}

	bool IsDDAOrMA() const
	{
		if( eKP == KPF_MA || eKP == KPF_DDA )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

// �����ṹ
struct TipsOrderInfo
{
	TipsType eTipsType;
	string  sInsID;
	string  sExchID;
	QString csPrice;
	QString csAmount;
	QString csTips;
	QString csOrderNo;

	// Ϊ�˼���
	string sTitle;
	string sContent;

	TipsOrderInfo(){}

	TipsOrderInfo( const TipsType &type )
	{
		IniData(type);
	}

	// �����ڱ����ͳɽ���
	void IniData(const TipsType &type, const string &sInsID2, const string &sExchID2, const QString &csPrice2, const QString &csAmount2, const QString &sTips2 = "", const QString &csOrderNo2 = "")
	{
		eTipsType = type;
		sInsID = sInsID2;
		sExchID = sExchID2;
		csPrice = csPrice2;
		csAmount = csAmount2;
		csTips   = sTips2;
		csOrderNo = csOrderNo2;
	}

	// �����ڳ���
	void IniData(const TipsType &type, const QString &csOrderNo2)
	{
		eTipsType = type;
		csOrderNo = csOrderNo2;
	}

	// �����ڳ���
	void IniData(const TipsType &type)
	{
		eTipsType = type;
		if( type == E_Tips2_CreatePreOrder )
		{
			sTitle = "Ԥ������";
		}
	}
};
