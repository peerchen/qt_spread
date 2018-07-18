#pragma once

#include <QMap>
#include "StDef.h"
#define g_PosiMgr CPosiMgr::GetInstance()

class CPosiMgr
{
private:
	CPosiMgr(void);
	~CPosiMgr(void);

	CPosiMgr( const CPosiMgr&) ;            // ��ʵ��.
	CPosiMgr& operator= ( const CPosiMgr& ); // ��ʵ��.

public:
	static CPosiMgr& GetInstance();

	void Initialize( QMap<QString, DeferPosi> &mapDeferPosi, QMap<QString, StoreInfo> &mapStoreInfo );

	const DeferPosi* GetPosiInfo( const QString &sInsID );

	// ��ȡĳ��Ʒ��ĳ�������ϵĳֲ���Ϣ
	const DeferPosiInfo* GetPosiInfo( const QString &sInsID, const QString &sExchID );

	// ��ȡĳ��Ʒ��ĳ�������ϵĳֲ���Ϣ
	const DeferPosiInfo* GetPosiInfo( const QString &sInsID, bool bLong );

	// ���ݽ�������ID�ж��Ƕ�ֻ��ǿղ�
	bool IsLong( bool &bLong, const QString &sExchID );

	// ��ÿ����Ϣ
	const StoreInfo* GetStoreInfo( const QString &sInsID );

private:
	// �ֲ���Ϣ
	QMap<QString, DeferPosi> *m_QMapDeferPosi;

	// �����Ϣ
	QMap<QString, StoreInfo> *m_QMapStoreInfo; // 
};
