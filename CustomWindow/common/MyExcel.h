#pragma once

#include "Qexcel.h"
#include <vector>
#include <qtableview.h>

using namespace std;
class CMyExcel
{
public:
	CMyExcel(void);
public:
	~CMyExcel(void);

	// ����ģ�彫CListCtrl������д�뵽excel
	void WriteListDataToExcel(QTableView &lst, QString csNewSheetName, QString csTitleName, const vector<int>  &vecAlign, const QString &csPath, QString csTemSheetName="sheet1");




	QExcel *excel;

};