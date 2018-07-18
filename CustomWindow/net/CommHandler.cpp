
#include "CommHandler.h"
#include "TcpShortCp.h"
#include "ProcessInterfaceB1C.h"
#include "ProcessInterfaceB2C.h"
#include "ProcessInterfaceB3C.h"
#include "ProcessInterfaceB4C.h"
#include "ProcessInterfaceYC.h"
#include "BroadcastPacket.h"

#include "ProtocolConnectPoint.h"
#include "Global.h"
//#include "MyLogEx.h"
#include "app.h"
//#include "AutoConnector.h"

// ��ʼ��
CCommHandler* CCommHandler::s_pCommHandler = nullptr;


CCommHandler* CCommHandler::Instance()
{
    if (s_pCommHandler == nullptr)
    {
       s_pCommHandler = new CCommHandler();
    }

    return s_pCommHandler;
}


CCommHandler::CCommHandler(void) 
: m_pCpInterfaceYC(0)
, m_pCpInterfaceB1C(0)
, m_pCpInterfaceB2C(0)
, m_pCpInterfaceB3C(0)
, m_pCpInterfaceB4C(0)
{
    m_pConfig = new CConfigImpl();

	m_nB1CPos = -1;
	m_nB2CPos = -1;
	m_nB3CPos = -1;
	m_nB4CPos = -1;
	m_pCpInterfaceB2CVip = nullptr;
}

CCommHandler::~CCommHandler(void)
{
    Finish();

   if (m_pConfig != nullptr)
    {
        delete m_pConfig;
        m_pConfig = nullptr;
    }
}

//�ͻ���Э�����ӵ����ӳɹ���ص�
int CCommHandler::OnConnect(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort, 
                            const string& sPeerIp, int nPeerPort, int nFlag)
{
	
	return 0;
}

//�����Э�����ӵ���յ����Ӻ�ص�
int CCommHandler::OnAccept(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort,
                           const string& sPeerIp, int nPeerPort)
{
	if (ulKey >= EnumKeyUnknown)
		return -1;
	
	return 0;
}

int CCommHandler::OnLogin( const unsigned long& ulKey,const string& sLocalIp, int nLocalPort,
                          const string& sPeerIp, int nPeerPort,int nFlag)
{
	return 0;
}

int CCommHandler::OnClose(const unsigned long& ulKey, const string& sLocalIp, int nLocalPort,
                          const string& sPeerIp, int nPeerPort)
{
	if (ulKey >= EnumKeyUnknown)
		return -1;

	return 0;
}

// ���̻����ӵ��������ʼ��
int CCommHandler::Init(const QString& strPath)
{
	m_nCurServerPos = 0;

    //��pCfg��map���ͣ�����������ļ���key��value��ӳ���ϵ�ŵ�m_Props
	if (m_pConfig->Load(strPath.toStdString()) != 0)
	{
		return -1;
	}

	// ��ʼ����־����Ӧ�Ķ����У����������־�����ò����ڣ���Ҫ��ʼ��
	if (CLogger::Instance()->Initial(m_pConfig->GetProperties("logger")) != 0)
	{
		return -1;
	}

	// ������־
	if (CLogger::Instance()->Start() != 0)
	{
		return -1;
	}

	return 0;
}

//��������
void CCommHandler::Finish()
{
	if (0 != m_pCpInterfaceYC)
	{
		m_pCpInterfaceYC->Stop();

	
		m_pCpInterfaceYC->Stop();
		delete m_pCpInterfaceYC;
		m_pCpInterfaceYC = nullptr;
	}

	if (0 != m_pCpInterfaceB1C)
	{
		delete m_pCpInterfaceB1C;
		m_pCpInterfaceB1C = nullptr;
	}
	
	if (0 != m_pCpInterfaceB2C)
	{
		delete m_pCpInterfaceB2C;
		m_pCpInterfaceB2C = nullptr;
	}

	if (0 != m_pCpInterfaceB3C)
	{
		delete m_pCpInterfaceB3C;
		m_pCpInterfaceB3C = nullptr;
	}

	if (0 != m_pCpInterfaceB4C)
	{
		delete m_pCpInterfaceB4C;
		m_pCpInterfaceB4C = nullptr;
	}

}

