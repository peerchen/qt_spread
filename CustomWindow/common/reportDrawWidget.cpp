#include "reportDrawWidget.h"
#include <QPainter>
#include <QStyleOption>
#include "Global.h"
#include "HJGlobalFun.h"
#include <qapplication.h>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include  <QColor>
#include "frmReportDlg.h"


#pragma execution_character_set("utf-8")


reportDrawWidget::reportDrawWidget(QWidget* parent)
	:QWidget(parent)
{
	m_xRate = m_yRate = 1;
	m_xRate = (float)g_Global.m_ndpiX / DEFAULT_DPI_X;
	m_yRate = (float)g_Global.m_ndpiY / DEFAULT_DPI_Y;

	TABLE_LINE_HEIGHT = 20;   // ����ڵ��еĸ߶ȣ����ŵı���ڵı�������
	TABLE_TITLE_HEIGHT = 18;    // ��������ı���ĸ߶�
	TABLE_WIDTH = 718;   // ���Ŀ��
	LEFT_X = 20;    // �������ߵ�x���  56
	RIGHT_X = 738;   // �������ұߵ�x��㣬TABLE_WIDTH+LEFT_X
	TABLE_TO_TITLE_DIS = 8;     // ���׶˺���һ�����ı���ľ���
	TABLE_BEGIN_Y = 82;    // ���ʼ����y���ϵ�λ�ã�����һ�����ĵ�һ���ߵ�yֵ��

	TABLE_PAGE2_BEGIN_Y = 48;    // �ڶ�ҳ���ʼ��yֵ

								 //��������
	TITLE_BEGIN_X = 232;
	TITLE_BEGIN_Y = 42;//kenny  2018-01-05
	LINE_Y = 48;      //���������������ߵ�yֵ

					  //table1�����ݣ�ǰ�������
	TABLE1_LINE_TITLE_COUNT = 3; //����ǰ�������ÿ�����ÿһ��������title
								 //#define TABLE1_TITLE_HEIGHT 114   //��һ�ֱ�����ĸ߶ȣ�����ͻ���Ϣ���ʽ���Ϣ����Щ�֣�����ڵı���ĸ߶�û���������ã����ɺܼ�
								 //table2�����ݣ����������
	TABLE2_TITLE_HEIGHT = 35;  //�ڶ��ֱ�񣨼�����������񣩱����еĸ߶�

							   //�ͻ���Ϣ���
	CUS_INFO_COL_TITLE_WIDTH = 64;   //����Ŀ��
	CUS_INFO_LINE_COUNT = 2;        //�ܹ�������
									//�ʽ���Ϣ���
	FUN_INFO_COL_TITLE_WIDTH = 102;   //����Ŀ��
	FUN_INFO_LINE_COUNT = 5;        //�ܵ�����
									//�ʽ�����ϸ���
	FUN_DETAIL_COL_TITLE_WIDTH = 80; //����Ŀ��
	FUN_DETAIL_LINE_COUNT = 7;      //�ܵ�����
									//����ı�������
	STORE_INFO_COLUME_COUNT = 11;     //�����Ϣ������
	CHICANG_INFO_COLUME_COUNT = 10;  //���ڳֲ���Ϣ������
	YINGKUI_INFO_COLUME_COUNT = 3;    //����ӯ����Ϣ������
	MATCHFLOW_COLUME_COUNT = 8;   //�ɽ���ˮ������
	FUNINOUTFLOW_COLUME_COUNT = 6;  //�������ˮ������
									//�����������Ϣ
	TEXT_DISTANCE_X = 5;            //���ֿ�ʼ����x��������ľ���
	TEXT_DISTANCE_Y = 4;             //���ֿ�ʼ����y��������ľ���
	MY_FONT_SIZE = 13;            //ʵ�ʵ�����Ĵ�С������ʱ�ã���������ʱ��     
								  /*************************************************************************************************************�������ӡ�������*/
								  //��������
	TIHUO_TITLE_BEGIN_X = 128;
	TIHUO_TITLE_BEGIN_Y = 48;

	TITLE_TOP_DISTANCE = 16;
	TOP_BEGIN_X = 16;
	TOP_BEGIN_Y = 32;
	TOP_LINE_HEIGHT = 35;
	TOP_TITLE_WIDTH = 96;
	TOP_CONTENT_EIDTH = 192;

	TOP_MIDDLE_DISTANCE = 8;
	MIDDLE_BEGIN_X = 16;
	MIDDLE_BEGIN_Y = 32;
	MIDDLE_COLUMN_WIDTH = 272;
	MIDDLE_LINE_HEIGTH = 35;
	MIDDLE_TEXT_DISTANCE_Y = 6;             //���ֿ�ʼ����y��������ľ���

	MIDDLE_BOTTOM_DISTANCE = 8;
	BOTTOM_TITLE_WIDTH = 48;
	BOTTOM_CONTENT_EIDTH = 272;

	m_iMaxPage = 1;
	m_iType = E_DAY;

}
void reportDrawWidget::init()
{

	m_printInfo.m_nCurPage = 1;

	//m_bDay = true;

	m_Painter = new QPainter(this);
	m_Painter->setPen(QColor(0, 0, 0));
	// ��������
	QFont oldFont = qApp->font();
	QFont*newFont = new QFont("FixedSys", 12);
	m_Painter->setFont(*newFont);

	QFontMetrics fm = m_Painter->fontMetrics();
	int width = fm.width("---------1---------2---------3---------4---------5---------6---------7---------8---");

	m_Painter->setFont(oldFont);
	int cxOffset = (rect().width() - width) / 2;

	//�ж�ҳ��ĸ���
	m_nHeight = 0;
	SetPage(&m_printInfo, m_nHeight);//���������ݳ�ʼ��֮�������ȷ���㻭���ĸ߶�
	m_nHeight += 100;

	// �ڴ�λͼ���
	m_nWidth = GetY((width + 100<rect().width()) ? rect().width() : (width + 100));
	//mPixmap = new QPixmap(m_nWidth, m_nHeight);

	setGeometry(0,0,m_nWidth, m_nHeight);

	image = new QImage(m_nWidth, m_nHeight, QImage::Format_RGB32);
	//m_Painter->fillRect(0, 0, m_nWidth, m_nHeight, Qt::white);
	//mPixmap = new QPixmap(m_nWidth, m_nHeight);
}


