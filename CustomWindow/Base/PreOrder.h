//#ifndef _PREORDER_MGR_H
//#define _PREORDER_MGR_H

#pragma once

#include <vector>
#include <QMutex>

//#include "Task.h"
#include "PreOrder/PreOrderDef.h"


namespace PreOrderBusiness
{
	// 根据预埋单类型ID获取其类型名称
	QString GetOrderTypeName( const PreOrderStruct &stPreOrder );

	// 获取报单价格文字
	QString GetAskPrice( const PreOrderStruct &stPreOrder );

	// 根据行情价格类型ID获取名称
	QString GetPriceTypeName( EQTType eQTType );

	// 获取触发条件文字
	QString GetTriConditionName( const PreOrderStruct &stPreOrder );

	// 根据比较类型ID获取比较类型名称
	QString GetCompareTypeName(ECompareType eCmpType);

	QString GetPreOrderTips( const PreOrderStruct &stPreOrder );

	QString GetPreOrderLog( const PreOrderStruct &stPreOrder );

	QString GetRelateMatchNo( const PreOrderStruct &stPreOrder );
}

class CPreOrderMgr
{
public:
	CPreOrderMgr(void);
public:
	~CPreOrderMgr(void);

	// 添加一笔预埋单
	int Add(PreOrderStruct &stPreOrder);

	// 添加一笔预埋单
	int AddEx( const PreOrderStruct &stPreOrder );

	// 根据预埋单ID删除预埋单
	bool Erase(int iOrderID);

	// 生成一笔预埋单报单
	bool CreatePreOrder( int iOrderID );

protected:
	int m_iPreOrderID;                   // 预埋单ID，递增，用来标识预埋单
	vector<PreOrderStruct> m_vPreOrders; // 存储预埋单
	//CGessMutex	 m_csMutex;
	//CRITICAL_SECTION m_criticalSection; // 临界区
	QMutex  m_criticalSection;
};

class CPreOrder
{
public:
	CPreOrder(void);
public:
	~CPreOrder(void);

	// 添加一笔预埋单
	int Add(PreOrderStruct &stPreOrder);

	// 根据预埋单ID删除预埋单
	bool Erase(int iOrderID);

	bool bRun;
public:
	// 根据预埋单类型ID获取其类型名称
	QString GetOrderTypeName(EPreOrderType eOrderTypeID, bool bServer = false );

	// 根据行情价格类型ID获取名称
	QString GetPriceTypeName(EQTType eQTType);

	// 根据比较类型ID获取比较类型名称
	QString GetCompareTypeName(ECompareType eCmpType);

	// 根据预埋单状态ID获取状态名称
	QString GetOrderStateName(EPreOrderState eOrderStateID);

	// 获得触发条件列的显示文字
	QString GetTriConditionName(const PreOrderStruct &stPreOrder);

	QString GetTriConditionNameEx(const PreOrderStruct &stPreOrder);

public:
	// 清除内存中已发送的预埋单，如果有删除的记录则返回true，如果没有删除则返回false
	bool ClearSended();

	// 复制一笔预埋单
	void CopyOrder( PreOrderStruct &stOrder, const PreOrderStruct &stOrgOrder );
    
    // 根据预埋单ID获得该笔单的信息，没有找到则返回false，找到则返回true
	bool GetOrderByID(int iPos, PreOrderStruct &stOrder);

	// 将ID为iOrderID的报单发送
	int CommitAsk(int iOrderID); //

	// 设置ID为iOrderID的预埋单的状态，找到则返回true，没找到则返回fale
	bool SetOrderState(int iOrderID, EPreOrderState eState);

	// 接受到一笔延期行情后调用的函数，处理止损，用来更新触发价格
	void HandleRecQuotation( const string &sInsID, unsigned int uiLast );

	// 处理用户平仓时减去预埋单相应仓位，暂时废弃
	void HandleReceiveCovPosi( const string &sInsID, const string &sExchID, int iHand );

	// 删除相关的止损报单，用于一笔止损止损单后，删除掉与它由同一成交单生成的止盈止损单
	void DelRelativeOrder( const PreOrderStruct &stOrder );

	// 是否是止盈止损单
	bool IsStopPLOrder( EPreOrderType eOrderType );

	inline void SendMessage( int iOrderID, PreOrderMsgFlag iType );
 
    // 获取要发送的报单的ID
	void GetSendOrders( vector<int> &vSendOrders );
	inline ECompareType ComparePrice(double dAsk, double dQT);

	void ClearPreOrder();

	// 判断当前是否存在未发送的预埋单
	bool HasUnSendOrder();

	void CommitAskAll();//线程函数   kenny   2018-1-8
private:
	typedef vector<PreOrderStruct>::iterator IT; 
	IT EraseOrder( const IT &it );

	// 获得一笔相关联的单
	IT GetRelativeOrder( IT itCompare );

	// 预埋单ID，递增，用来标识预埋单
	int m_iPreOrderID; 

	// 存储预埋单
	vector<PreOrderStruct> m_vPreOrders;

	// 临界区
	//CRITICAL_SECTION m_criticalSection;
	QMutex m_criticalSection;

// 待定
public:
	// 获得当前预埋单的个数
	int GetOrderCount();

	// 根据位置获得预埋单信息，如果该位置上的数据没有被删除，则返回true，否则返回false
	bool GetOrderByPos(size_t iPos, PreOrderStruct &stOrder);
};


//////////////////////////////////////////////////////////////////////////
/*class CAutoSendThread: public CTaskThread
{
public:
	CAutoSendThread()
	{
	}

	virtual ~CAutoSendThread()
	{

	}

	void Set(CPreOrder* pPreOrder);

protected:
	virtual int Run();

private:
	CPreOrder* m_pPreOrder;
};
*/

//#endif