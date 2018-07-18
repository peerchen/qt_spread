#include "TranMessage.h"

#include "Global.h"
#include "HJConstant.h"
#include "TraderCpMgr.h"
//#include "Business.h"
#include "HJGlobalFun.h"
bool CTranMessage::m_bUseSystemTips = true;

CTranMessage::CTranMessage(void)
{
}

CTranMessage::~CTranMessage(void)
{
}

// ����-1���ʾ���ӷ�����ʧ�� 0 ��ʾ���ӷ������ɹ������ǻ�ȡӦ���������� 1��ʾ�ɹ�
int CTranMessage::Handle6002( Rsp6002 &stRsp6002, const QString &sQueryTag, const ArrayListMsg &almViewField, QVector< pair<QString,QString> > & vecPara, int iCountPerPage, int iCurPage )
{
	int iReturn = -1;

	Req6002 req;
	req.login_branch_id = g_HeaderReq.branch_id;
	req.login_teller_id = g_Global.m_strUserID.toStdString();
	req.oper_flag       = 1;  //����
	req.paginal_num     = iCountPerPage;  // ÿһҳ����Ŀ
	req.curr_page       = iCurPage;       // ��ǰҳ��
	req.query_id        = sQueryTag.toStdString();    // ��ѯ����
	req.alm_view_field  = almViewField;


	if ( 0 == g_TraderCpMgr.HandlePacket6002(stRsp6002, req, "6002", vecPara)) //
	{
		iReturn = GetResult(CHJGlobalFun::str2qstr(stRsp6002.rsp_code));
	}

	DealShowTips(iReturn,CHJGlobalFun::str2qstr( stRsp6002.rsp_code), CHJGlobalFun::str2qstr(stRsp6002.rsp_msg));

	return iReturn;
}

void CTranMessage::DealShowTips( int iReturn, const QString &sCode, QString &sMsg, bool bUseSystemTips )
{
	if(bUseSystemTips)
	{
		if(iReturn == -1)
		{
			//QMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);//, MB_TOPMOST);
		}
		else
		{
			g_TraderCpMgr.CheckRspCode(sCode, sMsg);
		}
	}
}

int CTranMessage::Handle2040( Rsp2040 &rsp2040 )
{
	int iReturn = -1;

	Req2040 req; //��������
	req.oper_flag        = 1;
	req.acct_no          = g_Global.m_strUserID.toStdString();

	if(0 == g_TraderCpMgr.HandlePacket(rsp2040, req, "2040"))
	{
		iReturn = GetResult(CHJGlobalFun::str2qstr(rsp2040.rsp_code));
	}

	DealShowTips(iReturn, CHJGlobalFun::str2qstr( rsp2040.rsp_code), CHJGlobalFun::str2qstr(rsp2040.rsp_msg));

	return iReturn;
}
// ����������
int CTranMessage::Handle4001( Rsp4001 &rsp4001, const QString &sProdCode, double dPrice, int iAmount, const QString &sExchID, int orderType,bool bUseSystemTips )
{
	int iReturn = -1;

	Req4001 req; //��������
	req.oper_flag        = "1";
	req.match_type       = "1";
	req.order_send_type  = "1";
	req.acct_no          = g_Global.m_strUserID.toStdString();
	req.cust_id          = g_Global.m_strUserID.toStdString();
	req.prod_code        = sProdCode.toStdString(); // ��Լ����
	req.entr_price       = dPrice;    // ί�м۸�
	req.entr_amount      = iAmount;   // ί������
	req.order_type       = to_string(orderType);
	g_TraderCpMgr.m_uOrderSerial++;
	req.client_serial_no = g_TraderCpMgr.GetOrderSerialStr().toStdString();

	if(sExchID == CONSTANT_EXCH_CODE_SPOT_BUY || sExchID == CONSTANT_EXCH_CODE_SPOT_SELL) // �ֻ�
	{
		req.b_market_id = CONSTANT_B_MARKET_ID_SPOT;
		req.bs = (sExchID == CONSTANT_EXCH_CODE_SPOT_BUY ? "b" : "s");
	}
	else if(sExchID == CONSTANT_EXCH_CODE_FORWARD_LONG || sExchID == CONSTANT_EXCH_CODE_FORWARD_SHORT) // Զ��
	{
		req.b_market_id = CONSTANT_B_MARKET_ID_FORWARD;
		req.offset_flag = "0";
		req.bs = (sExchID == CONSTANT_EXCH_CODE_FORWARD_LONG ? "b" : "s");
	}
	else // ����
	{
		req.b_market_id = CONSTANT_B_MARKET_ID_DEFER;
		if(sExchID == CONSTANT_EXCH_CODE_DEFER_OPEN_LONG)//���ڿ����
		{
			req.bs          = "b";
			req.offset_flag = "0";
		}
		else if(sExchID == CONSTANT_EXCH_CODE_DEFER_OPEN_SHORT)//���ڿ��ղ�
		{
			req.bs          = "s";
			req.offset_flag = "0";
		}
		else if(sExchID == CONSTANT_EXCH_CODE_DEFER_COV_LONG)//����ƽ���
		{
			req.bs          = "s";
			req.offset_flag = "1";
			req.cov_type    = "1";
		}
		else if(sExchID == CONSTANT_EXCH_CODE_DEFER_COV_SHORT)//����ƽ�ղ�
		{
			req.bs          = "b";
			req.offset_flag = "1";
			req.cov_type    = "1";
		}
		else if(sExchID == CONSTANT_EXCH_CODE_DELIVERY_LONG)//�����ս�
		{
			req.bs        = "b";
			req.deli_flag = "1";
		}
		else if(sExchID == CONSTANT_EXCH_CODE_DELIVERY_SHORT)//���ڽ���
		{
			req.bs        = "s";
			req.deli_flag = "1";
		}
		else if(sExchID == CONSTANT_EXCH_CODE_MIDD_DELIVERY_LONG)//�����������ս�
		{
			req.bs        = "b";
			req.deli_flag = "2";
		}
		else if(sExchID == CONSTANT_EXCH_CODE_MIDD_DELIVERY_SHORT)//���������ֽ���
		{
			req.bs        = "s";
			req.deli_flag = "2";
		}
	}

	if(0 == g_TraderCpMgr.HandlePacket(rsp4001, req, sExchID))
	{
		iReturn = GetResult(rsp4001.rsp_code.c_str());
	}

	/*WLog(E_LOG_NORMAL,
		"�û��µ���%s�����ر����ţ�%s����������(%s %s)",
		Business::GetOrderInfo(sProdCode,dPrice,iAmount,sExchID),
		rsp4001.local_order_no.toLatin1(),
		rsp4001.rsp_code.toLatin1(),
		rsp4001.rsp_msg.toLatin1());*/

	DealShowTips(iReturn, rsp4001.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp4001.rsp_msg), bUseSystemTips);

	return iReturn;
}