//����ת������ ����ֵ-2��ʾ��·��
int CCommHandler::Forward(CPacket &pkt,const unsigned long& ulKey)
{
	//try
	{	
		int nRtn = -2;
		assert(EnumKeyUnknown > ulKey);
		if (EnumKeyUnknown <= ulKey)
			return -1;

		CBroadcastPacket pktRecv = dynamic_cast<CBroadcastPacket&>(pkt);
		string sCmdID;
		pktRecv.GetParameterVal("ApiName",sCmdID);
		sCmdID = pktRecv.GetCmdID();

		//CRLog(E_ERROR,"ApiName:%s",sCmdID.c_str());

        // �㲥����
        for (VPKTRECEIVER::iterator it = m_vPketReceiver.begin(); it < m_vPketReceiver.end(); 
            it++)
        {
            (*it)->Receive(pkt);
        }

		return 0;
	}

}

int CCommHandler::OpenInterfaceB1C(const QString& szIP, const QString& szPort)
{

	if (0 == m_pConfig)
		return -1;

	CConfig *pCfgB1C;
	pCfgB1C = m_pConfig->GetProperties(gc_sCfgIfB1C.toStdString().c_str());
	if (0 != pCfgB1C /*&& !pCfgB1C->IsEmpty()*/)
	{
		string  sIp   = szIP.toStdString();
		string  sPort = szPort.toStdString();
		pCfgB1C->SetProperty("ip",sIp);
		pCfgB1C->SetProperty("port", sPort);

		m_pCpInterfaceB1C = new CTcpShortCpCli<CProcessInterfaceB1C>();
		m_pCpInterfaceB1C->Init(std::move(pCfgB1C));

		// ���ýӿڵĴ�����Ϣ
		SetProxy(m_pCpInterfaceB1C);

		return 0;
	}

    return 0;
}

void CCommHandler::OpenInterface( EnumKeyIf eKey )
{
	switch(eKey)
	{
	case EnumKeyIfB2C:
		{
			OpenInterfaceB2C();
			break;
		}

	case EnumKeyIfB3C:
		{
			OpenInterfaceB3C();
			break;
		}
	case EnumKeyIfB4C:
		{
			OpenInterfaceB4C();
			break;
		}
	default: break;
	}
}

int CCommHandler::SwitchToCurIP()
{
	const map<string,string>& pmServer = GetServerInfo(m_nCurServerPos);
	if( pmServer.size() > 0 )
	{
		if( NULL != m_pCpInterfaceB2C )
		{
			CTcpShortCpCli<CProcessInterfaceB2C>* pCpCliB2C = (CTcpShortCpCli<CProcessInterfaceB2C>*)m_pCpInterfaceB2C;
			pCpCliB2C->SetIp(pmServer.find("trans_ip")->second,atoi(pmServer.find("trans_port")->second.c_str()));

		}

		if( NULL != m_pCpInterfaceB2CVip )
		{
			CTcpShortCpCli<CProcessInterfaceB2C>* pCpCliB2CVip = (CTcpShortCpCli<CProcessInterfaceB2C>*)m_pCpInterfaceB2CVip;
			pCpCliB2CVip->SetIp(pmServer.find("trans_ip")->second,atoi(pmServer.find("trans_port")->second.c_str()));
		}

		if( NULL != m_pCpInterfaceB3C )
		{
			CTcpShortCpCli<CProcessInterfaceB3C>* pCpCliB3C = (CTcpShortCpCli<CProcessInterfaceB3C>*)m_pCpInterfaceB3C;
			pCpCliB3C->SetIp(pmServer.find("query_ip")->second,atoi(pmServer.find("query_port")->second.c_str()));


		}

		if( NULL != m_pCpInterfaceB4C )
		{
			CTcpShortCpCli<CProcessInterfaceB4C>* pCpCliB4C = (CTcpShortCpCli<CProcessInterfaceB4C>*)m_pCpInterfaceB4C;
			pCpCliB4C->SetIp(pmServer.find("risk_trans_ip")->second,atoi(pmServer.find("risk_trans_port")->second.c_str()));

		}
	}

	return 0;
}

