#pragma once
#include <string>
#include "BroadcastPacket.h"
#include "ArrayListMsg.h"
#include "HashtableMsg.h"

using namespace std;

//----------------------------------------------��������Ex ����  --δ�ã�����
typedef struct tagOrderBaseEx
{
	bool bProcessed;                // ��־�Ƿ񱻴���
	string orderNo;					// ������ 
	string localOrderNo;			// ���ر�����
	string instID;				    // ��Լ����       
}OrderBaseEx,*POrderBaseEx;

//----------------------------------------------�������� ����
typedef struct tagOrderBase
{
	bool bProcessed;                // ��־�Ƿ񱻴���
	string orderNo;					// ������ 
	string localOrderNo;			// ���ر�����
	string instID;				    // ��Լ����       
	int amount;						// ����        
	int remainAmount;				// ʣ������  
	string status;					// ״̬
	string RspMsg;					// ��������
	string  applyTime;				// ����ʱ��
}OrderBase,*POrderBase;

//----------------------------------------------��������
// �ֻ�������Ϣ  
typedef struct tagSpotOrder : public OrderBase
{     
	string buyOrSell;				// ���׷���
	double price;					// �۸�

	string clientID;			    // �ͻ�����        
	string memberID;				// ��Ա����        
	string applyDate;				// �걨����            
	string traderID;				// ����Ա����        
	string cancelTime;				// ����ʱ��        
	string cancelID;				// ����Ա����        
	string matchType;				// ����        
	string endorseInstID;		    // ת�ú�Լ����        

	//����  TSpotOrder:�ֻ�������Ϣ �ṹ��ֵ
	int Packet2Struct(CBroadcastPacket & pkt) 
	{
		pkt.GetParameterVal("orderNo",orderNo);              // ������
		pkt.GetParameterVal("instID",instID);                // ��Լ���� (not null)
		pkt.GetParameterVal("clientID",clientID);            // �ͻ����� (not null)
		pkt.GetParameterVal("memberID",memberID);            // ��Ա���� (not null)
		pkt.GetParameterVal("buyOrSell",buyOrSell);          // �������� (not null)
		pkt.GetParameterVal("applyDate",applyDate);          // �걨����
		pkt.GetParameterVal("applyTime",applyTime);          // �걨ʱ��
		pkt.GetParameterVal("traderID",traderID);            // ����Ա���� (not null)
		pkt.GetParameterVal("price",price);                  // �۸�  (not null)
		pkt.GetParameterVal("amount",amount);                // ����  (not null)
		pkt.GetParameterVal("remainAmount",remainAmount);    // ʣ������
		pkt.GetParameterVal("cancelTime",cancelTime);        // ����ʱ��
		pkt.GetParameterVal("cancelID",cancelID);            // ����Ա����
		pkt.GetParameterVal("status",status);                // ״̬
		pkt.GetParameterVal("matchType",matchType);          // ����  (not null)
		pkt.GetParameterVal("endorseInstID",endorseInstID);  // ת�ú�Լ���� (not null)
		pkt.GetParameterVal("localOrderNo",localOrderNo);    // ���ر����� (not null)
		pkt.GetParameterVal("RspMsg",RspMsg);                // ��������
		return 0;
	}
}SpotOrder,*PSpotOrder;

// �ֻ�T+N������Զ�ڱ�����  
typedef struct tagForwardOrder : public OrderBase
{
	double  price;				    // �۸� 
	string  buyOrSell;				// ��������

	string  clientID;				// �ͻ�����     
	string  memberID;				// ��Ա����     
	string  applyDate;				// �걨����
	string  traderID;				// ����Ա����   
	string  cancelTime;				// ����ʱ��
	string  cancelID;				// ����Ա����
	string  matchType;				// ����		

	int Packet2Struct(CBroadcastPacket & pkt) 
	{
		pkt.GetParameterVal("orderNo",     orderNo);       // ������
		pkt.GetParameterVal("instID",      instID);        // ��Լ����  (not null)
		pkt.GetParameterVal("clientID",    clientID);      // �ͻ�����  (not null)
		pkt.GetParameterVal("memberID",    memberID);      // ��Ա����  (not null)
		pkt.GetParameterVal("buyOrSell",   buyOrSell);     // ��������  (not null)
		pkt.GetParameterVal("applyDate",   applyDate);     // �걨����
		pkt.GetParameterVal("applyTime",   applyTime);     // �걨ʱ��
		pkt.GetParameterVal("traderID",    traderID);      // ����Ա���� (not null)
		pkt.GetParameterVal("price",       price);         // �۸�   (not null)
		pkt.GetParameterVal("amount",      amount);        // ����  (not null)
		pkt.GetParameterVal("remainAmount",remainAmount);  // ʣ������
		pkt.GetParameterVal("cancelTime",  cancelTime);    // ����ʱ��
		pkt.GetParameterVal("cancelID",    cancelID);      // ����Ա����
		pkt.GetParameterVal("status",      status);        // ״̬
		pkt.GetParameterVal("localOrderNo",localOrderNo);  // ���ر�����  (not null)
		pkt.GetParameterVal("matchType",   matchType);     // ����  (not null)
		pkt.GetParameterVal("RspMsg",      RspMsg);        // ��������

		return 0;
	}
}ForwardOrder,*PForwardOrder;

// DeferOrder �ֻ����ڽ��ձ���  
typedef struct tagDeferOrder : public OrderBase
{        
	string buyOrSell; 				// ���׷���
	string offSetFlag;    		    // ��ƽ�ֱ�־
	double price;        	        // �۸�

	string clientID;  				// �ͻ�����         
	string memberID;  				// ��Ա���� 
	string applyDate; 				// �걨���� 
	string cancelTime;    		    // ����ʱ��
	double margin;      		    // ��֤����
	string marginType;    		    // ��֤������
	string traderID;      		    // ����Ա����
	string cancelID;     		    // ����Ա����
	string matchType;				// ����

	int Packet2Struct(CBroadcastPacket & pkt) 
	{
		pkt.GetParameterVal("orderNo",     orderNo);      // ������ (not null)
		pkt.GetParameterVal("clientID",    clientID);     // �ͻ����� (not null)
		pkt.GetParameterVal("instID",      instID);       // ��Լ���� (not null)
		pkt.GetParameterVal("memberID",    memberID);     // ��Ա���� (not null)
		pkt.GetParameterVal("buyOrSell",   buyOrSell);    // �������� (not null)
		pkt.GetParameterVal("applyDate",   applyDate);    // �걨����
		pkt.GetParameterVal("applyTime",   applyTime);    // �걨ʱ��
		pkt.GetParameterVal("offSetFlag",  offSetFlag);   // ��ƽ�ֱ�־ (not null)
		pkt.GetParameterVal("price",       price);        // �۸�   (not null)
		pkt.GetParameterVal("amount",      amount);       // ����  (not null)
		pkt.GetParameterVal("remainAmount",remainAmount); // ʣ������
		pkt.GetParameterVal("cancelTime",  cancelTime);   // ����ʱ��
		pkt.GetParameterVal("status",      status);       // ״̬
		pkt.GetParameterVal("localOrderNo",localOrderNo); // ���ر�����  (not null)
		pkt.GetParameterVal("margin",      margin);       // ��֤����
		pkt.GetParameterVal("marginType"  ,marginType);   // ��֤������  (not null)
		pkt.GetParameterVal("traderID",    traderID);     // ����Ա����  (not null)
		pkt.GetParameterVal("cancelID",    cancelID);     // ����Ա����
		pkt.GetParameterVal("matchType",   matchType);    // ����  (not null)
		pkt.GetParameterVal("RspMsg",      RspMsg);       // ��������

		return 0;
	}
}DeferOrder,*PDeferOrder;

//�ֻ����ڽ��ս����걨����  
typedef struct tagDeferDeliveryAppOrder : public OrderBase
{
	string  buyOrSell;				// ��������   

	string  applyDate;				// ��������
	string  cancelTime;				// ����ʱ��
	string  memberID;				// ��Ա����     
	string  traderID;				// ����Ա����   
	string  cancelID;				// ����Ա����
	string  clientID;				// �ͻ�����

	int Packet2Struct(CBroadcastPacket & pkt) 
	{
		pkt.GetParameterVal("orderNo",orderNo);           // �������
		pkt.GetParameterVal("clientID",clientID);         // �ͻ�����  (not null)
		pkt.GetParameterVal("instID",instID);             // ��Լ����  (not null)
		pkt.GetParameterVal("buyOrSell",buyOrSell);       // ��������  (not null)
		pkt.GetParameterVal("applyDate",applyDate);       // ��������
		pkt.GetParameterVal("applyTime",applyTime);       // ����ʱ��
		pkt.GetParameterVal("amount",amount);             // ����  (not null)
		pkt.GetParameterVal("cancelTime",cancelTime);     // ����ʱ��
		pkt.GetParameterVal("status",status);             // ����״̬
		pkt.GetParameterVal("localOrderNo",localOrderNo); // ���ر������ (not null)
		pkt.GetParameterVal("memberID",memberID);         // ��Ա����  (not null)
		pkt.GetParameterVal("traderID",traderID);         // ����Ա����  (not null)
		pkt.GetParameterVal("cancelID",cancelID);         // ����Ա����
		pkt.GetParameterVal("remainAmount",remainAmount); // ʣ������
		pkt.GetParameterVal("RspMsg",      RspMsg);       // ��������

		return 0;
	}
}DeferDeliveryAppOrder,*PDeferDeliveryAppOrder;

//�ֻ����ڽ����������걨����  
typedef struct tagMiddleAppOrder : public OrderBase
{
	string  buyOrSell;				// ��������

	string  applyDate;				// ��������
	string  cancelTime;				// ����ʱ��
	string  cancelID;				// ����Ա����
	string  traderID;				// ����Ա����
	string  clientID;				// �ͻ�����     
	string  memberID;				// ��Ա����

	int Packet2Struct(CBroadcastPacket & pkt) 
	{
		pkt.GetParameterVal("orderNo", orderNo);          // �������
		pkt.GetParameterVal("clientID",clientID);         // �ͻ����� (not null)
		pkt.GetParameterVal("instID",  instID);           // ��Լ���� (not null)
		pkt.GetParameterVal("memberID",memberID);         // ��Ա����  (not null)
		pkt.GetParameterVal("buyOrSell",buyOrSell);       // ��������  (not null)
		pkt.GetParameterVal("applyDate",applyDate);       // ��������
		pkt.GetParameterVal("applyTime",applyTime);       // ����ʱ��
		pkt.GetParameterVal("amount",   amount);          // ����  (not null)
		pkt.GetParameterVal("cancelTime",cancelTime);     // ����ʱ��
		pkt.GetParameterVal("status",    status);         // ����״̬
		pkt.GetParameterVal("localOrderNo",localOrderNo); // ���ر������ (not null)
		pkt.GetParameterVal("traderID",    traderID);     // ����Ա����  (not null)
		pkt.GetParameterVal("cancelID",    cancelID);     // ����Ա����
		pkt.GetParameterVal("remainAmount",remainAmount); // ʣ������
		pkt.GetParameterVal("RspMsg",      RspMsg);       // ��������
		return 0;
	}
}MiddleAppOrder,*PMiddleAppOrder;



// �ṹ����:onRecvRtnSpotInstStateUpdate
typedef struct tagInstState
{
	string       instID               ; //��Լ����    
	string       tradeState           ; //��Լ����״̬  
	// ���Ľ��������� -> �ṹ    onRecvDeferDeliveryQuotation
	int Packet2Struct(CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"         , instID);
		pkt.GetParameterVal("tradeState"     , tradeState);	
		return 0;
	};
}InstState,*PInstState;


//----------------------------------------------���Ľӿ� [onSysInit] ����
// �ṹ����:onSysInit
typedef struct tagSysInit
{
	string       old_exch_date        ; //ԭ��������    
	string       new_exch_date        ; //�½�������    
}SysInit,*PSysInit;


//----------------------------------------------���Ľӿ� [onSysStatChange] ����
// �ṹ����:onSysStatChange
typedef struct tagSysStat
{
	string       sys_date             ; //ϵͳ����    
	string       exch_date            ; //��������    
	string       m_sys_stat           ; //����ϵͳ״̬    m_sys_stat
	string       b_sys_stat           ; //������ϵͳ״̬    b_sys_stat
}SysStat,*PSysStat;


//----------------------------------------------���Ľӿ� [onBaseTableUpdate] ����
// �ṹ����:onBaseTableUpdate
typedef struct tagBaseTableUpdate
{
	string       table_name           ; //����    ��֧�ֵı�����bank_infobank_mer_code_infobranch_infobroker_infocode_tablefare_model_defacct_fare_detailfare_model_detailinstID_defsystem_parateller_infovariety
}BaseTableUpdate,*PBaseTableUpdate;


//----------------------------------------------���Ľӿ� [onForceLogout] ����
// �ṹ����:onForceLogout
typedef struct tagTForceLogout
{
	string       hint_msg             ; //��ʾ��Ϣ    
	string		 session_id			  ;
}TForceLogout,*PTForceLogout;


//----------------------------------------------���Ľӿ� [onNewBourseBulletin] ����
// �ṹ����:onNewBourseBulletin
typedef struct tagTNewBourseBulletin
{
	string       seq_no               ; //�������    
	string       title                ; //�������    
	string       content              ; //��������    
}TNewBourseBulletin,*PTNewBourseBulletin;


