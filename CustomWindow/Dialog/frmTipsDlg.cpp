#include "frmTipsDlg.h"
#include "ModifySetting.h"
#include "GlobalMgr.h"
#include "ClientTips.h"
#include "TraderCpMgr.h"
#include "HJGlobalFun.h"

#pragma execution_character_set("utf-8")

const int iOneLineMaxWord = 40; // һ��������ɵ��ַ���

frmTipsDlg::frmTipsDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);

	setFixedSize(521, 351);
	ui.widget->setGeometry(0, 0, 521, 251);
	setContent(ui.widget);
}

frmTipsDlg::~frmTipsDlg()
{
}


// �����û����ã��´��Ƿ����ѵ�
void frmTipsDlg::OnBnClickedOk()
{
	// �޸��Ƿ�����
	if (ui.checkBox->isChecked())
	{
		if (m_eType == E_Tips2_Asksus)
		{
			CModifySetting::ModifyTipsAskSus(false);
		}
		else if (m_eType == E_Tips2_AskFail)
		{
			CModifySetting::ModifyTipsAskFail(false);
		}
		else if (m_eType == E_Tips2_OrderMatch)
		{
			CModifySetting::ModifyTipsOrderMatch(false);
		}
		else if (m_eType == E_Tips2_CancelSus)
		{
			CModifySetting::ModifyTipsCancelSus(false);
		}
		else if (m_eType == E_Tips2_CancelFail)
		{
			CModifySetting::ModifyTipsCancelFail(false);
		}
		else if (m_eType == E_Tips2_CreatePreOrder)
		{
			CModifySetting::ModifyTipsAskPreOrder(false);
		}
	}

	// �رնԻ���
	//PostMessage(WM_CLOSE); //	EndDialog(IDOK);
	close();
}



