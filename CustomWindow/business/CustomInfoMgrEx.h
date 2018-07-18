#pragma once

#include "StDef.h"
#include <map>
#include <unordered_map>
#include "TradePacketAndStruct.h"
struct QUOTATION;
struct FundInfoS;
struct FundInfo;

class CustomInfoMgrEx
{
public:
	CustomInfoMgrEx(void);
public:
	~CustomInfoMgrEx(void);

	// ����Ӧ����ˢ���ڴ���Ϣ
	void UpdateCustomInfo( const Rsp1020 &stRsp, const Req1020& req1020 );

	// �������һ������
	void HandleRecvQuotation( const QUOTATION& stQuotation );

	// ��ȡ�ܵĳֲ�ӯ��
	double GetTotalPosiSurplus();

	// ��ȡ�ֲ���Ϣ
	unordered_map<string, DeferPosi> GetPosi();

	// ��ȡ�����Ϣ
	unordered_map<string, StoreInfo> GetStore();

	// ��ȡ�ʽ���Ϣ
	FundInfoS GetFundInfoS();

	// ��ȡ�ʽ���Ϣ
	FundInfo GetFundInfo();

	// ��ȡ�ͻ�����
	string GetCustomName();

	// ��ȡ�������
	double GetUsefullBal();

	// ��ȡ���ÿ��
	int GetUsefulStore( const string& sInst );

	// ��ȡ���óֲ�
	int GetUsefulPosi( const string& sInst, bool bLong );

	// ��ȡһ��Ʒ�ֵĳֲ���Ϣ
	bool GetPosiInfo( DeferPosi& stPosi, const string& sInst );

	Rsp1020 Get1020();

	//���б��صĴ����Ϣ���㶳�ᱣ֤��
	double  CalculateFrozenCapital(const QString & ProdCode, const QString & ExchId  , double  orderCapital);
protected:
	// �ӱ����л�ȡ�ֲ���Ϣ���ڴ�
	void RefreshPosi( const HashtableMsg &hsmPosi );

	// �ӱ����л�ȡ�����Ϣ���ڴ�
	void RefreshStore( const HashtableMsg &htmStore );

	// ˢ���ʽ���Ϣ
	void RefreshFundInfo( const Rsp1020 &stRsp );

	// ��ȡ�ֲ�ӯ��
	double GetPosiSurplus( UINT uiLast, double dPosiAve, int iTotalHand, double dUnite, bool bLong );

	// ����ֲ�ӯ��
	void CalculateSurplus( DeferPosi& stPosiInfo, UINT uiLast );

protected:
	Rsp1020 m_rsp1020; // ����һ��ԭʼ����
	//map<string, DeferPosi>   m_mapDeferPosi; // �ֲ���Ϣ
	//map<string, StoreInfo>   m_mapStoreInfo; // �����Ϣ

	unordered_map<string, DeferPosi>   m_mapDeferPosi; // �ֲ���Ϣ
	unordered_map<string, StoreInfo>   m_mapStoreInfo; // �����Ϣ

	CGessMutex	 m_csMutex;
};

extern CustomInfoMgrEx g_CusInfo;