//----------------------------------------------���Ľӿ� [onNewMemberBulletin] ����
// �ṹ����:onNewMemberBulletin
typedef struct tagTNewMemberBulletin
{
	string       bulletin_id          ; //�������    
	string       title                ; //�������    
}TNewMemberBulletin,*PTNewMemberBulletin;


//----------------------------------------------���Ľӿ� [onSessionKey] ����
// �ṹ����:onSessionKey
typedef struct tagTSessionKey
{
	int          oper_flag            ; //������־    1����Ч2��ע��
	string       session_id           ; //�ỰID    
	string       session_key          ; //�Ự��Կ    
}TSessionKey,*PTSessionKey;


//----------------------------------------------���Ľӿ� [onRiskNotify] ����
// �ṹ����:onRiskNotify
typedef struct tagTRiskNotity
{
	string       acct_no              ; //�ͻ���    
	string       risk_idx1            ; //���ն�1    
	string       risk_idx2            ; //���ն�2    
	string       call_margin          ; //׷�����    
	string       exch_date            ; //��������    
	string       notify_title         ; //֪ͨ����    
	string       notify_content       ; //����֪ͨ����    

	tagTRiskNotity& operator = (const tagTRiskNotity& Other)
	{
		this->acct_no        = Other.acct_no;
		this->risk_idx1      = Other.risk_idx1;
		this->risk_idx2      = Other.risk_idx2;
		this->call_margin    = Other.call_margin;
		this->exch_date      = Other.exch_date;
		this->notify_title   = Other.notify_title;
		this->notify_content = Other.notify_content;
		return *this;
	}
}TRiskNotity,*PTRiskNotity;


//----------------------------------------------���Ľӿ� [onRecvRtnSpotInstStateUpdate] ����
// �ṹ����:onRecvRtnSpotInstStateUpdate
typedef struct tagSpotInstState
{
	string       instID               ; //��Լ����    
	char         tradeState           ; //��Լ����״̬    
}SpotInstState,*PSpotInstState;


//----------------------------------------------���Ľӿ� [onRecvRtnForwardInstStateUpdate] ����
// �ṹ����:onRecvRtnForwardInstStateUpdate
typedef struct tagForwardInstState
{
	string       instID               ; //��Լ����    
	char         tradeState           ; //��Լ����״̬    
}ForwardInstState,*PForwardInstState;


//----------------------------------------------���Ľӿ� [onRecvRtnDeferInstStateUpdate] ����
// �ṹ����:onRecvRtnDeferInstStateUpdate
typedef struct tagDeferInstState
{
	string       instID               ; //��Լ����    
	char         tradeState           ; //��Լ����״̬    
}DeferInstState,*PDeferInstState;


//----------------------------------------------���Ľӿ� [onRecvRtnSpotMarketStateUpdate] ����
// �ṹ����:onRecvRtnSpotMarketStateUpdate
typedef struct tagSpotMarketState
{
	string       marketID             ; //�г�����    
	char         marketState          ; //�г�����״̬    
}SpotMarketState,*PSpotMarketState;


//----------------------------------------------���Ľӿ� [onRecvRtnForwardMarketStateUpdate] ����
// �ṹ����:onRecvRtnForwardMarketStateUpdate
typedef struct tagForwardMarketState
{
	string       marketID             ; //�г�����    
	char         marketState          ; //�г�����״̬    
}ForwardMarketState,*PForwardMarketState;


//----------------------------------------------���Ľӿ� [onRecvRtnDeferMarketStateUpdate] ����
// �ṹ����:onRecvRtnDeferMarketStateUpdate
typedef struct tagDeferMarketState
{
	string       marketID             ; //�г�����    
	char         marketState          ; //�г�����״̬    
}DeferMarketState,*PDeferMarketState;


//----------------------------------------------���Ľӿ� [onAcctCapitalAccess] ����
// �ṹ����:onAcctCapitalAccess
typedef struct tagAcctCapitalAccess
{
	string       fund_src_type        ; //�ʽ���Դ����    fund_src_type
	string       serial_no            ; //������ˮ��    
	string       acct_no              ; //�ͻ���    
	int          access_way           ; //��ȡ����    ���뷽��access_way
	double       amount               ; //ת�˽��    
}AcctCapitalAccess,*PAcctCapitalAccess;


//----------------------------------------------���Ľӿ� [onCustInfoChange] ����
// �ṹ����:onCustInfoChange
typedef struct tagCustInfoChange
{
	int          update_flag          ; //���ı�־    1������2���޸�3��ɾ��
	string       acct_no              ; //�ͻ���    
	string       member_id            ; //��Ա���    
	string       cust_abbr            ; //�ͻ����    
	string       m_Fare_model_id      ; //��Ա����ģ��ID    
	string       b_Fare_model_id      ; //����������ģ��ID    
	string       acct_type            ; //�˻�����    acct_type
	string       acct_stat            ; //�˻�״̬    
	string       branch_ID            ; //�����������    
}CustInfoChange,*PCustInfoChange;


//----------------------------------------------���Ľӿ� [onCustRiskDegreeChange] ����
// �ṹ����:onCustRiskDegreeChange
typedef struct tagCustRiskDegreeChange
{
	int          oper_flag            ; //������־    1���㲥
	string       risk_degree1         ; //���ն�1    
	string       risk_degree2         ; //���ն�2    
	string       risk_grade           ; //���յȼ�    
}CustRiskDegreeChange,*PCustRiskDegreeChange;


typedef struct tagRspMsg
{        
	string RspCode;					///������        
	string RspMsg;					///��������
}RspMsg,*PRspMsg;
		


//�ֻ���������  
typedef struct tagSpotOrderCancel
{
	string  orderNo;				//������         (not null)
	string  instID;					//��Լ����        (not null)
	string  clientID;				//�ͻ�����       (not null)
	string  memberID;				//��Ա����         (not null)
	string  traderID;				//����Ա����      (not null)
}SpotOrderCancel,*PSpotOrderCancel;

// ����ͳһ�ṹ add by xiaorensong
typedef struct tagOrderCancel
{
	string  orderNo;				// ������
	string  localOrderNo;
	string  instID;				    // ��Լ����
	int     amount;                 // �ܱ�����
	int     remainAmount;           // δ�ɽ���
	double  price;					// �۸�
	string  buyOrSell;
	string  offSetFlag;

	int Packet2Struct(CBroadcastPacket & pkt) 
	{
		pkt.GetParameterVal("orderNo",orderNo);
		pkt.GetParameterVal("localOrderNo",localOrderNo);
		if(localOrderNo.empty()) // ���ڽ�����ճ�����ʱ���͹�����keyΪlocalOrderID������
		{
			pkt.GetParameterVal("localOrderID",localOrderNo);
		}
		pkt.GetParameterVal("instID",instID);
		pkt.GetParameterVal("amount",amount);
		pkt.GetParameterVal("remainAmount",remainAmount);
		pkt.GetParameterVal("price",price);
		pkt.GetParameterVal("buyOrSell",buyOrSell);
		pkt.GetParameterVal("offSetFlag",offSetFlag);

		return 0;
	}
}OrderCancel,*POrderCancel;

//�ֻ��ɽ�����Ϣ  
typedef struct tagSpotMatch
{
	string  matchNo;				// �ɽ����
	string  buyOrSell;				// ��������
	string  clientID;				// �ͻ�����
	string  clientType;				// �ͻ�����
	string  memberID;				// ��Ա����
	string  instID;				    // ��Լ����
	string  matchDate;				// �ɽ�����
	string  matchTime;				// �ɽ�ʱ��
	double  price;				    // �۸�
	int     volume;				    // ����
	string  orderNo;				// ϵͳ������
	string  localOrderNo;		    // �������ر��

	string  matchType;				// ����

	static int Packet2Struct(tagSpotMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.matchNo );
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.clientType);
		pkt.GetParameterVal("memberID"          , stBody.memberID);
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("matchDate"         , stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.price);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("orderNo"           , stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.localOrderNo);
		pkt.GetParameterVal("matchType"         , stBody.matchType);

		return 0;
	};
}SpotMatch,*PSpotMatch;




//�ֻ����ڽ��ճ�������  
typedef struct tagDeferOrderCancel
{
	string  orderNo;				//������             (not null)
	string  instID;					//��Լ����             (not null)
	string  clientID;				//�ͻ�����           (not null)
	string  memberID;				//��Ա����            (not null)
	string  traderID;				//����Ա����           (not null)
}DeferOrderCancel,*PDeferOrderCancel;

//�ֻ����ڽ��ճɽ���  
typedef struct tagDeferMatch
{
	string  localOrderNo;		    // �������ر��
	string  matchNo;				// �ɽ����
	string  orderNo;				// ϵͳ������
	string  instID;				    // ��Լ����
	double  price;				    // �۸�
	int     volume;				    // ����
	string  buyOrSell;				// ��������
	string  offsetFlag;				// ��ƽ��־
	
	string  matchDate;				// �ɽ�����
	string  matchTime;				// �ɽ�ʱ��
	string  clientID;				// �ͻ�����
	string  clientType;				// �ͻ�����
	string  memberID;				// ��Ա����

	string sExchTypeCode;

	static int Packet2Struct(tagDeferMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.matchNo);
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.clientType);
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.memberID);
		pkt.GetParameterVal("matchDate"         , stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.price);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("offSetFlag"        , stBody.offsetFlag);
		pkt.GetParameterVal("orderNo"           , stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.localOrderNo);

		return 0;
	};
}DeferMatch,*PDeferMatch;



//�ֻ����ڽ��ս����걨��������  
typedef struct tagDeferDeliveryAppOrderCancel
{
	string  orderNo;				//������               (not null)
	string  instID;				//��Լ����              (not null)
	string  clientID;				//�ͻ�����             (not null)
	string  memberID;				//��Ա����		(not null)
	string  traderID;				//����Ա����       (not null)
}DeferDeliveryAppOrderCancel,*PDeferDeliveryAppOrderCancel;

//���ӽ����걨�ɽ���  
typedef struct tagDeferDeliveryAppMatch
{
	string  orderNo;				// ������
	string  LocalOrderNo;			// �������ر��
	string  matchNo;				// �ɽ����
	string  instID;				    // ��Լ����
	int     volume;				    // ����
	string  buyOrSell;				// ��������
	string  middleFlag;				// �Ƿ�Ϊ������

	string  matchDate;				// �ɽ�����
	string  matchTime;				// �ɽ�ʱ��
	string  clientID;				// �ͻ�����
	string  memberID;				// ��Ա����

	static int Packet2Struct(tagDeferDeliveryAppMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.matchNo);
		pkt.GetParameterVal("clientID"          , stBody.clientID);
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.memberID);
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("matchDate"         , stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.matchTime);
		pkt.GetParameterVal("orderNo"           , stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.LocalOrderNo);
		pkt.GetParameterVal("middleFlag"        , stBody.middleFlag);

		return 0;
	};
}DeferDeliveryAppMatch,*PDeferDeliveryAppMatch;



//�ֻ����ڽ����������걨��������  
typedef struct tagMiddleAppOrderCancel
{
	string  orderNo;				//������          (not null)
	string  instID;				//��Լ����         (not null)
	string  clientID;				//�ͻ�����        (not null)
	string  memberID;				//��Ա����        (not null)
	string  traderID;				//����Ա����      (not null)
}MiddleAppOrderCancel,*PMiddleAppOrderCancel;



//�ֻ�T+N��������  
typedef struct tagForwardOrderCancel
{                                                                           
	string  orderNo;				//������            (not null)
	string  instID;				//��Լ����           (not null)
	string  clientID;				//�ͻ�����          (not null)
	string  memberID;				//��Ա����          (not null)
	string  traderID;				//����Ա����        (not null)
}ForwardOrderCancel,*PForwardOrderCancel;

//�ֻ�T+N�ɽ���  
typedef struct tagForwardMatch
{
	string  matchNo;				// �ɽ����
	string  buyOrSell;				// ��������
	string  clientID;				// �ͻ�����
	string  clientType;				// �ͻ�����
	string  memberID;				// ��Ա����
	string  instID;				    // ��Լ����
	string  matchDate;				// �ɽ�����
	string  matchTime;				// �ɽ�ʱ��
	double  price;				    // �۸�
	int     volume;				    // ����
	string  orderNo;				// ϵͳ������
	string  localOrderNo;			// �������ر��
	string  marginRate;				// ��֤����
	string  rateType;				// ��֤������

	static int Packet2Struct(tagForwardMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.matchNo);
		pkt.GetParameterVal("buyOrSell"         , stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.clientType);
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.memberID);
		pkt.GetParameterVal("matchDate"         , stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.price);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("marginRate"        , stBody.marginRate);
		pkt.GetParameterVal("rateType"          , stBody.rateType);
		pkt.GetParameterVal("orderNo"           , stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.localOrderNo);

		return 0;
	};
}ForwardMatch,*PForwardMatch;

//�ֻ����ڽ��ղ���������Ϣ  
typedef struct tagDeferFeeRate
{
	string  effectDate;				//����
	string  instID;				//��Լ����
	string  payDirection;				//֧������
	double  feeRate;				//���ӷ���
}DeferFeeRate,*PDeferFeeRate;

