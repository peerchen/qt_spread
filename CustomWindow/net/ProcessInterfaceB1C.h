#ifndef _PROCESS_INTERFACE_B1C_H
#define _PROCESS_INTERFACE_B1C_H

#include "CommApCln.h"
#include "TcpShortCp.h"
#include "ProtocolProcess.h"

using namespace std;

class COMMAPCLIENT_CLASS CProcessInterfaceB1C : public CTcpShortProcess
{
public:
	CProcessInterfaceB1C(void);
	virtual ~CProcessInterfaceB1C(void);
	int Init(CConfig* pCfg);

	//���ͱ����ر�Ĵ��� PreSendHandle���崦������Ǽ���,ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�ʵ�ʷ��͵��ֽ���
	int PreSendHandle(CPacket &sndPacket);
	//���������ر�Ĵ��� SufRecvHandle���崦������ǽ���,��ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�1 
	int SufRecvHandle(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket);
	//QString GetSystemPath();
protected:
	//���ඨ��Ļص�����ʵ��
	void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
private:
	PacketInfo m_stInfo;
	string m_sPriKeyPath;
	string m_sPubKeyPath;
	string m_sPriKeyPwd;
};
#endif
