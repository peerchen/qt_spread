#include "frmCapitalSearchDialog.h"
#include "TraderCpMgr.h"
#include "HJConstant.h"
#include "Macrodefs.h"
#include "HJGlobalFun.h"
#include <QDate>
#include <qdatetime.h>
#include "Global.h"
#include "frmOptionDlg.h"
frmCapitalSearchDialog::frmCapitalSearchDialog(QWidget *parent)
:frmFramelessDialogBase(parent)
{
	ui.setupUi(this);

	m_list    = ui.tableView;
	m_cmbNum   = ui.comboBox_num;
	m_cmbPage  = ui.comboBox_page;
	m_tableModle = new QStandardItemModel();
	//setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\dialog.css"));

	LoadList();

	ui.tableView->horizontalHeader()->setFixedHeight(32);
	ui.tableView->verticalHeader()->hide();
	ui.tableView->verticalHeader()->setDefaultSectionSize(30);
	ui.tableView->setShowGrid(false);
	ui.tableView->setSortingEnabled(false);
	ui.tableView->setAlternatingRowColors(true);//���л�ɫ
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	//tableModel->setSortRole(1);
	ui.tableView->setModel(m_tableModle);

	// ��ʼ��ҳ��
	InitPage();

	// ��ʼ��ÿҳ��Ŀ
	InitPageNum();


	ui.dateEdit_st->setDate(QDate::fromString(g_Global.m_strLast_Exch_Date,"yyyyMMdd"));
	ui.dateEdit_ed->setDate(QDate::fromString(g_Global.m_strLast_Exch_Date,"yyyyMMdd"));

	g_TraderCpMgr.Subscribe(E_UPDATE_LIST, this);

	setFixedSize(991, 481);
	ui.widget->resize(QSize(991, 381));
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("��ʷ�ʽ��ѯ"));

	connect(ui.pushButton_query, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonQuery()));
	connect(ui.pushButton_first, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonFirpage()));
	connect(ui.pushButton_pre, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonPrepage()));
	connect(ui.pushButton_next, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonNexpage()));
	connect(ui.pushButton_last, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonLaspage()));
	connect(ui.pushButton_output_excel, SIGNAL(clicked()), this, SLOT(OnBnClickedOutTExcel()));
	connect(ui.pushButton_option, SIGNAL(clicked()), this, SLOT(OnBnClickedOption()));

	connect(ui.comboBox_num, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboBoxNumChanged(QString)));
	connect(ui.comboBox_page, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboBoxPageChanged(QString)));
}

frmCapitalSearchDialog::~frmCapitalSearchDialog()
{
}

void frmCapitalSearchDialog::comboBoxNumChanged(QString)
{
	OnSelchangeComboNum();
}
void frmCapitalSearchDialog::OnBnClickedOption()
{
	frmOptionDlg dlg;
	dlg.selectTreeItem("23");
	dlg.exec();
}
void frmCapitalSearchDialog::OnBnClickedOutTExcel()
{
	OnOutputToExce(QStringLiteral("��ʷ�ʽ��ѯ"));
}

//��ѯ��ť�Ĵ�������
void frmCapitalSearchDialog::comboBoxPageChanged(QString str)
{
	OnBnClickedButtonQuery();
}

// ��Լ���������˵��Ĵ�����������Ӧ���ǽ������͵ı仯
//void frmCapitalSearchDialog::OnCbnSelchangeComboProdCode(QString str)
//{
//	ProdCodeSelectChange(*ui.comboBox_code, *ui.comboBox__buysell);
//}

//void frmWTSearchDialog::OnCbnSelchangeComboTypeCode()
//{
//	ProdCodeSelectChange(ui.comboBox_code, ui.comboBox_type);
//}

void frmCapitalSearchDialog::OnBnClickedButtonQuery()
{
	OnButtonQuery();
}

//��һҳ��ť�Ĵ�������
void frmCapitalSearchDialog::OnBnClickedButtonFirpage()
{
	OnButtonFirst();
}
//��һҳ��ť�Ĵ�������
void frmCapitalSearchDialog::OnBnClickedButtonPrepage()
{
	OnButtonPrev();
}

//��һҳ��ť�Ĵ�������
void frmCapitalSearchDialog::OnBnClickedButtonNexpage()
{
	OnButtonNext();
}

//���һҳ��ť�Ĵ�������
void frmCapitalSearchDialog::OnBnClickedButtonLaspage()
{
	OnButtonLast();
}

//�����Զ�����Ϣ
void frmCapitalSearchDialog::customEvent(QEvent * event)
{
	if (event->type() == WM_UPDATE_LIST)
	{
		ClearList();
		LoadList();
	}
}

string frmCapitalSearchDialog::GetQueryID()
{
	return "AcctFundHis";
}
void frmCapitalSearchDialog::GetQueryPara(QVector< pair<QString, QString> >  &vecPara)
{
	PairAdd(vecPara, "start_date", ui.dateEdit_st->date().toString("yyyyMMdd")); //��ӿ�ʼ���ڲ�ѯ������
	PairAdd(vecPara, "end_date", ui.dateEdit_ed->date().toString("yyyyMMdd"));    //��ӽ������ڲ�ѯ������

}