// ����ƽ��������������ӷ�����ʧ�ܷ���-1�����ر����쳣����1����������0
int CTranMessage::Handle4071( Rsp4071 &rsp4071, const QString &sProdCode, const QString &sType, const QString &sPrice, int iAmount )
{
	int iReturn = -1;

	Req4071 req; //��������
	req.oper_flag  = 1;
	req.acct_no    = g_Global.m_strUserID.toStdString(); // �û�id;
	req.prod_code  = sProdCode.toStdString();            // ��Լ����
	req.cov_bs     = sType.toStdString();                // ƽ������
	req.cov_price  = sPrice.toStdString();               // ƽ�ּ۸�
	req.cov_amount = iAmount;              // ƽ������

	if(0 == g_TraderCpMgr.HandlePacket(rsp4071, req, "4071"))
	{
		iReturn = GetResult(rsp4071.rsp_code.c_str());
	}

	DealShowTips(iReturn, rsp4071.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp4071.rsp_msg));

	return iReturn;
}

int CTranMessage::Handle1005( Rsp1005 &rsp1005 )
{
	int iReturn = -1;

	Req1005 req; //��������
	req.oper_flag  = 1;

	if(0 == g_TraderCpMgr.HandlePacket(rsp1005, req, "1005"))
	{
		iReturn = GetResult(rsp1005.rsp_code.c_str());
	}

	DealShowTips(iReturn, rsp1005.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp1005.rsp_msg));

	return iReturn;
}

int CTranMessage::Handle9030( Rsp9030 &rsp9030, const QString &sParaID )
{
	int iReturn = -1;

	Req9030 req; //��������
	req.oper_flag  = 1;
	req.para_id = sParaID.toStdString();

	if(0 == g_TraderCpMgr.HandlePacket(rsp9030, req, "9030"))
	{
		iReturn = GetResult(rsp9030.rsp_code.c_str());
	}

	DealShowTips(iReturn, rsp9030.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp9030.rsp_msg));

	return iReturn;
}

int CTranMessage::Handle3099( Rsp3099 &rsp3099, bool bUseSystemTips )
{
	int iReturn = -1;

	Req3099 req; //��������
	req.oper_flag     = 0;

	if(0 == g_TraderCpMgr.HandlePacket(rsp3099, req, "3099"))
	{
		iReturn = GetResult(rsp3099.rsp_code.c_str());
	}

	DealShowTips(iReturn, rsp3099.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp3099.rsp_msg), bUseSystemTips);

	return iReturn;
}

int CTranMessage::Handle3064( Rsp3064 &rsp3064, bool bUseSystemTips )
{
	int iReturn = -1;

	Req3064 req3064; //��������
	req3064.oper_flag   = 2;
	req3064.acct_no     = g_HeaderReq.user_id;
	
	if(0 == g_TraderCpMgr.HandlePacket(rsp3064, req3064, "3064"))
	{
		iReturn = GetResult(rsp3064.rsp_code.c_str());
	}

	DealShowTips(iReturn, rsp3064.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp3064.rsp_msg), bUseSystemTips);

	return iReturn;
}

