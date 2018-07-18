/*
����Ʒ�ִ���Ĺ�����
������Ʒ�ִ����йص���Ϣ���ϵ��������ͬʱ�����˹��ܵĸĽ�
ʹ�ÿ���֧���������ļ��б���Alm����Htm�������ݣ���ǰֻ֧��Alm��
��ǿ�˶Դ�����쳣�Ĵ���

�����漰���Ķ�̫������⣬û��ȥ��CTraderCpMgr��m_vVariety��
��ʱֻ����Ϊ�����ݵĴ�����ѣ��Ժ�Ĵ�������Ե��������
�Ժ��ع���ʱ����ɽ����ݱ��浽����࣬����ʵ�����ݵĹ���
*/
#pragma once

#include "AlmHtmBase.h"
#include "StDef.h"
#include <QVector>

#define g_VarietyMgr CVarietyMgr::GetInstance()

class CVarietyMgr : public CAlmHtmBase
{
private:
	CVarietyMgr(void);
	~CVarietyMgr(void);

	CVarietyMgr( const CVarietyMgr&) ;            // ��ʵ��.
	CVarietyMgr& operator= ( const CVarietyMgr& ); // ��ʵ��.

public:
	static CVarietyMgr& GetInstance();

	// ��ʼ�������
	bool Initialize( QVector<VarietyInfo> &vVariety, const ArrayListMsg *pVariety_list = NULL );

	// ��ȡ����Ʒ������
	QString GetVarietyName( const QString &sID );

	// ��ȡ����Ʒ��ID
	QString GetVarietyID( const QString &sName );

	// ����Ʒ��ID��ȡƷ�����ƻ�ȡƷ����Ϣ
	const VarietyInfo* GetInfo( const QString &sKey, bool bID );

private:
	// �ӷ���������
	bool LoadDataFromServer( void );

	// ��ArrayListMsg���ؽ���Ʒ�ִ���
	void LoadFromAlm( const ArrayListMsg &alm );

	// ��HashtableMsg����
	void LoadFromHtm( HashtableMsg &htm );

	// ���ݽ���Ʒ��ID��ȡƷ����Ϣ
	const VarietyInfo* FindFromID( const QString &sID );

	// ���ݽ���Ʒ�����ƻ�ȡƷ����Ϣ
	const VarietyInfo* FindFromName( const QString &sName );

private:
	QVector<VarietyInfo> *m_vVariety;   // ����Ʒ�ִ���
};