//�ֻ�����  
typedef struct tagSpotQuotation
{
	string  instID;				//��Լ����
	string  name;				//��Լ����
	double  lastClose;		    //������
	double  open;				//���̼�
	double  high;				//��߼�
	double  low;				//��ͼ�
	double  last;				//���¼�
	double  close;				//���̼�
	double  bid1;				//���1
	int  bidLot1;				//����1
	double  bid2;				//���2
	int  bidLot2;				//����2
	double  bid3;				//���3
	int  bidLot3;				//����3
	double  bid4;				//���4
	int  bidLot4;				//����4
	double  bid5;				//���5
	int  bidLot5;				//����5
	double  ask1;				//����1
	int  askLot1;				//����1
	double  ask2;				//����2
	int  askLot2;				//����2
	double  ask3;				//����3
	int  askLot3;				//����3
	double  ask4;				//����4
	int  askLot4;				//����4
	double  ask5;				//����5
	int  askLot5;				//����5
	int  volume;				//�ɽ�����˫�ߣ�
	double  weight;				//�ɽ���˫�ߣ�����
	double  highLimit;				//��ͣ��
	double  lowLimit;				//��ͣ��
	double  upDown;				//�ǵ�
	double  upDownRate;				//�ǵ�����
	double  turnOver;				//�ɽ���
	double  average;				//����
	string  quoteDate;				//��������
	string  quoteTime;				//����ʱ��
	int  sequenceNo;				//�������,ÿ���1��ʼ����
	string sZipBuff;				//ѹ��
    
	tagSpotQuotation& operator = (const tagSpotQuotation& Other)
	{
		this->instID    = Other.instID;
		this->name      = Other.name;
		this->lastClose = Other.lastClose;
		this->open = Other.open;
		this->high = Other.high;
		this->low = Other.low;
		this->last = Other.last;
		this->close = Other.close;
		this->bid1 = Other.bid1;
		this->bidLot1 = Other.bidLot1;
		this->bid2 = Other.bid2;
		this->bidLot2 = Other.bidLot2;
		this->bid3 = Other.bid3;
		this->bidLot3 = Other.bidLot3;
		this->bid4 = Other.bid4;
		this->bidLot4 = Other.bidLot4;
		this->bid5 = Other.bid5;
		this->bidLot5 = Other.bidLot5;
		this->ask1 = Other.ask1;
		this->askLot1 = Other.askLot1;
		this->ask2 = Other.ask2;
		this->askLot2 = Other.askLot2;
		this->ask3 = Other.ask3;
		this->askLot3 = Other.askLot3;
		this->ask4 = Other.ask4;
		this->askLot4 = Other.askLot4;
		this->ask5 = Other.ask5;
		this->askLot5 = Other.askLot5;
		this->volume = Other.volume;
		this->weight = Other.weight;
		this->highLimit = Other.highLimit;
		this->lowLimit = Other.lowLimit;
		this->upDown = Other.upDown;
		this->upDownRate = Other.upDownRate;
		this->turnOver = Other.turnOver;
		this->average = Other.average;
		this->quoteDate = Other.quoteDate;
		this->quoteTime = Other.quoteTime;
		this->sequenceNo = Other.sequenceNo;
		this->sZipBuff = Other.sZipBuff;

		return *this;
	}
}SpotQuotation,*PSpotQuotation;
    
//�ֻ����ڽ�������  
typedef struct tagDeferQuotation
{
	string  instID;				//��Լ����
	string  name;				//��Լ����
	double  lastSettle;				//�����
	double  lastClose;				//������
	double  open;				//���̼�
	double  high;				//��߼�
	double  low;				//��ͼ�
	double  last;				//���¼�
	double  close;				//���̼�
	double  settle;				//�����
	double  bid1;				//���1
	int  bidLot1;				//����1
	double  bid2;				//���2
	int  bidLot2;				//����2
	double  bid3;				//���3
	int  bidLot3;				//����3
	double  bid4;				//���4
	int  bidLot4;				//����4
	double  bid5;				//���5
	int  bidLot5;				//����5
	double  ask1;				//����1
	int  askLot1;				//����1
	double  ask2;				//����2
	int  askLot2;				//����2
	double  ask3;				//����>3
	int  askLot3;				//����3
	double  ask4;				//����4
	int  askLot4;				//����4
	double  ask5;				//����5
	int  askLot5;				//����5
	int  volume;				//�ɽ���
	double  weight;				//�ɽ���˫�ߣ�����
	double  highLimit;				//��ͣ��
	double  lowLimit;				//��ͣ��
	int  Posi;				//�ֲ���
	double  upDown;				//�ǵ�
	double  upDownRate;				//�ǵ�����
	double  turnOver;				//�ɽ���
	double  average;				//����
	string  quoteDate;				//��������
	string  quoteTime;				//����ʱ��
	int  sequenceNo;				//�������
	string sZipBuff;				//ѹ��

	tagDeferQuotation& operator = (const tagDeferQuotation& Other)
	{
		this->instID    = Other.instID;
		this->name      = Other.name;
		this->lastClose = Other.lastClose;
		this->open = Other.open;
		this->high = Other.high;
		this->low = Other.low;
		this->last = Other.last;
		this->close = Other.close;
		this->bid1 = Other.bid1;
		this->bidLot1 = Other.bidLot1;
		this->bid2 = Other.bid2;
		this->bidLot2 = Other.bidLot2;
		this->bid3 = Other.bid3;
		this->bidLot3 = Other.bidLot3;
		this->bid4 = Other.bid4;
		this->bidLot4 = Other.bidLot4;
		this->bid5 = Other.bid5;
		this->bidLot5 = Other.bidLot5;
		this->ask1 = Other.ask1;
		this->askLot1 = Other.askLot1;
		this->ask2 = Other.ask2;
		this->askLot2 = Other.askLot2;
		this->ask3 = Other.ask3;
		this->askLot3 = Other.askLot3;
		this->ask4 = Other.ask4;
		this->askLot4 = Other.askLot4;
		this->ask5 = Other.ask5;
		this->askLot5 = Other.askLot5;
		this->volume = Other.volume;
		this->weight = Other.weight;
		this->highLimit = Other.highLimit;
		this->lowLimit = Other.lowLimit;
		this->upDown = Other.upDown;
		this->upDownRate = Other.upDownRate;
		this->turnOver = Other.turnOver;
		this->average = Other.average;
		this->quoteDate = Other.quoteDate;
		this->quoteTime = Other.quoteTime;
		this->sequenceNo = Other.sequenceNo;
		this->sZipBuff = Other.sZipBuff;

		return *this;
	}
}DeferQuotation,*PDeferQuotation;


// ����ͳһ�ṹ
typedef struct	tagBidAskUnit
{ 
	tagBidAskUnit()
	{
		m_uiVol = 0;
		m_uiPrice = 0;
	}
	unsigned int m_uiVol;		//ί��
	unsigned int m_uiPrice;	    //ί��
} BID_ASK_UNIT,*PBID_ASK_UNIT;

struct QUOTATION
{
	string  instID;				//��Լ����
	string  name;				//��Լ����

	QUOTATION()
	{
		m_uilastClose = 0;
		m_uiLastSettle = 0;
		m_uiSettle = 0;
		m_uiOpenPrice = 0;
		m_uiHigh = 0;
		m_uiLow = 0;
		m_uiClose = 0;
		m_uiHighLimit = 0;
		m_uiLowLimit = 0;
		m_uiLast = 0;
		m_uiAverage = 0;
		m_uiVolume = 0;
		m_uiWeight = 0;
		m_uiTurnOver = 0;
		m_uiChiCangLiang = 0;
		m_uiLastChiCangLiang = 0;
        m_uiUpDown = 0;
        m_dUpDownRate = 0;

		m_Bid[0].m_uiPrice = 0;

		memset(m_Bid, 0, sizeof(BID_ASK_UNIT));
		memset(m_Ask, 0, sizeof(BID_ASK_UNIT));
	}

	unsigned int m_uiSeqNo;     //����
	unsigned int m_uiDate;
	unsigned int m_uiTime; 
	unsigned int m_uilastClose; //����
	unsigned int m_uiLastSettle;//���
	unsigned int m_uiSettle;    //����
	unsigned int m_uiOpenPrice; //����
	unsigned int m_uiHigh;      //��߼�
	unsigned int m_uiLow;       //��ͼ�
	unsigned int m_uiClose;     //���̼�
	unsigned int m_uiHighLimit;
	unsigned int m_uiLowLimit;	
	unsigned int m_uiLast;      //���¼�
	unsigned int m_uiAverage;   //����
	unsigned int m_uiVolume;    //�ɽ���
	unsigned int m_uiWeight;    //�ɽ�����
	//unsigned int m_uiTurnOver;  //�ɽ����
	UINT64 m_uiTurnOver;  //�ɽ����
	unsigned int m_uiChiCangLiang; //�ֲ���
	unsigned int m_uiLastChiCangLiang;//���ճֲ���
	int m_uiUpDown;       // �ǵ�
	double m_dUpDownRate;   // �ǵ�����
	BID_ASK_UNIT     m_Bid[10];//����۸�
	BID_ASK_UNIT     m_Ask[10];//�����۸�

	string Key() const
	{
		return instID;
	}
	void Decode(const char* pBuf, unsigned int uiSize)
	{
		*this = *(QUOTATION*)(pBuf);
	}
	const char* Encode(unsigned int & uiLen)
	{
		uiLen = sizeof(QUOTATION);
		return (const char*)(this);
	}

	bool IsValidate( unsigned int uiPrice ) const
	{
		if( m_uiLowLimit > 0 && uiPrice >= m_uiLowLimit && m_uiHighLimit >= uiPrice )
			return true;
		else
			return false;
	}

	// ��ȡ���㸡��ӯ���ļ۸�
	UINT GetCalSurplusPrice() const
	{
		// ������¼�û����������
		return m_uiLast > 0 ? m_uiLast : m_uiLastSettle;
	}

} /*QUOTATION,*PQUOTATION*/;

    
//���ӽ�������  
typedef struct tagDeferDeliveryQuotation
{
	string  instID;				//��Լ����
	int  bidLot;				//����
	int  askLot;				//����
	int  midBidLot;				//����������
	int  midAskLot;				//����������

	int Packet2Struct(CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"         , instID);
		pkt.GetParameterVal("bidLot"         , bidLot);
		pkt.GetParameterVal("askLot"         , askLot);
		pkt.GetParameterVal("midBidLot"      , midBidLot);
		pkt.GetParameterVal("midAskLot"      , midAskLot);		
		return 0;
	};
}DeferDeliveryQuotation,*PDeferDeliveryQuotation;


//�ֻ�T+N����  
typedef struct tagForwardQuotation
{
	string  instID;				//��Լ����
	string  name;				//��Լ����
	double  lastSettle;				//�����
	double  lastClose;				//������
	double  open;				//���̼�
	double  high;				//��߼�
	double  low;				//��ͼ�
	double  last;				//���¼�
	double  close;				//���̼�
	double  settle;				//�����
	double  bid1;				//���1
	int  bidLot1;				//����1
	double  bid2;				//���2
	int  bidLot2;				//����2
	double  bid3;				//���3
	int  bidLot3;				//����3
	double  bid4;				//���4
	int  bidLot4;				//����4
	double  bid5;				//���5
	int  bidLot5;				//����5
	double  ask1;				//����1
	int  askLot1;				//����1
	double  ask2;				//����2
	int  askLot2;				//����2
	double  ask3;				//����>3
	int  askLot3;				//����3
	double  ask4;				//����4
	int  askLot4;				//����4
	double  ask5;				//����5
	int  askLot5;				//����5
	int  volume;				//�ɽ���
	double  weight;				//�ɽ���˫�ߣ�����
	double  highLimit;				//��ͣ��
	double  lowLimit;				//��ͣ��
	int  Posi;				//�ֲ���
	double  upDown;				//�ǵ�
	double  upDownRate;				//�ǵ�����
	double  turnOver;				//�ɽ���
	double  average;				//����
	string  quoteDate;				//��������
	string  quoteTime;				//����ʱ��
	int  sequenceNo;				//�������
	string sZipBuff;				//ѹ��

	tagForwardQuotation& operator = (const tagForwardQuotation& Other)
	{
		this->instID    = Other.instID;
		this->name      = Other.name;
		this->lastClose = Other.lastClose;
		this->open = Other.open;
		this->high = Other.high;
		this->low = Other.low;
		this->last = Other.last;
		this->close = Other.close;
		this->bid1 = Other.bid1;
		this->bidLot1 = Other.bidLot1;
		this->bid2 = Other.bid2;
		this->bidLot2 = Other.bidLot2;
		this->bid3 = Other.bid3;
		this->bidLot3 = Other.bidLot3;
		this->bid4 = Other.bid4;
		this->bidLot4 = Other.bidLot4;
		this->bid5 = Other.bid5;
		this->bidLot5 = Other.bidLot5;
		this->ask1 = Other.ask1;
		this->askLot1 = Other.askLot1;
		this->ask2 = Other.ask2;
		this->askLot2 = Other.askLot2;
		this->ask3 = Other.ask3;
		this->askLot3 = Other.askLot3;
		this->ask4 = Other.ask4;
		this->askLot4 = Other.askLot4;
		this->ask5 = Other.ask5;
		this->askLot5 = Other.askLot5;
		this->volume = Other.volume;
		this->weight = Other.weight;
		this->highLimit = Other.highLimit;
		this->lowLimit = Other.lowLimit;
		this->upDown = Other.upDown;
		this->upDownRate = Other.upDownRate;
		this->turnOver = Other.turnOver;
		this->average = Other.average;
		this->quoteDate = Other.quoteDate;
		this->quoteTime = Other.quoteTime;
		this->sequenceNo = Other.sequenceNo;
		this->sZipBuff = Other.sZipBuff;

		return *this;
	}
}ForwardQuotation,*PForwardQuotation;

