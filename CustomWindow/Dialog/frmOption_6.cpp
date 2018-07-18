#include "frmOption_6.h"
#include "Global.h"
#include "app.h"
#include "HJGlobalFun.h"
//#include <QScrollBar>
#include "TraderCpMgr.h"
#include <QMessageBox>

#pragma execution_character_set("utf-8")


frmOption_6::frmOption_6(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_strFileName = "";
	ui.listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	
	//connect(ui.listWidget, &QListWidget::itemSelectionChanged , this, &frmOption_6::ProcessSelect);



}

frmOption_6::~frmOption_6()
{
}
void frmOption_6::saveIni()
{
	if (!CompareData()) // ����û������ı�Ŵ���
	{
		m_strUserColumnIndexsOld = m_strUserColumnIndexsNew;
		QString strPath = QString("%1QueryConfig\\%2.ini").arg(g_Global.GetSystemPath()).arg(m_strFileName);
		App::WritePriProfileString(strPath,"Info", "UserColumnIndexs", m_strUserColumnIndexsNew);

		//֪ͨ��صĽ��棬�������ݸ���
		if (m_uiMessage > 0)
		{
			g_TraderCpMgr.m_mapBdr[E_UPDATE_LIST].Broadcast(m_uiMessage, NULL, NULL, FALSE);
		}
	}

}

void frmOption_6::ProcessSelect(int row, int col)
{
	if (row == 0)
	{//������ǵ�1��item������,emit�źŸı�button1��״̬

	}
	else if (row == 1)
	{//������ǵ�2��item�����ģ�emit�źŸı�button2��״̬

	}
}


void frmOption_6::loadIni()
{
	QListWidgetItem *item = nullptr;
	while (nullptr != (item = ui.listWidget->takeItem(0)))
	{
		delete item;
		item = nullptr;
	}


	list.clear();

	LoadInfo("UserColumnIndexs");
}

void frmOption_6::setFileName(const QString &csFileTitle)
{
	m_strFileName = csFileTitle;
}

void frmOption_6::LoadInfo(const QString &csUserTitle)
{
	m_vShowFlag.clear();

	// ��ȡAllColumnNames���ָ���飬Ȼ����ӵ�list
	// ��ȡUserColumnIndexs���ָ���飬�����������ö�Ӧ���ֶε�checkΪtrue
	// ��ȡ�����ļ���·��
	QString strPath = QString("%1QueryConfig\\%2.ini").arg(g_Global.GetSystemPath()).arg(m_strFileName);

	QString strValue;
	QString strAligns;
	int i;
	QVector<QString> vecAllNames;
	QVector<int> vecColumnIndexs;

	QString buf;

	// ��ȡȫ���ֶ����ƣ����ָvector
	App::GetPriProfileString(strPath,"Info", "AllColumnNames", buf);
	strValue = buf;
	CHJGlobalFun::SplitStrToVector(strValue, QUERY_INI_SPLITER, vecAllNames);

	// ��ȡλ���ֶΣ����ҷָvector
	App::GetPriProfileString(strPath, "Info", csUserTitle, buf);
	strValue = buf;
	CHJGlobalFun::SplitStrToVector(strValue, QUERY_INI_SPLITER, vecColumnIndexs);
	if (csUserTitle != "DefaultColumnIndexs")
	{
		m_strUserColumnIndexsOld = strValue;
	}

	// ���ص�ǰ��ʾ��
	for (i = 0; i < vecColumnIndexs.size(); i++)
	{
		// ��������
		//��ӽ�����
		QListWidgetItem * item = new QListWidgetItem();
		item->setCheckState(Qt::Checked);
		item->setText(vecAllNames.at(vecColumnIndexs.at(i)));
		ui.listWidget->addItem(item);

		//ui.listWidget->setItemWidget(item, list[list.count() - 1]);
		//�����Զ���ֵ
		item->setData(Qt::UserRole, vecColumnIndexs.at(i));
		// ���ýڵ�ֵ
		//m_CheckListbox.SetItemData(i, vecColumnIndexs.at(i));
		// ���ÿɼ�
		//m_CheckListbox.SetCheck(i, true);
	}

	int iCount = vecColumnIndexs.size();
	// ����û����ʾ���˳����ʾ
	for (i = 0; i < vecAllNames.size(); i++)
	{
		if (!IsLoad(vecColumnIndexs, i))
		{
			// ��������
			QListWidgetItem * item = new QListWidgetItem();
			item->setCheckState(Qt::Unchecked);
			item->setText(vecAllNames.at(i));

			ui.listWidget->addItem(item);
			//ui.listWidget->setItemWidget(item, list[list.count() - 1]);

			// ���ýڵ�ֵ
			//m_CheckListbox.SetItemData(iCount, i);
			item->setData(Qt::UserRole, i);

			// ���ò��ɼ�����ȥ����ΪĬ����û��ѡ�е�
			//m_CheckListbox.SetCheck(iCount, false);
			iCount++;
		}
	}

	// ��ȡλ���ֶΣ����ҷָvector
	App::GetPriProfileString(strPath,"Info", "ShowFlag", buf);
	strValue = buf;
	CHJGlobalFun::SplitStrToVector(strValue, QUERY_INI_SPLITER, m_vShowFlag);
}


