#ifndef _DEF_H
#define _DEF_H

enum EReqType
{
	e_ReqType_FundPosiStore,
	e_ReqType_CustomInfo, //
};

// ��ʾ������
enum ETipsShowType
{
	e_TipsShowType_always,
	e_TipsShowType_Suc,
	e_TipsShowType_Fail,
	e_TipsShowType_no,
};

// ��������
enum BSFLAG
{
	BS_UKNOWN = 0,
	BS_BUY ,
	BS_SELL,
};

// ��ƽ
enum KPFLAG
{
	KPF_UKNOWN = 0,  // δ֪
	KPF_USELESS,     // ��ƽû�����ã����ֻ�
	KPF_KAI,         // ����
	KPF_PING,        // ƽ��
	KPF_PT,          // ƽ��
	KPF_PY,          // ƽ��
	KPF_FP,          // ǿƽ
	KPF_DDA,         // ����
	KPF_MA,          // ������
};

typedef enum
{
	E_Tips2_Asksus,
	E_Tips2_AskFail,
	E_Tips2_OrderMatch,
	E_Tips2_CancelSus,
	E_Tips2_CancelFail,
	E_Tips2_CreatePreOrder,
} TipsType;


#endif