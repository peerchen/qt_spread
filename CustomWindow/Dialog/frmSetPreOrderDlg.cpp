#include "frmSetPreOrderDlg.h"
#include  "HJDef.h"
#include "TraderCpMgr.h"
#include "Global.h"
#include "HJCommon.h"
#include "Mgr/QuotationMgr.h"
#include <QMessageBox>
#include "TranMsg.h"


#pragma execution_character_set("utf-8")

frmSetPreOrderDlg::frmSetPreOrderDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);


	layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->setSpacing(0);

	ui.radioButton->show();
	ui.radioButton_2->show();
	ui.radioButton->setChecked(true);//Ĭ��

	m_bUseServer = false;


	// ��ʼ���۸����������˵�
	ui.comboBox->insertItem(0, "���¼�");
	ui.comboBox->insertItem(1, "��һ��");
	ui.comboBox->insertItem(2, "��һ��");

	ui.comboBox->setCurrentIndex(0);

	// ��ʼ���Ƚ����������˵�
	ui.comboBox_2->insertItem(0, "���ڻ����");
	ui.comboBox_2->insertItem(1, "С�ڻ����");
	ui.comboBox_2->insertItem(2, "����");

	ui.comboBox_2->setCurrentIndex(0);

	//if (!g_Global.m_bUseSerPreOrder)
	//{

	//	GetDlgItem(IDC_CHECK_USE_SERVER)->ShowWindow(SW_HIDE);
	//}


	ui.label->hide();
	ui.comboBox->hide();
	ui.comboBox_2->hide();
	ui.doubleSpinBox->hide();
	ui.spinBox->hide();
	ui.label_2->hide();


	// �۸�ؼ�
	/*const QUOTATION* pQT = g_QuoMgr.GetQuotation(m_sProdCode);
	if (pQT != nullptr)
	{		
		// ������¼�
		QString csLast = "";
		g_QuoMgr.GetFormatPrice(csLast, m_sProdCode, PriceType_Last);
		// ���ü۸�ؼ�������
		//CHJCommon::SetPriceControl(m_editPrice, m_sProdCode, pQT);
		if (m_sProdCode == "Ag(T+D)" || m_sProdCode == "Ag99.9")
		{
			ui.spinBox ->setEnabled(true);
			ui.doubleSpinBox->setEnabled(false);
			// ���ü۸�
			ui.spinBox->setMinimum(1);
			ui.spinBox->setSingleStep(1);
			ui.spinBox->setValue(csLast.toInt());
			spinType = 0;
		}
		else
		{
			ui.spinBox->setEnabled(false);
			ui.doubleSpinBox->setEnabled(true);

			// ���ü۸�			
			ui.doubleSpinBox->setMinimum(0.01);
			ui.doubleSpinBox->setSingleStep(0.01);
			ui.doubleSpinBox->setValue(csLast.toDouble());
			spinType = 2;
		}

		//m_editPrice.SetText(csLast, true);
		
	}
*/


	setFixedSize(600, 441);
	ui.widget->setGeometry(0, 0, 561, 341);
	setContent(ui.widget);


	setWindowTitle(("���ô�������"));
}

frmSetPreOrderDlg::~frmSetPreOrderDlg()
{
}

//����ǰ��̬����
void frmSetPreOrderDlg::initLayOut()
{

	//// ����ǽ��ջ��������֣�������������ѡ
	//if (IsDeferSpecial(m_sExchId))
	//{
	//	ui.radioButton_3->setEnabled(false);
	//	m_csAskInfo = QString("'��").arg(m_sProdCode).arg(g_TraderCpMgr.GetExchName(m_sExchId)).arg(m_iHand);

	//}
	//else
	//{
	//	// ��ʼ��������ʾ
	//	m_csAskInfo = QString("%1���۸�%2%3%4��").arg(m_sProdCode).arg(m_csAskPrice).arg(g_TraderCpMgr.GetExchName(m_sExchId)).arg(m_iHand);

	//}

	//���ݵ�ǰֵ�����ж�̬����
	ui.groupBox->setFixedHeight(131);
	//layout->addWidget(ui.groupBox);


	// ����ǽ��ջ��������֣�������������ѡ
	if (IsDeferSpecial(m_sExchId))
	{
		ui.radioButton_3->setChecked(false);
		m_csAskInfo = QString("%1%2%3��").arg(m_sProdCode).arg(g_TraderCpMgr.GetExchName(m_sExchId)).arg(m_iHand);

	}
	else
	{
		// ��ʼ��������ʾ
		m_csAskInfo = QString("%1���۸�%2%3%4��").arg(m_sProdCode).arg(m_csAskPrice).arg(g_TraderCpMgr.GetExchName(m_sExchId)).arg(m_iHand);

	}

	//��֯��ʾ
	ui.label_tip->setText(m_csAskInfo);


	
	//if (ui.radioButton_3->isChecked())
	//{
	//	QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
	//	//���벼��
	//	hBoxLayout->addWidget(ui.label);
	//	hBoxLayout->addWidget(ui.comboBox);
	//	hBoxLayout->addWidget(ui.comboBox_2);

	//	if (spinType >= 2)
	//		hBoxLayout->addWidget(ui.doubleSpinBox);
	//	else
	//		hBoxLayout->addWidget(ui.spinBox);

	//	hBoxLayout->addWidget(ui.label_2);


	//	layout->addLayout(hBoxLayout);
	//}

	//layout->addWidget(ui.label_tip,0,Qt::AlignHCenter);

	//ui.widget->setLayout(layout);

}

