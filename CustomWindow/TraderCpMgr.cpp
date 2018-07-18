/******************************************************************************
ģ������:�������̻��������ص���ģ��
��Ҫ����:Init(...)��ʼ������
Finish() ��������
Run()�����̺߳���
�޸ļ�¼:
******************************************************************************/
#include <iostream>
//#include "Logger.h"
//#include "ConfigImpl.h"

#include "TraderCpMgr.h"
#include "TradePacket.h"
#include <QMessageBox>
#include "app.h"

#include "ProtocolConnectPoint.h"
#include "ProcessInterfaceYC.h"
#include <sstream>
#include <iomanip>
//
#include "TcpShortCp.h"
#include "ProcessInterfaceB1C.h"
#include "ProcessInterfaceB2C.h"
#include "ProcessInterfaceB3C.h"
#include "ProcessInterfaceB4C.h"
//
#include "ArrayListMsg.h"
//
//#include "MD5.h"
#include "Const.h"
#include "TradePacketAndStruct.h"
//
//#include "HsmClient.h"
//
#include "Mgr/VarietyMgr.h"
#include "Mgr/SystemParaMgr.h"
#include "Mgr/CodeTableMgrOld.h"
#include "Mgr/CodeTableMgr.h"
#include "Mgr/ProdCodeMgr.h"
//#include "PreOrder/StopPLMgr.h"
#include "Mgr/QuotationMgr.h"
#include "Mgr/PosiMgr.h"
#include "Mgr/TiHuoMgr.h"
#include "DelayReqHandler.h"
//
#include "Global.h"
#include "HJGlobalFun.h"
#include "TranMessage.h"
#include "HJCommon.h"
//#include "Log/MyLogEx.h"
#include "CustomInfoMgrEx.h"
#include "ClientTips.h"
#include "myhelper.h"
#include "app.h"
#include "Struct.h"
#include "HJGlobalFun.h"
#include <QMessageBox>
#include "IniFilesManager.h"
#include "QParamEvent.h"
#include <QTextCodec>




#ifdef _WIN32
    #include "MD5.h"
#else
    #include <openssl/md5.h>
#endif


CTraderCpMgr  g_TraderCpMgr;
HEADER_REQ    g_HeaderReq;
quint64       g_SeqNo = 0x9a1f3241;


#pragma execution_character_set("utf-8")

#define MenuIdByHand "M030100"
#define MenuIdByAuto "M030000"






// ģ��ⶳiCancelHand��
//bool OrderFrozeInfo::CancelBal(int iCancelHand, double &dCancelBal)
//{
//	if(iTotal > 0)
//	{
//		iRemainAmt -= iCancelHand;
//		double dCancelBuy = CHJGlobalFun::DoubleFormat(dEntrBuy * iCancelHand / iTotal, 4);
//		double dReserve = CHJGlobalFun::DoubleFormat(dEntrReserve * iCancelHand / iTotal, 4);
//		double dExchFare = CHJGlobalFun::DoubleFormat(dEntrExchFare * iCancelHand / iTotal, 4);
//
//		// ģ��洢���̣���һ���Ƿ���Կ���ȥ��
//		dCancelBal = CHJGlobalFun::DoubleFormat(dCancelBuy+dReserve+dExchFare, 4);
//		//dCancelBal = dCancelBuy+dReserve+dExchFare;
//		// ģ��洢������ִ��p_trade_fund_unfroze������ת��
//		dCancelBal = CHJGlobalFun::DoubleFormat(dCancelBal);
//	}
//	else
//	{
//		dCancelBal = 0.00;
//	}
//
//	return iRemainAmt > 0 ? false : true;
//}
//
//// ģ��ⶳiCancelHand��
//bool OrderFrozeInfo::CancelBalForward(int iCancelHand, double &dCancelBal)
//{
//	if(iTotal > 0)
//	{
//		iRemainAmt -= iCancelHand;
//		double dCancelBuy = CHJGlobalFun::DoubleFormat(dEntrBuy * iCancelHand / iTotal, 4);
//		double dReserve = CHJGlobalFun::DoubleFormat(dEntrReserve * iCancelHand / iTotal, 4);
//		double dExchFare = CHJGlobalFun::DoubleFormat(dEntrExchFare * iCancelHand / iTotal, 4);
//
//		// ģ��洢���̣���һ���Ƿ���Կ���ȥ��
//		dCancelBal = CHJGlobalFun::DoubleFormat(dCancelBuy+dReserve+dExchFare, 4);
//		// ģ��洢������ִ��p_trade_fund_unfroze������ת��
//		dCancelBal = CHJGlobalFun::DoubleFormat(dCancelBal);
//	}
//	else
//	{
//		dCancelBal = 0.00;
//	}
//
//	return iRemainAmt > 0 ? false : true;
//}
//
///*
//�ж�һ��ҵ��ı�����ˮ�����Ƿ�����Ч����
//���򷵻�true�����򷵻�false
//*/
template<class QMapType>
bool HasValidOrder(const QMap<QString, QMapType> &QMapOrder)
{
	for (auto it = QMapOrder.begin(); it != QMapOrder.end(); it++)
	{
		if (it.value().status != "d")
			return true;
	}
	return false;
}
//
////ȥ����ʼ���ṹ�����һ�к���Ķ��ţ�����EnumKeyUnknown�޸�Ϊʵ�ʵĽӿ�ID
CTraderCpMgr::IfRouterCfg CTraderCpMgr::m_tblIfRouterCfg[] =
{
	//CmdID         To                      Obj
	{ "1001",        EnumKeyIfB2C,           0 },
	{ "1002",        EnumKeyIfB2C,           0 },
	{ "1004",        EnumKeyIfB2C,           0 },
	{ "1005",        EnumKeyIfB2C,           0 },
	{ "1006",        EnumKeyIfB2C,           0 },
	{ "1007",        EnumKeyIfB2C,           0 },
	{ "1020",        EnumKeyIfB2C,           0 },//�ͻ���Ϣ
	{ "2022",        EnumKeyIfB2C,           0 },
	{ "2040",        EnumKeyIfB2C,           0 },
	{ "2201",        EnumKeyIfB2C,           0 },
	{ "3010",        EnumKeyIfB2C,           0 }, //��Ŀ��û�иýṹ
	{ "3021",        EnumKeyIfB2C,           0 },
	{ "3024",        EnumKeyIfB2C,           0 },
	{ "3064",        EnumKeyIfB4C,           0 }, // ����֪ͨ����ѯ
	{ "3069",        EnumKeyIfB4C,           0 }, // ǿƽ����ѯ
	{ "3099",        EnumKeyIfB4C,           0 }, // ���նȲ�ѯ
	{ "3101",        EnumKeyIfB2C,           0 }, // ����ͨ�����ת��
	{ "4001",        EnumKeyIfB2C,           0 },
	{ "4011",        EnumKeyIfB2C,           0 },//add by xiao ���ڱ��� begin
	{ "4012",        EnumKeyIfB2C,           0 },
	{ "4021",        EnumKeyIfB2C,           0 },
	{ "4022",        EnumKeyIfB2C,           0 },
	{ "4041",        EnumKeyIfB2C,           0 },
	{ "4042",        EnumKeyIfB2C,           0 },
	{ "4043",        EnumKeyIfB2C,           0 },
	{ "4044",        EnumKeyIfB2C,           0 },
	{ "4045",        EnumKeyIfB2C,           0 },
	{ "4046",        EnumKeyIfB2C,           0 },
	{ "4047",        EnumKeyIfB2C,           0 },
	{ "4048",        EnumKeyIfB2C,           0 }, // end
	{ "4061",        EnumKeyIfB2C,           0 },
	{ "4071",        EnumKeyIfB2C,           0 },
	{ "5041",        EnumKeyIfB2C,           0 },
	{ "5101",        EnumKeyIfB2C,           0 },
	{ "5103",        EnumKeyIfB2C,           0 },
	{ "6001",        EnumKeyIfB3C,           0 },
	{ "6002",        EnumKeyIfB3C,           0 },
	{ "6005",        EnumKeyIfB2C,           0 },
	{ "6007",        EnumKeyIfB2C,           0 },
	{ "8001",        EnumKeyIfB2C,           0 },
	{ "8006",        EnumKeyIfB1C,           0 },
	{ "8007",        EnumKeyIfB2C,           0 },
	{ "8031",        EnumKeyIfB2C,           0 },
	{ "9010",        EnumKeyIfB2C,           0 },
	{ "9030",        EnumKeyIfB2C,           0 },
	{ "4074",        EnumKeyIfB2C,           0 },
	{ "3201",        EnumKeyIfB2C,           0 },
	{ "8002",        EnumKeyIfB2C,           0 },

#ifdef RUN_EMULATOR
	{ "3999",        EnumKeyIfB2C,           0 },
	{ "5999",        EnumKeyIfB2C,           0 },
	{ "2997",        EnumKeyIfB2C,           0 },
	{ "2996",        EnumKeyIfB2C,           0 },
	{ "2995",        EnumKeyIfB2C,           0 },
	{ "2994",        EnumKeyIfB2C,           0 },
	{ "8999",        EnumKeyIfB2C,           0 },
	{ "8998",        EnumKeyIfB2C,           0 },
	{ "8997",        EnumKeyIfB2C,           0 },
	{ "8897",        EnumKeyIfB2C,           0 },
	{ "2998",        EnumKeyIfB1C,           0 },
	{ "2999",        EnumKeyIfB1C,           0 },
#endif
};
//
CBroadcaster::CBroadcaster()
{

}
CBroadcaster::~CBroadcaster()
{

}
CBroadcaster::CBroadcaster(const CBroadcaster& bdr)
{
	*this = bdr;
}
CBroadcaster& CBroadcaster::operator=(const CBroadcaster& bdr)
{
	if (this != &bdr)
	{
		//m_arrint.RemoveAll();
		m_arrint.clear();

		for (int i = 0; i<bdr.m_arrint.size(); i++)
		{
			//m_arrint.insert(bdr.m_arrint.keys()[i], bdr.m_arrint.values()[i]);
			m_arrint = bdr.m_arrint;
			// m_arrint.(bdr.m_arrint[i]);
		}


	}

	return *this;
}


// ���ھ��Ϊint�Ĵ��ڶ�����Ϣ
void CBroadcaster::Subscribe(QWidget * val)
{
	if (Find(val) < 0)
	{
		m_arrint.append(val);
	}
}
// ���ھ��Ϊint�Ĵ���ȡ��������Ϣ
void CBroadcaster::Unsubscribe(QWidget * val)
{
	int i = Find(val);
	if (i >= 0)
	{
		m_arrint.removeAt(i);
	}
}

void CBroadcaster::Broadcast(UINT uMsg, void * wParam,void * lParam,BOOL bAsyn)
{
	//std::shared_ptr<QParamEvent> event = make_shared<QParamEvent>(QEvent::Type(uMsg));
	for (int i = 0; i<m_arrint.size(); i++)
	{
		QParamEvent *event = new QParamEvent(QEvent::Type(uMsg));
		event->setWParam(wParam);
		event->setLParam(lParam);
		if(wParam != nullptr)
			event->setOrderId(*(int *)wParam);
		if(lParam != nullptr)
			event->setInt(*(int *)lParam);
		//if (bAsyn)
		{
			QApplication::postEvent((QWidget *)m_arrint[i], event);
		}
		//else
		{
			//QApplication::sendEvent((QWidget *)m_arrint[i], event);
		}
	}

}

int CBroadcaster::Find(QWidget * val)
{
	int nRet = -1;
	for (int i = 0; i<m_arrint.size(); i++)
	{
		if (val == m_arrint[i])
		{
			nRet = i;
			break;
		}
	}

	return nRet;
}

//
CTraderCpMgr::CTraderCpMgr()
{
	m_pConfig = new CConfigImpl();

	m_nTimeOut = 30;
}

CTraderCpMgr::~CTraderCpMgr(void)
{
	if (0 != m_pConfig)
	{
	    delete m_pConfig;
	    m_pConfig = 0;
	}

	m_cPreOrder.bRun = false;

	CCommHandler::Instance()->Unsubscribe(this);
}

//���̻����ӵ��������ʼ��
int CTraderCpMgr::Init()
{
	m_bLoginSucceed = false;

	//��pCfg��QMap���ͣ�����������ļ���key��value��ӳ���ϵ�ŵ�m_Props
	QString csPath;
	myHelper::GetSystemIniPath(csPath);
	
	if (m_pConfig->Load(csPath.toStdString()) != 0)
	{
		return -1;
	}

	//��������
	g_Global.m_strNetAgent      = App::net_agent;
	g_Global.m_strBankNo        = App::bank_no;
	g_Global.m_strNetEnvionment = App::net_envionment;

	// ��ʼ������������ͷ
	memset(&g_HeaderReq, 0, sizeof(HEADER_REQ));
	g_HeaderReq.SetMsgType("1");
	g_HeaderReq.SetMsgFlag("1");
	g_HeaderReq.SetTermType("01");
	g_HeaderReq.SetUserType("1");
	g_HeaderReq.SetAreaCode("    ");
	g_HeaderReq.SetBranchID("            ");
	g_HeaderReq.SetCTellerID1("          ");
	g_HeaderReq.SetCTellerID2("          ");

	//
	CCommHandler::Instance()->Init(csPath);
	CCommHandler::Instance()->Subscribe(this);

	//
	InitStrategy();


	return 0;
}

