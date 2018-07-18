/*
�����������
*/
#pragma once

#include "..\Mgr\AlmHtmBase.h"
#include <QMap>
#include <QMultiMap>
#include <QPair>
#include "HJDef.h"

struct CodeValue
{
	QString  code_id              ; // ������    
	QString  code_desc            ; // ��������

	CodeValue(const QString &sCode_id,  const QString &sCode_desc) : code_id(sCode_id),code_desc(sCode_desc){}
};

#define g_CodeTableMgr CCodeTableMgr::GetInstance()

class CCodeTableMgr : public CAlmHtmBase
{
private:
	CCodeTableMgr( void );
	virtual ~CCodeTableMgr( void) ;

	CCodeTableMgr( const CCodeTableMgr&) ;            // ��ʵ��.
	CCodeTableMgr& operator= ( const CCodeTableMgr& ); // ��ʵ��.

public:
	static CCodeTableMgr& GetInstance();

	// ��ʼ�������
	bool Initialize( const ArrayListMsg *pCodeTable /*= NULL */ );

	// ��ȡһ�����
	QVector<const CodeValue*> GetGroupCode( const QString &sCodeType );

	// ��������ֶ�ID��������ֶε�ֵ
	QString GetCodeNameFromID( const QString &sCodeType, const QString &sCodeID);

	// ��������ֶ�ֵ����ȡ����ֶ�ID
	QString GetCodeIDFromName( const QString &sCodeType, const QString &sCodeName);

	// �����г���ȡ�佻�׷�ʽ
	void GetExchTypeName( QVector<const CodeValue*> &vecCode, MarketType eMarket );

	// ȥ�����׷�ʽ�в���Ҫ�ģ�exch_code��4061��������
	void EraseUselessExchType( QVector<const CodeValue*> &vecCode );

private:
	// �ӷ������������
    bool LoadDataFromServer( void );

	// ��HashtableMsg����
	void LoadFromHtm( HashtableMsg &htm );

	// ��ArrayListMsg����
	void LoadFromAlm( const ArrayListMsg &alm );

	// �Ƿ���Ҫ���ֶ�
	bool IsNeed( const QString &sValue );

private:
	typedef QMultiMap <QString, CodeValue>::const_iterator CIT; 
	typedef QPair<CIT, CIT> Range;
	QMultiMap<QString, CodeValue> m_mapCode;
};
