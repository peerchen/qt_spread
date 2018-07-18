#ifndef _CLIENT_CP_MGR_H
#define _CLIENT_CP_MGR_H

//#pragma warning( disable: 4819 ) // ȥ�������ļ����������ڵ�ǰ����ҳ(936)�б�ʾ���ַ�����warning

#include "Comm.h"
#include "CommHandler.h"
#include <QString>
#include <iostream>
#include <QMap>
#include <list>
#include <QString>
#include <QVector>
#include <QList>
#include <QMutex>

#include <thread>
#include <functional>
using namespace std;

#include "TradePacketAndStruct.h"
#include "BroadcastPacketAndStruct.h"
#include "..\StDef.h"
//
#include "PreOrder.h"
//#include "MyLogEx.h"
#include "HJDef.h"
#include "Const.h"
#include "threadPool.h"
#include "mainWindow.h"
#include "QParamEvent.h"


// added by Jerry Lee, 2013-6-14, �����붨��
#define YLINK_NO_ERROR					0
#define YLINK_ERROR_BASECODE			-1
#define YLINK_ERROR_NETWORK				1000  // �����쳣
#define YLINK_ERROR_AUTHENTICATION		1001  // ��֤ʧ��
#define YLINK_ERROR_PASSWORD			1002  // ������֤ʧ��

struct ExchFare;
struct FareInfo;

struct OrderFrozeInfo
{
	double dEntrBuy;         // ί�н�Զ�ڵĻ����Ǳ�֤��
	double dEntrReserve;     // ί����̱�����
	double dEntrExchFare;    // ί��������
	int iTotal;              // ������

	int iRemainAmt;          // ʣ������
							 // 	double dEntrBuyRem;      // ʣ��ί�н�� double dEntrReserveRem;  // double dEntrExchFareRem; //

	void Init(double dTempEntrBuy, double dTempEntrReserve, double dTempEntrExchFare, int iTempTotal)
	{
		iRemainAmt = iTotal = iTempTotal;
		dEntrReserve = dTempEntrReserve;
		dEntrExchFare = dTempEntrExchFare;

		dEntrBuy = dTempEntrBuy;
	}

	// ģ��ⶳiCancelHand��
	//bool OrderFrozeInfo::CancelBal(int iCancelHand, double &dCancelBal);

	//bool OrderFrozeInfo::CancelBalForward(int iCancelHand, double &dCancelBal);
};

struct FundInfo
{
	double dSurplus;       // ����ӯ��
	double dAllBalance;    // �ܶ�
	double dUseFulBal;     // ���ý��
	double dExchFrozeBal;  // ���׶����ʽ�
	double dPosiMargin;    // �ֲ�ӯ��

	FundInfo()
	{
		ClearData();
	}

	void ClearData()
	{
		dSurplus = 0.0;
		dAllBalance = 0.0;
		dUseFulBal = 0.0;
		dExchFrozeBal = 0.0;
		dPosiMargin = 0.0;
	}
};


extern HEADER_REQ    g_HeaderReq;
extern quint64        g_SeqNo;

typedef enum
{
	FIELDKEY_LASTSETTLE = 0x0000,
	FIELDKEY_LASTCLOSE = 0x0001,
	FIELDKEY_OPEN = 0x0002,
	FIELDKEY_HIGH = 0x0003,
	FIELDKEY_LOW = 0x0004,
	FIELDKEY_LAST = 0x0005,
	FIELDKEY_CLOSE = 0x0006,
	FIELDKEY_SETTLE = 0x0007,
	FIELDKEY_BID1 = 0x0008,
	FIELDKEY_BIDLOT1 = 0x0009,
	FIELDKEY_BID2 = 0x000A,
	FIELDKEY_BIDLOT2 = 0x000B,
	FIELDKEY_BID3 = 0x000C,
	FIELDKEY_BIDLOT3 = 0x000D,
	FIELDKEY_BID4 = 0x000E,
	FIELDKEY_BIDLOT4 = 0x000F,
	FIELDKEY_BID5 = 0x0010,
	FIELDKEY_BIDLOT5 = 0x0011,
	FIELDKEY_ASK1 = 0x0012,
	FIELDKEY_ASKLOT1 = 0x0013,
	FIELDKEY_ASK2 = 0x0014,
	FIELDKEY_ASKLOT2 = 0x0015,
	FIELDKEY_ASK3 = 0x0016,
	FIELDKEY_ASKLOT3 = 0x0017,
	FIELDKEY_ASK4 = 0x0018,
	FIELDKEY_ASKLOT4 = 0x0019,
	FIELDKEY_ASK5 = 0x001A,
	FIELDKEY_ASKLOT5 = 0x001B,
	FIELDKEY_VOLUME = 0x001C,
	FIELDKEY_WEIGHT = 0x001D,
	FIELDKEY_HIGHLIMIT = 0x001E,
	FIELDKEY_LOWLIMIT = 0x001F,
	FIELDKEY_POSI = 0x0020,
	FIELDKEY_UPDOWN = 0x0021,
	FIELDKEY_TURNOVER = 0x0022,
	FIELDKEY_AVERAGE = 0x0023,
	FIELDKEY_SEQUENCENO = 0x0024,
	FIELDKEY_QUOTETIME = 0x0025,
	FIELDKEY_UPDOWNRATE = 0x0026,
	//��������
	//FIELDKEY_QUOTEDATE = 0x0027,
	//FIELDKEY_UNIT = 0x0028,//40
	FIELDKEY_BID6 = 0x0027,
	FIELDKEY_BIDLOT6 = 0x0028,
	FIELDKEY_BID7 = 0x0029,
	FIELDKEY_BIDLOT7 = 0x002A,
	FIELDKEY_BID8 = 0x002B,
	FIELDKEY_BIDLOT8 = 0x002C,
	FIELDKEY_BID9 = 0x002D,
	FIELDKEY_BIDLOT9 = 0x002E,
	FIELDKEY_BID10 = 0x002F,
	FIELDKEY_BIDLOT10 = 0x0030,

	FIELDKEY_ASK6 = 0x0031,
	FIELDKEY_ASKLOT6 = 0x0032,
	FIELDKEY_ASK7 = 0x0033,
	FIELDKEY_ASKLOT7 = 0x0034,
	FIELDKEY_ASK8 = 0x0035,
	FIELDKEY_ASKLOT8 = 0x0036,
	FIELDKEY_ASK9 = 0x0037,
	FIELDKEY_ASKLOT9 = 0x0038,
	FIELDKEY_ASK10 = 0x0039,
	FIELDKEY_ASKLOT10 = 0x003A,

	FIELDKEY_UNKNOWN
} ENUM_FIELDKEY;

#define QUOTATION_REC_SIZE sizeof(QUOTATION) //128


