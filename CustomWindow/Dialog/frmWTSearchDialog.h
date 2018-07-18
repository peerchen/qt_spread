#pragma once

#include <QDialog>
#include "frmFramelessDialogBase.H"
#include "ui_frmWTSearchDialog.h"
#include "HJQueryBase.h"

class frmWTSearchDialog : public frmFramelessDialogBase,public CHJQueryBase
{
	Q_OBJECT

public:
	frmWTSearchDialog(QWidget *parent = Q_NULLPTR);
	~frmWTSearchDialog();

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
	
	void OnBnClickedOutTExcel();
	void OnBnClickedOption();

	void comboBoxNumChanged(QString str);
	//��ѯ��ť�Ĵ�������
	void comboBoxPageChanged(QString str);
	void OnCbnSelchangeComboProdCode(QString str);
private:
	Ui::frmWTSearchDialog ui;
};
