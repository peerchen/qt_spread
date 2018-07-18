#include "StopPLMgr.h"

//#include "IniMgr.h"
#include "Global.h"
#include "HashtableMsg.h"
#include "TraderCpMgr.h"
#include "HJGlobalFun.h"
#include "HJConstant.h"
#include "Mgr/ProdCodeMgr.h"
#include "TranMsg.h"
#include "CustomInfoMgrEx.h"
#include "app.h"

#pragma execution_character_set("utf-8")


CStopPLMgr::CStopPLMgr(void)
{
	m_bMatchNoChange = false;
	m_bUseServer = false;
}

CStopPLMgr::~CStopPLMgr(void)
{
	// �����˳�ʱ���m_vecHandledMatchNo�б仯��������д�뵽�����ļ�
	/*if( m_bMatchNoChange )
	{
		WriteMatchNo();
	}*/
}

CStopPLMgr& CStopPLMgr::GetInstance()
{
	static CStopPLMgr theSingleton;
	return theSingleton;
}

void CStopPLMgr::Initialize(  )
{
	LoadSetting();

	LoadHandledMatchNo();
}

// ��ȡһ��Ʒ�ֵ�ֹ��ֹӯ������Ϣ
PLInfo* CStopPLMgr::GetPLInfo( const string &sInsID )
{
	map<string, PLInfo>::iterator it = m_mapInfo.find( sInsID );
	if( it != m_mapInfo.end() )
	{
		return &it->second;
	}
	return NULL;
}

