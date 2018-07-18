#include "LxGlobalFun.h"


// �����г����ͣ�strMarketID����ʼ����Լ����
void CLxGlobalFun::IniProdCode()
{
	
}

/*
��ȡ��Լ�����Ӧ��id
*/
string CLxGlobalFun::GetProdCode()
{

	return "";
}
string CLxGlobalFun::GetProdCodeName(const string &strID)
{
	return "";
}


string CLxGlobalFun::GetCurrency(TRADE_MONEY_KIND type)
{
	string strTmp = "";
	switch (type)
	{
	case TD_CNY:
		strTmp = "�����";
		break;
	case TD_USD:
		strTmp = "��Ԫ";
		break;
	case TD_GBP:
		strTmp = "Ӣ��";
		break;
	case TD_JPY:
		strTmp = "��Ԫ";
		break;
	case TD_HKD:
		strTmp = "�۱�";
		break;
	case TD_CAD:
		strTmp = "���ô�Ԫ";
		break;
	case TD_EUR:
		strTmp = "ŷԪ";
		break;
	case TD_AUD:
		strTmp = "��Ԫ";
	case TD_CHF:
		strTmp = "��ʿ����";
		break;
	case TD_RUB:
		strTmp = "����˹¬��";
		break;
    default:	
		strTmp = "��������";
		break;
	}

	return strTmp;
}

string CLxGlobalFun::GetCurrency(const string & type)
{
	string strTmp = type;
	if (type == "CNY")
	{
		return "�����";
	}
	else if (type == "USD")
	{
		return  "��Ԫ";
	}
	else if (type == "GBP")
	{
		return "Ӣ��";
	}
	else if (type == "JPY")
	{
		return "��Ԫ";
	}
	else if (type == "HKD")
	{
		return "�۱�";
	}
	else if (type == "CAD")
	{
		return "���ô�Ԫ";
	}
	else if (type == "EUR")
	{
		return "ŷԪ";
	}
	else if (type == "AUD")
	{
		return "��Ԫ";
	}
	else if (type == "CHF")
	{
		return "��ʿ����";
	}
	else if (type == "RUB")
	{
		return "����˹¬��";
	}else
	{
		return "�����";//��������
	}

	return "";
}

/*
��ȡ��������
*/
string CLxGlobalFun::GetExchCode()
{
	string strTmp = "";
	/*switch (type)
	{
	case FTDC_TRDT_deault:
		strTmp = "δ֪";
		break;
	case RDT_SplitCombination:
		strTmp = "��ϳֲֲ��Ϊ��һ�ֲ�,��ʼ����Ӧ���������͵ĳֲ�";
		break;
	case FTDC_TRDT_Common:
		strTmp = "��ͨ�ɽ�";
		break;
	case FTDC_TRDT_OptionsExecution:
		strTmp = "��Ȩִ��";
		break;
	case FTDC_TRDT_OTC:
		strTmp = "OTC�ɽ�";
		break;
	case FTDC_TRDT_EFPDerived:
		strTmp = "��ת�������ɽ�";
		break;
	case FTDC_TRDT_CombinationDerived:
		strTmp = "��������ɽ�";
		break;
	default:
		strTmp = "δ֪";
		break;
	}*/

	return strTmp;
}
// ��ʼ����ƽ��־
void CLxGlobalFun::IniOffsetFlag()
{
}


string CLxGlobalFun::FormatPrice(const double &price)
{
	char   szTmp[32] = {0};
	sprintf(szTmp, "%.2f", price);
	return szTmp;
}

string CLxGlobalFun::StrFromIntVolume(const int &vol)
{
	char   szTmp[32] = { 0 };
	sprintf(szTmp, "%d", vol);
	return szTmp;

}

string CLxGlobalFun::StrFromDoubleVolume(const double &vol)
{
	char   szTmp[32] = { 0 };
	sprintf(szTmp, "%.2f", vol);
	return szTmp;
}


/*
��ȡ��ƽ��־
*/
string CLxGlobalFun::GetOffsetFlag(TRADE_OPEN_CLOSE flag)
{
	if (flag == TOC_OPEN)
	{
		return "��";
	}
	else if (flag == TOC_CLOSE)
	{
		return "ƽ";
	}
	else if (flag == TOC_EXTENT)
	{
		return "����";
	}
	else if (flag == TOC_ForceClose)
	{
		return "ǿƽ";
	}
	else if (flag == TOC_CLOSE_Today)
	{
		return "ƽ��";
	}
	else if (flag == TOC_Close_Yesterday)
	{
		return "ƽ";// "ƽ��";����չʾΪ"ƽ"
	}
	else if (flag == TOC_ForceOff)
	{
		return "ǿ��";
	}
	else if (flag == TOC_LocalForceClose)
	{
		return "����ǿƽ";
	}

	return "";
}
// ��ʼ���ֲַ��������˵�
void CLxGlobalFun::IniLongShort()
{
	
}
// ��ȡ�ֲַ���id
string CLxGlobalFun::GetLongShort()
{
	return "";
	
}

// ��ȡ��ȡ����id
std::string CLxGlobalFun::GetAccessWay()
{
	return "";
	
}

// ��ʼ������Ʒ�ִ���
void CLxGlobalFun::IniVarietyId()
{
}

// ��ȡ����Ʒ�ִ���ID
std::string CLxGlobalFun::GetVarietyId()
{
	return "";
}



/*
���ܣ���vector(v)���һ������ΪstrtitleֵΪstrvalue��pare(p)
v vector
p ������
strtitile ����
strvalue �����ֵ
*/
void CLxGlobalFun::PairAdd(vector< pair<string, string> > & v, string strtitle, string strvalue)
{
	pair<string,string> p;
	p.first  = strtitle;
	p.second = strvalue;
	v.push_back(p);
}



// ���ݽ����г�ID��ȡ�����г�����
std::string CLxGlobalFun::GetMarketName(const string &strID)
{
	//���������г�

	return strID;
}