//��Ӧradio3--��̬����
void frmSetPreOrderDlg::slotReLayout()
{
	const QUOTATION* pQT = g_QuoMgr.GetQuotation(m_sProdCode);
	if (pQT != nullptr)
	{
		// ������¼�
		QString csLast = "";
		g_QuoMgr.GetFormatPrice(csLast, m_sProdCode, PriceType_Last);
		// ���ü۸�ؼ�������
		//CHJCommon::SetPriceControl(m_editPrice, m_sProdCode, pQT);
		if (m_sProdCode == "Ag(T+D)" || m_sProdCode == "Ag99.9")
		{
			ui.spinBox->setEnabled(true);
			ui.doubleSpinBox->setEnabled(false);
			// ���ü۸�
			ui.spinBox->setMinimum(1);
			ui.spinBox->setSingleStep(1);
			//int value = csLast.toDouble();
			ui.spinBox->setValue(csLast.toDouble());
			spinType = 0;

			ui.doubleSpinBox->hide();
			ui.spinBox->show();
		}
		else
		{

			ui.spinBox->setEnabled(false);
			ui.doubleSpinBox->setEnabled(true);

			// ���ü۸�			
			ui.doubleSpinBox->setMinimum(0.01);
			ui.doubleSpinBox->setSingleStep(0.01);
			ui.doubleSpinBox->setValue(csLast.toDouble());
			spinType = 2;

			ui.spinBox->hide();
			ui.doubleSpinBox->show();
		}

	}

	ui.label->show();
	ui.comboBox->show();
	ui.comboBox_2->show();
	ui.label_2->show();
	

	ui.radioButton->setEnabled(true);
	ui.radioButton_2->setEnabled(true);
	//���²���
	//initLayOut();

	radioindex = 2;
}



void  frmSetPreOrderDlg::slotRadio0()
{
	radioindex = 0;

	ui.label->hide();
	ui.comboBox->hide();
	ui.comboBox_2->hide();
	ui.doubleSpinBox->hide();
	ui.spinBox->hide();
	ui.label_2->hide();

}

void  frmSetPreOrderDlg::slotRadio1()
{
	radioindex = 1;

	ui.label->hide();
	ui.comboBox->hide();
	ui.comboBox_2->hide();
	ui.doubleSpinBox->hide();
	ui.spinBox->hide();
	ui.label_2->hide();
}