//
void CCommHandler::SetInterface(CConnectPointSync* &pInterface, CConfig* &pCfg, int nServerPos, const QString &sIpName, const QString &sIpPort )
{
	// ��ȡ������ip�Ͷ˿�
	const map<string,string>& pmServer = GetCurServerInfo();

	pCfg->SetProperty("ip", pmServer.find(sIpName.toStdString())->second);
	pCfg->SetProperty("port", pmServer.find(sIpPort.toStdString())->second);
	//д������
	App::WriteConfigProperty(QString("ip"),*(QString *)(sIpName.data()));
	App::WriteConfigProperty(QString("port"), *(QString *)sIpPort.data());
	
    // ��ʼ���ӿ�
	pInterface->Init(pCfg);


	 //���ýӿڵĴ�����Ϣ
	SetProxy(pInterface);
}

int CCommHandler::OpenInterfaceB2C()
{
	if (NULL != m_pConfig)
	{
		CConfig *pCfg;
		pCfg = m_pConfig->GetProperties(gc_sCfgIfB2C.toStdString());
		if (NULL != pCfg)
		{
			// ��ȡ��ǰ������ip�Ͷ˿�
			const map<string, string>& pmServer = GetCurServerInfo();
			pCfg->SetProperty("ip", pmServer.find("trans_ip")->second);
			pCfg->SetProperty("port", pmServer.find("trans_port")->second);
			pCfg->SetProperty("SessionID", g_Global.m_strSessionID.toStdString());

			// �������׽ӿ�
			if (m_pCpInterfaceB2C != NULL)
			{
				delete m_pCpInterfaceB2C;
				m_pCpInterfaceB2C = NULL;
			}
			m_pCpInterfaceB2C = new CTcpShortCpCli<CProcessInterfaceB2C>();
			m_pCpInterfaceB2C->Init(pCfg); // ��ʼ���ӿ�
			SetProxy(m_pCpInterfaceB2C); // ���ýӿڵĴ�����Ϣ

			 // ����vipͨ�� m_pCpInterfaceB2CVip
			if (m_pCpInterfaceB2CVip != NULL)
			{
				delete m_pCpInterfaceB2CVip;
			}
			m_pCpInterfaceB2CVip = new CTcpShortCpCli<CProcessInterfaceB2C>();
			m_pCpInterfaceB2CVip->Init(pCfg); // ��ʼ���ӿ�
			SetProxy(m_pCpInterfaceB2CVip);   // ���ýӿڵĴ�����Ϣ

			return 0;
		}
	}

	return -1;

}

int CCommHandler::OpenInterfaceB3C()
{

	if (NULL != m_pConfig)
	{
		CConfig *pCfg;
		pCfg = m_pConfig->GetProperties(gc_sCfgIfB3C.toStdString());
		if (NULL != pCfg)
		{
			// ��ȡ��ǰ������ip�Ͷ˿�
			const map<string, string>& pmServer = GetCurServerInfo();
			pCfg->SetProperty("ip", pmServer.find("query_ip")->second);
			pCfg->SetProperty("port", pmServer.find("query_port")->second);
			pCfg->SetProperty("SessionID", g_Global.m_strSessionID.toStdString());

			if (m_pCpInterfaceB3C != NULL)
			{
				delete m_pCpInterfaceB3C;
				m_pCpInterfaceB3C = NULL;
			}
			m_pCpInterfaceB3C = new CTcpShortCpCli<CProcessInterfaceB3C>();
			m_pCpInterfaceB3C->Init(pCfg); // ��ʼ���ӿ�
			SetProxy(m_pCpInterfaceB3C);   // ���ýӿڵĴ�����Ϣ

			return 0;
		}
	}

	return -1;

}