/*
stMatch �ɽ�����ˮ�ṹ
bLong �Ƿ��Ƕ�֣�false��Ϊ�ղ�
*/
void CStopPLMgr::HandleOpenPosiMatch( const DeferMatch &stMatch, bool bLong)
{
	// ��������޸��ļ����򲻴���ֹӯֹ�𣬱���ÿ�ε�½�����ظ�����ֹӯֹ��
	if( !g_Global.m_bEnableIniFile )
		return;

	QString sRecordMatchNO(CHJGlobalFun::str2qstr(stMatch.matchNo));
	sRecordMatchNO += bLong ? "1" : "0";
	if( !IsHandled(sRecordMatchNO) )
	{
		// ��ӳɽ�����
		AddMatchNo( sRecordMatchNO );

		// ��ȡ��Ʒ�ֵ�ֹӯֹ��������Ϣ
		const PLInfo *pInfo = GetPLInfo( stMatch.instID );
		if( pInfo != NULL ) // �����Ʒ��������
		{
			// ��ȡ��Ʒ�ֵ���Ϣ����Ҫ��Ϊ�˻�ȡtick������С�۸�λ��
			const ProdCodeInfo* pProCodeInfo = g_ProdCodeMgr.GetProdeCode( CHJGlobalFun::str2qstr(stMatch.instID ));
			if( pProCodeInfo != NULL )
			{
				// ��ȡƷ�ֵ���С�۸�λ
				double fPriceUnite = pProCodeInfo->tick;

				// ��ȡ�����Ƚϼ۸�
				double dCmpPrice;
				if( GetBaseCmpPrice(dCmpPrice, m_eCmpType, stMatch, bLong) )
				{
#ifdef _Write_StopPL_Log
					if( m_eCmpType == E_PLMatchPrice )
						g_Global.WriteLog("��ȡ�ɽ��۸�");
					else
						g_Global.WriteLog("��ȡ�ֲ־���");
#endif
					if( m_bUseServer ) // ������ֹӯֹ��
					{
						bool bMatchNoChange = false;
						if( pInfo->iStopProfitAjust > 0 || pInfo->iStopLossAjust > 0 )
						{
							Req4074 req;
							req.oper_flag = 2; // ���
							req.exch_type = bLong ? CONSTANT_EXCH_CODE_DEFER_COV_LONG : CONSTANT_EXCH_CODE_DEFER_COV_SHORT;; // ���׷�ʽ
							req.prod_code = stMatch.instID; // Ʒ��

							char temp[3];
							sprintf(temp, "%d", GetPreOrderAskPriceType( m_eAskPriceType, bLong ));
							req.entr_price_type = temp; // �����۸�����
							req.entr_amount = stMatch.volume;; // ����
							req.entr_adjust_step = bLong ? -m_iAskPriceAjust : m_iAskPriceAjust; // ����������λ
							req.src_match_no = stMatch.matchNo;

							//req.trigger_value = CHJGlobalFun::DoubleToString(dCmpPrice,false); // �����Ƚϼ۸�
							req.trigger_value = CHJGlobalFun::qstr2str(QString::number(dCmpPrice)); // �����Ƚϼ۸�
						

							
							// ����ֹӯ
							if( pInfo->iStopProfitAjust > 0 )
							{
#ifdef _Write_StopPL_Log
								g_Global.WriteLog("����ֹӯ��");
#endif

								req.delegate_type = "2";  // ֹӯ��
								req.trigger_condition = bLong ? "0" : "1"; // �Ƚ����ͣ��������ڻ���ڣ��ղ���ΪС�ڻ����

								//req.trigger_value_type = bLong ? "0" : "1"; // ��ֲ�����1�ۣ��ղֲ�����1��

								req.base_adjust_step = bLong ? pInfo->iStopProfitAjust : -pInfo->iStopProfitAjust;

                                // mod by Jerry Lee, 2013-4-22, ���ս���ͨҪ��ʹ�����¼۴���
								//sprintf(temp, "%d", bLong ? E_Buy1 : E_Sell1);
                                sprintf(temp, "%d", E_Latest);
								req.trigger_value_type = temp;

								Rsp4074 rsp;
								if( CTranMsg::Handle4074(rsp, req) )
								{
									bMatchNoChange = true;
								}
							}

							// ����ֹ��
							if( pInfo->iStopLossAjust > 0 )
							{
#ifdef _Write_StopPL_Log
								g_Global.WriteLog("����ֹ��");
#endif
								req.delegate_type = "1";  // ֹ��
								req.trigger_condition = bLong ? "1" : "0"; // �Ƚ����ͣ������С�ڻ���ڣ��ղ���Ϊ����
								//req.trigger_value_type = "2"; // ���¼�

								req.base_adjust_step = bLong ? -pInfo->iStopLossAjust : pInfo->iStopLossAjust; // ����������λ

								sprintf(temp, "%d", E_Latest);
								req.trigger_value_type = temp;

								Rsp4074 rsp;
								if( CTranMsg::Handle4074(rsp, req) )
								{
									bMatchNoChange = true;
								}
							}
#ifdef _Write_StopPL_Log
							g_Global.WriteLog("��ʼ������ֹӯֹ��ˢ�¹㲥");
#endif

							if( bMatchNoChange )
							{
								g_TraderCpMgr.m_mapBdr[E_SER_PREORDER_REFRESH].Broadcast(WM_SER_PREORDER_REFRESH,0,0);
							}

#ifdef _Write_StopPL_Log
							g_Global.WriteLog("����������ֹӯֹ��ˢ�¹㲥");
#endif
						}
					}
					else
					{
						PreOrderStruct stPreOrder;
						stPreOrder.sProdCode = stMatch.instID;
						stPreOrder.sExchId = bLong ? CONSTANT_EXCH_CODE_DEFER_COV_LONG : CONSTANT_EXCH_CODE_DEFER_COV_SHORT;//stMatch.sExchTypeCode;
						stPreOrder.iHand = stMatch.volume;
						stPreOrder.sTime =CHJGlobalFun::qstr2str( CHJGlobalFun::GetCurTimeFormat());
						stPreOrder.eAskPriceType = GetPreOrderAskPriceType( m_eAskPriceType, bLong );

						// ���ݱ���ʱ�۸����ͻ�ȡ�����ָ��
						const unsigned int *pHQPrice = GetHQPricePointer( stPreOrder.eAskPriceType, stMatch.instID);

						int iAskPriceAjust = bLong ? -m_iAskPriceAjust : m_iAskPriceAjust;

						// ����ֹӯ��
						if( pInfo->iStopProfitAjust > 0 )
						{
							stPreOrder.dCmpPrice =  bLong ? dCmpPrice + pInfo->iStopProfitAjust*fPriceUnite : dCmpPrice - pInfo->iStopProfitAjust*fPriceUnite;
							stPreOrder.eCompType = bLong ? E_Big_Equal : E_Small_Equal;
                            // mod by Jerry Lee, 2013-4-22, ���ս���ͨҪ��ʹ�����¼۴���
							//stPreOrder.eQTType = bLong ? E_Buy1 : E_Sell1;
                            stPreOrder.eQTType = E_Latest;

							stPreOrder.wParam = (void *)new PLParam( pHQPrice, iAskPriceAjust, bLong, stMatch.matchNo );
							stPreOrder.eOrderType = PreOrderType_Profit;

							// ���һ��Ԥ��
							int iOrderID = AddPreOrder( stPreOrder );

							//WLog(E_LOG_NORMAL,"����ֹӯֹ�𵥣�%s", PreOrderBusiness::GetPreOrderLog(stPreOrder));
						}

						short nLossAjust = GetLossAjust(pInfo);
						if( nLossAjust != 0 )
						{
							stPreOrder.dCmpPrice =  bLong ? dCmpPrice - nLossAjust*fPriceUnite : dCmpPrice + nLossAjust*fPriceUnite;
							stPreOrder.eCompType = bLong ? E_Small_Equal : E_Big_Equal;
							stPreOrder.eQTType = E_Latest;

							LossParam *pLossParam = new LossParam( pHQPrice, iAskPriceAjust, bLong, stMatch.matchNo );

                            // added by Jerry Lee, 2013-3-31, �Գɽ���Ϊ��׼�ۣ�����׷��ֹ��۸������������
							pLossParam->uiExtreme = dCmpPrice*g_Global.m_dQTFactor+0.5;//g_TraderCpMgr.m_mapQuotation[stMatch.instID].m_uiLast;

							pLossParam->uiDys = GetLossPrice( pInfo->iDysAjust, dCmpPrice, bLong, fPriceUnite )*g_Global.m_dQTFactor+0.5;
							pLossParam->uiStatic = GetLossPrice( pInfo->iStopLossAjust, dCmpPrice, bLong, fPriceUnite )*g_Global.m_dQTFactor+0.5;

							stPreOrder.wParam = pLossParam;
							stPreOrder.eOrderType = PreOrderType_Loss;

							// ���һ��Ԥ��
							int iOrderID = AddPreOrder( stPreOrder );

                            //WLog(E_LOG_NORMAL,"����ֹӯֹ�𵥣�%s", PreOrderBusiness::GetPreOrderLog(stPreOrder));
						}
					}
				}
			}
		}
	}
}

