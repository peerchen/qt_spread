/*
������ʱ����ɵ������������
�����������
*/
#pragma once

#include "..\Mgr\AlmHtmBase.h"
#include "StDef.h"
#include <QMap>

#define g_CodeTableMgrOld CCodeTableMgrOld::GetInstance()

class CCodeTableMgrOld : public CAlmHtmBase
{
private:
	CCodeTableMgrOld( void );
	virtual ~CCodeTableMgrOld( void) ;

	CCodeTableMgrOld( const CCodeTableMgrOld&) ;            // ��ʵ��.
	CCodeTableMgrOld& operator= ( const CCodeTableMgrOld& ); // ��ʵ��.

public:
	static CCodeTableMgrOld& GetInstance();

	// ��ʼ�������
	bool Initialize( const ArrayListMsg *pCodeTable /*= NULL */ );

private:
	// �ӷ������������
    bool LoadDataFromServer( void );

	// ��HashtableMsg����
	void LoadFromHtm( HashtableMsg &htm );

	// ��ArrayListMsg����
	void LoadFromAlm( const ArrayListMsg &alm );

	// �Ƿ���Ҫ���ֶ�
	bool IsNeed( const string &sValue );

	// ���ô���
	void SetDelegate( void );

	// ���һ�����
	void AddValue( const MyCodeInfo &stCodeValue );

private:
	QVector<MyCodeInfo> *m_vExchCode;   //��������
	QVector<MyCodeInfo> *m_vOffsetFlag; //��ƽ��־
	QVector<MyCodeInfo> *m_vFeeCode;    //���ô���
	QVector<MyCodeInfo> *m_vSubFeeCode; //���ô���
	QVector<MyCodeInfo> *m_vLongShort;  //�ֲַ���

	//list�ֶ�ת��
	QVector<MyCodeInfo> *m_vMarketId;   //�����г�
	QVector<MyCodeInfo> *m_vEntrState;  //ί��״̬
	QVector<MyCodeInfo> *m_vCancelFlag; //������־
	QVector<MyCodeInfo> *m_vTermType;   //��������
	QVector<MyCodeInfo> *m_vAccessWay;  //��������
	QVector<MyCodeInfo> *m_vCheckState; //����״̬
	QVector<MyCodeInfo> *m_vTakeState;  //���״̬
	QVector<MyCodeInfo> *m_vDrawType;   //�������
	QVector<MyCodeInfo> *m_vCertType;   //֤������
	QVector<MyCodeInfo> *m_vAcctState;  //�˻�״̬
	QVector<MyCodeInfo> *m_vInstState2;  //��������Լ״̬
	QVector<MyCodeInfo> *m_vFCOrderState; // ����ǿƽ�����͵�ת��
	QVector<MyCodeInfo> *m_vDeliFlag; // ���ձ�־
	QVector<MyCodeInfo> *m_vPageInfo; // ��ѯ�����ҳ����Ϣ
};