//��¼��֤����½ʱ�û�������10λ���ȡǰ10λ���˺�����Ҫ�����˻�����
int CTraderCpMgr::Authenticate(const char* pszUsr, const char* pszPwd, const char* pszAddr,
	int nPort, QString useridtype /* = "1"*/, bool bSign /*= false*/)
{
	// ����Ƿ��Ѿ�ͨ����֤
	if (g_Global.m_strSessionID != "" && g_Global.m_strSessionKey != "")
	{
		//return 0;
	}

	// ����֤�˿�
	QString acPort = QString::number(nPort);

	// mod by Jerry Lee, 2013-4-2, ��ʹ�ô���ʱ��ת��������IP��ַ
	QString strIPAddr = pszAddr;

	//if (g_Global.m_nProxyType == 0)
	//{
	//    strIPAddr = GetIPFromDomain(pszAddr); 
	//}

	if (CCommHandler::Instance()->OpenInterfaceB1C(std::move(strIPAddr), std::move(acPort)) != 0)
	{
		return -1;
	}

	// ��ʼ��·�ɱ���m_tblIfRouterCfg�����е����ü��ص�m_tblIfRouter��QMap���ͣ�����ÿ�����ļ��ض�Ӧ�Ľӿ���
	InitRouterTbl();

	// ������ͷ����
	g_HeaderReq.SetUserID(pszUsr);
	g_HeaderReq.SetExchCode("8006");
	g_HeaderReq.SetSeqNo(g_SeqNo++);

	g_HeaderReq.SetTermType("03"); //��ʾ��½������03Ϊ�����նˣ�
	g_HeaderReq.SetUserType("2");  //��ʾ�û����ͣ�2Ϊ�ͻ���
	g_HeaderReq.SetUserID(pszUsr); //�û���
	g_HeaderReq.SetMsgFlag("1");   //�����ı�ʶ��δ֪��
	g_HeaderReq.SetMsgType("1");   //���ױ������ͣ�1Ϊ���ף�

								   //8006�����ĳ�ʼ��
	Req8006 stBodyReq;
	//memset(&stBodyReq, 0, sizeof(Req8006));//�򿪾ͱ���

	myHelper::initLocalNet();

	stBodyReq.oper_flag = 1; // ������־    ��1Ϊ��¼��֤��
	stBodyReq.user_type ="2"; // �û����ͣ���1Ϊ����Ա��2Ϊ�ͻ�������û�в���Ա�Ŀ��ܣ�����û�ж��嵽ȫ�ֱ�����
	stBodyReq.user_id_type = useridtype.toLatin1(); // �û�ID����    ����¼�û�Ϊ�ͻ�ʱ����ֵ��Ч��1���ͻ���2�������˺�
	stBodyReq.user_id = pszUsr; // �û�ID   
	stBodyReq.login_ip = myHelper::getHostIpAddress().toStdString(); //��ȡ������ip��ַ     
	stBodyReq.net_agent = App::net_agent.toLatin1(); //  ������Ӫ��id                   
	stBodyReq.bank_no = App::bank_no.toLatin1(); // �����˺�
	stBodyReq.net_envionment = App::net_envionment.toLatin1(); // ���绷��id 
	stBodyReq.user_pwd = GetEncryptPSW(pszPwd).toStdString();

	// add for ����ͨ
	stBodyReq.isSign = bSign ? "1" : "0";// �û�����

	/*char cLog[100] = { 0 };
	sprintf(cLog, "��¼ip��%s����¼�˿ڣ�%d", pszAddr, nPort);
	qDebug("��ʼ��֤", cLog);*/

	Rsp8006 stBodyRsp;
	if (HandlePacket(stBodyRsp, stBodyReq, "8006") == 0)
	{
		if (CheckRspCode(stBodyRsp.rsp_code.c_str(), CHJGlobalFun::str2qstr(stBodyRsp.rsp_msg)))
		{
			//����½
			ArrayListMsg moreLoginInfo = stBodyRsp.htm_more_login_list;
			int curLinkNum = 0;
			int maxLinkNum = 0;
			if (moreLoginInfo.size() > 0)
			{
				ArrayListMsg s = (ArrayListMsg)moreLoginInfo.GetValue(0);
				curLinkNum = CHJGlobalFun::str2qstr(s.GetStringEx(0)).toInt();
				maxLinkNum = CHJGlobalFun::str2qstr(s.GetStringEx(1)).toInt();
				if (curLinkNum != 0 && maxLinkNum != 0 && curLinkNum >= maxLinkNum)
				{
					QString  strTip;
					strTip = QString("��ǰ������¼��������Ϊ%1d�����ѳ������������%2d����Ϊ������������¼����ǿ��ǩ��һ�����߽��׶�,�Ƿ������").arg(curLinkNum).arg(maxLinkNum);
					/*if (IDNO == ::QMessageBox(NULL, strTip, "��ʾ", MB_YESNO|MB_ICONWARNING))
					return -1;*/

					if (QMessageBox::NoButton == QMessageBox::warning(NULL, "warning", strTip, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
						return -1;
				}
			}

			// ��¼��������Ϣ
			SetServerList(stBodyRsp.htm_server_list);

			// ��¼��������Ϣ����־
			CCommHandler::Instance()->LogServerInfo();

			// ����ỰID�ͻỰ��Կ�Լ����ܺ���û�������û�ID���û����ƣ�
			g_Global.m_strUserID = pszUsr;
			g_Global.m_strSessionID = stBodyRsp.session_id.c_str();  //�ỰID
			g_Global.m_strSessionKey = stBodyRsp.session_key.c_str(); //�Ự��Կ
			g_Global.m_strPwdMD5 = stBodyReq.user_pwd.c_str();

			qDebug("��֤�ɹ�");

			return 0;
		}
		else
		{
			qDebug("��֤ʧ��", stBodyRsp.rsp_msg);
			return -2;
		}
	}
	else //added by Jerry Lee, 2013-6-14, �������ݴ���ʧ��
	{
		qDebug("��֤ʧ��", LOG_CONNECT_SERVER_FAIL_TIPS);
		return YLINK_ERROR_NETWORK;
	}


	return -1;
}

//#include "CBlockHouse.h"
// �û���¼���˺�����Ҫ�����˻�����
int CTraderCpMgr::UserLogin(const QString &sLoginMode /* = CONSTANT_LOGIN_TYPE_CODE*/, bool bSign /*= false*/)
{
	//����Ƿ��Ѿ�ͨ����֤
	if (g_Global.m_strSessionID == "" || g_Global.m_strSessionKey == "")
	{
		return -1;
	}

	//8006�����ĳ�ʼ��
	Req8001 stBodyReq;
	memset(&stBodyReq, 0, sizeof(Req8001));

	// ��ȡ�����ļ�
	QString csPath = g_Global.GetSystemIniPath();

	stBodyReq.oper_flag			= 1; // ������־    1���û���¼
	stBodyReq.user_type			= "2"; // �û����ͣ���1Ϊ����Ա��2Ϊ�ͻ�������û�в���Ա�Ŀ��ܣ�����û�ж��嵽ȫ�ֱ�����
	stBodyReq.login_server_code = "M006"; // �����䣿 ����������    �ͻ���ǰ����ҵ��ʹ�õķ���������
	stBodyReq.user_id           = g_Global.m_strUserID.toStdString(); // �û�ID    
	stBodyReq.user_pwd          = g_Global.m_strPwdMD5.toStdString(); // �û�����   
	stBodyReq.bank_no           = g_Global.m_strBankNo.toStdString(); // �����˺�
	stBodyReq.ver_num           = App::ver_num.toStdString(); // �ͻ��˰汾�� 
	stBodyReq.is_down_para      = App::is_down_para.toStdString(); // �Ƿ����ز�����Ϣ    ����ͻ��˵İ汾����������˵����°汾�Ų�һ�£�ǿ�����ء���Ӧ���ĵ��ֶ�20��ʼ

	stBodyReq.user_id_type      = sLoginMode.toStdString(); //�û�ID����    ����¼�û�Ϊ�ͻ�ʱ����ֵ��Ч��1���ͻ���2�������˺�
	stBodyReq.login_ip          = myHelper::getHostIpAddress().toStdString(); //��ȡ������ip��ַ
	stBodyReq.session_id        = g_Global.m_strSessionID.toStdString();

	stBodyReq.isSign = "0";


	CCommHandler* pCommHandler = CCommHandler::Instance();

	pCommHandler->OpenInterfaceB2C();

	Rsp8001 stBodyRsp;
	int iRet = -1;
	// �����������б����Ե�¼
	for (int i = 0; i < pCommHandler->GetServerCount(); i++)
	{
		iRet = HandlePacket(stBodyRsp, stBodyReq, "8001");
		if (iRet == 0)
		{
			break;
		}
	}

	if (iRet == 0)
	{
		if (CCommHandler::Instance()->OpenInterfaceB3C() == 0
			&& CCommHandler::Instance()->OpenInterfaceB4C() == 0)
		{
			if (CheckRspCode(stBodyRsp.rsp_code.c_str(), CHJGlobalFun::str2qstr(stBodyRsp.rsp_msg)))
			{
				// ������������ 
				CallUpdateExe();

				// ��¼��½�û���
				//::WritePrivateProfileQString("Display", "cust_code", stBodyReq.user_id, g_Global.GetUserIniPath());
				//::WritePrivateProfileQString("Display", "LoginMode", sLoginMode, g_Global.GetUserIniPath());

				// added by Jerry Lee, 2013-02-28
				//  g_Global.ChangeUserIniFile(stBodyReq.user_id);

				g_Global.m_strExchDate = stBodyRsp.exch_date.c_str();         // ϵͳ������
				g_Global.m_strLast_Exch_Date = stBodyRsp.last_exch_date.c_str();    // ��һ������
				g_Global.m_strSysState = stBodyRsp.m_sys_stat.c_str();        // ϵͳ״̬ID
				g_Global.m_strUserName = stBodyRsp.user_name.c_str();         // �ͻ���ƣ�����"����һ"
				g_Global.m_strBranchName = CHJGlobalFun::str2qstr( stBodyRsp.branch_name); ;//stBodyRsp.branch_name.c_str();       // �ͻ���������������ƣ�����"�����У�"
				g_Global.m_almTake_Man_List = stBodyRsp.alm_take_man_list; // �ͻ�������б�
				g_Global.m_strAcctType = stBodyRsp.acct_type.c_str();         // �˻�����

				g_Global.m_strNo_Affirm_Rpt_Num = stBodyRsp.no_affirm_rpt_num; //
				g_Global.m_almNoRead_Bulletin_List = stBodyRsp.alm_noread_bulletin_list;
				g_Global.m_strUserID = stBodyRsp.user_id.c_str();

				g_HeaderReq.SetBranchID(stBodyRsp.branch_id); //�����������
				g_HeaderReq.SetUserID(stBodyRsp.user_id);     //�����������Ϊ���кŵĻ�����̨�Ὣ���к�ת��Ϊ���ױ���

															  // ��¼��½�û���
															  //::WritePrivateProfileQString("Display", "cust_code", stBodyReq.user_id, g_Global.GetUserIniPath());
															  //::WritePrivateProfileQString("Display", "LoginMode", sLoginMode, g_Global.GetUserIniPath());

//#if (defined _VERSION_JSZX) || (defined _VERSION_ZHLHY)
//															  // ���ó����ģʽ
//				SetTransferMode(stBodyRsp.alm_menu_info);
//#endif
				// �Ƿ���Ȩ�޲���Ԥ��
				g_Global.m_bUseSerPreOrder = stBodyRsp.auto_entry_menu_id == "M000000" ? true : false;

				// �Ƿ���Ҫ����
				bool bNeedUpdate = (stBodyReq.is_down_para == "1") ? true : CompareVersion(App::ver_num, stBodyRsp.version.c_str(), 3);

				// ���°汾��Ϣ
				if (bNeedUpdate)
					RecordVersionInfo(stBodyRsp.version.c_str());

				// ����Ҫ����д���ڴ�
				{
					// ��ʼ������Ʒ�ִ���
					g_VarietyMgr.Initialize(m_vVariety, bNeedUpdate ? &stBodyRsp.alm_variety_list : NULL);

					// ��ʼ�����
					g_CodeTableMgrOld.Initialize(bNeedUpdate ? &stBodyRsp.alm_code_table_list : NULL);

					g_CodeTableMgr.Initialize(bNeedUpdate ? &stBodyRsp.alm_code_table_list : NULL);

					// ��ʼ��Ʒ����Ϣ
					g_ProdCodeMgr.Initialize(m_vProdCode, bNeedUpdate ? &stBodyRsp.alm_prod_code_list : NULL);

					// ί�й���m_QMapSystemPara��������ʱ�������Ժ�m_QMapSystemParaҪ¼�뵽g_SysParaMgr����
					g_SysParaMgr.Initialize( m_QMapSystemPara );

					g_PosiMgr.Initialize(m_QMapDeferPosi, m_QMapStoreInfo);
				}

				// ��ʼ���������к�
				IniOrderSerial();

				// ��ȡ����ģ����Ϣ
				GetRsp2040();

				// ��ʼ��ϵͳ����
				IniSystemSetting();

				// ��ʼ������Ʒ��
				IniQuotationInsID();

				// ��ʼ��ֹӯֹ�������
				//g_StopPLMgr.Initialize();

				// ��ʼ�����������
				g_QuoMgr.Initialize(m_QMapQuotation);
				/*if (g_Global.m_bForceTerminate)
				{
				return -2;
				}*/
				// ���������Ԥ���������������ڹ㲥���ý��׽ӿڶ������������������ݼ���������
				GetParaValue("MaxEntrAmount", "0");

				// �����ӳ�ˢ���߳�
				QString sBroadcastDelayActionTime = GetParaValue("BroadcastDelayActionTime", "700");
				
///////////����ͻ���ʼ����Ϣ///////////////////////////////////////////////////////////////
				g_DelayReqHandler.Initlize(CHJGlobalFun::qstr2str(sBroadcastDelayActionTime));

				// ��½�ɹ�������һ�οͻ���Ϣ
				g_DelayReqHandler.AddCustomInfoReq();
//////////////////////////////////////////////////////////////////////////
				 //�򿪹㲥�˿ڣ�Ҫ�ڻ�ȡ�ͻ�������Ϣ���������㲥�������Զ���������
				if(CCommHandler::Instance()->OpenInterfaceYCEx() != 0)
				{
					QMessageBox::warning(nullptr, "��¼��ʾ", "�򿪹㲥�˿�ʧ��!", QMessageBox::Ok);
					return -1;
				}

				// ����Ԥ�񵥹����߳�
				//m_cAutoSendThread.Set(&m_cPreOrder);
				//m_cAutoSendThread.Start();
				//ͨ���̳߳ؽ���Զ��߳�
				pool.AddTask(std::bind(&CPreOrder::CommitAskAll, &m_cPreOrder));

				if (g_Global.m_bShowLastLoginInfo)
				{
					//������Ϣ  
					if (stBodyRsp.last_login_date.length() > 0 && stBodyRsp.last_lan_ip.length() > 0)
					{
						QString strMsg;
						if (stBodyRsp.exist_login == CONSTANT_YES_NO_YES)
						{

							strMsg = QString("������һ����ͬ���û���½��\n�Է���¼ʱ�䣺%1 %2\n�Է���¼IP��ַ��%3")\
								.arg( CHJGlobalFun::str2qstr(stBodyRsp.last_login_date))\
								.arg(CHJGlobalFun::str2qstr(stBodyRsp.last_login_time))\
								.arg(CHJGlobalFun::str2qstr(stBodyRsp.last_lan_ip ));
						
						}
						else
						{
							strMsg = QString("�ϴε�¼ʱ�䣺%1 %2\n�ϴε�¼IP��ַ��%3")\
								.arg(CHJGlobalFun::str2qstr(stBodyRsp.last_login_date))\
								.arg(CHJGlobalFun::str2qstr(stBodyRsp.last_login_time))\
								.arg(CHJGlobalFun::str2qstr(stBodyRsp.last_lan_ip));

						}
						QMessageBox::warning(nullptr,"��¼��ʾ",strMsg, QMessageBox::Ok);

					}
					if (stBodyRsp.more_login_msg.length() > 0)
					{
						QString str = QString("����¼�û���¼��¼��\n %1 ").arg(CHJGlobalFun::str2qstr(stBodyRsp.more_login_msg));

						QMessageBox::warning(nullptr, "��¼��ʾ", str, QMessageBox::Ok);

						//QParamEvent *msg = new QParamEvent(WM_SHOW_ORDER_TIPS);
						//msg->setWParam(&str);

						//QApplication::sendEvent(m_hMain, new QEvent(WM_SHOW_ORDER_TIPS));


					}
				}

				m_bLoginSucceed = true;

				//WLog(E_LOG_NORMAL,"�ͻ�%s��¼�ɹ�����½SessionID��%s", g_Global.m_strUserID,g_Global.m_strSessionID);

				return stBodyRsp.need_change_pwd == CONSTANT_YES_NO_YES ? 1 : 0;
			}
			else
			{
				qDebug("��¼ʧ��", stBodyRsp.rsp_msg);
			}
		}
	}
	else
	{
		qDebug("��¼ʧ��", LOG_CONNECT_SERVER_FAIL_TIPS);
	}
	return -1;
}
//
//#ifdef Q_OS_WIN
//
//int CTraderCpMgr::setMainwnd(HWND wnd)
//{
//	// ��¼�����ھ��������̷߳���Ϣֱ�ӵ���AfxGetMainWnd()���ܵ��¾�����������
//	m_hMain = wnd;
//
//	return 1;
//}
//#elif  defined Q_OS_UNIX
//int CTraderCpMgr::setMainwnd(mainWindow* wnd)
//{
//	// ��¼�����ھ��������̷߳���Ϣֱ�ӵ���AfxGetMainWnd()���ܵ��¾�����������
//	m_hMain = wnd;
//
//	return 1;
//}
//
//#endif


// �������ܱ��ģ���Ļ����
int CTraderCpMgr::UnlockScreen(const QString &pwd, const QString &useridtype /* = CONSTANT_LOGIN_TYPE_CODE */)
{
#ifdef _VERSION_GF
	Req8007 stBodyReq;
	Rsp8007 stBodyRsp;

	stBodyReq.oper_flag = 1;
	stBodyReq.user_type = "2";
	stBodyReq.user_id_type = (useridtype == "1") ? "1" : "2";
	stBodyReq.user_id = g_Global.m_strUserID;
	// 	char *szPWD = NULL;
	// 	szPWD = pwd.GetBuffer();
	stBodyReq.user_pwd = GetEncryptPSW(pwd);
	// 	pwd.ReleaseBuffer();
	stBodyReq.login_ip = CCommHandler::Instance()->GetLocalIP();
	stBodyReq.bank_no = g_Global.m_strBankNo;
	stBodyReq.isSign = "0";

	if (HandlePacket(stBodyRsp, stBodyReq, "8007") == 0)
	{
		return CheckRspCode(stBodyRsp.rsp_code, stBodyRsp.rsp_msg) ? 0 : -1;
	}
	else
	{
		return YLINK_ERROR_NETWORK;
	}

#else
	if (GetEncryptPSW(pwd.toLatin1()) == g_Global.m_strPwdMD5)
		return 0;
	else
		return -1;
#endif
}

// ��ȡ�������ĳһ�����µ�ĳһid�¶�Ӧ��ֵ(codedesc)�������ֲ������������
QString CTraderCpMgr::GetCode_desc(QString codetype, QString codeid)
{
	for (size_t i = 0; i < m_vCode.size(); i++)
	{
		MyCodeInfo mystruct = m_vCode.at(i);
		if (mystruct.code_type == codetype && mystruct.code_id == codeid)
		{
			return mystruct.code_desc.toLatin1();
		}
	}
	return "";
}

// ��ȡ�������ĳһ�����µ�ĳһ�����¶�Ӧ��id(codedesc)�������ֲ������������
QString CTraderCpMgr::GetCode_id(QString codetype, QString codedesc)
{
	for (size_t i = 0; i < m_vCode.size(); i++)
	{
		MyCodeInfo mystruct = m_vCode.at(i);
		if (mystruct.code_type == codetype && mystruct.code_desc == codedesc)
		{
			return mystruct.code_id;
		}
	}
	return "";
}

void CTraderCpMgr::ClearSession()
{
	g_Global.m_strSessionID = "";
	g_Global.m_strSessionKey = "";
}

//�û��˳�
//CProcessInterfaceYC �رճ����� ��close ��finish
//�ͷ���Դ
int CTraderCpMgr::UserLogout()
{
	//����Ƿ��Ѿ�ͨ����֤
	if (g_Global.m_strSessionID != "" && g_Global.m_strSessionKey != "")
	{
		//return 0;
	}

	Req8002 stBodyReq;
	memset(&stBodyReq, 0, sizeof(Req8002));
	stBodyReq.oper_flag = 1; //������־    1���û���¼   ԭ����0
	stBodyReq.user_type = "1"; //�û�����    user_type
	stBodyReq.user_id = g_Global.m_strUserID.toStdString(); //�û�ID    
	stBodyReq.session_id = g_Global.m_strSessionID.toStdString(); //�û�����    

	Rsp8002 stBodyRsp;
	if (HandlePacket(stBodyRsp, stBodyReq, "8002", 20) == 0)
	{
		//LOG("�����˳��ɹ�");
		m_bLoginSucceed = false;
		return 0;
	}
	else
	{
		//qDebug("�����˳�ʧ��",stBodyRsp.rsp_msg);
	}

	return -1;
}

// 
QString CTraderCpMgr::GetSessionID()
{
	return g_Global.m_strSessionID;
}


// ��ʼ��·�ɱ�
int CTraderCpMgr::InitRouterTbl()
{
	//���ñ�
	int nSize = sizeof(m_tblIfRouterCfg) / sizeof(IfRouterCfg);

	//����·�����ñ��ʼ���ڴ�·�ɱ�
	for (int m = 0; m < nSize; m++)
	{
		QString sCmdID = m_tblIfRouterCfg[m].sCmdID;
		switch (m_tblIfRouterCfg[m].ulIfTo)
		{
		case EnumKeyIfB1C:
			m_tblIfRouter[sCmdID] = &CCommHandler::Instance()->m_pCpInterfaceB1C;
			break;
		case EnumKeyIfB2C:
			m_tblIfRouter[sCmdID] = &CCommHandler::Instance()->m_pCpInterfaceB2C;
			break;
		case EnumKeyIfB3C:
			m_tblIfRouter[sCmdID] = &CCommHandler::Instance()->m_pCpInterfaceB3C;
			break;
		case EnumKeyIfB4C:
			m_tblIfRouter[sCmdID] = &CCommHandler::Instance()->m_pCpInterfaceB4C;
			break;
		default:
			m_tblIfRouter[sCmdID] = NULL;
			break;
		}
	}

	return 0;
}

CConnectPointSync* CTraderCpMgr::FindRoute(const QString &sCmdID)
{
	auto it = m_tblIfRouter.find(sCmdID);
	if (it != m_tblIfRouter.end())
	{
		return *(it.value());
	}
	return 0;
}



// ���� �ӿ� [6002]��ͨ��ѯ ��ҵ��ʵ��
int CTraderCpMgr::Tran6002Handle(HEADER_REQ& stHeaderReq, Req6002& stBodyReq, HEADER_RSP& stHeaderRsp,
	Rsp6002& stBodyRsp, QVector< pair<QString, QString> > & v, unsigned int uiTimeout)
{
	CTradePacket oPktReq;
	oPktReq.SetHeader(stHeaderReq);
	CTradePacketAndStruct::Struct2Packet(stBodyReq, oPktReq);

	for (size_t i = 0;i<v.size();i++)
	{
		QByteArray ba = v.at(i).first.toLatin1();
		QByteArray bb = v.at(i).second.toLatin1();
		oPktReq.AddParameter(ba.data(), bb.data());
	}

	CConnectPointSync* pCp = 0;
	QString sCmdID = CHJGlobalFun::str2qstr(oPktReq.GetCmdID());
	pCp = FindRoute(sCmdID);
	if (0 == pCp)
		return -2;

	//���ͱ���
	CTradePacket oPktRsp;
	int nRtn = 0;
	//qDebug( sCmdID, "���ͱ���" );
	nRtn = pCp->SendPacket(oPktReq,oPktRsp,uiTimeout);
	if (0 != nRtn)
	{
		CConnectPointSync** pCp = m_tblIfRouter[sCmdID];
		nRtn =  CCommHandler::Instance()->SendPacket(pCp, &oPktReq, &oPktRsp, uiTimeout);
		if (0 != nRtn)
		{
			//qDebug( sCmdID, LOG_CONNECT_SERVER_FAIL_TIPS );
			return nRtn;
		}
	}

	oPktRsp.GetHeader(stHeaderRsp);
	CTradePacketAndStruct::Packet2Struct(stBodyRsp, oPktRsp);

	//qDebug(sCmdID,stHeaderRsp.rsp_code);
	return 0;
};

const QUOTATION* CTraderCpMgr::Translate(CBroadcastPacket& oPktSrc)
{
	QUOTATION *qt = NULL;

	string sZipVal;
	string sInstID;
	string sName;
	oPktSrc.GetParameterVal("instID", sInstID);
	oPktSrc.GetParameterVal("name", sName);

	auto it = m_QMapQuotation.find(sInstID);
	if (it != m_QMapQuotation.end())
	{
		QUOTATION& stQuotation = it->second;
		qt = &stQuotation;

		// ��¼ԭ���飬����������������������ָ�
		/*QUOTATION stTempQt = stQuotation;*/
		if (0 != oPktSrc.GetParameterVal("sZipBuff", sZipVal))
		{
			auto vKey = oPktSrc.GetKeys();
			if (vKey.size() > 2)
			{
				TranslateUnzipPacket(oPktSrc, stQuotation);
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			TranslateZipPacket(oPktSrc, stQuotation);
		}
		/*if (!CheckQt(stQuotation))
		{
		m_QMapQuotation[sInstID] = stTempQt;
		return NULL;
		}*/
	}
	else
	{
		QUOTATION stQuotation;
		if (0 != oPktSrc.GetParameterVal("sZipBuff", sZipVal))
		{
			auto vKey = oPktSrc.GetKeys();
			if (vKey.size() > 2)
			{
				TranslateUnzipPacket(oPktSrc, stQuotation);
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			TranslateZipPacket(oPktSrc, stQuotation);
		}

		stQuotation.instID = sInstID;
		stQuotation.name = sName;
		m_QMapQuotation[sInstID] = stQuotation;
		qt = &m_QMapQuotation[sInstID];
	}

	return qt;
}


const QUOTATION* CTraderCpMgr::TranslateQH(CBroadcastPacket& oPktSrc)
{
	QUOTATION *qt = nullptr;

	string sZipVal;
	string sInstID;
	string sName;
	oPktSrc.GetParameterVal("instID", sInstID);
	oPktSrc.GetParameterVal("name", sName);

	auto it = m_QHMapQuotation.find(sInstID.c_str());
	if (it != m_QHMapQuotation.end())
	{
		QUOTATION& stQuotation = it->second;
		qt = &stQuotation;

		// ��¼ԭ���飬����������������������ָ�
		/*QUOTATION stTempQt = stQuotation;*/
		auto vKey = oPktSrc.GetKeys();
		if (vKey.size() > 2)
		{
			TranslateQHPacket(oPktSrc, stQuotation);
		}
		else
		{
			return nullptr;
		}

	}
	else
	{
		QUOTATION stQuotation;

		auto vKey = oPktSrc.GetKeys();
		if (vKey.size() > 2)
		{
			TranslateQHPacket(oPktSrc, stQuotation);
		}
		else
		{
			return nullptr;
		}

		stQuotation.instID = sInstID;
		stQuotation.name = sName;
		m_QHMapQuotation[QString::fromStdString(sInstID)] = stQuotation;
		qt = &m_QHMapQuotation[sInstID.c_str()];
	}
	return qt;
}


bool CTraderCpMgr::CheckQt(const QUOTATION& stQuotation)
{
	// �۸�ӵ͵�����ӵ����飨��2 ��1 ��1 ��2��
	QVector<unsigned int> vPrice;
	AddPrice(vPrice, stQuotation.m_Bid[1].m_uiPrice);
	AddPrice(vPrice, stQuotation.m_Bid[0].m_uiPrice);
	AddPrice(vPrice, stQuotation.m_Ask[0].m_uiPrice);
	AddPrice(vPrice, stQuotation.m_Ask[1].m_uiPrice);
	if (vPrice.size() > 1)
	{
		for (size_t i = 0; i < vPrice.size() - 1; i++)
		{
			if (vPrice[i] >= vPrice[i + 1])
			{
				return false;
			}
		}
	}

	// ������¼۲�������һ��֮�䣬��Ϊ��Ч���飬���ڴ��㷨δȷ������ʱע��
	/*if( stQuotation.m_uiLast > 0 )
	{
	if( stQuotation.m_Ask[0].m_uiPrice > 0 )
	{
	if( stQuotation.m_uiLast > stQuotation.m_Ask[0].m_uiPrice )
	{
	return false;
	}
	}

	if( stQuotation.m_Bid[0].m_uiPrice > 0 )
	{
	if( stQuotation.m_uiLast < stQuotation.m_Bid[0].m_uiPrice )
	{
	return false;
	}
	}
	}*/
	return true;
}

int CTraderCpMgr::TranslateUnzipPacket(CBroadcastPacket& oPktSrc, QUOTATION& stQuotation)
{
	double  dvlTmp = 0;
	QString strTmp = "";
	if (0 == oPktSrc.GetParameterVal("name", strTmp.toStdString()))
	{
		stQuotation.name = strTmp.toStdString();
	}

	if (0 == oPktSrc.GetParameterVal("sequenceNo", strTmp.toStdString()))
	{
		stQuotation.m_uiSeqNo = strTmp.toUInt();
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("quoteDate", strTmp.toStdString()))
	{
		stQuotation.m_uiDate = strTmp.toUInt();
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("quoteTime", strTmp.toStdString()))
	{
		//QVector<QString> v = strutils::explode(":",strTmp);
		QStringList  v = strTmp.split(QRegExp(":"));
		if (v.size() == 3)
		{
			int nHour = v[0].toInt();
			int nMin = v[1].toInt();
			int nSec = v[2].toInt();
			//stQuotation.m_uiTime = nHour * 10000 + nMin * 100 + nSec;
			stQuotation.m_uiTime = nHour * 10000000 + nMin * 100000 + nSec * 1000 + 0;
		}
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("open", strTmp.toStdString()))
	{
		//stQuotation.m_uiOpenPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
		stQuotation.m_uiOpenPrice = strTmp.toDouble();
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("high", strTmp.toStdString()))
	{
		//stQuotation.m_uiHigh = RoundToInt<double>(FromQString<double>(strTmp),2);
		stQuotation.m_uiHigh = strTmp.toDouble();
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("low", strTmp.toStdString()))
	{
		//stQuotation.m_uiLow = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("lastClose", strTmp.toStdString()))
	{
		//stQuotation.m_uilastClose = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("last", strTmp.toStdString()))
	{
		//stQuotation.m_uiLast = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("volume", strTmp.toStdString()))
	{
		//stQuotation.m_uiVolume = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("close", strTmp.toStdString()))
	{// ������
	 //stQuotation.m_uiClose = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask1", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[0].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask2", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[1].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask3", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[2].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask4", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[3].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask5", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[4].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot1", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[0].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot2", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[1].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot3", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[2].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot4", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[3].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot5", strTmp.toStdString()))
	{
		//stQuotation.m_Ask[4].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid1", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[0].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid2", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[1].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid3", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[2].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid4", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[3].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid5", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[4].m_uiPrice = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot1", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[0].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot2", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[1].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot3", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[2].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot4", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[3].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot5", strTmp.toStdString()))
	{
		//stQuotation.m_Bid[4].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("turnOver", strTmp.toStdString()))
	{//�� /����������
	 //stQuotation.m_dbTurnOver = (FromQString<double>(strTmp)/10000);
	 //stQuotation.m_uiTurnOver = RoundToInt<double>(FromQString<double>(strTmp),-2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("highLimit", strTmp.toStdString()))
	{// ��ͣ��
	 //stQuotation.m_uiHighLimit = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("lowLimit", strTmp.toStdString()))
	{// ��ͣ��
	 //stQuotation.m_uiLowLimit = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("average", strTmp.toStdString()))
	{// ��ͣ��
	 //stQuotation.m_uiAverage = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("weight", strTmp.toStdString()))
	{// ��ͣ��
	 //stQuotation.m_uiWeight = RoundToInt<double>(FromQString<double>(strTmp),3);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("Posi", strTmp.toStdString()))
	{
		//stQuotation.m_uiChiCangLiang = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("settle", strTmp.toStdString()))
	{
		//stQuotation.m_uiSettle = RoundToInt<double>(FromQString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("lastSettle", strTmp.toStdString()))
	{
		//stQuotation.m_uiLastSettle = RoundToInt<double>(FromQString<double>(strTmp),2);
	}
	return 0;

}

int CTraderCpMgr::TranslateQHPacket(CBroadcastPacket& oPktSrc, QUOTATION& stQuotation)
{
	//
	double  dvlTmp   = 0;
	string strTmp   = "";
	if (0 == oPktSrc.GetParameterVal("name", strTmp))
	{
		stQuotation.name = strTmp;
	}

	if (0 == oPktSrc.GetParameterVal("sequenceNo", strTmp))
	{
		stQuotation.m_uiSeqNo = QString::fromStdString(strTmp).toUInt();
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("quoteDate", strTmp))
	{
		stQuotation.m_uiDate = QString::fromStdString(strTmp).toUInt();
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("quoteTime", strTmp))
	{
		//QVector<QString> v = strutils::explode(":",strTmp);
		QStringList  v = QString::fromStdString(strTmp).split(QRegExp(":"));
		if (v.size() == 3)
		{
			int nHour = v[0].toInt();
			int nMin = v[1].toInt();
			int nSec = v[2].toInt();
			//stQuotation.m_uiTime = nHour * 10000 + nMin * 100 + nSec;
			stQuotation.m_uiTime = nHour * 10000000 + nMin * 100000 + nSec * 1000 + 0;
		}
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("open", strTmp))
	{
		stQuotation.m_uiOpenPrice = RoundToInt<double>(FromString<double>(strTmp),2);

	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("high", strTmp))
	{
		stQuotation.m_uiHigh = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("low", strTmp))
	{
		stQuotation.m_uiLow = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("lastClose", strTmp))
	{
		stQuotation.m_uilastClose = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("last", strTmp))
	{
		stQuotation.m_uiLast = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("volume", strTmp))
	{
		stQuotation.m_uiVolume = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("close", strTmp))
	{// ������
	 stQuotation.m_uiClose = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask1", strTmp))
	{
		stQuotation.m_Ask[0].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask2", strTmp))
	{
		stQuotation.m_Ask[1].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask3", strTmp))
	{
		stQuotation.m_Ask[2].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask4", strTmp))
	{
		stQuotation.m_Ask[3].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("ask5", strTmp))
	{
		stQuotation.m_Ask[4].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot1", strTmp))
	{
		stQuotation.m_Ask[0].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot2", strTmp))
	{
		stQuotation.m_Ask[1].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot3", strTmp))
	{
		stQuotation.m_Ask[2].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot4", strTmp))
	{
		stQuotation.m_Ask[3].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("askLot5", strTmp))
	{
		stQuotation.m_Ask[4].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid1", strTmp))
	{
		stQuotation.m_Bid[0].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid2", strTmp))
	{
		stQuotation.m_Bid[1].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid3", strTmp))
	{
		stQuotation.m_Bid[2].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid4", strTmp))
	{
		stQuotation.m_Bid[3].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bid5", strTmp))
	{
		stQuotation.m_Bid[4].m_uiPrice = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot1", strTmp))
	{
		stQuotation.m_Bid[0].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot2", strTmp))
	{
		stQuotation.m_Bid[1].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot3", strTmp))
	{
		//stQuotation.m_Bid[2].m_uiVol = (unsigned int)(FromQString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot4", strTmp))
	{
		stQuotation.m_Bid[3].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("bidLot5", strTmp))
	{
		stQuotation.m_Bid[4].m_uiVol = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("turnOver", strTmp))
	{//�� /����������
	 //stQuotation.m_dbTurnOver = (FromString<double>(strTmp)/10000);
	 stQuotation.m_uiTurnOver = RoundToInt<double>(FromString<double>(strTmp),-2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("highLimit", strTmp))
	{// ��ͣ��
	 stQuotation.m_uiHighLimit = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("lowLimit", strTmp))
	{// ��ͣ��
	 stQuotation.m_uiLowLimit = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("average", strTmp))
	{// ��ͣ��
	 stQuotation.m_uiAverage = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("weight", strTmp))
	{// ��ͣ��
	 stQuotation.m_uiWeight = RoundToInt<double>(FromString<double>(strTmp),3);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("Posi", strTmp))
	{
		stQuotation.m_uiChiCangLiang = (unsigned int)(FromString<unsigned int>(strTmp));
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("settle", strTmp))
	{
		stQuotation.m_uiSettle = RoundToInt<double>(FromString<double>(strTmp),2);
	}

	strTmp = "";
	if (0 == oPktSrc.GetParameterVal("lastSettle", strTmp))
	{
		stQuotation.m_uiLastSettle = RoundToInt<double>(FromString<double>(strTmp),2);
	}
	return 0;
}

int CTraderCpMgr::TranslateZipPacket(CBroadcastPacket& oPktSrc, QUOTATION& stQuotation)
{
	string sZipVal;
	string sInstID;
	oPktSrc.GetParameterVal("instID", sInstID);
	oPktSrc.GetParameterVal("sZipBuff", sZipVal);

	unsigned int uiTime = 0;

	//ȥ��\r\n
	sZipVal = strutils::stripNewLines(sZipVal);

	//base64����
	sZipVal = strutils::base64Decode(sZipVal);

	//int nLen = CEncode::unbase64(const_cast<char*>(sZipVal),sZipVal.length(),aZipData);
	//aZipData ���ն��FLV���Ӷ��� ����һ�ֽڵ�6bit��ʾFieldID,���2bit��ֵ+3=����ʵ��ֵռ���ֽ���,ʵ��ֵ���������ֽ���

	int nIdx = 0;
	char cField;
	char cLen;
	char acValues[6];
	//unsigned int uiValue;
	INT64 uiValue;
	unsigned char* lpPointer = (unsigned char*)sZipVal.data();
	int nLen = sZipVal.length();
	char cByte;

	while (nIdx < nLen)
	{
		cByte = lpPointer[nIdx];
		// BIT:0 - 5
		cField = (cByte & 0xFC) >> 2;//11111100;
									 // BIT:6 - 7   x + 3
		cLen = (cByte & 0x03) + 3;
		if (nIdx + cLen >= nLen)
		{
			//CRLog(E_ERROR,"���鱨�ĳ����쳣!");
			return false;
		}

		nIdx++;
		memset(acValues, 0, 6);
		memcpy(acValues, &lpPointer[nIdx], cLen);
		nIdx += cLen;
		double dbValue = 0.0;
		for (int i = 0; i < cLen; i++)
		{
			unsigned char chTmp = acValues[i];

			for (int j = 7; j >= 0; j--)
			{
				unsigned int nIndex = ((cLen - i - 1) * 8 + j);
				int nFlag = ((chTmp >> j) & 0x01);
				if (nFlag > 0)
				{
					dbValue += pow(2.0, (double)nIndex);
				}
			}
		}
		//uiValue = (unsigned int)dbValue;
		uiValue = (INT64)dbValue;
		switch (cField)
		{
		case FIELDKEY_LASTSETTLE:
			stQuotation.m_uiLastSettle = uiValue / 10;
			break;
		case FIELDKEY_LASTCLOSE:
			stQuotation.m_uilastClose = uiValue / 10;
			break;
		case FIELDKEY_OPEN:
			stQuotation.m_uiOpenPrice = uiValue / 10;
			break;
		case FIELDKEY_HIGH:
			stQuotation.m_uiHigh = uiValue / 10;
			break;
		case FIELDKEY_LOW:
			stQuotation.m_uiLow = uiValue / 10;
			break;
		case FIELDKEY_LAST:
			stQuotation.m_uiLast = uiValue / 10;
			break;
		case FIELDKEY_CLOSE:
			stQuotation.m_uiClose = uiValue / 10;
			break;
		case FIELDKEY_SETTLE:
			stQuotation.m_uiSettle = uiValue / 10;
			break;
		case FIELDKEY_BID1:
			stQuotation.m_Bid[0].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT1:
			stQuotation.m_Bid[0].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_BID2:
			stQuotation.m_Bid[1].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT2:
			stQuotation.m_Bid[1].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_BID3:
			stQuotation.m_Bid[2].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT3:
			stQuotation.m_Bid[2].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_BID4:
			stQuotation.m_Bid[3].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT4:
			stQuotation.m_Bid[3].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_BID5:
			stQuotation.m_Bid[4].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT5:
			stQuotation.m_Bid[4].m_uiVol = uiValue / 1000;
			break;


		case FIELDKEY_BID6:
			stQuotation.m_Bid[5].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT6:
			stQuotation.m_Bid[5].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_BID7:
			stQuotation.m_Bid[6].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT7:
			stQuotation.m_Bid[6].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_BID8:
			stQuotation.m_Bid[7].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT8:
			stQuotation.m_Bid[7].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_BID9:
			stQuotation.m_Bid[8].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT9:
			stQuotation.m_Bid[8].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_BID10:
			stQuotation.m_Bid[9].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_BIDLOT10:
			stQuotation.m_Bid[9].m_uiVol = uiValue / 1000;
			break;



		case FIELDKEY_ASK1:
			stQuotation.m_Ask[0].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT1:
			stQuotation.m_Ask[0].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_ASK2:
			stQuotation.m_Ask[1].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT2:
			stQuotation.m_Ask[1].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_ASK3:
			stQuotation.m_Ask[2].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT3:
			stQuotation.m_Ask[2].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_ASK4:
			stQuotation.m_Ask[3].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT4:
			stQuotation.m_Ask[3].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_ASK5:
			stQuotation.m_Ask[4].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT5:
			stQuotation.m_Ask[4].m_uiVol = uiValue / 1000;
			break;

		case FIELDKEY_ASK6:
			stQuotation.m_Ask[5].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT6:
			stQuotation.m_Ask[5].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_ASK7:
			stQuotation.m_Ask[6].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT7:
			stQuotation.m_Ask[6].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_ASK8:
			stQuotation.m_Ask[7].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT8:
			stQuotation.m_Ask[7].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_ASK9:
			stQuotation.m_Ask[8].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT9:
			stQuotation.m_Ask[8].m_uiVol = uiValue / 1000;
			break;
		case FIELDKEY_ASK10:
			stQuotation.m_Ask[9].m_uiPrice = uiValue / 10;
			break;
		case FIELDKEY_ASKLOT10:
			stQuotation.m_Ask[9].m_uiVol = uiValue / 1000;
			break;

		case FIELDKEY_VOLUME:
			stQuotation.m_uiVolume = uiValue / 1000;
			break;
		case FIELDKEY_WEIGHT:
			stQuotation.m_uiWeight = uiValue / 10;
			break;
		case FIELDKEY_HIGHLIMIT:
			stQuotation.m_uiHighLimit = uiValue / 10;
			break;
		case FIELDKEY_LOWLIMIT:
			stQuotation.m_uiLowLimit = uiValue / 10;
			break;
		case FIELDKEY_POSI:
			stQuotation.m_uiChiCangLiang = uiValue / 1000;
			break;
		case FIELDKEY_UPDOWN: // ֮ǰ���Ը��ֶ�������
							  //stQuotation.m_uiUpDown = uiValue /10;
			break;
		case FIELDKEY_TURNOVER:
			stQuotation.m_uiTurnOver = uiValue / 10;
			break;
		case FIELDKEY_AVERAGE:
			stQuotation.m_uiAverage = uiValue / 10;
			break;
		case FIELDKEY_SEQUENCENO:
			stQuotation.m_uiSeqNo = uiValue / 1000;
			break;
		case FIELDKEY_QUOTETIME: //���ֶδ�����Ҫ��ȷ��
			stQuotation.m_uiTime = uiValue;
			break;
		//case FIELDKEY_QUOTEDATE: //���ֶδ�����Ҫ��ȷ��
		//	stQuotation.m_uiDate = uiValue;
		//	break;
		case FIELDKEY_UPDOWNRATE: // ֮ǰ���Ը��ֶ�������
								  //stQuotation.m_uiUpDownRate = uiValue;
			break;
		default:
			CRLog(E_ERROR,"���鱨���ֶ����[%d]������!",cField);
			break;
		}
	}

	// �����ǵ� �����¼�-��ᣨ���գ���/���¼�
	if (stQuotation.m_uiLast != 0)
	{
		if (stQuotation.m_uiLastSettle != 0)
		{
			stQuotation.m_uiUpDown = stQuotation.m_uiLast - stQuotation.m_uiLastSettle;
			stQuotation.m_dUpDownRate = stQuotation.m_uiUpDown / (double)stQuotation.m_uiLastSettle * 100;
		}
		else
		{
			stQuotation.m_uiUpDown = stQuotation.m_uiLast - stQuotation.m_uilastClose;
			stQuotation.m_dUpDownRate = stQuotation.m_uiUpDown / (double)stQuotation.m_uilastClose * 100;
		}
	}
	else
	{
		stQuotation.m_uiUpDown = 0;
		stQuotation.m_dUpDownRate = 0.00;
	}

	// �����ǵ�����
	return 0;
}

// ���ܵ�����㲥���ĵ�ʱ��ͳһ���õĺ���
int CTraderCpMgr::DealRecvQuotation(CBroadcastPacket& pkt, const int& iBroadcastID, bool bPosi_PL /*= false*/)
{
	const QUOTATION* pQuotation = Translate(pkt);
	if (pQuotation == NULL)
	{
		// ����ʧ��
		return -1;
	}
	else
	{
		const string &sInstID = pQuotation->instID;
		if (bPosi_PL)
		{
			// ����ֲ�ӯ��
			//g_CusInfo.HandleRecvQuotation(*pQuotation);

			// ����
			//m_cPreOrder.HandleRecQuotation( sInstID, pQuotation->m_uiLast );

#ifdef _WRITE_LOG
			/*
			static QString csLog;
			static double dFactor = g_Global.m_dQTFactor;;
			csLog.Format("%s ���¼�%.2f ��һ��%.2f ��һ��%.2f", sInstID, pQuotation->m_uiLast/dFactor, pQuotation->m_Bid[0].m_uiPrice/dFactor, pQuotation->m_Ask[0].m_uiPrice/dFactor);
			g_Global.WriteLog(csLog);
			*/
#endif
		}

		// �㲥��Ϣ
		 m_mapBdr[iBroadcastID].Broadcast(MSG_RECV_QUOTATION, (void *)pQuotation, nullptr, false);//&sInstID
	}

	return 0;
}

CBroadcaster* CTraderCpMgr::GetBroadcaster(int nBdrType)
{
	QMapBDR::iterator it = m_mapBdr.find(nBdrType);
	if (it != m_mapBdr.end())
	{
		return &(it.value());// &(it.value);
	}
	else
	{
		return nullptr;
	}

	return nullptr;
}


void CTraderCpMgr::Subscribe(int nBdrMsgType, QWidget* val)
{
	m_mapBdr[nBdrMsgType].Subscribe(val);
}

void CTraderCpMgr::Unsubscribe(int nBdrMsgType, QWidget* val)
{
	m_mapBdr[nBdrMsgType].Unsubscribe(val);
}


/*���Ƕ�����һ��ȫ�ֹ�������ʵ�֣�����CHJGlobalFun********************************************************************************************************/
bool CTraderCpMgr::CheckRspCode(const QString &strCode, QString &strMsg, bool bShowMsg /*= true*/)
{
	if (strCode == "00000000")
	{
		return true;
	}
	else
	{
		if (bShowMsg)
		{
			if (strMsg.length() <= 0)
			{
				QMessageBox::warning(NULL, "������ʾ", "����ͨѶ�쳣!", QMessageBox::Yes, QMessageBox::Yes);
			}
			else
			{

				QMessageBox::warning(NULL, "������ʾ", strMsg, QMessageBox::Yes, QMessageBox::Yes);
			}
		}

		return false;
	}
}
/*��ȡCTraderCpMgr���ڴ����********************************************************************************************************/
// ���ݽ���Ʒ��ID��ȡ����Ʒ������
QString CTraderCpMgr::GetVarietyName(const QString &sID)
{
	for (size_t i = 0; i < m_vVariety.size(); i++)
	{
		if (m_vVariety.at(i).variety_id == sID)
		{
			return m_vVariety.at(i).name;
		}
	}

	return sID;
}
// ���ݽ�������ID��ȡ������������
QString CTraderCpMgr::GetExchName(const QString &sID)
{
	if (sID == "4061")
	{
		return "����";// ����Ϊ��combo����Ҫ��ȥ���˳���������������Ҫ����
	}

	for (size_t i = 0; i < m_vExchCode.size(); i++)
	{
		if (m_vExchCode.at(i).code_id == sID)
		{
			return m_vExchCode.at(i).code_desc;
		}
	}

	return sID;
}

// ���ݽ�������ID��ȡ������������
QString CTraderCpMgr::GetExchIDFromName(const QString &sName)
{
	if (sName == "����")
	{
		return "4061";// ����Ϊ��combo����Ҫ��ȥ���˳���������������Ҫ����
	}

	for (size_t i = 0; i < m_vExchCode.size(); i++)
	{
		if (m_vExchCode.at(i).code_desc == sName)
		{
			return m_vExchCode.at(i).code_id;
		}
	}

	return sName;
}
// ����ί��״̬ID��ȡί��״̬����
QString CTraderCpMgr::GetEntr_statName(const QString &sID)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vEntrState.size(); i++)
	{
		if (g_TraderCpMgr.m_vEntrState.at(i).code_id == sID)
			return g_TraderCpMgr.m_vEntrState.at(i).code_desc;
	}

	return sID;
}
// ���ݸ���״̬ID��ȡ����״̬����
QString CTraderCpMgr::GetCheck_staName(const QString &sID)
{
	for (size_t i = 0; i < m_vCheckState.size(); i++)
	{
		if (m_vCheckState.at(i).code_id == sID)
		{
			return m_vCheckState.at(i).code_desc;
		}
	}

	return sID;
}

// �����˻�״̬ID��ȡ�˻�״̬����
QString CTraderCpMgr::GetAcct_statName(const QString &sID)
{
	for (size_t i = 0; i < m_vAcctState.size(); i++)
	{
		if (m_vAcctState.at(i).code_id == sID)
			return m_vAcctState.at(i).code_desc;
	}

	return sID;
}
// ����֤��ID��ȡ֤������
QString CTraderCpMgr::GetIdTypeName(const QString &sID)
{
	for (size_t i = 0; i < m_vCertType.size(); i++)
	{
		if (m_vCertType.at(i).code_id == sID)
			return m_vCertType.at(i).code_desc;
	}

	return sID;

}
// ����֤�����ƻ��֤��id
QString CTraderCpMgr::GetIdTypeId(const QString &sName)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vCertType.size(); i++)
	{
		if (g_TraderCpMgr.m_vCertType.at(i).code_desc == sName)
			return g_TraderCpMgr.m_vCertType.at(i).code_id;
	}
	return sName;
}
// �������״̬ID��ȡ���״̬����
QString CTraderCpMgr::GetTake_statName(const QString &sID)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vTakeState.size(); i++)
	{
		if (g_TraderCpMgr.m_vTakeState.at(i).code_id == sID)
			return g_TraderCpMgr.m_vTakeState.at(i).code_desc;
	}
	return sID;
}
// �����������ID��ȡ�����������
QString CTraderCpMgr::GetDraw_typeName(const QString &sID)
{
	for (size_t i = 0; i < m_vDrawType.size(); i++)
	{
		if (m_vDrawType.at(i).code_id == sID)
			return m_vDrawType.at(i).code_desc;
	}
	return sID;
}
//
QString CTraderCpMgr::GetFCOrderStateName(const QString &sID)
{
	for (size_t i = 0; i < m_vFCOrderState.size(); i++)
	{
		if (m_vFCOrderState.at(i).code_id == sID)
		{
			return m_vFCOrderState.at(i).code_desc;
		}
	}
	return sID;
}

// �������״̬���ƻ�ȡ���״̬ID
QString CTraderCpMgr::GetTake_statID(const QString &sName)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vTakeState.size(); i++)
	{
		if (g_TraderCpMgr.m_vTakeState.at(i).code_desc == sName)
			return g_TraderCpMgr.m_vTakeState.at(i).code_id;
	}
	return sName;
}

QString CTraderCpMgr::GetMarketName(const QString &sID)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vMarketId.size(); i++)
	{
		if (g_TraderCpMgr.m_vMarketId.at(i).code_id == sID)
			return g_TraderCpMgr.m_vMarketId.at(i).code_desc;
	}
	return sID;
}

QString CTraderCpMgr::GetOffset_flagName(const QString &sID)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vOffsetFlag.size(); i++)
	{
		if (g_TraderCpMgr.m_vOffsetFlag.at(i).code_id == sID)
		{
			return g_TraderCpMgr.m_vOffsetFlag.at(i).code_desc;
		}
	}
	return sID;
}

QString CTraderCpMgr::GetDeli_flagName(const QString &sID)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vDeliFlag.size(); i++)
	{
		if (g_TraderCpMgr.m_vDeliFlag.at(i).code_id == sID)
		{
			return g_TraderCpMgr.m_vDeliFlag.at(i).code_desc;
		}
	}
	return sID;
}

QString CTraderCpMgr::GetBuySellName(const QString &sID)
{
	if (sID == "s")
	{
		return "��";
	}
	else if (sID == "b")
	{
		return "��";
	}
	return sID;
}

QString CTraderCpMgr::GetCancel_flagName(const QString &sID)
{
	for (size_t i = 0;i < g_TraderCpMgr.m_vCancelFlag.size(); i++)
	{
		if (g_TraderCpMgr.m_vCancelFlag.at(i).code_id == sID)
		{
			return g_TraderCpMgr.m_vCancelFlag.at(i).code_desc;
		}
	}
	return sID;
}

QString CTraderCpMgr::GetAccessWayName(const QString &sID)
{
	for (size_t i = 0;i < g_TraderCpMgr.m_vAccessWay.size(); i++)
	{
		if (g_TraderCpMgr.m_vAccessWay.at(i).code_id == sID)
		{
			return g_TraderCpMgr.m_vAccessWay.at(i).code_desc;
		}
	}
	return sID;
}

QString CTraderCpMgr::GetIn_account_flagName(const QString &sID)
{
	if (sID == "1")
	{
		return "��";
	}
	else
	{
		return sID;
	}
}

QString CTraderCpMgr::GetLongShortName(const QString &sID)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vLongShort.size(); i++)
	{
		if (g_TraderCpMgr.m_vLongShort.at(i).code_id == sID)
		{
			return g_TraderCpMgr.m_vLongShort.at(i).code_desc;
		}
	}
	return sID;
}

QString CTraderCpMgr::GetTerm_typeName(const QString &sID)
{
	for (size_t i = 0; i < g_TraderCpMgr.m_vTermType.size(); i++)
	{
		if (g_TraderCpMgr.m_vTermType.at(i).code_id == sID)
		{
			return g_TraderCpMgr.m_vTermType.at(i).code_desc;
		}
	}
	return sID;
}


/*��¼������ݴ������********************************************************************************************************/
// �Ƚϱ��ذ汾����������汾�ţ����С�ڷ������İ汾�ţ�����Ҫ���²���
bool CTraderCpMgr::CompareVersion(QString strLocalVersion, QString strSerVersion, int iCompare /*= 2 */)
{
	// ������ذ汾��������һ��Ϊ�գ�������������߼��������ҵ������޸ģ�
	if (strLocalVersion == "" || strSerVersion == "")
	{
		return false;
	}
	else
	{
		// �ֱ�ָ�ε�����
		QVector<QString> vecLocal, vecServer;
		//CHJGlobalFun::SplitStrToVector(strLocalVersion, ".", vecLocal);
		//CHJGlobalFun::SplitStrToVector(strSerVersion,   ".", vecServer);

		// ��ȡ���ء�����ˡ���iCompare����С�ĶΣ���Ҫ�Ƿ�ֹѭ����ʱ���������
		int iCliSize = vecLocal.size();
		int iSerSize = vecServer.size();
		int iComStep = iCliSize < iSerSize ? iCliSize : iSerSize;
		iComStep = iComStep < iCompare ? iComStep : iCompare;

		for (int i = 0; i < iComStep; i++)
		{
			/*if(atoi(vecServer.at(i)) > atoi(vecLocal.at(i)))
			{
			return true;
			}*/
		}

		// �����ͬ�����ڵ�ֵ��ȣ���Ƚϲ����ĳ���
		if (iSerSize > iCliSize)
		{
			return true;
		}
	}

	return false;
}

// ������б�������vector
void CTraderCpMgr::ClearCodeTableList()
{
	m_vExchCode.clear();
	m_vOffsetFlag.clear();
	m_vFeeCode.clear();
	m_vSubFeeCode.clear();
	m_vMarketId.clear();
	m_vEntrState.clear();
	m_vCancelFlag.clear();
	m_vTermType.clear();
	m_vAccessWay.clear();
	m_vCheckState.clear();
	m_vLongShort.clear();
	m_vTakeState.clear();
	m_vDrawType.clear();
	m_vCertType.clear();
	m_vAcctState.clear();
}

QString CTraderCpMgr::GetProdCodeName(const QString &sID)
{
	for (size_t i = 0; i < m_vProdCode.size(); i++)
	{
		if (m_vProdCode.at(i).prod_code == sID)
		{
			return m_vProdCode.at(i).prod_name;
		}
	}
	return sID;
}

QString CTraderCpMgr::TranslateIDToValue(const QString &sTitleID, const QString &sValue)
{
	QString sFinal;
	if (sTitleID == "exch_date" || sTitleID == "bk_plat_date" || sTitleID == "stor_date")//����ʱ��
		sFinal = CHJGlobalFun::FormatDate(sValue);
	else if (sTitleID == "market_id")//�����г�
		sFinal = GetMarketName(sValue);
	else if (sTitleID == "exch_code")//��������
		sFinal = GetExchName(sValue);
	else if (sTitleID == "offset_flag")//��ƽ��־
		sFinal = GetOffset_flagName(sValue);
	else if (sTitleID == "deli_flag")//���ձ�־��������
		sFinal = GetDeli_flagName(sValue);
	else if (sTitleID == "bs")//��������
		sFinal = GetBuySellName(sValue);
	else if (sTitleID == "entr_stat")//ί��״̬
		sFinal = GetEntr_statName(sValue);
	else if (sTitleID == "cancel_flag")//������־
		sFinal = GetCancel_flagName(sValue);
	else if (sTitleID == "access_way")//��������
		sFinal = GetAccessWayName(sValue);
	else if (sTitleID == "check_stat1" || sTitleID == "check_stat2")//����״̬
		sFinal = GetCheck_staName(sValue);
	else if (sTitleID == "in_account_flag")//�Ƿ�ɹ�
		sFinal = GetIn_account_flagName(sValue);
	else if (sTitleID == "long_short")//�ֲַ���
		sFinal = GetLongShortName(sValue);
	else if (sTitleID == "e_term_type" || sTitleID == "c_term_type" || sTitleID == "term_type" || sTitleID == "o_term_type")//ί������,��������,������Դ
		sFinal = GetTerm_typeName(sValue);
	else if (sTitleID == "market_id" || sTitleID == "accept_time" || sTitleID == "e_exch_time" || sTitleID == "c_exch_time" || sTitleID == "exch_time")//����ʱ��
		sFinal = CHJGlobalFun::FormatTime(sValue);
	else if (IsFloatTitle(sTitleID))//ί�м۸�
		sFinal = CHJGlobalFun::FormatFloat(sValue);
	else
		sFinal = sValue;

	return sFinal;
}

bool CTraderCpMgr::IsFloatTitle(const QString &sTitleID)
{
	const int iCount = 51;
	// ȥ��last_long_froz,last_can_use,curr_can_use,curr_can_get
	QString title[iCount] = { "entr_price", "match_price", "exch_bal", "exch_fare", "margin", "long_open_avg_price", "short_open_avg_price", "long_posi_avg_price", "short_posi_avg_price", "last_settle_price",
		"day_settle_price", "storage_cost", "last_bal", "curr_bal", "last_margin", "last_reserve", "out_bal",
		"in_bal","real_buy","real_sell","real_reserve","real_margin","base_margin","last_base_margin","deli_prepare","last_deli_prepare","deli_margin",
		"last_deli_margin","real_exch_fare","other_fare","pay_breach","take_breach","cov_surplus","mark_surplus","float_surplus","day_long_froz ",
		"last_forward_froz","day_forward_froz","inte_integral","puni_integral","wait_incr_inte","wait_incr_inte_tax","day_incr_inte","day_incr_inte_tax","last_take_margin","day_take_margin",
		"last_stor_fare_froz", "day_stor_fare_froz", "stor_price", "price", "fee_value" };//

	for (int i = 0; i < iCount; i++)
	{
		if (title[i] == sTitleID)
		{
			return true;
		}
	}
	return false;
}

// ��ȡ�ͻ�����ģ�嵽�ڴ�
void CTraderCpMgr::GetRsp2040()
{
	CTranMessage::Handle2040(m_rsp2040);
}

FareInfo CTraderCpMgr::GetBFareValue(const QString &sProdCode, const QString &sExchCode)
{
	FareInfo fi;
	for (size_t i = 0; i < m_rsp2040.alm_b_fare_list.size(); i++) //�������ؽ��
	{
		ArrayListMsg &aMsg = m_rsp2040.alm_b_fare_list.GetValue(i); //��ȡ����ĵ�һ��������

		if (aMsg.GetStringEx(0) == sProdCode.toStdString() && aMsg.GetStringEx(2) == sExchCode.toStdString())
		{
			fi.fare_mode_id = aMsg.GetStringEx(4).c_str();
			fi.fare_mode_name = aMsg.GetStringEx(5).c_str();
			fi.fare_value = aMsg.GetStringEx(6).c_str();
			return fi;
		}
	}

	return fi;
}
// ����Ʒ�ֻ�û�Ա��������Ϣ
FareInfo CTraderCpMgr::GetMFareValue(const QString &sProdCode, const QString &sExchCode)
{
	FareInfo fi;
	for (size_t i = 0; i < m_rsp2040.alm_m_fare_list.size(); i++) //�������ؽ��
	{
		ArrayListMsg &aMsg = m_rsp2040.alm_m_fare_list.GetValue(i); //��ȡ����ĵ�һ��������

		if (aMsg.GetStringEx(0) == sProdCode.toStdString() && aMsg.GetStringEx(2) == sExchCode.toStdString())
		{
			fi.fare_mode_id = aMsg.GetStringEx(4).c_str();
			fi.fare_mode_name = aMsg.GetStringEx(5).c_str();
			fi.fare_value = aMsg.GetStringEx(6).c_str();
			return fi;
		}
	}

	return fi;
}

ProdCodeInfo CTraderCpMgr::GetProdeCode(const QString &sProdCode)
{
	ProdCodeInfo info;

	for (size_t i = 0; i < m_vProdCode.size(); i++)
	{
		if (m_vProdCode.at(i).prod_code == sProdCode)
		{
			info = m_vProdCode.at(i);
			break;
		}
	}

	return info;
}

bool CTraderCpMgr::GetProdeCode(ProdCodeInfo& stProdCode, const QString &sProdCode)
{
	for (size_t i = 0; i < m_vProdCode.size(); i++)
	{
		if (m_vProdCode.at(i).prod_code == sProdCode)
		{
			stProdCode = m_vProdCode.at(i);
			return true;
		}
	}

	return false;
}



// �ӽ��������˳��ƽ��iHand��  20121107 ��ΪҪ�������ڳɽ���ˮ��Ϣ�����Բ�ɾ����ˮ
void CTraderCpMgr::RemoveMatchFlow(LISTDeferMatch &listMatch, int iHand)
{
	for (LISTDeferMatch::iterator it = listMatch.begin(); it != listMatch.end(); it++)
	{
		if (it->iHand >= iHand) // �����ǰ��ˮ��������С��ʣ�����������¼ƽ�����������˳�ѭ��
		{
			it->iHand -= iHand;
			break;
		}
		else // �����ǰ��ˮ������С��ʣ�����������¼δ��ƽ������������ɾ����ǰ��ˮ
		{
			//  ���֮ǰû�н�it->iHand��Ϊ0���µļ������
			if (it->iHand != 0)
			{
				iHand -= it->iHand;
				it->iHand = 0;
			}
		}
		/*
		if(it->iHand > iHand ) // �����ǰ��ˮ����������ʣ�����������¼ƽ�����������˳�ѭ��
		{
		it->iHand -= iHand;
		break;
		}
		else if(it->iHand == iHand) // ����պ���ȣ������ˮ��ƽ����ɾ������ˮ���˳�ѭ��
		{
		listMatch.erase(it);
		break;
		}
		else // �����ǰ��ˮ������С��ʣ�����������¼δ��ƽ������������ɾ����ǰ��ˮ
		{
		iHand -= it->iHand;
		it = listMatch.erase(it);
		}
		*/
	}
}

#if 0
// ���¼���ĳһ��Ʒ����ĳһ����λ�ϵ�ͳ����Ϣ���ֲ־��ۡ��ֲ�ӯ�����ֱֲ�֤��
void CTraderCpMgr::CalculateOtherValue(const QString &sProdCode, DeferPosiInfo &stDeferPosiInfo, bool bLong)
{
	// ����ֲ־����Լ����־���-----------------------------------------------------------------------------------------
	// ��ȡ�ɽ���ˮ
	const LISTDeferMatch &listMatch = stDeferPosiInfo.listMatch;

	// ��ȡ�ֲܳ���
	int iTotalHand = stDeferPosiInfo.iYesAmt; // ����ֳ�ʼ��
											  // �����ܱ�֤��
	double dTotalMoney = stDeferPosiInfo.fYesAvgPosPrice * stDeferPosiInfo.iYesAmt; // ����ֵĳֱֲ�֤���ʼ��

																					// modify by  20130222 ���ݽ���ͨ��Ҫ�󣬿��־��������������һ��
																					//// �ܵĿ��������������յ�ԭʼ��λ��ʼ��
																					//int iOpenTotalHand = stDeferPosiInfo.iYesOrgAmt;
																					//// �ܵĿ��ֽ������յ�ԭʼ���ֽ���ʼ��
																					//double dOpenTotalMoney = stDeferPosiInfo.dYesAvgOpenPosPrice * stDeferPosiInfo.iYesOrgAmt;

																					// �ܵĿ��������������յ�ԭʼ��λ��ʼ��
	int iOpenTotalHand = stDeferPosiInfo.iYesAmt;
	// �ܵĿ��ֽ������յ�ԭʼ���ֽ���ʼ��
	double dOpenTotalMoney = stDeferPosiInfo.dYesAvgOpenPosPrice * stDeferPosiInfo.iYesAmt;

	// ���Ͻ�ֵı�֤��
	for (LISTDeferMatch::const_iterator it = listMatch.begin(); it != listMatch.end(); ++it)
	{
		dTotalMoney += it->dPrice * it->iHand;
		iTotalHand += it->iHand;

#ifdef _WRITE_LOG
		static QString csLog;
		csLog.Format("Ʒ�֣�%s ���Ӽ۸�%.2f ������%d �ܽ�%.2f ��������%d",
			sProdCode, it->dPrice, it->iHand, dTotalMoney, iTotalHand);
		g_Global.WriteLog(csLog);
#endif

		// modify by  20130222 ���ݽ���ͨ��Ҫ�󣬿��־��������������һ��
		/*dOpenTotalMoney += it->dPrice * it->iTotalHand;
		iOpenTotalHand += it->iTotalHand;*/
		dOpenTotalMoney += it->dPrice * it->iHand;
		iOpenTotalHand += it->iHand;
	}
	stDeferPosiInfo.dAvgPosPrice = dTotalMoney / iTotalHand;
	stDeferPosiInfo.dAvgOpenPosPrice = dOpenTotalMoney / iOpenTotalHand;

	// ����ֲ�ӯ��-----------------------------------------------------------------------------------------
	stDeferPosiInfo.dPosi_PL = GetPosi_PL(sProdCode, stDeferPosiInfo.dAvgPosPrice, iTotalHand, bLong);

	// ����ֱֲ�֤��--------------------------------------------------------------------------------------
	//stDeferPosiInfo.dTotalFare = CalculateMagin(sProdCode, stDeferPosiInfo.dAvgPosPrice, iTotalHand);
	if (stDeferPosiInfo.iYesOrgAmt > 0)
	{
		stDeferPosiInfo.dTotalFare = stDeferPosiInfo.dYesPosiMoney * stDeferPosiInfo.iYesAmt / stDeferPosiInfo.iYesOrgAmt;
	}
	else
	{
		stDeferPosiInfo.dTotalFare = 0.00;
	}

	for (LISTDeferMatch::const_iterator it = listMatch.begin(); it != listMatch.end(); ++it)
	{
		stDeferPosiInfo.dTotalFare += it->dPosiMoney*it->iHand / it->iTotalHand;
	}

	// ����ֲ�ӯ��
}
#endif

// ���¼���ĳһ��Ʒ����ĳһ����λ�ϵ�ͳ����Ϣ���ֲ־��ۡ��ֲ�ӯ�����ֱֲ�֤��
void CTraderCpMgr::CalculateOtherValue(const QString &sProdCode, DeferPosiInfo &stDeferPosiInfo, bool bLong, bool bRefresh /*= false*/)
{
	// ����ֲ־����Լ����־���-----------------------------------------------------------------------------------------
	// ��ȡ�ɽ���ˮ
	const LISTDeferMatch &listMatch = stDeferPosiInfo.listMatch;

	// ��ȡ�ֲܳ���
	int iTotalHand = stDeferPosiInfo.iYesAmt; // ����ֳ�ʼ��
											  // �����ܱ�֤��
	double dTotalMoney = stDeferPosiInfo.fYesAvgPosPrice * stDeferPosiInfo.iYesAmt; // ����ֵĳֱֲ�֤���ʼ��

																					// modify by  20130222 ���ݽ���ͨ��Ҫ�󣬿��־��������������һ��
																					//// �ܵĿ��������������յ�ԭʼ��λ��ʼ��
																					//int iOpenTotalHand = stDeferPosiInfo.iYesOrgAmt;
																					//// �ܵĿ��ֽ������յ�ԭʼ���ֽ���ʼ��
																					//double dOpenTotalMoney = stDeferPosiInfo.dYesAvgOpenPosPrice * stDeferPosiInfo.iYesOrgAmt;

																					// �ܵĿ��������������յ�ԭʼ��λ��ʼ��
	int iOpenTotalHand = stDeferPosiInfo.iYesAmt;
	// �ܵĿ��ֽ������յ�ԭʼ���ֽ���ʼ��
	double dOpenTotalMoney = stDeferPosiInfo.dYesAvgOpenPosPrice * stDeferPosiInfo.iYesAmt;

	// ���Ͻ�ֵı�֤��
	for (LISTDeferMatch::const_iterator it = listMatch.begin(); it != listMatch.end(); ++it)
	{
		double d = it->dPrice;
		int h = it->iHand;
		dTotalMoney += it->dPrice * it->iHand;
		iTotalHand += it->iHand;

#ifdef _WRITE_LOG
		static QString csLog;
		csLog.Format("Ʒ�֣�%s ���Ӽ۸�%.2f ������%d �ܽ�%.2f ��������%d",
			sProdCode, it->dPrice, it->iHand, dTotalMoney, iTotalHand);
		g_Global.WriteLog(csLog);
#endif

		// modify by  20130222 ���ݽ���ͨ��Ҫ�󣬿��־��������������һ��
		/*dOpenTotalMoney += it->dPrice * it->iTotalHand;
		iOpenTotalHand += it->iTotalHand;*/
		dOpenTotalMoney += it->dPrice * it->iHand;
		iOpenTotalHand += it->iHand;
	}
	stDeferPosiInfo.dAvgPosPrice = dTotalMoney / iTotalHand;
	stDeferPosiInfo.dAvgOpenPosPrice = dOpenTotalMoney / iOpenTotalHand;

	if (bRefresh)
	{
		// mod by Jerry Lee, 2013-3-23, ͨ����ѯ��óֲ־��ۺͿ��־��ۣ����������˲�һ�µ��������
		Rsp1020 rsp1020;
		//if(CTranMessage::Handle1020(rsp1020, '0', '0', '0', '0', '1', '0', true) == 0)
		//{
		//	for (int j = 0; j < rsp1020.htm_td_info.size(); j++)
		//	{
		//		QString s = rsp1020.htm_td_info.GetQString(j, "td_prod_code");
		//		if(s == sProdCode)
		//		{
		//			double dAvgPosPrice = atof(rsp1020.htm_td_info.GetQString(j, 
		//				bLong?"td_long_posi_avg_price":"td_short_posi_avg_price"));
		//			double dAvgOpenPosPrice = atof(rsp1020.htm_td_info.GetQString(j, 
		//				bLong?"td_long_open_avg_price":"td_short_open_avg_price"));
		//			//stDeferPosiInfo.dAvgPosPrice = dAvgPosPrice;
		//			stDeferPosiInfo.dAvgOpenPosPrice = dAvgOpenPosPrice;
		//			stDeferPosiInfo.dSvrAvgPosPrice = dAvgPosPrice;

		//			break;
		//		}
		//	}
		//}
	}
	else
	{
		for (int j = 0; j < m_rsp1020.htm_td_info.size(); j++)
		{
			string s = m_rsp1020.htm_td_info.GetString(j, "td_prod_code");
			if (s == sProdCode.toStdString())
			{
				double dAvgPosPrice =CHJGlobalFun::str2qstr( m_rsp1020.htm_td_info.GetString(j,
					bLong ? "td_long_posi_avg_price" : "td_short_posi_avg_price")).toFloat();
				double dAvgOpenPosPrice = CHJGlobalFun::str2qstr(m_rsp1020.htm_td_info.GetString(j,
					bLong ? "td_long_open_avg_price" : "td_short_open_avg_price")).toFloat();
				//stDeferPosiInfo.dAvgPosPrice = dAvgPosPrice;
				stDeferPosiInfo.dAvgOpenPosPrice = dAvgOpenPosPrice;
				stDeferPosiInfo.dSvrAvgPosPrice = dAvgPosPrice;

				break;
			}
		}
	}

	//

	// ����ֲ�ӯ��-----------------------------------------------------------------------------------------
	stDeferPosiInfo.dPosi_PL = GetPosi_PL(sProdCode, stDeferPosiInfo.dAvgPosPrice, iTotalHand, bLong);

	// ����ֱֲ�֤��--------------------------------------------------------------------------------------
	//stDeferPosiInfo.dTotalFare = CalculateMagin(sProdCode, stDeferPosiInfo.dAvgPosPrice, iTotalHand);
	if (stDeferPosiInfo.iYesOrgAmt > 0)
	{
		stDeferPosiInfo.dTotalFare = stDeferPosiInfo.dYesPosiMoney * stDeferPosiInfo.iYesAmt / stDeferPosiInfo.iYesOrgAmt;
	}
	else
	{
		stDeferPosiInfo.dTotalFare = 0.00;
	}

	for (LISTDeferMatch::const_iterator it = listMatch.begin(); it != listMatch.end(); ++it)
	{
		stDeferPosiInfo.dTotalFare += it->dPosiMoney*it->iHand / it->iTotalHand;
	}

	// ����ֲ�ӯ��
}

// ����һ��Ʒ�ֵĳֲ�ӯ��
double CTraderCpMgr::GetPosi_PL(const QString &sProdCode, double dAvgPosiPrice, int iTotalHand, bool bLong)
{
	// ��ȡ��Ʒ�ֵļ�����λ����ÿ�ֵĿ�����
	ProdCodeInfo& info = GetProdeCode(sProdCode);
	double dUnite = 0.00;
	if (!info.prod_code.isEmpty())
	{
		dUnite = info.measure_unit;
	}

	// ����Ʒ�ֻ������
	const QUOTATION &qt = m_QMapQuotation[sProdCode.toStdString()];

	// ��ȡ���¼�
	unsigned int uiOrg = qt.m_uiLast > 0 ? qt.m_uiLast : qt.m_uiLastSettle; // ������¼�û����������
	double dNewest = (double)uiOrg / g_Global.m_dQTFactor; // ��ȡ���¼�

														   // ��ȡӯ���ۣ�ע������ǿղֵĻ���ӯ���෴
	double dPriceDif = bLong ? (dNewest - dAvgPosiPrice) : (dAvgPosiPrice - dNewest);

	// �ü���ֲ�ӯ�� = �����¼�-�ֲ־��ۣ�*�ֲܳ�*������λ
	double dMoney = dPriceDif * iTotalHand * CHJCommon::HandToGram(sProdCode, dUnite);

	// ����ղֵ�ʱ��ֲ�ӯ��Ϊ0��ʱ����ʾ-0.00������
	if (dMoney < 0.001 && dMoney > -0.001)
	{
		dMoney = 0.00;
	}

	/*
	// ��ȡ��Ʒ�ֵļ�����λ����ÿ�ֵĿ�����
	double dUnite = GetProdeCode(sProdCode).measure_unit;

	// ����Ʒ�ֻ������
	const QUOTATION &qt = m_QMapQuotation[sProdCode];

	// ��ȡ���¼�
	unsigned int uiOrg = qt.m_uiLast > 0 ? qt.m_uiLast : qt.m_uiLastSettle; // ������¼�û����������
	unsigned int u = uiOrg - dAvgPosiPrice*g_Global.m_dQTFactor;

	// ��ȡӯ���ۣ�ע������ǿղֵĻ���ӯ���෴
	int nProfit = bLong ? u : -1*u;

	// �ü���ֲ�ӯ�� = �����¼�-�ֲ־��ۣ�*�ֲܳ�*������λ
	double dMoney = (nProfit * iTotalHand * CHJCommon::HandToGram(sProdCode, dUnite))/g_Global.m_dQTFactor;

	// ����ղֵ�ʱ��ֲ�ӯ��Ϊ0��ʱ����ʾ-0.00������
	if(dMoney < 0.001 && dMoney > -0.001)
	{
	dMoney = 0.00;
	}
	*/


	return dMoney;
}
/*
��������ƽ�ֳ������ͷŶ����λ
instID��������Ʒ��
bLong��trueΪ��֣�falseΪ�ղ�
bExist���ñʳ�����Ӧ�ı�����ˮ�Ƿ����ڴ��д��ڣ�һ������¶�Ϊtrue
false��������£�һ�ʲ��ֳɽ��ı��������������������µ�¼��������������
������ˮ�Լ��ɽ���ˮ�����ǲ������ͱ�����ˮ���������ڳɽ���ˮ
���ᴦ����ò�λ�������Ļ��ѳɽ��Ĳ�λû�м���������Ҫ�����ﴦ��
iTotalAmount���ܵı�������
iRemainAmount��ʣ������
*/
bool CTraderCpMgr::DealDeferCancelFreezePosi(const QString &instID, bool bLong, bool bExist, int iTotalAmount, int iRemainAmount)
{
	// ���ݺ�Լ�����ȡ��Ʒ�ֵ��ڸò�λ�ϵĳֲ���Ϣ
	QMap<QString, DeferPosi>::iterator itPosi = m_QMapDeferPosi.find(instID);
	DeferPosiInfo &info = bLong ? itPosi.value().infoLong : itPosi.value().infoShort;

	// ���ݸó����ı��ر����Ų����Ƿ��ڱ�����ˮ�д���
	if (bExist)
	{
		// ȡ��������ʱ�򶳽�Ŀ��ò�λ
		info.iUsefulAmt += iRemainAmount;

		return true;
	}
	else
	{
		// ���ڴ���һ�ʱ������ֳɽ��ĳ�����û�б�����Ϣ�����������տ�ʼ��¼��ʱ����֣�
		// �������������δ�ɽ�����֤���гɽ�
		// ģ��һ�α�����ˮ���������òּ���1��
		int iMatchHand = iTotalAmount - iRemainAmount;
		if (iMatchHand > 0)
		{
			info.iUsefulAmt -= iMatchHand;

			return true;
		}
	}

	return false;
}

int CTraderCpMgr::GetInstStatePos(const QString &sProdCode)
{
	for (size_t i = 0; i < m_vInstState.size(); i++)
	{
		if (m_vInstState.at(i).instID == sProdCode.toStdString())
			return i;
	}

	return -1;
}

QString CTraderCpMgr::GetInsStateID(const QString &sInsID)
{
	for (size_t i = 0; i < m_vInstState.size(); i++)
	{
		if (m_vInstState.at(i).instID == sInsID.toStdString())
		{
			return m_vInstState.at(i).tradeState.c_str();
		}
	}

	return "";
}
// ��ȡ�޷������εĹ������¼�
unsigned int CTraderCpMgr::GetLastPrice(const QUOTATION &qt)
{
	unsigned int uiOrg = qt.m_uiLast > 0 ? qt.m_uiLast : qt.m_uiLastSettle;

	if (uiOrg > 0)
		return uiOrg;
	else
		return qt.m_uilastClose;
}
// ��ȡdouble�Ĺ������¼�
double CTraderCpMgr::GetLastPriceEx(const QUOTATION &qt)
{
	return GetLastPrice(qt) / g_Global.m_dQTFactor;
}
// ��ʼ���ͻ����ݣ�csTitle �����ļ��е�title��pFunAsk��Ӧ���������ݵĺ�����ַ��pFunLoad��Ӧ�ļ������ݵĺ�����ַ
bool CTraderCpMgr::IniBasicData(const QString &csTitle, PFunTypeAsk pFunAsk, PFunTypLoad pFunLoad)
{
	bool bLoad = false;

	QString strDataPath = g_Global.GetDataIniPath();
	char buf[500] = { 0 };
	QString sValue;

	// ��ȡ�ļ��б���Ŀͻ���
	//::GetPrivateProfileQString("info", csTitle, "", buf, sizeof(buf), strDataPath);
	sValue = buf;
	int iPos = sValue.indexOf("��"); // ��ȡ�ͻ��ŵķָ���
	if (iPos != -1)
	{
		// ����ͻ�����ͬ
		if (sValue.mid(0, iPos) == g_Global.m_strUserID)
		{
			// ��ȡ��һ������+ֵ���ַ���
			sValue = sValue.mid(iPos + 2);

			iPos = sValue.indexOf("��"); // ��ȡ�ͻ��ŵķָ���
			if (iPos != -1)
			{
				// ��ȡ���ݶ�Ӧ����һ������
				QString sLastExchDate = sValue.mid(0, iPos);
				// �뵱ǰʵ�ʵ���һ�����նԱ�
				if (sLastExchDate == g_Global.m_strLast_Exch_Date)
				{
					// �����ͬ����ֱ���ñ��ص����ݼ���
					ArrayListMsg alm_result;
					alm_result.Parse(sValue.mid(iPos + 2).toStdString());

					(this->*pFunLoad)(alm_result);
				}
				else
				{
					// ��������ղ����������Ϊ���������������
					bLoad = true;
				}
			}
			else
			{
				bLoad = true;
			}
		}
		else
		{
			bLoad = true;
		}
	}
	else
	{
		// ���û�ҵ��ָ������Ϊ���������������
		bLoad = true;
	}

	// ������ر�������ݲ������µĻ���û�У������������������
	if (bLoad)
	{
		ArrayListMsg alm_result;
		if ((this->*pFunAsk)(alm_result))
		{
			QString sWriteData = g_Global.m_strUserID + "��" + g_Global.m_strLast_Exch_Date + "��" + CHJGlobalFun::str2qstr(alm_result.ToString());
			//::WritePrivateProfileQString("Info", csTitle, sWriteData,strDataPath); 
			(this->*pFunLoad)(alm_result);
		}
		else
		{
			return false;
		}
	}

	return true;
}

// �����������������ͳһ���õĺ���
bool CTraderCpMgr::AskForData(const QString &sReqTitle, QVector< pair<QString, QString> > &vecPara, const ArrayListMsg &almViewField, ArrayListMsg &alm_result)
{
	Rsp6002 rsp6002;

	// ��Ӳ�ѯ����
	//CHJGlobalFun::PairAdd(vecPara, "start_date", g_Global.m_strLast_Exch_Date); 
	//CHJGlobalFun::PairAdd(vecPara, "end_date", g_Global.m_strLast_Exch_Date);

	// ���������������������
	//if( CTranMessage::Handle6002(rsp6002, sReqTitle, almViewField, vecPara, 500 ) == 0 )
	//{
	//	alm_result = rsp6002.alm_result;
	//	return true;
	//}
	//else
	{
		return false;
	}
}
// �����������ͻ������ʽ�����
bool CTraderCpMgr::AskForFundBaseData(ArrayListMsg &alm_result)
{
	QVector< pair<QString, QString> > vecPara;

	// ��ȡ�������ID ������curr_bal�� ���տ��ã�curr_can_use�� ���������֤�𶳽ᣨday_take_margin�� ���ղִ��Ѷ��ᣨday_stor_fare_froz��
	ArrayListMsg almViewField;
	almViewField.Parse("curr_bal��curr_can_use��day_take_margin��day_stor_fare_froz��");

	bool bReturn = AskForData("AcctFundHis", vecPara, almViewField, alm_result);
	if (bReturn && alm_result.size() == 0)
	{
		alm_result.Parse("0��0��0��0����");
	}

	return bReturn;
}
// ���������ʽ����ݵ��ڴ�
void CTraderCpMgr::LoadFundBaseData(const ArrayListMsg &alm_result)
{
	// �������ݵ��ڴ棬ע�⵽�����ȡĳһ���ֶε�ֵ���ǲ������
	const ArrayListMsg &aMsg = alm_result.GetValue(0); // ��ȡ�����һ������

	m_stFundInfo.dAllBalance += aMsg.GetValue<double>(0);

	//m_stFundInfo.dUseFulBal += aMsg.GetValue<double>(1);
	m_stFundInfo.dUseFulBal = m_stFundInfo.dUseFulBal + aMsg.GetValue<double>(1) - aMsg.GetValue<double>(2) - aMsg.GetValue<double>(3);
}

// �����������ͻ���������
bool CTraderCpMgr::AskForDeferPosiBaseData(ArrayListMsg &alm_result)
{
	QVector< pair<QString, QString> > vecPara;
	// ��Ӳ�ѯ����
	//CHJGlobalFun::PairAdd(vecPara, "prod_code", "");

	ArrayListMsg almViewField; // ��ȡ�������ID
							   //almViewField.Parse("exch_date��prod_code��last_long_amt��last_short_amt��curr_long_amt��curr_short_amt��curr_long_can_use��curr_short_can_use��open_long_amt��open_short_amt��cov_long_amt��cov_short_amt��deli_long_amt��deli_short_amt��midd_open_long_amt��midd_open_short_amt��long_open_avg_price��short_open_avg_price��long_posi_avg_price��short_posi_avg_price��last_settle_price��day_settle_price��");
	almViewField.Parse("prod_code��curr_long_amt��curr_short_amt��curr_long_can_use��curr_short_can_use��day_settle_price��long_open_avg_price��short_open_avg_price��");

	return AskForData("AcctDeferPosiHis", vecPara, almViewField, alm_result);
}
// �����������ݵ��ڴ�
void CTraderCpMgr::LoadDeferPosiBaseData(const ArrayListMsg &alm_result)
{
	size_t iTotalCount = alm_result.size();

	// �������ݵ��ڴ棬ע�⵽�����ȡĳһ���ֶε�ֵ���ǲ�����ţ������ű��˵Ļ��������Ƿ��Ǹ����ֶ�ID��
	for (size_t i = 0; i < iTotalCount; i++)
	{
		const ArrayListMsg &aMsg = alm_result.GetValue(i); // ��ȡ�����һ������

														   // ȥ�����һ�е�ͳ��
		if (i == iTotalCount - 1 && aMsg.GetStringEx(0).empty())
			break;

		// ��ȡ��ԼƷ��
		QString sProdCode = aMsg.GetStringEx(0).c_str();

		// ��ȡ�ú�Լ�����Ӧ�ĳֲ���Ϣ
		QMap<QString, DeferPosi>::iterator it = m_QMapDeferPosi.find(sProdCode);
		if (it == m_QMapDeferPosi.end())
		{
			DeferPosi stDeferPosi;
			stDeferPosi.sProdCode = sProdCode;
			it = m_QMapDeferPosi.insert(sProdCode, stDeferPosi);
		}
		DeferPosi &stDeferPosi = it.value();

		//��� ���ն����Ϣ���ֲܳ֡����ò֡���֣�
		stDeferPosi.infoLong.iCurrAllAmt += CHJGlobalFun::str2qstr( aMsg.GetStringEx(1)).toInt(); // ��ȡ������ֲܳ���Ϊ������ֲܳ�
		stDeferPosi.infoLong.iYesOrgAmt = stDeferPosi.infoLong.iYesAmt = CHJGlobalFun::str2qstr(aMsg.GetStringEx(1)).toUInt(); // ���ڲ�λ���ݼ�¼���ǽ���ģ������ڴ��е����Ӧ���Ǳ����е��ֲܳ�
		stDeferPosi.infoLong.iUsefulAmt += CHJGlobalFun::str2qstr(aMsg.GetStringEx(3)).toUInt(); //  ��ȡ����Ŀ��ò���Ϊ����Ŀ��ò�

																		  // ������տղ���Ϣ
		stDeferPosi.infoShort.iCurrAllAmt += CHJGlobalFun::str2qstr(aMsg.GetStringEx(2)).toUInt();
		stDeferPosi.infoShort.iYesOrgAmt = stDeferPosi.infoShort.iYesAmt = CHJGlobalFun::str2qstr(aMsg.GetStringEx(2)).toUInt(); //
		stDeferPosi.infoShort.iUsefulAmt += CHJGlobalFun::str2qstr(aMsg.GetStringEx(4)).toUInt();

		// ��¼���ճֲ־��ۣ���ᣩ
		stDeferPosi.infoLong.fYesAvgPosPrice = CHJGlobalFun::str2qstr(aMsg.GetStringEx(5)).toUInt();
		stDeferPosi.infoShort.fYesAvgPosPrice = CHJGlobalFun::str2qstr(aMsg.GetStringEx(5)).toUInt();

		// ��¼���յĿ��־���
		stDeferPosi.infoLong.dYesAvgOpenPosPrice = CHJGlobalFun::str2qstr(aMsg.GetStringEx(6)).toUInt();
		stDeferPosi.infoShort.dYesAvgOpenPosPrice = CHJGlobalFun::str2qstr(aMsg.GetStringEx(7)).toUInt();

		// ��¼���ձ�֤����Ϣ
		if (stDeferPosi.infoLong.iYesOrgAmt > 0)
		{
			stDeferPosi.infoLong.dYesPosiMoney = CalculateMagin(sProdCode, stDeferPosi.infoLong.fYesAvgPosPrice, stDeferPosi.infoLong.iYesOrgAmt, false);
		}
		if (stDeferPosi.infoShort.iYesOrgAmt > 0)
		{
			stDeferPosi.infoShort.dYesPosiMoney = CalculateMagin(sProdCode, stDeferPosi.infoShort.fYesAvgPosPrice, stDeferPosi.infoShort.iYesOrgAmt, false);
		}

		// ����ͳ����Ϣ
		CalculateOtherValue(stDeferPosi.sProdCode, stDeferPosi.infoLong, true);
		CalculateOtherValue(stDeferPosi.sProdCode, stDeferPosi.infoShort, false);

		m_QMapDeferPosi[stDeferPosi.sProdCode] = stDeferPosi;
	}
}

// �����������ͻ�����Զ������
bool CTraderCpMgr::AskForForwardPosiBaseData(ArrayListMsg &alm_result)
{
	QVector< pair<QString, QString> > vecPara;
	// ��Ӳ�ѯ����
	/*CHJGlobalFun::PairAdd(vecPara, "prod_code", "");*/

	ArrayListMsg almViewField; // ��ȡ�������ID
							   // ��Լ����ĵ�ǰ��֡ĵ�ǰ�ղ֡Ŀ��ö�֡Ŀ��ÿղ֡����ս����
	almViewField.Parse("prod_code��curr_long_amt��curr_short_amt��curr_long_can_use��curr_short_can_use��settle_price��");

	return AskForData("AcctForwardPosiHis", vecPara, almViewField, alm_result);
}
// ��������Զ�����ݵ��ڴ�
void CTraderCpMgr::LoadForwardPosiBaseData(const ArrayListMsg &alm_result)
{
	size_t iTotalCount = alm_result.size();

	// �������ݵ��ڴ棬ע�⵽�����ȡĳһ���ֶε�ֵ���ǲ�����ţ������ű��˵Ļ��������Ƿ��Ǹ����ֶ�ID��
	for (size_t i = 0; i < iTotalCount; i++)
	{
		const ArrayListMsg &aMsg = alm_result.GetValue(i); // ��ȡ�����һ������

														   // ȥ�����һ�е�ͳ��
		if (i == iTotalCount - 1 && aMsg.GetStringEx(0).empty())
			break;

		// ��ȡ��ԼƷ��
		QString sProdCode = aMsg.GetStringEx(0).c_str();

		// ��ȡ�ú�Լ�������ڴ��ж�Ӧ�ĳֲ���Ϣ
		QMap<QString, DeferPosi>::iterator it = m_QMapDeferPosi.find(sProdCode);
		if (it == m_QMapDeferPosi.end())
		{
			// ��������������
			DeferPosi stDeferPosi;
			stDeferPosi.sProdCode = sProdCode;
			it = m_QMapDeferPosi.insert(sProdCode, stDeferPosi);
			//it = Insert_Pair.key;
		}
		DeferPosi &stDeferPosi = it.value();

		// ��¼���ն����Ϣ���ֲܳ֡���֡����ò֣�
		stDeferPosi.infoLong.iCurrAllAmt += CHJGlobalFun::str2qstr(aMsg.GetStringEx(1)).toUInt(); // ��ȡ������ֲܳ���Ϊ������ֲܳ�
		stDeferPosi.infoLong.iYesOrgAmt = stDeferPosi.infoLong.iYesAmt = CHJGlobalFun::str2qstr(aMsg.GetStringEx(1)).toUInt(); // ���ڲ�λ���ݼ�¼���ǽ���ģ������ڴ��е����Ӧ���Ǳ����е��ֲܳ�
		stDeferPosi.infoLong.iUsefulAmt += CHJGlobalFun::str2qstr(aMsg.GetStringEx(3)).toUInt(); //  ��ȡ����Ŀ��ò���Ϊ����Ŀ��ò�

																		  // ��¼���տղ���Ϣ
		stDeferPosi.infoShort.iCurrAllAmt += CHJGlobalFun::str2qstr(aMsg.GetStringEx(2)).toUInt();
		stDeferPosi.infoShort.iYesOrgAmt = stDeferPosi.infoShort.iYesAmt = CHJGlobalFun::str2qstr(aMsg.GetStringEx(2)).toUInt(); //
		stDeferPosi.infoShort.iUsefulAmt += CHJGlobalFun::str2qstr(aMsg.GetStringEx(4)).toUInt();

		// ��¼���ճֲ־��ۣ���ᣩ
		stDeferPosi.infoLong.fYesAvgPosPrice = CHJGlobalFun::str2qstr(aMsg.GetStringEx(5)).toUInt();
		stDeferPosi.infoShort.fYesAvgPosPrice = CHJGlobalFun::str2qstr(aMsg.GetStringEx(5)).toUInt();

		// ��¼���ձ�֤����Ϣ
		if (stDeferPosi.infoLong.iYesOrgAmt > 0)
		{
			stDeferPosi.infoLong.dYesPosiMoney = CalculateMagin(sProdCode, stDeferPosi.infoLong.fYesAvgPosPrice, stDeferPosi.infoLong.iYesOrgAmt, false);
		}
		if (stDeferPosi.infoShort.iYesOrgAmt > 0)
		{
			stDeferPosi.infoShort.dYesPosiMoney = CalculateMagin(sProdCode, stDeferPosi.infoShort.fYesAvgPosPrice, stDeferPosi.infoShort.iYesOrgAmt, false);
		}

		// ����ͳ����Ϣ
		//CalculateOtherValue(stDeferPosi.sProdCode, stDeferPosi.infoLong, true);
		//CalculateOtherValue(stDeferPosi.sProdCode, stDeferPosi.infoShort, false);

		m_QMapDeferPosi[stDeferPosi.sProdCode] = stDeferPosi;
	}
}

// �����������ͻ����տ������
bool CTraderCpMgr::AskForStoreBaseData(ArrayListMsg &alm_result)
{
	QVector< pair<QString, QString> > vecPara;
	// ��Ӳ�ѯ����
	//CHJGlobalFun::PairAdd(vecPara, "variety_id", "");

	// ��ȡ�������ID����Լ���룬��ǰ��棨curr_amt������ǰ���ã�curr_can_use������ǰ���ᣨcurr_can_get��
	ArrayListMsg almViewField;
	almViewField.Parse("variety_id��curr_amt��curr_can_use��");

	return AskForData("AcctStorageHis", vecPara, almViewField, alm_result);
}
// �������տ�����ݵ��ڴ�
void CTraderCpMgr::LoadStoreBaseData(const ArrayListMsg &alm_result)
{
	size_t iTotalCount = alm_result.size();

	// �������ݵ��ڴ棬ע�⵽�����ȡĳһ���ֶε�ֵ���ǲ�����ţ������ű��˵Ļ��������Ƿ��Ǹ����ֶ�ID��
	for (size_t i = 0; i < iTotalCount; i++)
	{
		const ArrayListMsg &aMsg = alm_result.GetValue(i); // ��ȡ�����һ������

														   // ȥ�����һ�е�ͳ��
		if (i == iTotalCount - 1 && CHJGlobalFun::str2qstr(aMsg.GetStringEx(0)).isEmpty())
			break;

		// ��ȡ��ԼƷ��
		const QString &sProdCode = CHJGlobalFun::str2qstr(aMsg.GetStringEx(0));

		// ��ȡ�ú�Լ�����Ӧ�Ŀ����Ϣ
		QMap<QString, StoreInfo>::iterator it = m_QMapStoreInfo.find(sProdCode);
		if (it == m_QMapStoreInfo.end())
		{
			StoreInfo stStore;
			it = m_QMapStoreInfo.insert(sProdCode, stStore);

		}
		StoreInfo &stStoreInfo = it.value();

		// ��¼�����Ϣ
		stStoreInfo.iAllAmt += aMsg.GetValue<int>(1);   // ��ȡ������ܿ����Ϊ������ܿ��
		stStoreInfo.iUseFulAmt += aMsg.GetValue<int>(2); // ��ȡ����Ŀ��ÿ����Ϊ����Ŀ��ÿ��

#ifdef _WRITE_SPOT_LOG
		QString csLog;
		csLog.Format("��ʼ��%s�Ŀ�棬�ܿ��Ϊ%d�����ÿ��Ϊ��%d",
			sProdCode,
			stStoreInfo.iAllAmt,
			stStoreInfo.iUseFulAmt);
		g_Global.WriteLog(csLog);
#endif
	}
}



// �ò��ִ���
void CTraderCpMgr::CalSpotSellMatchFee(const ProdCodeInfo &info, double dPrice, int iHand, double &dMatchBal, double &dExchFare)
{
	// ��Լ����
	const QString &sProd_Code = info.prod_code;

	// ��ȡÿ�ֵļ�����λ ���ˣ�
	double dUnite = CHJCommon::HandToGram(sProd_Code, info.measure_unit);

	// ���𣨷������   ������λ*ί�м۸�*��������ע�����շ��������룬�Խ�����˴���
	double dOrgCost = CHJGlobalFun::DoubleFormat(dUnite * iHand * dPrice);

	// ��ȡ��������Ϣ����Ա�ͽ�������
	ExchFare ef_exch_fare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_SPOT_SELL_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_SPOT_SELL_FARE_ID));
	dExchFare = ef_exch_fare.sum();

	dMatchBal = dOrgCost;
}

/*
info Ʒ����Ϣ�ṹ
sExchID�����״���ID
dPrice���۸�
iHand������
bMatch���Ƿ��Ǵ���ɽ����ɽ�ʱ������ʽ��뱨����һ��һ�£���Ҫ�����ڼ��㾫�ȵ����⣩
*/
//������� = �����ʽ�/ (ÿ�ֶ��ᱣ֤��  + ÿ��������)
//kenny:20180507  ���ݽ����������޸Ķ��ᱣ֤��ļ��㹫ʽ
/*
1020 ����Ӧ�������������ֶ�


// ��߱�֤����Ϣ	�ֶΣ�group_id,long_margin,short_margin

public HashtableMsg htm_acct_large_side_sum = new HashtableMsg();

//��������Ϣ	  �ֶΣ�prod_code,group_id
public HashtableMsg htm_prod_group_info = new HashtableMsg();


1��������ʱ�����жϺ�Լ �Ƿ��� htm_prod_group_info �У�������ڣ�����ԭ�߼����㡣
����ڣ����ȸ��ݺ�Լȡhtm_prod_group_info��Ӧ��group_id������group_idȡ htm_acct_large_side_sum �Ķ�Ӧ��Ķ�ֺͿղֱ�֤��
2:�ȸ��ݶ�ֺͿղ��ıߴ����Ǳ�Ϊ��ߡ����������ȣ�����ԭ�߼����㡣
3 :
	�������������Ϊ��ߣ����������Ϊ������
	�������������ΪС�ߣ���С�߽�� + ������� <= ��߽����������Ϊ0��
	���򣬴�������Ϊ С�߽�� + ������� �C ��߽�
*/
double CTraderCpMgr::CalculateTradeFee(const ProdCodeInfo &info, const QString &sExchID, double dPrice, int iHand, bool bMatch /*= false*/, const QString &localOrderNo /*= ""*/) //, bool bTry /*=false*/
{
	// ��Լ����
	const QString &sProd_Code = info.prod_code;

	// ��ȡÿ�ֵļ�����λ ���ˣ�
	double dUnite = CHJCommon::HandToGram(sProd_Code, info.measure_unit);

	// ��������Ҫ���ܽ��
	double fTotalMoney = 0.00;

	// ���𣨷������   ������λ*ί�м۸�*��������ע�����շ��������룬�Խ�����˴���
	double dOrgCost = CHJGlobalFun::DoubleFormat(dUnite * iHand * dPrice);

	

	FareInfo stFareInfo;
	if (info.market_id == CONSTANT_B_MARKET_ID_SPOT) // �ֻ��г�
	{
		// ��ȡ��������Ϣ����Ա�ͽ�������
		ExchFare ef_exch_fare;

		// �ֻ�����
		if (sExchID == CONSTANT_EXCH_CODE_SPOT_BUY)
		{
			ef_exch_fare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_SPOT_BUY_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_SPOT_BUY_FARE_ID));

			// ��̱�����
			ExchFare ef_diff_margin;

			if (sProd_Code == CONSTANT_PT9995)  // ���� Pt99.95 ����Ҫ����̱�����
			{
				// ������̱�����
				ef_diff_margin = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_OVER_SPARE_BAIL_ID), GetMFareValue(sProd_Code, CONSTANT_OVER_SPARE_BAIL_ID));
			}

			if (bMatch)
				fTotalMoney = dOrgCost + ef_exch_fare.sum() + ef_diff_margin.sum();
			else
				fTotalMoney = dOrgCost + ef_exch_fare.sumSingle() + ef_diff_margin.sumSingle();

			// ����Ǳ�����Ϣ���¼�����Ķ�����Ϣ
			if (!localOrderNo.isEmpty())
			{
				OrderFrozeInfo stFrozeInfo;
				stFrozeInfo.Init(dOrgCost, ef_diff_margin.sumSingle(), ef_exch_fare.sumSingle(), iHand);

				m_QMapOrderFroze[localOrderNo] = stFrozeInfo;
			}
		}
		else // �ֻ�����
		{
			// ��ȡ��������Ϣ����Ա�ͽ�������
			ef_exch_fare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_SPOT_SELL_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_SPOT_SELL_FARE_ID));

			if (bMatch)
				fTotalMoney = dOrgCost - ef_exch_fare.sum();
			else
				fTotalMoney = dOrgCost - ef_exch_fare.sumSingle();
		}
	}
	else if (info.market_id == CONSTANT_B_MARKET_ID_DEFER) // ����
	{
		//kenny  20180507   ÿ�ֶ��ᱣ֤��  ��ǰ�������ı仯�߼�
		if (sExchID == CONSTANT_EXCH_CODE_DEFER_OPEN_LONG || sExchID == CONSTANT_EXCH_CODE_DEFER_OPEN_SHORT) // ���ڿ���
		{
			// ��ȡ��������Ϣ����Ա�ͽ�������
			ExchFare ef_exch_fare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, 
																		GetBFareValue(sProd_Code, CONSTANT_OPEN_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_OPEN_FARE_ID));

			if (bMatch)
			{
				// ����ɽ��Ļ�ֻ��۳�������
				fTotalMoney = ef_exch_fare.sumSingle();
			}
			else
			{
				// ��֤����㣨��Ա�ͽ�������
				QString sFareCode;

				sFareCode = CONSTANT_EXCH_BAIL_FARE_ID;

				ExchFare ef_margin = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand,	
														GetBFareValue(sProd_Code, sFareCode), GetMFareValue(sProd_Code, sFareCode));
				//1.�жϴ���Ƿ�ͬ����
				//kenny  �����ʽ�  
				double frozen = g_CusInfo.CalculateFrozenCapital(sProd_Code, sExchID, dOrgCost);
				
				// ����������+���ֱ�֤��
				if(frozen <= -1)
					fTotalMoney = ef_exch_fare.sumSingle() + ef_margin.sumSingle();
				else
					fTotalMoney = ef_exch_fare.sumSingle() + frozen;

				// ����Ǳ�����Ϣ���¼�����Ķ�����Ϣ
				if (!localOrderNo.isEmpty())
				{
					OrderFrozeInfo stFrozeInfo;
					stFrozeInfo.Init(ef_margin.sumSingle(), 0.00, ef_exch_fare.sumSingle(), iHand);

					m_QMapOrderFroze[localOrderNo] = stFrozeInfo;
				}
			}
		}
		else if (sExchID == CONSTANT_EXCH_CODE_DEFER_COV_LONG || sExchID == CONSTANT_EXCH_CODE_DEFER_COV_SHORT) // ����ƽ��
		{
			// ��ȡ��������Ϣ����Ա�ͽ�������
			ExchFare ef_exch_fare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_COV_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_COV_FARE_ID));

			if (bMatch)
			{
				// ����ɽ��Ļ�ֻ��۳�������
				fTotalMoney = ef_exch_fare.sumSingle();
			}
			else
			{
				// ��֤����㣨��Ա�ͽ�������
				ExchFare ef_margin = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID));

				// ����������-���ֱ�֤��
				fTotalMoney = ef_margin.sumSingle() - ef_exch_fare.sumSingle();
			}
		}
		else if (sExchID == CONSTANT_EXCH_CODE_DELIVERY_LONG) // �ջ�
		{
			// ���֤�𣨻�Ա�ͽ�������
			ExchFare ef_DDA_margin = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_FTD_T_DELI_MARGIN), GetMFareValue(sProd_Code, CONSTANT_FTD_T_DELI_MARGIN));

			ExchFare efPosiMoney;
			double d_cov_surplus;

			// ��ȡƽ���ͷŵı�֤��
			HandleDeferCovReleaseFee(sProd_Code, dPrice, iHand, info.measure_unit, true, efPosiMoney, d_cov_surplus);

			//kenny 20180507
			//4045  ��Ҫ�ĳɶ���100%���֤��
			//fTotalMoney = ef_DDA_margin.sumSingle() - efPosiMoney.sumSingle();
			fTotalMoney = ef_DDA_margin.sumSingle();

			// ����Ǳ�����Ϣ���¼�����Ķ�����Ϣ
			if (!localOrderNo.isEmpty())
			{
				OrderFrozeInfo stFrozeInfo;
				stFrozeInfo.Init(fTotalMoney, 0.00, 0.00, iHand);

				m_QMapOrderFroze[localOrderNo] = stFrozeInfo;
			}
		}
		//kenny  20180507  
		else if (sExchID == CONSTANT_EXCH_CODE_MIDD_DELIVERY_LONG || sExchID == CONSTANT_EXCH_CODE_MIDD_DELIVERY_SHORT) // ������  || sExchID == CONSTANT_EXCH_CODE_MIDD_DELIVERY_SHORT
		{
			ExchFare ef_entr_margin = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID));

			if (sExchID == CONSTANT_EXCH_CODE_MIDD_DELIVERY_LONG) // �ս�
			{
				// ���֤�𣨻�Ա�ͽ�������
				ExchFare ef_deli_prepare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_FTD_T_DELI_MARGIN), GetMFareValue(sProd_Code, CONSTANT_FTD_T_DELI_MARGIN));


				double frozen = g_CusInfo.CalculateFrozenCapital(sProd_Code, sExchID, dOrgCost);

				// ����������+���ֱ�֤��
				if (frozen <= -1)
					fTotalMoney = ef_deli_prepare.sumSingle() + ef_entr_margin.sumSingle();
				else
					fTotalMoney = ef_deli_prepare.sumSingle() + frozen;

				//fTotalMoney = ef_entr_margin.sumSingle() + ef_deli_prepare.sumSingle();
			}
			else // ����
			{
				fTotalMoney = ef_entr_margin.sumSingle();
			}

			// ����Ǳ�����Ϣ���¼�����Ķ�����Ϣ
			if (!localOrderNo.isEmpty())
			{
				OrderFrozeInfo stFrozeInfo;
				stFrozeInfo.Init(fTotalMoney, 0.00, 0.00, iHand);

				m_QMapOrderFroze[localOrderNo] = stFrozeInfo;
			}
		}
	}
	else // Զ��
	{
		// ��ȡ��������Ϣ���������ͻ�Ա��
		ExchFare ef_exch_fare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_OPEN_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_OPEN_FARE_ID));

		if (bMatch) // �����Զ�ڳɽ�
		{
			// ����ɽ��Ļ�ֻ��۳�������
			fTotalMoney = ef_exch_fare.sum();
		}
		else // ����Ǳ���
		{
			// ��֤����㣨��Ա�ͽ�������
			ExchFare ef_margin = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID));

			// ����������+���ֱ�֤��
			fTotalMoney = ef_exch_fare.sumSingle() + ef_margin.sumSingle();

			// ����Ǳ�����Ϣ���¼�����Ķ�����Ϣ
			if (!localOrderNo.isEmpty())
			{
				OrderFrozeInfo stFrozeInfo;
				stFrozeInfo.Init(ef_margin.sumSingle(), 0.00, ef_exch_fare.sumSingle(), iHand);

				m_QMapOrderFroze[localOrderNo] = stFrozeInfo;
			}
		}
	}

	//fTotalMoney = CHJGlobalFun::DoubleFormat(fTotalMoney);

	return fTotalMoney;
}