// ��ȡ���������Ļ����۸�
bool CStopPLMgr::GetBaseCmpPrice( double &dBaseCmpPrice, EPLCmpType eCmpType, const DeferMatch &stMatch, bool bLong )
{
	if( eCmpType == E_PLMatchPrice ) // �ɽ��۸�
	{
		dBaseCmpPrice = stMatch.price;
		return true;
	}
	else // �ֲ־���
	{
		DeferPosi stPosi;
		if(  g_CusInfo.GetPosiInfo(stPosi,stMatch.instID) )
		{
			dBaseCmpPrice = bLong ? stPosi.infoLong.dAvgPosPrice : stPosi.infoShort.dAvgPosPrice;
			return true;
		}
	}

	return false;
}

int CStopPLMgr::AddPreOrder( PreOrderStruct &stPreOrder )
{
	// ����һ��Ԥ��
	int iOrderID = g_TraderCpMgr.m_cPreOrder.Add(stPreOrder);

	// �㲥��Ϣ
	g_TraderCpMgr.m_cPreOrder.SendMessage(iOrderID, PreOrderMsgFlag_Add);

	return iOrderID;
}

/*
����ֹ�𵥹��ú���
ֹ�𵥶������¼��봥���۸�dCmpPrice�����Ƚ�
*/
void CStopPLMgr::SetStopLoss( PreOrderStruct &stPreOrder, double dCmpPrice, double fPriceUnite, bool bLong, short nLossAjust )
{
	// ��ȡֹ��۸�����ǿ���֣���ֹ��۸�Ϊ�Ƚϼ�-ƫ�Ƽۣ�������ղ֣���ֹ���+ƫ�Ƽ�
	stPreOrder.dCmpPrice =  bLong ? dCmpPrice - nLossAjust*fPriceUnite : dCmpPrice + nLossAjust*fPriceUnite;
	stPreOrder.eCompType = bLong ? E_Small_Equal : E_Big_Equal;
	stPreOrder.eQTType = E_Latest;
}

