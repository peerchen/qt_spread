/*
��Լ����Ĺ�����
����Լ�����йص���Ϣ���ϵ��������ͬʱ�����˹��ܵĸĽ�
ʹ�ÿ���֧���������ļ��б���Alm����Htm�������ݣ���ǰֻ֧��Alm��
��ǿ�˶Դ�����쳣�Ĵ���

�����漰���Ķ�̫������⣬û��ȥ��CTraderCpMgr��m_vProdCode��
��ʱֻ����Ϊ�����ݵĴ�����ѣ��Ժ�Ĵ�������Ե��������
�Ժ��ع���ʱ����ɽ����ݱ��浽����࣬����ʵ�����ݵĹ���
*/
#pragma once

#include "AlmHtmBase.h"
#include "StDef.h"
#include <QVector>
#include "HJDef.h"

#define g_ProdCodeMgr CProdCodeMgr::GetInstance()

class CProdCodeMgr : public CAlmHtmBase
{
private:
	CProdCodeMgr(void);
	~CProdCodeMgr(void);

	CProdCodeMgr( const CProdCodeMgr&) ;            // ��ʵ��.
	CProdCodeMgr& operator= ( const CProdCodeMgr& ); // ��ʵ��.

public:
	static CProdCodeMgr& GetInstance();

	// ��ʼ�������
	bool Initialize( QVector<ProdCodeInfo> &vProdCode, const ArrayListMsg *pVariety_list /*= NULL */ );

	// ��ȡһ��Ʒ�ֵ���Ϣ
	const ProdCodeInfo* GetProdeCode( const QString &sInsID );

	MarketType GetMarketType( const ProdCodeInfo* pInfo );

private:
	// �ӷ���������
	bool LoadDataFromServer( void );

	// ��ArrayListMsg���غ�Լ����
	void LoadFromAlm( const ArrayListMsg &alm );

	// ��HashtableMsg����
	void LoadFromHtm( HashtableMsg &htm );

private:
	QVector<ProdCodeInfo> *m_vProdCode; //��������
};