/*
//����һ��ģ�� 
typedef std::function<void(const char * prod, const char * price, const char * volume)> Functional;

class  QStrategyRunning : public QRunnable
{

public:
	QStrategyRunning()
	{
		flgRunning = true;
		if (condition == nullptr)
		{
			condition = new strategy_conditionOrder();
		}
	};

	void stop()
	{
		//unique_lock<mutex> lock(queue_mutex);
		flgRunning = false;
	}

	void setStragtegyCondition(strategy_conditionOrder *sc)
	{
		*condition = *sc;
	}
	void run()
	{
		flgRunning = true;
		while (flgRunning)
		{
			unique_lock<mutex> lock(queue_mutex);

			qDebug() << " Strategy  Running.....";
			//�ж�����
			//QMap<QString, vector<KLine> >mapProdData;
			//;
			if (g_TraderCpMgr.m_QHMapQuotation.size() < 1)
			{
				QThread::msleep(1500);
				continue;
			}

			QUOTATION  &quote = g_TraderCpMgr.m_QHMapQuotation[condition->id];

			//KLine &test = list[list.size() - 1];//�ó����µ����ݳ����Ƚ�
			if (condition->gainPrice > 0) //>= ����
			{
				//�۸��
				//double val = quote.m_Ask[0].m_uiPrice- condition->;
				//if (condition->compType  > 0)
				{
					//if (val >= condition->compVal)
					{
						//�����źţ��ύ������
						//if (condition->orderDirection <= 0)//����
						{
							//����
							//SendOrder(sellType,test.closeingPrice,condition->SellVolmune);
							/*funcSell(condition->strategyObj.prodID.toStdString().c_str(),
							QString::number(condition->SellPrice).toStdString().c_str(),
							QString::number(condition->SellVolmune).toStdString().c_str());

							condition->SellRunNum++;
						//}
					}
				}
			}
		}

		qDebug() << "Strategy Exited!";
	}

public:

	bool     flgRunning;
	//QMutex    *mutext;//һ������һ���̣߳�����
	strategy_conditionOrder *condition;

	mutex queue_mutex;

	Functional  funcSell;
	Functional  funcBuy;

	Functional  funcSell_QH;
	Functional  funcBuy_QH;
};

*/







// ���еĹ㲥��Ϣ����
typedef enum
{
	E_ONRECVRTNSPOTMATCH = 0,
	E_ONRECVRTNFORWARDMATCH,
	E_ONRECVRTNDEFERMATCH,
	E_ONRECVRTNDEFERDELIVERYAPPMATCH,

	E_ONRECVRTNSPOTORDER,
	E_ONRECVRSPSPOTORDER,
	E_ONRECVRSPFORWARDORDER,
	E_ONRECVRTNFORWARDORDER,
	E_ONRECVRTNDEFERORDER,
	E_ONRECVRSPDEFERORDER,
	E_ONRECVRTNDEFERDELIVERYAPPORDER,
	E_ONRECVRSPDEFERDELIVERYAPPORDER,
	E_ONRECVRTNMIDDLEAPPORDER,
	E_ONRECVRSPMIDDLEAPPORDER,

	E_ONRECVRTNSPOTORDERCANCEL,
	E_ONRECVRSPSPOTORDERCANCEL,
	E_ONRECVRTNFORWARDORDERCANCEL,
	E_ONRECVRSPFORWARDORDERCANCEL,
	E_ONRECVRTNDEFERORDERCANCEL,
	E_ONRECVRSPDEFERORDERCANCEL,
	E_ONRECVRTNDEFERDELIVERYAPPORDERCANCEL,
	E_ONRECVRSPDEFERDELIVERYAPPORDERCANCEL,
	E_ONRECVRTNMIDDLEAPPORDERCANCEL,
	E_ONRECVRSPMIDDLEAPPORDERCANCEL,

	E_ONNEWBOURSEBULLETIN,
	E_ONNEWMEMBERBULLETIN,
	E_ONRISKNOTIFY,
	E_ONSYSINIT,
	E_ONSYSSTATCHANGE,

	E_ONRECVSPOTQUOTATION,
	E_ONRECVFORWARDQUOTATION,
	E_ONRECVDEFERQUOTATION,
	E_ONRECVDEFERDELIVERYQUOTATION,
	E_ONRECVFUTUREQUOTATION,//�ڻ�����
	E_ONRECVSPREADQUOTATION,//��������

	E_ONRECVRTNSPOTINSTSTATEUPDATE,
	E_ONRECVRTNFORWARDINSTSTATEUPDATE,
	E_ONRECVRTNDEFERINSTSTATEUPDATE,

	E_ONBASETABLEUPDATE,
	E_ONRECVRTNSPOTMARKETSTATEUPDATE,
	E_ONRECVRTNFORWARDMARKETSTATEUPDATE,
	E_ONRECVRTNDEFERMARKETSTATEUPDATE,
	E_ONCUSTINFOCHANGE,
	E_ONCUSTRISKDEGREECHANGE,

	E_ONFORCELOGOUT,
	E_ONSESSIONKEY,
	E_ONACCTCAPITALACCESS,

	E_ONRECVSPOTORDER,
	E_ONRECVFORWARDORDER,
	E_ONRECVDEFERORDER,
	E_ONRECVDEFERDELIVERYAPPORDER,
	E_ONRECVMIDDLEAPPORDER,

	// ��¼�ɹ�
	E_ONLOGINSUCC,
	E_ONREFRESHCUSTOMDATA,
	E_COMMIT_POSI,
	E_COMMIT_STORE,
	E_PREORDER_CHANGE,
	E_REFRESHFUND,
	E_UPDATE_LIST,
	E_HQ_STATE,
	E_SER_PREORDER_REFRESH,

	E_WIND_VANE,
	E_SURPLUS_CHANGE, // �ֲ�ӯ�������仯
	E_TOTAL_SURPLUS_CHANGE, // �ֲܳ�ӯ�������仯
	E_CUSTOM_INFO_CHANGE, // �ͻ���Ϣ�仯
	E_ADD_PREORDER_CONFIRM, // ����������
} EHJBROADCASTMSGTYPE;

typedef enum
{
	E_DlgOrder,
	E_DlgUpRight,
	E_DlgDownLeft,
	E_DlgDownRight,
	// 	E_DlgEnterFlow,
	// 	E_DlgPreOrder,
	// 	E_DlgPosi,
	// 	E_DlgStore,
	// 	E_DlgFund,
	// 	E_DlgMatchFlow,
} EDLGID;


// �㲥����
class CBroadcaster
{
public:
	CBroadcaster();

	~CBroadcaster();

	CBroadcaster(const CBroadcaster& bdr);

	CBroadcaster& operator=(const CBroadcaster& bdr);


	// ���ھ��Ϊint�Ĵ��ڶ�����Ϣ
	void Subscribe(QWidget* val);

	// ���ھ��Ϊint�Ĵ���ȡ��������Ϣ
	void Unsubscribe(QWidget* val);

	// �㲥��Ϣ
	void Broadcast(uint uMsg, void* wParam, void * lParam, BOOL bAsyn = TRUE);
	

private:

	int Find(QWidget* val);
	QVector<QWidget *> m_arrint;


};


