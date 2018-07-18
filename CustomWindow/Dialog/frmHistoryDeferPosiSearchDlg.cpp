#include "frmHistoryDeferPosiSearchDlg.h"
#include "TraderCpMgr.h"
#include "HJConstant.h"
#include "Macrodefs.h"
#include "HJGlobalFun.h"
#include <QDate>
#include <qdatetime.h>
#include "Global.h"
#include "frmOptionDlg.h"

frmHistoryDeferPosiSearchDlg::frmHistoryDeferPosiSearchDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);	
	
	m_list = ui.tableView;
	m_cmbNum = ui.comboBox_num;
	m_cmbPage = ui.comboBox_page;
	m_tableModle = new QStandardItemModel();
	//setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\dialog.css"));

	//setWindowFlags(Qt::WindowCloseButtonHint);//�����ر�
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

	//// ��ʼ����ѯ������combo
	//IniProdCode(*ui.comboBox_code);
	//IniExchCode(*ui.comboBox_type);
	//��ʼ����ѯ������combo
	IniProdCode(*ui.comboBox_code, "02");
	//IniLongShort(*ui.comboBox_buysell);

	ui.dateEdit_st->setDate(QDate::fromString(g_Global.m_strLast_Exch_Date,"yyyyMMdd"));
	ui.dateEdit_ed->setDate(QDate::fromString(g_Global.m_strLast_Exch_Date,"yyyyMMdd"));

	g_TraderCpMgr.Subscribe(E_UPDATE_LIST, this);

	connect(ui.pushButton_query, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonQuery()));
	connect(ui.pushButton_first, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonFirpage()));
	connect(ui.pushButton_pre, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonPrepage()));
	connect(ui.pushButton_next, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonNexpage()));
	connect(ui.pushButton_last, SIGNAL(clicked()), this, SLOT(OnBnClickedButtonLaspage()));
	connect(ui.pushButton_output_excel, SIGNAL(clicked()), this, SLOT(OnBnClickedOutTExcel()));
	connect(ui.pushButton_option, SIGNAL(clicked()), this, SLOT(OnBnClickedOption()));

	connect(ui.comboBox_num, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboBoxNumChanged(QString)));
	connect(ui.comboBox_page, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboBoxPageChanged(QString)));
	//connect(ui.comboBox_code, SIGNAL(currentIndexChanged(QString)), this, SLOT(OnCbnSelchangeComboProdCode(QString)));


	setFixedSize(1031, 490);
	ui.widget->setGeometry(0, 0, 1031, 390);
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("��ʷ���ڳֲֲ�ѯ"));
}

frmHistoryDeferPosiSearchDlg::~frmHistoryDeferPosiSearchDlg()
{
}

void frmHistoryDeferPosiSearchDlg::comboBoxNumChanged(QString)
{
	OnSelchangeComboNum();
}
void   frmHistoryDeferPosiSearchDlg::OnBnClickedOption()
{
	frmOptionDlg dlg;
	dlg.selectTreeItem("21");
	dlg.exec();
}

void frmHistoryDeferPosiSearchDlg::OnBnClickedOutTExcel()
{
	OnOutputToExce(QStringLiteral("��ʷ���ڳֲֲ�ѯ"));
}
//��ѯ��ť�Ĵ�������
void frmHistoryDeferPosiSearchDlg::comboBoxPageChanged(QString str)
{
	OnBnClickedButtonQuery();
}

//// ��Լ���������˵��Ĵ�����������Ӧ���ǽ������͵ı仯
//void frmHistoryDeferPosiSearchDlg::OnCbnSelchangeComboProdCode(QString str)
//{
//	ProdCodeSelectChange(*ui.comboBox_code, *ui.comboBox__buysell);
//}

//void frmWTSearchDialog::OnCbnSelchangeComboTypeCode()
//{
//	ProdCodeSelectChange(ui.comboBox_code, ui.comboBox_type);
//}

void frmHistoryDeferPosiSearchDlg::OnBnClickedButtonQuery()
{
	OnButtonQuery(ui.dateEdit_st->dateTime(),ui.dateEdit_ed->dateTime());
}

//��һҳ��ť�Ĵ�������
void frmHistoryDeferPosiSearchDlg::OnBnClickedButtonFirpage()
{
	OnButtonFirst();
}
//��һҳ��ť�Ĵ�������
void frmHistoryDeferPosiSearchDlg::OnBnClickedButtonPrepage()
{
	OnButtonPrev();
}

//��һҳ��ť�Ĵ�������
void frmHistoryDeferPosiSearchDlg::OnBnClickedButtonNexpage()
{
	OnButtonNext();
}

//���һҳ��ť�Ĵ�������
void frmHistoryDeferPosiSearchDlg::OnBnClickedButtonLaspage()
{
	OnButtonLast();
}

//�����Զ�����Ϣ
void frmHistoryDeferPosiSearchDlg::customEvent(QEvent * event)
{
	if (event->type() == WM_UPDATE_LIST)
	{
		ClearList();
		LoadList();
	}
}

string frmHistoryDeferPosiSearchDlg::GetQueryID()
{
	return "AcctDeferPosiHis";
}

void frmHistoryDeferPosiSearchDlg::GetQueryPara(QVector< pair<QString, QString> >  &vecPara)
{
	PairAdd(vecPara, "prod_code", CHJGlobalFun::str2qstr(GetProdCode(*ui.comboBox_code))); //��Ӻ�Լ��������
	//PairAdd(vecPara, "long_short", CHJGlobalFun::str2qstr(GetLongShort(*ui.comboBox__buysell))); //��ӽ�����������
	
	PairAdd(vecPara, "start_date", ui.dateEdit_st->date().toString("yyyyMMdd")); //��ӿ�ʼ���ڲ�ѯ������
	PairAdd(vecPara, "end_date", ui.dateEdit_ed->date().toString("yyyyMMdd"));    //��ӽ������ڲ�ѯ������


}