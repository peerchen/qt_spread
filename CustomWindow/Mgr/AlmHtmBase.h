#pragma once

#include "ArrayListMsg.h"
#include "HashtableMsg.h"

#include <QString>
class CAlmHtmBase
{
public:
	CAlmHtmBase(void);
public:
	~CAlmHtmBase(void);

	// ��ʼ��
	virtual bool Initialize( const ArrayListMsg *pAlm /*= NULL */ );

	// д�����ݵ��ļ�
	void WriteDataToFile( const QString &csValue, bool bHashTable );

	// ��������ļ��������Ϣ
	void EmptyFileInfo( );

protected:
	// �ӷ������������
	virtual bool LoadDataFromServer( void ) = 0;

	// ��ArrayListMsg���أ���������д
	virtual void LoadFromAlm( const ArrayListMsg &alm ) = 0;

	// ��HashtableMsg���أ���������д
	virtual void LoadFromHtm( HashtableMsg &htm ) = 0;

private:
	// �ӱ����ļ��������
	bool LoadDataFromFile( void );

	// ��ȡ�ļ�·��
	QString GetFilePath( );

	// �жϱ��ش洢�����ݵ����ͣ���HashTable��Ϊtrue����ArrayListMsg��Ϊfalse��
	bool IsHashTable( void );

	//
	QString GetData( void );

protected:
	QString m_csTitle;
	QString m_csTitleType;
	int m_iBufSize;

private:
	bool m_bInit;
};
