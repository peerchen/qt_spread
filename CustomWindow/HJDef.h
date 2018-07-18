#ifndef _HJDEF_H
#define _HJDEF_H

#include  <QString>

#define LOG_CONNECT_SERVER_FAIL_TIPS   "���ӷ�����ʧ�ܣ�"

#define CONSTANT_YES								 "1"
#define CONSTANT_NO									 "0"
#define CONSTANT_TIHUO_SUS							"1"
#define CONSTANT_TIHUO_CANCEL_TODAY					"3"
#define CONSTANT_TIHUO_CANCEL_ANOTHER_DAY           "4"

#define CONSTANT_STOP_PL_SER_TIPS "ע�⣺ֹӯֹ�𵥽��������������ɷ�����������\r\n ��׷��ֹ�������λ���ֶν���Ч��"
#define CONSTANT_STOP_PL_CLIENT_TIPS "ע�⣺ֹӯֹ�𵥽������ڱ������ɱ���������"



enum MarketType
{
	e_mk_Spot,
	e_mk_Forward,
	e_mk_Defer,
	e_mk_Others,
};

typedef enum
{
	E_LOgin_Type_NUll = 0,
	E_Login_Type_Trade  = 1, // ����
	E_TYPE3,
	E_TYPE4,
	E_Login_Type_HQ_Trade = 4, // ����ӽ���
} ELoginType;


const QString g_sEmptyStr("");

extern QString GetYesNoName(const QString &sID);

/*
�Ƿ������ڽ��ջ��������ֵĽ��׷�ʽ
*/
extern bool IsDeferSpecial(const QString &sExchTypeID);

extern MarketType GetMarketFromExchType( const QString &sExchTypeID );

extern MarketType GetMarketType( const QString &sMarketID );

extern bool IsDeferInst( const QString &sInst );

#endif