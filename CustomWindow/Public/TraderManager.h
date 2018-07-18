#pragma once

#include <Windows.h>
#include "../lxTraderCTP/DllTradeInterface.h"
#include "../lxTraderCTP/base/ObjectPool.h"
#include <map>
#include <mutex>
#include <algorithm>
#include<ctime>

//ֻ�����ݽӿ� �������ݽ�����
struct IEvData:public Countor
{
	virtual const eventData* ReadData() = 0;
	virtual int GetValInt(int index, const char* valname) = 0;
	virtual unsigned int GetValUInt(int index,const char* valname) = 0;
	virtual double GetValDouble(int index, const char* valname) = 0;
	virtual string GetValString(int index, const char* valname) = 0;
};
using EvDataHolder = AutoHolder<IEvData>;

//��д���ݽӿ� ��������ά����
struct IEvDataReadWrite : public IEvData
{
	virtual eventData* WriteData() = 0;
	virtual int SetValInt(int index, const char* valname, int val) = 0;
	virtual int SetValUInt(int index, const char* valname, unsigned int val) = 0;
	virtual int SetValDouble(int index, const char* valname, double val) = 0;
	virtual int SetValString(int index, const char* valname, const char* val) = 0;
};


using EvDataReadWriteHolder = AutoHolder<IEvDataReadWrite>;
//
struct ITraderHook
{
	//���Ͷ���
	virtual int AfterSendOrder(const string& accName, string strategy, orderReq& req) = 0;
	//ȡ������
	virtual int AfterCancelOrder(const string& accName, const string& orderNum) = 0;
	//�޸Ķ���
	virtual int AfterModifyOrder(const string& accName, orderModifyReq& req) = 0;

	virtual void OnSessionStatusChanged(const string& accName, __int64 cbUser, ACCOUNT_STATUS status) = 0;
	virtual void OnDataUpdate(const string& accName, EvDataReadWriteHolder data) = 0;
	virtual void OnMessage(const string& accName, MSG_TYPE mt, int num, const char* msg)=0;
};
using TraderHookMap = map<string, ITraderHook*>;

struct ITraderHandler
{
	virtual void OnSessionStatusChanged(const string& accName, __int64 cbUser, ACCOUNT_STATUS status) = 0;
	virtual void OnDataUpdate(const string& accName, EvDataHolder data) = 0;
	virtual void OnMessage(const string& accName, MSG_TYPE mt, int num, const char* msg) = 0;
};

//���⽻�׻ص��ӿڣ�����״̬ȥȡ����
//��ʱȡAS_NORMAL��AS_LOGIN
struct IVTraderHandler
{
	//���µ�¼״̬
	virtual void OnSessionStatusChanged(const string& accName,ACCOUNT_STATUS status) = 0;
	//���½���״̬
	virtual void OnMessage(const string& accName, MSG_TYPE mt, int num, const char* msg) = 0;
};

using TraderHandlerMap = map<string, ITraderHandler*>;
using TraderVHandlerMap = map<string, IVTraderHandler*>;
using AccountNameMap = map<string, int>;




////���⽻��״̬
//typedef void(*eventVSessionStatusChanged)(int sessId, __int64 cbUser, ACCOUNT_STATUS status);
//typedef struct __eventVHandler
//{
//	eventVSessionStatusChanged lpeventSessionStatusChanged;
//
//}eventVHandler;



struct SnapPrice
{

};
struct orderReqEx :public orderReq
{
	SnapPrice price;
};

class CTraderManager :public Singleton<CTraderManager>
{

	
public:
	CTraderManager();
	virtual ~CTraderManager();
	//ע���뷴ע��Hook
	bool RegHook(string hookname,ITraderHook * hook);
	bool UnRegHook(string hookname);

	//ע���뷴ע��Handler
	bool RegHandler(string handlername,ITraderHandler * hook);
	bool UnRegHandler(string handlername);

	//ע�����⽻�׽ӿھ��
	bool RegVHandler(string handlername, IVTraderHandler * hook);
	bool UnRegVHandler(string handlername);

	int LoadTraderDll(string dllname);
	//�����˺����ӻỰ
	int CreateSession(string dllname,string accName,AccountInfo& account, __int64 cbUser);
	int SessionIDList(vector<string>& sessidlist);
	int SessionStatus(const string& accName);
	int SessionOpen(const string& accName);
	int SessionClose(const string& accName);
	int SessionDel(const string& accName);
	int SessionAccountInfo(const string& accName, AccountInfo& account);
	
