#include "frmDeferCloseCalDlg.h"
#include "macrodefs.h"
#include "TraderCpMgr.h"
#include "HJConstant.h"
#include <QListView>
#include "Mgr/QuotationMgr.h"
#include "TranMessage.h"
#include "HJGlobalFun.h"


frmDeferCloseCalDlg::frmDeferCloseCalDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);

	//QStringList  strList;
	for (size_t i = 0; i < g_TraderCpMgr.m_vProdCode.size(); i++)
	{
		// ���Ʒ��Ϊ���ڣ�����ӵ��б�
		if (g_TraderCpMgr.m_vProdCode.at(i).market_id == CONSTANT_B_MARKET_ID_DEFER)
		{
			QString sProdCode = g_TraderCpMgr.m_vProdCode.at(i).prod_code;
			//strList.append(sProdCode);
			ui.comboBox_code->insertItem(i, sProdCode, sProdCode);
		}
	}
	//ui.comboBox_code->addItems(strList);
	ui.comboBox_code->setView(new QListView());//�Ӵ˾䣬CSS��ʽ�����߶ȣ���������ʽ����Ч

	ui.comboBox_code->setCurrentIndex(0);


	ui.comboBox_type->insertItem(0,QStringLiteral("����ƽ�ղ�"),"b");//b
	ui.comboBox_type->insertItem(1,QStringLiteral("����ƽ���"),"s");//s
	ui.comboBox_type->setCurrentIndex(0);


	//���ü۸�
	QString sProdCode = ui.comboBox_code->currentText();

	// ���ü۸�ؼ�
	//CHJCommon::SetPriceControl(m_ctlEditPrice, sProdCode);

	// ���۸�
	ui.doubleSpinBox_price->setMaximum(10000);

	if (sProdCode.contains(QStringLiteral("Ag(T+D)")))
	{
		ui.doubleSpinBox_price->setMinimum(1);
		ui.doubleSpinBox_price->setSingleStep(1);
	}
	else
	{	ui.doubleSpinBox_price->setMinimum(0.01);
		ui.doubleSpinBox_price->setSingleStep(0.01);
	}

	const QUOTATION* pQuo = g_QuoMgr.GetQuotation(sProdCode);
	if (pQuo != NULL)
	{
		ui.doubleSpinBox_price->setValue(g_QuoMgr.GetBSPriceEx(*pQuo, (ui.comboBox_type->currentText().contains("ƽ���") ? PriceType_Buy1 : PriceType_Sell1)));

	}

	ui.spinBox_num->setMinimum(1);
	ui.spinBox_num->setMaximum(10000);
	ui.spinBox_num->setSingleStep(1);
	ui.spinBox_num->setValue(1);

	ui.label_up_val->setText(QStringLiteral("0"));
	ui.label_down_val->setText(QStringLiteral("0"));

	connect(ui.comboBox_code, SIGNAL(currentIndexChanged(QString)), this, SLOT(slotChangeCode(QString)));

	connect(ui.pushButton, &QPushButton::clicked, this, &frmDeferCloseCalDlg::slotCal);


	//setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\dialog.css"));


	setFixedSize(649, 400);
	ui.widget->setGeometry(0, 0, 649, 300);
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("����ƽ������"));

}

frmDeferCloseCalDlg::~frmDeferCloseCalDlg()
{
}


void frmDeferCloseCalDlg::initStyle()
{
	//setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\dialog.css"));
	//this->setProperty("Form", true);
	//this->setProperty("CanMove", true);
	////ui.horizontalLayout_main->setGeometry(QRect(0, 0, width(), height()));

	////���ô������������
	//this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
	//ui.label_login_png->setPixmap(QPixmap::fromImage(QImage(":/res/login")));
	//ui.label_login_png->setFixedWidth(389);
	//ui.label_login_png->setFixedHeight(598);
	//QStringList list;
	//list << tr("���ױ���") << tr("�����ʺ�");//<< tr("����֤") << tr("�۰�ͨ��֤");
	//ui.comboBox_login_type->addItems(list);

	//ui.textEdit_user_pswd->setEchoMode(QLineEdit::Password);
	//ui.textEdit_userId->setText(App::user);

}


void frmDeferCloseCalDlg::slotChangeCode(QString str)
{
	QString sProdCode = ui.comboBox_code->currentText();
	const QUOTATION* pQuo = g_QuoMgr.GetQuotation(sProdCode);
	if (pQuo != NULL)
	{
		ui.doubleSpinBox_price->setValue(g_QuoMgr.GetBSPriceEx(*pQuo, (ui.comboBox_type->currentText().contains("ƽ���") ? PriceType_Buy1 : PriceType_Sell1)));
	}

	if (sProdCode.contains(QStringLiteral("Ag(T+D)")))
	{
		ui.doubleSpinBox_price->setMinimum(1);
		ui.doubleSpinBox_price->setSingleStep(1);
	}
	else
	{
		ui.doubleSpinBox_price->setMinimum(0.01);
		ui.doubleSpinBox_price->setSingleStep(0.01);
	}
}



// �������Ϸ���
bool frmDeferCloseCalDlg::CheckInput()
{
	//int index;

	//// ��Լ�����Ƿ�ѡ��
	//index = ui.comboBox_code->currentIndex();
	//if (index == -1)
	//{
	//	//AfxMessageBox("��Լ����û��ѡ��");
	//	GetDlgItem(IDC_COMBO_PROD_CODE)->SetFocus();
	//	return false;
	//}

	//// ƽ�������Ƿ�ѡ��
	//index = m_combType.GetCurSel();
	//if (index == -1)
	//{
	//	//AfxMessageBox("ƽ������û��ѡ��");
	//	GetDlgItem(IDC_COMBO_CLOPOS_TYPE)->SetFocus();
	//	return false;
	//}

	return true;
}

void frmDeferCloseCalDlg::slotCal()
{

	if (!CheckInput())
	{
		return;
	}

	// ��տؼ�
	ui.label_close_fee->setText(QStringLiteral(""));
	ui.label_up_count->setText(QStringLiteral(""));
	ui.label_down_count->setText(QStringLiteral(""));
	ui.label_close_gain->setText(QStringLiteral(""));
	ui.label_close_canuse->setText(QStringLiteral(""));
	// ���ͱ���
	Rsp4071 rsp; //Ӧ������
	int iReturn = CTranMessage::Handle4071(rsp, ui.comboBox_code->currentData().toString(), ui.comboBox_type->currentData().toString(), ui.doubleSpinBox_price->text(), ui.spinBox_num->value());
	if (iReturn == 0)
	{
		ui.label_close_fee->setText(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.cov_exch_fare)));
		ui.label_close_gain->setText(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.cov_surplus)));
		ui.label_up_count->setText(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.remain_long)));
		ui.label_close_canuse->setText(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.can_use_bal)));
		ui.label_down_count->setText(CHJGlobalFun::FormatFloat(CHJGlobalFun::str2qstr(rsp.remain_short)));

	}
}