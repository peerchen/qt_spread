#pragma once

#include <QString>
#include <QMap>
#include "BroadcastPacketAndStruct.h"
typedef enum
{
	PriceType_Buy1,
	PriceType_Sell1,
	PriceType_Last,
	PriceType_LastSettle,
	PriceType_LastClose,
}EPriceType;

#define g_QuoMgr CQuotationMgr::GetInstance()

class CQuotationMgr
{
private:
	CQuotationMgr(void);
	~CQuotationMgr(void);

	CQuotationMgr( const CQuotationMgr&) ;            // ��ʵ��.
	CQuotationMgr& operator= ( const CQuotationMgr& ); // ��ʵ��.

public:
	static CQuotationMgr& GetInstance();

	// ��ʼ�������
	bool Initialize( map<string, QUOTATION> &mapQuotation );

	// ��ȡĳ��Ʒ�ָ�ʽ����ļ۸�
	int GetFormatPrice( QString &csPrice, const QString &sInsID, EPriceType eType );

	// ���ݼ۸����ͻ�ȡĳ��Ʒ�ֵ�ĳ���۸�����1�ۡ����¼ۣ�
	uint GetPrice( const QUOTATION &qt, EPriceType eType ) const;

	// ��ȡ����1��
	uint GetBSPrice( const QUOTATION &qt, EPriceType eType ) const;

	// ��ȡһ���Ϸ���
	uint GetValidePrice( const QUOTATION &qt ) const;

	double GetBSPriceEx( const QUOTATION &qt, EPriceType eType ) const;

	const QUOTATION* GetQuotation( const QString &sInsID ) const;

private:
	double m_fFactor;
	map<string, QUOTATION> *m_mapQuotation;
};
