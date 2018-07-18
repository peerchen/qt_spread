#pragma once

#include "TraderCpMgr.h"
#include <QStringList>
#include <QPainter>

#define DEFAULT_DPI_X 96
#define DEFAULT_DPI_Y 96

struct RptDataInfo
{
	QString strTitle;
	QString strContent;
	bool isLeftAli;//�����Ƿ������
};

struct RptColumnInfo
{
	int iColumnPercent; // �����0����ȡƽ��ֵ
	bool bReturn;       // �����Ƿ���
	int iReturnBegin;   // ���⻻�еĿ�ʼλ�ã����ַ�������
};

struct Table1Info
{
	int iColumnPercent;
};

typedef enum
{
	E_REPORT  = 0,
	E_PRINT,
} EShowMode;

typedef enum
{
	E_DAY = 0,
	E_MONTH,
	E_TIHUO,
} EDataMode;

class QReportBase
{
public:
	QReportBase(void);
public:
	~QReportBase(void);

public:
	// ��һ�ֱ�������
	vector<RptDataInfo> m_vecRisk;       // �ͻ���Ϣ
	vector<RptDataInfo> m_vecFund;       // �ʽ���Ϣ
	vector<RptDataInfo> m_vecFundDetail; // �ʽ�����ϸ
	QString m_strGaCha;                  // ��¼�ʽ�����ϸ�е�����
	// �ڶ��ֱ�������
	/*QStringArray*/ QStringList m_arrayStorage;         // �����Ϣ
	/*QStringArray*/ QStringList m_arrayForward;         // Զ��
	/*QStringArray*/QStringList  m_arrayDefer;           // ���ڳֲ���Ϣ
	/*QStringArray */QStringList m_arraySurplus;         // ����ӯ��
	/*QStringArray */QStringList m_arrayMatchFlow;       // �ɽ���ˮ
	/*QStringArray*/ QStringList m_arrayFundInOutFlow;   // �������ˮ

	vector<RptColumnInfo> m_vStorage;
	vector<RptColumnInfo> m_vForward;
	vector<RptColumnInfo> m_vDefer;
	vector<RptColumnInfo> m_vSurplus;
	vector<RptColumnInfo> m_vMatchFlow;
	vector<RptColumnInfo> m_vFundInOutFlow;

	vector<Table1Info> m_vecRiskColumn;

	// ���ݶ��壬�ڶ��ֱ��������У������˱����У��ĸ���
	int m_iStorage;
	int m_iForward;
	int m_iDefer;
	int m_iSurplus;
	int m_iMatchFlow;
	int m_iFundInOutFlow;

public:
	void IniAllData(Rsp6007 &rsp);

protected:
	struct PrintInfo
	{
		int m_nCurPage;
		int m_MaxPage;
	};
	 /*CPrintInfo*/ PrintInfo  m_printInfo;
	 void SetPage(/*CPrintInfo*/PrintInfo* pInfo, int& nHeight);

	// �սᵥ���½ᵥ��ӡ�����ݳ�ʼ��
	void IniRisk(Rsp6007 &rsp);
	void IniFund(Rsp6007 &rsp);
	void IniFundDetail(Rsp6007 &rsp);
	void IniStorage(Rsp6007 &rsp);
	void IniForward(Rsp6007 &rsp);
	void IniDefer(Rsp6007 &rsp);
	void IniSurplus(Rsp6007 &rsp);
	void IniMatchFlow(Rsp6007 &rsp);
	void IniFundInOutFlow(Rsp6007 &rsp);
    
	float m_xRate;
	float m_yRate;

	// ҵ���߼�
	int GetX(int x)
	{
		return (int)(x*m_xRate);
	}

	int GetY(int y)
	{
		return (int)(y*m_yRate);
	}
	