//QWaitCondition bufferUpdate;
//bool           newSignal;
//QMutex         sigMutex;
//QString        gstrCurT1ProdId;
//QString        gstrCurT2ProdId;
//
////��������
//using Functional = std::function<void(const char * prod, const char * price, const char * volume)>;
//class  QStrategyRunning : public QRunnable
//{
//
//public:
//	QStrategyRunning()
//	{
//		newSignal = false;
//		flgRunning = true;
//		//if (condition == nullptr)
//		//{
//		//	condition = new strategy_conditionOrder();
//		//}\
//
//		condition = std::make_shared<strategy_conditionOrder>();
//	};
//
//
//	void stop()
//	{
//		//unique_lock<mutex> lock(queue_mutex);
//		flgRunning = false;
//	}
//
//	void setStragtegyCondition(strategy_conditionOrder *sc)
//	{
//		*condition = *sc;
//	}
//	void run()
//	{
//		flgRunning = true;
//		while (flgRunning)
//		{
//			unique_lock<mutex> lock(queue_mutex);
//
//			sigMutex.lock();
//			//�ж�����
//			if (!newSignal)
//				bufferUpdate.wait(&sigMutex);
//
//			//if (g_TraderCpMgr.m_QHMapQuotation.size() < 1)
//			//{
//			//	QThread::msleep(1500);
//			//	continue;
//			//}
//
//			QUOTATION  &QHquote = condition->obj[0].quote;// g_TraderCpMgr.m_QHMapQuotation[gstrCurT1ProdId];//condition->id
//			QUOTATION  &HJquote = condition->obj[1].quote;
//
//			//KLine &test = list[list.size() - 1];//�ó����µ����ݳ����Ƚ�
//			if (condition->gainPrice > 0) //>= ����
//			{
//				//�۸��
//				//double val = quote.m_Ask[0].m_uiPrice- condition->;
//				//if (condition->compType  > 0)
//				{
//					//if (val >= condition->compVal)
//					{
//						//�����źţ��ύ������
//						//if (condition->orderDirection <= 0)//����
//						{
//							//����
//							//SendOrder(sellType,test.closeingPrice,condition->SellVolmune);
//							/*funcSell(condition->strategyObj.prodID.toStdString().c_str(),
//							QString::number(condition->SellPrice).toStdString().c_str(),
//							QString::number(condition->SellVolmune).toStdString().c_str());
//
//							condition->SellRunNum++;*/
//						}
//					}
//				}
//			}
//
//
//
//			sigMutex.unlock();
//			newSignal = false;
//		}
//
//		//qDebug() << "Strategy Exited!";
//	}
//
//public:
//
//	bool     flgRunning;
//	//QMutex    *mutext;//һ������һ���̣߳�����
//	std::shared_ptr<strategy_conditionOrder >condition;
//
//	mutex queue_mutex;
//
//
//	Functional  funcSell;
//	Functional  funcBuy;
//
//	Functional  funcSell_QH;
//	Functional  funcBuy_QH;
//};



//class CPacketReceiver;

//class QStrategyRunning;

//struct   srategy_condition1
//{
//	//
//	int  test;
//	std::string t1;
//	std::string t2;
//};

class  strategyCondition : public Theron::Actor
{
public:
	inline strategyCondition(Theron::Framework & framework) :Theron::Actor(framework)
	{
		RegisterHandler(this, &strategyCondition::produce);
	}

private:
	inline void produce(const strategy_conditionOrder& item, const Theron::Address  from)
	{
		//
		strategy_conditionOrder  test;
		/*test.test = item.test + 1;
		test.t1 = item.t1;
		test.t2 = item.t2;*/
		if (Send(test, from))
		{
			//
		}

		return;
	}
};

class  strategyOrder : public Theron::Actor
{
	using Task = std::function<void(const char *prodId,double price,double volume,int direction��bool)>;//direction  1:
public:
	inline strategyOrder(Theron::Framework & framework) :Theron::Actor(framework)
	{
		RegisterHandler(this, &strategyOrder::consume);
	}
	void setTask(Task &task)
	{
		mDeque.push_back(task);
	}

	//void setSellTask(Task &task)
	//{
	//	mSTask = task;
	//}

private:
	inline void consume(const strategy_conditionOrder& item, const Theron::Address  from)
	{
		//
		//strategy_conditionOrder  test;
		/*test.test = item.test - 1;
		test.t1 = item.t1;
		test.t2 = item.t2;*/
		//���룬ִ�б���
		for (auto t : mDeque)
		{
			t(item.obj[0].prodID.toStdString().c_str(), item.price, item.volume, item.direction.toInt());//0����ͬ��
			t(item.obj[1].prodID.toStdString().c_str(), item.price, item.volume, item.direction == "1" ? 0 : 1);//����
		}
		//֪ͨ���
		if (Send(0, from))
		{
			//
		}

		return;
	}


	std::deque<Task> mDeque;
	//Task  mBTask;
	//Task  mSTask;
};





// �ƽ�ҵ������
class CTraderCpMgr : public CPacketReceiver, public CPacketReceiverQH
{
	Theron::Framework  *framework = nullptr;
	strategyCondition  *gstrategyCond = nullptr;
	strategyOrder      *gstrategyOrder = nullptr;
public:
	CTraderCpMgr();
	virtual ~CTraderCpMgr();

	void resetAccount(QString && str);
	void InitStrategy();
public:
	// ����㲥�����гɽ���ˮ����
	QMap<QString, SpotMatch>                m_QMapSpotMatch;
	QMap<QString, ForwardMatch>             m_QMapForwardMatch;
	QMap<QString, DeferMatch>               m_QMapDeferMatch;
	QMap<QString, DeferDeliveryAppMatch>    m_QMapDDAMatch;

	// ����㲥�����б�����ˮ����
	QMap<QString, SpotOrder>                 m_QMapSpotOrder;      //
	QMap<QString, ForwardOrder>              m_QMapForwardOrder;   //
	QMap<QString, DeferOrder>                m_QMapDeferOrder;     // 
	QMap<QString, DeferDeliveryAppOrder>     m_QMapDDAOrder;       // 
	QMap<QString, MiddleAppOrder>            m_QMapMiddleAppOrder; // 

																   // ������ˮ
	QMap<QString, OrderCancel>               m_QMapDeferOrderCancel; // ���ڵĳ�����������
	QMap<QString, OrderCancel>               m_QMapOrderCancel;      // ���������ڵĳ���

																	 // ��¼�ͻ��ĳֲ���Ϣ
	QMap<QString, DeferPosi>                 m_QMapDeferPosi;

	// �����Ϣ
	QMap<QString, StoreInfo>               m_QMapStoreInfo; // 

															// �ʽ���Ϣ
	FundInfo m_stFundInfo;

	// ���ճ������Ϣ
	QMap<QString, QString> m_QMapTransfer;

	// ���ձ���������Ϣ
	QMap<QString, OrderFrozeInfo> m_QMapOrderFroze; //

	// ����ɽ���ˮʱ�ͷŶ����ʽ��ʱ��û�ҵ��ı����ı��ر����ţ������������
	QVector<QString> m_arrUnFindLocalOrderNo;

	QMap<QString, int> m_QMapMatchUnFindInfo;


	// ϵͳ����
	QMap<QString, QString> m_QMapSystemPara;

	// Ʒ��״̬
	QVector<InstState>                      m_vInstState;//

	// Ԥ��
	CPreOrder                              m_cPreOrder;       // Ԥ�񵥹�����

	//CAutoSendThread                        m_cAutoSendThread;  //Ԥ���߳�
	//kenny  2018-1-8 �滻�Զ��߳�
	ThreadPool    pool;
	std::thread   *m_cAutoSendThread;