bool frmOption_6::IsLoad(const QVector<int> &vecColumnIndexs, int iPos)
{
	for (size_t i = 0; i < vecColumnIndexs.size(); i++)
	{
		if (vecColumnIndexs.at(i) == iPos)
		{
			return true;
		}
	}

	return false;
}

// ��iPosλ���ϵ��ַ������ƣ�Ҳ������������ַ�������
void frmOption_6::MoveUp(int iPos)
{
	Qt::CheckState bCur, bOther;
	
	bCur   = ui.listWidget->item(iPos)->checkState();
	bOther = ui.listWidget->item(iPos-1)->checkState();

	QString textCur = ui.listWidget->item(iPos)->text();
	QString textPre = ui.listWidget->item(iPos-1)->text();

	ui.listWidget->item(iPos)->setText(textPre);
	ui.listWidget->item(iPos)->setCheckState(bOther);

	ui.listWidget->item(iPos-1)->setText(textCur);
	ui.listWidget->item(iPos-1)->setCheckState(bCur);


}

void frmOption_6::slotUp()
{
	int iPos = ui.listWidget->currentRow();
	if (iPos == -1)
	{
		QMessageBox::information(nullptr, "��ʾ", "��ǰû��ѡ���", QMessageBox::Ok);
		//AfxMessageBox("��ǰû��ѡ���");
	}
	else if (iPos == 0)
	{

	}
	else
	{
		MoveUp(iPos);
		//SendDataModifiedStatus();
	}
}

void frmOption_6::slotDown()
{
	int iPos = ui.listWidget->currentRow();

	if (iPos == -1)
	{
		QMessageBox::information(nullptr, "��ʾ", "��ǰû��ѡ���", QMessageBox::Ok);
	}
	else if (iPos == ui.listWidget->count()-1)//m_CheckListbox.GetCount() - 1)
	{
		// �Ѿ������һ��
	}
	else
	{
		// ��iPos���ƣ���ʵҲ�����൱�ڽ����������
		iPos = iPos + 1;
		MoveUp(iPos);

		ui.listWidget->setItemSelected(ui.listWidget->item(iPos),true);
	}

}
void frmOption_6::slotAll()
{
	for (int i = 0; i < ui.listWidget->count()/*m_CheckListbox.GetCount()*/; i++)
	{
		ui.listWidget->item(i)->setCheckState(Qt::Checked);
	}

}

void frmOption_6::slotUnAll()
{
	int iCount = 0;
	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		// �������ǿ����ʾ��������Ϊ��ѡ��
		QListWidgetItem *pItem =  ui.listWidget->item(i);
		if (pItem->checkState() == Qt::Checked)
		{
			pItem->setCheckState(Qt::Unchecked);
		}
		else
		{
			iCount++;
		}
	}
	//SendDataModifiedStatus();

	if (iCount > 0)
	{
		QMessageBox::information(nullptr, "��ʾ", "�����б�����ʾ���У�", QMessageBox::Ok);
	}

}

void frmOption_6::slotDefault()
{
	QListWidgetItem *item = nullptr;
	while (nullptr != (item = ui.listWidget->takeItem(0)))
	{
		delete item;
		item = nullptr;
	}


	list.clear();

	LoadInfo("DefaultColumnIndexs");
}



bool frmOption_6::CompareData()
{
	m_strUserColumnIndexsNew = "";

	for (int i = 0; i <ui.listWidget->count(); i++)
	{
		QListWidgetItem *pItem = ui.listWidget->item(i);
		if (pItem->checkState() == Qt::Checked)
		{
			QString strPos = pItem->data(Qt::UserRole).toString();
			m_strUserColumnIndexsNew += strPos + QUERY_INI_SPLITER;
		}
	}

	if (m_strUserColumnIndexsOld == m_strUserColumnIndexsNew) // ǰ��������ͬ
	{
		return true;
	}

	return false;
}

void frmOption_6::SetMessageID(uint uiMes)
{
	//
	m_uiMessage = uiMes;
}