int CTranMessage::Handle1020( Rsp1020 &rsp1020, char cCusInfo, char cFund, char cStorage, char cForward, char cDefer, char cSurplus, bool bUseSystemTips )
{
	int iReturn = -1;

	Req1020 req1020; //��������
	req1020.is_check_stat = "1";
	req1020.oper_flag     = 1;
	req1020.acct_no       = g_Global.m_strUserID.toStdString();

	req1020.qry_cust_info = cCusInfo;
	req1020.qry_fund      = cFund;
	req1020.qry_storage   = cStorage;
	req1020.qry_forward   = cForward;
	req1020.qry_defer     = cDefer;
	req1020.qry_surplus   = cSurplus;

	if(0 == g_TraderCpMgr.HandlePacket(rsp1020, req1020, "1020"))
	{
		iReturn = GetResult(rsp1020.rsp_code.c_str());
	}

	DealShowTips(iReturn, rsp1020.rsp_code.c_str(),CHJGlobalFun::str2qstr( rsp1020.rsp_msg), bUseSystemTips);

	return iReturn;
}

//
int CTranMessage::Handle3101( Rsp3101 &rsp3101, int iOper_flag, const QString &sAccess_way /*= ""*/, double dExch_bal /*= 0*/, char *pcFund_pwd /*= NULL*/, bool bUseSystemTips /*= true*/ )
{
	int iReturn = -1;

	Req3101 req; //��������

	// ������ʶ
	req.oper_flag  = iOper_flag;
	// �ͻ����
	req.acct_no    = g_Global.m_strUserID.toStdString();

	// ��ȡ���򣨴��룬ȡ����
	req.access_way = sAccess_way.toStdString();
	
	// �������
	req.exch_bal   = dExch_bal;

	//  �ʽ�����
	if(pcFund_pwd)
	{
		// ��Ϊ���ģ��ϵͳ���õ��Ƕ�MD5
		#if (defined _VERSION_PA) && (!(defined RUN_EMULATOR)) 
		req.fund_pwd   = g_TraderCpMgr.GetEncryptPSW(pcFund_pwd, false).toStdString();
		#else
		req.fund_pwd   = g_TraderCpMgr.GetEncryptPSW(pcFund_pwd, false).toStdString();//true  ->  false
		#endif
	}

	if(0 == g_TraderCpMgr.HandlePacket(rsp3101, req, "3101"))
	{
		iReturn = GetResult(rsp3101.rsp_code.c_str());
	}

	// ���ݽ���ͨ���Ե�Ҫ���ʽ������������ʱ���÷��������ص���ʾ̫רҵ���޸�Ϊ�ռ���
	if( strcmp(rsp3101.rsp_code.c_str(), "HJ2002  ") == 0)
		rsp3101.rsp_msg = "�ʽ����벻��ȷ��";
		
	DealShowTips(iReturn, rsp3101.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp3101.rsp_msg), bUseSystemTips);

	return iReturn;
}

int CTranMessage::Handle3021( Rsp3021 &rsp3021,  int iOper_flag, const QString &sPsw, 
							 const QString &sAccess_way /*= ""*/, double dExch_bal /*= 0*/, 
							 bool bFundPsw/* = true*/, bool bUseSystemTips /*= true*/ )
{
	int iReturn = -1;

	Req3021 req; //��������

	//������ʶ
	req.oper_flag  = iOper_flag;
	//�ͻ����
	req.acct_no    = g_Global.m_strUserID.toStdString();

	//��ȡ���򣨴��룬ȡ����
	if(!sAccess_way.isEmpty())
	{
		req.access_way = sAccess_way.toStdString();
	}

	//�������
	req.exch_bal   = dExch_bal;

	//�ʽ�����
	if(bFundPsw)
		req.fund_pwd   = g_TraderCpMgr.GetEncryptPSW(sPsw.toLatin1(), true).toStdString();
	else
	{
		req.card_pwd  = sPsw.toStdString();
	}

	//���ӷ�����
	if(0 == g_TraderCpMgr.HandlePacket(rsp3021, req, "3021"))
	{
		iReturn = GetResult(rsp3021.rsp_code.c_str());
	}

	DealShowTips(iReturn, rsp3021.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp3021.rsp_msg), bUseSystemTips);

	return iReturn;
}

int CTranMessage::Handle4061( Rsp4061 &rsp4061, const QString &sOrderNo )
{
	int iReturn = -1;

	Req4061 req; //��������

	// ���������ֵ
	req.oper_flag   = 1;
	req.cancel_order_no     = sOrderNo.toStdString();

	if(0 == g_TraderCpMgr.HandlePacket(rsp4061, req, "4061"))
	{
		iReturn = GetResult(rsp4061.rsp_code.c_str());
	}

	DealShowTips(iReturn, rsp4061.rsp_code.c_str(), CHJGlobalFun::str2qstr(rsp4061.rsp_msg));

	/*WLog(E_LOG_NORMAL,
		"�û������������ţ�%s����������(%s %s)",
		sOrderNo.toLatin1(),
		rsp4061.rsp_code.toLatin1(),
		rsp4061.rsp_msg.toLatin1());*/

	return iReturn;
}

int CTranMessage::GetResult( const QString& sRspCode )
{
	return (strcmp(sRspCode.toLatin1(), RSP_SUCCESS_CODE) == 0 ? 0 : 1);
}

