#ifndef PREORDERDEF_H
#define PREORDERDEF_H

#include <string>
#include <QString>
#include "osdepend.h"

using namespace std;

typedef enum
{
	PreOrderMsgFlag_Add = 0,   // ���   
	PreOrderMsgFlag_Mdf_State, // �޸�״̬
	PreOrderMsgFlag_Mdf_Con,   // �޸Ĵ�������
	PreOrderMsgFlag_Del,       // ɾ��
	PreOrderMsgFlag_Clear,       // ���
	PreOrderMsgFlag_Mdf_Hand,  // �޸�����
}PreOrderMsgFlag;

typedef enum
{
	E_NoSend = 0, // δ����    
	E_Sended,     // �ѷ���
	E_SendFailed, // ����ʧ�� 
} EPreOrderState;

typedef enum
{
	PreOrderType_Condition = 0, // ����������������ʱ����
	PreOrderType_Loss,      // ֹ��
	PreOrderType_Profit,    // ֹӯ��
	PreOrderType_Hand,  // �ֶ�����
	PreOrderType_AUTO,      // �Զ������������뽻��ʱ�κ���
} EPreOrderType;

/*
����۸��뱨�۵ıȽ����ͣ�����E_Small����������۸�С�ڱ���ʱ����

*/
typedef enum
{
	E_Big_Equal=0,       // ���ڻ����
	E_Small_Equal,     // С�ڻ����
	E_Equal,           // ����
	E_Small,      // С��
	E_Big,             // ����
} ECompareType; 

/*
�����˱���һ��
*/
typedef enum
{
	E_Buy1 = 0, // ��1
	E_Sell1, // ��1
	E_Latest, // ���¼�
}EQTType;

// ֹӯֹ�𵥲�������
class PLParam
{
public:
	const unsigned int *pPrice; // ֹӯֹ�𵥱����۸�ָ��������ֶΣ�����Ϊ���¼ۡ���1�ۻ�����1�ۣ�
	int iAjust;                 // ƫ������۸�ĳ߶�
	bool bLong;                 // �Ƿ���
	string sMatchNo;            // ��ǰֹӯֹ�𵥶�Ӧ�ĳɽ�����

	PLParam( const unsigned int *pPrice2, int iAjust2, bool bLong2, const string &sMatchNo2 ) : pPrice(pPrice2), iAjust(iAjust2), bLong(bLong2), sMatchNo(sMatchNo2) {};

	PLParam()
	{
		pPrice = NULL;
	}
	virtual ~PLParam() {};
};

// ֹ�𵥵Ĳ���
class LossParam : public PLParam
{
public:
	unsigned int uiExtreme; // ��ֵ����ʼ��Ϊ����������ʱ�����¼ۣ��Ըñʶ�ֹ̬�𵥿�ʼ�����¼۵ļ�ֵ����ּ�Ϊ��󣬿ղ���Ϊ��С��
	bool bUseDys;           // ��ǰ��ֵ���õ��Ƿ��Ƕ�̬������
	uint uiStatic;          // ��ֹ̬�𴥷���
	uint uiDys;             // ��ֹ̬�𴥷���

	LossParam( const unsigned int *pPrice2, int iAjust2, bool bLong2, const string &sMatchNo2 ) : PLParam(pPrice2, iAjust2, bLong2, sMatchNo2){};
	LossParam()
	{
		pPrice = NULL;
	}
	~LossParam() {};
};

// Ԥ�񵥽ṹ
struct PreOrderStruct
{
	int iID; // Ԥ��ID
	EPreOrderType  eOrderType;  // Ԥ������
	EPreOrderState eOrderState; // Ԥ��״̬
	string sProdCode; // Ʒ��
	string sExchId;   // ��������
	int iHand;        // ����
	string sTime;     // ¼��ʱ��

	double dPrice;    // �����۸�ֹӯֹ����Ч����Ϊֹӯֹ�𵥱����۸���õ�������ۼӵ�����λ����������Ч

	/*
	����3���ֶζ��������Լ�ֹӯֹ����Ч
	*/
	ECompareType eCompType; // �Ƚϵ�ԭ���ǣ�����۸� VS �Ƚϼ۸�
	EQTType eQTType;        // �������ĸ����ݱȽϣ����¼ۡ���һ����һ��
	double dCmpPrice;       // �����۸�

	/*
	���õ������ֶ����ͣ����¼ۡ�����1�ۣ������ڱ�����
	������ֹӯֹ�𵥲�Ҫ�õ��ֶΣ����������Ժ�Ҫ�õ��������͵����棬����������������
	*/
	EQTType eAskPriceType;

	bool bServer;

	void* wParam;

	PreOrderStruct()
	{
		eOrderState = E_NoSend;
		wParam = NULL;
		bServer = false;
		iID = -1;
	}

	bool IsUserDefPrice()
	{
		if( eOrderType == PreOrderType_Loss || eOrderType == PreOrderType_Profit )
			return true;
		else
			return false;
	}

	PreOrderStruct& operator = (const PreOrderStruct& Other)
	{
		Release();

		Copy(Other);
		
		return *this;
	}

	PreOrderStruct(const PreOrderStruct& Other)
	{
		Copy(Other);
	}

	void Copy( const PreOrderStruct& Other )
	{
		this->iID = Other.iID;
		this->eOrderType = Other.eOrderType;
		this->eOrderState = Other.eOrderState;
		this->sProdCode = Other.sProdCode;
		this->sExchId = Other.sExchId;
		this->dPrice = Other.dPrice;
		this->eAskPriceType = Other.eAskPriceType;
		this->iHand = Other.iHand;
		this->sTime = Other.sTime;
		this->eCompType = Other.eCompType;
		this->eQTType = Other.eQTType;
		this->dCmpPrice = Other.dCmpPrice;
		
		if( eOrderType == PreOrderType_Profit )
		{
			PLParam *pParam = new PLParam();
			*pParam = *((LossParam*)Other.wParam);
			wParam = pParam;
		}
		else if( eOrderType == PreOrderType_Loss )
		{
			LossParam *pParam = new LossParam();
			*pParam = *((LossParam*)Other.wParam);
			wParam = pParam;
		}
		else
		{
			this->wParam = Other.wParam;
		}
	}

	void Release()
	{
		if( wParam != NULL )
		{
			if( eOrderType == PreOrderType_Profit )
			{
				PLParam *pPLParam = (PLParam*)wParam;
				if( pPLParam != NULL )
					delete pPLParam;
			}
			else if( eOrderType == PreOrderType_Loss )
			{
				LossParam *pPLParam = (LossParam*)wParam;
				if( pPLParam != NULL )
					delete pPLParam;
			}

			wParam = NULL;
		}
	}

	~PreOrderStruct()
	{
		Release();
	}
};

// ֹӯֹ�𵥱Ƚϼ۸�����
typedef enum
{
	E_PLMatchPrice, // ÿ�ʿ��ּ�
	E_PLPosiAvg,    // �ֲ־���	
}EPLCmpType;

// ƽ�ֱ���������
typedef enum
{
	e_PLLatestPrice, // ���¼�
	e_BuySellPrice, // ������
}EPLAskPriceType;

// һ��Ʒ�ֵ�ֹӯֹ��Ľṹ
struct PLInfo
{
	//string sInsID;     // ��Լ����
	short iStopProfitAjust; // ֹӯ������λ
	short iStopLossAjust;   // ֹ�������λ
	short iDysAjust;        // ׷��ֹӯֹ�������λ
	//EPLCmpType eCmpType;    // �Ƚϣ��������۸�����
	//EPLAskPriceType eAskPriceType; // ƽ�ֱ����۸�����
	//short iAskPriceAjust;
};

struct InstPLInfo
{
	QString csInsID;
	QString csStopProfitAjust;
	QString csStopLossAjust;
	QString csDysAjust;

	InstPLInfo(){};

	InstPLInfo( const QString&csInsID2, const QString&csStopProfitAjust2, 
		const QString&csStopLossAjust2,const QString&csDysAjust2) :
	    csInsID(csInsID2), csStopProfitAjust(csStopProfitAjust2), 
		csStopLossAjust(csStopLossAjust2),csDysAjust(csDysAjust2){};;
};

#endif