//Ϊ���ܹ�ʹ����ʽ������ҪΪ�Զ���Widget�ṩpaintEvent�¼�
void reportDrawWidget::paintEvent(QPaintEvent *)
{
	
	QPainter imagePainter(image);
	imagePainter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
	imagePainter.initFrom(image);
	imagePainter.setRenderHint(QPainter::Antialiasing, true);
	imagePainter.eraseRect(rect());
	Draw(&imagePainter, &m_printInfo);
	imagePainter.end();

	QPainter  painter(this);
	painter.drawImage(0, 0, *image);

	// ���û�����ɫ
	//QPainter imagePainter(mPixmap);
	//imagePainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
	//imagePainter.initFrom(mPixmap);
	//imagePainter.setRenderHint(QPainter::Antialiasing, true);
	//imagePainter.eraseRect(rect());
	//Draw(&imagePainter, &m_printInfo);
	//imagePainter.end();

	//QPainter  painter(this);
	//painter.drawPixmap(0, 0, *mPixmap);
}



// �Ƿ���ʾȷ���սᵥ��ť
void reportDrawWidget::ShowConfirmBtn()
{
	bShowBtn = false;

	// ������սᵥ���ж��Ƿ�Ҫ��ʾ�սᵥȷ�ϰ�ť
	if (m_bDay)
	{
		Req2201 req; //��������
		req.oper_flag = 1;
		req.acct_no = CHJGlobalFun::qstr2str(g_Global.m_strUserID);
		req.affirm_date = m_strDate;

		Rsp2201 rsp; //Ӧ������
		if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "2201"))
		{
			//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
		}
		else
		{
			if (g_Global.m_strSysState == CONSTANT_SYSTEM_STAT_DZFINISHED)
			{
				if (CHJGlobalFun::qstr2str(g_Global.m_strExchDate) >= m_strDate && rsp.affirm_date < m_strDate)
				{
					bShowBtn = true;
				}
			}
			else
			{
				if (CHJGlobalFun::qstr2str(g_Global.m_strExchDate) > m_strDate && rsp.affirm_date < m_strDate)
				{
					bShowBtn = true;
				}
			}
		}
	}



}



