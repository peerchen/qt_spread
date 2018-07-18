#include "frmModifyOrderDlg.h"
#include "TraderCpMgr.h"
#include <QThread>
#include <QMessageBox>

frmModifyOrderDlg::frmModifyOrderDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);


	setFixedSize(261, 251);
	ui.widget->setGeometry(0, 0, 261, 151);
	setContent(ui.widget);

	setWindowTitle(QStringLiteral("�޸ı���"));


	connect(ui.pushButton_ok,SIGNAL(clicked()),this,SLOT(slotOk()));
}

frmModifyOrderDlg::~frmModifyOrderDlg()
{
}


void frmModifyOrderDlg::setVal(QString  &price, QString &num)
{
	ui.lineEdit_price->setText(price);
	ui.lineEdit_num->setText(num);
}



void frmModifyOrderDlg::IniData(const QString &csOldOrderNo, const QString &sExchTypeID, const QString &csInsID,
	const QString &csPrice, const QString &csAmount)
{
	m_csOldOrderNo = csOldOrderNo;
	m_sExchTypeID = sExchTypeID;
	m_csShouShu = csAmount;
	m_sInsID = csInsID;
	m_csPrice = csPrice;
}

void frmModifyOrderDlg::slotOk()
{
	if (g_TraderCpMgr.CancelOrder(m_csOldOrderNo) == 0)
	{
		// �ӳٰ��뷢�ͣ����������δ���ü����³�������Ϣ���¸ĵ�ʧ�ܵ�����
		QThread::sleep(1);
		int nCommiOrderRsp = g_TraderCpMgr.CommitOrder(m_sInsID, ui.lineEdit_price->text(), ui.lineEdit_num->text(), m_sExchTypeID,0);
		if (nCommiOrderRsp != 0)
		{

			QMessageBox::information(nullptr, "ϵͳ��ʾ", ("�ĵ�ʧ�ܣ�ԭ�����Ѿ�������������ָ����������ڱ��������µ���"));

		}
		else
		{

		}
	}
	else
	{

		QMessageBox::information(nullptr, "ϵͳ��ʾ", ("���ڳ������ɹ��������޷��ĵ���"));
	}

	close();
}