int CCommHandler::OpenInterfaceB4C()
{

	if (NULL != m_pConfig)
	{
		CConfig *pCfg;
		pCfg = m_pConfig->GetProperties(gc_sCfgIfB4C.toStdString());
		if (NULL != pCfg)
		{
			// ��ȡ��ǰ������ip�Ͷ˿�
			const map<string, string>& pmServer = GetCurServerInfo();
			pCfg->SetProperty("ip", pmServer.find("risk_trans_ip")->second);
			pCfg->SetProperty("port", pmServer.find("risk_trans_port")->second);

			if (m_pCpInterfaceB4C != NULL)
			{
				delete m_pCpInterfaceB4C;
			}
			m_pCpInterfaceB4C = new CTcpShortCpCli<CProcessInterfaceB4C>();
			m_pCpInterfaceB4C->Init(pCfg); // ��ʼ���ӿ�
			SetProxy(m_pCpInterfaceB4C);   // ���ýӿڵĴ�����Ϣ

			return 0;
		}
	}

	return -1;
}

int CCommHandler::OpenInterfaceYC()
{

	CConfig *pCfgYC;
	pCfgYC = m_pConfig->GetProperties(gc_sCfgIfYC.toStdString());
	if (0 != pCfgYC /*&& !pCfgYC->IsEmpty()*/)
	{
		if (m_mapServerGroup.size() > 0)
		{
			const map<string, string>& pmServer = GetServerInfo(m_nCurServerPos);

			if (g_Global.m_nProxyType == 0) // ���ô���
			{
				pCfgYC->SetProperty("ip", pmServer.find("broadcast_ip")->second);
				pCfgYC->SetProperty("port", pmServer.find("broadcast_port")->second);
			}
			else // ʹ�ô���
			{
				// ����Ŀ��IP��Port
				string szIP, sPort;

				szIP = pmServer.find("broadcast_ip")->second;
				sPort = pmServer.find("broadcast_port")->second;
				g_Global.m_sTargetIP = szIP.c_str();
				g_Global.m_nTargetPort = atoi(sPort.c_str());

				// �Ѵ���IP��Port���õ��㲥�ӿ�
				pCfgYC->SetProperty("ip", g_Global.m_sProxyIP.toStdString());
				g_Global.m_sProxyIP;

				char cPort[20];
				memset(cPort, 0, 20);
				sprintf(cPort, "%d", g_Global.m_nProxyPort);

				pCfgYC->SetProperty("port", cPort);
			}
		}

		pCfgYC->SetProperty("user_id", g_Global.m_strUserID.toStdString());
		pCfgYC->SetProperty("user_type", "2");

		if (NULL != m_pCpInterfaceYC)
		{
			m_pCpInterfaceYC->Finish();
			delete m_pCpInterfaceYC;
			m_pCpInterfaceYC = NULL;
		}

		CRLog(E_NOTICE, "��ʼ�����ӵ�YC");
		m_pCpInterfaceYC = new CProtocolCpCli<CProcessInterfaceYC>();
		m_pCpInterfaceYC->Bind(this, EnumKeyIfYC);
		m_pCpInterfaceYC->Init(pCfgYC);

		CGessTimerMgrImp::Instance()->Start();

		m_pCpInterfaceYC->Start();

		return 0;
	}

	return -1;

}