std::string CLxGlobalFun::GetHedgeFlag(POSI_HF_PLAG type)
{
	string strTmp;
	switch (type)
	{
	case THOST_HF_Speculation:
		strTmp = "Ͷ��";
		break;
	case THOST_HF_Arbitrage:
		strTmp = "����";
		break;
	case THOST_HF_Hedge:
		strTmp = "�ױ�";
		break;
	case THOST_HF_MarketMaker:
		strTmp = "������";
		break;
	default:
		strTmp = "";
		break;
	}

	return  strTmp;
}

string CLxGlobalFun::GetTodayOrYestoday(POSI_DATE m_nPosiDate)
{
	string strTmp;
	switch (m_nPosiDate)
	{
	case THOST_FTDC_POSI_TODAY:
		strTmp = "���";
		break;
	case THOST_FTDC_POSI_HISTORY:
		strTmp = "���";
		break;
	default:
		strTmp = "";
		break;
	}

	return  strTmp;
}

string CLxGlobalFun::GetStatusString(ACCOUNT_STATUS status)
{
	string str;
	switch (status)
	{
	case AS_NULL:
		str = "���˺�";
		break;
	case AS_NORMAL:
		str = "������δ��¼��";
		break;
	case AS_LOGINING:
		str = "��¼��...";
		break;
	case AS_LOGIN:
		str = "�ѵ�¼";
		break;
	case AS_CONNECTED:
		str = "������";
		break;
	case AS_DISCONNECTED:
		str = "���ӶϿ�";
		break;
	case AS_GET_INVESTOR:
		str = "ȡ��Ͷ��������";
		break;
	case AS_GET_INSTRUMENTED:
		str = "ȡ�ý�������Լ��Ϣ";
		break;
	case AS_ACCOUNT_CAPITAL_UPDATE:
		str = "�˻��ʽ����";
		break;
	case AS_POSITIONS_UPDATE:
		str = "�ֲָ���";
		break;
	case AS_POSITIONS_DETAIL_UPDATE:
		str = "�ֲ���ϸ����";
		break;
	case AS_TRANS_UPDATE:
		str = "�ɽ���ϸ����";
		break;
	case AS_CONNIMTS_UPDATE:
		str = "ί�б�������";
		break;
	default:
		str = "δ֪״̬";
		break;
	}

	return str;
}



string CLxGlobalFun::GetOrderStatus(const int &status)
{
	string  strTmp = "";
	switch (status)
	{
	case tos_default:
		strTmp = "δ֪";
		break;
	case tos_ordering:
		strTmp = "ί����";
		break;
	case tos_ordered:
		strTmp = "ί�гɹ�";
		break;
	case tos_orderfailed:
		strTmp = "ί��ʧ��";
		break;
	case tos_tradeing:
		strTmp = "���ֳɽ�";
		break;
	case tos_traded:
		strTmp = "�ɽ����";
		break;
	case tos_cancling:
		strTmp = "������";
		break;
	case tos_cancled:
		strTmp = "�����ɹ�";
		break;
	case tos_canclfailed:
		strTmp = "����ʧ��";
		break;

	default:
		break;
	}

	return  strTmp;
}

// ��ȡ�����ύ״̬
string CLxGlobalFun::GetSubmitOrderStatus(const int &status)
{
	string  strTmp = "";
	switch (status)
	{
	case tos_submit_default:
		strTmp = "�ύ��";
		break;
	case tos_Inserted:
		strTmp = "�����Ѿ��ύ";
		break;
	case tos_Cancel:
		strTmp = "�����Ѿ��ύ";
		break;
	case tos_Modify:
		strTmp = "�޸��Ѿ��ύ";
		break;
	case tos_Accepted:
		strTmp = "�Ѿ�����";
		break;
	case tos_InsertRejected:
		strTmp = "�����Ѿ����ܾ�";
		break;
	case tos_CancelRejected:
		strTmp = "�����Ѿ����ܾ�";
		break;
	case tos_ModifyRejected:
		strTmp = "�ĵ��Ѿ����ܾ�";
		break;

	default:
		break;
	}

	return  strTmp;
}

// ���ݽ�������ID��ȡ������������
std::wstring CLxGlobalFun::GetPageBussType(BussType  bussType)
{
	wstring m_strType = L"";
	switch (bussType)
	{
	case EProgramRuntime:
		m_strType = L"����ʵ��";
		break;
	case EManualRuntime:
		m_strType = L"�ֶ�ʵ��";
		break;
	
	case EManualSimu:
		m_strType = L"�ֶ�ʵ��";
		break;
	case EManualRuntimeSimu:
		m_strType = L"�ֶ�ʵʱģ��";
		break;
	case EProgramRuntimeSimu:
		m_strType = L"����ʵʱģ��";
		break;
	case EManulaHis:
		m_strType = L"�ֶ���ʷģ��";
		break;
	case EStaticTest:
		m_strType = L"��̬����";
	case EDYNTest:
		m_strType = L"��̬����";
		break;
	default:
		m_strType = L"δ֪";
		break;
	}

	return m_strType;
}

// ���ݽ�������ID��ȡ������������
std::string CLxGlobalFun::GetTradeTypeName(TRADE_TYPE type)
{
	string strTmp = "";
	switch (type)
	{
	case FTDC_TRDT_deault:
		strTmp = "δ֪";
		break;
	case RDT_SplitCombination:
		strTmp = "��ϳֲֲ��Ϊ��һ�ֲ�,��ʼ����Ӧ���������͵ĳֲ�";
		break;
	case FTDC_TRDT_Common:
		strTmp = "��ͨ�ɽ�";
		break;
	case FTDC_TRDT_OptionsExecution:
		strTmp = "��Ȩִ��";
		break;
	case FTDC_TRDT_OTC:
		strTmp = "OTC�ɽ�";
		break;
	case FTDC_TRDT_EFPDerived:
		strTmp = "��ת�������ɽ�";
		break;
	case FTDC_TRDT_CombinationDerived:
		strTmp = "��������ɽ�";
		break;
	default:
		strTmp = "δ֪";
		break;
	}

	return strTmp;
}
// ���ݿ�ƽ��־ID��ȡ��ƽ��־����
std::string CLxGlobalFun::GetOffset_flagName(const string &strID)
{
	return strID;
}

