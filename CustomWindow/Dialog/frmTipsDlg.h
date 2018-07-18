#pragma once

#include <QDialog>
#include "ui_frmTipsDlg.h"
#include "Def.h"
#include "frmFramelessDialogBase.h"

class frmTipsDlg : public frmFramelessDialogBase
{
	Q_OBJECT

public:
	frmTipsDlg(QWidget *parent = Q_NULLPTR);
	~frmTipsDlg();


	void    Show(int iPos);
	QString DealTips(const QString &csTips, int &iLineCount);
	QString DealOneLine(const QString &csLine);

public slots:
	void OnBnClickedOk();
	void OnBnClickedButtonPre();
	void OnBnClickedButtonNext();

private:
	Ui::frmTipsDlg ui;

	int  m_iShowPos;// ��ǰ�Ի���Ҫ��ʾ����ʾ�ڼ�¼�е�λ��
	QString m_csTips;   // ��ʾ���ӳ�����
	QString m_csTitle;  // ��¼�Ի����title��û�õ������ڼ���
	bool    m_bCheck;      // �Ƿ��´β���ʾ��check�ؼ���ӳ�����

	int m_iAddLine;     // ��ʾ�ַ������ӵ�������Ĭ��ֻ��һ�еĸ߶ȣ�

	TipsType m_eType;   // ��ʾ������

};
