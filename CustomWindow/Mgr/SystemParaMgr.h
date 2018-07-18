#pragma once

#include <QString>
#include <QMap>


#define g_SysParaMgr CSystemParaMgr::GetInstance()

class CSystemParaMgr
{
private:
	CSystemParaMgr(void);
	~CSystemParaMgr(void);

	CSystemParaMgr( const CSystemParaMgr&) ;            // ��ʵ��.
	CSystemParaMgr& operator= ( const CSystemParaMgr& ); // ��ʵ��.

public:
	static CSystemParaMgr& GetInstance();

	void Initialize( QMap<QString, QString> &mapSystemPara );

	// ���ݲ���ID��ȡϵͳ������ֵ�������ȡʧ�ܣ�����Ĭ��ֵ������ɹ������¼���ڴ�
	QString GetParaValue( const QString &sParaID, const QString &sDefaultValue = "" );

	//void ShowKeyBoard(CWnd* pWnd, const int nID);
	void HideKeyBoard();
private:
	QMap<QString, QString> *m_mapSystemPara; // ϵͳ����
	//CKeyBoard * m_pKeyBoard;
};