void frmTipsDlg::Show(int iPos)
{
	if (iPos > g_TipsManager.GetSize())
		iPos = g_TipsManager.GetSize();
	// modify by xrs 20140501�����ʾ������Ĭ�Ϲ�ѡ�´β����ѵ�����
	/*m_bCheck = FALSE;
	UpdateData(TRUE);*/
	//QCheckBox *p;
	//p->setChecked()
	ui.checkBox->setChecked(false);
	m_iShowPos = iPos;
	
	TipsOrderInfo stTipsInfo;
	if (g_TipsManager.GetTips(stTipsInfo, iPos) != -1)
	{
		{
			// ��ȡ��ʾ������
			m_eType = stTipsInfo.eTipsType;

			// begin ����������ʾ������
			if (m_eType == E_Tips2_Asksus)
			{
				m_csTitle = "�µ��ɹ�";
			}
			else if (m_eType == E_Tips2_AskFail)
			{
				m_csTitle = "�µ�ʧ��";
			}
			else if (m_eType == E_Tips2_OrderMatch)
			{
				m_csTitle = "�ɽ���֪ͨ";
			}
			else if (m_eType == E_Tips2_CancelSus)
			{
				m_csTitle = "�����ɹ�";
			}
			else if (m_eType == E_Tips2_CancelFail)
			{
				m_csTitle = "����ʧ��";
			}
			else if (m_eType == E_Tips2_CreatePreOrder)
			{
				m_csTitle = "����Ԥ��";
			}
			QString csValue = QString("(%1/%2)  %3").arg(m_iShowPos + 1).arg(g_TipsManager.GetSize()).arg( m_csTitle);
			//csValue.Format("(%d/%d)  %s", m_iShowPos + 1, g_TipsManager.GetSize(), m_csTitle);
			setWindowTitle(csValue);
			//SetWindowText(csValue);
			// end ����������ʾ������

			// ���ò������ѵ�check�ؼ�������
			//GetDlgItem(IDC_CHECK1)->SetWindowText("�´β�������" + m_csTitle);
			ui.checkBox->setText("�´β�������"+m_csTitle);

			// begin ������ʾ�����齨��ʾ����ʾ���Լ���¼tipsҪ���ӵ�����
			if (m_iShowPos > -1)
			{
				// modify by xrs 20130220 ���ݽ���ͨ���Ե�Ҫ�󣬳����ɹ�������ʾ��ʾΪ�գ��ʽ���ʾ��Ϣ��ʾΪ�������ɹ���
				if (m_eType == E_Tips2_CancelFail)
				{
					// ��������Ϊ��ʱ����ʾ��ʾ���������������Ϊ��ʧ������ʾ��ϢΪ�յ�����
					if (stTipsInfo.csOrderNo == "")
					{
						m_csTips = "��ʾ��Ϣ������ʧ�ܣ�";
						m_iAddLine = 1;
					}
					else
					{
						m_csTips = QString("���ţ�%1\r\n ��ʾ��Ϣ��%2").arg(stTipsInfo.csOrderNo).arg(stTipsInfo.csTips);
						/*m_csTips.Format("���ţ�%s\r\n ��ʾ��Ϣ��%s",
							stTipsInfo.csOrderNo, stTipsInfo.csTips*/
						//); // 
						m_iAddLine = 2;
					}
				}
				else if (m_eType == E_Tips2_CancelSus)
				{
					m_csTips = QString("���ţ�%1\r\n ��ʾ��Ϣ��%2").arg(stTipsInfo.csOrderNo).arg("�����ɹ�");

					//m_csTips.Format("���ţ�%s\r\n ��ʾ��Ϣ��%s",
					//	stTipsInfo.csOrderNo, "�����ɹ�"
					//); // 
					m_iAddLine = 2;
				}
				else if (m_eType == E_Tips2_OrderMatch)
				{
					m_csTips = QString("  �����ţ�%1\r\n ��Լ���룺%2\r\n �������ͣ�%3\r\n         �۸�%4\r\n         ������%5\r\n ��ʾ��Ϣ��%6\r\n")
						.arg(stTipsInfo.csOrderNo)
						.arg(CHJGlobalFun::str2qstr(stTipsInfo.sInsID))
						.arg(g_TraderCpMgr.GetExchName(CHJGlobalFun::str2qstr(stTipsInfo.sExchID)))
						.arg(stTipsInfo.csPrice)
						.arg(stTipsInfo.csPrice)
						.arg(stTipsInfo.csAmount)
						.arg("�ҵ��ɽ�");

					//m_csTips.Format("  �����ţ�%s\r\n ��Լ���룺%s\r\n �������ͣ�%s\r\n         �۸�%s\r\n         ������%s\r\n ��ʾ��Ϣ��%s\r\n",
					//	stTipsInfo.csOrderNo,
					//	stTipsInfo.sInsID.c_str(),
					//	g_TraderCpMgr.GetExchName(stTipsInfo.sExchID).c_str(),
					//	stTipsInfo.csPrice,
					//	stTipsInfo.csAmount,
					//	"�ҵ��ɽ�"
					//); // 
					m_iAddLine = 6;
				}
				else if (m_eType == E_Tips2_CreatePreOrder)
				{
					m_csTips = CHJGlobalFun::str2qstr(stTipsInfo.sContent);

					// ��ȡҪ��Ӷ�����
					//m_iAddLine = GetLineCount(m_csTips);
				}
				else
				{
					int iTipsLine=0;
					
					//QString csTips = DealTips(stTipsInfo.csTips, iTipsLine);
					QString csTips  = stTipsInfo.csTips;
					m_csTips = QString(" ��Լ���룺%1\r\n �������ͣ�%2\r\n         �۸�%3\r\n         ������%4\r\n ��ʾ��Ϣ��%5\r\n")
						.arg(CHJGlobalFun::str2qstr(stTipsInfo.sInsID))
						.arg(g_TraderCpMgr.GetExchName(CHJGlobalFun::str2qstr(stTipsInfo.sExchID)))
						.arg(stTipsInfo.csPrice)
						.arg(stTipsInfo.csAmount)
						.arg(csTips);

					//m_csTips.Format(" ��Լ���룺%s\r\n �������ͣ�%s\r\n         �۸�%s\r\n         ������%s\r\n ��ʾ��Ϣ��%s\r\n",
					//	stTipsInfo.sInsID.c_str(),
					//	g_TraderCpMgr.GetExchName(stTipsInfo.sExchID).c_str(),
					//	stTipsInfo.csPrice,
					//	stTipsInfo.csAmount,
					//	csTips
					//); // 
					m_iAddLine = 4 + iTipsLine;
				}
			}
			// end ������ʾ�����齨��ʾ����ʾ��
		}

		// �ƶ��ؼ�
		//MoveDialog();
		ui.label->setText(m_csTips);
		// 
		//UpdateData(FALSE);

		// ���ݵ�ǰ��ȡ��λ�ÿ�����һ������һ����ť����ʾ
		if (g_TipsManager.GetSize() <= 1) // ����һ����ȫ������
		{
			//ui.pushButton->setEnabled(false);
			//ui.pushButton_2->setEnabled(false);

			ui.pushButton->hide();
			ui.pushButton_2->hide();

			//GetDlgItem(IDC_BUTTON_PRE)->ShowWindow(FALSE);
			//GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(FALSE);
		}
		else
		{
			if (m_iShowPos == 0) // ����ǵ�һ����������һ����ť
			{
				ui.pushButton->hide();
				ui.pushButton_2->show();

				/*GetDlgItem(IDC_BUTTON_PRE)->ShowWindow(FALSE);
				GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(TRUE);*/
			}
			else if (m_iShowPos == g_TipsManager.GetSize() - 1) // ���һ����������һ����ť
			{
				ui.pushButton->show();
				ui.pushButton_2->hide();

			/*	GetDlgItem(IDC_BUTTON_PRE)->ShowWindow(TRUE);
				GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(FALSE);*/
			}
			else // ȫ����ʾ
			{
				ui.pushButton->show();
				ui.pushButton_2->show();

			/*	GetDlgItem(IDC_BUTTON_PRE)->ShowWindow(TRUE);
				GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(TRUE);*/
			}
		}
	}
}



