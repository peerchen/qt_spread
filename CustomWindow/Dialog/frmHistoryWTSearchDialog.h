#pragma once

#include <QDialog>
#include "ui_frmHistoryWTSearchDialog.h"
#include "HJQueryBase.h"
#include"frmFramelessDialogBase.h"

class frmHistoryWTSearchDialog : public frmFramelessDialogBase, public CHJQueryBase
{
	Q_OBJECT

public:
	frmHistoryWTSearchDialog(QWidget *parent = Q_NULLPTR);
	~frmHistoryWTSearchDialog();

protected:

	virtual void customEvent(QEvent *event);
	virtual string GetQueryID();
	// ��ȡ��ѯ��������������ʵ��
	virtual void GetQueryPara(QVector< pair<QString, QString> >  &vecPara);

public slots:
	void OnBnClickedButtonQuery();
	//��һҳ��ť�Ĵ�������
	void OnBnClickedButtonFirpage();
	//��һҳ��ť�Ĵ�������
	void OnBnClickedButtonPrepage();
	//��һҳ��ť�Ĵ�������
	void OnBnClickedButtonNexpage();
	//���һҳ��ť�Ĵ�������
	void OnBnClickedButtonLaspage();

	void comboBoxNumChanged(QString str);
	//��ѯ��ť�Ĵ�������
	void comboBoxPageChanged(QString str);
	void OnCbnSelchangeComboProdCode(QString str);

	void OnBnClickedOutTExcel();
	void OnBnClickedOption();

private:
	Ui::frmHistoryWTSearchDialog ui;
};