// ��ʽ���սᵥ����1
QString reportDrawWidget::FormatDate(QString strValue)
{
	int len = strValue.length();
	if (len != 8)//������Ǳ�׼��ʽ���ַ�������������
	{
		return strValue;
	}
	else
	{
		return strValue.left(4) + ("��") + strValue.mid(4, 2) + ("��") + strValue.mid(6) + ("��");
	}
}
// ��ʽ���սᵥ����2
QString reportDrawWidget::FormatDate()
{
	QString strValue = CHJGlobalFun::str2qstr(m_strDate);

	int len = strValue.length();
	if (len != 8)//������Ǳ�׼��ʽ���ַ�������������
	{
		return strValue;
	}
	else
	{
		return strValue.left(4) + ("��") + strValue.mid(4, 2) + ("��") + strValue.mid(6) + ("��");
	}
}
// ��ʽ���½ᵥ������
QString reportDrawWidget::FormatDate2()
{
	QString strDate = CHJGlobalFun::str2qstr(m_strDate);

	// ���ڳ��ȷ��Ϲ淶��ʱ��������
	if (strDate.length() >= 6)
	{
		// ��ȡ��ݺ���λ���·�
		QString strYear, strMonth;

		strYear = strDate.left(4);
		strMonth = strDate.mid(4);
		if (strMonth.length() == 1)
		{
			// ��ʽ���·�
			strMonth = "0" + strMonth;
		}
		strDate = QString("%1��%2��").arg(strYear).arg(strMonth);
		//strDate.sprintf("%s��%s��", strYear, strMonth);
	}

	return strDate;
}



// ��ʼ���Ի���
void reportDrawWidget::ShowReportDlg(const bool &bMode, Rsp6007 &rsp6007, const string &strDate)
{
	// ���öԻ���ģʽ���սᵥ�����½ᵥ��
	SetMode(bMode);
	// ��������
	m_strDate = strDate;
	// ��������
	IniAllData(rsp6007);
	
	//20187-1-5
	init();
	// ����������ͼ
	//CreateView();
	//DrawReport();
	// 	// ���ñ����title
	// 	SetReportViewTitle(GetReportTitle());
	m_strTitle = GetReportTitle();
	// ��ʾ�սᵥȷ�ϰ�ť
	ShowConfirmBtn();

	//SetWindowPos(NULL, 300, 150, 780, 500, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE); //SetWindowPos �õ��������������εıȽ�
	show();//�������»���

}


// ��ȡ����ʹ�ӡ�����ı���
QString reportDrawWidget::GetReportTitle()
{
	QString strTitle;
	if (m_bDay)
	{
		strTitle = FormatDate(CHJGlobalFun::str2qstr(m_strDate)) + "�ͻ��սᵥ";
	}
	else
	{
		strTitle = FormatDate2() + "�ͻ��½ᵥ";
	}

	return strTitle;
}


//// ���öԻ����ģʽ�����սᵥ�����½ᵥ
void reportDrawWidget::SetMode(bool bDay)
{
	m_bDay = bDay;

	if (m_bDay) // ������սᵥ����
	{
		//SetWindowText("�սᵥ��ѯ");
		setWindowTitle(("�սᵥ����"));
	}
	else
	{
		//SetWindowText("�½ᵥ��ѯ");
		setWindowTitle(("�½ᵥ����"));
	}
}



void reportDrawWidget::DrawReport()
{
	//Draw(m_Painter, &m_printInfo);
}