bool CTraderCpMgr::GetProdCodeInfo(const QString &sProdCode, ProdCodeInfo &info)
{
	for (size_t i = 0; i < m_vProdCode.size(); i++)
	{
		if (m_vProdCode.at(i).prod_code == sProdCode)
		{
			info = m_vProdCode.at(i);

			return true;
		}
	}

	return false;
}

/*
sProdCode  ��Ҫ����Ľ���Ʒ��
sExchID ����Id
dPrice �����۸�
iHand ��������
bFreeze trueΪ���ᣬfalseΪ�ⶳ
localOrderNo
*/
bool CTraderCpMgr::HandleTradeFee(const QString &sProdCode, const QString &sExchID, double dPrice, int iHand, bool bFreeze, const QString &localOrderNo /*= ""*/)
{
	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info)) // �����ȡ�ú�Լ����Ϣ�ɹ�
	{
#ifdef _Write_Fund_Log
		QString csLog;
		csLog.Format("����HandleTradeFee�����ر����ţ�%s���Ƿ񶳽᣺%d������ǰ�����ʽ�%.2f",
			localOrderNo,
			bFreeze,
			m_stFundInfo.dUseFulBal
		);
		g_Global.WriteLog(csLog);
#endif
		// ���㽻�ײ��ַ���
		double dTradeFee = CalculateTradeFee(info, sExchID, dPrice, iHand, false, localOrderNo);

		// ����ɽ�ʱδ����Ľⶳ���ã���Ϊ��ʱ�����յ��ɽ���ˮ���յ�������ˮ��
		double dReleaseMoney = GetMatchUnReleaseMoney(localOrderNo);
		dTradeFee -= dReleaseMoney;

		// ��������ʽ�
		bFreeze ? m_stFundInfo.dUseFulBal -= dTradeFee : m_stFundInfo.dUseFulBal += dTradeFee;

		// �����׶����ʽ�
		bFreeze ? m_stFundInfo.dExchFrozeBal += dTradeFee : m_stFundInfo.dExchFrozeBal -= dTradeFee;

#ifdef _Write_Fund_Log
		QString csqDebug;
		csqDebug.Format("����HandleTradeFee�����������ʽ�%.2f��ʵ�ʽ��׷��ã�%.2f���ⶳ��%.2f",
			m_stFundInfo.dUseFulBal,
			dTradeFee,
			dReleaseMoney
		);
		g_Global.WriteLog(csqDebug);
#endif

		return true;
	}

	return false;
}