//----------------------------------------------���Ľӿ� [onRecvRtnSpotMatch] ����
// �ṹ����:onRecvRtnSpotMatch
typedef struct tagPktSpotMatch
{
	SpotMatch    stBody   						; //�ֻ��ɽ�����Ϣ
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}PktSpotMatch,*PPktSpotMatch;



//----------------------------------------------���Ľӿ� [onRecvRtnForwardMatch] ����
// �ṹ����:onRecvRtnForwardMatch
typedef struct tagPktForwardMatch
{
	ForwardMatch	stBody							; //�ֻ�T+N�ɽ���    
	string       acctNo               ; //�ͻ��� 
	RspMsg			 stRsp								; //������Ϣ   
}PktForwardMatch,*PPktForwardMatch;



//----------------------------------------------���Ľӿ� [onRecvRtnDeferMatch] ����
// �ṹ����:onRecvRtnDeferMatch
typedef struct tagPktDeferMatch
{
	DeferMatch	 stBody 							; //�ֻ����ڽ��ճɽ���   
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ   
}PktDeferMatch,*PPktDeferMatch;



//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppMatch] ����
// �ṹ����:onRecvRtnDeferDeliveryAppMatch
typedef struct tagPktDeferDeliveryAppMatch
{
	DeferDeliveryAppMatch	stBody			; //���ӽ����걨�ɽ���   
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}PktDeferDeliveryAppMatch,*PPktDeferDeliveryAppMatch;

