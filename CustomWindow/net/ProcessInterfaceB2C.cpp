
#include "TradePacket.h"
#include "ProcessInterfaceB2C.h"
#include "Logger.h"
#include "Gess.h"

#include <openssl/ossl_typ.h>
#include <openssl/evp.h>

#include "SufRecvHandler.h"

/******************************************************************************
��������:Э�鱨�Ĵ���ص�����,��ȡЭ�鶨��ı��ĸ�ʽ��Ϣ
���ú���:�������ص�
�������:PacketInfo & stInfo ���ĸ�ʽ��Ϣ
        eLengthType �����ֶ����� ����/10�����ַ���/16�����ַ���
		nLengthBytes ��Ϣ�������ֶεĳ���,Ϊ����ʱֻ֧�� 1 2 4�ֽ�
		nLengthPos �����ֶ���ʼλ��
		blLenIncludeHeader �����Ƿ񺬱���ͷ
		nFixHeadLen  �������ֶ�ָʾ�ĳ�����,���Ĺ̶����ֳ���
������  :��ΰ
��������:2008.07.22
�޸ļ�¼:
******************************************************************************/
CProcessInterfaceB2C::CProcessInterfaceB2C(void)
{
	m_s3DesKey = "240262447423713749922240";
	m_s3DesIV = "12345678";
	m_sSessionID = "12345678";

	m_stInfo.eLengthType = ltCharactersDec;
	m_stInfo.nLengthPos = 0;
	m_stInfo.nLengthBytes = 8;
	m_stInfo.blLenIncludeHeader = false;
	m_stInfo.nFixHeadLen = m_stInfo.nLengthPos + m_stInfo.nLengthBytes;
}

CProcessInterfaceB2C::~CProcessInterfaceB2C(void)
{
}

void CProcessInterfaceB2C::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo = m_stInfo;
	//stInfo.eLengthType = ltCharactersDec;
	//stInfo.nLengthPos = 0;
	//stInfo.nLengthBytes = 8;
	//stInfo.blLenIncludeHeader = false;
	//stInfo.nFixHeadLen = stInfo.nLengthPos + stInfo.nLengthBytes;
}

int CProcessInterfaceB2C::Init(CConfig* pCfg)
{
	CTcpShortProcess::Init(pCfg);

	if (0 == pCfg)
		return 0;

	string sKey = "3DesKey";
	//pCfg->GetProperty(sKey, m_s3DesKey);

	//sKey = "3DesIV";
	//pCfg->GetProperty(sKey, m_s3DesIV);

	sKey = "SessionID";
	pCfg->GetProperty(sKey, m_sSessionID);

	return 0;
}

//���ͱ����ر�Ĵ��� PreSendHandle���崦������Ǽ���,ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�ʵ�ʷ��͵��ֽ���
int CProcessInterfaceB2C::PreSendHandle(CPacket &sndPacket)
{
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_des_ede3_cbc(), NULL, (const unsigned char*)m_s3DesKey.c_str(), (const unsigned char*)m_s3DesIV.c_str());

	unsigned int uiLen = 0;
	const char* pPktData = sndPacket.Encode(uiLen);

	unsigned int uiHeadLen = m_stInfo.nLengthBytes + 1 + m_sSessionID.length();
	unsigned char* pEccrypted = new unsigned char[uiHeadLen + uiLen + 128];
	int nEncryptedLen = 0;
	int nRtn = 0;
	do
	{
		nRtn = EVP_EncryptUpdate(&ctx,pEccrypted + uiHeadLen,&nEncryptedLen,(const unsigned char*)pPktData,uiLen);
	} while(false);
	
	int nTmpLen = 0;
	nRtn = EVP_EncryptFinal_ex(&ctx, pEccrypted + uiHeadLen + nEncryptedLen, &nTmpLen);
	nEncryptedLen += nTmpLen;
	
	char szHeader[128] = {0};
	sprintf(szHeader,"%08d%d%s", 1 + m_sSessionID.length() + nEncryptedLen,0x02,m_sSessionID.c_str());
	szHeader[8] = 0x02;

	memcpy(pEccrypted,szHeader,uiHeadLen); 	
	int nSendLen = SendData((const char*)pEccrypted,nEncryptedLen + uiHeadLen);
	if (nSendLen < 0)
	{
		nSendLen = -1;
	}
	else if (nSendLen == 0)
	{
		nSendLen = 1;
	}

	delete []pEccrypted;
	return nSendLen;
}

//���������ر�Ĵ��� SufRecvHandle���崦������ǽ���,��ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�1 
int CProcessInterfaceB2C::SufRecvHandle(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket)
{
	return g_SufRecvHandler.SufRecvHandle(pRecvBuf,ulLen,rcvPacket);
}