bool CTraderCpMgr::HandleCancelTradeFee(const QString &sProdCode, int iHand, const QString &localOrderNo)
{
	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info)) // �����ȡ�ú�Լ����Ϣ�ɹ�
	{
#ifdef _Write_Fund_Log
		QString cslog;
		cslog.Format("����HandleCancelTradeFee���������ᣬ���ر����ţ�%s��Ʒ�֣�%s������ǰ�����ʽ�%.2f",
			localOrderNo,
			sProdCode,
			m_stFundInfo.dUseFulBal);
		g_Global.WriteLog(cslog);
#endif	
		// ---------------------����ⶳ����
		double dFrozenTradeFee = GetRealeaseMoney(localOrderNo, iHand);

		// ��������ʽ�
		m_stFundInfo.dUseFulBal += dFrozenTradeFee;

		// �����׶����ʽ�
		m_stFundInfo.dExchFrozeBal -= dFrozenTradeFee;

#ifdef _Write_Fund_Log
		QString csqDebug;
		csqDebug.Format("����HandleCancelTradeFee���������ᣬ���ر����ţ�%s��Ʒ�֣�%s���ⶳ������ʽ�%.2f���ⶳ���ã�%.2f",
			localOrderNo,
			sProdCode,
			m_stFundInfo.dUseFulBal,
			dFrozenTradeFee);
		g_Global.WriteLog(csqDebug);
#endif	

		return true;
	}

	return false;
}
// ����һ���ֻ��ɽ������ʽ�ı仯������ɹ��򷵻�true��ʧ���򷵻�false
// sProdCode����Լ���룩  sExchID������ID�� dPrice���ɽ��۸� iHand���ɽ������� bSell���Ƿ�������
bool CTraderCpMgr::HandleSpotMatchFee(const QString &sProdCode, const QString &sExchID, double dPrice, int iHand, bool bSell, const QString &localOrderNo /*= ""*/)
{
	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info)) // �����ȡ�ú�Լ����Ϣ�ɹ�
	{
		double dSellMatchBal, dSellExchFare;

		// ���㽻�׳ɽ�����������ȫ����������Ϊ��Ҫ��ȡ��ȫ����������Ϊ��Ҫ���ӵ�ȫ����
		double dTradeFee;
		if (!bSell)
		{
			dTradeFee = CalculateTradeFee(info, sExchID, dPrice, iHand, true);
		}
		else
		{
			CalSpotSellMatchFee(info, dPrice, iHand, dSellMatchBal, dSellExchFare);

			dTradeFee = dSellMatchBal - dSellExchFare;
		}

		// ---------------------���㱨��ʱ��Ķ������
		double dFrozenTradeFee = 0.00; //
		if (!bSell) // 
		{
			dFrozenTradeFee = HandleMatchReleaseMoney(localOrderNo, iHand);
		}

		// ���������ӽ���������ٽ��
		bSell ? m_stFundInfo.dAllBalance += dTradeFee : m_stFundInfo.dAllBalance -= dTradeFee;

		// �����ʽ��������ɽ������ӽ��׽�ͬʱ����10%�ı���
		// ��������룬��ⶳ�����ӣ����׶���Ĳ��֣�Ȼ���ȥȫ��Ľ��׷���
		if (bSell) // ����
		{
			m_stFundInfo.dUseFulBal += dFrozenTradeFee + CHJGlobalFun::DoubleFormat(dSellMatchBal*0.9) - dSellExchFare;
		}
		else // ����
		{
			m_stFundInfo.dUseFulBal += dFrozenTradeFee - dTradeFee;
		}

		// �����׶��ᣬ����������򶳽�10%�ı�����������룬��ⶳ����ʱ�Ķ�����
		if (bSell)
		{
			m_stFundInfo.dExchFrozeBal += CHJGlobalFun::DoubleFormat(dSellMatchBal*0.1);
		}
		else
		{
			m_stFundInfo.dExchFrozeBal -= dFrozenTradeFee;
		}

		return true;
	}

	return false;
}