	int GetSessionID(const string& accName);
	string GetSessionName(int sessId);
	int SessionNameList(vector<string>& SessionNameList);

	int Recyle(eventData* data);

	//////////////////////////////////////////////////////////////////////////
	/////////////////////////////�������⽻������/////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	bool  IsVirtualExchange(const string& accName);
	int   VirtualSessionNameList(vector<string>& SessionNameList);
	int   VitualSessionIDList(vector<string>& sessidlist);
	int   VitualSessionID(const string &accName);
	int   VirtualSessionStatus(const string& accName);
	string VirtualSessionName(int& sessId);

	int   VirtualSessionOpen(const string& accName);//��������
	int   VirtualSessionClose(const string& accName);//�Ͽ�����
	int   VirtualSessionDel(const string& accName);

	int   VirtualSessionAccountInfo(const string& accName, AccountInfo& account);
	int   VirtualSendOrder(string accName, string strategy, orderReq& req);

	//����ģ�⽻����Ϣ
	int   GenarateOrder(const string &accName, orderReq& req);
	int   GenarateTrade(const string &accName, orderReq& req);
	int   GenaratePosiAndUpdate(const string &accName, orderReq& req);
	int   UpdateCapital(const string &accName, TRADEPARSEUNIT &tpu);
	
	int   UpdatePosition(const string &accName, TRADEPARSEUNIT &tpu);
	int   UpdateAccountInfo(const string &accName, TRADEPARSEUNIT &tpu);

	char* get_num_str(char* lp_char);
	static char* GetGUID(char*lp_char, size_t size);

	//ObjBufferPool<string, orderReqVirtual> m_ReqOrderBuffMap;//����ģ�⽻�׵������µ���Ϣ orderRefΪΨһ��ʶ

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	/************************************��������*************************************************/
	//���Ͷ���
	int SendOrder(const string& accName, string strategy, orderReq& req);
	//ȡ������
	int CancelOrder(const string& accName, orderCancelReq& req);
	//�޸Ķ���
	int ModifyOrder(const string& accName, orderModifyReq& req);
	//�첽��ȡ����
	int QueryData(const string& accName, eventData::EVENT_DATA_TYPE type, __int64 param, cbDataUpdate cbFunc);
	/********************************************************************************************/
	//�޸ĳֲ�Ԥ����
	int ModifyPosiPreOrder(const string& accName, orderModifyReq& req);





private:
	//���⽻����ר�ã���������淢��״̬
	void FireVSessionStatusChanged(int sessId,  ACCOUNT_STATUS status);
	void FireVMessage(int sessId, MSG_TYPE mt, int num, const char* msg);


	void FireSessionStatusChanged(int sessId, __int64 cbUser, ACCOUNT_STATUS status);
	void FireDataUpdate(int sessId, eventData* data, __int64 param);
	void FireMessage(int sessId, MSG_TYPE mt, int num, const char* msg);
private:
	static bool SliptAccName(string& src, string& accNum, string& brokerNum);
	
	//���ڴ��ݸ�CTP����Ļص��ӿ�
	static void OnSessionStatusChanged(int sessId, __int64 cbUser, ACCOUNT_STATUS status);
	static void OnDataUpdate(int sessId, eventData* data, __int64 param);
	static void OnMessage(int sessId, MSG_TYPE mt, int num, const char* msg);

	static eventHandler s_handler;

	///��ȡ����ģ������
	fnTrade_Name m_lpTradeName=nullptr;
	//��ʼ��
	fnTrade_Init m_lpTradeInit = nullptr;
	//����ʼ��
	fnTrade_Uninit m_lpTradeUninit = nullptr;
	//��������
	fnTrade_Recyle m_lpTradeRecyle = nullptr;
	//�����˺����ӻỰ
	fnTrade_CreateSession m_lpTradeCreateSession = nullptr;
	fnTrade_SessionIDList m_lpTradeSessionIDList = nullptr;
	fnTrade_SessionStatus m_lpTradeSessionStatus = nullptr;
	fnTrade_SessionOpen m_lpTradeSessionOpen = nullptr;
	fnTrade_SessionClose m_lpTradeSessionClose = nullptr;
	fnTrade_SessionDel m_lpTradSessionDel = nullptr;
	fnTrade_SessionAccountInfo m_lpTradeSessionAccountInfo = nullptr;
	//���Ͷ���
	fnTrade_SendOrder m_lpTradeSendOrder = nullptr;
	//ȡ������
	fnTrade_CancelOrder m_lpTradeCancelOrder = nullptr;
	//�޸Ķ���
	fnTrade_ModifyOrder m_lpTradeModifyOrder = nullptr;
	//�õ��˻�������Ϣ	
	//�첽��ȡ����
	fnTrade_QueryData m_lpTradeQueryData = nullptr;

	

