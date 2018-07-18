/*
* ͨѶ��������
* ���е�ͨѶ�ӿڶ���������д���
*/


#ifndef _COMM_HANDLER_
#define _COMM_HANDLER_

#pragma once

#include "Comm.h"
#include "ConfigImpl.h"
#include <QString>
#include <iostream>
#include "HashtableMsg.h"
#include "TradePacket.h"
#include <map>
#include "..\..\CTPSample\MyCTPQuote.h"

//���ӵ�key����
typedef enum tagEnumKey 
{
    EnumKeyIfB1C,
    EnumKeyIfB2C,
    EnumKeyIfB3C,
    EnumKeyIfB4C,
    EnumKeyIfYC,
    EnumKeyUnknown
} EnumKeyIf;


//�������ӵ���������
const QString gc_sCfgIfYC  = "IFYC";
const QString gc_sCfgIfB1C = "IFB1C";
const QString gc_sCfgIfB2C = "IFB2C";
const QString gc_sCfgIfB3C = "IFB3C";
const QString gc_sCfgIfB4C = "IFB4C";

class CPacketReceiver
{
public:
	virtual void Receive(CPacket &pkt) = 0;
};



// ͨѶ�ӿڴ�����
class CCommHandler : public CProtocolCpMgr
{
public:
    static CCommHandler* Instance();

	// ��ȡ���÷������ĸ���
	int GetServerCount();

protected:
    CCommHandler(void);
    ~CCommHandler(void);

public:
    QString GetLocalIP();        //��ȡ����ip��ַ

    int OnAccept(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, 
        const string& sPeerIp, int nPeerPort);
	int OnConnect(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort,
        const string& sPeerIp, int nPeerPort,int nFlag);
    int OnLogin( const unsigned long& ulKey,const string& sLocalIp, int nLocalPort,
        const string& sPeerIp, int nPeerPort,int nFlag);
	int OnClose(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort,
        const string& sPeerIp, int nPeerPort);
 
    //int OnLogout
    int Forward(CPacket &GessPacket,const unsigned long& ulKey);

    int Init(const QString& strPath);
    void Finish();

    int OpenInterfaceB1C(const QString& szIP, const QString& szPort);
    int OpenInterfaceB2C();
    int OpenInterfaceB3C();
    int OpenInterfaceB4C();
    int OpenInterfaceYC();
	// ֧�ֶ��������
	int OpenInterfaceYCEx();

	CConnectPointSync* FindRoute(QString& sCmdID);

    void ClearSession();
    QString GetSessionID();

    // ���Ĺ㲥����
    void Subscribe(CPacketReceiver *pPacketReceiver);

    // ȡ���㲥���Ķ���
    void Unsubscribe(CPacketReceiver *pPacketReceiver);

    // ����һ����������ַ
    void InsertServer(const map<string,string>& server);

	CConnectPointAsyn*		m_pCpInterfaceYC;		//ͨѶ�ӿڻ��㲥Y�ӿ�
  	CConnectPointSync*		m_pCpInterfaceB1C;		//��֤�ӿ�
	CConnectPointSync*		m_pCpInterfaceB2C;		//���׽ӿ�
	CConnectPointSync*		m_pCpInterfaceB2CVip;	//����ר��ͨ��
	CConnectPointSync*		m_pCpInterfaceB3C;		//��ѯ�ӿ�
	CConnectPointSync*		m_pCpInterfaceB4C;		//��ؽӿ�

   // CConnectPointSync*		m_pCpInterfaceB4C;		//��ؽӿ�

    int                     m_nCurServerPos;
    HashtableMsg            m_mapServerGroup;

public:
	// �����һ����������λ��
	bool GetNextServerPos( int &nCurPos );

	// ��ʱ����
	void OpenInterface( EnumKeyIf eKey );

	// �����ӿڹ��õĵ��ú���
	void SetInterface(CConnectPointSync* &pInterface, CConfig* &pCfg, int nServerPos, const QString &sIpName, const QString &sIpPort );

	//
	int SendPacket(CConnectPointSync **pCp, CTradePacket *oPktReq, CTradePacket *oPktRsp, unsigned int uiTimeout );

	// ����ǰ�ӿ����ӵ���һ��������
	void ToNextServer(CConnectPointSync **pCp );


	// ���ݽӿ�ָ���ȡ��Ӧ�Ľӿ�����
	EnumKeyIf GetEnumKey(CConnectPointSync *pCp );

	// �л�����һ��������
	void SwitchToNextServer();

	CConnectPointSync* GetInterfaceVip();

	// ��¼��������Ϣ
	void LogServerInfo();

public:
	int m_nB1CPos;
	int m_nB2CPos;
	int m_nB3CPos;
	int m_nB4CPos;
	

private:
	//void SetProxy(CConnector3* pInterface);
	void SetProxy(CConnectPointSync* pInterface);
protected:
	// ��ȡ��������Ϣ
	map<string, string> GetServerInfo( int nPos );

	// ��ȡ��ǰ��������Ϣ
	map<string, string> GetCurServerInfo();

	// ��ȡ��һ����������λ��
	int GetNextServerPos();

	// ���÷�������λ��
	void SetServerPos( int nPos );

	// ����ǰ���ж������л�����ǰ������
	int SwitchToCurIP();

private:
    QString                  m_strSessionID;
    QString                  m_strSessionKey;
    CConfigImpl*		    m_pConfig;

    typedef vector<CPacketReceiver*> VPKTRECEIVER;
    VPKTRECEIVER            m_vPketReceiver;

    static CCommHandler* s_pCommHandler;
};

#endif