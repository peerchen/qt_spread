#pragma once
#include "TraderManager.h"
#include "ViewCommDataDef.h"
#include <string>
#include <vector>
using namespace std;

enum BussType;

class CLxGlobalFun
{
public:
	// ��ʼ����Լ����
	static void IniProdCode();
	// ��ȡ��Լ�����Ӧ��id
	static string GetProdCode();
	static string GetProdCodeID(const string &strName);
	static string GetProdCodeName(const string &strID);
	// ��ʼ����������
	static void IniExchCode();
	// ��ȡ��������id
	static string GetExchCode();
	static string GetCurrency(TRADE_MONEY_KIND type);
	static string GetCurrency(const string & type);
	static string GetHedgeFlag(POSI_HF_PLAG type);
	static string GetTodayOrYestoday(POSI_DATE m_nPosiDate);
	static wstring CLxGlobalFun::GetPageBussType(BussType  bussType);
	static string GetStatusString(ACCOUNT_STATUS status);
	// ��ʼ����ƽ��־
	static void IniOffsetFlag();
	// ��ȡ��ƽ��־id
	static string GetOffsetFlag(TRADE_OPEN_CLOSE flag);
	// ��ʼ���ֲַ���
	static void IniLongShort();
	// ��ȡ�ֲַ���id
	static string GetLongShort();
	// ��ʼ����ȡ���������˵�
	static void IniAccessWay( bool bAddEmpty = true);
	// ��ȡ��ȡ����id
	static string GetAccessWay();
	static string GetAccessWayID();
	// ��ʼ������Ʒ�ִ���
	static void IniVarietyId();
	// ��ȡ����Ʒ�ִ���ID
	static string GetVarietyId();

    // ���ܣ���vector(v)���һ������ΪstrtitleֵΪstrvalue��pare(p)
	static void PairAdd( vector< pair<string,string> > & v, string strtitle, string strvalue );
	// ���ݽ����г�ID��ȡ�����г�����
	static string GetMarketName(const string &strID);
	// ���ݽ�������ID��ȡ������������
	static string GetTradeTypeName(TRADE_TYPE type);
	// ��ȡ����״̬��������
	static string GetOrderStatus(const int &status);
	// ��ȡ�����ύ״̬
	static string GetSubmitOrderStatus(const int &status);
	static string FormatPrice(const double &price);
	//��ֵת�ַ�
	static string StrFromIntVolume(const int &vol);
	static string StrFromDoubleVolume(const double &vol);
	
	// ���ݿ�ƽ��־ID��ȡ��ƽ��־����
	static string GetOffset_flagName(const string &strID);
	// ���ݽ��ձ�־ID��ȡ���ձ�־����
	static string GetDeli_flagName(const string &strID);
	// ������������ID��ȡ������������
	static string GetBuySellName(TRADE_DIRECTION dirct);
	// ����ί��״̬ID��ȡί��״̬����
	static string GetEntr_statName(const string &strID);
	// ���ݳ�����־ID��ȡ������־����
	static string GetCancel_flagName(const string &strID);
	// ���ݲ�������ID��ȡ������������
	static string GetAccessWayName(const string &strID);
	// ���ݸ���״̬ID��ȡ����״̬����
	static string GetCheck_staName(const string &strID);
	// ����ת���Ƿ�ɹ�ID��ȡת���Ƿ�ɹ�����
	static string GetIn_account_flagName(const string &strID);
	// ���ݳֲַ���ID��ȡ�ֲַ�������
	static string GetLongShortName(const string &strID);
	// ��������ID��ȡ�������ƣ�����ί������,��������,������Դ��
	static string GetTerm_typeName(const string &strID);
	// ˢ����Ϣʱ���ݴ������id��ȡ�����������
	static string GetBranch(const string &strID); 
	// ����Ʒ��ID��ȡƷ������
	static string GetGetVarietyName(const string &strID);
	// �������״̬ID��ȡ���״̬����
	static string GetTake_statName(const string &strID);
	// �����������ID��ȡ�����������
	static string GetDraw_typeName(const string &strID);
	// ����֤������ID��ȡ֤����������
	static string GetCert_typeName(const string &strID);
   