// ����һ��Զ�ڳɽ�����ʽ�仯
bool CTraderCpMgr::HandleForwardMatchFee(const QString &sProdCode, const QString &sExchID, double dPrice, int iHand, double &dPosiMoney, const QString &localOrderNo)
{
	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info)) // �����ȡ�ú�Լ����Ϣ�ɹ�
	{
		// ���㽻�ײ����ķ���
		double dExchFare;
		CalForwardMatchFee(info, dPrice, iHand, dPosiMoney, dExchFare);

		// ���㱨��ʱ��Ķ������
		double dFrozenTradeFee = HandleMatchReleaseMoney(localOrderNo, iHand);

		// �������ʽ��ܶ���������ѵĲ���
		m_stFundInfo.dAllBalance -= dExchFare;

		// ��������ʽ�
		m_stFundInfo.dUseFulBal -= dExchFare + dPosiMoney - dFrozenTradeFee;

		// �������ʽ�
		m_stFundInfo.dExchFrozeBal -= dFrozenTradeFee;

		return true;
	}

	return false;
}

// ����һ�����ڳɽ�����ʽ�仯��bSell���Ƿ񿪲֣� 
bool CTraderCpMgr::HandleDeferMatchFee(const QString &sProdCode, const QString &sExchID, double dPrice, int iHand, bool bOpen, double &dPosiMoney, const QString &localOrderNo /*= ""*/)
{
	dPosiMoney = 0.00;
	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info)) // �����ȡ�ú�Լ����Ϣ�ɹ�
	{
#ifdef _Write_Fund_Log
		QString csLog;
		csLog.Format("����HandleDeferMatchFee�������ڳɽ������ر�����Ϊ��%s��Ʒ�֣�%s������ǰ���ý��Ϊ��%.2f���ܶ�Ϊ��%.2f",
			localOrderNo,
			sProdCode,
			m_stFundInfo.dUseFulBal,
			m_stFundInfo.dAllBalance);
		g_Global.WriteLog(csLog);
#endif

		// ���㽻�ײ����ķ���
		double dExchFare; // ���������ѣ��ֱֲ�֤��
		CalDeferMatchFee(info, dPrice, iHand, dPosiMoney, dExchFare, bOpen);

		// ���㱨��ʱ��Ķ�����ã�ƽ�ֵ�ʱ���ǽⶳ�ķ��ã�
		double dFrozenTradeFee = HandleMatchReleaseMoney(localOrderNo, iHand);

		// �������ʽ��ܶ���������ѵĲ���
		m_stFundInfo.dAllBalance -= dExchFare;

		// ��������ʽ�
		m_stFundInfo.dUseFulBal += dFrozenTradeFee - dExchFare - dPosiMoney;

		// �������ʽ�
		m_stFundInfo.dExchFrozeBal -= dFrozenTradeFee;

#ifdef _Write_Fund_Log
		QString csqDebug;
		csqDebug.Format("����HandleDeferMatchFee�������ڳɽ������ر�����Ϊ��%s��Ʒ�֣�%s���������ý��Ϊ��%.2f���ܶ�Ϊ��%.2f�����ᣨ�ⶳ�����Ϊ��%.2f�����׷��ã�%.2f���ֱֲ�֤��%.2f���ܷ��ã�%.2f",
			localOrderNo,
			sProdCode,
			m_stFundInfo.dUseFulBal,
			m_stFundInfo.dAllBalance,
			dFrozenTradeFee,
			dExchFare,
			dPosiMoney,
			dFrozenTradeFee - dExchFare - dPosiMoney);
		g_Global.WriteLog(csqDebug);
#endif

		return true;
	}

	return false;
}

// ��������ƽ�ֳɽ����ʽ���Ϣ bLong
bool CTraderCpMgr::HandleDeferCovMatchFee(const QString &sProdCode, double dPrice, int iHand, bool bLong)
{
	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info)) // �����ȡ�ú�Լ����Ϣ�ɹ�
	{
#ifdef _Write_Fund_Log
		QString csLog;
		csLog.Format("����HandleDeferCovMatchFee��������ƽ�ֳɽ���Ʒ�֣�%s������ǰ���ý��Ϊ��%.2f���ܽ��Ϊ��%.2f",
			sProdCode,
			m_stFundInfo.dUseFulBal,
			m_stFundInfo.dAllBalance);
		g_Global.WriteLog(csLog);
#endif

		// ���㽻�ײ����ķ���
		ExchFare efExchFare, efPosiMoney;
		double d_cov_surplus;

		CalDeferCovMatchFee(info, dPrice, iHand, bLong, efPosiMoney, efExchFare, d_cov_surplus);

		m_stFundInfo.dAllBalance += d_cov_surplus - efExchFare.sum();

		m_stFundInfo.dUseFulBal += efPosiMoney.sum() - efExchFare.sum() + d_cov_surplus;

#ifdef _Write_Fund_Log
		QString csqDebug;
		csqDebug.Format("����HandleDeferCovMatchFee��������ƽ�ֳɽ���Ʒ�֣�%s���������ý��Ϊ��%.2f���ܽ��Ϊ��%.2f��efPosiMoneyΪ��%.2f��efExchFareΪ��%.2f��d_cov_surplusΪ��%.2f",
			sProdCode,
			m_stFundInfo.dUseFulBal,
			m_stFundInfo.dAllBalance,
			efPosiMoney.sum(),
			efExchFare.sum(),
			d_cov_surplus);
		g_Global.WriteLog(csqDebug);
#endif

		return true;
	}

	return false;
}


bool CTraderCpMgr::HandleDDAMatchFee(const QString &sProdCode, int iHand, bool bBuy, const QString &localOrderNo /*= ""*/)
{
	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info)) // �����ȡ�ú�Լ����Ϣ�ɹ�
	{
		ExchFare ef_m_deli_prepare;
		ExchFare ef_m_release_margin;
		GetDDATradeFee(info, bBuy, iHand, ef_m_deli_prepare, ef_m_release_margin);

		if (bBuy) // ������ս�
		{
			// ���㱨��ʱ��Ķ�����ã�ƽ�ֵ�ʱ���ǽⶳ�ķ��ã�
			double dFrozenTradeFee = HandleMatchReleaseMoney(localOrderNo, iHand);

			// �ͷſ����ʽ�Ķ���
			m_stFundInfo.dUseFulBal += dFrozenTradeFee - (ef_m_deli_prepare.sum() - ef_m_release_margin.sum());

			// �ͷŽ��׶���
			m_stFundInfo.dExchFrozeBal -= dFrozenTradeFee;
		}
		else
		{
			m_stFundInfo.dUseFulBal += ef_m_release_margin.sum();
		}
	}

	return false;
}

// ���������ֳɽ����ʽ���Ϣ������ɽ������ʽ�Ĵ���
bool CTraderCpMgr::HandleMAMatchFee(const QString &sProdCode, int iHand, bool bBuy, const QString &localOrderNo /*= ""*/)
{
	//return true;

	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info)) // �����ȡ�ú�Լ����Ϣ�ɹ�
	{
		// ������ɽ��Ŀ۳������������ͷŽ����ʱ�򶳽���ʽ�
		// 		if(bBuy)
		// 		{
		// 			// ��ȡ�ɽ��Ŀ۳����
		// 			ExchFare ef_m_deli_prepare;
		// 			ExchFare ef_m_margin;
		// 			GetMAMatchFee(info, bBuy, iHand, ef_m_deli_prepare, ef_m_margin);
		// 			
		// 			// ��ȡ�ɽ���Ҫ�ͷŵĶ����ʽ�
		// 			double dFrozenTradeFee  = HandleMatchReleaseMoney(localOrderNo, iHand);
		// 
		// 			m_stFundInfo.dUseFulBal += dFrozenTradeFee - (ef_m_deli_prepare.sum() + ef_m_margin.sum());
		// 
		// 			// �ͷŽ��׶���
		// 			m_stFundInfo.dExchFrozeBal -= dFrozenTradeFee;
		// 		}

		// ��ȡ�ɽ��Ŀ۳����
		ExchFare ef_m_deli_prepare;
		ExchFare ef_m_margin;
		GetMAMatchFee(info, bBuy, iHand, ef_m_deli_prepare, ef_m_margin);

		// ��ȡ�ɽ���Ҫ�ͷŵĶ����ʽ�
		double dFrozenTradeFee = HandleMatchReleaseMoney(localOrderNo, iHand);

		//if(bBuy)
		// 
		m_stFundInfo.dUseFulBal += dFrozenTradeFee - (ef_m_deli_prepare.sum() + ef_m_margin.sum());

		// �ͷŽ��׶���
		m_stFundInfo.dExchFrozeBal -= dFrozenTradeFee;

	}

	return false;
}

