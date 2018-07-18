#pragma once

#include "DelayReqBase.h"

class CDelayReqHandler : public CReqHandlerBase
{
public:
	CDelayReqHandler(void);
public:
	~CDelayReqHandler(void);

	// �ⲿ���øú����������߳�
	bool Initlize( const string& sDelayTime );

	// ����ͻ�������Ϣ
	void AddCustomInfoReq();

	
public: // �㲥����---------------------------------------------------

	// ��������ֻ�����
	void HandleRecSpotOrder( BSFLAG eBSFlag );

	// ����������ڱ���
	void HandleRecDeferOrder( KPFLAG eKPFlag );

	// ������ս��ձ���
	void HandleRecDDAOrder( void );

	// ������������ֱ���
	void HandleRecMAOrder( void );


	// ��������ֻ�����
	void HandleRevSpotOrderCancel( BSFLAG eBSFlag );

	// ����������ڳ���
	void HandleRevDeferOrderCancel( KPFLAG eKPFlag );

	// ������ս��ճ���
	void HandleRevDDAOrderCancel( void );

	// ������������ֳ���
	void HandleRevMAOrderCancel( void );


	// �����ֻ��ɽ�
	void HandleSpotMatch( void );

	// �������ڳɽ�
	void HandleDeferMatch( void );

	// �����������ֳɽ�
	void HandleDDA_MAMatch( void );

	//��������ˢ���ʽ���Ϣ
	void RequestFundInfo();
protected:
	/*
	��д���ຯ�����������е�����
	*/
	void SendReq( const deque<ReqPara> &deqReq );

	/*
	��д���ຯ�����ж�һ�������Ƿ����
	*/
	bool IsUseless( ReqPara &stReqInQue, const ReqPara &stReqAdd );

	/*
	*/
	void AddReqCommon();

	/*
	*/
	void AddCustomInfoReq( bool bFund, bool bPosi, bool bStore, bool bCusInfo = false, bool bSurplus = false );

	const string GetReqPara( bool bReq );

private:
	bool m_bRspToBroadcast; // ���ս�����㲥�Ƿ�ˢ��
};

extern CDelayReqHandler g_DelayReqHandler;
