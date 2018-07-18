#include "frmStopOutDialog.h"
#include "TradePacketAndStruct.h"
#include "global.h"
#include "HJGlobalFun.h"
#include "TraderCpMgr.h"
#include "Macrodefs.h"


frmStopOutDialog::frmStopOutDialog(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);


	//Ϊlist2���ɽ���ˮ����ӱ�������ñ���
	//��ʼ����Լ����
	for (size_t i = 0; i < g_TraderCpMgr.m_vProdCode.size(); i++)
	{
		if (g_TraderCpMgr.m_vProdCode.at(i).market_id == "02")
		{
			ui.comboBox->insertItem(i, g_TraderCpMgr.m_vProdCode.at(i).prod_code);
			
		}
	}
	ui.comboBox->insertItem(ui.comboBox->count(), "");


	ui.dateEdit_st->setDate(QDate::fromString(g_Global.m_strExchDate, ("yyyyMMdd")));
	ui.dateEdit_ed->setDate(QDate::fromString(g_Global.m_strExchDate, ("yyyyMMdd")));

	tableModel = new QStandardItemModel();

	//setWidgetStyleFromQssFile(ui.tableView, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\ordertable.css"));

	////������
	tableModel->setColumnCount(16);
	int columnIndex = 0;
	tableModel->setHeaderData(columnIndex, Qt::Horizontal, QStringLiteral("��Լ����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("ǿƽ����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("ί�м۸�"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("ί������"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("ǿƽ����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("ǿƽ״̬"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�ɽ�����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("�ɽ�����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("ί��ʱ��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("����ʱ��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("ǿƽ���κ�"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��ʱ�����ʽ�(���)"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��ʱ����ӯ��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��ʱ���ն�"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��ʱ�ܱ�֤��"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, QStringLiteral("��ʱ��Լ�۸�"));

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


	connect(ui.QueryButton, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonQuery()));


	setFixedSize(1031, 501);
	ui.widget->setGeometry(0, 0, 1031, 401);
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("ǿƽ����ѯ"));

}

frmStopOutDialog::~frmStopOutDialog()
{
}


QString frmStopOutDialog::GetProdCode()
{
	int index = ui.comboBox->currentIndex();
	//int index = m_cmbprodc.GetCurSel();
	if (index < 0)//���ѡ��Ϊ�գ��򷵻ؿ�ֵ
	{
		return "";
	}
	else
	{
		return ui.comboBox->currentText();
	}
}


void frmStopOutDialog::OnBnClickedButtonQuery()
{
	if (ui.dateEdit_st->text().toInt()  >  ui.dateEdit_ed->text().toInt())
	{
		//AfxMessageBox("��ʼʱ�䲻�ܴ��ڽ���ʱ��");
		//QMessageBox::Information();
		return;
	}
	else
	{
		tableModel->removeRows(0, tableModel->rowCount());
		//m_list.DeleteAllItems(); //���list�ؼ�

		Req3069 req; //��������
		ArrayListMsg arraylistmsg;

		//���������ĵ�����
		req.oper_flag = 1;
		req.acct_no = CHJGlobalFun::qstr2str(g_Global.m_strUserID);
		req.instid = CHJGlobalFun::qstr2str(GetProdCode());
		req.gene_type = "";
		req.begin_date = CHJGlobalFun::qstr2str(ui.dateEdit_st->text());
		req.end_date = CHJGlobalFun::qstr2str(ui.dateEdit_ed->text());

		Rsp3069 rsp; //Ӧ������
		g_HeaderReq.SetTermType("12"); //ǿƽ������Ҫ��Ҫ�ָ��Ա�֤������ѯ
		if (0 != g_TraderCpMgr.HandlePacket(rsp, req, "3069"))
		{
			g_HeaderReq.SetTermType("03");//�ָ�
										  //AfxMessageBox(CONSTANT_CONNECT_SERVER_FAIL_TIPS);
			QMessageBox::information(nullptr, ("ϵͳ��ʾ"), rsp.rsp_msg.c_str());
			return;
		}

		g_HeaderReq.SetTermType("03");//�ָ�

		if (g_TraderCpMgr.CheckRspCode(CHJGlobalFun::str2qstr(rsp.rsp_code), CHJGlobalFun::str2qstr(rsp.rsp_msg)))
		{
			if (rsp.order_status_set.size() == 0)
			{
				//AfxMessageBox(CONSTANT_QUERY_NO_RECORD);
				return;
			}
			else
			{
				for (size_t i = 0; i < rsp.order_status_set.size(); i++) //�������ؽ��
				{
					int iPos[16] = { 4, 5, 6, 7, 8, 9, 11, 12, 15, 16, 19, 20, 21, 22, 26, 27 };
					ArrayListMsg aMsg = rsp.order_status_set.GetValue(i); //��ȡ����ĵ�һ��������
																		  //size_t count = aMsg.size();//��ȡÿ�����ݵ��ֶ���

					for (int j = 0; j < 16; j++) //������е�������
					{
						int iCompPos = iPos[j];

						QString value = CHJGlobalFun::str2qstr(aMsg.GetStringEx(iCompPos));//����ֶ�ֵ

						if (j == 1)
						{
							// ǿƽ����
							value == value;
						}
						else if (j == 2 || j == 6 || j == 14 || j == 12 || j == 11)
						{
							value = CHJGlobalFun::FormatFloat(value);
						}
						else if (j == 13)
						{
							double fValue = value.toFloat();
							//fValue += 0.001;
							fValue = 100.00*fValue;
							fValue += 0.0001;  // ���float���µ����
											   //QString strValue;
											   //strValue.Format("%.2f", fValue);
											   //strValue += "%";
											   //m_list.SetItemText(i, j, strValue); //��list�ؼ����������

							tableModel->setItem(i, j, new QStandardItem(QString::number(fValue, 'f', 2) + ("%")));
							continue;
						}
						else if (j == 5)
						{
							value = g_TraderCpMgr.GetFCOrderStateName(value);
						}

						if (j == 0)
						{
							tableModel->insertRow(i);
							tableModel->setItem(i, 0, new QStandardItem(value));
							//m_list.InsertItem(i, value.c_str()); //����ÿһ�еĵ�һ��
						}
						else
						{
							tableModel->setItem(i, j, new QStandardItem(value));
							//m_list.SetItemText(i, j, value.c_str()); //��list�ؼ����������	
						}
					}
				}
			}
		}
	}
}