	// ˢ����Ϣʱ�����˻�״̬id��ȡ�˻�״̬����
	static string GetAcct_stat(const string &strID);     
    
	// �ж�һ���ֶ�ID�Ƿ�Ӧ�ø�ʽ��Ϊ������
	static bool IsFloatTitle(string strID);
	static int StringXiaoAdd1(string &strFloat);
    // ��ʽ��������
	static string FormatFloat(string strFloat, bool bQuotation = false);
	// ���Ҫ��ʽ���ĸ������Ƿ�Ϸ�
	static bool CheckFloat(string &sFloat);

	//����ʱ��  int64��Ϊ��
	static  string StrFromInt64(__int64 ntime);

	static wstring Str2Wstr(const char * szData);
	static string t2sA(__int64 ntime);
	static std::string Get16HexRandNumber(const int &iCount);
	static UINT64 HexStrToUINT64(const string &sHexStr);

	//////////////////////////////////////////////////////////////////////////
	//�����߼�����
	//////////////////////////////////////////////////////////////////////////
	//�������
	static void CalcSlipPointPrice(double & dPrice, double dSlipPoint, DIRECTION_TRADETYPE direction);
	//�������¼��Ƿ������µ���
	static bool IsSuperiorPrice(double dOrderPrice, double dQuotePrice, DIRECTION_TRADETYPE direction);
	//ֹ��ֹӯ�������(bStopLoss:TRUEΪֹ��,FALSEΪֹӯ)
	static void CalcSlipPointPriceForStopLossandProfit(double & dPrice, double dSlipPoint, DIRECTION_TRADETYPE direction, BOOL bStopLoss/*=FALSE*/);
	//��ȡ���ּ�
	static int GetOpponentPrice(DIRECTION_TRADETYPE direction, double & dPrice, double dSellPrice, double dBuyPrice);
	//�Ż�����������
	static void CalcMarketPrice(double & dPrice, TRADEPARSEUNIT &tpu);
	//ֹ��ֹӯ�߼��ж�
	static int JudgeStopLossandProfit(TRADEPARSEUNIT &tpu, TRADEPRICE &tp, BOOL bSimulate);
	//�ƶ�ֹ��ֹӯ�߼��ж�
	//����:tpu �µ�����
	//	   tp ���������ۺͳɽ���(�ɽ���ģ��ʱ��Ҫʹ��)
	//	   bSimulate �Ƿ���ģ�⽻��(TRUE-��, FALSE-��)
	//����ֵ:
	//		0	�ɹ�,������ֹӯֹ�𴫳������ۻ�ɽ���
	//		1	�ɹ�,����ֹӯֹ���ұ���Ԥ���,�ж�ͨ��,����������
	//		2	ʧ��,ָ��������δ�ﵽ
	static int JudgeMoveStopLossandProfit(TRADEPARSEUNIT &tpu, TRADEPRICE &tp, BOOL bSimulate);

    //////////////////////////////////////////////////////////////////////////
	//ģ�⽻����
	//////////////////////////////////////////////////////////////////////////
	//ģ��ƽ���ж��ӿ�
	static int  simu_CloseParse(TRADEPARSEUNIT &tpu, TRADEPRICE &tp);
	//ģ�⿪���ж��ӿ�
	static int  simu_OpenParse(TRADEPARSEUNIT &tpu, TRADEPRICE & tp);
	//�µ��߼�����ϻ���
	static int  logic_MatchEngine(TRADEPARSEUNIT &tpu, TRADEPRICE &tp);


private:
	//kenny  ��ֵ��Ӻ���  
	static int NTCheckPrice(TRADEPARSEUNIT &tpu, double *l_dReportPrice, double *l_dBidPrice);

};






