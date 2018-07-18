#include "Business.h"
#include "Const.h"
#include "TraderCpMgr.h"
#include "HJGlobalFun.h"

namespace Business
{
	BSFLAG GetBS( const string& sBS )
	{
		if (sBS == CHJGlobalFun::qstr2str(gc_BSFlag_Buy))
			return BS_BUY;
		else if( sBS == CHJGlobalFun::qstr2str(gc_BSFlag_Sell ))
			return BS_SELL;
		else
			return BS_UKNOWN;
	}

	KPFLAG GetKP( const string& offSetFlag )
	{
		if( offSetFlag == CHJGlobalFun::qstr2str(gc_OffsetFlag_Open )) // ����
		{
			return KPF_KAI;
		}
		else if( offSetFlag == CHJGlobalFun::qstr2str(gc_OffsetFlag_Cov )) // ƽ��
		{
			return KPF_PING;
		}
		else if( offSetFlag == CHJGlobalFun::qstr2str(gc_OffsetFlag_ForceCov )) // ǿƽ
		{
			return KPF_FP;
		}
		else if( offSetFlag == CHJGlobalFun::qstr2str(gc_OffsetFlag_TodayCov) ) // ƽ��
		{
			return KPF_PT;
		} 
		else
		{
			return KPF_UKNOWN;
		}
	}

	QString GetOrderInfo( const string &sProdCode, double dPrice, int iAmount, const string &sExchID )
	{
		QString sInfo;
		
		/*sInfo.Format("%s�Լ۸�%.2f %s %d��",
			sProdCode.c_str(),
			dPrice,
			g_TraderCpMgr.GetExchName(CHJGlobalFun::str2qstr(sExchID)),
			iAmount);*/

		return sInfo;
	}

};