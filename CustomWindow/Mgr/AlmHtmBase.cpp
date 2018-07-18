#include "AlmHtmBase.h"

#include "Global.h"
#include <algorithm>
#include "app.h"
#include "HJGlobalFun.h"

CAlmHtmBase::CAlmHtmBase(void)
{
	m_bInit = false;
	m_iBufSize = 1024;
}

CAlmHtmBase::~CAlmHtmBase(void)
{
}

void CAlmHtmBase::WriteDataToFile( const QString &csValue, bool bHashTable )
{
	QString csPath( GetFilePath() );

	// ��¼��������
	//::WritePrivateProfileString( (LPCWSTR)("Info"), m_csTitleType.toStdWString().c_str(), bHashTable ? "1" : "", csPath.toLatin1() );
	App::WriteServerProperty("Info", m_csTitleType, bHashTable ? "1" : "");
	
	// ��¼����
	//::WritePrivateProfileString( "Info", m_csTitle, csValue, csPath );
	App::WriteServerProperty("Info", m_csTitle, csValue);
}

QString CAlmHtmBase::GetFilePath()
{
	return g_Global.GetDataIniPath();
}

QString CAlmHtmBase::GetData( void )
{
	// ��ȡ�����ļ��ֶ�
	QString  str;

	App::GetServerProperty("Info", m_csTitle, str);

	return str;
}

bool CAlmHtmBase::LoadDataFromFile( void )
{
	QString str = GetData();
	if( !str.isEmpty() )
	{
		if( IsHashTable() )
		{
			HashtableMsg htm;
			
			if( htm.Parse(CHJGlobalFun::qstr2str(str)) == 0 && htm.size() > 0)
			{
				LoadFromHtm( htm );

				return true;
			}
		}
		else
		{
			ArrayListMsg alm;
			if( alm.Parse(str.toStdString()) == 0 && alm.size() > 0) // �����ɹ�
			{
				LoadFromAlm( alm );

				return true;
			}
		}
	}

	return false;
}

bool CAlmHtmBase::IsHashTable( void )
{
	QString  str;

	App::GetServerProperty("Info", m_csTitleType, str);
	return str.compare("1") == 0 ? true : false;
}

bool CAlmHtmBase::Initialize( const ArrayListMsg *pAlm /*= NULL */ )
{
	if( pAlm != NULL && pAlm->size() != 0 )
	{
		// ���ص��ڴ�
		LoadFromAlm( *pAlm );

		// д������
		WriteDataToFile( CHJGlobalFun::str2qstr(pAlm->ToString()), false );

		m_bInit = true;
	}
	else
	{
		if( LoadDataFromFile() || LoadDataFromServer() )
		{
			m_bInit = true;
		}
	}

	return m_bInit;
}

void CAlmHtmBase::EmptyFileInfo()
{
//	WriteDataToFile( QString::fromLatin1(""), false );
}
