#pragma once

//#include "..\..\Framework\Utility\Include\Gess.h"

#include "ThreadInterface.h"
#include "Def.h"
#include <vector>

struct ReqPara
{
	int          nFailTry; // ʧ�ܺ��ԵĴ�����δ���ã�
	int     nFailWaitTime; // ʧ�ܺ���һ�εȴ��ļ��ʱ�䣨δ���ã�
	int      nCurReqCount; // ��ǰ���ԵĴ�����δ���ã�
	DWORD    dLastReqTick; // ��һ�������ʱ�䣨δ���ã�
	DWORD        dIniWait; // ��һ������ʱ�ȴ���ʱ�䣨δ���ã�

	EReqType eReqType;     // ��������
	vector<string>  vPara; // ��������

	ReqPara()
	{
		nFailTry = 2;
		nFailWaitTime = 0;
		nCurReqCount = 0;

#ifdef  _WIN32
                dLastReqTick = ::GetTickCount64();
#else
                //macx???
                dLastReqTick = ::mach_absolute_time();
#endif
		dIniWait = 0;
	}
};

class CReqHandlerBase : public CThreadInferface
{
public:
	CReqHandlerBase(void);
public:
	~CReqHandlerBase(void);

	// �������
	void AddReq( const ReqPara &stReq );

	// ��������ʱ��
	void SetDelayTime( int nTime );

protected:

	/*
	�ж���ӵ�һ�������Ƿ���Ч���ظ����߲���Ҫ��������ʵ��
	*/
	virtual bool IsUseless( ReqPara &stReqInQue, const ReqPara &stReqAdd );

	/*
	�������е����󣬸���ʵ��
	*/
	virtual void SendReq( const deque<ReqPara> &deqReq );

protected:
	int ThreadEntry();
	int End();
	void OnStart() { };
	void OnStop() { };

protected:
	std::deque<ReqPara> m_deqReq;
	CCondMutex	  m_deqCondMutex;
	int m_nDelayTime; // ���ڵ�ʱ�䣬����Ϊ��λ
};
