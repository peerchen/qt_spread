#include "TradePacket.h"
#include "ProcessInterfaceB4C.h"
#include "Logger.h"
#include "Gess.h"
#include "TraderCpMgr.h"

#include "zlib.h"

#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/pkcs12.h>
#include <openssl/ossl_typ.h>
#include <cassert>
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
CProcessInterfaceB4C::CProcessInterfaceB4C(void)
{
	m_s3DesKey = "240262447423713749922240";
	m_s3DesIV = "12345678";
	m_sSessionID = "0012345678";
	
	m_stInfo.eLengthType = ltCharactersDec;
	m_stInfo.nLengthPos = 0;
	m_stInfo.nLengthBytes = 8;
	m_stInfo.blLenIncludeHeader = false;
	m_stInfo.nFixHeadLen = m_stInfo.nLengthPos + m_stInfo.nLengthBytes;
}

CProcessInterfaceB4C::~CProcessInterfaceB4C(void)
{
}

void CProcessInterfaceB4C::GetPacketInfo(PacketInfo & stInfo)
{
	stInfo = m_stInfo;
}

int CProcessInterfaceB4C::Init(CConfig* pCfg)
{
	CTcpShortProcess::Init(pCfg);

	return 0;
}

//���ͱ����ر�Ĵ��� PreSendHandle���崦������Ǽ���,ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�ʵ�ʷ��͵��ֽ���
int CProcessInterfaceB4C::PreSendHandle(CPacket &sndPacket)
{
	m_sSessionID = "1100002894"; //

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
	

	//return 0;
}

//���������ر�Ĵ��� SufRecvHandle���崦������ǽ���,��ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�1 
int CProcessInterfaceB4C::SufRecvHandle(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket)
{
	if (m_stInfo.nLengthBytes + 1 > ulLen)
		return -1;

	char cFlag = *(pRecvBuf + m_stInfo.nLengthBytes);
	if (cFlag == 0x01)
	{
		return Unzip(pRecvBuf,ulLen,rcvPacket);
	}
	else if (cFlag == 0x02 || cFlag == 0x03)
	{
		return Decrypt(pRecvBuf,ulLen,rcvPacket,cFlag);
	}
	else
	{
		return 0;
	}

	//return 0;
}

//��ѹ��
int CProcessInterfaceB4C::Unzip(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket)
{
	int nFlagLen = 1;
	int nFlag = static_cast<int>(*(pRecvBuf + m_stInfo.nLengthBytes + nFlagLen));
	int nHeadLen = m_stInfo.nLengthBytes + nFlagLen;

	char *pPlainBuff = new char[1024*128];	
	z_stream stream;
	stream.zalloc = 0;
	stream.zfree = 0;
	stream.opaque = 0;
	stream.avail_in = ulLen - nHeadLen;	
	stream.next_in = (Bytef*)(pRecvBuf + nHeadLen);

	int nRtnZip = 0;
	if (Z_OK != inflateInit2(&stream, 16 + MAX_WBITS))
	{
		return -1;
	}

	stream.avail_out = 1024*128;
	stream.next_out = (Bytef*)pPlainBuff;
	do
	{
		nRtnZip = inflate(&stream,Z_NO_FLUSH);
		if (Z_OK != nRtnZip && Z_STREAM_END != nRtnZip)
		{
			return -1;
		}
	} while (false);//nRtnZip != Z_STREAM_END);
	inflateEnd(&stream);

	*(pPlainBuff+21) = '2';

	rcvPacket.Decode(pPlainBuff,stream.total_out);
	return 1;
}

int CProcessInterfaceB4C::Decrypt(char* pRecvBuf, unsigned int uiLen, CPacket &rcvPacket, char cMode)
{
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);

	if (cMode == 0x02)
	{
		string sKey = "240262447423713749922240";
		EVP_DecryptInit_ex(&ctx, EVP_des_ede3_cbc(), NULL, (const unsigned char*)sKey.c_str(), (const unsigned char*)m_s3DesIV.c_str());
	}
	else
	{
		EVP_DecryptInit_ex(&ctx, EVP_des_ede3_cbc(), NULL, (const unsigned char*)m_s3DesKey.c_str(), (const unsigned char*)m_s3DesIV.c_str());
	}

	unsigned int uiHeadLen = m_stInfo.nLengthBytes + 1 + m_sSessionID.length();
	const char* pPktData = pRecvBuf + uiHeadLen;

	unsigned char* pDecrypted = new unsigned char[uiLen - uiHeadLen + 128];
	int nDecryptedLen = 0;
	int nRtn = 0;
	do
	{
		nRtn = EVP_DecryptUpdate(&ctx,pDecrypted,&nDecryptedLen,(const unsigned char*)pPktData,uiLen - uiHeadLen);
	} while(false);

	int nTmpLen = 0;
	nRtn = EVP_DecryptFinal_ex(&ctx, pDecrypted + nDecryptedLen, &nTmpLen);
	nDecryptedLen += nTmpLen;

	// ������ر����и�λ���ϵ�ֵΪ'1'�����⣨1��ʾ�����ģ�2��ʾ��Ӧ���ģ�
	*(pDecrypted+21) = '2';

	rcvPacket.Decode((const char*)pDecrypted,nDecryptedLen);
	return 1;
}