//----------------------------------------------���Ľӿ� [onRecvRspSpotOrder] ����
// �ṹ����:onRecvRspSpotOrder
typedef struct tagRspSpotOrder
{
	SpotOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspSpotOrder,*PRspSpotOrder;

//----------------------------------------------���Ľӿ� [onRecvRtnSpotOrder] ����
// �ṹ����:onRecvRtnSpotOrder
typedef struct tagRtnSpotOrder
{
	SpotOrder				stBody						; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnSpotOrder,*PRtnSpotOrder;

//----------------------------------------------���Ľӿ� [onRecvRspSpotOrderCancel] ����
// �ṹ����:onRecvRspSpotOrderCancel
typedef struct tagRspSpotOrderCancel
{
	SpotOrderCancel				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspSpotOrderCancel,*PRspSpotOrderCancel; 

//----------------------------------------------���Ľӿ� [onRecvRtnSpotOrderCancel] ����
// �ṹ����:onRecvRtnSpotOrderCancel
typedef struct tagRtnSpotOrderCancel
{
	SpotOrder				stBody						; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnSpotOrderCancel,*PRtnSpotOrderCancel;

//----------------------------------------------���Ľӿ� [onRecvRspDeferOrder] ����
// �ṹ����:onRecvRspDeferOrder
typedef struct tagRspDeferOrder
{
	DeferOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspDeferOrder,*PRspDeferOrder;     
 
//----------------------------------------------���Ľӿ� [onRecvRtnDeferOrder] ����
// �ṹ����:onRecvRtnDeferOrder
typedef struct tagRtnDeferOrder
{
	DeferOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnDeferOrder,*PRtnDeferOrder;

//----------------------------------------------���Ľӿ� [onRecvRspDeferOrderCancel] ����
// �ṹ����:onRecvRspDeferOrderCancel
typedef struct tagRspDeferOrderCancel
{
	DeferOrderCancel				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspDeferOrderCancel,*PRspDeferOrderCancel; 

//----------------------------------------------���Ľӿ� [onRecvRtnDeferOrderCancel] ����
// �ṹ����:onRecvRtnDeferOrderCancel
typedef struct tagRtnDeferOrderCancel
{
	DeferOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnDeferOrderCancel,*PRtnDeferOrderCancel;

//----------------------------------------------���Ľӿ� [onRecvRspDeferDeliveryAppOrder] ����
// �ṹ����:onRecvRspDeferDeliveryAppOrder
typedef struct tagRspDeferDeliveryAppOrder
{
	DeferDeliveryAppOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspDeferDeliveryAppOrder,*PRspDeferDeliveryAppOrder;  


//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppOrder] ����
// �ṹ����:onRecvRtnDeferDeliveryAppOrder
typedef struct tagRtnDeferDeliveryAppOrder
{
	DeferDeliveryAppOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnDeferDeliveryAppOrder,*PRtnDeferDeliveryAppOrder;

//----------------------------------------------���Ľӿ� [onRecvRspDeferDeliveryAppOrderCancel] ����
// �ṹ����:onRecvRspDeferDeliveryAppOrderCancel
typedef struct tagRspDeferDeliveryAppOrderCancel
{
	DeferDeliveryAppOrderCancel				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspDeferDeliveryAppOrderCancel,*PRspDeferDeliveryAppOrderCancel;   

//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppOrderCancel] ����
// �ṹ����:onRecvRtnDeferDeliveryAppOrderCancel
typedef struct tagRtnDeferDeliveryAppOrderCancel
{
	DeferDeliveryAppOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnDeferDeliveryAppOrderCancel,*PRtnDeferDeliveryAppOrderCancel;  
 
//----------------------------------------------���Ľӿ� [onRecvRspMiddleAppOrder] ����
// �ṹ����:onRecvRspMiddleAppOrder
typedef struct tagRspMiddleAppOrder
{
	MiddleAppOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspMiddleAppOrder,*PRspMiddleAppOrder; 

//----------------------------------------------���Ľӿ� [onRecvRtnMiddleAppOrder] ����
// �ṹ����:onRecvRtnMiddleAppOrder
typedef struct tagRtnMiddleAppOrder
{
	MiddleAppOrder				stBody			; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnMiddleAppOrder,*PRtnMiddleAppOrder;

//----------------------------------------------���Ľӿ� [onRecvRspMiddleAppOrderCancel] ����
// �ṹ����:onRecvRspMiddleAppOrderCancel
typedef struct tagRspMiddleAppOrderCancel
{
	MiddleAppOrderCancel				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspMiddleAppOrderCancel,*PRspMiddleAppOrderCancel;  
   
//----------------------------------------------���Ľӿ� [onRecvRtnMiddleAppOrderCancel] ����
// �ṹ����:onRecvRtnMiddleAppOrderCancel
typedef struct tagRtnMiddleAppOrderCancel
{
	MiddleAppOrder	stBody						; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnMiddleAppOrderCancel,*PRtnMiddleAppOrderCancel;      
    

//----------------------------------------------���Ľӿ� [onRecvRtnForwardOrder] ����
// �ṹ����:onRecvRtnForwardOrder
typedef struct tagRtnForwardOrder
{
	ForwardOrder				stBody				; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnForwardOrder,*PRtnForwardOrder;
  
//----------------------------------------------���Ľӿ� [onRecvRspForwardOrder] ����
// �ṹ����:onRecvRspForwardOrder
typedef struct tagRspForwardOrder
{
	ForwardOrder				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspForwardOrder,*PRspForwardOrder; 

//----------------------------------------------���Ľӿ� [onRecvRspForwardOrderCancel] ����
// �ṹ����:onRecvRspForwardOrderCancel
typedef struct tagRspForwardOrderCancel
{
	ForwardOrderCancel				stBody					; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RspForwardOrderCancel,*PRspForwardOrderCancel; 
       
//----------------------------------------------���Ľӿ� [onRecvRtnForwardOrderCancel] ����
// �ṹ����:onRecvRtnForwardOrderCancel
typedef struct tagRtnForwardOrderCancel
{
	ForwardOrder				stBody				; //    
	string       acctNo               ; //�ͻ���    
	RspMsg			 stRsp								; //������Ϣ
}RtnForwardOrderCancel,*PRtnForwardOrderCancel;

//----------------------------------------------���Ľӿ� [onRecvRtnForwardOrderCancel] ����
// �ṹ����:onRecvRtnForwardOrderCancel
typedef struct tagWindVane
{
	//string        serial_no		   ; // ������ˮ��  ���������ж�Ӧ������������ˮ�� 
	string        prod_code            ; // ��Լ���� Ŀǰֻ��Au(T+D)��Ag(T+D)    
	string        memo                 ; // ��ע�� ��ϸ�������漰��ע����ʾ�ͻ����α�ע
	string        moreStorPer          ; // ���ռ����
	string        openMoreStorAvg      ; // ����־���
	string        haveMoreStorAvg      ; // �ֶ�־���
	string        haveMoreStorPer      ; // �ֶ�ֱ���
	string        nullStorPer          ; // �ղ�ռ����
	string        openNullStorAvg      ; // ���ղ־���
	string        haveNullStorAvg      ; // �ֿղ־���
	string        haveNullStorPer      ; // �ֿղֱ���
	string        lookPer              ; // ����ռ���� 
	//RspMsg		  stRsp				   ; // ������Ϣ

	// ���Ľ��������� -> �ṹ    onRecvDeferDeliveryQuotation
	int Packet2Struct(CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("prod_code"         , prod_code);
		pkt.GetParameterVal("memo"         , memo);
		pkt.GetParameterVal("moreStorPer"         , moreStorPer);
		pkt.GetParameterVal("openMoreStorAvg"         , openMoreStorAvg);
		pkt.GetParameterVal("haveMoreSotrAvg"         , haveMoreStorAvg);
		pkt.GetParameterVal("haveMoreStorPer"         , haveMoreStorPer);
		pkt.GetParameterVal("nullStorPer"         , nullStorPer);
		pkt.GetParameterVal("openNullStorAvg"         , openNullStorAvg);
		pkt.GetParameterVal("haveNullStorAvg"         , haveNullStorAvg);
		pkt.GetParameterVal("haveNullStorPer"         , haveNullStorPer);
		pkt.GetParameterVal("lookPer"         , lookPer);
		return 0;
	};
}WindVane,*PWindVane;


class CBroadcastPacketAndStruct
{
public:
	//----------------------------------------------���Ľӿ� [onSysInit] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onSysInit
	static int Packet2Struct(SysInit& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("old_exch_date"     , stBody.old_exch_date);
		pkt.GetParameterVal("new_exch_date"     , stBody.new_exch_date);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onSysInit
	static int Struct2Packet(SysInit& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("old_exch_date"     , stBody.old_exch_date);
		pkt.AddParameter("new_exch_date"     , stBody.new_exch_date);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onSysStatChange] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onSysStatChange
	static int Packet2Struct(SysStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("sys_date"          , stBody.sys_date);
		pkt.GetParameterVal("exch_date"         , stBody.exch_date);
		pkt.GetParameterVal("m_sys_stat"        , stBody.m_sys_stat);
		pkt.GetParameterVal("b_sys_stat"        , stBody.b_sys_stat);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onSysStatChange
	static int Struct2Packet(SysStat& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("sys_date"          , stBody.sys_date);
		pkt.AddParameter("exch_date"         , stBody.exch_date);
		pkt.AddParameter("m_sys_stat"        , stBody.m_sys_stat);
		pkt.AddParameter("b_sys_stat"        , stBody.b_sys_stat);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onBaseTableUpdate] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onBaseTableUpdate
	static int Packet2Struct(BaseTableUpdate& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("table_name"        , stBody.table_name);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onBaseTableUpdate
	static int Struct2Packet(BaseTableUpdate& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("table_name"        , stBody.table_name);
		return 0;
	};
	//----------------------------------------------���Ľӿ� [onForceLogout] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onForceLogout
	static int Packet2Struct(TForceLogout& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("hint_msg"          , stBody.hint_msg);
		pkt.GetParameterVal("session_id"          , stBody.session_id);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onForceLogout
	static int Struct2Packet(TForceLogout& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("hint_msg"          , stBody.hint_msg);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onNewBourseBulletin] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onNewBourseBulletin
	static int Packet2Struct(TNewBourseBulletin& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("seq_no"            , stBody.seq_no);
		pkt.GetParameterVal("title"             , stBody.title);
		pkt.GetParameterVal("content"           , stBody.content);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onNewBourseBulletin
	static int Struct2Packet(TNewBourseBulletin& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("seq_no"            , stBody.seq_no);
		pkt.AddParameter("title"             , stBody.title);
		pkt.AddParameter("content"           , stBody.content);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onNewMemberBulletin] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onNewMemberBulletin
	static int Packet2Struct(TNewMemberBulletin& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("bulletin_id"       , stBody.bulletin_id);
		pkt.GetParameterVal("title"             , stBody.title);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onNewMemberBulletin
	static int Struct2Packet(TNewMemberBulletin& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("bulletin_id"       , stBody.bulletin_id);
		pkt.AddParameter("title"             , stBody.title);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onSessionKey] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onSessionKey
	static int Packet2Struct(TSessionKey& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("session_id"        , stBody.session_id);
		pkt.GetParameterVal("session_key"       , stBody.session_key);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onSessionKey
	static int Struct2Packet(TSessionKey& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("session_id"        , stBody.session_id);
		pkt.AddParameter("session_key"       , stBody.session_key);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRiskNotify] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRiskNotify
	static int Packet2Struct(TRiskNotity& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("risk_idx1"         , stBody.risk_idx1);
		pkt.GetParameterVal("risk_idx2"         , stBody.risk_idx2);
		pkt.GetParameterVal("call_margin"      , stBody.call_margin );
		pkt.GetParameterVal("exch_date"         , stBody.exch_date);
		pkt.GetParameterVal("notify_title"      , stBody.notify_title);
		pkt.GetParameterVal("notify_content"    , stBody.notify_content);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRiskNotify
	static int Struct2Packet(TRiskNotity& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("risk_idx1"         , stBody.risk_idx1);
		pkt.AddParameter("risk_idx2"         , stBody.risk_idx2);
		pkt.AddParameter("call_margin "      , stBody.call_margin );
		pkt.AddParameter("exch_date"         , stBody.exch_date);
		pkt.AddParameter("notify_title"      , stBody.notify_title);
		pkt.AddParameter("notify_content"    , stBody.notify_content);
		return 0;
	};

	//----------------------------------------------���Ľӿ� [onRecvRtnSpotInstStateUpdate] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnSpotInstStateUpdate
	static int Packet2Struct(SpotInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("tradeState"        , stBody.tradeState);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnSpotInstStateUpdate
	static int Struct2Packet(SpotInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("tradeState"        , stBody.tradeState);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvRtnForwardInstStateUpdate] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnForwardInstStateUpdate
	static int Packet2Struct(ForwardInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("tradeState"        , stBody.tradeState);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnForwardInstStateUpdate
	static int Struct2Packet(ForwardInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("tradeState"        , stBody.tradeState);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvRtnDeferInstStateUpdate] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnDeferInstStateUpdate
	static int Packet2Struct(DeferInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("tradeState"        , stBody.tradeState);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnDeferInstStateUpdate
	static int Struct2Packet(DeferInstState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("tradeState"        , stBody.tradeState);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvRtnSpotMarketStateUpdate] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnSpotMarketStateUpdate
	static int Packet2Struct(SpotMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("marketID"          , stBody.marketID);
		pkt.GetParameterVal("marketState"       , stBody.marketState);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnSpotMarketStateUpdate
	static int Struct2Packet(SpotMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("marketID"          , stBody.marketID);
		pkt.AddParameter("marketState"       , stBody.marketState);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvRtnForwardMarketStateUpdate] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnForwardMarketStateUpdate
	static int Packet2Struct(ForwardMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("marketID"          , stBody.marketID);
		pkt.GetParameterVal("marketState"       , stBody.marketState);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnForwardMarketStateUpdate
	static int Struct2Packet(ForwardMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("marketID"          , stBody.marketID);
		pkt.AddParameter("marketState"       , stBody.marketState);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvRtnDeferMarketStateUpdate] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnDeferMarketStateUpdate
	static int Packet2Struct(DeferMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("marketID"          , stBody.marketID);
		pkt.GetParameterVal("marketState"       , stBody.marketState);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnDeferMarketStateUpdate
	static int Struct2Packet(DeferMarketState& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("marketID"          , stBody.marketID);
		pkt.AddParameter("marketState"       , stBody.marketState);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onAcctCapitalAccess] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onAcctCapitalAccess
	static int Packet2Struct(AcctCapitalAccess& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("fund_src_type"     , stBody.fund_src_type);
		pkt.GetParameterVal("serial_no"         , stBody.serial_no);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("access_way"        , stBody.access_way);
		pkt.GetParameterVal("amount"            , stBody.amount);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onAcctCapitalAccess
	static int Struct2Packet(AcctCapitalAccess& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("fund_src_type"     , stBody.fund_src_type);
		pkt.AddParameter("serial_no"         , stBody.serial_no);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("access_way"        , stBody.access_way);
		pkt.AddParameter("amount"            , stBody.amount);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onCustInfoChange] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onCustInfoChange
	static int Packet2Struct(CustInfoChange& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("update_flag"       , stBody.update_flag);
		pkt.GetParameterVal("acct_no"           , stBody.acct_no);
		pkt.GetParameterVal("member_id"         , stBody.member_id);
		pkt.GetParameterVal("cust_abbr"         , stBody.cust_abbr);
		pkt.GetParameterVal("m_Fare_model_id"   , stBody.m_Fare_model_id);
		pkt.GetParameterVal("b_Fare_model_id"   , stBody.b_Fare_model_id);
		pkt.GetParameterVal("acct_type"         , stBody.acct_type);
		pkt.GetParameterVal("acct_stat"         , stBody.acct_stat);
		pkt.GetParameterVal("branch_ID"         , stBody.branch_ID);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onCustInfoChange
	static int Struct2Packet(CustInfoChange& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("update_flag"       , stBody.update_flag);
		pkt.AddParameter("acct_no"           , stBody.acct_no);
		pkt.AddParameter("member_id"         , stBody.member_id);
		pkt.AddParameter("cust_abbr"         , stBody.cust_abbr);
		pkt.AddParameter("m_Fare_model_id"   , stBody.m_Fare_model_id);
		pkt.AddParameter("b_Fare_model_id"   , stBody.b_Fare_model_id);
		pkt.AddParameter("acct_type"         , stBody.acct_type);
		pkt.AddParameter("acct_stat"         , stBody.acct_stat);
		pkt.AddParameter("branch_ID"         , stBody.branch_ID);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onCustRiskDegreeChange] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onCustRiskDegreeChange
	static int Packet2Struct(CustRiskDegreeChange& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         , stBody.oper_flag);
		pkt.GetParameterVal("risk_degree1"      , stBody.risk_degree1);
		pkt.GetParameterVal("risk_degree2"      , stBody.risk_degree2);
		pkt.GetParameterVal("risk_grade"        , stBody.risk_grade);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onCustRiskDegreeChange
	static int Struct2Packet(CustRiskDegreeChange& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("oper_flag"         , stBody.oper_flag);
		pkt.AddParameter("risk_degree1"      , stBody.risk_degree1);
		pkt.AddParameter("risk_degree2"      , stBody.risk_degree2);
		pkt.AddParameter("risk_grade"        , stBody.risk_grade);
		return 0;
	};

	//---------------------------------------------- [RspMsg] �ṹ��ؽ���
	// ���Ľ��������� -> �ṹ    RspMsg
	static int Packet2Struct(RspMsg &v, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("RspCode",v.RspCode);
		pkt.GetParameterVal("RspMsg",v.RspMsg);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    RspMsg
	static int Struct2Packet(RspMsg &v, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("RspCode",v.RspCode);
		pkt.AddParameter("RspMsg",v.RspMsg);
		return 0;
	};  
		
		//����  TSpotOrder:�ֻ�������Ϣ �ṹ��ֵ
    static int Packet2Struct(SpotOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //������
        pkt.GetParameterVal("instID",v.instID);    //��Լ���� (not null)
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ����� (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա���� (not null)
        pkt.GetParameterVal("buyOrSell",v.buyOrSell);    //�������� (not null)
        pkt.GetParameterVal("applyDate",v.applyDate);    //�걨����
        pkt.GetParameterVal("applyTime",v.applyTime);    //�걨ʱ��
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա���� (not null)
        pkt.GetParameterVal("price",v.price);    //�۸�  (not null)
        pkt.GetParameterVal("amount",v.amount);    //����  (not null)
        pkt.GetParameterVal("remainAmount",v.remainAmount);    //ʣ������
        pkt.GetParameterVal("cancelTime",v.cancelTime);    //����ʱ��
        pkt.GetParameterVal("cancelID",v.cancelID);    //����Ա����
        pkt.GetParameterVal("status",v.status);    //״̬
        pkt.GetParameterVal("matchType",v.matchType);    //����  (not null)
        pkt.GetParameterVal("endorseInstID",v.endorseInstID);    //ת�ú�Լ���� (not null)
        pkt.GetParameterVal("localOrderNo",v.localOrderNo);    //���ر����� (not null)
        return 0;
    }

    //��  TSpotOrder:�ֻ�������Ϣ �ṹ��ֵ����ַ���
    static int Struct2Packet(SpotOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("buyOrSell",v.buyOrSell);
        pkt.AddParameter("applyDate",v.applyDate);
        pkt.AddParameter("applyTime",v.applyTime);
        pkt.AddParameter("traderID",v.traderID);
        pkt.AddParameter("price",v.price);
        pkt.AddParameter("amount",v.amount);
        pkt.AddParameter("remainAmount",v.remainAmount);
        pkt.AddParameter("cancelTime",v.cancelTime);
        pkt.AddParameter("cancelID",v.cancelID);
        pkt.AddParameter("status",v.status);
        pkt.AddParameter("matchType",v.matchType);
        pkt.AddParameter("endorseInstID",v.endorseInstID);
        pkt.AddParameter("localOrderNo",v.localOrderNo);
        return 0;
    }
	
		//��  TSpotOrderCancel:�ֻ��������� �ṹ��ֵ����ַ���
    static int Struct2Packet(SpotOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("traderID",v.traderID);
    }
	
		//����  TDeferOrderCancel:�ֻ����ڽ��ճ������� �ṹ��ֵ
    static int Packet2Struct(SpotOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //������  (not null)
        pkt.GetParameterVal("instID",v.instID);    //��Լ����  (not null)
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ�����  (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա����  (not null)
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա����  (not null)
        return 0;
    }
    
    //����  TDeferOrder:�ֻ����ڽ��ձ��� �ṹ��ֵ
    static int Packet2Struct(DeferOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //������ (not null)
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ����� (not null)
        pkt.GetParameterVal("instID",v.instID);    //��Լ���� (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա���� (not null)
        pkt.GetParameterVal("buyOrSell",v.buyOrSell);    //�������� (not null)
        pkt.GetParameterVal("applyDate",v.applyDate);    //�걨����
        pkt.GetParameterVal("applyTime",v.applyTime);    //�걨ʱ��
        pkt.GetParameterVal("offSetFlag",v.offSetFlag);    //��ƽ�ֱ�־ (not null)
        pkt.GetParameterVal("price",v.price);    //�۸�   (not null)
        pkt.GetParameterVal("amount",v.amount);    //����  (not null)
        pkt.GetParameterVal("remainAmount",v.remainAmount);    //ʣ������
        pkt.GetParameterVal("cancelTime",v.cancelTime);    //����ʱ��
        pkt.GetParameterVal("status",v.status);    //״̬
        pkt.GetParameterVal("localOrderNo",v.localOrderNo);    //���ر�����  (not null)
        pkt.GetParameterVal("margin",v.margin);    //��֤����
        pkt.GetParameterVal("marginType",v.marginType);    //��֤������  (not null)
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա����  (not null)
        pkt.GetParameterVal("cancelID",v.cancelID);    //����Ա����
        pkt.GetParameterVal("matchType",v.matchType);    //����  (not null)
        return 0;
    }

    //��  TDeferOrder:�ֻ����ڽ��ձ��� �ṹ��ֵ����ַ���
    static int Struct2Packet(DeferOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("buyOrSell",v.buyOrSell);
        pkt.AddParameter("applyDate",v.applyDate);
        pkt.AddParameter("applyTime",v.applyTime);
        pkt.AddParameter("offSetFlag",v.offSetFlag);
        pkt.AddParameter("price",v.price);
        pkt.AddParameter("amount",v.amount);
        pkt.AddParameter("remainAmount",v.remainAmount);
        pkt.AddParameter("cancelTime",v.cancelTime);
        pkt.AddParameter("status",v.status);
        pkt.AddParameter("localOrderNo",v.localOrderNo);
        pkt.AddParameter("margin",v.margin);
        pkt.AddParameter("marginType",v.marginType);
        pkt.AddParameter("traderID",v.traderID);
        pkt.AddParameter("cancelID",v.cancelID);
        pkt.AddParameter("matchType",v.matchType);
        return 0;
    }

		//����  TDeferOrderCancel:�ֻ����ڽ��ճ������� �ṹ��ֵ
    static int Packet2Struct(DeferOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //������  (not null)
        pkt.GetParameterVal("instID",v.instID);    //��Լ����  (not null)
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ�����  (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա����  (not null)
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա����  (not null)
        return 0;
    }

    //��  TDeferOrderCancel:�ֻ����ڽ��ճ������� �ṹ��ֵ����ַ���
    static int Struct2Packet(DeferOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("traderID",v.traderID);
        return 0;
    }
    
    //����  TDeferDeliveryAppOrder:�ֻ����ڽ��ս����걨���� �ṹ��ֵ
    static int Packet2Struct(DeferDeliveryAppOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //�������
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ�����  (not null)
        pkt.GetParameterVal("instID",v.instID);    //��Լ����  (not null)
        pkt.GetParameterVal("buyOrSell",v.buyOrSell);    //��������  (not null)
        pkt.GetParameterVal("applyDate",v.applyDate);    //��������
        pkt.GetParameterVal("applyTime",v.applyTime);    //����ʱ��
        pkt.GetParameterVal("amount",v.amount);    //����  (not null)
        pkt.GetParameterVal("cancelTime",v.cancelTime);    //����ʱ��
        pkt.GetParameterVal("status",v.status);    //����״̬
        pkt.GetParameterVal("localOrderNo",v.localOrderNo);    //���ر������ (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա����  (not null)
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա����  (not null)
        pkt.GetParameterVal("cancelID",v.cancelID);    //����Ա����
        pkt.GetParameterVal("remainAmount",v.remainAmount);    //ʣ������
        return 0;
    }

    //��  TDeferDeliveryAppOrder:�ֻ����ڽ��ս����걨���� �ṹ��ֵ����ַ���
    static int Struct2Packet(DeferDeliveryAppOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("buyOrSell",v.buyOrSell);
        pkt.AddParameter("applyDate",v.applyDate);
        pkt.AddParameter("applyTime",v.applyTime);
        pkt.AddParameter("amount",v.amount);
        pkt.AddParameter("cancelTime",v.cancelTime);
        pkt.AddParameter("status",v.status);
        pkt.AddParameter("localOrderNo",v.localOrderNo);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("traderID",v.traderID);
        pkt.AddParameter("cancelID",v.cancelID);
        pkt.AddParameter("remainAmount",v.remainAmount);
        return 0;
    }
    
    
    //����  TDeferDeliveryAppOrderCancel:�ֻ����ڽ��ս����걨�������� �ṹ��ֵ
    static int Packet2Struct(DeferDeliveryAppOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //������  (not null)
        pkt.GetParameterVal("instID",v.instID);    //��Լ����  (not null)
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ�����  (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա���� (not null)
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա���� (not null)
        return 0;
    }

    //��  TDeferDeliveryAppOrderCancel:�ֻ����ڽ��ս����걨�������� �ṹ��ֵ����ַ���
    static int Struct2Packet(DeferDeliveryAppOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("traderID",v.traderID);
        return 0;
    }
    
    //����  TMiddleAppOrder:�ֻ����ڽ����������걨���� �ṹ��ֵ
    static int Packet2Struct(MiddleAppOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //�������
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ����� (not null)
        pkt.GetParameterVal("instID",v.instID);    //��Լ���� (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա����  (not null)
        pkt.GetParameterVal("buyOrSell",v.buyOrSell);    //��������  (not null)
        pkt.GetParameterVal("applyDate",v.applyDate);    //��������
        pkt.GetParameterVal("applyTime",v.applyTime);    //����ʱ��
        pkt.GetParameterVal("amount",v.amount);    //����  (not null)
        pkt.GetParameterVal("cancelTime",v.cancelTime);    //����ʱ��
        pkt.GetParameterVal("status",v.status);    //����״̬
        pkt.GetParameterVal("localOrderNo",v.localOrderNo);    //���ر������ (not null)
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա����  (not null)
        pkt.GetParameterVal("cancelID",v.cancelID);    //����Ա����
        pkt.GetParameterVal("remainAmount",v.remainAmount);    //ʣ������
        return 0;
    }

    //��  TMiddleAppOrder:�ֻ����ڽ����������걨���� �ṹ��ֵ����ַ���/
    static int Struct2Packet(MiddleAppOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("buyOrSell",v.buyOrSell);
        pkt.AddParameter("applyDate",v.applyDate);
        pkt.AddParameter("applyTime",v.applyTime);
        pkt.AddParameter("amount",v.amount);
        pkt.AddParameter("cancelTime",v.cancelTime);
        pkt.AddParameter("status",v.status);
        pkt.AddParameter("localOrderNo",v.localOrderNo);
        pkt.AddParameter("traderID",v.traderID);
        pkt.AddParameter("cancelID",v.cancelID);
        pkt.AddParameter("remainAmount",v.remainAmount);
        return 0;
    }
    
    //����  TMiddleAppOrderCancel:�ֻ����ڽ����������걨�������� �ṹ��ֵ
    static int Packet2Struct(MiddleAppOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //������  (not null)
        pkt.GetParameterVal("instID",v.instID);    //��Լ����  (not null)
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ����� (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա���� (not null)
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա���� (not null)
        return 0;
    }

    //TMiddleAppOrderCancel:�ֻ����ڽ����������걨�������� �ṹ��ֵ����ַ���
    static int Struct2Packet(MiddleAppOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("traderID",v.traderID);
        return 0;
    }
          
    //����  TForwardOrder:�ֻ�T+N���� �ṹ��ֵ/
    static int Packet2Struct(ForwardOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //������
        pkt.GetParameterVal("instID",v.instID);    //��Լ����  (not null)
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ�����  (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա����  (not null)
        pkt.GetParameterVal("buyOrSell",v.buyOrSell);    //��������  (not null)
        pkt.GetParameterVal("applyDate",v.applyDate);    //�걨����
        pkt.GetParameterVal("applyTime",v.applyTime);    //�걨ʱ��
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա���� (not null)
        pkt.GetParameterVal("price",v.price);    //�۸�   (not null)
        pkt.GetParameterVal("amount",v.amount);    //����  (not null)
        pkt.GetParameterVal("remainAmount",v.remainAmount);    //ʣ������
        pkt.GetParameterVal("cancelTime",v.cancelTime);    //����ʱ��
        pkt.GetParameterVal("cancelID",v.cancelID);    //����Ա����
        pkt.GetParameterVal("status",v.status);    //״̬
        pkt.GetParameterVal("localOrderNo",v.localOrderNo);    //���ر�����  (not null)
        pkt.GetParameterVal("matchType",v.matchType);    //����  (not null)
        return 0;
    }

    //��  TForwardOrder:�ֻ�T+N���� �ṹ��ֵ����ַ���/
    static int Struct2Packet(ForwardOrder &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("buyOrSell",v.buyOrSell);
        pkt.AddParameter("applyDate",v.applyDate);
        pkt.AddParameter("applyTime",v.applyTime);
        pkt.AddParameter("traderID",v.traderID);
        pkt.AddParameter("price",v.price);
        pkt.AddParameter("amount",v.amount);
        pkt.AddParameter("remainAmount",v.remainAmount);
        pkt.AddParameter("cancelTime",v.cancelTime);
        pkt.AddParameter("cancelID",v.cancelID);
        pkt.AddParameter("status",v.status);
        pkt.AddParameter("localOrderNo",v.localOrderNo);
        pkt.AddParameter("matchType",v.matchType);
		return 0;
    }
    
    //����  TForwardOrderCancel:�ֻ�T+N�������� �ṹ��ֵ
    static int Packet2Struct(ForwardOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.GetParameterVal("orderNo",v.orderNo);    //������  (not null)
        pkt.GetParameterVal("instID",v.instID);    //��Լ����  (not null)
        pkt.GetParameterVal("clientID",v.clientID);    //�ͻ�����  (not null)
        pkt.GetParameterVal("memberID",v.memberID);    //��Ա����  (not null)
        pkt.GetParameterVal("traderID",v.traderID);    //����Ա���� (not null)
        return 0;
    }

    //��  TForwardOrderCancel:�ֻ�T+N�������� �ṹ��ֵ����ַ���/
    static int Struct2Packet(ForwardOrderCancel &v, CBroadcastPacket & pkt) 
    {
        pkt.AddParameter("orderNo",v.orderNo);
        pkt.AddParameter("instID",v.instID);
        pkt.AddParameter("clientID",v.clientID);
        pkt.AddParameter("memberID",v.memberID);
        pkt.AddParameter("traderID",v.traderID);
		return 0;
    }

	//----------------------------------------------���Ľӿ� [onRecvSpotQuotation] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvSpotQuotation
	static int Packet2Struct(SpotQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("name"              , stBody.name);
		pkt.GetParameterVal("lastClose"         , stBody.lastClose);
		pkt.GetParameterVal("open"              , stBody.open);
		pkt.GetParameterVal("high"              , stBody.high);
		pkt.GetParameterVal("low"               , stBody.low);
		pkt.GetParameterVal("last"              , stBody.last);
		pkt.GetParameterVal("close"             , stBody.close);
		pkt.GetParameterVal("bid1"              , stBody.bid1);
		pkt.GetParameterVal("bidLot1"           , stBody.bidLot1);
		pkt.GetParameterVal("bid2"              , stBody.bid2);
		pkt.GetParameterVal("bidLot2"           , stBody.bidLot2);
		pkt.GetParameterVal("bid3"              , stBody.bid3);
		pkt.GetParameterVal("bidLot3"           , stBody.bidLot3);
		pkt.GetParameterVal("bid4"              , stBody.bid4);
		pkt.GetParameterVal("bidLot4"           , stBody.bidLot4);
		pkt.GetParameterVal("bid5"              , stBody.bid5);
		pkt.GetParameterVal("bidLot5"           , stBody.bidLot5);
		pkt.GetParameterVal("ask1"              , stBody.ask1);
		pkt.GetParameterVal("askLot1"           , stBody.askLot1);
		pkt.GetParameterVal("ask2"              , stBody.ask2);
		pkt.GetParameterVal("askLot2"           , stBody.askLot2);
		pkt.GetParameterVal("ask3"              , stBody.ask3);
		pkt.GetParameterVal("askLot3"           , stBody.askLot3);
		pkt.GetParameterVal("ask4"              , stBody.ask4);
		pkt.GetParameterVal("askLot4"           , stBody.askLot4);
		pkt.GetParameterVal("ask5"              , stBody.ask5);
		pkt.GetParameterVal("askLot5"           , stBody.askLot5);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("weight"            , stBody.weight);
		pkt.GetParameterVal("highLimit"         , stBody.highLimit);
		pkt.GetParameterVal("lowLimit"          , stBody.lowLimit);
		pkt.GetParameterVal("upDown"            , stBody.upDown);
		pkt.GetParameterVal("upDownRate"        , stBody.upDownRate);
		pkt.GetParameterVal("turnOver"          , stBody.turnOver);
		pkt.GetParameterVal("average"           , stBody.average);
		pkt.GetParameterVal("quoteDate"         , stBody.quoteDate);
		pkt.GetParameterVal("quoteTime"         , stBody.quoteTime);
		pkt.GetParameterVal("sequenceNo"        , stBody.sequenceNo);
		pkt.GetParameterVal("sZipBuff"          , stBody.sZipBuff);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvSpotQuotation
	static int Struct2Packet(SpotQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("name"              , stBody.name);
		pkt.AddParameter("lastClose"         , stBody.lastClose);
		pkt.AddParameter("open"              , stBody.open);
		pkt.AddParameter("high"              , stBody.high);
		pkt.AddParameter("low"               , stBody.low);
		pkt.AddParameter("last"              , stBody.last);
		pkt.AddParameter("close"             , stBody.close);
		pkt.AddParameter("bid1"              , stBody.bid1);
		pkt.AddParameter("bidLot1"           , stBody.bidLot1);
		pkt.AddParameter("bid2"              , stBody.bid2);
		pkt.AddParameter("bidLot2"           , stBody.bidLot2);
		pkt.AddParameter("bid3"              , stBody.bid3);
		pkt.AddParameter("bidLot3"           , stBody.bidLot3);
		pkt.AddParameter("bid4"              , stBody.bid4);
		pkt.AddParameter("bidLot4"           , stBody.bidLot4);
		pkt.AddParameter("bid5"              , stBody.bid5);
		pkt.AddParameter("bidLot5"           , stBody.bidLot5);
		pkt.AddParameter("ask1"              , stBody.ask1);
		pkt.AddParameter("askLot1"           , stBody.askLot1);
		pkt.AddParameter("ask2"              , stBody.ask2);
		pkt.AddParameter("askLot2"           , stBody.askLot2);
		pkt.AddParameter("ask3"              , stBody.ask3);
		pkt.AddParameter("askLot3"           , stBody.askLot3);
		pkt.AddParameter("ask4"              , stBody.ask4);
		pkt.AddParameter("askLot4"           , stBody.askLot4);
		pkt.AddParameter("ask5"              , stBody.ask5);
		pkt.AddParameter("askLot5"           , stBody.askLot5);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("weight"            , stBody.weight);
		pkt.AddParameter("highLimit"         , stBody.highLimit);
		pkt.AddParameter("lowLimit"          , stBody.lowLimit);
		pkt.AddParameter("upDown"            , stBody.upDown);
		pkt.AddParameter("upDownRate"        , stBody.upDownRate);
		pkt.AddParameter("turnOver"          , stBody.turnOver);
		pkt.AddParameter("average"           , stBody.average);
		pkt.AddParameter("quoteDate"         , stBody.quoteDate);
		pkt.AddParameter("quoteTime"         , stBody.quoteTime);
		pkt.AddParameter("sequenceNo"        , stBody.sequenceNo);
		pkt.AddParameter("sZipBuff"          , stBody.sZipBuff);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvForwardQuotation] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvForwardQuotation
	static int Packet2Struct(ForwardQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("name"              , stBody.name);
		pkt.GetParameterVal("lastSettle"        , stBody.lastSettle);
		pkt.GetParameterVal("lastClose"         , stBody.lastClose);
		pkt.GetParameterVal("open"              , stBody.open);
		pkt.GetParameterVal("high"              , stBody.high);
		pkt.GetParameterVal("low"               , stBody.low);
		pkt.GetParameterVal("last"              , stBody.last);
		pkt.GetParameterVal("close"             , stBody.close);
		pkt.GetParameterVal("settle"            , stBody.settle);
		pkt.GetParameterVal("bid1"              , stBody.bid1);
		pkt.GetParameterVal("bidLot1"           , stBody.bidLot1);
		pkt.GetParameterVal("bid2"              , stBody.bid2);
		pkt.GetParameterVal("bidLot2"           , stBody.bidLot2);
		pkt.GetParameterVal("bid3"              , stBody.bid3);
		pkt.GetParameterVal("bidLot3"           , stBody.bidLot3);
		pkt.GetParameterVal("bid4"              , stBody.bid4);
		pkt.GetParameterVal("bidLot4"           , stBody.bidLot4);
		pkt.GetParameterVal("bid5"              , stBody.bid5);
		pkt.GetParameterVal("bidLot5"           , stBody.bidLot5);
		pkt.GetParameterVal("ask1"              , stBody.ask1);
		pkt.GetParameterVal("askLot1"           , stBody.askLot1);
		pkt.GetParameterVal("ask2"              , stBody.ask2);
		pkt.GetParameterVal("askLot2"           , stBody.askLot2);
		pkt.GetParameterVal("ask3"              , stBody.ask3);
		pkt.GetParameterVal("askLot3"           , stBody.askLot3);
		pkt.GetParameterVal("ask4"              , stBody.ask4);
		pkt.GetParameterVal("askLot4"           , stBody.askLot4);
		pkt.GetParameterVal("ask5"              , stBody.ask5);
		pkt.GetParameterVal("askLot5"           , stBody.askLot5);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("weight"            , stBody.weight);
		pkt.GetParameterVal("highLimit"         , stBody.highLimit);
		pkt.GetParameterVal("lowLimit"          , stBody.lowLimit);
		pkt.GetParameterVal("Posi"              , stBody.Posi);
		pkt.GetParameterVal("upDown"            , stBody.upDown);
		pkt.GetParameterVal("upDownRate"        , stBody.upDownRate);
		pkt.GetParameterVal("turnOver"          , stBody.turnOver);
		pkt.GetParameterVal("average"           , stBody.average);
		pkt.GetParameterVal("quoteDate"         , stBody.quoteDate);
		pkt.GetParameterVal("quoteTime"         , stBody.quoteTime);
		pkt.GetParameterVal("sequenceNo"        , stBody.sequenceNo);
		pkt.GetParameterVal("sZipBuff"          , stBody.sZipBuff);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvForwardQuotation
	static int Struct2Packet(ForwardQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("name"              , stBody.name);
		pkt.AddParameter("lastSettle"        , stBody.lastSettle);
		pkt.AddParameter("lastClose"         , stBody.lastClose);
		pkt.AddParameter("open"              , stBody.open);
		pkt.AddParameter("high"              , stBody.high);
		pkt.AddParameter("low"               , stBody.low);
		pkt.AddParameter("last"              , stBody.last);
		pkt.AddParameter("close"             , stBody.close);
		pkt.AddParameter("settle"            , stBody.settle);
		pkt.AddParameter("bid1"              , stBody.bid1);
		pkt.AddParameter("bidLot1"           , stBody.bidLot1);
		pkt.AddParameter("bid2"              , stBody.bid2);
		pkt.AddParameter("bidLot2"           , stBody.bidLot2);
		pkt.AddParameter("bid3"              , stBody.bid3);
		pkt.AddParameter("bidLot3"           , stBody.bidLot3);
		pkt.AddParameter("bid4"              , stBody.bid4);
		pkt.AddParameter("bidLot4"           , stBody.bidLot4);
		pkt.AddParameter("bid5"              , stBody.bid5);
		pkt.AddParameter("bidLot5"           , stBody.bidLot5);
		pkt.AddParameter("ask1"              , stBody.ask1);
		pkt.AddParameter("askLot1"           , stBody.askLot1);
		pkt.AddParameter("ask2"              , stBody.ask2);
		pkt.AddParameter("askLot2"           , stBody.askLot2);
		pkt.AddParameter("ask3"              , stBody.ask3);
		pkt.AddParameter("askLot3"           , stBody.askLot3);
		pkt.AddParameter("ask4"              , stBody.ask4);
		pkt.AddParameter("askLot4"           , stBody.askLot4);
		pkt.AddParameter("ask5"              , stBody.ask5);
		pkt.AddParameter("askLot5"           , stBody.askLot5);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("weight"            , stBody.weight);
		pkt.AddParameter("highLimit"         , stBody.highLimit);
		pkt.AddParameter("lowLimit"          , stBody.lowLimit);
		pkt.AddParameter("Posi"              , stBody.Posi);
		pkt.AddParameter("upDown"            , stBody.upDown);
		pkt.AddParameter("upDownRate"        , stBody.upDownRate);
		pkt.AddParameter("turnOver"          , stBody.turnOver);
		pkt.AddParameter("average"           , stBody.average);
		pkt.AddParameter("quoteDate"         , stBody.quoteDate);
		pkt.AddParameter("quoteTime"         , stBody.quoteTime);
		pkt.AddParameter("sequenceNo"        , stBody.sequenceNo);
		pkt.AddParameter("sZipBuff"          , stBody.sZipBuff);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvDeferQuotation] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvDeferQuotation
	static int Packet2Struct(DeferQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"            , stBody.instID);
		pkt.GetParameterVal("name"              , stBody.name);
		pkt.GetParameterVal("lastSettle"        , stBody.lastSettle);
		pkt.GetParameterVal("lastClose"         , stBody.lastClose);
		pkt.GetParameterVal("open"              , stBody.open);
		pkt.GetParameterVal("high"              , stBody.high);
		pkt.GetParameterVal("low"               , stBody.low);
		pkt.GetParameterVal("last"              , stBody.last);
		pkt.GetParameterVal("close"             , stBody.close);
		pkt.GetParameterVal("settle"            , stBody.settle);
		pkt.GetParameterVal("bid1"              , stBody.bid1);
		pkt.GetParameterVal("bidLot1"           , stBody.bidLot1);
		pkt.GetParameterVal("bid2"              , stBody.bid2);
		pkt.GetParameterVal("bidLot2"           , stBody.bidLot2);
		pkt.GetParameterVal("bid3"              , stBody.bid3);
		pkt.GetParameterVal("bidLot3"           , stBody.bidLot3);
		pkt.GetParameterVal("bid4"              , stBody.bid4);
		pkt.GetParameterVal("bidLot4"           , stBody.bidLot4);
		pkt.GetParameterVal("bid5"              , stBody.bid5);
		pkt.GetParameterVal("bidLot5"           , stBody.bidLot5);
		pkt.GetParameterVal("ask1"              , stBody.ask1);
		pkt.GetParameterVal("askLot1"           , stBody.askLot1);
		pkt.GetParameterVal("ask2"              , stBody.ask2);
		pkt.GetParameterVal("askLot2"           , stBody.askLot2);
		pkt.GetParameterVal("ask3"              , stBody.ask3);
		pkt.GetParameterVal("askLot3"           , stBody.askLot3);
		pkt.GetParameterVal("ask4"              , stBody.ask4);
		pkt.GetParameterVal("askLot4"           , stBody.askLot4);
		pkt.GetParameterVal("ask5"              , stBody.ask5);
		pkt.GetParameterVal("askLot5"           , stBody.askLot5);
		pkt.GetParameterVal("volume"            , stBody.volume);
		pkt.GetParameterVal("weight"            , stBody.weight);
		pkt.GetParameterVal("highLimit"         , stBody.highLimit);
		pkt.GetParameterVal("lowLimit"          , stBody.lowLimit);
		pkt.GetParameterVal("Posi"              , stBody.Posi);
		pkt.GetParameterVal("upDown"            , stBody.upDown);
		pkt.GetParameterVal("upDownRate"        , stBody.upDownRate);
		pkt.GetParameterVal("turnOver"          , stBody.turnOver);
		pkt.GetParameterVal("average"           , stBody.average);
		pkt.GetParameterVal("quoteDate"         , stBody.quoteDate);
		pkt.GetParameterVal("quoteTime"         , stBody.quoteTime);
		pkt.GetParameterVal("sequenceNo"        , stBody.sequenceNo);
		pkt.GetParameterVal("sZipBuff"          , stBody.sZipBuff);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvDeferQuotation
	static int Struct2Packet(DeferQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"            , stBody.instID);
		pkt.AddParameter("name"              , stBody.name);
		pkt.AddParameter("lastSettle"        , stBody.lastSettle);
		pkt.AddParameter("lastClose"         , stBody.lastClose);
		pkt.AddParameter("open"              , stBody.open);
		pkt.AddParameter("high"              , stBody.high);
		pkt.AddParameter("low"               , stBody.low);
		pkt.AddParameter("last"              , stBody.last);
		pkt.AddParameter("close"             , stBody.close);
		pkt.AddParameter("settle"            , stBody.settle);
		pkt.AddParameter("bid1"              , stBody.bid1);
		pkt.AddParameter("bidLot1"           , stBody.bidLot1);
		pkt.AddParameter("bid2"              , stBody.bid2);
		pkt.AddParameter("bidLot2"           , stBody.bidLot2);
		pkt.AddParameter("bid3"              , stBody.bid3);
		pkt.AddParameter("bidLot3"           , stBody.bidLot3);
		pkt.AddParameter("bid4"              , stBody.bid4);
		pkt.AddParameter("bidLot4"           , stBody.bidLot4);
		pkt.AddParameter("bid5"              , stBody.bid5);
		pkt.AddParameter("bidLot5"           , stBody.bidLot5);
		pkt.AddParameter("ask1"              , stBody.ask1);
		pkt.AddParameter("askLot1"           , stBody.askLot1);
		pkt.AddParameter("ask2"              , stBody.ask2);
		pkt.AddParameter("askLot2"           , stBody.askLot2);
		pkt.AddParameter("ask3"              , stBody.ask3);
		pkt.AddParameter("askLot3"           , stBody.askLot3);
		pkt.AddParameter("ask4"              , stBody.ask4);
		pkt.AddParameter("askLot4"           , stBody.askLot4);
		pkt.AddParameter("ask5"              , stBody.ask5);
		pkt.AddParameter("askLot5"           , stBody.askLot5);
		pkt.AddParameter("volume"            , stBody.volume);
		pkt.AddParameter("weight"            , stBody.weight);
		pkt.AddParameter("highLimit"         , stBody.highLimit);
		pkt.AddParameter("lowLimit"          , stBody.lowLimit);
		pkt.AddParameter("Posi"              , stBody.Posi);
		pkt.AddParameter("upDown"            , stBody.upDown);
		pkt.AddParameter("upDownRate"        , stBody.upDownRate);
		pkt.AddParameter("turnOver"          , stBody.turnOver);
		pkt.AddParameter("average"           , stBody.average);
		pkt.AddParameter("quoteDate"         , stBody.quoteDate);
		pkt.AddParameter("quoteTime"         , stBody.quoteTime);
		pkt.AddParameter("sequenceNo"        , stBody.sequenceNo);
		pkt.AddParameter("sZipBuff"          , stBody.sZipBuff);
		return 0;
	};
	
	//----------------------------------------------���Ľӿ� [onRecvDeferDeliveryQuotation] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvDeferDeliveryQuotation
	static int Packet2Struct(DeferDeliveryQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("instID"         , stBody.instID);
		pkt.GetParameterVal("bidLot"         , stBody.bidLot);
		pkt.GetParameterVal("askLot"         , stBody.askLot);
		pkt.GetParameterVal("midBidLot"      , stBody.midBidLot);
		pkt.GetParameterVal("midAskLot"      , stBody.midAskLot);		
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvDeferDeliveryQuotation
	static int Struct2Packet(DeferDeliveryQuotation& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("instID"         , stBody.instID);
		pkt.AddParameter("bidLot"         , stBody.bidLot);
		pkt.AddParameter("askLot"         , stBody.askLot);
		pkt.AddParameter("midBidLot"      , stBody.midBidLot);
		pkt.AddParameter("midAskLot"      , stBody.midAskLot);		
		return 0;
	};


	//----------------------------------------------���Ľӿ� [onRecvRtnSpotMatch] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnSpotMatch
	static int Packet2Struct(PktSpotMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.stBody.matchNo );
		pkt.GetParameterVal("buyOrSell"         , stBody.stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.stBody.clientType);
		pkt.GetParameterVal("memberID"          , stBody.stBody.memberID);
		pkt.GetParameterVal("instID"            , stBody.stBody.instID);
		pkt.GetParameterVal("matchDate"         , stBody.stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.stBody.price);
		pkt.GetParameterVal("volume"            , stBody.stBody.volume);
		pkt.GetParameterVal("orderNo"           , stBody.stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.stBody.localOrderNo);
		pkt.GetParameterVal("matchType"         , stBody.stBody.matchType);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		pkt.GetParameterVal("RspCode"           , stBody.stRsp.RspCode);
		pkt.GetParameterVal("RspMsg"            , stBody.stRsp.RspMsg);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnSpotMatch
	static int Struct2Packet(PktSpotMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo "          , stBody.stBody.matchNo );
		pkt.AddParameter("buyOrSell"         , stBody.stBody.buyOrSell);
		pkt.AddParameter("clientID"          , stBody.stBody.clientID);
		pkt.AddParameter("clientType"        , stBody.stBody.clientType);
		pkt.AddParameter("memberID"          , stBody.stBody.memberID);
		pkt.AddParameter("instID"            , stBody.stBody.instID);
		pkt.AddParameter("matchDate"         , stBody.stBody.matchDate);
		pkt.AddParameter("matchTime"         , stBody.stBody.matchTime);
		pkt.AddParameter("price"             , stBody.stBody.price);
		pkt.AddParameter("volume"            , stBody.stBody.volume);
		pkt.AddParameter("orderNo"           , stBody.stBody.orderNo);
		pkt.AddParameter("localOrderNo"      , stBody.stBody.localOrderNo);
		pkt.AddParameter("matchType"         , stBody.stBody.matchType);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		pkt.AddParameter("RspCode"           , stBody.stRsp.RspCode);
		pkt.AddParameter("RspMsg"            , stBody.stRsp.RspMsg);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvRtnForwardMatch] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnForwardMatch
	static int Packet2Struct(PktForwardMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.stBody.matchNo);
		pkt.GetParameterVal("buyOrSell"         , stBody.stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.stBody.clientType);
		pkt.GetParameterVal("instID"            , stBody.stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.stBody.memberID);
		pkt.GetParameterVal("matchDate"         , stBody.stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.stBody.price);
		pkt.GetParameterVal("volume"            , stBody.stBody.volume);
		pkt.GetParameterVal("marginRate"        , stBody.stBody.marginRate);
		pkt.GetParameterVal("rateType"          , stBody.stBody.rateType);
		pkt.GetParameterVal("orderNo"           , stBody.stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.stBody.localOrderNo);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		pkt.GetParameterVal("RspCode"           , stBody.stRsp.RspCode);
		pkt.GetParameterVal("RspMsg"            , stBody.stRsp.RspMsg);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnForwardMatch
	static int Struct2Packet(PktForwardMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           , stBody.stBody.matchNo);
		pkt.AddParameter("buyOrSell"         , stBody.stBody.buyOrSell);
		pkt.AddParameter("clientID"          , stBody.stBody.clientID);
		pkt.AddParameter("clientType"        , stBody.stBody.clientType);
		pkt.AddParameter("instID"            , stBody.stBody.instID);
		pkt.AddParameter("memberID"          , stBody.stBody.memberID);
		pkt.AddParameter("matchDate"         , stBody.stBody.matchDate);
		pkt.AddParameter("matchTime"         , stBody.stBody.matchTime);
		pkt.AddParameter("price"             , stBody.stBody.price);
		pkt.AddParameter("volume"            , stBody.stBody.volume);
		pkt.AddParameter("marginRate"        , stBody.stBody.marginRate);
		pkt.AddParameter("rateType"          , stBody.stBody.rateType);
		pkt.AddParameter("orderNo"           , stBody.stBody.orderNo);
		pkt.AddParameter("localOrderNo"      , stBody.stBody.localOrderNo);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		pkt.AddParameter("RspCode"           , stBody.stRsp.RspCode);
		pkt.AddParameter("RspMsg"            , stBody.stRsp.RspMsg);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvRtnDeferMatch] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnDeferMatch
	static int Packet2Struct(PktDeferMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.stBody.matchNo);
		pkt.GetParameterVal("buyOrSell"         , stBody.stBody.buyOrSell);
		pkt.GetParameterVal("clientID"          , stBody.stBody.clientID);
		pkt.GetParameterVal("clientType"        , stBody.stBody.clientType);
		pkt.GetParameterVal("instID"            , stBody.stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.stBody.memberID);
		pkt.GetParameterVal("matchDate"         , stBody.stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.stBody.matchTime);
		pkt.GetParameterVal("price"             , stBody.stBody.price);
		pkt.GetParameterVal("volume"            , stBody.stBody.volume);
		pkt.GetParameterVal("offSetFlag"        , stBody.stBody.offsetFlag);
		pkt.GetParameterVal("orderNo"           , stBody.stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.stBody.localOrderNo);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		pkt.GetParameterVal("RspCode"           , stBody.stRsp.RspCode);
		pkt.GetParameterVal("RspMsg"            , stBody.stRsp.RspMsg);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnDeferMatch
	static int Struct2Packet(PktDeferMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           , stBody.stBody.matchNo);
		pkt.AddParameter("buyOrSell"         , stBody.stBody.buyOrSell);
		pkt.AddParameter("clientID"          , stBody.stBody.clientID);
		pkt.AddParameter("clientType"        , stBody.stBody.clientType);
		pkt.AddParameter("instID"            , stBody.stBody.instID);
		pkt.AddParameter("memberID"          , stBody.stBody.memberID);
		pkt.AddParameter("matchDate"         , stBody.stBody.matchDate);
		pkt.AddParameter("matchTime"         , stBody.stBody.matchTime);
		pkt.AddParameter("price"             , stBody.stBody.price);
		pkt.AddParameter("volume"            , stBody.stBody.volume);
		pkt.AddParameter("offSetFlag"        , stBody.stBody.offsetFlag);
		pkt.AddParameter("orderNo"           , stBody.stBody.orderNo);
		pkt.AddParameter("localOrderNo"      , stBody.stBody.localOrderNo);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		pkt.AddParameter("RspCode"           , stBody.stRsp.RspCode);
		pkt.AddParameter("RspMsg"            , stBody.stRsp.RspMsg);
		return 0;
	};



	//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppMatch] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnDeferDeliveryAppMatch
	static int Packet2Struct(PktDeferDeliveryAppMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("matchNo"           , stBody.stBody.matchNo);
		pkt.GetParameterVal("clientID"          , stBody.stBody.clientID);
		pkt.GetParameterVal("instID"            , stBody.stBody.instID);
		pkt.GetParameterVal("memberID"          , stBody.stBody.memberID);
		pkt.GetParameterVal("buyOrSell"         , stBody.stBody.buyOrSell);
		pkt.GetParameterVal("volume"            , stBody.stBody.volume);
		pkt.GetParameterVal("matchDate"         , stBody.stBody.matchDate);
		pkt.GetParameterVal("matchTime"         , stBody.stBody.matchTime);
		pkt.GetParameterVal("orderNo"           , stBody.stBody.orderNo);
		pkt.GetParameterVal("localOrderNo"      , stBody.stBody.LocalOrderNo);
		pkt.GetParameterVal("middleFlag"        , stBody.stBody.middleFlag);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		pkt.GetParameterVal("RspCode"           , stBody.stRsp.RspCode);
		pkt.GetParameterVal("RspMsg"            , stBody.stRsp.RspMsg);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnDeferDeliveryAppMatch
	static int Struct2Packet(PktDeferDeliveryAppMatch& stBody, CBroadcastPacket& pkt)
	{
		pkt.AddParameter("matchNo"           , stBody.stBody.matchNo);
		pkt.AddParameter("clientID"          , stBody.stBody.clientID);
		pkt.AddParameter("instID"            , stBody.stBody.instID);
		pkt.AddParameter("memberID"          , stBody.stBody.memberID);
		pkt.AddParameter("buyOrSell"         , stBody.stBody.buyOrSell);
		pkt.AddParameter("volume"            , stBody.stBody.volume);
		pkt.AddParameter("matchDate"         , stBody.stBody.matchDate);
		pkt.AddParameter("matchTime"         , stBody.stBody.matchTime);
		pkt.AddParameter("orderNo"           , stBody.stBody.orderNo);
		pkt.AddParameter("localOrderNo"      , stBody.stBody.LocalOrderNo);
		pkt.AddParameter("middleFlag"        , stBody.stBody.middleFlag);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		pkt.AddParameter("RspCode"           , stBody.stRsp.RspCode);
		pkt.AddParameter("RspMsg"            , stBody.stRsp.RspMsg);
		return 0;
	};


  //----------------------------------------------���Ľӿ� [onRecvRspSpotOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspSpotOrder
	static int Packet2Struct(RspSpotOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspSpotOrder
	static int Struct2Packet(RspSpotOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  
    
    
  //----------------------------------------------���Ľӿ� [onRecvRtnSpotOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnSpotOrder
	static int Packet2Struct(RtnSpotOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnSpotOrder
	static int Struct2Packet(RtnSpotOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  
	
	//----------------------------------------------���Ľӿ� [onRecvRspSpotOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspSpotOrderCancel
	static int Packet2Struct(RspSpotOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspSpotOrderCancel
	static int Struct2Packet(RspSpotOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  
	
	//----------------------------------------------���Ľӿ� [onRecvRtnSpotOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnSpotOrderCancel
	static int Packet2Struct(RtnSpotOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnSpotOrderCancel
	static int Struct2Packet(RtnSpotOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	
	

	//----------------------------------------------���Ľӿ� [onRecvRspDeferOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspDeferOrder
	static int Packet2Struct(RspDeferOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspDeferOrder
	static int Struct2Packet(RspDeferOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	
		

	//----------------------------------------------���Ľӿ� [onRecvRtnDeferOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnDeferOrder
	static int Packet2Struct(RtnDeferOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnDeferOrder
	static int Struct2Packet(RtnDeferOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRspDeferOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspDeferOrderCancel
	static int Packet2Struct(RspDeferOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspDeferOrderCancel
	static int Struct2Packet(RspDeferOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRtnDeferOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnDeferOrderCancel
	static int Packet2Struct(RtnDeferOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnDeferOrderCancel
	static int Struct2Packet(RtnDeferOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRspDeferDeliveryAppOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspDeferDeliveryAppOrder
	static int Packet2Struct(RspDeferDeliveryAppOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspDeferDeliveryAppOrder
	static int Struct2Packet(RspDeferDeliveryAppOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnDeferDeliveryAppOrder
	static int Packet2Struct(RtnDeferDeliveryAppOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnDeferDeliveryAppOrder
	static int Struct2Packet(RtnDeferDeliveryAppOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRspDeferDeliveryAppOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspDeferDeliveryAppOrderCancel
	static int Packet2Struct(RspDeferDeliveryAppOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspDeferDeliveryAppOrderCancel
	static int Struct2Packet(RspDeferDeliveryAppOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnDeferDeliveryAppOrderCancel
	static int Packet2Struct(RtnDeferDeliveryAppOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnDeferDeliveryAppOrderCancel
	static int Struct2Packet(RtnDeferDeliveryAppOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRspMiddleAppOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspMiddleAppOrder
	static int Packet2Struct(RspMiddleAppOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspMiddleAppOrder
	static int Struct2Packet(RspMiddleAppOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRtnMiddleAppOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnMiddleAppOrder
	static int Packet2Struct(RtnMiddleAppOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnMiddleAppOrder
	static int Struct2Packet(RtnMiddleAppOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	



	//----------------------------------------------���Ľӿ� [onRecvRspMiddleAppOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspMiddleAppOrderCancel
	static int Packet2Struct(RspMiddleAppOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspMiddleAppOrderCancel
	static int Struct2Packet(RspMiddleAppOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	



	//----------------------------------------------���Ľӿ� [onRecvRtnMiddleAppOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnMiddleAppOrderCancel
	static int Packet2Struct(RtnMiddleAppOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnMiddleAppOrderCancel
	static int Struct2Packet(RtnMiddleAppOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRtnForwardOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnForwardOrder
	static int Packet2Struct(RtnForwardOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnForwardOrder
	static int Struct2Packet(RtnForwardOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRspForwardOrder] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspForwardOrder
	static int Packet2Struct(RspForwardOrder& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspForwardOrder
	static int Struct2Packet(RspForwardOrder& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRspForwardOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRspForwardOrderCancel
	static int Packet2Struct(RspForwardOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRspForwardOrderCancel
	static int Struct2Packet(RspForwardOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	//----------------------------------------------���Ľӿ� [onRecvRtnForwardOrderCancel] ���Ľṹ��ؽ���
	// ���Ľ��������� -> �ṹ    onRecvRtnForwardOrderCancel
	static int Packet2Struct(RtnForwardOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Packet2Struct(stBody.stBody,pkt);
		pkt.GetParameterVal("acctNo"            , stBody.acctNo);
		Packet2Struct(stBody.stRsp,pkt);
		return 0;
	};


	// ���Ľ����� �ṹ -> ����    onRecvRtnForwardOrderCancel
	static int Struct2Packet(RtnForwardOrderCancel& stBody, CBroadcastPacket& pkt)
	{
		Struct2Packet(stBody.stBody,pkt);
		pkt.AddParameter("acctNo"            , stBody.acctNo);
		Struct2Packet(stBody.stRsp,pkt);		
		return 0;
	};  	


	// ���Ľ����� �ṹ -> ����    onRecvRtnForwardOrderCancel
	/*static int Packet2Struct(WindVane& stBody, CBroadcastPacket& pkt)
	{
		pkt.GetParameterVal("prod_code"            , stBody.prod_code);
		pkt.GetParameterVal("memo"                 , stBody.memo);
		pkt.GetParameterVal("moreStorPer"          , stBody.moreStorPer);
		pkt.GetParameterVal("openMoreStorAvg"      , stBody.openMoreStorAvg);
		pkt.GetParameterVal("haveMoreSotrAvg"      , stBody.haveMoreSotrAvg);
		pkt.GetParameterVal("haveMoreStorPer"      , stBody.haveMoreStorPer);
		pkt.GetParameterVal("nullStorPer"          , stBody.nullStorPer);
		pkt.GetParameterVal("openNullSotrAvg"      , stBody.openNullSotrAvg);
		pkt.GetParameterVal("haveNullSotrAvg"      , stBody.haveNullSotrAvg);
		pkt.GetParameterVal("haveNullStorPer"      , stBody.haveNullStorPer);
		pkt.GetParameterVal("lookPer"              , stBody.lookPer);

		return 0;
	};  	*/
};