int CCommHandler::OpenInterfaceYCEx()
{
	CConfig *pCfgYC;
	pCfgYC = m_pConfig->GetProperties(gc_sCfgIfYC.toStdString());
	if (0 != pCfgYC /*&& !pCfgYC->IsEmpty()*/)
	{
		if (m_mapServerGroup.size() > 0)
		{
			// ��ȡ���е�ip�Ͷ˿�
			vector<string> vIP;
			vector<string> vPort;
			for (size_t i = 0; i < m_mapServerGroup.size(); i++)
			{
				map<string, string> pmServer = GetServerInfo(i);
				vIP.push_back(pmServer.find("broadcast_ip")->second);
				vPort.push_back(pmServer.find("broadcast_port")->second);
			}

			if (g_Global.m_nProxyType == 0) // ���ô���
			{
				pCfgYC->SetProperty("ip", vIP);
				pCfgYC->SetProperty("port", vPort);
			}
			else // ʹ�ô���
			{
				// ����Ŀ��IP��Port
				string szIP, sPort;

				const map<string, string>& pmServer = GetServerInfo(m_nCurServerPos);
				szIP = pmServer.find("broadcast_ip")->second;
				sPort = pmServer.find("broadcast_port")->second;
				g_Global.m_sTargetIP = szIP.c_str();
				g_Global.m_nTargetPort = atoi(sPort.c_str());

				// �Ѵ���IP��Port���õ��㲥�ӿ�
				pCfgYC->SetProperty("ip", g_Global.m_sProxyIP.toStdString());


				char cPort[20];
				memset(cPort, 0, 20);
				sprintf(cPort, "%d", g_Global.m_nProxyPort);

				pCfgYC->SetProperty("port", cPort);
			}
		}

		pCfgYC->SetProperty("user_id", g_Global.m_strUserID.toStdString());
		pCfgYC->SetProperty("user_type", "2");

		if (NULL != m_pCpInterfaceYC)
		{
			m_pCpInterfaceYC->Finish();
			delete m_pCpInterfaceYC;
			m_pCpInterfaceYC = NULL;
		}

		CRLog(E_NOTICE, "��ʼ�����ӵ�YC");
		m_pCpInterfaceYC = new CProtocolCpCli<CProcessInterfaceYC>();
		m_pCpInterfaceYC->Bind(this, EnumKeyIfYC);
		m_pCpInterfaceYC->Init(pCfgYC);

		CGessTimerMgrImp::Instance()->Start();

		m_pCpInterfaceYC->Start();

		return 0;
	}

	return -1;
}

// ���Դ���
//int CCommHandler::OpenInterfaceYCEx()
//{
//	CQString csPath = g_Global.GetSystemIniPath();
//	char cBuf[500] = {0};
//	::GetPrivateProfileQString("info", "DirectModeInfo", "", cBuf, sizeof(cBuf), csPath);
//	QString sValue(cBuf);
//	HashtableMsg m_mapServerGroup(sValue);
//
//	CConfig *pCfgYC;
//	pCfgYC = m_pConfig->GetProperties(gc_sCfgIfYC);
//	if (0 != pCfgYC /*&& !pCfgYC->IsEmpty()*/)
//	{
//		if (m_mapServerGroup.size() > 0)
//		{
//			// ��ȡ���е�ip�Ͷ˿�
//			vector<QString> vIP;
//			vector<QString> vPort;
//			for( size_t i = 0; i < m_mapServerGroup.size(); i++ )
//			{
//				map<QString,QString> pmServer = m_mapServerGroup.GetMap(i);
//				vIP.push_back(pmServer.find("broadcast_ip")->second);
//				vPort.push_back(pmServer.find("broadcast_port")->second);
//			}
//
//			if (g_Global.m_nProxyType == 0) // ���ô���
//			{
//				pCfgYC->SetProperty("ip", vIP);
//				pCfgYC->SetProperty("port",vPort);
//			}
//			else // ʹ�ô���
//			{
//				// ����Ŀ��IP��Port
//				QString szIP,sPort;
//
//				const map<QString, QString>& pmServer = GetServerInfo(m_nCurServerPos);
//				szIP = pmServer.find("broadcast_ip")->second;
//				sPort = pmServer.find("broadcast_port")->second;
//				g_Global.m_sTargetIP = szIP.c_str();
//				g_Global.m_nTargetPort = atoi(sPort.c_str());
//
//				// �Ѵ���IP��Port���õ��㲥�ӿ�
//				pCfgYC->SetProperty("ip", g_Global.m_sProxyIP.GetBuffer());
//				g_Global.m_sProxyIP.ReleaseBuffer();
//
//				char cPort[20];
//				memset(cPort, 0, 20);
//				sprintf(cPort, "%d", g_Global.m_nProxyPort);
//
//				pCfgYC->SetProperty("port", cPort);
//			}
//		}
//
//		pCfgYC->SetProperty("user_id",g_Global.m_strUserID);
//		pCfgYC->SetProperty("user_type","2");
//
//		if( NULL != m_pCpInterfaceYC )
//		{
//			m_pCpInterfaceYC->Finish();
//			delete m_pCpInterfaceYC;
//			m_pCpInterfaceYC = NULL;
//		}
//
//		CRLog(E_NOTICE,"��ʼ�����ӵ�YC");
//		m_pCpInterfaceYC = new CProtocolCpCli<CProcessInterfaceYC>();
//		m_pCpInterfaceYC->Bind(this,EnumKeyIfYC);
//		m_pCpInterfaceYC->Init(pCfgYC);
//
//		//CGessTimerMgrImp::Instance()->Init();
//		CGessTimerMgrImp::Instance()->Start();
//
//		m_pCpInterfaceYC->Start();
//
//		return 0;
//	}	
//
//	return -1;
//}

