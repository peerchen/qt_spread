/*
�������̻߳���
*/
#pragma once

//#include "..\..\Framework\Utility\Include\Gess.h"

#include "ThreadInterface.h"
#include "Def.h"
#include <vector>

#ifdef _WIN32
#else
#include <mach/mach_time.h>
#endif

struct RTReqPara
{
	int          nFailTry; // ʧ�ܺ��ԵĴ�����δ���ã�
	int     nFailWaitTime; // ʧ�ܺ���һ�εȴ��ļ��ʱ�䣨δ���ã�
	int      nCurReqCount; // ��ǰ���ԵĴ�����δ���ã�
	DWORD    dLastReqTick; // ��һ�������ʱ�䣨δ���ã�
	DWORD        dIniWait; // ��һ������ʱ�ȴ���ʱ�䣨δ���ã�

	EReqType eReqType;     // ��������
	vector<string>  vPara; // ��������

	RTReqPara()
	{
		nFailTry = 2;
		nFailWaitTime = 0;
		nCurReqCount = 0;
#ifdef _WIN32
                dLastReqTick = ::GetTickCount64();
#else
                dLastReqTick = ::mach_absolute_time();
#endif

		dIniWait = 0;
	}
};

class CRealTimeReqBase : public CThreadInferface
{
public:
	CRealTimeReqBase(void);
public:
	~CRealTimeReqBase(void);

	// �������
	void AddReq( const RTReqPara &stReq );

protected:
	/*
	�������е����󣬸���ʵ��
	*/
	virtual int SendReq( RTReqPara& req ) = 0;

protected:
	int ThreadEntry();
	int End();
	void OnStart() { };
	void OnStop() { };

protected:
	std::deque<RTReqPara> m_deqReq;
	CCondMutex	  m_deqCondMutex;
};
