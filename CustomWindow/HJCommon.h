#pragma once

#include "HJConstant.h"
#include "HJGlobalFun.h"
#include <QString>


#define CONSTANT_OPEN_FARE_ID          "103"  // ����������ID
#define CONSTANT_COV_FARE_ID           "104"  // ƽ��������ID

#define CONSTANT_FTD_T_MARGIN_LONG       "105"  // ����ֱ�֤��
#define CONSTANT_FTD_T_MARGIN_SHORT      "125"  // ���ղֱ�֤��

#define CONSTANT_SPOT_BUY_FARE_ID      "101"  // �ֻ�����������ID
#define CONSTANT_SPOT_SELL_FARE_ID      "102"  // �ֻ�����������ID

#define CONSTANT_EXCH_BAIL_FARE_ID     "105"  // ���ױ�֤��IDID
#define CONSTANT_OVER_SPARE_BAIL_ID    "106"  // ��̱�������

#define CONSTANT_FTD_T_DELI_MARGIN    "108"  // ��̱�������

#define CONSTANT_CT_FARE_MODE_BAL      "1"  // �շ�ģʽ ���  �ɽ�������
#define CONSTANT_CT_FARE_MODE_WEIGHT   "2"  // �շ�ģʽ ����  ����(Ԫ/��)
#define CONSTANT_CT_FARE_MODE_HAND     "3"  // �շ�ģʽ ����  ����(Ԫ/��)

#define CONSTANT_AGTD                  "Ag(T+D)"  // ���� Ag(T+D)
#define CONSTANT_PT9995                "Pt99.95"  // ���� Pt99.95

struct FareInfo
{
	// �շ�ģʽ
	QString fare_mode_id;

	// �շ�ģʽ����
	QString fare_mode_name;

	/// ����ֵ
	QString fare_value;
};

struct ExchFare
{
	double dBourseFare;
	double dMemberFare;

	int iVolume;

	ExchFare()
	{
		dBourseFare = 0.00;
		dMemberFare = 0.00;
		iVolume = 0;
	}

	double getBourseFare45()
	{
		return CHJGlobalFun::DoubleFormat(dBourseFare);
	}

	double getMemberFare45()
	{
		return CHJGlobalFun::DoubleFormat(dMemberFare);
	}

	// ��ð�ÿ��Ϊ��������Ľ��������úͻ�Ա���õĺϣ�һ�㱨���걨��
	double sumSingle()
	{
		double dBourseValue = CHJGlobalFun::DoubleFormat(dBourseFare);
		double dMemberValue = CHJGlobalFun::DoubleFormat(dMemberFare);
		double dTotal = dBourseValue + dMemberFare;

		if(iVolume > 0)
			dTotal = CHJGlobalFun::DoubleFormat(dTotal / iVolume, 2, ROUND_UP) * iVolume;

		return dTotal;
	}

	double sum()
	{
		return CHJGlobalFun::DoubleFormat(dBourseFare) + CHJGlobalFun::DoubleFormat(dMemberFare);
	}
};

class CScrollEditEx;
struct QUOTATION;

class CHJCommon
{
public:
	CHJCommon(void);
public:
	~CHJCommon(void);

	// �������������ȡ�ֻ���������id
	static QString GetSpotId(const QString &sBuySellFlag);

	// �������������ȡԶ�ڽ�������id
	static QString GetForwardId(const QString &sBuySellFlag );

	// ������������Ϳ�ƽ��־��ȡ���ڽ�������id
	static QString GetDeferId(const QString &sOffFlag, const QString &sBuySellFlag);

	// �������������ȡ���ڽ��ս�������ID
	static QString GetDDAOrderId(const QString &sBuySellFlag);

	// �������������ȡ�����ֽ�������ID
	static QString GetMAOrderId(const QString &sBuySellFlag);

	// �������ܣ����ݷ���ģ��,����ID�ķ��ü���ģʽ������Ӧ�ķ���
	static double CalculateFareEx( const QString &sProdCode, double fUnite, double dExchBal, const FareInfo &fi, int iHand, bool bMatch = false );

	// �������ܣ����ݷ���ID�ķ��ü���ģʽ������Ӧ��Ա���úͽ���������
	static ExchFare GetExchFareValueByExchBal(const QString &sProdCode, double dUnite, double dExchBal, int iHand, const FareInfo &fiBourse, const FareInfo &fiMember, bool bMatch = false);

	// ����������־�ж��Ƿ��Ƕ�֣��ݶ��������ڽ��պ������ֵ��жϣ�
	static bool IsLongPosition(const QString &sBuySellFlag);

	//
	static QString GetDDAMatchId(const QString &sMiddleFlag, const QString &sBuySellFlag);

	// �жϱ�����ˮ�Ƿ���Ч
	static bool CheckEntrFlowIsInvalidate( const QString &sState, int iRemainAmount );

	// ��ȡ��������
	static QString GetOrderType(const QString &sLocalOrderNo, const QString &sStateId);

	// ����ĳ��Ʒ��ÿ����ȡ�ı�֤�� sProdCode����Լ���룩 fUnite��ÿ�ֵ������� fPrice����Ʒ�ֵļ۸� fi����Ʒ�ֵķ�����Ϣ��
	static double CalculateFare( const QString &sProdCode, double fUnite, double fPrice, const FareInfo &fi, int iHand = 1 );

	// ��ȡĳ��Ʒ�ֵ�һ�ֵĿ���
	static double HandToGram( const QString &sProdCode, double dMeasureUnit );

	//
	static bool SetPriceControl( CScrollEditEx &editCtl, const QString &sInsID );

	static bool SetPriceControl( CScrollEditEx &editCtl, const QString &sInsID, const QUOTATION* pQT );

	// �ж�һ��Ʒ���Ƿ�������
	static bool IsDefer( const QString &sInst );
};