void CTraderCpMgr::CalDeferCovMatchFee(const ProdCodeInfo &info, double dPrice, int iHand, bool bLong, ExchFare &efPosiMoney, ExchFare &efExchFare, double &d_cov_surplus)
{
	// ��Լ����
	const QString &sProd_Code = info.prod_code;

	// ��ȡÿ�ֵļ�����λ ���ˣ�
	double dUnite = CHJCommon::HandToGram(sProd_Code, info.measure_unit);

	// ���𣨷������
	double dOrgCost = dUnite * iHand * dPrice;

	// ��ȡ��������Ϣ���������ͻ�Ա��
	efExchFare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_COV_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_COV_FARE_ID), true);

	// ��ȡƽ���ͷŵı�֤��
	HandleDeferCovReleaseFee(sProd_Code, dPrice, iHand, info.measure_unit, bLong, efPosiMoney, d_cov_surplus);
}

// ����ƽ�ֵ�ʱ���ͷŵı�֤��ͳֲ�ӯ��
void CTraderCpMgr::HandleDeferCovReleaseFee(const QString &sProdCode, double dPrice, int iHand, double dMeasure_unit, bool bLong, ExchFare &ef_m_release_margin, double &d_cov_surplus)
{
	d_cov_surplus = 0.00;

	// ���ݳֲַ����ȡ��Ӧ�ĳֲ���Ϣ
	QMap<QString, DeferPosi>::iterator it = m_QMapDeferPosi.find(sProdCode);
	if (it == m_QMapDeferPosi.end())
	{
		return;
	}
	DeferPosiInfo &info = bLong ? it->infoLong : it->infoShort;
	LISTDeferMatch &listMatch = info.listMatch;

	int iCovYes;
	int iCovToday;
	if (info.iYesAmt > iHand || info.iYesAmt == iHand) // ������������ƽ��
	{
		iCovYes = iHand;
		iCovToday = 0;
	}
	else
	{
		iCovYes = info.iYesAmt;
		iCovToday = iHand - info.iYesAmt;
	}

	double dDifPrice;
	dMeasure_unit = CHJCommon::HandToGram(sProdCode, dMeasure_unit);

	// ��ƽ������Ĳ�λ
	if (iCovYes > 0)
	{
		// �ͷŵĳֱֲ�֤��
		ef_m_release_margin.dMemberFare += info.dYesPosiMoney * iCovYes / info.iYesOrgAmt;

		// ƽ���(bLong=true)   = (ƽ�ּ�-���ּۣ�����ǰƽ��������ÿ������
		dDifPrice = bLong ? (dPrice - info.fYesAvgPosPrice) : (info.fYesAvgPosPrice - dPrice);
		d_cov_surplus += dDifPrice*dMeasure_unit*iCovYes; // ����ӯ��
	}

	if (iCovToday > 0)
	{
		const LISTDeferMatch &listMatch = info.listMatch;
		for (LISTDeferMatch::const_iterator it = listMatch.begin(); it != listMatch.end(); )
		{
			dDifPrice = bLong ? (dPrice - it->dPrice) : (it->dPrice - dPrice);

			if (it->iHand > iCovToday || it->iHand == iCovToday) // �����ǰ��ˮ��������С��ʣ������
			{
				ef_m_release_margin.dMemberFare += it->dPosiMoney * iCovToday / it->iTotalHand;
				d_cov_surplus += dDifPrice*dMeasure_unit*iCovToday; // ����ӯ��
				break;
			}
			else // �����ǰ��ˮ������С��ʣ�����������¼δ��ƽ��������
			{
				if (it->iHand > 0)
				{
					iCovToday -= it->iHand;
					ef_m_release_margin.dMemberFare += it->dPosiMoney*it->iHand / it->iTotalHand;
					d_cov_surplus += dDifPrice*dMeasure_unit*it->iHand; // ����ӯ��
				}

				it++;
			}
		}
	}
}

void CTraderCpMgr::GetDDATradeFee(const ProdCodeInfo &info, bool bLong, int iHand, ExchFare &ef_m_deli_prepare, ExchFare &ef_m_release_margin)
{
	const QString &sProdCode = info.prod_code;

	double dPrice = GetDeferDeliveryPrice(sProdCode);

	// ��ȡÿ�ֵļ�����λ ���ˣ�
	double dUnite = CHJCommon::HandToGram(sProdCode, info.measure_unit);

	if (bLong) // ֻ���ս��Ҫ���㽻��׼�����ս���
	{
		// ���𣨷������
		double dOrgCost = dUnite * iHand * dPrice;

		// ���֤�𣨻�Ա�ͽ�������
		ef_m_deli_prepare = CHJCommon::GetExchFareValueByExchBal(sProdCode, dUnite, dOrgCost, iHand, GetBFareValue(sProdCode, CONSTANT_FTD_T_DELI_MARGIN), GetMFareValue(sProdCode, CONSTANT_FTD_T_DELI_MARGIN));
	}

	double d_cov_surplus;
	HandleDeferCovReleaseFee(sProdCode, dPrice, iHand, dUnite, bLong, ef_m_release_margin, d_cov_surplus);

	// ���ֵ�ȫ�����׽��
	//double dOpenFrozFare = GetOpenFareOrg(sProdCode, true, dUnite, iHand);

	// ���ֱ�֤����㣨��Ա�ͽ�������
	//ef_m_release_margin = CHJCommon::GetExchFareValueByExchBal(sProdCode, dUnite, dOpenFrozFare, iHand,  GetBFareValue(sProdCode, CONSTANT_EXCH_BAIL_FARE_ID), GetMFareValue(sProdCode, CONSTANT_EXCH_BAIL_FARE_ID));
}

void CTraderCpMgr::GetMAMatchFee(const ProdCodeInfo &info, bool bLong, int iHand, ExchFare &ef_m_deli_prepare, ExchFare &ef_m_release_margin)
{
	const QString &sProdCode = info.prod_code;

	double dPrice = GetMAOrderPrice(sProdCode);

	// ��ȡÿ�ֵļ�����λ ���ˣ�
	double dUnite = CHJCommon::HandToGram(sProdCode, info.measure_unit);

	double dOrgCost = dUnite * iHand * dPrice;

	ef_m_release_margin = CHJCommon::GetExchFareValueByExchBal(sProdCode, dUnite, dOrgCost, iHand, GetBFareValue(sProdCode, CONSTANT_OPEN_FARE_ID), GetMFareValue(sProdCode, CONSTANT_OPEN_FARE_ID));

	if (bLong) // �ս�
	{
		// ���֤�𣨻�Ա�ͽ�������
		ef_m_deli_prepare = CHJCommon::GetExchFareValueByExchBal(sProdCode, dUnite, dOrgCost, iHand, GetBFareValue(sProdCode, CONSTANT_FTD_T_DELI_MARGIN), GetMFareValue(sProdCode, CONSTANT_FTD_T_DELI_MARGIN));
	}
}

// �ò��ִ���
void CTraderCpMgr::CalForwardMatchFee(const ProdCodeInfo &info, double dPrice, int iHand, double &dPosiMoney, double &dExchFare)
{
	// ��Լ����
	const QString &sProd_Code = info.prod_code;

	// ��ȡÿ�ֵļ�����λ ���ˣ�
	double dUnite = CHJCommon::HandToGram(sProd_Code, info.measure_unit);

	// ���𣨷������   ������λ*ί�м۸�*��������ע�����շ��������룬�Խ�����˴���
	//double dOrgCost = CHJGlobalFun::DoubleFormat(dUnite * iHand * dPrice );
	double dOrgCost = dUnite * iHand * dPrice;

	// ��ȡ��������Ϣ���������ͻ�Ա��
	ExchFare ef_exch_fare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_OPEN_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_OPEN_FARE_ID), true);

	// ��֤����㣨��Ա�ͽ�������
	ExchFare ef_margin = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID), true);

	// �ɽ��ֲ��ܶ�
	dPosiMoney = ef_margin.sum();
	// �ɽ��������ܶ�
	dExchFare = ef_exch_fare.sum();
}

// �������ڳɽ����漰���ʽ���㣺��Ҫ�۳��ĳɽ��������Լ���֤�𣨿�����Ϊ���ᣬƽ����Ϊ�ⶳ��
void CTraderCpMgr::CalDeferMatchFee(const ProdCodeInfo &info, double dPrice, int iHand, double &dPosiMoney, double &dExchFare, bool bOpen)
{
	// ��Լ����
	const QString &sProd_Code = info.prod_code;

	// ��ȡÿ�ֵļ�����λ ���ˣ�
	double dUnite = CHJCommon::HandToGram(sProd_Code, info.measure_unit);

	// ���𣨷������
	double dOrgCost = dUnite * iHand * dPrice;

	// ��ȡ��������Ϣ���������ͻ�Ա��
	QString sExchCode = (bOpen) ? CONSTANT_OPEN_FARE_ID : CONSTANT_COV_FARE_ID;
	ExchFare ef_exch_fare = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, sExchCode), GetMFareValue(sProd_Code, sExchCode), true);

	// ��֤����㣨��Ա�ͽ�������
	ExchFare ef_margin = CHJCommon::GetExchFareValueByExchBal(sProd_Code, dUnite, dOrgCost, iHand, GetBFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID), GetMFareValue(sProd_Code, CONSTANT_EXCH_BAIL_FARE_ID), true);

	// �ɽ��ֲ��ܶ�
	dPosiMoney = ef_margin.sum();
	// �ɽ��������ܶ�
	dExchFare = ef_exch_fare.sum();
}

// �����ֻ��ɽ��Ŀ��䶯��������ֻ�����ɽ�����bAddΪtrue�����ܿ��Ϳ��ÿ�����ӣ�������ֻ������ɽ���bAddΪfalse���򶳽���٣��ܿ�����
bool CTraderCpMgr::HandleMatchStore(const QString &sProdCode, int iHand, bool bAdd)
{
	auto itStore = m_QMapStoreInfo.find(sProdCode);
	if (itStore == m_QMapStoreInfo.end()) // �����������
	{
		StoreInfo body;
		//auto Insert_Pair = m_QMapStoreInfo.insert(sProdCode, body);
		//itStore = Insert_Pair.key();
		itStore = m_QMapStoreInfo.insert(sProdCode, body);

	}

	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info))
	{
		StoreInfo &stStore = itStore.value();

#ifdef _WRITE_SPOT_LOG
		QString csLog1;
		csLog1.Format("�����ֻ��ɽ���棬Ʒ��%s������ǰ�ֱ�Ϊ%d,%d", stStore.iUseFulAmt, stStore.iExchFreeze);
		g_Global.WriteLog(csLog1);
#endif

		// ���Ʒ�ֻ�����λ����һ�ֵĿ�����
		int iTotal = iHand*(int)(info.measure_unit + 0.5);

		// �����ܿ��
		bAdd ? stStore.iAllAmt += iTotal : stStore.iAllAmt -= iTotal;

		// added by Jerry Lee, 2013-3-25, ������ÿ��С��������
		if (stStore.iAllAmt < 0)
		{
			stStore.iAllAmt = 0;
		}

		// ������ÿ�棬��������룬�����ӿ�棬��������������ڱ�����ʱ���Ѿ������ˣ��������ﲻ������
		if (bAdd)
		{
			stStore.iUseFulAmt += iTotal;
		}

		// ������������򶳽���٣���������룬��������
		if (!bAdd)
		{
			stStore.iExchFreeze -= iTotal;
		}

#ifdef _WRITE_SPOT_LOG
		QString csqDebug;
		csqDebug.Format("�����ֻ��ɽ���棬Ʒ��%s������ǰ�ֱ�Ϊ%d,%d", stStore.iUseFulAmt, stStore.iExchFreeze);
		g_Global.WriteLog(csqDebug);
#endif

		return true;
	}


	return false;
}

/*
������ʱ�Ŀ�涳���ⶳ
bFreeze��true��Ϊ���ᣬfalse��Ϊ�ⶳ
sDDAProdCode����ֵΪ��ʱ��ʾ���������ͨ���ֻ�����
����ֵ��Ϊ�յ�ʱ���ʾ��ʱ����������ڽ��ջ��������֣����������Ϊ����ʱ�ɲ��ô��潻��Ʒ�֣�
��ʱ�򶳽��Ʒ�ֲ���sDDAProdCode��
*/
bool CTraderCpMgr::HandleTradeStore(const QString &sProdCode, int iHand, bool bFreeze, const QString &sDDAProdCode)
{
	// ���ݺ�Լ�����ҵ��ñʿ��
	QMap<QString, StoreInfo>::iterator itStore = m_QMapStoreInfo.find(sProdCode);
	if (itStore != m_QMapStoreInfo.end())
	{
#ifdef _WRITE_SPOT_LOG
		QString csLog1;
		csLog1.Format("��������棬Ʒ��%s������ǰ�ֱ�Ϊ%d,%d", itStore.value.iUseFulAmt, itStore.value.iExchFreeze);
		g_Global.WriteLog(csLog1);
#endif

		// ���Ʒ����Ϣ
		ProdCodeInfo info;

		// ������Ҫ��Ϊ�˻�ȡƷ�ֵļ�����λ�����sDDAProdCode��Ϊ�գ����ȡsDDAProdCode�ļ�����λ��Ϊ�����ȡsProdCode�ļ�����λ
		bool bGetInfoSuc = false;
		if (sDDAProdCode.isEmpty())
			bGetInfoSuc = GetProdCodeInfo(sProdCode, info);
		else
			bGetInfoSuc = GetProdCodeInfo(sDDAProdCode, info);

		if (bGetInfoSuc)
		{
			// ���Ʒ�ֿ����Ϣ
			StoreInfo &stStore = itStore.value();

			// ��ȡһ�ֵĿ���������0.5�ǽ���������Ĳ���ȷ����
			int iUnit = (int)(CHJCommon::HandToGram(sProdCode, info.measure_unit) + 0.5);

			// ������ÿ�棺����Ƕ��ᣬ����ÿ����٣�����ǽⶳ������ÿ������
			bFreeze ? stStore.iUseFulAmt -= iHand*iUnit : stStore.iUseFulAmt += iHand*iUnit;

			// �����׶��᣺����Ƕ��ᣬ���׶������ӣ�����ǽⶳ�����׶������
			bFreeze ? stStore.iExchFreeze += iHand*iUnit : stStore.iExchFreeze -= iHand*iUnit;

#ifdef _WRITE_SPOT_LOG
			QString csqDebug;
			csqDebug.Format("��������棬Ʒ��%s�������ֱ�Ϊ%d,%d", itStore.value.iUseFulAmt, itStore.value.iExchFreeze);
			g_Global.WriteLog(csqDebug);
#endif

			return true;
		}
	}

	return false;
}
// ��ʼ�����潻��Ʒ����Ϣ
bool CTraderCpMgr::Ini1005()
{
	m_htmSubVariety.clear();

	//QString strDataPath = g_Global.GetSystemPath() + CONSTANT_DATA_INI_NAME;
	//char buf[500] = {0};

	//// ��ȡ���ر���Ľ������Ʒ��
	//   // mod by Jerry Lee, 2013-3-27, ���ӽ��������ļ������ӷ�������ȡ���ݵĴ���
	//::GetPrivateProfileQString("info", "VARIETY_SUBSTITUE", "", buf, sizeof(buf), strDataPath);
	//   int nParseRet = -1;
	//if(strlen(buf) > 10)
	//{
	//	// ����
	//	QString str = buf;
	//	nParseRet = m_htmSubVariety.Parse(str);
	//}
	//
	//   if (nParseRet != 0)
	//   {
	//	// ����û�еĻ��������������
	//	Rsp1005 rsp1005;

	//	// ���ͱ���
	//	int iReturn = CTranMessage::Handle1005(rsp1005);
	//	if(iReturn == 0)
	//	{
	//           // ��������
	//		::WritePrivateProfileQString("Info", "VARIETY_SUBSTITUE", rsp1005.htm_variety_info.ToQString(),    
	//               strDataPath);
	//		// ��¼���ڴ�
	//		m_htmSubVariety = rsp1005.htm_variety_info;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	return true;
}

bool CTraderCpMgr::GetCusSubVarietyName(const QString &sProdCode, QString &sSubVAriety, const QString &sSeq)
{
	// ��ȡ��һλ�Ľ���Ʒ�ֵ�ID
	QString sVarietyID = GetSubVarietyBySeqNo(sProdCode, sSeq);
	if (!sVarietyID.isEmpty())
	{
		// ����ID��ȡ����Ʒ����Ϣ
		VarietyInfo info;
		if (GetVarietyInfo(sVarietyID, info))
		{
			// �жϿͻ��Ƿ��Ʒ�ֵĿ��
			if (m_QMapStoreInfo.count(info.name) > 0)
			{
				if (m_QMapStoreInfo[info.name].iUseFulAmt > 0)
				{
					sSubVAriety = info.name;
					return true;
				}
			}
		}
	}

	return false;
}
// �������ڽ��𱨵���Ʒ�ֻ�ȡ����Ľ���Ʒ�ֵ�����
QString CTraderCpMgr::GetSubVarietyProdCode(const QString &sProdCode)
{
	// ȷ���ڴ����Ѿ�����
	if (m_htmSubVariety.size() == 0)
	{
		if (!Ini1005())
		{
			return "";
		}
	}

	QString sSubVAriety;
	if (!GetCusSubVarietyName(sProdCode, sSubVAriety, "1"))
	{
		GetCusSubVarietyName(sProdCode, sSubVAriety, "2");
	}

	return sSubVAriety;

	/*
	// ��ȡ��һλ�Ľ���Ʒ�ֵ�ID
	QString sVarietyID = GetSubVarietyBySeqNo(sProdCode, "1");
	if(!sVarietyID.isEmpty())
	{
	// ����ID��ȡ����Ʒ����Ϣ
	VarietyInfo info;
	if(GetVarietyInfo(sVarietyID, info))
	{
	// �жϿͻ��Ƿ��Ʒ�ֵĿ��
	if(m_QMapStoreInfo.count(info.name) > 0)
	{
	return info.name;
	}
	}
	}
	else
	{
	// �����һλ�Ľ���Ʒ�ִ���ûƷ�֣�����ڶ�λ
	sVarietyID = GetSubVarietyBySeqNo(sProdCode, "2");

	// ����ID��ȡ����Ʒ����Ϣ
	VarietyInfo info;
	if(GetVarietyInfo(sVarietyID, info))
	{
	// �жϿͻ��Ƿ��Ʒ�ֵĿ�棬���ڿ���Ƿ��㹻��������ʱ��������Ѿ������жϣ����Բ���Ҫ������
	if(m_QMapStoreInfo.count(info.name) > 0)
	{
	return info.name;
	}
	}
	}

	return "";
	*/
}

// ���ݽ���Ʒ��ID��ȡ����Ʒ����Ϣ��û���ҵ��򷵻�false������Ϊtrue
bool CTraderCpMgr::GetVarietyInfo(const QString &sVarietyID, VarietyInfo &info)
{
	for (size_t i = 0; i < m_vVariety.size(); i++)
	{
		if (m_vVariety.at(i).variety_id == sVarietyID)
		{
			info = m_vVariety.at(i);
			return true;
		}
	}

	return false;
}

// ���ݺ�ԼƷ�ֺͽ���˳���ҵ��������Ʒ�ֵ�ID
QString CTraderCpMgr::GetSubVarietyBySeqNo(const QString &sProdCode, const QString &sSeqNo)
{
	for (size_t i = 0; i < m_htmSubVariety.size(); i++)
	{
		if (m_htmSubVariety.GetString(i, "prod_code") == sProdCode.toStdString()
			&& m_htmSubVariety.GetString(i, "seq_no") == sSeqNo.toStdString())
		{
			return m_htmSubVariety.GetString(i, "variety_id").c_str();
		}
	}

	return "";
}
// ��ȡ���ڽ��ն��ʽ��������õļ۸�
double CTraderCpMgr::GetDeferDeliveryPrice(const QString &sProdCode)
{
	// ��ȡ��ͣ���ʺͼ۸�ʽ
	QString sPriceModePara = g_TraderCpMgr.GetParaValue("DeferDeliveryTestPriceBasePrice", "lastSettle");
	QString sUpRatePara = g_TraderCpMgr.GetParaValue("DeferDeliveryTestPriceUpRate", "0.07");

	// ��¼��󷵻صļ۸�
	double dPrice;

	// ��ȡ������Ϣ
	const QUOTATION& qt = g_TraderCpMgr.m_QMapQuotation[sProdCode.toStdString()];

	// �������õļ۸�ʽȡ�����Ӧ�ļ۸�
	unsigned int uiPrice;
	if (sPriceModePara == "average")
		uiPrice = qt.m_uiAverage;
	else if (sPriceModePara == "lastClose")
		uiPrice = qt.m_uilastClose;
	else
		uiPrice = qt.m_uiLastSettle;

	// �۸���쳣����
	if (uiPrice == 0)
		uiPrice = qt.m_uilastClose;

	// ��ȡ�������͵ļ۸񣬲��շ����������ʽ��
	dPrice = CHJGlobalFun::DoubleFormat(uiPrice / g_Global.m_dQTFactor);

	// ������ͣ����
	dPrice *= (1 + sUpRatePara.toFloat());

	// ���շ����������ݸ�ʽ��
	return CHJGlobalFun::DoubleFormat(dPrice);
}

// ����ϵͳ����ID��ȡϵͳ����ֵ����ȡʧ�ܵĻ�����Ĭ�ϵģ�sDefaultValue��
QString CTraderCpMgr::GetParaValue(const QString &sParaID, const QString &sDefaultValue)
{
	QMap<QString, QString>::const_iterator it = m_QMapSystemPara.find(sParaID);
	//if( it != m_QMapSystemPara.end() )
	//{
	//	return it.value;
	//}
	//else
	//{
	//	QString sValue;

	//	Rsp9030 rsp9030;
	//	if(CTranMessage::Handle9030(rsp9030, sParaID) == 0 && rsp9030.htm_para_info.size() > 0)
	//	{
	//		sValue = rsp9030.htm_para_info.GetQString(0, "para_value");
	//		m_QMapSystemPara[sParaID] = sValue;
	//	}
	//	else
	//	{
	//		// ��������������ʧ������Ĭ�ϵĲ���
	//		sValue = sDefaultValue;
	//	}

	//	return sValue;
	//}


	return "";
}

// ˢ�±�����Ϣ
void CTraderCpMgr::RefreshOrderInfo(OrderBase *OrgOrder, const OrderBase *NewOrder)
{
	OrgOrder->status = NewOrder->status;

	// ��¼�µĹ㲥��Ϣ
	if (NewOrder->orderNo != "")
	{
		// ��Ϊһ��ʼ��¼������ʱ��״̬Ϊ"�����걨"����ʱ����û�б����ţ�����ϵͳ�ı����ţ��ģ��ڽ��������ɹ�����б�����
		OrgOrder->orderNo = NewOrder->orderNo;
	}

	if (OrgOrder->remainAmount >= NewOrder->remainAmount)
	{
		OrgOrder->remainAmount = NewOrder->remainAmount;
		OrgOrder->applyTime = NewOrder->applyTime;

		if (NewOrder->RspMsg.length() > 3)
		{
			OrgOrder->RspMsg = NewOrder->RspMsg;
		}
	}
}

double CTraderCpMgr::GetOpenFare(const QString &sProdCode, bool bLong, double fUnite, const FareInfo &fi, int iHand /*= 1*/)
{
	if (fi.fare_value.isEmpty())
	{
		return 0;
	}


	double dTotalMoney = 0;
	if (fi.fare_mode_id == CONSTANT_CT_FARE_MODE_BAL) // �����ģʽ���㱣֤��
	{
		// ���ݳֲַ����ȡ��Ӧ�ĳֲ���Ϣ
		QMap<QString, DeferPosi>::iterator it = m_QMapDeferPosi.find(sProdCode);
		const DeferPosiInfo &info = bLong ? it->infoLong : it->infoShort;

		// ��ȡ�������ϵ����ս����
		const QUOTATION& qt = g_TraderCpMgr.m_QMapQuotation[sProdCode.toStdString()];
		double dLastSettle = qt.m_uiLastSettle / g_Global.m_dQTFactor;


		// ��ȡ�÷����ϵĳֲ���Ϣ���ж�����Ƿ�����
		if (info.iYesAmt >= iHand)
		{
			dTotalMoney = dLastSettle*fUnite*iHand;
		}
		else
		{
			// ���δ��ƽ���Ĳ���
			iHand -= info.iYesAmt;
			dTotalMoney = dLastSettle*fUnite*info.iYesAmt;

			// ���Ͻ�ֵ�ƽ��������
			const LISTDeferMatch &listMatch = info.listMatch;
			for (LISTDeferMatch::const_iterator it = listMatch.begin(); it != listMatch.end(); )
			{
				if (it->iHand > iHand || it->iHand == iHand) // �����ǰ��ˮ��������С��ʣ������
				{
					dTotalMoney += iHand * it->dPrice;
					break;
				}
				else // �����ǰ��ˮ������С��ʣ�����������¼δ��ƽ������������ɾ����ǰ��ˮ
				{
					iHand -= it->iHand;
					dTotalMoney += it->iHand * it->dPrice;
					it++;
				}
			}
		}

		dTotalMoney *= fi.fare_value.toFloat();
	}

	return dTotalMoney;
}

double CTraderCpMgr::GetOpenFareOrg(const QString &sProdCode, bool bLong, double fUnite, int iHand /*= 1*/)
{
	double dTotalMoney;

	// ���ݳֲַ����ȡ��Ӧ�ĳֲ���Ϣ
	QMap<QString, DeferPosi>::iterator it = m_QMapDeferPosi.find(sProdCode);
	const DeferPosiInfo &info = bLong ? it->infoLong : it->infoShort;

	// ��ȡ�������ϵ����ս���ۣ�Ҳ���ô��ڴ��еĳֲ���Ϣ���
	const QUOTATION& qt = g_TraderCpMgr.m_QMapQuotation[sProdCode.toStdString()];
	double dLastSettle = qt.m_uiLastSettle / g_Global.m_dQTFactor;

	// �ж�����Ƿ�����
	if (info.iYesAmt >= iHand)
	{
		dTotalMoney = dLastSettle*fUnite*iHand; // �Ƿ�Ҫ��ʽ��
	}
	else
	{
		// ���δ��ƽ���Ĳ���
		iHand -= info.iYesAmt;
		dTotalMoney = dLastSettle*fUnite*info.iYesAmt;

		// ���Ͻ�ֵ�ƽ��������
		const LISTDeferMatch &listMatch = info.listMatch;
		for (LISTDeferMatch::const_iterator it = listMatch.begin(); it != listMatch.end(); )
		{
			if (it->iHand > iHand || it->iHand == iHand) // �����ǰ��ˮ��������С��ʣ������
			{
				dTotalMoney += iHand * it->dPrice;
				break;
			}
			else // �����ǰ��ˮ������С��ʣ�����������¼δ��ƽ������������ɾ����ǰ��ˮ
			{
				iHand -= it->iHand;
				dTotalMoney += it->iHand * it->dPrice;
				it++;
			}
		}
	}

	return dTotalMoney;
}

