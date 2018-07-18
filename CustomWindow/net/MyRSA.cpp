//#include "StdAfx.h"
#include "MyRSA.h"

#include <openssl/ossl_typ.h>
#include <openssl/pkcs12.h>
#include <openssl/pem.h>

CMyRSA::CMyRSA(void)
{
}

CMyRSA::~CMyRSA(void)
{
}

int CMyRSA::HandleRsaEncrypt( char *&pEncryptBuf, 
							 unsigned int &uiEncryptLen, 
							 const char* pOrgBuf,      // 
							 unsigned int uiOrgLen, // uiOrgLen
							 const QString &csCertFilePath )
{
	BIO *in = NULL;
	EVP_PKEY * pPubKeyPem = 0;
	X509 *x509Pem = NULL;

	if ((in = BIO_new_file (csCertFilePath.toStdString().c_str(), "r")) == 0)
	{
		return -1;
	}

	x509Pem = PEM_read_bio_X509(in, NULL, 0, NULL);
	if (x509Pem == 0)
	{
		return -1;
	}

	pPubKeyPem = X509_get_pubkey(x509Pem);
	if (pPubKeyPem == 0) 
	{
		if (x509Pem) 
		{
			X509_free(x509Pem);
		}
		return -1;
	}
	else if (pPubKeyPem->pkey.rsa == 0)
	{
		if (x509Pem) 
		{
			X509_free(x509Pem);
		}
		return -1;
	}

	const char * pData = pOrgBuf;

	// ����洢���ĵĻ�����
	unsigned int uiTotalSize = (uiOrgLen/100 + 2) * 128;
	pEncryptBuf = new char[uiTotalSize];
	memset(pEncryptBuf, 0, uiTotalSize);

	// ���������洢һ�μ��ܵ���ʱ������
	unsigned int nRsaSize = RSA_size(pPubKeyPem->pkey.rsa); // �����ʱ�������ĳ���
	unsigned char* pEncrpted = new unsigned char[nRsaSize];


	int nInLen = 0;  // ��Ҫ���ܵĶεĳ���
	uiEncryptLen = 0; // ���ܻ��������Ѿ����ܵĳ���
	for (size_t n = 100; n - 100 < uiOrgLen; n += 100)
	{
		// �����μ��ܵ����ĵĳ��ȣ�һ��Ϊ100���������һ�Σ�
		nInLen = uiOrgLen / n == 0 ? uiOrgLen - (n - 100) : 100;

		// ��������ļ��ܵ�pEncrpted������������ü��ܺ��ʵ�ʳ���
		int nTmp = RSA_public_encrypt(nInLen,(const unsigned char*)pData,pEncrpted,pPubKeyPem->pkey.rsa,RSA_PKCS1_PADDING);

		// ���Ƽ��ܺ�����ĵ����ܻ�����
		memcpy(pEncryptBuf + uiEncryptLen, pEncrpted, nTmp);

		// ��ü��ܻ���������һ�μ��ܵ���ʼλ��
		uiEncryptLen += nTmp;

		// ����δ���ܵ����ĵ���ʼλ��
		pData += nInLen;
	}

	if (x509Pem) 
	{
		X509_free(x509Pem);
	}

	delete []pEncrpted;

	return 0;
}
