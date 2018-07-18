#ifndef _STDEF_H
#define _STDEF_H


#include <QString>
#include <list>
#include <QRunnable>
#include "BroadcastPacketAndStruct.h"
#include <QMutex>
#include <QWaitCondition>

#include <thread>
#include <functional>
#include <mutex>

//#include<iostream>
//#include<stack>
//#include<map>
//#include<set>
//#include<functional>
//#include<string>


using namespace std;

struct VarietyInfo
{
	QString       variety_id           ; // ����Ʒ�ִ���    
	QString       name                 ; // ����Ʒ��ȫ��            
	QString       abbr                 ; // ���                    
	QString       variety_type         ; // Ʒ�����    
	double        min_pickup           ; // ��С�������        
	double        pickup_base          ; // �������
	QString       weight_unit          ; // ������λ        
	QString       destroy_flag         ; // ע����־ 
};

struct MyCodeInfo
{
	QString       code_type            ; //�������    
	QString       code_id              ; //������    
	QString       code_desc            ; //��������  

	MyCodeInfo(){}

	MyCodeInfo( const QString &sCode_type, const QString &sCode_id,  const QString &sCode_desc) : code_type(sCode_type),code_id(sCode_id),code_desc(sCode_desc){}
};

//
struct ProdCodeInfo
{
	QString       prod_code            ; //��Լ����    
	QString       prod_name            ; //��Լ����    
	QString       variety_type         ; //Ʒ�����    
	QString       variety_id           ; //Ʒ�ִ���    
	double       tick                 ; //��С�䶯��λ    
	double       upper_limit_value    ; //��ͣ����    
	double       lower_limit_value    ; //��ͣ����    
	QString       active_flag          ; //��Ծ��־    
	QString       exch_unit            ; //���׵�λ    
	double       measure_unit         ; //������λ    
	QString       market_id            ; //�����г�   
};

struct StoreInfo
{
	int iAllAmt;
	int iUseFulAmt;
	int iCanGetAmt;
	int iTodayIn;
	int iTodayOut;
	int iExchFreeze;
	int iTihuoFreeze;
	int iUnitCost;

	StoreInfo()
	{
		iAllAmt = 0;
		iUseFulAmt = 0;
		iCanGetAmt = 0;
		iTodayIn = 0;
		iTodayOut = 0;
		iExchFreeze = 0;
		iTihuoFreeze = 0;
		iUnitCost = 0;
	}
};

struct DeferMatchSimple
{
	QString sLocalOrderNo;
	double dPosiMoney;
	double dPrice;
	int iHand; // ʣ�������
	int iTotalHand; // �ܵ����������ɽ�������

	DeferMatchSimple()
	{
		dPosiMoney = 0.00;
		iTotalHand = 1;
	}
};

typedef list<DeferMatchSimple> LISTDeferMatch;

struct DeferPosiInfo
{
	int iCurrAllAmt;     // �ֲܳ�
	int iYesAmt;         // ���
	int iTodayAmt;       // ���
	int iUsefulAmt;      // ���ò�

	double fYesAvgPosPrice; // ���ճֲ־���

	double dAvgPosPrice;     // �ܵĳֲ־���
	double dAvgOpenPosPrice; // �ܵĿ��־���
	double dPosi_PL;         // �ֲ�ӯ��
	double dTotalFare;       // �ֱֲ�֤��

    double dSvrAvgPosPrice;  // ����˳ֲ־���
    double dSvrAvgOpenPosPrice; // ����˿��־���

	LISTDeferMatch listMatch; // �ɽ��б�

	double dYesPosiMoney;
	int iYesOrgAmt;
	double dYesAvgOpenPosPrice; // ���տ��־���

	DeferPosiInfo()
	{
		iCurrAllAmt = 0;
		iYesAmt = 0;
		iTodayAmt = 0;
		iUsefulAmt = 0;

		fYesAvgPosPrice = 0.00;
		dAvgOpenPosPrice = 0.00;
		dAvgPosPrice = 0.00;
		dPosi_PL = 0.00;
		dTotalFare = 0.00;

		iYesOrgAmt = 0;
		dYesPosiMoney = 0.00;
	}
};

struct DeferPosi
{
	QString sProdCode;
	unsigned int uiLastPrice; // ��һ����������ӯ���ļ۸�
	double dUnite; // 

	DeferPosiInfo infoLong;//��
	DeferPosiInfo infoShort;//��

	DeferPosi()
	{	
		uiLastPrice = 0;
		dUnite = 0.00;
	}
};

// ����ƽ���������
struct PCSSPara 
{
	QString csProdCode;
	QString sBS;
	QString csPrice;
	QString csHand;
};

namespace AutoMode
{

}
struct  strategy_obj
{
	QString prodID;
	QString market;//��QH��,"HJ"
	int     direction;//0����գ�1�����
	int     flag;//0: -  ;  1:  +
	int     rate;//���
	QUOTATION quote;
};
//����-������
struct  strategy_conditionOrder
{
	QString  id;
	QString  flag;//"0":���Σ�"1":���
	QString  name;//������Լ����
	QString  status;//����״̬
	QString  direction;//��������
	double   price;
	double   volume;
	double   positionPrice;
	double   positionColume;
	double   gainPrice;
	double   lossPrice;
	double   avgPrice;
	double   profitloss;
	QString  stop;   //ֹͣ��ʽ"0"���ֹ�����1�����ֶ�
	QString  proInfo;//�����Ϣ
	int      period; //��Ͻ׶�
	QString  express;//�۸�ʽ��������ʽ  ��:T1-T2
	strategy_obj  obj[2];//0:T1��Լ   ��  1��t2��Լ
	strategy_conditionOrder operator = (const strategy_conditionOrder& sCondOrder)
	{
		this->id = sCondOrder.id;
		this->flag = sCondOrder.flag;//"0":���Σ�"1":���
		this->name = sCondOrder.name;//������Լ����
		this->status = sCondOrder.status;//����״̬
		this->direction = sCondOrder.direction;//��������
		this->price = sCondOrder.price;
		this->volume = sCondOrder.volume;
		this->positionPrice = sCondOrder.positionPrice;
		this->positionColume = sCondOrder.positionColume;
		this->gainPrice = sCondOrder.gainPrice;
		this->lossPrice = sCondOrder.lossPrice;
		this->avgPrice = sCondOrder.avgPrice;
		this->profitloss = sCondOrder.profitloss;
		this->stop = sCondOrder.stop;   //ֹͣ��ʽ"0"���ֹ�����1�����ֶ�
		this->proInfo = sCondOrder.proInfo;//�����Ϣ
		this->period = sCondOrder.period; //��Ͻ׶�

		for (int i = 0; i < 2; i++)
		{
			obj[i].direction = sCondOrder.obj[i].direction;
			obj[i].flag = sCondOrder.obj[i].flag;
			obj[i].prodID = sCondOrder.obj[i].prodID;
			obj[i].rate = sCondOrder.obj[i].rate;
			obj[i].quote.m_uiLast = sCondOrder.obj[i].quote.m_uiLast;
			obj[i].quote.m_Bid[0].m_uiPrice = sCondOrder.obj[i].quote.m_Bid[0].m_uiPrice;
			obj[i].quote.m_Ask[0].m_uiPrice = sCondOrder.obj[i].quote.m_Ask[0].m_uiPrice;
		}
		

		return  *this;
	}
};









#endif