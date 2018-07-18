//Э������ ������ 
#ifndef _PROCESS_INTERFACE_YC_H
#define _PROCESS_INTERFACE_YC_H

#include "CommApCln.h"
#include "ProtocolProcess.h"
#include "BroadcastPacket.h"
//#include "MyRsaPfx.h"

using namespace std;

class COMMAPCLIENT_CLASS CProcessInterfaceYC : public CTcpAppProcessClient
{
public:
	CProcessInterfaceYC(void);
	~CProcessInterfaceYC(void);

	typedef struct tagGessPktInfo
	{
		unsigned long ulIdleInterval;		//����ʱ��������Hello���ʱ�䣬Ҳ����·�ϵ������ʱ��
		unsigned long ulIntervalReSend;		//��Ӧ����ؼ����
		unsigned long ulHelloReSend;		//��Ӧ����ط������Ĵ���
		bool blNeedLogin;					//�Ƿ���Ҫ��¼

		std::string	node_type;
		std::string	node_id;
		std::string	node_name;
		std::string	host_id;
		std::string	sUserName;				//���ͻ�ʱ�����˵�¼�û���
		std::string	sPassword;				//���ͻ�ʱ�����˵�¼����

		std::string	term_type;	//
		std::string	user_key;
		std::string	user_type;
		std::string	user_id;
		std::string	user_pwd;
		std::string	branch_id;
		std::string	again_flag;
	} GessPktInfo,*PGessPktInfo;

	int Init(CConfig * pCfg);
	int SendPacket(CPacket & packet);
	int OnSend(int nSize);

	virtual int OnConnect();		// ���ͻ������ӳɹ���ص�
	virtual void OnClose();	        // �Ͽ�����ʱ����
	int GetNmKey(string& sKey);

	void LoginProxy();

	std::string m_sTargetIP;
	int m_nTargetPort;
	int m_nProxyType;
	std::string m_sProxyHost;
	int m_nProxyPort;
	std::string m_sProxyUser;
	std::string m_sProxyPassword;
	BOOL m_bUseLogon;

protected:
	//���ඨ��Ļص�����ʵ��
	virtual int OnPacket(char * pData, size_t nSize);
	virtual void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
	int HandleTimeout(unsigned long& ulTmSpan);

	virtual bool IsLogin() {return m_blIsLogin;} //��¼״̬

	//Э�鶨��Ľ�������
	virtual int SendHello();
	virtual int OnHello(CBroadcastPacket & GessPacket);
	virtual int SendLogin();
    virtual int OnRspLogin(CBroadcastPacket & GessPacket);
private:
	static GessPktInfo m_GessPktInfo;
	static bool	m_blGessPktInfoInited;
	bool		m_blIsLogin;	//��¼״̬
	
	CConfig *	m_pCfg;
	//std::deque<CBroadcastPacket> m_qSend;
	CGessMutex m_csYC;

	unsigned long m_uiCountNoAlive;			//��ʱ�������Ĵ���
	unsigned long m_uiCountSended;			//��Ӧ����ѷ�����������
};

class CBase64CodingEx
{
public:

	// Construction

	CBase64CodingEx();
	virtual ~CBase64CodingEx();

	virtual BOOL Encode(const string &src, string &des); 
};

#endif