double CTraderCpMgr::CalculateMagin(const QString &sProdCode, double dPrice, int iHand, bool bSumSingle /*= true*/)
{
	ProdCodeInfo info;
	if (GetProdCodeInfo(sProdCode, info))
	{
		// ��ȡÿ�ֵļ�����λ ���ˣ�
		double dUnite = CHJCommon::HandToGram(sProdCode, info.measure_unit);

		// ��������Ҫ���ܽ��
		double dTotalMoney = 0.00;

		// ���𣨷������   ������λ*ί�м۸�*��������ע�����շ��������룬�Խ�����˴���
		double dOrgCost = CHJGlobalFun::DoubleFormat(dUnite * iHand * dPrice);

		// ��֤����㣨��Ա�ͽ�������
		ExchFare ef_margin = CHJCommon::GetExchFareValueByExchBal(sProdCode, dUnite, dOrgCost, iHand, GetBFareValue(sProdCode, CONSTANT_EXCH_BAIL_FARE_ID), GetMFareValue(sProdCode, CONSTANT_EXCH_BAIL_FARE_ID));

		// ����������-���ֱ�֤��
		if (bSumSingle)
			dTotalMoney = ef_margin.sumSingle();
		else
			dTotalMoney = ef_margin.sum();

		return dTotalMoney;
	}
	else
	{
		return 0.00;
	}
}



// ע�ᱨ���㲥 hHandle��ע����Ϣ�Ĵ��ھ�� bSubscrib���Ƿ��Ƕ��ģ�����Ϊȡ������ sMarketID���г�����ID
void CTraderCpMgr::SubscribeOrder(QWidget* hHandle, bool bSubscrib /*= true*/, const QString &sMarketID /*= ""*/)
{
	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_SPOT)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRTNSPOTORDER, hHandle);
			Subscribe(E_ONRECVRSPSPOTORDER, hHandle);
			Subscribe(E_ONRECVSPOTORDER, hHandle);
		}
		else
		{
			Unsubscribe(E_ONRECVRTNSPOTORDER, hHandle);
			Unsubscribe(E_ONRECVRSPSPOTORDER, hHandle);
			Unsubscribe(E_ONRECVSPOTORDER, hHandle);
		}
	}

	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_FORWARD)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRSPFORWARDORDER, hHandle);
			Subscribe(E_ONRECVRTNFORWARDORDER, hHandle);
			Subscribe(E_ONRECVDEFERORDER, hHandle);
		}
		else
		{
			Unsubscribe(E_ONRECVRSPFORWARDORDER, hHandle);
			Unsubscribe(E_ONRECVRTNFORWARDORDER, hHandle);
			Unsubscribe(E_ONRECVDEFERORDER, hHandle);
		}
	}

	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_DEFER)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRTNDEFERORDER, hHandle);
			Subscribe(E_ONRECVRSPDEFERORDER, hHandle);
			Subscribe(E_ONRECVDEFERORDER, hHandle);

			Subscribe(E_ONRECVRTNDEFERDELIVERYAPPORDER, hHandle);
			Subscribe(E_ONRECVRSPDEFERDELIVERYAPPORDER, hHandle);
			Subscribe(E_ONRECVDEFERDELIVERYAPPORDER, hHandle);

			Subscribe(E_ONRECVRTNMIDDLEAPPORDER, hHandle);
			Subscribe(E_ONRECVRSPMIDDLEAPPORDER, hHandle);
			Subscribe(E_ONRECVMIDDLEAPPORDER, hHandle);
		}
		else
		{
			Unsubscribe(E_ONRECVRTNDEFERORDER, hHandle);
			Unsubscribe(E_ONRECVRSPDEFERORDER, hHandle);
			Unsubscribe(E_ONRECVDEFERORDER, hHandle);

			Unsubscribe(E_ONRECVRTNDEFERDELIVERYAPPORDER, hHandle);
			Unsubscribe(E_ONRECVRSPDEFERDELIVERYAPPORDER, hHandle);
			Unsubscribe(E_ONRECVDEFERDELIVERYAPPORDER, hHandle);

			Unsubscribe(E_ONRECVRTNMIDDLEAPPORDER, hHandle);
			Unsubscribe(E_ONRECVRSPMIDDLEAPPORDER, hHandle);
			Unsubscribe(E_ONRECVMIDDLEAPPORDER, hHandle);
		}

	}
}
// ע�᳷���㲥 hHandle��ע����Ϣ�Ĵ��ھ�� bSubscrib���Ƿ��Ƕ��ģ�����Ϊȡ������ sMarketID���г�����ID
void CTraderCpMgr::SubscribeOrderCancel(QWidget * hHandle, bool bSubscrib /*= true*/, const QString &sMarketID /*= ""*/)
{
	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_SPOT)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRTNSPOTORDERCANCEL, hHandle);
			Subscribe(E_ONRECVRSPSPOTORDERCANCEL, hHandle);

		}
		else
		{
			Unsubscribe(E_ONRECVRTNSPOTORDERCANCEL, hHandle);
			Unsubscribe(E_ONRECVRSPSPOTORDERCANCEL, hHandle);
		}
	}

	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_FORWARD)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRTNFORWARDORDERCANCEL, hHandle);
			Subscribe(E_ONRECVRSPFORWARDORDERCANCEL, hHandle);
		}
		else
		{
			Unsubscribe(E_ONRECVRTNFORWARDORDERCANCEL, hHandle);
			Unsubscribe(E_ONRECVRSPFORWARDORDERCANCEL, hHandle);
		}
	}

	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_DEFER)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRTNDEFERORDERCANCEL, hHandle);
			Subscribe(E_ONRECVRSPDEFERORDERCANCEL, hHandle);

			Subscribe(E_ONRECVRTNDEFERDELIVERYAPPORDERCANCEL, hHandle);
			Subscribe(E_ONRECVRSPDEFERDELIVERYAPPORDERCANCEL, hHandle);

			Subscribe(E_ONRECVRTNMIDDLEAPPORDERCANCEL, hHandle);
			Subscribe(E_ONRECVRSPMIDDLEAPPORDERCANCEL, hHandle);
		}
		else
		{
			Unsubscribe(E_ONRECVRTNDEFERORDERCANCEL, hHandle);
			Unsubscribe(E_ONRECVRSPDEFERORDERCANCEL, hHandle);

			Unsubscribe(E_ONRECVRTNDEFERDELIVERYAPPORDERCANCEL, hHandle);
			Unsubscribe(E_ONRECVRSPDEFERDELIVERYAPPORDERCANCEL, hHandle);

			Unsubscribe(E_ONRECVRTNMIDDLEAPPORDERCANCEL, hHandle);
			Unsubscribe(E_ONRECVRSPMIDDLEAPPORDERCANCEL, hHandle);
		}
	}
}
// ע��ɽ�����Ϣ hHandle��ע����Ϣ�Ĵ��ھ�� bSubscrib���Ƿ��Ƕ��ģ�����Ϊȡ������ sMarketID���г�����ID
void CTraderCpMgr::SubscribeMatch(QWidget* hHandle, bool bSubscrib /*= true*/, const QString &sMarketID /*= ""*/)
{
	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_SPOT)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRTNSPOTMATCH, hHandle);
		}
		else
		{
			Unsubscribe(E_ONRECVRTNSPOTMATCH, hHandle);
		}
	}

	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_FORWARD)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRTNFORWARDMATCH, hHandle);
		}
		else
		{
			Unsubscribe(E_ONRECVRTNFORWARDMATCH, hHandle);
		}
	}

	if (sMarketID.isEmpty() || sMarketID == CONSTANT_B_MARKET_ID_DEFER)
	{
		if (bSubscrib)
		{
			Subscribe(E_ONRECVRTNDEFERMATCH, hHandle);
			Subscribe(E_ONRECVRTNDEFERDELIVERYAPPMATCH, hHandle);
		}
		else
		{
			Subscribe(E_ONRECVRTNDEFERMATCH, hHandle);
			Unsubscribe(E_ONRECVRTNDEFERDELIVERYAPPMATCH, hHandle);
		}
	}
}
// ע�����б�����صĹ㲥
void CTraderCpMgr::SubscribeAll(QWidget* hHandle, bool bSubscrib /*= true*/)
{
	SubscribeOrder(hHandle, bSubscrib);
	SubscribeOrderCancel(hHandle, bSubscrib);
	SubscribeMatch(hHandle, bSubscrib);
}

void CTraderCpMgr::SubscribeDefer(QWidget* hHandle, bool bSubscribe /*= true*/, bool bNormal /*= true*/, bool bDDA /*= true*/, bool bMA /*= true*/)
{
	if (bSubscribe)
	{
		if (bNormal)
		{
			Subscribe(E_ONRECVRTNDEFERORDER, hHandle);
			Subscribe(E_ONRECVRSPDEFERORDER, hHandle);
			Subscribe(E_ONRECVDEFERORDER, hHandle);

			Subscribe(E_ONRECVRTNDEFERORDERCANCEL, hHandle);
			Subscribe(E_ONRECVRSPDEFERORDERCANCEL, hHandle);

			Subscribe(E_ONRECVRTNDEFERMATCH, hHandle);
		}

		if (bDDA)
		{
			Subscribe(E_ONRECVRTNDEFERDELIVERYAPPORDER, hHandle);
			Subscribe(E_ONRECVRSPDEFERDELIVERYAPPORDER, hHandle);
			Subscribe(E_ONRECVDEFERDELIVERYAPPORDER, hHandle);

			Subscribe(E_ONRECVRTNDEFERDELIVERYAPPORDERCANCEL, hHandle);
			Subscribe(E_ONRECVRSPDEFERDELIVERYAPPORDERCANCEL, hHandle);

			Subscribe(E_ONRECVRTNDEFERDELIVERYAPPMATCH, hHandle);
		}

		if (bMA)
		{
			Subscribe(E_ONRECVRTNMIDDLEAPPORDER, hHandle);
			Subscribe(E_ONRECVRSPMIDDLEAPPORDER, hHandle);
			Subscribe(E_ONRECVMIDDLEAPPORDER, hHandle);

			Subscribe(E_ONRECVRTNMIDDLEAPPORDERCANCEL, hHandle);
			Subscribe(E_ONRECVRSPMIDDLEAPPORDERCANCEL, hHandle);
		}
	}
	else
	{
		if (bNormal)
		{
			Unsubscribe(E_ONRECVRTNDEFERORDER, hHandle);
			Unsubscribe(E_ONRECVRSPDEFERORDER, hHandle);
			Unsubscribe(E_ONRECVDEFERORDER, hHandle);

			Unsubscribe(E_ONRECVRTNDEFERORDERCANCEL, hHandle);
			Unsubscribe(E_ONRECVRSPDEFERORDERCANCEL, hHandle);

			Subscribe(E_ONRECVRTNDEFERMATCH, hHandle);
		}

		if (bDDA)
		{
			Unsubscribe(E_ONRECVRTNDEFERDELIVERYAPPORDER, hHandle);
			Unsubscribe(E_ONRECVRSPDEFERDELIVERYAPPORDER, hHandle);
			Unsubscribe(E_ONRECVDEFERDELIVERYAPPORDER, hHandle);

			Unsubscribe(E_ONRECVRTNDEFERDELIVERYAPPORDERCANCEL, hHandle);
			Unsubscribe(E_ONRECVRSPDEFERDELIVERYAPPORDERCANCEL, hHandle);

			Unsubscribe(E_ONRECVRTNDEFERDELIVERYAPPMATCH, hHandle);
		}

		if (bMA)
		{
			Unsubscribe(E_ONRECVRTNMIDDLEAPPORDER, hHandle);
			Unsubscribe(E_ONRECVRSPMIDDLEAPPORDER, hHandle);
			Unsubscribe(E_ONRECVMIDDLEAPPORDER, hHandle);

			Unsubscribe(E_ONRECVRTNMIDDLEAPPORDERCANCEL, hHandle);
			Unsubscribe(E_ONRECVRSPMIDDLEAPPORDERCANCEL, hHandle);
		}
	}

}



//#include "Mgr/WindVaneMgr.h"
void CTraderCpMgr::IniSystemSetting()
{
	QString csPath = g_Global.GetSystemIniPath();

	QString sfile = g_Global.GetUserIniPath();
	QString str;

	//// ����ʱ�� 
	//GetPrivateProfileQString("Display", "ScreenTimeout", "0", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	//g_Global.m_TimeOutScreen = atoi(str);
	App::GetPriProfileString(sfile, "Display", "ScreenTimeout", str);
	g_Global.m_TimeOutScreen = str.toInt();
	//// ��������λ��
	//GetPrivateProfileQString("Display", "OrderPosition", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Display", "OrderPosition", str);
	g_Global.m_bCommitLeft = (str == "1") ? true : false;
	//// ������
	//GetPrivateProfileQString("Display", "UIStyle", "0", str.GetBuffer(), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Display", "UIStyle", str);
	g_Global.m_iInterfaceStyle = str.toInt();
//// �µ��Ƿ�ȷ��
	//GetPrivateProfileQString("Order", "ConfirmOrder", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "ConfirmOrder", str);
	g_Global.m_bAskConfirm = (str == "1") ? TRUE : FALSE;
	//// �Ƿ�֤�������пɼ�
	//GetPrivateProfileQString("Order", "AlwayShowBS5", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "AlwayShowBS5", str);
	g_Global.m_bAlwaysShowBS5 = (str == "1") ? TRUE : FALSE;
	//// ѡ���嵵����ʱ�޸���������
	//GetPrivateProfileQString("Order", "ChangeBS", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "ChangeBS", str);
	g_Global.m_bChangeBS = (str == "1") ? TRUE : FALSE;

	//// �м�ƽ��ȷ��
	//GetPrivateProfileQString("Order", "OppCovConfirm", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "OppCovConfirm", str);
	g_Global.m_bOppCovConfirm = (str == "1") ? TRUE : FALSE;
	//// ��ʾ���ڷ�ʽ��
	//GetPrivateProfileQString("Order", "ShowDeferMode", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	//g_Global.m_bShowDeferMode = (str == "1") ? TRUE : FALSE;
	App::GetPriProfileString(sfile, "Order", "ShowDeferMode", str);
	g_Global.m_bShowDeferMode = (str == "1") ? TRUE : FALSE;

	//// �ڱ������ѡ���Լ��ֲ֡������Ϣ����
	//GetPrivateProfileQString("Order", "ChiCang", "1" ,str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "ChiCang", str);
	g_Global.m_bInsTriggerInfo = (str == "1") ? TRUE : FALSE;
	//// ˫���ֲ֡����ֱ�ӱ���
	//GetPrivateProfileQString("Order", "ChiCnag_Click", "0" ,str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	g_Global.m_bChiCang_Click = (str == "1") ? FALSE : TRUE;
	App::GetPriProfileString(sfile, "Order", "ChiCnag_Click", str);
	g_Global.m_bChiCang_Click = (str == "1") ? false : true;

	//// ����ȷ��
	//GetPrivateProfileQString("OrderModify", "ConfirmUnorder", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "OrderModify", "ConfirmUnorder", str);
	g_Global.m_bConfirmUnorder = (str == "1") ? TRUE : FALSE;
	//// ƽ��ȷ��
	//GetPrivateProfileQString("Order", "CovPosiConfirm", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "CovPosiConfirm", str);
	g_Global.m_bCovPosiConfirm = (str == "1") ? TRUE : FALSE;
	//// Ԥ�񵥷���ȷ��
	//GetPrivateProfileQString("Order", "PreOrderConfirm", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "PreOrderConfirm", str);
	g_Global.m_bPreOrderConfirm = (str == "0") ? false : true;
	//// ����ʱ������ǰ�ֲ�����ʾ
	//GetPrivateProfileQString("Order", "AskOFCfm", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Display", "AskOFCfm", str);
	g_Global.m_bPosiOFConfirm = (str == "0") ? false : true;
	//// ����Ԥ����ʾ
	//GetPrivateProfileQString("Order", "CreatePreOrderTip", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "CreatePreOrderTip", str);
	g_Global.m_bTipsAddPreOrder = (str == "0") ? false : true;
	//// �µ��ɹ���ʾ
	//GetPrivateProfileQString("Order", "TipsAskSus", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "TipsAskSus", str);
	g_Global.m_bTipsAskSus = (str == "1") ? TRUE : FALSE;
	//GetPrivateProfileQString("Order", "SoundAskSus", "", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "SoundAskSus", str);
	g_Global.m_csSoundAskSus = str;
//// �µ�ʧ����ʾ
	//GetPrivateProfileQString("Order", "TipsAskFail", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "TipsAskFail", str);
	g_Global.m_bTipsAskFail = (str == "1") ? TRUE : FALSE;
	//GetPrivateProfileQString("Order", "SoundAskFail", "", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "SoundAskFail", str);
	g_Global.m_csSoundAskFail = str;
	//// �ҵ��ɽ�
	//GetPrivateProfileQString("Order", "TipsOrderMatch", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "TipsOrderMatch", str);
	g_Global.m_bTipsOrderMatch = (str == "1") ? TRUE : FALSE;

	//GetPrivateProfileQString("Order", "SoundOrderMatch", "", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "SoundOrderMatch", str);
	g_Global.m_csSoundOrderMatch = str;
	//// �����ɹ�
	//GetPrivateProfileQString("Order", "TipsCancelSus", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "TipsCancelSus", str);
	g_Global.m_bTipsCancelSus = (str == "1") ? TRUE : FALSE;
	//GetPrivateProfileQString("Order", "SoundCancelSus", "", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "SoundCancelSus", str);
	g_Global.m_csSoundCancelSus = str;
	//// ����ʧ��
	//GetPrivateProfileQString("Order", "TipsCancelFail", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "TipsCancelFail", str);
	g_Global.m_bTipsCancelFail = (str == "1") ? TRUE : FALSE;
	//GetPrivateProfileQString("Order", "SoundCancelFail", "", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "SoundCancelFail", str);
	g_Global.m_csSoundCancelFail = str;

	//// �Ƿ���ʾ�ͻ���Ϣ
	//GetPrivateProfileQString("Display", "ShowCusInfo", "1", str.GetBuffer(MAX_PATH), MAX_PATH, sfile);
	App::GetPriProfileString(sfile, "Order", "ShowCusInfo", str);
	g_Global.m_bShowCusInfo = (str == "1") ? TRUE : FALSE;
	// ���ط������ʾƷ��
	//CWindVaneMgr::GetInstance().LoadShowInsID();
}

void CTraderCpMgr::SetBitSet( bitset<5> &bitvec, bool bFund /*= false*/, bool bStore /*= false*/, bool bPosi /*= false*/, bool bLong /*= false*/, bool bBuy /*= false*/ )
{
	if(bFund) bitvec.flip(0);
	if(bStore) bitvec.flip(1);
	if(bPosi) bitvec.flip(2);
	if(bLong) bitvec.flip(3);
	if(bBuy) bitvec.flip(4);
}

bool CTraderCpMgr::IsUnFindLocalOrderNo(const QString &sLocalOrderNo)
{
	for (int i = 0; i < m_arrUnFindLocalOrderNo.size(); i++)
	{
		if (m_arrUnFindLocalOrderNo[i] == sLocalOrderNo) return true;
	}

	return false;

}

double CTraderCpMgr::GetRealeaseMoney(const QString &localOrderNo, int iHand)
{
	// �ͷ��ʽ�
	double dFrozenTradeFee = 0.00;
	if (!localOrderNo.isEmpty())
	{
		// ��ȡ�ñʵ��Ķ�����Ϣ
		QMap<QString, OrderFrozeInfo>::iterator it = m_QMapOrderFroze.find(localOrderNo);
		if (it != m_QMapOrderFroze.end())
		{
			// ��ȡ�ⶳ�ʽ�
			//if(it.value().CancelBal(iHand, dFrozenTradeFee))
			//{
			//	 ɾ���ñ���ˮ
			//}
		}
	}

	return dFrozenTradeFee;
}

double CTraderCpMgr::GetMatchUnReleaseMoney(const QString &localOrderNo)
{
	double dFrozenTradeFee = 0.00;
	QMap<QString, int>::iterator it = m_QMapMatchUnFindInfo.find(localOrderNo);
	if (it != m_QMapMatchUnFindInfo.end())
	{
		dFrozenTradeFee = GetRealeaseMoney(localOrderNo, it.value());
	}

	return dFrozenTradeFee;
}

// ��ȡһ�ʳɽ�����Ӧ�ýⶳ���ʽ�
double CTraderCpMgr::HandleMatchReleaseMoney(const QString &localOrderNo, int iHand)
{
	double dFrozenTradeFee = 0.00; //

								   // ���ݱ��ر����Ų��Ҹñʱ����Ķ�����Ϣ
	QMap<QString, OrderFrozeInfo>::iterator it = m_QMapOrderFroze.find(localOrderNo);
	if (it != m_QMapOrderFroze.end()) // �������
	{
		// ��ȡ�ñʵ��Ķ�����Ϣ
		OrderFrozeInfo &stFrozeInfo = it.value();
		// �ⶳ�ʽ�
		//if(stFrozeInfo.CancelBal(iHand, dFrozenTradeFee))
		//{
		//	// ɾ���ñ���ˮ
		//}
	}
	else
	{
		// û�ҵ����ʾ����ɽ��Ľⶳ�ʽ�ʧ�ܣ���¼���ر����ź�����
		QMap<QString, int>::iterator it = m_QMapMatchUnFindInfo.find(localOrderNo);
		if (it != m_QMapMatchUnFindInfo.end())
		{
			it.value() += iHand;
		}
		else
		{
			m_QMapMatchUnFindInfo[localOrderNo] = iHand;
		}
	}

	return dFrozenTradeFee;
}

// ���ݱ���״̬ID�жϸñʵ��Ƿ�Ҫ�����Զ�����Ĵ���
bool CTraderCpMgr::IsOrderCanBeProcess(const QString &sOrderState)
{
	// o���ѱ��� c��ȫ���ɽ� p�����ֳɽ�  3�����ɲ��� 1�������걨
	// ȥ�������걨��״̬�����
	if (sOrderState == "o" || sOrderState == "c" || sOrderState == "p" || sOrderState == "3") // 3�����ɲ���  d���ѳ���
		return true;
	else
		return false;
}

// ����������ip����ȡip�������ip�Ļ����򷵻�һ����ֵ��
QString CTraderCpMgr::GetIPFromDomain(const QString &sDomainIP)
{/*
 if(sDomainIP.isEmpty())
 {
 return "";
 }
 else
 {
 WSAData wsData;
 int WSA_return = WSAStartup(0x0101,&wsData);

 DWORD dwIP = 0;
 //��������
 HOSTENT* pHS = gethostbyname(sDomainIP.toLatin1().data());
 if(   pHS   !=   NULL)
 {
 in_addr addr;
 CopyMemory(&addr.S_un.S_addr, pHS->h_addr_list[0], pHS->h_length);
 dwIP = addr.S_un.S_addr;
 }

 BYTE   by1,   by2,   by3,   by4;
 char   szIP[30] = {0};
 by1   =   HIBYTE(HIWORD(dwIP)),   by2   =   LOBYTE(HIWORD(dwIP)),   by3   =   HIBYTE(LOWORD(dwIP)),   by4   =   LOBYTE(LOWORD(dwIP));
 sprintf(szIP,   "%d.%d.%d.%d",   by4,   by3,   by2,   by1);

 // remove by  20121219 ȥ���Ļ�������ʹ��socket
 // WSACleanup();

 QString sReturn = szIP;
 return sReturn;
 }
 */


	QString sReturn = sDomainIP;
	return sReturn;
}

//kenny  20180309   byte ?? hex
template<typename TInputIter>
std::string make_hex_string(TInputIter first, TInputIter last, bool use_uppercase = true, bool insert_spaces = false)
{
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    if (use_uppercase)
        ss << std::uppercase;
    while (first != last)
    {
        ss << std::setw(2) << static_cast<int>(*first++);
        if (insert_spaces && first != last)
            ss << " ";
    }
    return ss.str();
}

// �һ�v����?�ը���??����v?O O=����?����pszPwd��v���v��ε??����?�Σ���bShort�� ??��v?�v��Ζ?O��O��/MD5��v?����v��
QString CTraderCpMgr::GetEncryptPSW(const char* pszPwd, bool bShort /*= false*/)
{
	QString sFinal;

#ifdef _WIN32
	//kenny  20171128  �v������������v��?����?��
    sFinal = MD5::ToMD5(pszPwd, strlen(pszPwd)).c_str();// �v��v��?
#else
    MD5_CTX ctx;
    unsigned char outmd[16];
    //????openssl?64??????
    int i=0;
    memset(outmd,0,sizeof(outmd));
    MD5_Init(&ctx);
    MD5_Update(&ctx,pszPwd,strlen(pszPwd));
    MD5_Final(outmd,&ctx);


    string str;
    std::vector<uint8_t> byte_vector(std::begin(outmd), std::end(outmd));
    str = make_hex_string(byte_vector.begin(), byte_vector.end(), false);
    sFinal = str.c_str();
#endif


	if (bShort)
	{
		sFinal = sFinal.mid(8, 16);
	}


	return sFinal;
}

// ���������ļ��еĵ��ճ������ˮ
void CTraderCpMgr::IniTodayTransfer()
{
	char buf[500] = { 0 };
	QString sValue;

	// ��ȡ�ļ��б���Ŀͻ���
	//::GetPrivateProfileQString("info", "InOutRecords", "", buf, sizeof(buf), g_Global.GetDataIniPath());
	//sValue = buf;
	//int iPos = sValue.find("��"); // ��ȡʱ����ֵ�ķָ���
	//if(iPos != -1)
	//{
	//	// ����ͻ�����ͬ
	//	if(sValue.substr(0, iPos) == g_Global.m_strUserID)
	//	{
	//		// ��ȡ��һ������+ֵ���ַ���
	//		sValue = sValue.substr(iPos+2);

	//		iPos = sValue.find("��"); // ��ȡʱ����ֵ�ķָ���
	//		if(iPos != -1)
	//		{
	//			// ��ȡ���ݶ�Ӧ�Ľ�����
	//			QString sExchDate = sValue.mid(0, iPos);
	//			// �뵱ǰʵ�ʵĽ����նԱ�
	//			if(sExchDate == g_Global.m_strExchDate)
	//			{
	//				// ���ص��ճ������ˮ
	//				ArrayListMsg alm_result;
	//				alm_result.Parse(sValue.mid(iPos+2));
	//				for(size_t i = 0; i < alm_result.size(); i++)
	//				{
	//					const ArrayListMsg &aMsg = alm_result.GetValue(i); // ��ȡ�����һ������
	//					if(!aMsg.GetQStringEx(0).isEmpty())
	//					{
	//						QString sMoney = aMsg.GetQStringEx(1);
	//						auto Insert_Pair = m_QMapTransfer.insert(aMsg.GetQStringEx(0), sMoney);
	//						m_stFundInfo.dAllBalance += sMoney.toFloat();
	//						m_stFundInfo.dUseFulBal += sMoney.toFloat();
	//					}
	//				}
	//			}
	//			else
	//			{
	//				// �Ƿ�Ҫ���
	//			}
	//		}
	//	}
	//}
}

// 
QString CTraderCpMgr::FormatCurTransferStr()
{
	QString sValue;
	for (QMap<QString, QString>::iterator it = m_QMapTransfer.begin(); it != m_QMapTransfer.end(); it++)
	{
		sValue = sValue + it.key() + "��" + it.value() + "��" + "��";;
	}

	return sValue;
}

