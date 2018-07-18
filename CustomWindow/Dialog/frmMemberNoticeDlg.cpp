#include "frmMemberNoticeDlg.h"
#include "Macrodefs.h"
#include "Global.h"
#include "TradePacketAndStruct.h"
#include "global.h"
#include "HJGlobalFun.h"
#include "TraderCpMgr.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QString>
#include  "frmNoticeDetailDlg.h"
#include "myhelper.h"


#pragma execution_character_set("utf-8")

frmMemberNoticeDlg::frmMemberNoticeDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);


	ui.dateEdit_st->setDate(QDate::fromString(g_Global.m_strExchDate));
	ui.dateEdit_ed->setDate(QDate::fromString(g_Global.m_strExchDate));

	tableModel = new QStandardItemModel();

	//setWidgetStyleFromQssFile(ui.tableView, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\ordertable.css"));

	////������
	tableModel->setColumnCount(4);
	int columnIndex = 0;
	tableModel->setHeaderData(columnIndex, Qt::Horizontal, ("���"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, ("����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, ("����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, ("����ʱ��"));


	ui.tableView->horizontalHeader()->setFixedHeight(32);
	ui.tableView->verticalHeader()->hide();
	ui.tableView->verticalHeader()->setDefaultSectionSize(30);
	ui.tableView->setShowGrid(false);
	ui.tableView->setSortingEnabled(false);
	ui.tableView->setAlternatingRowColors(true);//���л�ɫ
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	tableModel->setSortRole(1);
	ui.tableView->setModel(tableModel);
	ui.tableView->setColumnWidth(0, 150);
	ui.tableView->setColumnWidth(1, 150);


	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonQuery()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonDetail()));
	//connect(ui.tableView, SIGNAL(doubleCliecked()), this, SLOT(OnDBClicked()));
	connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(OnDBClicked(const QModelIndex &)));


	QDate ctime = QDate::fromString(g_Global.m_strLast_Exch_Date, ("yyyyMMdd"));
	if (!ctime.isNull())// != NULL)
	{
		ui.dateEdit_st->setDate(ctime);
		
	}

	ui.dateEdit_ed->setDateTime(QDateTime::currentDateTime());


	setFixedSize(871, 501);
	ui.widget->setGeometry(0, 0, 871, 401);
	setContent(ui.widget);
	setWindowTitle("�����ѯ");

}

frmMemberNoticeDlg::~frmMemberNoticeDlg()
{
}




void frmMemberNoticeDlg::OnBnClickedButtonQuery()
{

	//CTime timeBegin, timeEnd;
	//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_BEGIN))->GetTime(timeBegin);  // ��ȡ��ʼ���ںͽ�������
	//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_END))->GetTime(timeEnd);      // ��ȡ��������

	if (ui.dateEdit_st->text().toInt()  >  ui.dateEdit_ed->text().toInt())
	{
		QMessageBox::information(nullptr, /*QStringLiteral*/("��ʾ"), /*QStringLiteral*/(CONSTANT_BEGIN_DATE_BIGGER));

		//AfxMessageBox(CONSTANT_BEGIN_DATE_BIGGER);
		return;
	}
	else
	{
		//m_list.DeleteAllItems(); //���list�ؼ�
		tableModel->removeRows(0, tableModel->rowCount());
		Req8031 req; //��������

		//CString strID, strTitle;

		//// ��ȡ�û�����
		//GetDlgItem(IDC_EDIT_ID)->GetWindowText(strID);       // ��ȡ�������
		//GetDlgItem(IDC_EDIT_TITLE)->GetWindowText(strTitle); // ��ȡ�������

															 // ��֯��ѯ����
		req.oper_flag = 1;
		req.bulletin_id = CHJGlobalFun::qstr2str(ui.lineEdit->text());
		req.title = CHJGlobalFun::qstr2str(ui.lineEdit_2->text());
		req.s_exch_date = CHJGlobalFun::qstr2str(ui.dateEdit_st->text());
		req.e_exch_date = CHJGlobalFun::qstr2str(ui.dateEdit_ed->text());

		// modified by Jerry Lee, 2011-5-4, �޸�Ϊʹ��HandleTransaction����
		Rsp8031 rsp; //Ӧ������
		if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "8031"))
		{
				QMessageBox::information(nullptr, /*QStringLiteral*/("��ʾ"), /*QStringLiteral*/(CONSTANT_CONNECT_SERVER_FAIL_TIPS));
		//AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
			return;
		}

		if (g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
		{
			if (rsp.alm_result.size() == 0)
			{
				QMessageBox::information(nullptr, /*QStringLiteral*/("��ʾ"), /*QStringLiteral*/(CONSTANT_QUERY_NO_RECORD));

				//AfxMessageBox(CONSTANT_QUERY_NO_RECORD);
			}
			else
			{
				for (size_t i = 0; i < rsp.alm_result.size(); i++) // �������е�������
				{
					int iCount = 0;
					// ��ȡ��i������
					ArrayListMsg aMsg = rsp.alm_result.GetValue(i);
					// ��ȡÿ�����ݵ��ֶ���
					size_t count = aMsg.size();

					// ����ÿ�����ݵ������ֶ����ݣ�����ӵ�list
					for (size_t j = 0; j < count; j++)
					{
						string cstrValue = aMsg.GetStringEx(j);//����ֶ�ֵ
						QString str;
						if (j == 2)
						{
							str = ConvertCode(cstrValue.c_str());
						}
						else
						{
							str = CHJGlobalFun::str2qstr(cstrValue.c_str());
						}

						if (j == 0)
						{
							// ����ÿһ�еĵ�һ��

							//m_list.InsertItem(i, str);
							//tableModel->insertRow(i);
							tableModel->setItem(i, 0, new QStandardItem(str));

						}
						else
						{
							//��list�ؼ����������	
							//m_list.SetItemText(i, iCount, cstrValue.c_str()); 
							//m_list.SetItemText(i, iCount, str);

							tableModel->setItem(i, iCount, new QStandardItem(str));
						}

						iCount++;
					}
				}
			}
		}
	}


}