/*
���ݱ����۸����ͻ�ȡ�����ж�Ӧ�ֶε�ָ��
modify by xrs 20130129
*/
const unsigned int* CStopPLMgr::GetHQPricePointer( EQTType eAskPriceType, const string &sInsID )
{
	const QUOTATION& qt = g_TraderCpMgr.m_QMapQuotation[sInsID];
	if( eAskPriceType == E_Buy1 ) // ��һ��
		return &qt.m_Bid[0].m_uiPrice;
	else if( eAskPriceType == E_Sell1 ) // ��һ��
		return &qt.m_Ask[0].m_uiPrice;
	else
		return &qt.m_uiLast; // ���¼�
}

EPLCmpType CStopPLMgr::GetCmpType()
{
	return m_eCmpType;
}

EPLAskPriceType CStopPLMgr::GetAskPriceType()
{
	return m_eAskPriceType;
}

short CStopPLMgr::GetAskPriceAjust()
{
	return m_iAskPriceAjust;
}

const map<string, PLInfo>* CStopPLMgr::GetInfo()
{
	return &m_mapInfo;
}

/*
��ȡֹӯֹ�𵥵ı����۸�����
*/
EQTType CStopPLMgr::GetPreOrderAskPriceType( EPLAskPriceType eAskPriceType, bool bLong )
{
	if( eAskPriceType == e_PLLatestPrice ) // ���¼�
		return E_Latest;
	else // ������
		return  bLong ? E_Buy1 : E_Sell1; // ����ǿ���֣��������1�ۣ�����ǿ��ղ֣��������1��
}

short CStopPLMgr::GetLossAjust( const PLInfo *plInfo )
{
	short nLossAjust = 0;
	if( plInfo->iStopLossAjust > 0 && plInfo->iDysAjust == 0 )
		nLossAjust = plInfo->iStopLossAjust;
	else if( plInfo->iDysAjust > 0 && plInfo->iStopLossAjust == 0 )
		nLossAjust = plInfo->iDysAjust;
	else if( plInfo->iDysAjust > 0 && plInfo->iStopLossAjust > 0 )
		nLossAjust = (plInfo->iStopLossAjust > plInfo->iDysAjust) ? plInfo->iDysAjust : plInfo->iStopLossAjust;

	return nLossAjust;
}

double CStopPLMgr::GetLossPrice( short Ajust, double dCmpBasePrice, bool bLong, double fPriceUnite )
{
	if( Ajust != 0 )
		return  bLong ? dCmpBasePrice - Ajust*fPriceUnite : dCmpBasePrice + Ajust*fPriceUnite;
	else
		return 0.00;
}

bool CStopPLMgr::IsHandled( const QString &sMatchNo )
{
	auto it = m_mapHandledMatchNo.find(sMatchNo);
	if (it != m_mapHandledMatchNo.end())
	{
		return true;
	}
	return false;
	for(size_t i = 0; i< m_vecHandledMatchNo.size(); i++)
	{
		if( sMatchNo == m_vecHandledMatchNo[i] )
			return true;
	}

	return false;
}

bool CStopPLMgr::IsServer()
{
	return m_bUseServer;
}

bool CStopPLMgr::WriteMatchNo()
{
	QString csValue(g_Global.m_strExchDate);
	csValue += "��";
	for(size_t i = 0; i< m_vecHandledMatchNo.size(); i++ )
	{
		csValue += m_vecHandledMatchNo[i];
		csValue += "^";
	}

#ifdef _Write_Test_ReBuild_PL_Log
	CString csLog("д���Ѵ���ɽ����ţ�");
	csLog += csValue;
	g_Global.WriteLog(csLog);
#endif

#ifdef _Write_Test_ReBuild_PL_Log
	if( ::WritePrivateProfileString("Info", "HandledMatchNo", csValue, g_Global.GetUserDataIniPath()) )
	{
		g_Global.WriteLog("д���Ѵ���ɽ����ųɹ�");
	}
	else
	{
		g_Global.WriteLog("д���Ѵ���ɽ�����ʧ��");
	}
#else
	//::WritePrivateProfileString("Info", "HandledMatchNo", csValue, g_Global.GetUserDataIniPath());
	App::WritePriProfileString(g_Global.GetUserDataIniPath(),"Info", "HandledMatchNo", csValue);
#endif

	return true;
}

void CStopPLMgr::AddMatchNo( const QString &sMatchNo )
{
	// ��¼û������ĳɽ���
	m_vecHandledMatchNo.push_back(sMatchNo);
	m_mapHandledMatchNo.insert(make_pair(sMatchNo, sMatchNo));
	WriteMatchNo();
}

