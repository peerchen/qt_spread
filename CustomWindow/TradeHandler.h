#pragma once

#include "Def.h"
#include "TradePacketAndStruct.h"

class CTradeHandler
{
public:
	CTradeHandler(void);
public:
	~CTradeHandler(void);

	// ��ȡ�ͻ���Ϣ
	int GetCustomInfo( Rsp1020 &rsp1020, Req1020& req1020, ETipsShowType eType, bool bBackground = false );

	// ��ȡ�������ˮ
	int GetCushAccessFlow( Rsp3010 &rsp3010, Req3010& req3010, ETipsShowType eType, bool bBackground = false );

protected:
	// �ж�һ��Ӧ���Ƿ�ɹ�
	inline bool IsTradeSus( const string &sRspID );

	/*
	�ж�һ�������Ƿ�ɹ�
	*/
	inline int IsSuccess( int nRet, const string &sRspCode );

	/*
	�ж��Ƿ���Ҫ��ʾ
	*/
	bool NeedShowTips( int nRet, ETipsShowType eType );
};

extern CTradeHandler g_TradeHandler;
