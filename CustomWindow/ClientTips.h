#ifndef _CLIENTTIPS_H
#define _CLIENTTIPS_H

//#pragma once

#include "Struct.h"
#include <vector>
#include  <QMutex>
//#include <QMutexGuard>
class CClientTips
{
public:
	CClientTips(void);
public:
	~CClientTips(void);
};

class CTipsManager
{
public:
	CTipsManager();

	// ���һ����ʾ�����ҷ�����ӵ�λ��
	int Add( const TipsOrderInfo &TipsInfo );

	/*
	�����򷵻�0�������ڵ���vector��Ϊ�գ��򷵻�1������Ϊ���򷵻�-1
	*/
	int GetTips( TipsOrderInfo &TipsInfo, int nPos );

	void Clear();

	int GetSize();

	// ��¼�û����е���ʾ��Ϣ�������Ժ���ܸ��û��鿴��ʷ�����ʱ��
	vector<TipsOrderInfo> m_vecTips;
private:


	// ��
	QMutex	 m_csMutex;

	// ��¼��ǰ��ʾ����ʾ�ĸ���
	int m_iShowCount;
};

extern CTipsManager g_TipsManager;

#endif