void CStopPLMgr::LoadSetting()
{
	m_mapInfo.clear();

	/*
	��ȡƷ�ֻ������ã��������������ֹӯֹ�����沿�ֵ�����
	*/
	QString csValue;
	if( App::GetPriProfileString(g_Global.GetUserIniPath(),"PreOrder", "StopPLSetting",csValue))
		//CIniMgr::GetStringValue(csValue, "PreOrder", "StopPLSetting", g_Global.GetUserIniPath()) )
	{
		QVector<int> vSetting;
		CHJGlobalFun::SplitStrToVector(csValue, "^", vSetting);
		if( vSetting.size() >= 4 )
		{
			// ���ݽ���ͨ�汾V1.1�޸�
#ifdef _VERSION_GF
			m_eCmpType = E_PLMatchPrice;
			m_eAskPriceType = e_PLLatestPrice;
#else
			m_eCmpType = (EPLCmpType)vSetting[0];
			m_eAskPriceType = (EPLAskPriceType)vSetting[1];
#endif
			
			m_iAskPriceAjust = vSetting[2];
			m_bUseServer = vSetting[3];

			// �������ļ���ȡÿ��Ʒ�ֵ�ֹӯֹ������
			QString sValue;
			if(App::GetPriProfileString( g_Global.GetUserIniPath(), "PreOrder", "InstSetting",sValue) )
			{
				HashtableMsg htm;
				if( htm.Parse(CHJGlobalFun::qstr2str(sValue)) == 0 )
				{
					PLInfo info;
					for( size_t i = 0; i < htm.size(); i++ )
					{
						info.iStopProfitAjust = atoi(htm.GetString(i, "StopProfitAjust").c_str()); // ֹӯ������λ
						info.iStopLossAjust = atoi(htm.GetString(i, "StopLossAjust").c_str()); // ֹ�������λ
						info.iDysAjust = atoi(htm.GetString(i, "DysAjust").c_str()); // �Զ�׷��ֹ�������λ

						m_mapInfo[htm.GetString(i, "InsID")] = info;
					}
				}
			}
		}
	}
}

void CStopPLMgr::LoadHandledMatchNo()
{
	m_vecHandledMatchNo.clear();
	m_mapHandledMatchNo.clear();

	string sValue = "5000";
	QString buf;
	if(App::GetPriProfileString(g_Global.GetUserDataIniPath(), "Info", "HandledMatchNo",buf) )
	{
		sValue = CHJGlobalFun::qstr2str(buf);
		//sValue = "20121022��2012101902000002^2012101902000011^2012101902000005^2012101902000016^2012101902000017^2012101902000018^2012101902000019^2012101902000020^2012101902000022^2012101902000023^2012101902000025^2012101902000026^2012101902000027^2012101902000028^2012101902000030^2012101902000031^2012101902000032^2012101902000033^2012101902000034^2012101902000036^2012101902000037^2012101902000039^2012101902000041^2012101902000042^2012101902000043^2012101902000045^2012101902000048^2012101902000049^2012101902000050^2012101902000051^2012101902000076^2012101902000078^2012101902000079^2012101902000080^2012101902000081^";
		int iPos = sValue.find("��");
		if( iPos != -1 )
		{
			if(sValue.substr(0, iPos) == CHJGlobalFun::qstr2str(g_Global.m_strExchDate))
			{
#ifdef _Write_Test_ReBuild_PL_Log
				CString csLog("��ʼ���Ѵ���ɽ����ţ�");
				csLog += sValue.c_str();
				g_Global.WriteLog(csLog);
#endif

				sValue = sValue.substr(iPos+2);
				CHJGlobalFun::SplitStrToVector(CHJGlobalFun::str2qstr(sValue), "^", m_vecHandledMatchNo);
				for (size_t i = 0; i < m_vecHandledMatchNo.size(); i++)
				{
					m_mapHandledMatchNo.insert(make_pair(m_vecHandledMatchNo[i], m_vecHandledMatchNo[i]));
				}
			}
			else
			{
				//::WritePrivateProfileString("Info", "HandledMatchNo", "", g_Global.GetUserDataIniPath()); 
				App::WritePriProfileString(g_Global.GetUserDataIniPath(),"Info", "HandledMatchNo", "");

#ifdef _Write_Test_ReBuild_PL_Log
				g_Global.WriteLog("�������ڲ����ϣ�������ֶ�");
#endif
			}
		}
	}
}