// ������������ID��ȡ������������
//�����������������Ƕ࣬��
std::string CLxGlobalFun::GetBuySellName(TRADE_DIRECTION dirct)
{
	if (dirct == TD_BUY)
	{
		return "��";//��Ϊ�࣬����������һ��
	}
	else if (dirct == TD_SELL)
	{
		return "��";//
	}
	return "";
}
// ����ί��״̬ID��ȡί��״̬����
std::string CLxGlobalFun::GetEntr_statName(const string &strID)
{
	return strID;
}
// ���ݳ�����־ID��ȡ������־����
std::string CLxGlobalFun::GetCancel_flagName(const string &strID)
{
	
	return strID;
}
// ���ݲ�������ID��ȡ������������
std::string CLxGlobalFun::GetAccessWayName(const string &strID)
{
	
	return strID;
}

// ����ת���Ƿ�ɹ�ID��ȡת���Ƿ�ɹ�����
std::string CLxGlobalFun::GetIn_account_flagName(const string &strID)
{
	if(strID == "1")
	{
		return "��";
	}
	else
	{
		return strID;
	}
}
// ���ݳֲַ���ID��ȡ�ֲַ�������
std::string CLxGlobalFun::GetLongShortName(const string &strID)
{

	return strID;
}
// ��������ID��ȡ�������ƣ�����ί������,��������,������Դ��
std::string CLxGlobalFun::GetTerm_typeName(const string &strID)
{

	return strID;
}
// ˢ����Ϣʱ�����˻�״̬id��ȡ�˻�״̬����
std::string CLxGlobalFun::GetAcct_stat(const string &strID)
{

	return strID;
}
// ����Ʒ��ID��ȡƷ������
std::string CLxGlobalFun::GetGetVarietyName(const string &strID)
{
	return strID;
}




