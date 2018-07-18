/*
ֹӯֹ����Ϣ�Ĺ�����
����ֹӯֹ�𵥴������ļ��ļ����Լ��ɽ�ʱ����ֹӯֹ��

ֹӯֹ�������ʽ
����۸� �ȽϷ�ʽ �Ƚϼ۸� ʱ����
����۸����¼ۡ���һ�ۻ�����һ��
�ȽϷ�ʽ�����ڻ���ڡ�С�ڻ����
�Ƚϼ۸�CmpPrice���������Ƚϼ۸�BaseCmpPrice�����ϻ��߼�ȥ������λ�������ڿ����ʱ�����ˡ�ÿ�ʿ��ּ۵���3����λʱ����������
          ��ʱ������Ƚϼ۸�Ϊ��ÿ�ʿ��ּۡ���ֹ�𵥵ıȽϼ۸� = ÿ�ʿ��ּ� - 3*��λ

*/
#pragma once


#include "PreOrder/PreOrderDef.h"
#include "BroadcastPacketAndStruct.h"
#include <map>
#include <QVector>
#include <QString>

#define g_StopPLMgr CStopPLMgr::GetInstance()

class CStopPLMgr
{
private:
	CStopPLMgr(void);
	~CStopPLMgr(void);

	CStopPLMgr( const CStopPLMgr&) ;            // ��ʵ��.
	CStopPLMgr& operator= ( const CStopPLMgr& ); // ��ʵ��.

public:
	static CStopPLMgr& GetInstance();

	// ��ʼ��ֹ��ֹӯ������Ϣ
	void Initialize( );

	// �����û�ֹӯֹ������
	void LoadSetting();

	// �����Ѵ���ɽ���
	void LoadHandledMatchNo();

	// ������ܵ�һ�����ڳɽ���
	void HandleOpenPosiMatch( const DeferMatch &stMatch, bool bLong );

	EPLCmpType GetCmpType();
	EPLAskPriceType GetAskPriceType();
	short GetAskPriceAjust();
	bool IsServer();
	const map<string, PLInfo>* GetInfo();

private:
	// ��ȡһ��Ʒ�ֵ�ֹ��ֹӯ������Ϣ
	PLInfo* GetPLInfo( const string &sInsID );

	// ��û����Ƚϼ۸�
	bool GetBaseCmpPrice( double &dBaseCmpPrice, EPLCmpType eCmpType, const DeferMatch &stMatch, bool bLong );

	// ���һ��Ԥ��
	int AddPreOrder( PreOrderStruct &stPreOrder );

	// ����ֹ�𵥹��ú���
	void SetStopLoss( PreOrderStruct &stPreOrder, double dCmpPrice, double fPriceUnite, bool bLong, short nLossAjust );

	// ���ݱ����۸����ͻ�ȡ�����ж�Ӧ�ֶε�ָ��
	const unsigned int* GetHQPricePointer( EQTType eAskPriceType, const string &sInsID );

	// ��ñ���ʱ�ı������ͣ���ǰ��Ҫ��Ԥ�񵥶Ի�����ʾ�����ֶ�ʱҪ�õ�
	EQTType GetPreOrderAskPriceType( EPLAskPriceType eAskPriceType, bool bLong );

	//
	short GetLossAjust( const PLInfo *plInfo );

	// ����ֹ�������λ��ȡֹ��۸�
	double GetLossPrice( short Ajust, double dCmpBasePrice, bool bLong, double fPriceUnite );

	//
	bool IsHandled( const QString &sMatchNo );

	// ���Ѵ���ĳɽ���ˮд�뵽�����ļ�
	bool WriteMatchNo();

	void AddMatchNo( const QString &sMatchNo );

private:
	map<string, PLInfo> m_mapInfo; // ��¼ֹӯֹ��������Ϣ
	EPLCmpType m_eCmpType;    // �Ƚϣ��������۸����ͣ�����Ϊÿ�ʿ��ּۡ��ֲ־���
	EPLAskPriceType m_eAskPriceType; // ƽ�ֱ����۸����ͣ�����Ϊ���¼ۡ������
	short m_iAskPriceAjust; // �����۸������λ
	bool m_bUseServer;

	QVector<QString> m_vecHandledMatchNo; // ��¼�Ѿ����͹�ֹӯֹ�𵥵ĳɽ���
	map<QString, QString> m_mapHandledMatchNo; // ��¼�Ѿ����͹�ֹӯֹ�𵥵ĳɽ���
	bool m_bMatchNoChange; // ���m_vecHandledMatchNo�������ļ����غ��Ƿ�仯
};