	// ��ͼ���
	void Draw(QPainter* pDC, PrintInfo* pInfo);
	//
	void DrawPart1(int &iLeftTopy, QPainter* pDC);
	// 
	void DrawPart2(int &iLeftTopy, QPainter* pDC);
	//
	void DrawTitle(QPainter* pDC);
	//����һ�ֱ��
	int DrawTable(QPainter* pDC, int iLeftTopY, int iLineCount, int iTitleCount, int iTitleWid, const vector<RptDataInfo> &vec, QString strLTitle, QString strRTitle);
	//����һ�ֱ����չ
	int DrawTableEx(QPainter* pDC, int iLeftTopY, int iLineCount, int iTitleCount, int iTitleWid, const vector<RptDataInfo> &vec, QString strLTitle, QString strRTitle, const vector<Table1Info> &vColumnInfo);
	//���ʽ�����ϸ�е�����һ��
	int DrawFunDetail(QPainter* pDC, int iLeftTopY, QString strTitle, QString strContetn);//���ʽ�����ϸ�����һ��
	//���ڶ��ֱ��
	//int DrawTable2(QPainter* pDC, int iLeftTopY, int iLineCount, int iColCount, const QStringArray &strArray, QString strLTitle, QString strRTitle, int iLAliBegin = 0);
	//���ڶ��ֱ��
	int DrawTable2(QPainter* pDC, int iLeftTopY, int iLineCount, int iColCount, const QStringList &strArray, QString strLTitle, QString strRTitle, const vector<RptColumnInfo> &vColumnInfo, int iLAliBegin = 0,  bool bColumnEven = true);

/*������****************************************/
private:
	QString m_strTiHuoTop[17];
	QString m_strVarietyId;
	QString m_strAmount;
	QString m_strTradeName;
public:
	void DrawTiHuo(QPainter* pDC);
	void IniTiHuoData(Rsp5103 &rsp);

/*��������**********************************/
public:
	 int m_iType;            // 0Ϊ�սᵥ��ӡ��1Ϊ�½ᵥ��2Ϊ�������ӡ
	// ��������ı���
	QString m_strTitle;

	// ������ʾ��ģʽ���Ǳ����Ǵ�ӡԤ��
	void SetShowMode(EShowMode eShowMode);

protected:
	// ��ҳ����Ϣ�����������д
	virtual void WritePage(QPainter* pDC, PrintInfo* pInfo);

private:
	

protected:
	short m_iMaxPage;
	EShowMode m_eShowMode;

	//��������
	int TABLE_LINE_HEIGHT;
	int TABLE_TITLE_HEIGHT;
	int TABLE_WIDTH;
	int LEFT_X;
	int RIGHT_X;
	int TABLE_TO_TITLE_DIS;
	int TABLE_BEGIN_Y;
	int PAGE_BEGIN_X;
	int PAGE_BEGIN_Y;
	int TABLE_PAGE2_BEGIN_Y;

	//��������
	int TITLE_BEGIN_X;
	int TITLE_BEGIN_Y;
	int LINE_Y;

	int TABLE1_LINE_TITLE_COUNT;
	int TABLE2_TITLE_HEIGHT;
	int CUS_INFO_COL_TITLE_WIDTH;
	int CUS_INFO_LINE_COUNT;
	int FUN_INFO_COL_TITLE_WIDTH;
	int FUN_INFO_LINE_COUNT;
	int FUN_DETAIL_COL_TITLE_WIDTH;
	int FUN_DETAIL_LINE_COUNT;

	int STORE_INFO_COLUME_COUNT;
	int CHICANG_INFO_COLUME_COUNT;
    int YINGKUI_INFO_COLUME_COUNT;
	int MATCHFLOW_COLUME_COUNT;
	int FUNINOUTFLOW_COLUME_COUNT;

	int TEXT_DISTANCE_X;
	int TEXT_DISTANCE_Y;
	int MY_FONT_SIZE;

	int TIHUO_TITLE_BEGIN_X;
	int TIHUO_TITLE_BEGIN_Y;

	int TITLE_TOP_DISTANCE;
	int TOP_BEGIN_X;
	int TOP_BEGIN_Y;
	int TOP_LINE_HEIGHT;
	int TOP_TITLE_WIDTH;
	int TOP_CONTENT_EIDTH;

	int TOP_MIDDLE_DISTANCE;
	int MIDDLE_BEGIN_X;
	int MIDDLE_BEGIN_Y;
	int MIDDLE_COLUMN_WIDTH;
	int MIDDLE_LINE_HEIGTH;
	int MIDDLE_TEXT_DISTANCE_Y;

	int MIDDLE_BOTTOM_DISTANCE;
	int BOTTOM_TITLE_WIDTH;
	int BOTTOM_CONTENT_EIDTH;


	int			m_nPageHeight;				//��ӡֽ�߶�
	int			m_nPageWidth;				//��ӡֽ���
};