	 // ��¼�������ͻ���Ϣ���ʽ𡢸�����Ϣ���ֲ��Լ���棩
	Rsp1020 m_rsp1020;

	// ��¼�ͻ��ķ���ģ��
	Rsp2040 m_rsp2040;

	quint64 m_uOrderSerial;

	QMap<EDLGID, int> m_QMapDlgHandle;

	list<QString> m_QMapUnMatchOrder; // ��¼�ڱ����г��ֹ��ı�������Ҫ�����������ǵ�¼�����ͳɽ����������������ʱ�ɽ���
	bool bIsOrderUnMatch(const QString &sLocalOrderNo, bool bErase = false);

	// added by Jerry Lee, 2013-6-19, ������ˮ���Ƿ���ڿ��ֵ�
	bool OpenedBillExists();

public:
	// �����������-----------------------------------------------------------------------------------------------
	typedef bool (CTraderCpMgr::*PFunTypeAsk)(ArrayListMsg &);
	typedef void (CTraderCpMgr::*PFunTypLoad)(const ArrayListMsg &);

	// ��ʼ����������ͳһ���õĺ���
	bool IniBasicData(const QString &csTitle, PFunTypeAsk pFunAsk, PFunTypLoad pFunLoad);

	// �����������������ͳһ���õĺ���
	bool AskForData(const QString &sReqTitle, QVector< pair<QString, QString> > &vecPara, const ArrayListMsg &almViewField, ArrayListMsg &alm_result);

	// �����ʽ��������
	bool AskForFundBaseData(ArrayListMsg &alm_result);

	// �����ʽ��������
	void LoadFundBaseData(const ArrayListMsg &alm_result);

	// �������ڻ�������
	bool AskForDeferPosiBaseData(ArrayListMsg &alm_result);

	// �������ڻ�������
	void LoadDeferPosiBaseData(const ArrayListMsg &alm_result);

	// ����Զ�ڻ�������
	bool AskForForwardPosiBaseData(ArrayListMsg &alm_result);

	// ����Զ�ڻ�������
	void LoadForwardPosiBaseData(const ArrayListMsg &alm_result);

	// �������������
	bool AskForStoreBaseData(ArrayListMsg &alm_result);

	// ���ؿ���������
	void LoadStoreBaseData(const ArrayListMsg &alm_result);

	// ��ȡ�����ļ�����ʼ�����յĳ������ˮ
	void IniTodayTransfer();

	// ��ȡ�ڴ����汣��ĵ��ճ������ˮ��������arraylist�ĸ�ʽ
	QString FormatCurTransferStr();

	// �㲥�������---------------------------------------------------------------------------------
	void SubscribeOrder(QWidget* hHandle, bool bSubscribe = true, const QString &sMarketID = "");
	void SubscribeOrderCancel(QWidget* hHandle, bool bSubscribe = true, const QString &sMarketID = "");
	void SubscribeMatch(QWidget* hHandle, bool bSubscribe = true, const QString &sMarketID = "");
	void SubscribeAll(QWidget* hHandle, bool bSubscribe = true);
	// ��������ҵ��㲥
	void SubscribeDefer(QWidget* hHandle, bool bSubscribe = true, bool bNormal = true, bool bDDA = true, bool bMA = true);


	// ����𱾵ؼ������---------------------------------------------------------------------------------
	// ���ڴ��еĵ��ճ������ˮ�齨���ַ�����д���ļ�
	void WriteTodayTransferToFile();

	// ����������ˮ��ѯ��һ��������ˮ����Ϣ����ˮ���ڴ��в������򷵻�true�������򷵻�false
	bool DealOneHandTransfer(const QString &sSerialNo, QString sExchBal, bool bIn);

	// ��ȡ��ǰ�ĳ������Ϣ
	bool GetTodayTransfer();

	// ����3101����Ӧ���ļ��ص���������Ϣ
	void LoadTodayTransfer(HashtableMsg &htm_result);
	void LoadTodayTransfer(ArrayListMsg &alm_result);

	// �ʽ𱾵ؼ������---------------------------------------------------------------------------------

	void IniOrderSerial();

	QString GetOrderSerialStr();

#if (defined _VERSION_JSZX) || (defined _VERSION_ZHLHY)
	// ���ó������õ�ģʽ���Զ���������ֶ�����𣬽���JSZX�汾���ã�
	void SetTransferMode(const ArrayListMsg &alm_menu_info);
#endif

public:
	// ���ݺ�Լ�����ȡ�ͻ��Ŀ��ò�λ
	void CustomerUsefulPosi(const QString& prodCode, int& iUsefullong, int& iUsefulshort);

	// ��ȡ����Ʒ��sProdCode�Ľ������Ʒ�ֵ����ƣ�sProdCode�����ڱ���Ʒ��  sSubVAriety���������Ʒ������  sSeq����ţ�
	bool GetCusSubVarietyName(const QString &sProdCode, QString &sSubVAriety, const QString &sSeq);

	// ��ȡ�����ֱ����۸�
	double GetMAOrderPrice(const QString &sProdCode);

	// ����Ʒ��״̬���
	int GetInstStatePos(const QString &sProdCode);
	// ��������Ʒ�ֻ�ȡ��ǰƷ�ֵ�״̬ID
	QString GetInsStateID(const QString &sInsID);

	// �����ֻ�����ʱ�Ŀ�涳���ⶳ bFreeze���Ƿ��Ƕ��ᣬ����Ϊ������ᣩ
	bool HandleTradeStore(const QString &sProdCode, int iHand, bool bFreeze, const QString &sDDAProdCode = "");

	// ������ʱ���ʽ𶳽��ⶳ bFreeze���Ƿ��Ƕ��ᣬ����Ϊ������ᣩ
	bool HandleTradeFee(const QString &sProdCode, const QString &sExchID, double dPrice, int iHand, bool bFreeze, const QString &localOrderNo = "");

	// ������ʱ���ʽ�ⶳ
	bool HandleCancelTradeFee(const QString &sProdCode, int iHand, const QString &localOrderNo);

	// ����һ�ʽ��׵ķ���
	double CalculateTradeFee(const ProdCodeInfo &info, const QString &sExchID, double dPrice, int iHand, bool bMatch = false, const QString &localOrderNo = "");

	// ����
	void CalSpotSellMatchFee(const ProdCodeInfo &info, double dPrice, int iHand, double &dMatchBal, double &dExchFare);

	// ��ȡһ������Ʒ�ֵĳֱֲ�֤��
	double CalculateMagin(const QString &sProdCode, double dPrice, int iHand, bool bSumSingle = true);

	// �����ֻ��ɽ����ʽ���Ϣ
	bool HandleSpotMatchFee(const QString &sProdCode, const QString &sExchID, double dPrice, int iHand, bool bAdd, const QString &localOrderNo = "");

	// �����ֻ��ɽ��Ŀ��
	bool HandleMatchStore(const QString &sProdCode, int iHand, bool bAdd);

	// �������ڳɽ����ʽ���Ϣ
	bool HandleDeferMatchFee(const QString &sProdCode, const QString &sExchID, double dPrice, int iHand, bool bBuy, double &dPosiMoney, const QString &localOrderNo = "");