//��ӡԤ��
void reportDrawWidget::PrintView(QWidget *parent)
{
	QPrinter printer(QPrinter::HighResolution);
	//�Զ���ֽ�Ŵ�С  
	printer.setPageSize(QPrinter::Custom);
	printer.setPaperSize(QSizeF(height(), width()),	QPrinter::Point);
	QPrintPreviewDialog preview(&printer, this);
	preview.setMinimumSize(1000, 600);

	//Ϊʲô����źŲۣ�����Ӧ��2018-1-5������
	//this��Ϊparent�����ܹ������ˣ������£��������źŲۣ����񶼱���̳���QDlalog[2018-1-6]
	//connect(&preview, SIGNAL(paintRequested(QPrinter*)), parent,SLOT(printPreviewSlot(QPrinter*)));
	connect(&preview, &QPrintPreviewDialog::paintRequested, (frmReportDlg *)parent,&frmReportDlg::printPreviewSlot);


	preview.exec();//paintRequested(QPrinter *printer)��ϵͳ�ṩ�ģ���preview.exec()ִ��ʱ���źű�����
}



//��ӡ[��ʱ���ã���ӡԤ���Ѿ������˴�ӡ]
void reportDrawWidget::Print()
{
	QPrinter print(QPrinter::HighResolution);
	QPrintDialog  printDialog(&print, this);

	if (printDialog.exec())
	{
		QPainter  painter(&print);
		QRect rect = painter.viewport();
		QSize  size = image->size();
		size.scale(rect.size(), Qt::KeepAspectRatio);
		painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
		painter.setWindow(image->rect());
		painter.drawImage(0, 0, *image);

	}

}



