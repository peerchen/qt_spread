#pragma once

#define g_SufRecvHandler CSufRecvHandler::GetInstance()

class CPacket;
#include <string>
using namespace std;

class CSufRecvHandler
{
private:
	CSufRecvHandler( void );
	virtual ~CSufRecvHandler( void) ;

	CSufRecvHandler( const CSufRecvHandler&) ;            // ��ʵ��.
	CSufRecvHandler& operator= ( const CSufRecvHandler& ); // ��ʵ��.

public:
	static CSufRecvHandler& GetInstance();

	// ���������ر�Ĵ��� SufRecvHandle���崦������ǽ���,��ѹ��, �������κδ����򷵻�0,��������-1,���򷵻�1 
	int SufRecvHandle(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket);

private:
    // ��ѹ��
	int Unzip(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket);

	// 3DES����
	int Decrypt(char* pRecvBuf, unsigned int ulLen, CPacket &rcvPacket, char cMode);

	// ��ȡ�̶�3DESKey
	string GetFix3DESKey();

	// ��ȡ��̬3DESKey
	string GetDys3DESKey();

	// ��ȡ����
	string Get3DESIV();

	string GetSessionID();

private:
	int        m_nLengthBytes;
	int        m_nMaxZipPercent; // ���ѹ������

	string m_sFix3DESKey;
	string m_sDys3DESKey;
	string m_s3DESIV;
};
