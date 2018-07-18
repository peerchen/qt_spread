#include "frmOption_5.h"
#include "Global.h"
#include "stopPlMgr.h"
#include <QMessageBox>
#include "app.h"
#include "HJGlobalFun.h"
#include <QGridLayout>
#include  "HJCommon.h"


#pragma execution_character_set("utf-8")

frmOption_5::frmOption_5(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//��ʼ���ؼ�
	// ��ʼ�����������������˵�
	ui.comboBox->clear();

	ui.comboBox->insertItem(0, "ÿ�ʿ��ּ�");
	ui.comboBox->insertItem(1, "�ֲ־���");
	ui.comboBox->setItemData(0, E_PLMatchPrice);
	ui.comboBox->setItemData(1, E_PLPosiAvg);

	// ��ʼ�����������������˵�
	/*m_cmbAskPriceType.InsertString(0, "���¼�");
	m_cmbAskPriceType.InsertString(1, "������");
	m_cmbAskPriceType.SetItemData(0, (DWORD_PTR)e_PLLatestPrice);
	m_cmbAskPriceType.SetItemData(1, (DWORD_PTR)e_BuySellPrice);*/
	ui.comboBox_1->clear();
	ui.comboBox_1->insertItem(0, "���¼�");
	ui.comboBox_1->insertItem(1, "������");
	ui.comboBox_1->setItemData(0, e_PLLatestPrice);
	ui.comboBox_1->setItemData(1, e_BuySellPrice);

	// ��ʼ���۸�ƫ��������
	//m_editAjust.IniInt(CScrollEdit::e_min, 0);
	ui.spinBox->setMinimum(0);
	ui.spinBox->setSingleStep(1);
	//��ʼ����
	//���ñ�����
	tableModel = new QStandardItemModel();

	////������
	tableModel->setColumnCount(4);
	int columnIndex = 0;
	tableModel->setHeaderData(columnIndex, Qt::Horizontal, tr("Ʒ��/��Լ����"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("ֹ�������λ"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("ֹӯ������λ"));
	tableModel->setHeaderData(++columnIndex, Qt::Horizontal, tr("׷��ֹ�������λ"));

	tableModel->setSortRole(1);
	ui.tableView->setModel(tableModel);

	ui.tableView->setBaseSize(width() + 50, 350);
	ui.tableView->horizontalHeader()->setFixedHeight(32);
	ui.tableView->verticalHeader()->hide();
	ui.tableView->verticalHeader()->setDefaultSectionSize(30);
	ui.tableView->setShowGrid(false);
	ui.tableView->setSortingEnabled(false);
	ui.tableView->setAlternatingRowColors(true);//���л�ɫ
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	//��ʼ��ֹӯֹ��
	LoadSetting();
}

frmOption_5::~frmOption_5()
{
}
void frmOption_5::saveIni()
{
	if (!g_Global.m_bEnableIniFile)
	{
		QMessageBox::information(nullptr, "ϵͳ��ʾ", "��ǰϵͳ��¼�û����ǹ���Ա��û��Ȩ���޸����ã��޷�����.");
		return;
	}
	if (m_bModified)
	{
		WriteStopPLSetting();

		WriteInstSetting();

		g_StopPLMgr.LoadSetting();
	}

}


void frmOption_5::LoadSetting()
{
	//kenny 2018-1-9
	g_StopPLMgr.LoadSetting();
	// �����۸�����
	if (g_StopPLMgr.GetCmpType() == E_PLMatchPrice)
		ui.comboBox->setCurrentIndex(0);
	else
		ui.comboBox->setCurrentIndex(1);

	// �����۸�����
	if (g_StopPLMgr.GetAskPriceType() == e_PLLatestPrice)
		ui.comboBox_1->setCurrentIndex(0);
	else
		ui.comboBox_1->setCurrentIndex(1);

	// ������λ
	/*QString csAjust;
	csAjust.Format("%d", g_StopPLMgr.GetAskPriceAjust());*/
	ui.spinBox->setValue(g_StopPLMgr.GetAskPriceAjust());

	// �Ƿ��Ƿ�����
	if (g_Global.m_bUseSerPreOrder)
	{
		m_bUseServer = g_StopPLMgr.IsServer();
	}
	else // ���û�з�������������Ȩ�ޣ��򲻿ɼ�
	{
//#ifdef _VERSION_GF
//		GetDlgItem(IDC_CHECK_USE_SERVER)->EnableWindow(FALSE);
//#else
//		GetDlgItem(IDC_CHECK_USE_SERVER)->ShowWindow(SW_HIDE);
//#endif
		m_bUseServer = false;
	}

	// ����Ʒ�ֵ�����
	int i = 0;
	const map<string, PLInfo>* pInfo = g_StopPLMgr.GetInfo();
	for (map<string, PLInfo>::const_iterator it = pInfo->begin(); it != pInfo->end(); it++, i++)
	{
		QString csValue;
		//m_list.InsertItem(i, it->first.c_str());    // ��Լ����
		tableModel->insertRow(i);
		tableModel->setItem(i, 0, new QStandardItem(CHJGlobalFun::str2qstr(it->first)));
		tableModel->setItem(i, 1, new QStandardItem(QString::number(it->second.iStopLossAjust)));		//// ֹ�������λ
		tableModel->setItem(i, 2, new QStandardItem(QString::number(it->second.iStopProfitAjust)));		//// ֹӯ������λ
		tableModel->setItem(i, 3, new QStandardItem(QString::number(it->second.iDysAjust)));		//// �Զ�׷��ֹ�������λ

	}

	
}




void frmOption_5::WriteStopPLSetting(void)
{
	QString csStopPL;

	int iPosCmp = ui.comboBox->currentIndex();//.GetCurSel();
	int iPosAsk = ui.comboBox_1->currentIndex();//m_cmbAskPriceType.GetCurSel();

	//QString csAjust(ui.spinBox.GetText());
	//if (csAjust.IsEmpty())
	//	csAjust = "0";
	csStopPL = QString("%1^%2^%3^%4^").arg(ui.comboBox->itemData(iPosCmp).toString())
		.arg(ui.comboBox_1->itemData(iPosAsk).toString()).arg(ui.spinBox->value()).arg(m_bUseServer);

	App::WritePriProfileString(g_Global.GetUserIniPath(), "PreOrder", "StopPLSetting", csStopPL);
	WriteStopPLSettingLOG(iPosCmp, iPosAsk, QString::number(ui.spinBox->value()));

}

void frmOption_5::WriteStopPLSettingLOG(int iPosCmp, int iPosAsk, const QString csAjust)
{
	QString sLog = "ֹӯֹ�𴥷����ã����ã�";
	if (m_bUseServer)
	{
		sLog += "������";
	}
	else
	{
		sLog += "����";
	}
	sLog += "��ֹӯֹ�𣬴�����׼�ۣ���";
	if (iPosCmp == E_PLMatchPrice)
		sLog += "�ɽ��۸�";
	else
		sLog += "�ֲ־���";

	sLog += "����������Ϣ����";
	if (iPosAsk == e_PLLatestPrice)
	{
		sLog += "���¼�";
	}
	else
	{
		sLog += "������";
	}
	sLog += "��������";
	sLog += csAjust;
	sLog += "������λ";
	g_Global.WriteLog(sLog);
}


void frmOption_5::WriteInstSetting()
{
	QString csWrite("InsID��StopLossAjust��StopProfitAjust��DysAjust����");

	int i;
	for (i = 0; i < tableModel->rowCount(); i++)
	{
		QString csOneInst;
		for (int j = 0; j < 4; j++)
		{
			csOneInst += tableModel->item(i,j)->text() + +"��";
				//m_list.GetItemText(i, j) + "��";
		}
		csWrite += csOneInst + "��"; // ���һ��Ʒ�ֵ�����
	}
	if (i != 0)
		csWrite += "��"; // ����������õ�ʱ����ӽ�����

	//WritePrivateProfileString("PreOrder", "InstSetting", csWrite, g_Global.GetUserIniPath());
	App::WritePriProfileString(g_Global.GetUserIniPath(),"PreOrder", "InstSetting", csWrite);

	QString sLog = "ֹӯֹ��Ʒ�����ã�";
	sLog += csWrite;
	g_Global.WriteLog(sLog);
}


//��ӣ����������Ի���
void frmOption_5::slotAdd()
{
	QDialog * win       = new QDialog();
	QGridLayout* layout = new QGridLayout();
	win->setLayout(layout);
	win->setWindowTitle("���Ʒ��ֹӯֹ��");
	//
	QLabel *secLabel      = new QLabel(this);
	QComboBox * prodCombo = new QComboBox(this);
	secLabel->setText("��Լ");
	//��������
	QVector<QString> vecUserNames;
	CHJGlobalFun::ReadUserChoose(g_Global.GetListIniPath("InsID"), "UserColumnIndexs", true, vecUserNames);
	//���ComboBox
	int iInserPos = 0;
	for (int i = 0; i < vecUserNames.size(); i++)
	{
		if (!IsInList(vecUserNames.at(i)) && CHJCommon::IsDefer(vecUserNames.at(i)))
			prodCombo->insertItem(iInserPos++, vecUserNames.at(i));
	}
	prodCombo->setFixedWidth(150);


	QLabel *stopL       = new QLabel(this);
	QSpinBox* stopLSpin = new QSpinBox(this);
	stopL->setText("ֹ�������λ");
	stopLSpin->setMinimum(0);
	stopLSpin->setSingleStep(1);

	QLabel *stopP       = new QLabel(this);
	QSpinBox* stopPSpin = new QSpinBox(this);
	stopP->setText("ֹӯ������λ");
	stopPSpin->setMinimum(0);
	stopPSpin->setSingleStep(1);

	QLabel *StopLTrack       = new QLabel(this);
	QSpinBox* stopLTrackSpin = new QSpinBox(this);
	StopLTrack->setText("׷��ֹ�������λ");
	stopLTrackSpin->setMinimum(0);
	stopLTrackSpin->setSingleStep(1);

	QPushButton *addButton    = new QPushButton(this);
	QPushButton *cancelButton = new QPushButton(this);
	addButton->setText("���");
	cancelButton->setText("ȡ��");
	addButton->setFixedWidth(75);
	cancelButton->setFixedWidth(75);

	layout->addWidget(secLabel, 0, 0, 1, 1);
	layout->addWidget(prodCombo, 0, 1, 1, 1);
	
	layout->addWidget(stopL, 1, 0, 1, 1);
	layout->addWidget(stopLSpin, 1, 1, 1, 1);
	layout->addWidget(stopP, 2, 0, 1, 1);
	layout->addWidget(stopPSpin, 2, 1, 1, 1);
	layout->addWidget(StopLTrack, 3, 0, 1, 1);
	layout->addWidget(stopLTrackSpin, 3, 1, 1, 1);
	layout->addWidget(addButton, 4, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(cancelButton, 4, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

	// ����ˮƽ���
	layout->setHorizontalSpacing(10);
	// ���ô�ֱ���
	layout->setVerticalSpacing(10);
	// ��������
	layout->setContentsMargins(10, 10, 10, 10);


	connect(addButton, SIGNAL(clicked()), win, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), win, SLOT(reject()));

	if (win->exec() == QDialog::Accepted)
	{
		int row = tableModel->rowCount();
		tableModel->insertRow(row);
		tableModel->setItem(row, 0,new QStandardItem(prodCombo->currentText()));
		tableModel->setItem(row, 1, new QStandardItem(QString::number(stopLSpin->value())));
		tableModel->setItem(row, 2, new QStandardItem(QString::number(stopPSpin->value())));
		tableModel->setItem(row, 3, new QStandardItem(QString::number(stopLTrackSpin->value())));
	}


}

bool frmOption_5::IsInList(const QString &csInst)
{
	for (int i = 0; i < tableModel->rowCount(); i++)
		if (tableModel->item(i, 0)->data().toString() == csInst)
			return true;
	return false;
}

//
void frmOption_5::slotModify()
{
	auto sel = ui.tableView->selectionModel()->currentIndex().row();
	if (sel < 0)
	{
		//����
		return;
	}

	QDialog * win       = new QDialog();
	QGridLayout* layout = new QGridLayout();
	win->setLayout(layout);
	win->setWindowTitle("�޸�Ʒ��ֹӯֹ��");
	//
	QLabel *secLabel      = new QLabel(this);
	QComboBox * prodCombo = new QComboBox(this);
	secLabel->setText("��Լ");
	//��������
	QVector<QString> vecUserNames;
	CHJGlobalFun::ReadUserChoose(g_Global.GetListIniPath("InsID"), "UserColumnIndexs", true, vecUserNames);
	//���ComboBox
	int iInserPos = 0;
	for (int i = 0; i < vecUserNames.size(); i++)
	{
		if (!IsInList(vecUserNames.at(i)) && CHJCommon::IsDefer(vecUserNames.at(i)))
			prodCombo->insertItem(iInserPos++, vecUserNames.at(i));
	}
	prodCombo->setFixedWidth(150);

	QLabel *stopL       = new QLabel(this);
	QSpinBox* stopLSpin = new QSpinBox(this);
	stopL->setText("ֹ�������λ");
	stopLSpin->setMinimum(0);
	stopLSpin->setSingleStep(1);

	QLabel *stopP       = new QLabel(this);
	QSpinBox* stopPSpin = new QSpinBox(this);
	stopP->setText("ֹӯ������λ");
	stopPSpin->setMinimum(0);
	stopPSpin->setSingleStep(1);

	QLabel *StopLTrack       = new QLabel(this);
	QSpinBox* stopLTrackSpin = new QSpinBox(this);
	StopLTrack->setText("׷��ֹ�������λ");
	stopLTrackSpin->setMinimum(0);
	stopLTrackSpin->setSingleStep(1);

	QPushButton *addButton    = new QPushButton(this);
	QPushButton *cancelButton = new QPushButton(this);
	addButton->setText("�޸�");
	cancelButton->setText("ȡ��");
	addButton->setFixedWidth(75);
	cancelButton->setFixedWidth(75);

	layout->addWidget(secLabel, 0, 0, 1, 1);
	layout->addWidget(prodCombo, 0, 1, 1, 1);
	
	layout->addWidget(stopL, 1, 0, 1, 1);
	layout->addWidget(stopLSpin, 1, 1, 1, 1);
	layout->addWidget(stopP, 2, 0, 1, 1);
	layout->addWidget(stopPSpin, 2, 1, 1, 1);
	layout->addWidget(StopLTrack, 3, 0, 1, 1);
	layout->addWidget(stopLTrackSpin, 3, 1, 1, 1);
	layout->addWidget(addButton, 4, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(cancelButton, 4, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

	// ����ˮƽ���
	layout->setHorizontalSpacing(10);
	// ���ô�ֱ���
	layout->setVerticalSpacing(10);
	// ��������
	layout->setContentsMargins(10, 10, 10, 10);

	//
	prodCombo->setCurrentText(tableModel->item(sel, 0)->text());
	stopLSpin->setValue(tableModel->item(sel,1)->text().toInt());
	stopPSpin->setValue(tableModel->item(sel, 2)->text().toInt());
	stopLTrackSpin->setValue(tableModel->item(sel, 3)->text().toInt());

	connect(addButton, SIGNAL(clicked()), win, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), win, SLOT(reject()));

	if (win->exec() == QDialog::Accepted)
	{
		//int row = tableModel->rowCount();
		//tableModel->insertRow(row);
		tableModel->setItem(sel, 0,new QStandardItem(prodCombo->currentText()));
		tableModel->setItem(sel, 1, new QStandardItem(QString::number(stopLSpin->value())));
		tableModel->setItem(sel, 2, new QStandardItem(QString::number(stopPSpin->value())));
		tableModel->setItem(sel, 3, new QStandardItem(QString::number(stopLTrackSpin->value())));

		m_bModified = true;
	}

}

//
void frmOption_5::slotDelete()
{
	auto sel = ui.tableView->selectionModel()->currentIndex().row();
	if (sel < 0)
	{
		//����
		return;
	}

	tableModel->removeRow(sel);

	m_bModified = true;
}