void reportDrawWidget::OutToExcel()
{

	QString sPath = QString("%1Trade\\settle.xls").arg(g_Global.GetSystemPath());
	QString csSheetName = (m_bDay == true) ? "�սᵥ" : "�½ᵥ";
	QExcel *excel = new QExcel(sPath);
	excel->selectSheet("Sheet1");
	excel->RenameSheet(csSheetName);
	int iCurLine;
	excel->setCellString(2, 2, m_strTitle);
	
	if (m_vecRisk.size() != 0)
	{
		const int iCount = 6;
		QString csColumns[iCount] = { "E", "U", "AM", "E", "U", "AM" };
		int        iLines[iCount] = { 7, 7, 7, 8, 8, 8 };
		for (int i = 0; i < iCount; i++)
		{
			excel->setCellString(iLines[i], excel->Column_StrToInt(csColumns[i]), m_vecRisk.at(i).strContent);
		}
	}
	else
	{
		ExcelClear( *excel, 9);
		return;
	}

	if (m_vecFund.size() != 0)
	{
		const int iCount = 14;
		QString csColumns[iCount] = { "H", "Y", "AQ", "H", "Y", "AQ", "H", "Y", "AQ", "H", "Y", "AQ", "H", "Y" };
		int        iLines[iCount] = { 11, 11, 11, 12, 12, 12, 13, 13, 13 ,14, 14, 14, 15, 15 };
		for (int i = 0; i < iCount; i++)
		{
			excel->setCellString(iLines[i], excel->Column_StrToInt(csColumns[i]), m_vecFund.at(i).strContent);
		}

		QString csColumnsName[iCount] = { "C", "Q", "AH", "C", "Q", "AH", "C", "Q", "AH", "C", "Q", "AH", "C", "Q" };
		for (int i = 0; i < iCount; i++)
		{

			excel->setCellString(iLines[i], excel->Column_StrToInt(csColumnsName[i]), m_vecFund.at(i).strTitle);
	
		}
	}
	else
	{
		//ExcelClear(_app, _workSheet, myExcelEx, 16);
		ExcelClear(*excel, 16);
		return;
	}

	if (m_vecFundDetail.size() != 0)
	{
		const int iCount = 21;
		QString csColumns[iCount] = { "G", "X", "AO", "G", "X", "AO", "G", "X", "AO", "G", "X", "AO", "G", "X", "AO", "G", "X", "AO", "G", "X", "AO" };
		int        iLines[iCount] = { 18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23, 24,24, 24 };
		for (int i = 0; i < iCount; i++)
		{
			excel->setCellString(iLines[i], excel->Column_StrToInt(csColumns[i]), m_vecFundDetail.at(i).strContent);
		}

		//range.SetItem(25, myExcelEx.Column_StrToInt("G"), m_strGaCha);
		excel->setCellString(25, excel->Column_StrToInt("G"), m_strGaCha);
	}
	else
	{
		ExcelClear(*excel, 16);
		return;
	}

	iCurLine = 26;
	if (m_iStorage > 0)
	{
		WriteExcelAddEmptyLine(*excel, iCurLine);
		QString csColIDBeg[11] = { "B", "D", "J", "N", "S", "W", "AA", "AD", "AJ", "AN", "AR" };
		QString csBigTitle[2] = { "�����Ϣ", "��λ����" };
		QString csFinalNextCol = "AY";
		//QString csTitle[11] = {"����Ʒ��",  "���ڿ��","���ÿ��",    "������",    "��Ѻ���",  "������","��������","��������","���ڴ���","�������","�������"};
		int iAlign[11] = { Qt::AlignLeft, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight };
		WriteExcelModal(*excel, iCurLine, 11, csColIDBeg, csBigTitle, iAlign, csFinalNextCol, m_arrayStorage, m_iStorage);
	}

	if (m_iDefer > 0)
	{
		WriteExcelAddEmptyLine(*excel, iCurLine);
		QString csColIDBeg[10] = { "B", "F", "K", "R", "V", "Z", "AC", "AI", "AP", "AT" };
		QString csBigTitle[2] = { "���ڳֲ���Ϣ", "����:��  ���:Ԫ" };
		QString csFinalNextCol = "BA";
		//QString csTitle[10] = {"��Լ����", "�ֲַ���",  "���ڳֲ�","���ڿ���","����ƽ��","���ڽ���","�����ֽ���",  "���ڳֲ���","���־���",  "�ֲ־���"};
		int iAlign[10] = { Qt::AlignLeft, Qt::AlignLeft, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight };
		WriteExcelModal(*excel, iCurLine, 10, csColIDBeg, csBigTitle, iAlign, csFinalNextCol, m_arrayDefer, m_iDefer);
	}

	if (m_iSurplus > 0)
	{
		WriteExcelAddEmptyLine(*excel, iCurLine);
		QString csColIDBeg[3] = { "B", "L", "AK" };
		QString csBigTitle[2] = { "����ӯ����Ϣ", "��λ:Ԫ" };
		QString csFinalNextCol = "AZ";
		//QString csTitle[3] = {"��Լ����", "���ڽ����",  "����ӯ��"};
		int iAlign[3] = { Qt::AlignLeft, Qt::AlignRight, Qt::AlignRight };
		WriteExcelModal(*excel, iCurLine, 3, csColIDBeg, csBigTitle, iAlign, csFinalNextCol, m_arraySurplus, m_iSurplus);

		// mod by Jerry Lee, �޸�excel��������һ�С����ڽ���ۡ�������, 2013-3-7
		//range.SetItem(iCurLine+1, myExcelEx.Column_StrToInt(csColIDBeg[1]), m_arraySurplus[1]);
	}

	if (m_iMatchFlow > 0)
	{
		WriteExcelAddEmptyLine(*excel, iCurLine);
		QString csColIDBeg[8] = { "B", "I", "M", "T", "AB", "AF", "AL", "AS" };
		QString csBigTitle[2] = { "�ɽ���ˮ", "����:��  ���:Ԫ" };
		QString csFinalNextCol = "AX";
		//QString csTitle[8] = {"�ɽ����","������",  "��Լ����", "���׷���", "�ɽ��۸�",   "�ɽ�����", "�ɽ����", "������"};
		int iAlign[8] = { Qt::AlignLeft, Qt::AlignLeft, Qt::AlignLeft, Qt::AlignLeft, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight, Qt::AlignRight };
		WriteExcelModal(*excel, iCurLine, 8, csColIDBeg, csBigTitle, iAlign, csFinalNextCol, m_arrayMatchFlow, m_iMatchFlow);
	}

	if (m_iFundInOutFlow > 0)
	{
		WriteExcelAddEmptyLine(*excel, iCurLine);
		QString csColIDBeg[6] = { "B", "G", "N", "U", "AA", "AJ" };
		QString csBigTitle[2] = { "�������ˮ", "" };
		QString csFinalNextCol = "AP";
		//QString csTitle[6] = {"��������", "������ˮ��","��ȡ����",  "�������","��������","������ˮ��"};
		int iAlign[6] = { Qt::AlignLeft, Qt::AlignLeft, Qt::AlignLeft, Qt::AlignRight, Qt::AlignLeft, Qt::AlignRight };
		WriteExcelModal(*excel, iCurLine, 6, csColIDBeg, csBigTitle, iAlign, csFinalNextCol, m_arrayFundInOutFlow, m_iFundInOutFlow);
	}

	excel->show();

}