void frmMemberNoticeDlg::OnDBClicked(const QModelIndex &index)
{
	//int index = ui.tableView->currentIndex().row;
	//QModelIndex index = ui.tableView->currentIndex();
	//if (index.isValid())
	//{
	//	//QString sgr = tableModel->itemData(index).value().toString();
	//	////QS = tableModel->itemData(index.row());
	//	//QString value = record.value("xxxxxxx").toString();
	//}
	//���˫��
	OnBnClickedButtonDetail();
}

// ��ϸ��ť�Ĵ�������
void frmMemberNoticeDlg::OnBnClickedButtonDetail()
{
	int index = ui.tableView->currentIndex().row();//m_list.GetSelectionMark();//
	if (index == -1)
	{
		QMessageBox::information(nullptr, /*QStringLiteral*/("��ʾ"), /*QStringLiteral*/("����ѡ����"));

		return;
	}
	else
	{
		frmNoticeDetailDlg dlg;
		
		dlg.InitData(tableModel->item(index, 1)->text(),
			tableModel->item(index, 3)->text(),
			tableModel->item(index, 2)->text());

		dlg.exec();
	}
}



QString frmMemberNoticeDlg::ConvertCode(QString strUTF8)
{
	QString strDes, str1, str2, str3,str8;
	int len = strUTF8.count();
	int t;
	char *stop;

	for (int i = 0; i < len;)
	{
		if (strUTF8.at(i) == '%')
		{
			str1 = strUTF8.mid(i + 1, 2);
			if (str1 == "0A") // ����޷���"0A"ת��Ϊ���з�������
			{
				str2 = "\r\n";
			}
			else
			{
				QByteArray ba = str1.toLatin1();
				t = strtol(ba.data(), &stop, 16);
				str2.sprintf("%c", t);
			}
			str8 += str1;
			str3 = str3 + str2;
			i = i + 2;
		}
		else
		{
			str1 = strUTF8.mid(i, 1);

			//�������˷��͹��������ݿո��ɼӺŵ�����
			if (str1 == "+")
			{
				str1 = " ";

			}
			str3 = str3 + str1;

			str8 += str1;
		}

		i++;
	}

	QByteArray   ba = str3.toLatin1();
	char * szU8 =  ba.data();

    //������������utf8�����
	//utf8 to unicode
	//Ԥת�����õ�����ռ�Ĵ�С 
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ� 
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	//ת�� 
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
	//������'\0' 
	wszString[wcsLen] = '\0';

	strDes = QString::fromStdWString(wszString);//��խת��

	delete[]wszString;

	return strDes;
}