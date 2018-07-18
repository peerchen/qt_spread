#pragma once

#include <QDateTime>
#include <QComboBox>
#include <QStandardItemModel>
#include <QTableView>
#include "TraderCpMgr.h"
#include <vector>
#include <QVector>
using namespace std;

typedef enum
{
	E_FIRST  = 1,
	E_FORWARD,
	E_NEXT,
	E_LAST,
} EPageBtnType;

#define CONSTANT_LIST_TO_BORDER



class CHJQueryBase
{
public:
	CHJQueryBase(void);
public:
	~CHJQueryBase(void);

public:
	// д��
	//void WriteListDataToExcel(CString csSheetName, vector<CString>  &vecAlign);

protected: 

	//  ҳ���й�---------------------------------------------------------------------

	// ��ʼ��ҳ�������˵�
	void InitPage();

	// ��ȡ��ǰѡ���ҳ��
	int  GetCurPage();

	// ��ʼ��ÿҳ��¼�������˵�
	void InitPageNum();

	// ��ȡ��ǰѡ�е�ÿҳ��¼��
	int  GetPageNum();

	// �����һҳ��ǰһҳ����һҳ�����һҳ��ťʱ��Ӧ��Ҫ�ı䵱ǰҳ��combox�ĵ�ǰѡ��
	void SetComboxCurPage(EPageBtnType ePagebtnType);

	// ���������ѯ�����¼���ҳ�������˵��͵�ǰѡ��ҳ��
	void ResetComboxPage(const int &iTotal, int &iCurPage);

	void OnButtonFirst();
	void OnButtonPrev();
	void OnButtonNext();
	void OnButtonLast();

	void OnSelchangeComboNum();
	void OnSelchangeComboPage();
	

	//  �б�������---------------------------------------------------------------------
	void LoadList();

	// ���list���ݺͱ���
	void ClearList();

	// ������ʱ����û�б�Ҫ����Ϊ�������Ѿ����ϲ���LoadList()������б�Ҫ�����Իָ�
	//void AddListColumn( CListCtrl* lst, vector<CString> &vecName, vector<int> &vecAlign, vector<int> &vecWidth );

	// ��ȡ�û�ѡ���ֶε�ID�����Ͳ�ѯ�����ĺʹ����ر��ĵ�ʱ���õ��������޸�Ϊ�ֲ�����
	void GetUserColumnIDs(const QString &strPath);

	// 
	void GetUserAlign(vector<int> & vecAlign);

	// ��ѯ���---------------------------------------------------------------------

	void OnButtonQuery();
	void OnButtonQuery(QDateTime &dtBegin, QDateTime &dtEnd);

	// ��ȡ��ѯ�ı�ʶ��������ʵ��
	virtual string GetQueryID(){return "";};

	// ��ȡ��ѯ��������������ʵ��
	virtual void GetQueryPara(QVector< pair<QString, QString> >  &vecPara){};

	// ��������ύ��ѯ�������ӽ��׷�����ʧ���򷵻�false���ɹ��򷵻�true
	bool Query(const string &strQueryTag, QVector< pair<QString,QString> > & vecPara, const int &iPageNum/*ÿҳ������*/, const int &iCurPage/*��ǰ�����ҳ��*/, Req6002 &stReq6002, Rsp6002 &stRsp6002);

	// ��ʾ��ѯ���������
	void ShowQueryResult(const Req6002 &stReq6002, const Rsp6002 &stRsp6002);

	virtual QString GetSheetName(){ return "";};

	// �ݶ�������Ϊ�գ������б�Ҫ�Ļ���д
	virtual void QueryReserver(const Req6002 &stReq6002, const Rsp6002 &stRsp6002);

	// �����excel��ť�Ĵ�������
	void OnOutputToExce(QString csSheetName);

	void OnBtnSetshowcolumn(QString strNodeDate = "");

	// �ж�һ���ֶ�ID�Ƿ�Ӧ�ø�ʽ��Ϊ������
	bool IsFloatTitle( const string &strID, const string &sQueryID = "" );

	void PairAdd(QVector< pair<QString,QString> > & v,QString strtitle,QString strvalue);

	virtual void IniProdCode(QComboBox& comb,string marketid="");//��ʼ����Լ����
	string GetProdCode(QComboBox& comb);//��ȡ��Լ����
	void IniExchCode(QComboBox& comb);
	QString GetExchCode(QComboBox& comb);
	void IniOffsetFlag(QComboBox& comb);
	string GetOffsetFlag(QComboBox& comb);
	void IniLongShort(QComboBox& comb);
	string GetLongShort(QComboBox& comb);
	void IniAccessWay(QComboBox& comb);
	string GetAccessWay(QComboBox& comb);
	void IniVarietyId(QComboBox& comb);
	string GetVarietyId(QComboBox& comb);
	void IniFeeCode(QComboBox& comb);
	string GetFeeCode(QComboBox& comb);
	void IniSubFeeCode(QComboBox& comb);
	string GetSubFeeCode(QComboBox& comb);
	void FeeCodeSelectChange(QComboBox& comb1,QComboBox& comb2);
	void ProdCodeSelectChange(QComboBox& comb1,QComboBox& comb2);

	
    //  ����---------------------------------------------------------------------
	QTableView         * m_list;
	QStandardItemModel * m_tableModle;
	QComboBox *m_cmbPage;
	QComboBox *m_cmbNum;
	QVector<int> m_vecColumnIndexs;
	ArrayListMsg m_almUserColumnIDs;
};
