#include "VarietyMgr.h"
#include "TranMsg.h"
#include "HJGlobalFun.h"

CVarietyMgr& CVarietyMgr::GetInstance()
{
	static CVarietyMgr theSingleton;
	return theSingleton;
}

CVarietyMgr::CVarietyMgr(void)
{
	m_vVariety = NULL;
	m_csTitle = "variety";
	m_csTitleType = "VarietyDataType";
}

CVarietyMgr::~CVarietyMgr(void)
{
}

bool CVarietyMgr::Initialize( QVector<VarietyInfo> &vVariety, const ArrayListMsg *pVariety_list /*= NULL */ )
{
	m_vVariety = &vVariety;
	m_vVariety->clear();

	return CAlmHtmBase::Initialize( pVariety_list );
}

// �ӷ���������
bool CVarietyMgr::LoadDataFromServer( void )
{
	Rsp1004 rsp;
	if( CTranMsg::Handle1004( rsp ) )
	{
		if( rsp.htm_variety_list.size() > 0 )
		{
			// д������
			WriteDataToFile(CHJGlobalFun::str2qstr( rsp.htm_variety_list.ToString()), true );

			// ���ص��ڴ�
			LoadFromHtm( rsp.htm_variety_list );

			return true;
		}
	}

	return false;
}

// ��ArrayListMsg���ؽ���Ʒ�ִ���
void CVarietyMgr::LoadFromAlm( const ArrayListMsg &alm )
{
	for( size_t i = 0; i < alm.size(); i++ ) //�������ؽ��
	{  
		VarietyInfo varietyinfo;
		varietyinfo.destroy_flag = CHJGlobalFun::str2qstr(alm.GetStringEx(i, 7));
		if( varietyinfo.destroy_flag == "0" )
		{
			varietyinfo.variety_id   = CHJGlobalFun::str2qstr(alm.GetStringEx(i, 0));
			varietyinfo.name         = CHJGlobalFun::str2qstr(alm.GetStringEx(i, 1));
			varietyinfo.abbr         = CHJGlobalFun::str2qstr(alm.GetStringEx(i, 2));
			varietyinfo.variety_type = CHJGlobalFun::str2qstr(alm.GetStringEx(i, 3));
			varietyinfo.min_pickup   = alm.GetValue<double>(i, 4);
			varietyinfo.pickup_base  = alm.GetValue<double>(i, 5);
			varietyinfo.weight_unit  = CHJGlobalFun::str2qstr(alm.GetStringEx(i, 6));

			m_vVariety->push_back(varietyinfo);
		}
	}
}

// ��ȡ����Ʒ������
QString CVarietyMgr::GetVarietyName( const QString &sID )
{
	const VarietyInfo* pInfo = FindFromID( sID );
	return (pInfo != NULL ) ? pInfo->name : "";
}

// ���ݽ���Ʒ��ID��ȡƷ����Ϣ
const VarietyInfo* CVarietyMgr::FindFromID( const QString &sID )
{
	for( size_t i = 0; i < m_vVariety->size(); i++ )
	{
		if( m_vVariety->at(i).variety_id == sID )
			return &m_vVariety->at(i);
	}

	return NULL;
}

const VarietyInfo* CVarietyMgr::FindFromName( const QString &sName )
{
	for( size_t i = 0; i < m_vVariety->size(); i++ )
	{
		if( m_vVariety->at(i).name == sName )
			return &m_vVariety->at(i);
	}

	return NULL;
}

// ��HashtableMsg����
void CVarietyMgr::LoadFromHtm( HashtableMsg &htm )
{
	for( size_t i = 0; i < htm.size(); i++ )
	{
		VarietyInfo varietyinfo;
		if( htm.GetString(i,"destroy_flag") == "0" ) // ���������־Ϊ0�������
		{
			varietyinfo.variety_id   = CHJGlobalFun::str2qstr(htm.GetString(i,"variety_id"));
			varietyinfo.name         = CHJGlobalFun::str2qstr(htm.GetString(i,"name"));
			varietyinfo.abbr         = CHJGlobalFun::str2qstr(htm.GetString(i,"abbr"));
			varietyinfo.variety_type = CHJGlobalFun::str2qstr(htm.GetString(i,"variety_type"));
			varietyinfo.min_pickup   = htm.GetDouble(i,"min_pickup");
			varietyinfo.pickup_base  = htm.GetDouble(i,"pickup_base");
			varietyinfo.weight_unit  = CHJGlobalFun::str2qstr(htm.GetString(i,"weight_unit"));

			m_vVariety->push_back(varietyinfo);
		}
	}
}

const VarietyInfo* CVarietyMgr::GetInfo( const QString &sKey, bool bID )
{
	return bID ? FindFromID(sKey) : FindFromName(sKey);
}

QString CVarietyMgr::GetVarietyID( const QString &sName )
{
	const VarietyInfo* pInfo = FindFromName( sName );
	return (pInfo != NULL ) ? pInfo->variety_id : "";
}



