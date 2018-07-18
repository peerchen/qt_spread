#pragma once

//struct Rsp2040;
#include "TradePacketAndStruct.h"

#define g_CusInfoMgr CCustomInfoMgr::GetInstance()

class CCustomInfoMgr
{
private:
	CCustomInfoMgr(void);
	~CCustomInfoMgr(void);

	CCustomInfoMgr( const CCustomInfoMgr&) ;            // ��ʵ��.
	CCustomInfoMgr& operator= ( const CCustomInfoMgr& ); // ��ʵ��.

public:
	static CCustomInfoMgr& GetInstance();

	// ��ʼ�������
	bool Initialize( Rsp1020 *pRsp1020 );
    
	// ��ÿͻ���Ϣ
	const Rsp1020 &GetInfo( void );

	// ��ÿ����Ϣ
	HashtableMsg GetStorInfo( void );

	// ��óֲ���Ϣ
	const HashtableMsg &GetPosiInfo( void );

private:
	Rsp1020 *m_rsp1020;
};