	// ��������ƽ�ֳɽ����ʽ���Ϣ
	bool HandleDeferCovMatchFee(const QString &sProdCode, double dPrice, int iHand, bool bLong);

	// ����ƽ�ֵ�ʱ���ͷŵı�֤��ͳֲ�ӯ��
	void HandleDeferCovReleaseFee(const QString &sProdCode, double dPrice, int iHand, double dMeasure_unit, bool bLong, ExchFare &ef_m_release_margin, double &d_cov_surplus);

	// �������ڽ��ճɽ����ʽ���Ϣ
	bool HandleDDAMatchFee(const QString &sProdCode, int iHand, bool bBuy, const QString &localOrderNo = "");

	// ���������ֳɽ����ʽ���Ϣ
	bool HandleMAMatchFee(const QString &sProdCode, int iHand, bool bBuy, const QString &localOrderNo = "");

	// ���ڽ������ͷŵ����ڿ��ֱ�֤��
	double GetOpenFareOrg(const QString &sProdCode, bool bLong, double fUnite, int iHand /*= 1*/);

	// ���ݲ���ID��ȡϵͳ������ֵ�������ȡʧ�ܣ�����Ĭ��ֵ������ɹ������¼���ڴ�
	QString GetParaValue(const QString &sParaID, const QString &sDefaultValue);

	// ����ֲ�ӯ��
	void CalculatePosiMargin();

	// ���潻��Ʒ��
	HashtableMsg m_htmSubVariety;
	QString GetSubVarietyProdCode(const QString &sProdCode);

	// // ��ȡ���ڽ��ն��ʽ��������õļ۸����õļ۸񣨵�ǰʹ��Ĭ�ϵ����ս���ۣ�*��1+��ͣ���ʣ�
	double GetDeferDeliveryPrice(const QString &sProdCode);


	// ���±�����Ϣ
	void RefreshOrderInfo(OrderBase *OrgOrder, const OrderBase *NewOrder);
	// ��ʱ��Ϊ���ڽ������ͷŵ����ڿ��ֱ�֤��
	double GetOpenFare(const QString &sProdCode, bool bLong, double fUnite, const FareInfo &fi, int iHand /*= 1*/);

	// �����������ݲ�����bit���飬���ұ߿�ʼ�����ǣ��ʽ𡢿�桢�ֲ֡���ա�����
	void SetBitSet(bitset<5> &bitvec, bool bFund = false, bool bStore = false, bool bPosi = false, bool bLong = false, bool bBuy = false);

	double GetRealeaseMoney(const QString &localOrderNo, int iHand);

	double GetMatchUnReleaseMoney(const QString &localOrderNo);

	//void RecordOrderFroze(const QString &localOrderNo);

	double HandleMatchReleaseMoney(const QString &localOrderNo, int iHand);

	void CalForwardMatchFee(const ProdCodeInfo &info, double dPrice, int iHand, double &dPosiMoney, double &dExchFare);

	// ����һ��Զ�ڳɽ�����ʽ�仯
	bool HandleForwardMatchFee(const QString &sProdCode, const QString &sExchID, double dPrice, int iHand, double &dPosiMoney, const QString &localOrderNo);

	bool IsOrderCanBeProcess(const QString &sOrderState);

	void CalDeferMatchFee(const ProdCodeInfo &info, double dPrice, int iHand, double &dPosiMoney, double &dExchFare, bool bOpen);

	void CalDeferCovMatchFee(const ProdCodeInfo &info, double dPrice, int iHand, bool bLong, ExchFare &efPosiMoney, ExchFare &efExchFare, double &d_cov_surplus);

	void GetDDATradeFee(const ProdCodeInfo &info, bool bLong, int iHand, ExchFare &ef_m_deli_prepare, ExchFare &ef_m_release_margin);

	//
	void GetMAMatchFee(const ProdCodeInfo &info, bool bLong, int iHand, ExchFare &ef_m_deli_prepare, ExchFare &ef_m_release_margin);



	// �ֲ��Զ��������-----------------------------------------------------------------------------------------------

	// ģ������λ��ƽ��
	void RemoveMatchFlow(LISTDeferMatch &listMatch, int iHand);

	/*
	����ĳ��Ʒ�ֵ�ĳһ������ĳֲ־��ۡ��ֲ�ӯ�����ֱֲ�֤��
	bRefresh���Ƿ����������������
	*/
	void CalculateOtherValue(const QString &sProdCode, DeferPosiInfo &stDeferPosiInfo, bool bLong, bool bRefresh = false);

	// ����һ��Ʒ�ֵĳֲ�ӯ��
	double GetPosi_PL(const QString &sProdCode, double dAvgPosiPrice, int iTotalHand, bool bLong);

	// ���ܵ�����ƽ�ֵı�����ˮ�������λ
	bool DealDeferCancelFreezePosi(const QString &instID, bool bLong, bool bExist, int iTotalAmount, int iRemainAmount);

	int CommitOrder(const QString &sProdCode, double dPrice, int iAmount, const QString &sExchID);

	// ����һ������������Ƿ�����Զ���ʾ
	int CommitOrder(const QString &sProdCode, const QString &csPrice, const QString &csAmount, const QString &sExchID, int orderType,bool bAuto = true);

	void ShowMatchTips(const QString &sProdCode, const double &dPrice, const int &iAmount, const QString &sExchID, const QString &sOrderNo);

	int CancelOrder(QString &csOrderNo);


	// ������-----------------------------------------------------------------------------------------------

	bool GetVarietyInfo(const QString &sVarietyID, VarietyInfo &info);

	// ϵͳ�������-----------------------------------------------------------------------------------------------

	void GetRsp2040();

	void RefreshCusFundInfo();

	void ClearSession();
	QString GetSessionID();

	QString GetCode_desc(QString codetype, QString codeid); // ��ȡ�������ĳһ�����µ�ĳһid�¶�Ӧ��ֵ(codedesc)
	QString GetCode_id(QString codetype, QString codeid); // ��ȡ�������ĳһ�����µ�ĳһid�¶�Ӧ��ֵ(codedesc)

														  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int Init();

	int Authenticate(const char* pszUsr, const char* pszPwd, const char* pszAddr = 0, int nPort = 0, QString useridtype = "1", bool bSign = false);
	int UserLogin(const QString &useridtype = "1", bool bSign = false);
	int UnlockScreen(const QString &pwd, const QString &useridtype = "1");

	// �Ƚϱ��ذ汾����������汾�ţ����С�ڷ������İ汾�ţ�����Ҫ���²���
	bool CompareVersion(QString strLocalVersion, QString strSerVersion, int iCompare = 2);

	// ������б�������QVector
	void ClearCodeTableList();
	//
	void GetProdCodeFromServer();
	//
	void GetVarietyFromServer();
	//
	void GetCodeFromServer();

	// ��ȡ�������Ʒ���趨
	bool Ini1005();
	// 
	QString GetSubVarietyBySeqNo(const QString &sProdCode, const QString &sSeqNo);

	int UserLogout();

	bool IsLoginSucceed() { return m_bLoginSucceed; }



	int GetDlgHandleFromID(const EDLGID &eDlgID);

	void AddDlgHandle(const EDLGID &eDlgID, const int &hDlg);

	////�������������ȡ�ֻ���������id
	//QString GetSpotId(QString buysell);