// �ж�һ���ֶ�ID�Ƿ�Ӧ�ø�ʽ��Ϊ������
bool CLxGlobalFun::IsFloatTitle(string strID)
{
	return false;
}
bool CLxGlobalFun::CheckFloat(string &sFloat)
{
	int iLen = sFloat.length();
	if(iLen != 0)
	{
		char ch;
		bool bHasPoint = false;
		for(int i = 0; i < iLen; i++)
		{
			ch = sFloat[i];
			if(ch < '0' || ch > '9') // �����������
			{
				if(ch == '-' && i == 0 && iLen > 1) // ����Ǹ��ţ������ǵ�һ���������ַ������ȴ���1����ͨ��
				{
					continue;
				}
				else if(ch == '.' && !bHasPoint) // �����С���㣬���һ�û���ֹ�
				{
					bHasPoint = true;
					if(i == 0 || i == iLen -1)
					{
						return false;
					}
					else
					{
						continue;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}


/*
��С�����ּ�1������н�λ�������Ļ����򷵻�1�����򷵻�0
���磺strFloat = "4445"��ִ�к�strFloatΪ"4446"
*/
int CLxGlobalFun::StringXiaoAdd1(string &strFloat)
{
	int  iLen    = strFloat.length();
	int  iCount  = iLen -1;
	int  iReturn = 0;

	//�ҵ����ұ߿�ʼ��һ������9���������ҽ���֮ǰ��ȫ����Ϊ0������"8999"�����Ϊ"9000"
	char cTemp  = strFloat.at(iCount);
	while(cTemp == '9' && iCount > 0)
	{
		// ��Ϊ9��������0����Ϊ��1��
		strFloat.at(iCount) = '0'; //����λ��0
		iCount--;
		cTemp = strFloat.at(iCount);
	}

	//����ǵ�0������cTemp��9���򷵻�ֵΪ1������Ϊ0
	if(iCount == 0 && cTemp == '9')
	{
		strFloat.at(iCount) = '0';
		iReturn++;	
	}
	else//�ַ�����1
	{
		cTemp++;
		strFloat.at(iCount) = cTemp;
	}

	return iReturn;
}


// �������״̬ID��ȡ���״̬����
std::string CLxGlobalFun::GetTake_statName(const string &strID)
{
	
	return strID;
}

// ����֤������ID��ȡ֤����������
std::string CLxGlobalFun::GetCert_typeName(const string &strID)
{
	
	return strID;
}


string CLxGlobalFun::StrFromInt64(__int64 ntime)
{
	string ret = "";
	char sz[128] = { 0 };
	if (ntime != 0)
	{
		tm t;
		localtime_s(&t, &ntime);
		//gmtime_s(&t, &ntime);
		strftime(sz, 128, "%Y-%m-%d %H:%M:%S", &t);
		ret = sz;
	}
	return ret;
}

std::string CLxGlobalFun::Get16HexRandNumber(const int &iCount)
{
	srand((unsigned)time(NULL)); // ��ʱ��������

	const char *pHexUnit = "0123456789abcdef"; // �������飬��¼16���Ƶ������ַ�
	const int iUnitNum = 16; // ��λ�ĸ�����������16���ƣ�����16����λ

	string sNum;
	for (int i = 0; i < iCount; i++)
	{
		if (i == 0)
		{
			// ��һλֻ�����ֻ����e���������к����Ӻ����
			sNum.append(1, *(pHexUnit + rand() % (iUnitNum - 1))); // ��sNum�������һ���ַ�
		}
		else
		{
			sNum.append(1, *(pHexUnit + rand() % iUnitNum)); // ��sNum�������һ���ַ�
		}
	}

	return sNum;

}

// ˼·������"A1A2A3A4"�����ʾΪ(((A1)*16+A2)*16+A3)*16+A4 �൱�� A1*16*6*16+A2*16*16+A3*16+A4
UINT64 CLxGlobalFun::HexStrToUINT64(const string &sHexStr)
{
	int iLen = sHexStr.length();
	UINT64 u64 = 0;

	char ch;
	for (int i = 0; i < iLen; i++)
	{
		ch = sHexStr[i];
		if ((ch <= 'F'&& ch >= 'A') || (ch >= '0' && ch <= '9') || (ch <= 'f' && ch >= 'a'))
		{
			if (ch <= '9' && ch >= '0') // �����0-9������
				u64 = u64 * 16 + (ch - 0x30);
			else if (ch <= 'F' && ch >= 'A') // ����Ǵ�д����λ��
				u64 = u64 * 16 + (10 + ch - 'A');//(10 + ch - 'A') ��ø��ַ�ʵ�ʱ�ʾ�����θ�ʽ������ ch = 'A'�������Ϊ10
			else // �����Сд����λ��
				u64 = u64 * 16 + (10 + ch - 'a');
		}
		else
		{
			// ���������Ҫ���򷵻�-1
			return -1;
		}
	}

	return u64;

}



//�������
void CLxGlobalFun::CalcSlipPointPrice(double & dPrice, double dSlipPoint, DIRECTION_TRADETYPE direction)
{
	switch (direction)//����
	{
	case DTT_SHORT_BUY://��(����\ƽ��)
	case DTT_LONG_SELL:
	{
		dPrice -= dSlipPoint;
	}
	break;
	case DTT_LONG_BUY://��(����\ƽ��)
	case DTT_SHORT_SELL:
	{
		dPrice += dSlipPoint;
	}
	break;
	default://Ĭ��Ϊ��
	{
		//no op
	}
	break;
	}
}


//ֹ��ֹӯ�������(bStopLoss:TRUEΪֹ��,FALSEΪֹӯ)
void CLxGlobalFun::CalcSlipPointPriceForStopLossandProfit(double & dPrice, double dSlipPoint, DIRECTION_TRADETYPE direction, BOOL bStopLoss/*=FALSE*/)
{
	switch (direction)//����
	{
	case DTT_SHORT_BUY://��(����\ƽ��)
	case DTT_LONG_SELL:
	{
		if (!bStopLoss)
		{
			//ֹ��
			dPrice += dSlipPoint;
		}
		else
		{
			//ֹӯ
			dPrice -= dSlipPoint;
		}
	}
	break;
	case DTT_LONG_BUY://��(����\ƽ��)
	case DTT_SHORT_SELL:
	{
		if (bStopLoss)
		{
			//ֹ��
			dPrice += dSlipPoint;
		}
		else
		{
			//ֹӯ
			dPrice -= dSlipPoint;
		}
	}
	break;
	default://Ĭ��Ϊ��
	{
		//no op
	}
	break;
	}
}
//�������¼��Ƿ������µ���(����,�������¼�>=�µ���,�ɽ�;����,�����<=�µ���,�ɽ�;���򲻳ɽ�)
//�ɽ��򷵻����¼�Ϊ�ɽ���
//����ֵ:true ��������,���سɽ���
//		 false ����������,�����سɽ���
bool CLxGlobalFun::IsSuperiorPrice(double dOrderPrice, double dQuotePrice, DIRECTION_TRADETYPE direction)
{
	bool result = false;
	switch (direction)//����
	{
	case DTT_SHORT_BUY://��(����\ƽ��)
	case DTT_LONG_SELL:
	{
		if (dOrderPrice <= dQuotePrice)
		{
			result = true;
		}
	}
	break;
	case DTT_LONG_BUY://��(����\ƽ��)
	case DTT_SHORT_SELL:
	{
		if (dOrderPrice >= dQuotePrice)
		{
			result = true;
		}
	}
	break;
	default://Ĭ��Ϊ��
	{
		//no op
	}
	break;
	}

	return result;
}

//��ȡ���ּ�
int CLxGlobalFun::GetOpponentPrice(DIRECTION_TRADETYPE direction, double & dPrice, double dSellPrice, double dBuyPrice)
{
	switch (direction)//����
	{
	case DTT_SHORT_BUY://��(����\ƽ��)
	case DTT_LONG_SELL:
	{
		//���ּ�Ϊ��һ��
		dPrice = dBuyPrice;
	}
	break;
	case DTT_LONG_BUY://��(����\ƽ��)
	case DTT_SHORT_SELL:
	{
		//���ּ�Ϊ��һ��
		dPrice = dSellPrice;
	}
	break;
	default://Ĭ��Ϊ��
	{
		//���ּ�Ϊ��һ��
		dPrice = dBuyPrice;
	}
	break;
	}
	return 0;
}

//�Ż�����������
void CLxGlobalFun::CalcMarketPrice(double & dPrice, TRADEPARSEUNIT &tpu)
{
	if (tpu.bInternal)
	{
		if (tpu.dLowLimitPrice && dPrice < tpu.dLowLimitPrice)
		{
			//����۸���ڵ�ͣ��
			dPrice = tpu.dLowLimitPrice;
		}
		if (tpu.dTopLimitPrice && dPrice > tpu.dTopLimitPrice)
		{
			//����۸������ͣ��
			dPrice = tpu.dTopLimitPrice;
		}
	}
}




//ֹ��ֹӯ�߼��ж�
//����:tpu �µ�����
//	   tp ���������ۺͳɽ���(�ɽ���ģ��ʱ��Ҫʹ��)
//	   bSimulate �Ƿ���ģ�⽻��(TRUE-��, FALSE-��)
//����ֵ:
//		0	�ɹ�,������ֹӯֹ�𴫳������ۻ�ɽ���
//		1	�ɹ�,����ֹӯֹ���ұ���Ԥ���,�ж�ͨ��,����������
//		2	ʧ��,ָ��������δ�ﵽ
int CLxGlobalFun::JudgeStopLossandProfit(TRADEPARSEUNIT &tpu, TRADEPRICE &tp, BOOL bSimulate)
{
	int result = 0;
	int nStopType = 0;//0--��, 1--�ﵽֹ��, 2--�ﵽֹӯ
	double dStopLoss = 0.0f;//ֹ���
	double dStopProfit = 0.0f;//ֹӯ��
	double l_dReportPrice = 0.0f;//������
	double l_dBidPrice = 0.0f;//�ɽ���
	if (tpu.lc.b_stop_loss_flg || tpu.lc.b_stop_profit_flg)
	{
		//�������ֹ��
		if (tpu.lc.b_stop_loss_flg)
		{
			dStopLoss = tpu.dStopBasePrice;
			CalcSlipPointPriceForStopLossandProfit(dStopLoss, tpu.lc.f_stop_loss_leap, tpu.nDirection, TRUE);
		}
		//�������ֹӯ
		if (tpu.lc.b_stop_profit_flg)
		{
			dStopProfit = tpu.dStopBasePrice;
			CalcSlipPointPriceForStopLossandProfit(dStopProfit, tpu.lc.f_stop_profit_leap, tpu.nDirection, FALSE);
		}

		switch (tpu.nDirection)
		{
		case DTT_SHORT_BUY://��(����\ƽ��)
		case DTT_LONG_SELL:
		{
			if (tpu.lc.b_stop_loss_flg && dStopLoss >= tpu.dLatestPrice[0])
			{
				//�ﵽֹ���
				nStopType = 1;
				result = 0;
			}
			else if (tpu.lc.b_stop_profit_flg && dStopProfit <= tpu.dLatestPrice[0])
			{
				//�ﵽֹӯ��
				nStopType = 2;
				result = 0;
			}
			else
			{
				result = 2;//δ��������
			}
		}
		break;
		case DTT_LONG_BUY://��(����\ƽ��)
		case DTT_SHORT_SELL:
		{
			if (tpu.lc.b_stop_loss_flg && dStopLoss <= tpu.dLatestPrice[0])
			{
				//�ﵽֹ���
				nStopType = 1;
				result = 0;
			}
			else if (tpu.lc.b_stop_profit_flg && dStopProfit >= tpu.dLatestPrice[0])
			{
				//�ﵽֹӯ��
				nStopType = 2;
				result = 0;
			}
			else
			{
				result = 2;//δ��������
			}
		}
		break;
		default:
		{
			result = 2;//δ��������
		}
		break;
		}

		if (result == 0)
		{
			//����Ǳ���Ԥ���, ��ﵽֹ��ֹӯ���м�Ϊ�����۷���
			//Modify by ppshuai 2015-12-10����ֹ��ֹӯ�۷���
			if (tpu.lc.e_nt == NT_TRIGGER_PRICE)
			{
				//�ﵽֹӯ��
				if (nStopType == 2)
				{
					l_dReportPrice = dStopProfit;//tpu.dLatestPrice[0];
				}
				//�ﵽֹ���
				else if (nStopType == 1)
				{
					l_dReportPrice = dStopLoss;//tpu.dLatestPrice[0];
				}
				else
				{
					//no op
				}
				//����ó�50��������м�
				//CalcSlipPointPrice(l_dReportPrice, tpu.dLimitDots, tpu.nDirection);
				CalcMarketPrice(l_dReportPrice, tpu);
				tp.dReportPrice = l_dReportPrice;
				result = 1;//��������,ֱ�ӱ���
			}
			else
			{
				result = 0;//��������,�����¸��ӿڸ���ʵ�ʵļ۸����ʱ���(�м�,���ּ�,���¼�,�ŶӼ�)
			}

			//�����ģ�⽻��
			if (bSimulate)
			{
				//////////////////////////////////////////////////////////////////////////
				//�м۱���
				//�����۸�ֵΪ���¼�
				//Modify by ppshuai 2015-12-10����ֹ��ֹӯ�۷���

				//�ﵽֹӯ��
				if (nStopType == 2)
				{
					l_dReportPrice = dStopProfit;//tpu.dLatestPrice[0];
				}
				//�ﵽֹ���
				else if (nStopType == 1)
				{
					l_dReportPrice = dStopLoss;//tpu.dLatestPrice[0];
				}
				else
				{
					//no op
				}
				//����ó�50��������м�
				//CalcSlipPointPrice(l_dReportPrice, tpu.dLimitDots, tpu.nDirection);
				CalcMarketPrice(l_dReportPrice, tpu);
				tp.dReportPrice = l_dReportPrice;

				//�����¼�Ϊ�ɽ���
				l_dBidPrice = tpu.dLatestPrice[0];
				tp.dBidPrice = l_dBidPrice;
			}
		}
	}
	else
	{
		//δ����ֹ���ֹӯ,���������洦��
		result = 0;
	}

	return result;
}

//�ƶ�ֹ��ֹӯ�߼��ж�
//����:tpu �µ�����
//	   tp ���������ۺͳɽ���(�ɽ���ģ��ʱ��Ҫʹ��)
//	   bSimulate �Ƿ���ģ�⽻��(TRUE-��, FALSE-��)
//����ֵ:
//		0	�ɹ�,������ֹӯֹ�𴫳������ۻ�ɽ���
//		1	�ɹ�,����ֹӯֹ���ұ���Ԥ���,�ж�ͨ��,����������
//		2	ʧ��,ָ��������δ�ﵽ
int CLxGlobalFun::JudgeMoveStopLossandProfit(TRADEPARSEUNIT &tpu, TRADEPRICE &tp, BOOL bSimulate)
{
	int result = 0;
	int nStopType = 0;//0--��, 1--�ﵽֹ��, 2--�ﵽֹӯ
	double dStopLoss = 0.0f;//ֹ���
	double dStopProfit = 0.0f;//ֹӯ��
	double l_dReportPrice = 0.0f;//������
	double l_dBidPrice = 0.0f;//�ɽ���
	if (tpu.lc.b_stop_loss_flg || tpu.lc.b_stop_profit_flg)
	{
		//�������ֹ��
		if (tpu.lc.b_stop_loss_flg)
		{
			dStopLoss = tpu.dStopBasePrice;
			CalcSlipPointPriceForStopLossandProfit(dStopLoss, tpu.lc.f_stop_loss_leap, tpu.nDirection, TRUE);
		}
		//�������ֹӯ
		if (tpu.lc.b_stop_profit_flg)
		{
			dStopProfit = tpu.dStopBasePrice;
			CalcSlipPointPriceForStopLossandProfit(dStopProfit, tpu.lc.f_stop_profit_leap, tpu.nDirection, FALSE);
		}

		switch (tpu.nDirection)
		{
		case DTT_SHORT_BUY://��(����\ƽ��)
		case DTT_LONG_SELL:
		{
			if (tpu.lc.b_stop_loss_flg && dStopLoss >= tpu.dLatestPrice[0])
			{
				//�ﵽֹ���
				nStopType = 1;
				result = 0;
			}
			else if (tpu.lc.b_stop_profit_flg && dStopProfit >= tpu.dLatestPrice[0])
			{
				//////////////////////////////////////////////////////////////////////////
				//���¼ۻس���ֹӯ��ʱ����������������Լ��
				//�ﵽֹӯ��
				nStopType = 2;
				result = 0;
			}
			else
			{
				result = 2;//δ��������
			}
		}
		break;
		case DTT_LONG_BUY://��(����\ƽ��)
		case DTT_SHORT_SELL:
		{
			if (tpu.lc.b_stop_loss_flg && dStopLoss <= tpu.dLatestPrice[0])
			{
				//�ﵽֹ���
				nStopType = 1;
				result = 0;
			}
			else if (tpu.lc.b_stop_profit_flg && dStopProfit <= tpu.dLatestPrice[0])
			{
				//////////////////////////////////////////////////////////////////////////
				//���¼ۻس���ֹӯ��ʱ����������������Լ��
				//�ﵽֹӯ��
				nStopType = 2;
				result = 0;
			}
			else
			{
				result = 2;//δ��������
			}
		}
		break;
		default:
		{
			result = 2;//δ��������
		}
		break;
		}

		if (result == 0)
		{
			//����Ǳ���Ԥ���, ��ﵽֹ��ֹӯ���м�Ϊ�����۷���
			//Modify by ppshuai 2015-12-10����ֹ��ֹӯ�۷���
			if (tpu.lc.e_nt == NT_TRIGGER_PRICE)
			{
				//�ﵽֹӯ��
				if (nStopType == 2)
				{
					l_dReportPrice = dStopProfit;//tpu.dLatestPrice[0];
				}
				//�ﵽֹ���
				else if (nStopType == 1)
				{
					l_dReportPrice = dStopLoss;//tpu.dLatestPrice[0];
				}
				else
				{
					//no op
				}
				//����ó�50��������м�
				//CalcSlipPointPrice(l_dReportPrice, tpu.dLimitDots, tpu.nDirection);
				CalcMarketPrice(l_dReportPrice, tpu);
				tp.dReportPrice = l_dReportPrice;
				result = 1;//��������,ֱ�ӱ���
			}
			else
			{
				result = 0;//��������,�����¸��ӿڸ���ʵ�ʵļ۸����ʱ���(�м�,���ּ�,���¼�,�ŶӼ�)
			}

			//�����ģ�⽻��
			if (bSimulate)
			{
				//////////////////////////////////////////////////////////////////////////
				//�м۱���
				//�����۸�ֵΪ���¼�
				//Modify by ppshuai 2015-12-10����ֹ��ֹӯ�۷���

				//�ﵽֹӯ��
				if (nStopType == 2)
				{
					l_dReportPrice = dStopProfit;//tpu.dLatestPrice[0];
				}
				//�ﵽֹ���
				else if (nStopType == 1)
				{
					l_dReportPrice = dStopLoss;//tpu.dLatestPrice[0];
				}
				else
				{
					//no op
				}
				//����ó�50��������м�
				//CalcSlipPointPrice(l_dReportPrice, tpu.dLimitDots, tpu.nDirection);
				CalcMarketPrice(l_dReportPrice, tpu);
				tp.dReportPrice = l_dReportPrice;

				//�����¼�Ϊ�ɽ���
				l_dBidPrice = tpu.dLatestPrice[0];
				tp.dBidPrice = l_dBidPrice;
			}
		}
	}
	else
	{
		//δ����ֹ���ֹӯ,���������洦��
		result = 0;
	}

	return result;
}

//kenny  20170609
int CLxGlobalFun::NTCheckPrice(TRADEPARSEUNIT &tpu, double *l_dReportPrice, double *l_dBidPrice)
{
	int result = 0;
	double dSpecifiedPrice = tpu.lc.f_check_price;

	//������û���
	if (tpu.lc.b_slip_price_flg)
	{
		CalcSlipPointPrice(dSpecifiedPrice, tpu.lc.f_slip_price_leap, tpu.nDirection);
	}

	//ģ�⽻��
	switch (tpu.nDirection)
	{
	case DTT_SHORT_BUY:	//����
	case DTT_LONG_SELL:	//ƽ��
	{
		//ָ����С�ڵ��ڵ�ǰTICK���¼�
		if ((dSpecifiedPrice <= tpu.dLatestPrice[0]))
		{
			*l_dReportPrice = dSpecifiedPrice;
			*l_dBidPrice = tpu.dLatestPrice[0];//���¼۳ɽ�
			result = 0;
		}
		else
		{
			result = 1;//ָ����δ������
		}
	}
	break;
	case DTT_SHORT_SELL://ƽ��
	case DTT_LONG_BUY:	//����
	{
		//ָ���۴��ڵ��ڵ�ǰTICK���¼�
		if ((dSpecifiedPrice >= tpu.dLatestPrice[0]))
		{
			*l_dReportPrice = dSpecifiedPrice;
			*l_dBidPrice = tpu.dLatestPrice[0];//���¼۳ɽ�
			result = 0;
		}
		else
		{
			result = 1;//ָ����δ������
		}
	}
	break;
	default:
	{
		result = 1;//ָ����δ������
	}
	break;
	}

	return result;
}


//�µ��߼�����ϻ���
//����:tpu �µ�����
//	   tp ���������ۺͳɽ���(�ɽ���ģ��ʱ��Ҫʹ��)
//	   bSimulate �Ƿ���ģ�⽻��(TRUE-��, FALSE-��)
//����ֵ:0 �ɹ�,���������ۻ�ɽ���
//		 1 ʧ��,ָ��������δ�ﵽ
int CLxGlobalFun::logic_MatchEngine(TRADEPARSEUNIT &tpu, TRADEPRICE &tp)
{
	int result = 1;//Ĭ�ϲ��ܳɽ�
	double l_dBidPrice = 0.0f;//�ɽ���
	double l_dReportPrice = 0.0f;//������

	//���ݱ������ʴ�ϳɽ�
	switch (tpu.lc.e_nt)
	{
	case NT_MARKET_PRICE://�м�
	{
		//�м��µ�
		l_dReportPrice = tpu.dReportPrice;//tpu.dLatestPrice[0];
		//���¼�+/-50����Ϊ�м�
		CalcSlipPointPrice(l_dReportPrice, tpu.dLimitDots, tpu.nDirection);

		//ģ�⽻��
		if (IsSuperiorPrice(l_dReportPrice, tpu.dLatestPrice[0], tpu.nDirection))
		{
			l_dBidPrice = tpu.dLatestPrice[0];//���¼۳ɽ�
			result = 0;
		}
	}
	break;
	case NT_CHECK_PRICE://ָ����
	{

		result = NTCheckPrice(tpu, &l_dReportPrice,&l_dBidPrice);
		
	}
	break;
	case NT_BIDDING_PRICE://���ּ�
	{
		double dOpponentPrice = 0.0f;
		//��ȡ���ּ�
		GetOpponentPrice(tpu.nDirection, dOpponentPrice, tpu.dSellPrice[0], tpu.dBuyPrice[0]);

		l_dReportPrice = tpu.dReportPrice;//dOpponentPrice;(�Ѿ����˻���ļ۸�)
		//������û���
		if (tpu.lc.b_slip_price_flg)
		{
			//CalcSlipPointPrice(l_dReportPrice, tpu.lc.f_slip_price_leap, tpu.nDirection);
		}

		//ģ�⽻��
		if (IsSuperiorPrice(l_dReportPrice, tpu.dLatestPrice[0], tpu.nDirection))
		{
			l_dBidPrice = tpu.dLatestPrice[0];//���¼۳ɽ�
			result = 0;
		}
	}
	break;
	case NT_TRIGGER_PRICE://����Ԥ���
	{
		//����Ԥ��ۼ�λ������Tick���¼�֮��
		double dEmbeddedPrice = tpu.lc.f_trigger_price;
		//������û���
		if (tpu.lc.b_slip_price_flg)
		{
			CalcSlipPointPrice(dEmbeddedPrice, tpu.lc.f_slip_price_leap, tpu.nDirection);
		}
		//����Ԥ���λ������Tick���¼�֮��
		if (((dEmbeddedPrice <= tpu.dLatestPrice[0]) && (dEmbeddedPrice >= tpu.dLatestPrice[1])) //�������¼� >= ����Ԥ��� >= �ϴ����¼�
			|| ((dEmbeddedPrice >= tpu.dLatestPrice[0]) && (dEmbeddedPrice <= tpu.dLatestPrice[1])))//�������¼� <= ����Ԥ��� <= �ϴ����¼�
		{
			l_dReportPrice = dEmbeddedPrice;
			//ģ�⽻��
			l_dBidPrice = tpu.dLatestPrice[0];//���¼۳ɽ�
			result = 0;
		}
		else
		{
			result = 1;//����Ԥ���δ������
		}
	}
	break;
	case NT_LATEST://���¼�
	{
		l_dReportPrice = tpu.dReportPrice;//tpu.dLatestPrice[0];(�Ѿ����˻���ļ۸�)
		//������û���
		if (tpu.lc.b_slip_price_flg)
		{
			//CalcSlipPointPrice(l_dReportPrice, tpu.lc.f_slip_price_leap, tpu.nDirection);
		}

		//ģ�⽻��
		if (IsSuperiorPrice(l_dReportPrice, tpu.dLatestPrice[0], tpu.nDirection))
		{
			l_dBidPrice = tpu.dLatestPrice[0];//���¼۳ɽ�
			result = 0;
		}
	}
	break;
	case NT_QUEUE://�ŶӼ�
	{
		double dQueuePrice = 0.0f;
		//��ȡ�ŶӼ�
		GetOpponentPrice(tpu.nDirection, dQueuePrice, tpu.dBuyPrice[0], tpu.dSellPrice[0]);
		l_dReportPrice = tpu.dReportPrice;//dQueuePrice;(�Ѿ����˻���ļ۸�)
		//������û���
		if (tpu.lc.b_slip_price_flg)
		{
			//CalcSlipPointPrice(l_dReportPrice, tpu.lc.f_slip_price_leap, tpu.nDirection);
		}
		//ģ�⽻��
		if (IsSuperiorPrice(l_dReportPrice, tpu.dLatestPrice[0], tpu.nDirection))
		{
			l_dBidPrice = tpu.dLatestPrice[0];//���¼۳ɽ�
			result = 0;
		}
	}
	break;
	default://������
	{
		result = 1;//δ��������
	}
	break;
	}

	if (result == 0)
	{
		//�ж��Ƿ񳬹���ͣ���ͣ��,�������������ͣ���ͣ�ۼ���
		CalcMarketPrice(l_dReportPrice, tpu);
		tp.dReportPrice = l_dReportPrice;

		//ģ�⽻��
		tp.dBidPrice = l_dBidPrice;
	}

	return result;
}
//ģ�⿪���ж��ӿ�
//����:tpu �µ�����
//	   tp	���������ۺͳɽ���(ģ��ʱ��Ҫʹ��)
//����ֵ:0 �ɹ�
//		 1 ʧ��,ָ��������δ�ﵽ
//		 2 ʧ��,��Ч�Ľ����ź�
int CLxGlobalFun::simu_OpenParse(TRADEPARSEUNIT &tpu, TRADEPRICE & tp)
{
	int result = 0;//Ĭ�ϳɹ�
	//TRADEPRICE tp = {0.0f, 0.0f};

	if (tpu.nDirection <= DTT_NULL || tpu.nDirection >= DTT_MAX)
	{
		//PrintfOutputWindow(("==>ģ�⿪��-��Ч�ķ���ֵ:%d(��ЧֵΪ:[1, 4])\r\n"), tpu.nDirection);
		return 2;
	}

	//�м�Ĭ��ʹ�����¼۳ɽ�
	result = logic_MatchEngine(tpu, tp);
	if (result == 0)
	{
		//dBidPrice = tp.dBidPrice;
		//////////////////////////////////////////////////////////////////////////
		//����Ϊ���Դ�ӡ
		if (tpu.nDirection > DTT_NULL && tpu.nDirection < DTT_MAX)
		{
			//PrintfOutputWindow(TEXT("==>ģ�⿪��-%s ��һ��:%lf ��һ��:%lf ���¼�:%lf ������:%lf �ɽ���:%lf\r\n"), 
			//	g_ptOperatorList[tpu.nDirection], tpu.dBuyPrice[0], tpu.dSellPrice[0], tpu.dLatestPrice[0], tp.dReportPrice, tp.dBidPrice);
		}
		//////////////////////////////////////////////////////////////////////////
	}

	return result;
}

//ģ��ƽ���ж��ӿ�
//����:tpu �µ�����
//		tp	���������ۺͳɽ���(ģ��ʱ��Ҫʹ��)
//����ֵ:0 �ɹ�
//		 1 ʧ��,ָ��������δ�ﵽ
//		 2 ʧ��,��Ч�Ľ����ź�
int CLxGlobalFun::simu_CloseParse(TRADEPARSEUNIT &tpu, TRADEPRICE &tp)
{
	int result = 0;//Ĭ�ϳɹ�
	//TRADEPRICE tp = {0.0f, 0.0f};

	if (tpu.nDirection <= DTT_NULL || tpu.nDirection >= DTT_MAX)
	{
		//PrintfOutputWindow("<==ģ��ƽ��-��Ч�ķ���ֵ:%d(��ЧֵΪ:[1, 4])\r\n"), tpu.nDirection);
		return 2;
	}

	switch (tpu.lc.e_nt)
	{
	case NT_CHECK_PRICE:
	{
		//Ĭ��ʹ�����¼۳ɽ�
		result = logic_MatchEngine(tpu, tp);
	}
	break;
	case NT_TRIGGER_PRICE:
	{
		//ֹ��ֹӯ���ж�
		result = JudgeStopLossandProfit(tpu, tp, TRUE);
		if (result == 0)
		{
			//����Ԥ���,����ʵ�ʵļ۸����ʽ��м���ɽ���
			result = logic_MatchEngine(tpu, tp);
		}
		else if (result == 1)
		{
			result = 0;//�ﵽֹ��ֹӯ��,���Ǳ���Ԥ���
		}
		else
		{
			// no op
		}
	}
	break;
	case NT_MARKET_PRICE:	//�м�
	case NT_BIDDING_PRICE:	//���ּ�
	case NT_LATEST:			//���¼�
	case NT_QUEUE:			//�ŶӼ�
	{
		//ֹ��ֹӯ���ж�
		result = JudgeStopLossandProfit(tpu, tp, TRUE);
		if (result == 0)
		{
			//�м�Ĭ��ʹ�����¼۳ɽ�
			result = logic_MatchEngine(tpu, tp);
		}
	}
	break;
	default:
	{
		result = 1;//��Ч�۸���������
	}
	break;
	}

	if (result == 0)
	{
		//dBidPrice = tp.dBidPrice;
		//////////////////////////////////////////////////////////////////////////
		//����Ϊ���Դ�ӡ
		if (tpu.nDirection > DTT_NULL && tpu.nDirection < DTT_MAX)
		{
			//PrintfOutputWindow(TEXT("<==ģ��ƽ��-%s ��һ��:%lf ��һ��:%lf ���¼�:%lf ������:%lf �ɽ���:%lf\r\n"), 
			//	g_ptOperatorList[tpu.nDirection], tpu.dBuyPrice[0], tpu.dSellPrice[0], tpu.dLatestPrice[0], tp.dReportPrice, tp.dBidPrice);
		}
		//////////////////////////////////////////////////////////////////////////
	}

	return result;
}


wstring CLxGlobalFun::Str2Wstr(const char * szData)
{
	string str(szData);
	if (str.length() == 0)
		return L"";
	std::wstring wstr;
	wstr.assign(str.begin(), str.end());
	return wstr;
}

string CLxGlobalFun::t2sA(__int64 ntime)
{
	string ret = "";
	char sz[128] = { 0 };
	if (ntime != 0)
	{
		tm t;
		localtime_s(&t, &ntime);
		//gmtime_s(&t, &ntime);
		strftime(sz, 128, "%Y-%m-%d %H:%M:%S", &t);
		ret = sz;
	}
	return ret;
}