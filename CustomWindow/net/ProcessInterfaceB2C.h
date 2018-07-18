#ifndef _PROCESS_INTERFACE_B2C_H
#define _PROCESS_INTERFACE_B2C_H

#include "CommApCln.h"
#include "TcpShortCp.h"
#include "ProtocolProcess.h"

using namespace std;

class COMMAPCLIENT_CLASS CProcessInterfaceB2C : public CTcpShortProcess
{
public:
	CProcessInterfaceB2C(void);
	virtual ~CProcessInterfaceB2C(void);
	int Init(CConfig* pCfg);

	//���ͱ����ر�Ĵ��� PreSendHandle���崦������Ǽ���,ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�ʵ�ʷ��͵��ֽ���
	int PreSendHandle(CPacket &sndPacket);
	//���������ر�Ĵ��� SufRecvHandle���崦������ǽ���,��ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�1 
	int SufRecvHandle(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket);

protected:
	//���ඨ��Ļص�����ʵ��
	void GetPacketInfo(PacketInfo & stInfo);//���ĸ�ʽ��Ϣ
private:
	PacketInfo m_stInfo;
	string m_s3DesKey;
	string m_s3DesIV;
	string m_sSessionID;
};
#endif