	////�������������ȡԶ�ڽ�������id
	//QString GetForwardId(QString buysell);

	////������������Ϳ�ƽ��־��ȡ���ڽ�������id
	//QString GetDeferId(QString offflag, QString buysell);

	//QString GetDDAOrderId(QString buysell);

	//QString GetDDAMatchId(QString middleflag, QString buysell);

	//QString GetMAOrderId(QString buysell);

	//kenny �ٽ�����Ϊ������
	//CRITICAL_SECTION m_criticalSection;
	QMutex m_criticalSection;

	void Broadcast(UINT uType, UINT uMsg, void* wParam, void* lParam, BOOL bAsyn = TRUE)
	{
		m_criticalSection.lock();
		m_mapBdr[uType].Broadcast(uMsg, wParam, lParam, bAsyn);
		m_criticalSection.unlock();
	}

	// ������ip
	QString GetIPFromDomain(const QString &sDomain);

public: // �ڴ����
	std::map<string, QUOTATION> m_QMapQuotation;  //������¼�㲥����������ʵʱ����	
	std::map<QString, QUOTATION> m_QHMapQuotation;  //������¼�㲥�������ڻ�����ʵʱ����	
	std::map<QString, QUOTATION> m_SpreadMapQuotation;  //��������ʵʱ����	

	QVector<DeferDeliveryQuotation> m_vecDDQuotation;

	QVector<MyCodeInfo> m_vCode;                  // ��Ӧ��1001,���еĲ�ѯ�������루��ʱ���ã�

												  //��ѯ����
	QVector<ProdCodeInfo> m_vProdCode; //��������
	ProdCodeInfo GetProdeCode(const QString &sProdCode);
	bool GetProdeCode(ProdCodeInfo& stProdCode, const QString &sProdCode);

	QVector<VarietyInfo> m_vVariety;   //����Ʒ�ִ��� 

	QVector<MyCodeInfo> m_vExchCode;   //��������
	QVector<MyCodeInfo> m_vOffsetFlag; //��ƽ��־
	QVector<MyCodeInfo> m_vFeeCode;    //���ô���
	QVector<MyCodeInfo> m_vSubFeeCode; //���ô���
	QVector<MyCodeInfo> m_vLongShort;  //�ֲַ���

									   //list�ֶ�ת��
	QVector<MyCodeInfo> m_vMarketId;   //�����г�
	QVector<MyCodeInfo> m_vEntrState;  //ί��״̬
	QVector<MyCodeInfo> m_vCancelFlag; //������־
	QVector<MyCodeInfo> m_vTermType;   //��������
	QVector<MyCodeInfo> m_vAccessWay;  //��������
	QVector<MyCodeInfo> m_vCheckState; //����״̬
	QVector<MyCodeInfo> m_vTakeState;  //���״̬
	QVector<MyCodeInfo> m_vDrawType;   //�������
	QVector<MyCodeInfo> m_vCertType;   //֤������
	QVector<MyCodeInfo> m_vAcctState;  //�˻�״̬
	QVector<MyCodeInfo> m_vInstState2;  //��������Լ״̬
	QVector<MyCodeInfo> m_vFCOrderState; // ����ǿƽ�����͵�ת��
	QVector<MyCodeInfo> m_vDeliFlag; // ���ձ�־
	QVector<MyCodeInfo> m_vPageInfo; // ��ѯ�����ҳ����Ϣ

									 // ���ݺ�Լ�����Լ����״����ȡ�ͻ��Ľ���������ģ��
	FareInfo GetBFareValue(const QString &sProdCode, const QString &sExchCode);
	// ���ݺ�Լ�����Լ����״����ȡ�ͻ��Ļ�Ա����ģ��
	FareInfo GetMFareValue(const QString &sProdCode, const QString &sExchCode);

	unsigned int GetLastPrice(const QUOTATION &qt);

	double GetLastPriceEx(const QUOTATION &qt);

	// ���ݺ�Լ�����ȡ�ú�Լ�������Ϣ
	bool GetProdCodeInfo(const QString &sProdCode, ProdCodeInfo &info);

	// ��ʼ��ϵͳ��������
	void IniSystemSetting();

	//
	bool IsUnFindLocalOrderNo(const QString &sLocalOrderNo);

	//bool IsMatchOrderLegal();

public:
	// ���ݽ���Ʒ��ID��ȡ����Ʒ������
	QString GetVarietyName(const QString &sID);

	// ���ݽ�������ID��ȡ������������
	QString GetExchName(const QString &sID);

	QString GetExchIDFromName(const QString &sName);

	// ����ί��״̬ID��ȡί��״̬����
	QString GetEntr_statName(const QString &sID);

	// ���ݸ���״̬ID��ȡ����״̬����
	QString GetCheck_staName(const QString &sID);

	// �����˻�״̬ID��ȡ�˻�״̬����
	QString GetAcct_statName(const QString &sID);

	// ����֤��ID��ȡ֤������
	QString GetIdTypeName(const QString &sID);

	// ����֤�����ƻ��֤��id
	QString GetIdTypeId(const QString &sName);

	// �������״̬ID��ȡ���״̬����
	QString GetTake_statName(const QString &sID);

	// �������״̬���ƻ�ȡ���״̬ID
	QString GetTake_statID(const QString &sName);

	// �����������ID��ȡ�����������
	QString GetDraw_typeName(const QString &sID);

	// 
	QString GetFCOrderStateName(const QString &sID);

	// ���ݽ����г�ID��ȡ�����г�����
	QString GetMarketName(const QString &sID);

	// ���ݿ�ƽ��־ID��ȡ��ƽ��־����
	QString GetOffset_flagName(const QString &sID);

	// ���ݽ��ձ�־ID��ȡ���ձ�־����
	QString GetDeli_flagName(const QString &sID);

	// ������������ID��ȡ������������
	QString GetBuySellName(const QString &sID);

	// ���ݳ�����־ID��ȡ������־����
	QString GetCancel_flagName(const QString &sID);

	// ���ݲ�������ID��ȡ������������
	QString GetAccessWayName(const QString &sID);

	// ����ת���Ƿ�ɹ�ID��ȡת���Ƿ�ɹ�����
	QString GetIn_account_flagName(const QString &sID);

	// ���ݳֲַ���ID��ȡ�ֲַ�������
	QString GetLongShortName(const QString &sID);

	// ��������ID��ȡ�������ƣ�����ί������,��������,������Դ��
	QString GetTerm_typeName(const QString &sID);

	QString GetProdCodeName(const QString &sID);

	QString GetInsStateNameFromID(const QString &sInsID);

public:
	//�ڴ�·�ɱ�
	//QMap<QString, CConnector3**>  m_tblIfRouter;
	QMap<QString, CConnectPointSync**>  m_tblIfRouter;
	int InitRouterTbl();

	int Tran6002Handle(HEADER_REQ& stHeaderReq, Req6002& stBodyReq, HEADER_RSP& stHeaderRsp,
		Rsp6002& stBodyRsp, QVector< pair<QString, QString> > & v, unsigned int uiTimeout);


