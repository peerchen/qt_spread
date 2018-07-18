#pragma once

#include <QDialog>
#include "ui_frmGetGoodsDlg.h"
#include "ArrayListMsg.h"
#include <vector>
#include <QStandardItemModel>
#include "HashtableMsg.h"
#include  "frmFramelessDialogBase.h"

// �ֿ���Ϣ
struct StoreInfoEx
{
	string       stor_id; //�ֿ����    
	string       stor_name; //�ֿ�����    
	string       addr; //�ֿ��ַ    
	string       tel; //��ϵ�绰    
	string       fax; //��ϵ����    
	string       link_man; //��ϵ��    
	string       zip_code; //�ʱ�    
	string       use_variety_type; //֧�ֵ����Ʒ��    ÿ��Ʒ������֮��ʹ�á�,���ָ�
	string       is_take; //�Ƿ��������    yes_no
	string       city_code; //��������    ������д���֮��ʹ�á�,���ָ�
};


// ������Ϣ
struct CityInfo
{
	string       city_code; //���д���    
	string       city_name; //��������    
	string       all_stor_id; //�ֿ����    2*,3*
	string       stor_id_default; //Ĭ������ֿ�    2*,3*
};


class frmGetGoodsDlg : public frmFramelessDialogBase
{
	Q_OBJECT

public:
	frmGetGoodsDlg(QWidget *parent = Q_NULLPTR);
	~frmGetGoodsDlg();


	bool IsShowTakeSheetData();



	void IniVarietyComboBox();

	void OnCbnSelchangeComboPerson();

	ArrayListMsg* GetTakeShhetDate();
	void GetTakeSheetDateFromServer();
	void LoadTakeSheetDateToComBox();
	bool loadStore();
	void IniStoreInfo(HashtableMsg &htm);
	bool loadCityFromFile();
	void IniCityInfo(HashtableMsg &htm);
	void IniCityComboBox();

	bool CheckInput();

	string GetStoreId(const string &sName);

	bool IsWeightRight();
	bool CheckPassword();
	bool CheckIDCard();
	bool CheckIDCard15(QString Id);
	bool CheckIDCard18(QString Id);
	bool IsRightDate(QString datestr);
	string GetStoreName(const string &sID);
public slots:
	void OnApplyGoods();
	void OnSearch();
	void OnPrint();
	void OnCancel();
	void OnChangeCity(QString city);
	void OnChangeType(QString city);
private:
	Ui::frmGetGoodsDlg ui;

	bool m_bShowTakeSheetDate;
	int m_nTakeDayDis;

	ArrayListMsg m_alm_take_sheet_date; // ��������
	vector<CityInfo> m_vCity;  //����


	QStandardItemModel*   tableModel;

	vector<StoreInfoEx> m_vStore;//�ֿ�

};
