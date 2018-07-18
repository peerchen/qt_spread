#pragma once

#include "TradePacketAndStruct.h"
#include <map>
#include <string>
#include <QString>
#include <QMap>

#define g_TiHuoMgr CTiHuoMgr::GetInstance()

class CTiHuoMgr
{
private:
	CTiHuoMgr(void);
	~CTiHuoMgr(void);

	CTiHuoMgr( const CTiHuoMgr&) ;            // ��ʵ��.
	CTiHuoMgr& operator= ( const CTiHuoMgr& ); // ��ʵ��.

public:
	// �������Ľṹ
	struct FrozeInfo
	{
		string    sInsID;
		quint32   nWeight;
	};

public:
	static CTiHuoMgr& GetInstance();

	// ��ʼ�������������ʼ��ʱ����
	void Initialize( );

	// �����û�������ѯ
	void HandleUserQuery( Rsp5101 &rsp5101 );

	// ����ǰ���������
	void HandleTodayTrade();

	// �����û�����
	void HandleCancel( const string &sLocalSheetNo );

	// ��ѯ�����Ϣ���ṩ���ⲿ����
	bool Query( Rsp5101 &rsp, const string &sBegin, const string &sEnd, const string &sLocalSheetNo );

	// ��¼���������֤�𶳽�
	void SetDay_take_margin( const string &sDay_take_margin );

protected:
	// ��ѯ���У�����ֻ���Ϊ��ʼ��ʱ����
	void QueryAll();

	// ���������ѯ���, mod by Jerry Lee, 2013-3-25
	void HandleQueryResult( Rsp5101 &rsp5101, bool bCancel = true/*�Ƿ�����*/ );

	// ˢ�������֤�𶳽�
	void RefreshTakeFroze();

	/*
	������Ķ�����߽ⶳ����HandleQueryResult����
	sOrderNo �������
	sInsID ���Ʒ��
	nWeight ��������
	bFroze �Ƿ񶳽ᣬ����Ϊ�ⶳ
	*/
	bool HandleCalculate( const string &sOrderNo, const string sInsID, int nWeight, bool bFroze );

private:
	QMap<string, FrozeInfo> m_mapFroze; // ��¼����Ķ�����Ϣ

	string m_sDay_take_margin; // ���������֤�𶳽�
};