	template<class REQ, class RSP>
	int HandlePacketCommon(RSP& stBodyRsp, REQ& stBodyReq, const QString &sExchCode, CTradePacket &oPktReq, unsigned int uiTimeout = 0, bool bBackground = false)
	{
		if (uiTimeout == 0)
			uiTimeout = m_nTimeOut;

		//kenny  2017-11-17   �޸�����ӿڲ��ִ���
		// ��ʼ������ͷ
		m_csSendPkt.lock();
		g_HeaderReq.IniRequst(sExchCode.toStdString(), g_SeqNo);
		oPktReq.SetHeader(g_HeaderReq);
		m_csSendPkt.unlock();

		CTradePacketAndStruct::Struct2Packet(stBodyReq, oPktReq);

		// ���ݽ��ױ����ҵ���Ӧ�Ľӿ�
		CConnectPointSync* pCp = nullptr;
		if (bBackground)
		{
			pCp = CCommHandler::Instance()->GetInterfaceVip();
		}
		else
		{
			pCp = FindRoute(sExchCode);
		}

		if (nullptr == pCp) // û�ж�Ӧ�Ľӿ�
		{
			return -2;
		}

		qDebug( sExchCode.toLatin1().data(), "���ͱ���");

		// ���ͱ���
		CTradePacket oPktRsp;
		int nRtn = 0;
		nRtn = pCp->SendPacket(*(CPacket *)&oPktReq, *(CPacket *)&oPktRsp, uiTimeout);
		if (0 != nRtn)
		{
			stBodyRsp.rsp_code = gc_ErrCode_ConSverFail.toStdString();
			stBodyRsp.rsp_msg = "���ӷ�����ʧ��";
			qDebug(sExchCode.toLatin1().data(), stBodyRsp.rsp_code);

			/*if( nRtn == -100 )*/
			// ����Ƿ����أ����л������������Ի�����������նȼ�������ʧ�ܵ�
			/*			if( sExchCode != "3099" )
			{
			SwitchServer();
			}
			*/
			return nRtn;
		}

		oPktRsp.GetRspCode(stBodyRsp.rsp_code);
		CTradePacketAndStruct::Packet2Struct(stBodyRsp, oPktRsp);

		qDebug(sExchCode.toLatin1().data(), stBodyRsp.rsp_code);

		return 0;
	}

	template<class REQ, class RSP>
	int HandlePacket(RSP& stBodyRsp, REQ& stBodyReq, const QString &sExchCode, unsigned int uiTimeout = 0, bool bBackground = false)
	{
		CTradePacket oPktReq;
		return HandlePacketCommon(stBodyRsp, stBodyReq, sExchCode, oPktReq, uiTimeout, bBackground);
	}

	template<class REQ, class RSP>
	int HandlePacket6002(RSP& stBodyRsp, REQ& stBodyReq, const QString &sExchCode, const QVector< pair<QString, QString> > & v, unsigned int uiTimeout = 0)
	{
		CTradePacket oPktReq;

		for (size_t i = 0;i<v.size();i++)
		{
			//oPktReq.AddParameter(v.at(i).first, v.at(i).second);
		}

		return HandlePacketCommon(stBodyRsp, stBodyReq, sExchCode, oPktReq, uiTimeout);
	}

	// ��������
	virtual void Receive(CPacket &pkt);

	//�����ڻ�����
	virtual void Receive(CBroadcastPacket &pkt) override;

	// ������Ϣ�㲥��
	CBroadcaster* GetBroadcaster(int nBdrType);

	// ���Ĺ㲥��Ϣ
	void Subscribe(int nBdrMsgType, QWidget * val);

	// ȡ�����Ĺ㲥��Ϣ
	void Unsubscribe(int nBdrMsgType, QWidget * val);

	// ����id���Ʒ�ֵĿ��
	// QString GetUsefulStore(QString variety_id);

	// ����id���Ʒ�ֵ�Զ�ڲ�λ
	//   void GetCangWeiT5(const QString& prodCode, QString& usefullong, QString& usefulshort);

	QString GetEncryptPSW(const char* pszPwd, bool bShort = false);

private:
	//�����Ա����ָ��
	typedef int (CTraderCpMgr::*MFP_PacketHandleApi)(CBroadcastPacket& pkt);

	//�����������뱨�Ĵ����Ա����ӳ��ṹ
	typedef struct tagCmd2Api
	{
		string sApiName;						//����ApiName���״���
		MFP_PacketHandleApi pMemberFunc;		//���Ĵ�����ָ��

	} Cmd2Api;

	//�����������뱨�Ĵ����Ա����ӳ���
	static Cmd2Api m_Cmd2Api[];

	//�ɽ�����ˮ*****************************************************************************************
	int onRecvRtnSpotMatch(CBroadcastPacket& pkt);             //Spot
	int onRecvRtnForwardMatch(CBroadcastPacket& pkt);          //Forward
	int onRecvRtnDeferMatch(CBroadcastPacket& pkt);            //Defer
	int onRecvRtnDeferDeliveryAppMatch(CBroadcastPacket& pkt); //DeferDeliveryApp�����ڽ��պ������ֶ������ﴦ����
															   //������ˮ****************************************************************************************
	int onRecvRtnSpotOrder(CBroadcastPacket& pkt);             //Spot
	int onRecvRspSpotOrder(CBroadcastPacket& pkt);
	int onRecvSpotOrder(CBroadcastPacket& pkt);                //
	int HandleSpotOrder(CBroadcastPacket& pkt, int iBroadcastID);

	int onRecvRtnForwardOrder(CBroadcastPacket& pkt);          //Forward
	int onRecvRspForwardOrder(CBroadcastPacket& pkt);
	int onRecvForwardOrder(CBroadcastPacket& pkt);             //
	int HandleForwardOrder(CBroadcastPacket& pkt, int iBroadcastID);

	int onRecvRtnDeferOrder(CBroadcastPacket& pkt);            //Defer
	int onRecvRspDeferOrder(CBroadcastPacket& pkt);
	int onRecvDeferOrder(CBroadcastPacket& pkt);            //
	int HandleDeferOrder(CBroadcastPacket& pkt, int iBroadcastID);

	// DeferDeliveryApp
	int onRecvRtnDeferDeliveryAppOrder(CBroadcastPacket& pkt);
	int onRecvRspDeferDeliveryAppOrder(CBroadcastPacket& pkt);
	int onRecvDeferDeliveryAppOrder(CBroadcastPacket& pkt);
	int HandleDeferDeliveryAppOrder(CBroadcastPacket& pkt, int iBroadcastID);

	int onRecvRtnMiddleAppOrder(CBroadcastPacket& pkt);        //MiddleApp
	int onRecvRspMiddleAppOrder(CBroadcastPacket& pkt);
	int onRecvMiddleAppOrder(CBroadcastPacket& pkt);           //
	int HandleMiddleAppOrder(CBroadcastPacket& pkt, int iBroadcastID);
	//����********************************************************************************************
	int onRecvRtnSpotOrderCancel(CBroadcastPacket& pkt);             //Spot
	int onRecvRspSpotOrderCancel(CBroadcastPacket& pkt);
	int HandleSpotOrderCancel(CBroadcastPacket& pkt, int iBroadcastID);

	int onRecvRtnForwardOrderCancel(CBroadcastPacket& pkt);          //Forward
	int onRecvRspForwardOrderCancel(CBroadcastPacket& pkt);
	int HandleForwardOrderCancel(CBroadcastPacket& pkt, int iBroadcastID);