void frmTipsDlg::OnBnClickedButtonPre()
{
	if (m_iShowPos > 0)
		Show(--m_iShowPos);
}

void frmTipsDlg::OnBnClickedButtonNext()
{
	if (m_iShowPos <  g_TipsManager.GetSize() - 1)
		Show(++m_iShowPos);
}



// ������������ص���ʾ��Ϣ�����е�ʱ��Ķ��롢ȥ�����С�һ�е�������������У�
// ���ش�������ʾ�������ش������ʾ������
QString frmTipsDlg::DealTips(const QString &csTips, int &iLineCount)
{
	QString csFinal; // �����ַ���
	QString temp;    // һ�е��ַ���

	int iPosBeg = 0;  // ��¼�������з��Ŀ�ʼλ��
	iLineCount = 0;   // ��ʼ��

	int iPos = csTips.contains("\n");
	if (iPos == -1)
	{
		// �������һ�У���ֱ�ӷ���
		iLineCount = 1;
		return csTips;
	}

	// ���еĴ���
	while (iPos != -1)
	{
		// ��ȡһ�е��ַ��������������з�
		temp = csTips.mid(iPosBeg, iPos - iPosBeg);

		// ȥ������
		if (iPos - iPosBeg > 1)
		{
			// һ�е��ַ������ʱ��Ĵ���
			if (temp.length() > iOneLineMaxWord)
			{
				temp = DealOneLine(temp);
			}
			else
			{
				// ������ǵ�һ�У�����ӿո�������
				if (iLineCount != 0)
				{
					temp = "                    " + temp;
				}
			}

			// ������1����Ӵ�����һ���ַ���
			iLineCount++;
			csFinal += temp + "\n";
		}

		// ���¿�ʼ����
		iPosBeg = iPos + 1;
		iPos = csTips.right(iPosBeg).contains("\n");//iPosBeg

		// �������һ��
		if (iPos == -1)
		{
			int iLen = csTips.length();
			// ������һ�в��ǿո�����ӣ�Ȼ������ѭ��
			if (iLen - iPosBeg > 0)
			{
				csFinal += "                    " + csTips.mid(iPosBeg);
				iLineCount++;
			}

			break;
		}
	}

	return csFinal;
}


// ��������������ַ�����һ���ַ��ĳ���������Ĵ���
QString frmTipsDlg::DealOneLine(const QString &csLine)
{
	return csLine;
}