	HMODULE  m_hModule=NULL;

	mutex m_mtxHandler;
	mutex m_mtxHook;
	mutex m_mtxAcc;

	//���⽻�����ݵ�ͬ��
	mutex m_mtxVHandler;
	mutex m_mtxVAcc;
	TraderHandlerMap m_mapHandler;
	TraderVHandlerMap m_mapVHandler;

	TraderHookMap	 m_mapHook;

	AccountNameMap  m_mapAcc;
	AccountNameMap  m_mapVAcc;


public:
	// ��ѯ��Լ��Ϣ
	vector<InstrumentInfo> m_vProdCode; //��������

	// 20170509	
	//��������
	using AccInvestorMap   = map<string, AccountInfo>;
	using AccBullMap       = map<string, ExchangeBulletin>;
	using AccInstrumentMap = map<string, InstrumentInfo>;

	//ҵ������
	using AccCapitalMap    = map<string, accountDetail>;
	using AccOrderMap      = map<string, vector<commissionOrder>>;
	using AccPosiMap       = map<string, vector<positionOrder>>;
	using AccPosiDetailMap = map<string, vector<positionOrder>>;
	using AccTransMap      = map<string, vector<transDetail>>;


	/////////���⽻��һ������/////////////////////////////////////////////////////
	using CapitalInfoMap = map<string, vector<CaptalInfo>>;

	//Ͷ������Ϣ
	AccInvestorMap      m_mapVInvestor;
	//Ͷ�����ʽ���ˮ��Ϣ
	CapitalInfoMap      m_mapVCapitalInfo;

	//��Լ��Ϣ
	AccInstrumentMap    m_mapVInstrument;
	//�˻�������Ϣ
	AccCapitalMap       m_mapVAccCapital;
	//���汨����ˮ
	AccOrderMap         m_mapVComOrder;
	//����ֲ�����
	AccPosiMap          m_mapVPosiMatch;
	//����ֲ���ϸ����
	AccPosiDetailMap    m_mapVPosiDetailMatch;
	//����ɽ���ˮ����
	AccTransMap         m_mapVTransMatch;
	//////////////////////////////////////////////////////////////////////////

	//Ͷ������Ϣ
	AccInvestorMap      m_mapInvestor;
	//����������
	AccBullMap          m_mapBull;
	//��Լ��Ϣ
	AccInstrumentMap    m_mapInstrument;
	//�˻�������Ϣ
	AccCapitalMap       m_mapAccCapital;
	//���汨����ˮ
	AccOrderMap         m_mapComOrder;
	//����ֲ�����
	AccPosiMap          m_mapPosiMatch;
	//����ֲ���ϸ����
	AccPosiDetailMap    m_mapPosiDetailMatch;
	//����ɽ���ˮ����
	AccTransMap         m_mapTransMatch;
	


private:
	//dataUpdate  kenny   �������ݸ��µ��Ӵ�����
	void AddExchangeBull(const string& accName, const eventData *data);
	void AddInvestorInfo(const string& accName, const eventData *data);
	void AddAccountDetailInfo(const string& accName,const eventData *data);
	void AddInstrumentInfo(const string& accName, const eventData *data);
	void AddCommissionOrder(const string& accName, const eventData *data);
	void AddPositionOrder(const string& accName, const eventData *data);
	void AddPositionOrderDetail(const string& accName, const eventData *data);
	void AddTransDetail(const string& accName, const eventData *data);
	
	//end


	//���������ɽ������³ֲֽ��׵ĳֲ�����
	void UpdatePosiByTransaction(const string &accname, const transDetail *trans);
	//ͳ��ӯ��������ʤ�ʵ�
	void UpdateAccByPosiDetail(const string &accname);

	//ͨ���ֲ���ϸ�����³ֲ�
	void UpdatePosiByPosiDetail(const string &accname);

	//ͨ��ί�в��ҳֲ�
	void UpdatePosiByCommiss(const string &accname);

	//ͳ�������ѣ�ӯ���ܶ��
	void UpdateAllByPosi();
	//ͳ��ȫ��
	//void UpdateAll();


};


extern  CTraderManager   *g_LxTranManager;
