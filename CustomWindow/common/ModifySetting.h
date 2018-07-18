#pragma once

class CModifySetting
{
public:
	CModifySetting(void);
public:
	~CModifySetting(void);

	// ����ǰȷ��
    static void ModifyTradeConfirm(bool bConfirm);

	// ����ǰȷ��
	static void ModifyCancelConfirm(bool bConfirm);

	// ƽ��ǰȷ��
	static void ModifyOppCovConfirm(bool bConfirm);

	// ����ǰȷ��
	static void ModifyCovPosiConfirm(bool bConfirm);

	// temp
	static void ModifyTipsAskSus(bool bTips);

	// temp
	static void ModifyTipsAskFail(bool bTips);

	// temp
	static void ModifyTipsOrderMatch(bool bTips);

	// temp
	static void ModifyTipsCancelSus(bool bTips);

	// temp
	static void ModifyTipsCancelFail(bool bTips);

	static void ModifyTipsPreOrder(bool bTips);

	static void ModifyTipsAskOverFlow(bool bTips);

	static void ModifyTipsAskPreOrder(bool bTips);
};