void CTraderCpMgr::CustomerUsefulPosi(const QString& prodCode, int& iUsefullong, int& iUsefulshort)
{
	iUsefullong = iUsefulshort = 0;
	// ��ȡ��Ʒ�ֵĲ�λ��Ϣ
	QMap<QString, DeferPosi>::const_iterator it = g_TraderCpMgr.m_QMapDeferPosi.find(prodCode);
	if (it != g_TraderCpMgr.m_QMapDeferPosi.end())
	{
		iUsefullong = it->infoLong.iUsefulAmt;
		iUsefulshort = it->infoShort.iUsefulAmt;
	}
}

// ��ȡ�����ֱ����ļ۸�
double CTraderCpMgr::GetMAOrderPrice(const QString &sProdCode)
{
	// ��¼��󷵻صļ۸�
	double dPrice;

	// ��ȡ������Ϣ
	const QUOTATION& qt = m_QMapQuotation[sProdCode.toStdString()];

	// �������õļ۸�ʽȡ�����Ӧ�ļ۸�
	unsigned int uiPrice = qt.m_uiAverage;

	if (uiPrice != 0)
	{		// ��ȡ�������͵ļ۸񣬲��շ����������ʽ��
		dPrice = CHJGlobalFun::DoubleFormat(uiPrice / g_Global.m_dQTFactor);
	}
	else
	{
		dPrice = GetDeferDeliveryPrice(sProdCode);
	}

	return dPrice;
}

void CTraderCpMgr::WriteTodayTransferToFile()
{
	QString sWriteData = g_Global.m_strUserID + "��" + g_Global.m_strExchDate + "��" + FormatCurTransferStr();
	//::WritePrivateProfileQString("info", "InOutRecords", sWriteData,g_Global.GetDataIniPath()); 
}

// ����������ˮ��ѯ��һ��������ˮ����Ϣ�������û��¼��������ڴ��еĳ������ˮ��¼�����µ������ʽ���Ϣ
// ��ˮ���ڴ��в������򷵻�true�������򷵻�false
bool CTraderCpMgr::DealOneHandTransfer(const QString &sSerialNo, QString sExchBal, bool bIn)
{
	QMap<QString, QString>::iterator it = m_QMapTransfer.find(sSerialNo);
	if (it == m_QMapTransfer.end())
	{
		// ����ǳ������ж�ԭ���Ľ���ַ����Ƿ�����ţ�û�������
		if (!bIn)
		{
			int iPos = sExchBal.indexOf("-"); // ��ȡʱ����ֵ�ķָ���
			if (iPos == -1)
			{
				sExchBal = "-" + sExchBal;
			}
		}

		// ��¼���ڴ� 
		m_QMapTransfer[sSerialNo] = sExchBal;

		m_stFundInfo.dAllBalance += sExchBal.toFloat();
		m_stFundInfo.dUseFulBal += sExchBal.toFloat();

		m_mapBdr[E_REFRESHFUND].Broadcast(WM_REFRESH_FUND, 0, 0);

		return true;
	}

	return false;
}

// ��������������������ˮ
bool CTraderCpMgr::GetTodayTransfer()
{
	// 	// ��ȡ�������ID 
	// 	ArrayListMsg almViewField;  
	// 	QVector< pair<QString,QString> > vecPara;
	// 	ArrayListMsg alm_result;
	// 
	// 	almViewField.Parse("in_account_flag��serial_no��access_way��exch_bal��"); // �Ƿ����ˡ�ת����ˮ�šĳ�����ת�˽���
	// 	CHJGlobalFun::PairAdd(vecPara, "access_way", "");
	// 
	// 	Rsp6002 rsp6002;
	// 	HEADER_RSP headrsp;
	// 
	// 	if(CTranMessage::Handle6002(rsp6002, headrsp, "AcctFundAutoInOutFlow", almViewField, vecPara, 500 ) == 0 && rsp6002.alm_result.size() > 0)
	// 	{
	// 
	// 	}


#if (defined _VERSION_GF) || (defined _VERSION_JH) || (defined _VERSION_YC) || (defined _VERSION_PA)// ���кͽ���ͨ�������ˮ��ѯ����һ���ı���

	Rsp3101 rsp;
	if (CTranMessage::Handle3101(rsp, 5) == 0)
	{
		LoadTodayTransfer(rsp.htm_result);

		return true;
	}
	else
	{
		return false;
	}
#else
	Rsp3021 rsp; //Ӧ������
				 /*if(CTranMessage::Handle3021(rsp, 1, "") == 0)
				 {
				 LoadTodayTransfer(rsp.alm_custtype_list);

				 return true;
				 }
				 else*/
	{
		return false;
	}

#endif
}

// ����ͨ�汾
void CTraderCpMgr::LoadTodayTransfer(HashtableMsg &htm_result)
{
	int iRewriteCount = 0;

	for (size_t i = 0; i < htm_result.size(); i++)
	{
		if (htm_result.GetString(i, "in_account_flag") == "��")
		{
			bool bIn = htm_result.GetString(i, "access_way") == "����" ? true : false;

			if (DealOneHandTransfer(htm_result.GetString(i, "serial_no").c_str(), htm_result.GetString(i, "exch_bal").c_str(), bIn))
			{
				iRewriteCount++;
			}
		}
	}

	if (iRewriteCount > 0)
	{
		WriteTodayTransferToFile();
	}
}

void CTraderCpMgr::LoadTodayTransfer(ArrayListMsg &alm)
{
	int iRewriteCount = 0;

	for (size_t i = 0; i < alm.size(); i++)
	{
		if (alm.GetStringEx(i, 12) == "��")
		{
			bool bIn = alm.GetStringEx(i, 6) == "����" ? true : false;

			if (DealOneHandTransfer(alm.GetStringEx(i, 0).c_str(), alm.GetStringEx(i, 7).c_str(), bIn))
			{
				iRewriteCount++;
			}
		}
	}

	if (iRewriteCount > 0)
	{
		WriteTodayTransferToFile();
	}
}

void CTraderCpMgr::IniOrderSerial()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("ddhhmmss");
	current_date = g_Global.m_strUserID + current_date;// �ͻ��ż���ʱ���ʶ��Ϊ�ͻ����к�
	m_uOrderSerial = current_date.toULongLong();
}

QString CTraderCpMgr::GetOrderSerialStr()
{
	return QString::number(m_uOrderSerial);
}

void CTraderCpMgr::RefreshCusFundInfo()
{
#ifdef _NOAUTO_FUND
	Rsp1020 rsp1020;
	if (CTranMessage::Handle1020(rsp1020, '0', '1', '0', '0', '0', '1', true) == 0)
	{
		// ��ȡ�ɹ��򽫿ͻ��ʽ���Ϣ���Ƶ��ڴ����
		m_rsp1020.CopyFundInfo(rsp1020);
		m_mapBdr[E_ONREFRESHCUSTOMDATA].Broadcast(WM_REFRESH_CUSTOM_INFO, 0, 0);
	}
#endif
}

void CTraderCpMgr::CalculatePosiMargin()
{
	m_stFundInfo.dPosiMargin = 0.00;

	for (auto it = m_QMapDeferPosi.begin(); it != m_QMapDeferPosi.end(); it++)
	{
		//auto &stDeferPosi = it.value();
		if (it->infoLong.iCurrAllAmt > 0)
		{
			m_stFundInfo.dPosiMargin += it->infoLong.dPosi_PL;
		}
		if (it->infoShort.iCurrAllAmt > 0)
		{
			m_stFundInfo.dPosiMargin += it->infoShort.dPosi_PL;
		}
	}

	// added by Jerry Lee, 2013-3-24, ȷ���ͷ������ĸ���ӯ��һ��
	/*
	Rsp1020 rsp1020;
	if(CTranMessage::Handle1020(rsp1020, '1', '1', '0', '0', '0', '0', true) == 0)
	{
	m_stFundInfo.dPosiMargin = atof(rsp1020.r_surplus);
	}
	*/
	//
}

QString CTraderCpMgr::GetInsStateNameFromID(const QString &sInsID)
{
	for (size_t i = 0; i < m_vInstState2.size(); i++)
	{
		if (m_vInstState2.at(i).code_id == sInsID)
		{
			return m_vInstState2.at(i).code_desc;
		}
	}

	return "";
}

int CTraderCpMgr::CommitOrder(const QString &sProdCode, double dPrice, int iAmount, const QString &sExchID)
{
	Rsp4001 rsp;
	int nRet = CTranMessage::Handle4001(rsp,sProdCode, dPrice, iAmount, sExchID,0);

	  //���ӶԱ�����������ж�
	  if (rsp.rsp_code.find("HJ4034") != string::npos)  
	  {
	      nRet = 4034;
	  }

	return nRet;
	return  0;
}

/*
modify by  20130806 �����bAuto���ֶΣ����bAutoΪtrue������ÿ���Զ������ʾ���ڣ����������ֱ�ӵ�����ʾ����
*/
int CTraderCpMgr::CommitOrder(const QString &sProdCode, const QString &csPrice, const QString &csAmount, const QString &sExchID, int orderType,bool bAuto/* = true*/)
{
	// ���ͱ���
	Rsp4001 rsp;
	int iRspID = CTranMessage::Handle4001(rsp, sProdCode, csPrice.toFloat(), csAmount.toInt(), sExchID, orderType, false);

	   // added by Jerry Lee, 2013-4-1, ���ӶԱ�����������ж�
	   string strCode = rsp.rsp_code;
	   if (rsp.rsp_code.find("HJ4034") != string::npos)  
	   {
	       iRspID = 4034;

	       return iRspID;
	   }

	// ������ʾ������������ʾ���ڵ�����ʾ��ǰ�棬���򵯳��Ի�����пհ׵�˲��
	//if((iRspID == 0 && g_Global.m_csSoundAskSus != "") || (iRspID != 0 && g_Global.m_csSoundAskFail != ""))
	//{
	//	QString *pCS = (iRspID == 0) ? &g_Global.m_csSoundAskSus : &g_Global.m_csSoundAskFail;
	//	::PostMessage(m_hMain, WM_PLAY_TIPS_MUSIC, (WPARAM)pCS, 0);
	//	//AfxGetMainWnd()->PostMessage(WM_PLAY_TIPS_MUSIC, (WPARAM)pCS);
	//}

	// �����Ҫ��ʾ���򵯳���ʾ
	if((iRspID == 0 && g_Global.m_bTipsAskSus) || (iRspID != 0 && g_Global.m_bTipsAskFail))
	{
		if( bAuto )
		{
			TipsOrderInfo TipsInfo;
			// ��ȡ��ʾ����
			TipsType eType = (iRspID == 0) ? E_Tips2_Asksus : E_Tips2_AskFail;
			// ��ȡ��ʾ��
			QString sMsg = (iRspID == -1) ? CONSTANT_CONNECT_SERVER_FAIL_TIPS : CHJGlobalFun::str2qstr(rsp.rsp_msg);
			// ��ʼ������ʾ�ṹ
			//TipsInfo.IniData()
			TipsInfo.IniData(eType, CHJGlobalFun::qstr2str( sProdCode), CHJGlobalFun::qstr2str(sExchID), csPrice, csAmount, sMsg, "");
			// ����ʾ���ݼ��ؽ��ڴ�
			int nAddPos = g_TipsManager.Add(TipsInfo);


			QParamEvent *msg = new QParamEvent(WM_SHOW_ORDER_TIPS);
			//msg->setWParam(&nAddPos);
			msg->setInt(nAddPos);
			QApplication::postEvent(m_hMain, msg);

		}
		else
		{
			// ��ȡ��ʾ��
			QString sMsg = (iRspID == -1) ? CONSTANT_CONNECT_SERVER_FAIL_TIPS : CHJGlobalFun::str2qstr(rsp.rsp_msg);

			//kenny  2018-1-22  �����߳��е����Ի��򣬻��жϹ����̣߳�����
			//QMessageBox::information(nullptr, "��ʾ", sMsg , QMessageBox::Ok);
		}
	}

	return iRspID;

	return  0;
}

//�յ��ɽ��ر���Ϣ�󣬽��н�����ʾ
void CTraderCpMgr::ShowMatchTips(const QString &sProdCode, const double &dPrice, const int &iAmount, const QString &sExchID, const QString &sOrderNo)
{
	TipsOrderInfo TipsInfo;
	QString csPrice, csHand;
	csPrice = QString::number(dPrice,'f',2);//Format("%.2f", dPrice);
	csHand = QString::number(iAmount);
	//csHand.Format("%d", iAmount);
	QString  tips = "�ҵ��ɽ�";
	TipsInfo.IniData(E_Tips2_OrderMatch, CHJGlobalFun::qstr2str(sProdCode), CHJGlobalFun::qstr2str(sExchID), csPrice, csHand,tips, sOrderNo);
	int nAddPos = g_TipsManager.Add(TipsInfo);

	QParamEvent * msg = new QParamEvent(WM_SHOW_ORDER_RESULT_TIPS);
	msg->setInt(nAddPos);

	QApplication::postEvent(m_hMain, msg);

}


int CTraderCpMgr::CancelOrder(QString &csOrderNo)
{
	Rsp4061 rsp; //Ӧ������

	int iRspID = CTranMessage::Handle4061( rsp,csOrderNo );

	// ������ʾ������������ʾ���ڵ�����ʾ��ǰ�棬���򵯳��Ի�����пհ׵�˲��
	/*if((iRspID == 0 && g_Global.m_csSoundCancelSus != "") || (iRspID != 0 && g_Global.m_csSoundCancelFail != ""))
	{
		//QString pCS = (iRspID == 0) ? g_Global.m_csSoundCancelSus : g_Global.m_csSoundCancelFail;
		
		TipsOrderInfo TipsInfo;
		// ��ȡ��ʾ����
		TipsType eType = (iRspID == 0) ? E_Tips2_CancelSus : E_Tips2_CancelFail;

		TipsInfo.IniData(eType, csOrderNo);
		// ����ʾ���ݼ��ؽ��ڴ�
		int nAddPos = g_TipsManager.Add(TipsInfo);


		QParamEvent *msg = new QParamEvent(WM_SHOW_ORDER_CANCEL_TIPS);
		msg->setInt(nAddPos);
		QApplication::postEvent(m_hMain, msg);

	}*/

	if((iRspID == 0 && g_Global.m_bTipsCancelSus) || (iRspID != 0 && g_Global.m_bTipsCancelFail))
	{
		TipsOrderInfo TipsInfo;
		TipsType eType = (iRspID == 0) ? E_Tips2_CancelSus : E_Tips2_CancelFail;
		QString sMsg = (iRspID == -2 || iRspID == -1) ? CONSTANT_CONNECT_SERVER_FAIL_TIPS : CHJGlobalFun::str2qstr(rsp.rsp_msg);
		TipsInfo.IniData(eType, csOrderNo);
		int nAddPos = g_TipsManager.Add(TipsInfo);


		QParamEvent *msg = new QParamEvent(WM_SHOW_ORDER_CANCEL_TIPS);
		msg->setInt(nAddPos);
		QApplication::postEvent(m_hMain,msg);


	}

	return iRspID;

}

int CTraderCpMgr::GetDlgHandleFromID(const EDLGID &eDlgID)
{
	QMap<EDLGID, int>::const_iterator it = m_QMapDlgHandle.find(eDlgID);
	if (it != m_QMapDlgHandle.end())
		return it.value();
	else
		return NULL;
}

void CTraderCpMgr::AddDlgHandle(const EDLGID &eDlgID, const int &hDlg)
{
	m_QMapDlgHandle[eDlgID] = hDlg;
}

/*
�ж�
*/
bool CTraderCpMgr::bIsOrderUnMatch(const QString &sLocalOrderNo, bool bErase)
{
	for (list<QString>::iterator it = m_QMapUnMatchOrder.begin(); it != m_QMapUnMatchOrder.end(); it++)
	{
		if ((*it == sLocalOrderNo))
		{
			if (bErase)
			{
				m_QMapUnMatchOrder.erase(it);
			}
			return true;
		}
	}

	return false;
}



bool CTraderCpMgr::InitEx()
{
	// ����ֻ��ʼ��һ��
	static bool bInitSucs = false;

	if (!bInitSucs)
	{
		QString sIP;
		QString sPort;
		// �����֤��ip�Ͷ˿�
		if (GetAuthenticateInfo(sIP, sPort))
		{
			Init();

			if (CCommHandler::Instance()->OpenInterfaceB1C(g_TraderCpMgr.GetIPFromDomain(sIP), sPort) == 0)
			{
				// ��ʼ��·�ɱ���m_tblIfRouterCfg�����е����ü��ص�m_tblIfRouter��QMap���ͣ�����ÿ�����ļ��ض�Ӧ�Ľӿ���
				InitRouterTbl();

				// ������ͷ����
				g_HeaderReq.SetUserID("");
				g_HeaderReq.SetSeqNo(g_SeqNo++);

				g_HeaderReq.SetTermType("03"); //��ʾ��½������03Ϊ�����նˣ�
				g_HeaderReq.SetUserType("2");  //��ʾ�û����ͣ�2Ϊ�ͻ���
				g_HeaderReq.SetMsgFlag("1");   //�����ı�ʶ��δ֪��
				g_HeaderReq.SetMsgType("1");   //���ױ������ͣ�1Ϊ���ף�

				bInitSucs = true;
			}
		}
	}

	return bInitSucs;
}

// ��ȡ��֤��Ҫ��ip�Ͷ˿�
bool CTraderCpMgr::GetAuthenticateInfo(QString &sIP, QString &sPort)
{
	QString buf;
	QString strConfigPath( g_Global.GetSystemIniPath() );

	// ��ȡ��¼IP
	App::GetPriProfileString(strConfigPath, "Info", "LOGIN.ip", sIP);

	// ��ȡ��¼�˿�
	App::GetPriProfileString(strConfigPath, "Info", "LOGIN.port", sPort);

	if( sIP.isEmpty() || sPort.isEmpty() )
		return false;
	else
		return true;
}

void CTraderCpMgr::ClearHistoryInfo(void)
{
	QString csPath(g_Global.GetDataIniPath());

	App::WritePriProfileString(csPath, "Info", "FundInfo", "");
	App::WritePriProfileString(csPath, "Info", "DeferPosiInfo", "");
	App::WritePriProfileString(csPath, "Info", "StoreInfo", "");
	App::WritePriProfileString(csPath, "Info", "ForwardPosiInfo", "");
}

// �ж�һ���û��ڵ�ǰ�������Ƿ�����Ч�Ľ���
bool CTraderCpMgr::HasValidTrade(void)
{
	// �Ƿ��гɽ�
	if (m_QMapSpotMatch.size() > 0 || m_QMapForwardMatch.size() > 0 || m_QMapDeferMatch.size() > 0 || m_QMapDDAMatch.size() > 0)
		return true;

	//// �Ƿ�����Ч�ı���
	if (HasValidOrder(m_QMapSpotOrder) || HasValidOrder(m_QMapForwardOrder) || HasValidOrder(m_QMapDeferOrder)
		|| HasValidOrder(m_QMapDDAOrder) || HasValidOrder(m_QMapMiddleAppOrder))
		return true;

	// �Ƿ��г�����¼
	if (m_QMapTransfer.size() > 0)
		return true;

	return false;
}


void CTraderCpMgr::ClearCusInfo(void)
{
	// ��������ļ���ʷ��Ϣ
	ClearHistoryInfo();

	// ��տͻ��ڴ������Ϣ
	m_QMapDeferPosi.clear();
	m_QMapStoreInfo.clear();
	m_stFundInfo.ClearData();

	// �����Ƿ�����ɽ���ˮ��Ϣ
	int wval = 1;
	int lval = 0;
	// ���͹㲥
	m_mapBdr[E_ONSYSINIT].Broadcast( WM_ON_SYS_INIT, &wval, &lval, TRUE );
}


void CTraderCpMgr::RecordVersionInfo(QString strVersion)
{
	// ���������ļ��İ汾��
	if (strVersion == "")
	{
		strVersion = "1.0.0";
	}
	//::WritePrivateProfileQString("Info", "HJ.ver_num", strVersion, g_Global.GetSystemIniPath());

	// �´β���Ҫ���ز���
	//::WritePrivateProfileQString("Info", "HJ.is_down_para", "0", g_Global.GetSystemIniPath());
}

//#include "IniFilesManager.h"
void CTraderCpMgr::IniQuotationInsID()
{
	QIniFilesManager mgr;
	std::vector<QString> vecUserNames;
	mgr.GetIniValueToVector(g_Global.GetListIniPath("InsID"), "Info", "AllColumnIDs", QUERY_INI_SPLITER, "", vecUserNames );
	for (size_t i = 0; i < vecUserNames.size(); i++)
	{
		QUOTATION qt;
		qt.instID = vecUserNames[i].toStdString();
		m_QMapQuotation[qt.instID] = qt;
	}
}


bool CTraderCpMgr::OpenedBillExists()
{
	for (auto it = m_QMapDeferOrder.begin(); it != m_QMapDeferOrder.end(); it++)
	{
		DeferOrder& dOrder = it.value();

		QString nId = CHJCommon::GetDeferId(dOrder.offSetFlag.c_str(), dOrder.buyOrSell.c_str());

		if (((CONSTANT_EXCH_CODE_DEFER_OPEN_LONG == nId) || (CONSTANT_EXCH_CODE_DEFER_OPEN_SHORT == nId)))
		{
			QString strStatus = dOrder.status.c_str();
			if (strStatus != "c"  && strStatus != "d")
			{
				return true;
			}
		}

	}

	return false;
}

#define UPDATE_INI_NAME ("Update.ini")
// ������������
bool CTraderCpMgr::CallUpdateExe(void) const
{
	// �ж����������Ƿ���ڣ�������ڣ�����
	QString buf;

	App::GetPriProfileString(g_Global.GetSystemPath() + UPDATE_INI_NAME, "Update", "Update1", buf);
	if (buf == 0)
	{
		return false;
	}
	else
	{
		QString csFullName = buf;

		QString csExeName;
		QString csPara;
		int nPos = csFullName.indexOf(" ");
		if (nPos != -1)
		{
			csExeName = csFullName.left(nPos);
			csPara = csFullName.mid(nPos + 1);
		}
		else
		{
			csExeName = csFullName;
		}

		//ShellExecute( NULL, "open", g_Global.GetSystemPath()+csExeName, csPara, NULL, NULL );

		return true;

		/*QString csUpdateExeName = buf;
		BOOL bRet = CHJGlobalFun::RunFileExe( g_Global.GetSystemPath()+csUpdateExeName);
		if( bRet )
		LOG("������������ɹ�");
		else
		LOG("������������ʧ��");
		return bRet;*/
	}
}

#if (defined _VERSION_JSZX) || (defined _VERSION_ZHLHY)
void CTraderCpMgr::SetTransferMode(const ArrayListMsg &alm_menu_info)
{
	for (size_t i = 0; i < alm_menu_info.size(); i++)
	{
		const ArrayListMsg &aMsg = alm_menu_info.GetValue(i);
		QString sMenuID(aMsg.GetQStringEx(0));
		if (sMenuID == MenuIdByAuto)
		{
			g_Global.m_bAutoTransfer = true;
			return;
		}
		else if (sMenuID == MenuIdByHand)
		{
			g_Global.m_bAutoTransfer = false;
			return;
		}
	}
}
#endif


void CTraderCpMgr::SwitchServer()
{
	CCommHandler::Instance()->SwitchToNextServer();
}

bool CTraderCpMgr::AddPrice(QVector<unsigned int> &vPrice, unsigned int dPrice)
{
	if (dPrice > 0)
	{
		vPrice.push_back(dPrice);
		return true;
	}
	return false;
}

void CTraderCpMgr::SetServerList(HashtableMsg &htm_server_list)
{
	QString csPath = g_Global.GetSystemIniPath();
	QString sMode;

	App::GetPriProfileString(csPath, "info", "DirectMode", sMode);
	if (sMode == "1")
	{
		QString sValue;

		App::GetPriProfileString(csPath, "info", "DirectModeInfo", sValue);

		HashtableMsg htm(sValue.toStdString());
		for (size_t mm = 0; mm < htm.size(); mm++)
		{
			map<string, string> QMapValue = htm.GetMap(mm);
			CCommHandler::Instance()->InsertServer(QMapValue);
		}
	}
	else
	{
		// ����������б�
		for (size_t mm = 0; mm < htm_server_list.size(); mm++)
		{
			map<string, string> QMapValue = htm_server_list.GetMap(mm);

			// ���Ϊ���������޸�Ϊip
			QString sID[5] = { "broadcast_ip", "query_ip", "risk_broadcast_ip", "trans_ip", "risk_trans_ip" };
			for (int i = 0; i < 5; i++)
			{
				map<string, string>::iterator it = QMapValue.find(sID[i].toStdString());
				if (it != QMapValue.end())
				{
					// mod by Jerry Lee, 2013-3-27, ����Ҫת��ip
					if (g_Global.m_nProxyType == 0)
					{
						it->second = GetIPFromDomain(it->second.c_str()).toStdString();
					}
				}
			}

			CCommHandler::Instance()->InsertServer(QMapValue);
		}
	}
}

//��������״̬
void CTraderCpMgr::addStrategyConditionOrder(QString && id, strategy_conditionOrder &cond)
{
	mapStrategyConditionOrder[id] = cond;
}

void CTraderCpMgr::runStrategyConditionOrder(QString && id)
{
	mapStrategyStopping.remove(id);
	mapStrategyRunning[id] = mapStrategyConditionOrder[id];
}

void CTraderCpMgr::stopStrategyConditionOrder(QString && id)
{
	mapStrategyRunning.remove(id);
	mapStrategyStopping[id] = mapStrategyConditionOrder[id];
}

void CTraderCpMgr::deleteStrategyConditionOrder(QString && id)
{
	mapStrategyRunning.remove(id);
	mapStrategyStopping.remove(id);
	mapStrategyConditionOrder.remove(id);
}

void CTraderCpMgr::runAllStrategyConditionOrder()
{
	for (auto m : mapStrategyConditionOrder)
	{
		mapStrategyStopping.remove(m.id);
		mapStrategyRunning[m.id] = m;
	}
}


void CTraderCpMgr::resetAccount(QString && str)
{
	UserLogout();

	// ����㲥�����гɽ���ˮ����
	m_QMapSpotMatch.clear();
	m_QMapForwardMatch.clear();
	m_QMapDeferMatch.clear();
	m_QMapDDAMatch.clear();
	// ����㲥�����б�����ˮ����
	m_QMapSpotOrder.clear();
	m_QMapForwardOrder.clear();
	m_QMapDeferOrder.clear();
	m_QMapDDAOrder.clear();
	m_QMapMiddleAppOrder.clear();
	// ������ˮ
	m_QMapDeferOrderCancel.clear(); // ���ڵĳ�����������
	m_QMapOrderCancel.clear();      // ���������ڵĳ���
									// ��¼�ͻ��ĳֲ���Ϣ
	m_QMapDeferPosi.clear();
	// �����Ϣ
	m_QMapStoreInfo.clear();
	// �ʽ���Ϣ
	m_stFundInfo.ClearData();
	// ���ճ������Ϣ
	m_QMapTransfer.clear();
	m_QMapOrderFroze.clear();
	m_arrUnFindLocalOrderNo.clear();

	m_QMapMatchUnFindInfo.clear();

	int nRet = 0;
    //���ݱ�������ȡ�˻���Ϣ�����е�½
	for (int i = 0; i < App::accMgr.size(); i++)
	{
		if (App::accMgr[i].alias == str)
		{
			g_Global.m_strUserID = App::accMgr[i].user; // �û�ID    
			g_Global.m_strPwdMD5 = g_TraderCpMgr.GetEncryptPSW(App::accMgr[i].psw.toStdString().c_str());

			g_Global.m_bShowLastLoginInfo = false;
			nRet = g_TraderCpMgr.UserLogin();
			break;
		}

	}

	if (nRet < 0)
		return;

	
}