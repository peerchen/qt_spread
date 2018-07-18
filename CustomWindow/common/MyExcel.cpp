
#include "MyExcel.h"
#include <QAxObject>
#include <QStandardItemModel>
CMyExcel::CMyExcel(void)
{
}

CMyExcel::~CMyExcel(void)
{

	delete excel;
}
/*
����ģ�彫CListCtrl������д�뵽excel
ע�⣺ģ���
*/
void CMyExcel::WriteListDataToExcel(QTableView &lst, QString csNewSheetName, QString csTitleName, const vector<int>  &vecAlign, const QString &csPath, QString csTemSheetName /*= "sheet1"*/)
{
	QString cColLineBeg,cColLineEnd; // ��¼excel���ַ�����ʽ������


	// ���CListCtrl������������
	int iColumn = lst.model()->columnCount();//lst.GetHeaderCtrl()->GetItemCount(); //����
	int iLine   = lst.model()->rowCount();    //����

	excel = new QExcel(csPath);
	
	//�ϲ���Ԫ��  
	excel->selectSheet("Sheet1");
	excel->RenameSheet(csNewSheetName);
	excel->mergeCells("A1:P1");
	excel->mergeCells(1, 1, 1 ,10);

	//д����
	excel->setCellString(1, 1, csNewSheetName);
	excel->setCellTextCenter(1, 1);
	excel->setCellFontSize(1, 1, 24);

	excel->setRowHeight(1, 80);
	excel->setCellFontBold( 1, 1 ,true);
	

	//д����
	// �����б��⣨С�����У�
	for (int i = 0; i < iColumn; i++)
	{
		// ��ȡlist�е��б���
		QString sTitle = lst.model()->headerData(i, Qt::Horizontal).toString();;

		excel->setCellString(2, i+1, sTitle);
		excel->setColumnWidth(i + 1,10);
	}

	for (int i = 0; i < iLine; i++)
	{
		for (int j = 0; j < iColumn; j++)
		{
			QString str = ((QStandardItemModel *)lst.model())->item(i,j)->text();
			excel->setCellString(i+3, j+1, str);
			//����
			excel->setCellTextCenter(i+3,j+1);

		}
	}

	excel->show();

}