	int onRecvRtnDeferOrderCancel(CBroadcastPacket& pkt);            //Defer
	int onRecvRspDeferOrderCancel(CBroadcastPacket& pkt);
	int HandleDeferOrderCancel(CBroadcastPacket& pkt, int iBroadcastID);

	int onRecvRtnDeferDeliveryAppOrderCancel(CBroadcastPacket& pkt); //DeferDeliveryApp
	int onRecvRspDeferDeliveryAppOrderCancel(CBroadcastPacket& pkt);
	int HandleDeferDeliveryAppOrderCancel(CBroadcastPacket& pkt, int iBroadcastID);

	int onRecvRtnMiddleAppOrderCancel(CBroadcastPacket& pkt);        //MiddleApp
	int onRecvRspMiddleAppOrderCancel(CBroadcastPacket& pkt);
	int HandleMiddleAppOrderCancel(CBroadcastPacket& pkt, int iBroadcastID);
	//************************************************************************************************
	int onNewBourseBulletin(CBroadcastPacket& pkt); //�������棬�������洰��
	int onNewMemberBulletin(CBroadcastPacket& pkt); //��������
	int onRiskNotify(CBroadcastPacket& pkt);        //����������Ϣ
	int onSysInit(CBroadcastPacket& pkt);           //��ȡ���һ�������գ�����ɽ��ͱ�����ˮ�������սᵥ������Ϣ
	int onSysStatChange(CBroadcastPacket& pkt);     //
	int onCustRiskDegreeChange(CBroadcastPacket& pkt); //

	int onSessionKey(CBroadcastPacket& pkt);        //�ڶ���ϵͳ���׶�û�ҵ�����ʱ����
	int onForceLogout(CBroadcastPacket& pkt);       //������ʾ��Ϣ���رյ�ǰ����
	int onBaseTableUpdate(CBroadcastPacket& pkt);   //û�ҵ�
	int onAcctCapitalAccess(CBroadcastPacket& pkt); //????????????????????????????
	int onCustInfoChange(CBroadcastPacket& pkt);    //?????????????????????????????
													//StateUpdate*****************************************************************************************
	int onRecvRtnSpotInstStateUpdate(CBroadcastPacket& pkt);
	int onRecvRtnForwardInstStateUpdate(CBroadcastPacket& pkt);
	int onRecvRtnDeferInstStateUpdate(CBroadcastPacket& pkt);

	// ����״̬�ı��ʱ��ͳһ���õĺ���
	int DealRecvInstStateUpdate(CBroadcastPacket& pkt, const int &iBroadcastID);

	int onRecvRtnSpotMarketStateUpdate(CBroadcastPacket& pkt);
	int onRecvRtnForwardMarketStateUpdate(CBroadcastPacket& pkt);
	int onRecvRtnDeferMarketStateUpdate(CBroadcastPacket& pkt);

	//����************************************************************************************************
	int onRecvSpotQuotation(CBroadcastPacket& pkt);
	int onRecvForwardQuotation(CBroadcastPacket& pkt);
	int onRecvDeferQuotation(CBroadcastPacket& pkt);
	int onRecvDeferDeliveryQuotation(CBroadcastPacket& pkt);

	int onRecvWindVaneQuotation(CBroadcastPacket& pkt);

	int onRecvRtnFutureQuotation(CBroadcastPacket& pkt);
public:

	int Reigister(mainWindow* pkt);


	// ��Ϣ������table
	typedef QMap<int, CBroadcaster> QMapBDR;
	QMapBDR m_mapBdr;

	void addStrategyConditionOrder(QString && id, strategy_conditionOrder &cond);
	void runStrategyConditionOrder(QString && id);
	void stopStrategyConditionOrder(QString && id);
	void deleteStrategyConditionOrder(QString && id);

	//QString getT1ProdID(QString && id);
	//QString getT2ProdID(QString && id);

	void runAllStrategyConditionOrder();

	//����-������
	QMap<QString, strategy_conditionOrder >mapStrategyConditionOrder;

	QMap<QString, strategy_conditionOrder >mapStrategyRunning;//����״̬��
	QMap<QString, strategy_conditionOrder >mapStrategyStopping;//ֹͣ״̬��

	void LoginCTP(const char *user, const char*pswd, const char *broker);
private:
	CConfigImpl*		    m_pConfig;
	bool                    m_bLoginSucceed;

private:
	CConnectPointSync* FindRoute(const QString &sCmdID);

	const QUOTATION* Translate(CBroadcastPacket& oPktSrc);
	const QUOTATION* TranslateQH(CBroadcastPacket& oPktSrc);
	int TranslateUnzipPacket(CBroadcastPacket& oPktSrc, QUOTATION& stQuotation);
	int TranslateZipPacket(CBroadcastPacket& oPktSrc, QUOTATION& stQuotation);
	int TranslateQHPacket(CBroadcastPacket& oPktSrc, QUOTATION& stQuotation);
	int DealRecvQuotation(CBroadcastPacket& pkt, const int& iBroadcastID, bool bPosi_PL = false);
	bool CheckQt(const QUOTATION& stQuotation);
	inline bool AddPrice(QVector<unsigned int> &vPrice, unsigned int dPrice);
	//�������������Ӧ·�ɽӿ�ӳ��ṹ
	typedef struct tagIfRouterCfg
	{
		QString sCmdID;
		unsigned long ulIfTo;
		CConnectPointSync* pCp;
	}IfRouterCfg;

	//�������������Ӧ·�ɽӿ�ӳ���ϵ���ñ�
	static IfRouterCfg m_tblIfRouterCfg[];

	//
	QVector<QString> m_vInvalidLocalOrderNo;

	void SwitchServer();

public:

	//int  setMainwnd(mainWindow* wnd);

	//
	bool CheckRspCode(const QString &strCode, QString &strMsg, bool bShowMsg = true);

	QString TranslateIDToValue(const QString &sTitleID, const QString &sValue);

	bool IsFloatTitle(const QString &sTitleID);

	// 
	bool InitEx();

	// ��ȡ��֤��Ҫ��ip�Ͷ˿�
	bool GetAuthenticateInfo(QString &sIP, QString &sPort);

	int TranslateZipPacketTest();

	void ClearHistoryInfo(void);

	// �жϿͻ������Ƿ��й���Ч�Ľ���
	bool HasValidTrade(void);

	void ClearCusInfo(void);

	void RecordVersionInfo(QString csServerVersion);

	void IniQuotationInsID();


	mainWindow *   m_hMain;


	/*int LoginEx();*/

	// �ٽ���
	//	CRITICAL_SECTION m_criticalSectionBroadCast;
	QMutex m_criticalSectionBroadCast;//kenny  2017/11/16

	QMutex m_BroadCast_qh;//kenny  2017/11/16
private:
	// ������������
	bool CallUpdateExe(void) const;

	QMutex	    m_csSendPkt;
	int           m_nTimeOut; // ������Ĭ�ϳ�ʱʱ��

							  // ��¼��������Ϣ
	void SetServerList(HashtableMsg &htm_server_list);
};


extern CTraderCpMgr  g_TraderCpMgr;
#endif