void CCommHandler::Subscribe(CPacketReceiver *pPacketReceiver)
{
    VPKTRECEIVER::iterator it = find(m_vPketReceiver.begin(), m_vPketReceiver.end(), pPacketReceiver);
    if (it == m_vPketReceiver.end())
    {
        m_vPketReceiver.push_back(pPacketReceiver);
    }
}

void CCommHandler::Unsubscribe(CPacketReceiver *pPacketReceiver)
{
    VPKTRECEIVER::iterator it = find(m_vPketReceiver.begin(), m_vPketReceiver.end(), pPacketReceiver);
    if (it != m_vPketReceiver.end())
    {
        m_vPketReceiver.erase(it);
    }
}

void CCommHandler::ClearSession()
{
    m_strSessionID  = "";
    m_strSessionKey = "";
}

QString CCommHandler::GetSessionID()
{
    return m_strSessionID;
}

void CCommHandler::InsertServer(const map<string,string>& server)
{
    m_mapServerGroup.InsertMap(server);
}

QString CCommHandler::GetLocalIP()
{
    QString strIP; 

  /*  WSADATA wsaData; 
    char name[155]; 
    char *ip; 
    PHOSTENT hostinfo; 
    if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 ) 
    {  
        if( gethostname ( name, sizeof(name)) == 0) 
        { 
            if((hostinfo = gethostbyname(name)) != NULL) 
            {
                ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
                strIP = ip; 
            } 
        } 
    }*/

    //return ip;
	return  "";
}

// ���cQString��getbuffer���µ�����
void CCommHandler::SetProxy(CConnectPointSync* pInterface )
{
	QString m_sProxyIP = g_Global.m_sProxyIP.toLatin1();
	QString m_sProxyUser = g_Global.m_sProxyUser.toLatin1();
	QString m_sProxyPassword = g_Global.m_sProxyPassword.toLatin1();

	pInterface->SetProxy(g_Global.m_nProxyType, 
		m_sProxyIP.toStdString(), g_Global.m_nProxyPort, 
		m_sProxyUser.toStdString(), m_sProxyPassword.toStdString());

}

/*
�����һ����������λ��
�����ǰ�������ĸ���Ϊ0���򷵻�false
���򷵻�true�������л�����һ����������λ��
*/
bool CCommHandler::GetNextServerPos( int &nCurPos )
{
	if(  m_mapServerGroup.size() != 0 )
	{
		if( nCurPos < 0 || nCurPos >= m_mapServerGroup.size()-1 )
		{
			nCurPos = 0;
		}
		else
		{
			nCurPos++;
		}
		return true;
	}

	return false;
}

int CCommHandler::GetNextServerPos()
{
	if( m_mapServerGroup.size() != 0 )
	{
		if( m_nCurServerPos < 0 || m_nCurServerPos >= m_mapServerGroup.size()-1 )
		{
			return 0;
		}
		else
		{
			return m_nCurServerPos+1;
		}
	}
	else
	{
		return -1;
	}
}