//
void frmSetPreOrderDlg::slotOk()
{
	// ��ȡ��ѡ��radio��ť���ڵ��У���1��ʼ��
	int iCheckRadioPos = radioindex+1;//GetCheckRaido();
	if (iCheckRadioPos != 0) // �����radio��ť��ѡ��
	{
		if (iCheckRadioPos == 1 || iCheckRadioPos == 2 || iCheckRadioPos == 3) // ����Ϊfalse������ܣ�Ԥ���쳣����
		{
			PreOrderStruct stPreOrder;
			// ������Ϣ��ʼ��
			stPreOrder.sProdCode = CHJGlobalFun::qstr2str(m_sProdCode);
			stPreOrder.sExchId   = CHJGlobalFun::qstr2str(m_sExchId);
			stPreOrder.dPrice    = m_csAskPrice.toDouble();
			stPreOrder.iHand     = m_iHand.toInt(); // ί������
			stPreOrder.sTime     = CHJGlobalFun::qstr2str(CHJGlobalFun::GetCurTimeFormat());

			if (iCheckRadioPos == 1) // ������ֶ�Ԥ��
			{
				stPreOrder.eOrderType = PreOrderType_Hand;
			}
			else if (iCheckRadioPos == 3) // �����������
			{
				EQTType eQTType;
				ECompareType eCmpType;
				double dPrice;
				if (GetConditionValue(eQTType, eCmpType, dPrice))
				{
					if (!m_bUseServer)
					{
						stPreOrder.eCompType = eCmpType;
						stPreOrder.eQTType = eQTType;
						stPreOrder.dCmpPrice = dPrice;
						stPreOrder.eOrderType = PreOrderType_Condition;
					}
					else //
					{
						Req4074 req;
						req.oper_flag = 2; // ���
						req.delegate_type = "0";  // ������
						req.exch_type = CHJGlobalFun::qstr2str(m_sExchId); // ���׷�ʽ
						req.prod_code = CHJGlobalFun::qstr2str(m_sProdCode); // Ʒ��
						req.entr_price = m_csAskPrice.toDouble(); // �����۸�
						req.entr_amount = m_iHand.toInt(); //����
						req.entr_price_type = "9"; // �Զ���۸�

						req.trigger_condition = CHJGlobalFun::qstr2str(QString::number(eCmpType)); // �������������Ƚ�����

						req.trigger_value_type = CHJGlobalFun::qstr2str(QString::number(eQTType)); // ����ֵ���ͣ�����������

						double dPrice = 0;																		   // ��ȡ���ռ۸�
						if (m_sProdCode == "Ag(T+D)" || m_sProdCode == "Ag99.9")
						{
							dPrice = ui.spinBox->value();

						}
						else
						{
							dPrice = ui.doubleSpinBox->value();
						}

						req.trigger_value = dPrice; // �����۸񣬼��Ƚϼ۸�

						Rsp4074 rsp;
						if (CTranMsg::Handle4074(rsp, req))
						{
							QMessageBox::information(nullptr,"��ʾ","��ӷ������������ɹ���");
							g_TraderCpMgr.m_mapBdr[E_SER_PREORDER_REFRESH].Broadcast(WM_SER_PREORDER_REFRESH, 0, 0);
							//OnOK();
							close();
							return;
						}
						else
						{
							return;
						}
					}
				}
				else
				{
					// ��ȡ������Ϣ�쳣
					return;
				}
			}
			else // ������Զ�Ԥ��
			{
				stPreOrder.eOrderType = PreOrderType_AUTO;
			}

			// ����һ��Ԥ��
			int iOrderID = g_TraderCpMgr.m_cPreOrder.Add(stPreOrder);
			
			//20180408
			//g_TraderCpMgr.pool.AddTask(std::bind(&CPreOrder::CommitAskAll, &g_TraderCpMgr.m_cPreOrder));
			
			g_TraderCpMgr.m_cPreOrder.SendMessage(iOrderID, PreOrderMsgFlag_Add);

			// �˳��Ի���
			close();
		}
	}
	else
	{

	}
}




// ��������еĿؼ��������ֵ�������ȡ��Ϣ���쳣���򷵻�false�����򷵻�true
bool frmSetPreOrderDlg::GetConditionValue(EQTType &eQTType, ECompareType &eCmpType, double &dPrice)
{
	int iPos;

	// ��ȡ�۸�ʽ��ֵ
	iPos = ui.comboBox->currentIndex();//.GetCurSel();
	if (iPos == -1)
	{
		QMessageBox::information(nullptr,"��ʾ","�۸�ʽ������û��ѡ��");
		return false;
	}
	else
	{
		switch (iPos)
		{
		case 0: eQTType = E_Latest; break;
		case 1: eQTType = E_Sell1;  break;
		case 2: eQTType = E_Buy1;   break;
		default: return false;
		}
	}

	// ��ȡ�ȽϷ�ʽ
	iPos = ui.comboBox_2->currentIndex();//.GetCurSel();
	if (iPos == -1)
	{
		//AfxMessageBox("�ȽϷ�ʽ������û��ѡ��");
		QMessageBox::information(nullptr, "��ʾ", "�ȽϷ�ʽ������û��ѡ��");
		return false;
	}
	else
	{
		switch (iPos)
		{
		case 0: eCmpType = E_Big_Equal;   break; // ���ڻ����
		case 1: eCmpType = E_Small_Equal; break; // С�ڻ����
		case 2: eCmpType = E_Equal;       break; // ����

												 //case 0: eCmpType = E_Big;         break; // ����
												 //case 1: eCmpType = E_Big_Equal;   break; // ���ڻ����
												 //case 2: eCmpType = E_Small;       break; // С��
												 //case 3: eCmpType = E_Small_Equal; break; // С�ڻ����
		default: return false;
		}
	}

	// ��ȡ���ռ۸�
	if (m_sProdCode == "Ag(T+D)" || m_sProdCode == "Ag99.9")
	{
		dPrice = ui.spinBox->value();

	}
	else
	{
		dPrice = ui.doubleSpinBox->value();
	}

	return true;
}