void reportDrawWidget::WriteExcelModal(QExcel &myExcelEx, int &iCurLine, int iTitleCount, QString *pcsColIDBeg, QString *pcsBigTitle, int *piAlign, const QString &csFinalNextCol, const QStringList &m_arrayValue, int iDataLineCount)
{
	int iLine; // ��¼��ǰ����excel����
	int i; // ��ʱ����
	int j;
	QString cColLineBeg, cColLineEnd; // ��¼excel���ַ�����ʽ������

	iLine = iCurLine;
	// �ϲ��������Ϣ��
	cColLineBeg = "b"; cColLineEnd = "v";
	cColLineBeg = myExcelEx.FormatColLine(cColLineBeg, iLine);
	cColLineEnd = myExcelEx.FormatColLine(cColLineEnd, iLine);

	myExcelEx.mergeCells(cColLineBeg + ":" + cColLineEnd);
	//range = _workSheet.GetRange(_variant_t(cColLineBeg), _variant_t(cColLineEnd));
	//range.Merge(_variant_t(0));  //�ϲ���Ԫ��
	//range.SetRowHeight(_variant_t(20));
	myExcelEx.setRowHeight(cColLineBeg, 20);
	// �ϲ�"��λ:��"
	cColLineBeg = "w"; cColLineEnd = "AX";
	cColLineBeg = myExcelEx.FormatColLine(cColLineBeg, iLine);
	cColLineEnd = myExcelEx.FormatColLine(cColLineEnd, iLine);
	myExcelEx.mergeCells(cColLineBeg + ":" + cColLineEnd);

	//range = _workSheet.GetRange(_variant_t(cColLineBeg), _variant_t(cColLineEnd));
	//range.Merge(_variant_t(0));  //�ϲ���Ԫ��
	//range.SetHorizontalAlignment(_variant_t(EXCEL_ALIGN_RIGHT)); // �����ұ߶���
	//range.SetRowHeight(_variant_t(20));
	myExcelEx.setRowHeight(cColLineBeg, 20);
	myExcelEx.setFontAlignment(cColLineBeg, -4152);
	// ����title���еĺϲ�
	iLine = iCurLine + 1;
	for (j = 0; j <= iDataLineCount; j++)
	{
		for (i = 0; i < iTitleCount; i++)
		{
			// ��ȡ�ϲ���Ԫ��Ŀ�ʼ��
			cColLineBeg = myExcelEx.FormatColLine(*(pcsColIDBeg + i), iLine);
			// ��ȡ�ϲ���Ԫ��Ľ�����
			QString sTemp;
			sTemp = (i == iTitleCount - 1) ? csFinalNextCol : *(pcsColIDBeg + i + 1);
			cColLineEnd = myExcelEx.GeForColumn(sTemp);
			cColLineEnd = myExcelEx.FormatColLine(cColLineEnd, iLine);
			// �ϲ���Ԫ��
			//range = _workSheet.GetRange(_variant_t(cColLineBeg), _variant_t(cColLineEnd));
			//range.Merge(_variant_t(0));  //�ϲ���Ԫ��
			
			myExcelEx.mergeCells(cColLineBeg + ":" + cColLineEnd);
			int val = *(piAlign + i) == 1 ? -4131 : -4152;
			myExcelEx.setFontAlignment(cColLineBeg, j == 0 ? -4108 : val);
			// ���ö��뷽ʽ
			//range.SetHorizontalAlignment(_variant_t(j == 0 ? EXCEL_ALIGN_CENTER : *(piAlign + i)));

			if (j == 0)
			{
				myExcelEx.setCellFontBold(cColLineEnd, true); // ����Ϊ����
				//myExcelEx.setFontBold(cColLineEnd, sTemp,true);
			}
			else
			{
				myExcelEx.setCellFontSize(cColLineEnd, 9);
			}

			// �����ñ������壨��С�����壩
			//font.AttachDispatch(range.GetFont());
			//if (font.m_lpDispatch)
			//{
			//	if (j == 0)
			//	{
			//	font.SetBold(_variant_t(true)); // ����Ϊ����
			//	}
			//	else
			//	{
			//	font.SetSize(_variant_t(9));

			//	}
			//}

			//if (j == 0)
			//{
			//	// ���ñ���ɫ
			//	Interior m_nterior = range.GetInterior();
			//	m_nterior.SetColor(_variant_t(RGB(192, 192, 192)));
			//}

			if (j == 0)
			{
				myExcelEx.setBackColor(cColLineEnd, QColor(192, 192, 192,255)); 
															  
			}

			//weight = 3  ,color
			myExcelEx.setBorder(cColLineEnd,3, QColor(0, 0, 0));

			//// �߿�
			//range.BorderAround(COleVariant((short)1), 3, 1, _variant_t(RGB(0, 0, 0)));
		}

		// �����и�
		j == 0 ? myExcelEx.setRowHeight(cColLineBeg, 28.25) : myExcelEx.setRowHeight(cColLineBeg, 20.25);
		

		iLine++;
	}

	// �ָ���Ĭ�ϵ�ȫ����Ԫ�񣬷���������޸Ļ�����԰�
	//range.AttachDispatch(_workSheet.GetCells());

	// �����������ı���
	iLine = iCurLine;
	//range.SetItem(iLine, 2, *pcsBigTitle);
	//range.SetItem(iLine, myExcelEx.CharToInt('W'), *(pcsBigTitle + 1));

	myExcelEx.setCellString(iLine, 2, *pcsBigTitle);
	myExcelEx.setCellString(iLine, myExcelEx.CharToInt('W'), *(pcsBigTitle + 1));


	// ����Title��ֵ
	iLine = iCurLine + 1;
	for (i = 0; i < iTitleCount; i++)
	{
		//range.SetItem(iLine, myExcelEx.Column_StrToInt(*(pcsColIDBeg+i)), *(pcsTitle+i));
		//range.SetItem(iLine, myExcelEx.Column_StrToInt(*(pcsColIDBeg + i)), m_arrayValue.GetAt(i));

		myExcelEx.setCellString(iLine, myExcelEx.Column_StrToInt(*(pcsColIDBeg + i)), m_arrayValue.at(i));

	}

	// ���ֵ
	iLine = iCurLine + 2; // �Ƶ�������
	for (i = 0; i < iDataLineCount; i++)
	{
		for (j = 0; j < iTitleCount; j++)
		{
		//range.SetItem(iLine, myExcelEx.Column_StrToInt(*(pcsColIDBeg + j)), m_arrayValue.GetAt((i + 1)*iTitleCount + j));
			myExcelEx.setCellString(iLine, myExcelEx.Column_StrToInt(*(pcsColIDBeg + j)), m_arrayValue.at((i + 1)*iTitleCount + j));

		}
		iLine++;
	}

	iCurLine = iLine--;
}




void reportDrawWidget::WriteExcelAddEmptyLine(QExcel &myExcelEx,  int &iCurLine)
{
//QString cColLine = myExcelEx.FormatColLine("b", iCurLine);
//range = _workSheet.GetRange(_variant_t(cColLine), _variant_t(cColLine));
//range.SetRowHeight(_variant_t(10));
//?????????2018-1-12
myExcelEx.setCellString(iCurLine,QString("b").toInt(), "");
myExcelEx.setRowHeight(iCurLine, 10);

iCurLine++;
}

// ���iCurLine�����������
void reportDrawWidget::ExcelClear(QExcel &myExcelEx, int iCurLine)
{

	for (int j = iCurLine; j < 26; j++)
	{
		for (int i = 0; i< 52; i++)
		{
			myExcelEx.clearCell(j, i);
		}
	}

	myExcelEx.save();

}