/*
��һ�η���ʧ�ܺ���ã��������еķ����������ͣ�����ɹ��򷵻�
*/
int CCommHandler::SendPacket(CConnectPointSync **pCp, CTradePacket *oPktReq, CTradePacket *oPktRsp, unsigned int uiTimeout )
{
	int nRtn = -1;

	EnumKeyIf eKey = GetEnumKey( *pCp );
	if( eKey != EnumKeyUnknown )
	{
        // mod by Jerry Lee, 2013-3-8, ������ʱ�����ӷ�����û����Ӧ������
        if (m_mapServerGroup.size() > 0)
        {
            for( int i = 0; i < m_mapServerGroup.size()-1; i++ )
            {
                // ���´򿪽ӿ�
                OpenInterface(eKey);

                // ���ͱ���
                //nRtn = (*pCp)->SendPacket(oPktReq, oPktRsp,uiTimeout);

				//
                if( nRtn == 0 )
                    break;
            }
        }
	}

	return nRtn;
}

void CCommHandler::ToNextServer(CConnectPointSync **pCp )
{
	if ( m_mapServerGroup.size() > 1 )
	{
		EnumKeyIf eKey = GetEnumKey( *pCp );
		if( eKey != EnumKeyUnknown )
		{
			// ���´򿪽ӿ�
			OpenInterface(eKey);
		}
	}
}

EnumKeyIf CCommHandler::GetEnumKey(CConnectPointSync *pCp )
{
	if( pCp == m_pCpInterfaceB2C )
		return EnumKeyIfB2C;
	else if( pCp == m_pCpInterfaceB3C )
		return EnumKeyIfB3C;
	else if( pCp == m_pCpInterfaceB4C )
		return EnumKeyIfB4C;
	else if( pCp == m_pCpInterfaceB1C )
		return EnumKeyIfB1C;

	return EnumKeyUnknown;
}

void CCommHandler::SwitchToNextServer()
{
	// �жϵ�ǰ�����������Ƿ�������������������򲻴���

	if( m_mapServerGroup.size() > 1 )
	{
		// ��ȡ��һ����������λ��
		int nPos = GetNextServerPos();
		if( nPos >= 0 )
		{
			// �л�����һ��������
			SetServerPos(nPos);

			// ����ǰ���ж������л�����ǰ������
			SwitchToCurIP();

			// ��¼��־
			//WLog(E_LOG_NORMAL,"�л�����һ����������������λ�ã�%d", nPos );
		}
	}
}

map<string,string> CCommHandler::GetServerInfo( int nPos )
{
	if( m_mapServerGroup.size() > 0 && nPos >= 0 && nPos < m_mapServerGroup.size() )
	{
		return m_mapServerGroup.GetMap(nPos);
	}
	else
	{
		map<string, string> mapServer;
		return mapServer;
	}
}

void CCommHandler::SetServerPos( int nPos )
{
	m_nCurServerPos = nPos;
}

CConnectPointSync* CCommHandler::GetInterfaceVip()
{
	return m_pCpInterfaceB2CVip;
}

map<string,string> CCommHandler::GetCurServerInfo()
{
	return GetServerInfo(m_nCurServerPos);
}

void CCommHandler::LogServerInfo()
{
	string sValue;
	for( size_t i = 0; i < m_mapServerGroup.size(); i++ )
	{
		auto pmServer = m_mapServerGroup.GetMap(i);
		for( auto it = pmServer.begin(); it != pmServer.end(); it++ )
		{
			sValue += it->first + ":" + it->second.c_str();
			sValue += "��";
		}
		sValue += "��";
	}

	//WLog(E_LOG_NORMAL,"��������Ϣ��%s����ǰ������λ�ã�%d", 
	//	sValue.c_str(),
	//	m_nCurServerPos);
}

int CCommHandler::GetServerCount()
{
	return m_mapServerGroup.size();
}
