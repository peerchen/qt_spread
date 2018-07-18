#include "frmWTSearchDialog.h"
#include "TraderCpMgr.h"
#include "HJConstant.h"
#include "Macrodefs.h"
#include "HJGlobalFun.h"
#include "frmOptionDlg.h"


frmWTSearchDialog::frmWTSearchDialog(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);

	m_list       = ui.tableView;
	m_cmbNum     = ui.comboBox_num;
	m_cmbPage    = ui.comboBox_page;
	m_tableModle = new QStandardItemModel();
	//setWidgetStyleFromQssFile(this, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\dialog.css"));

	//setWindowFlags(Qt::CustomizeWindowHint);//���A
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

	// ��ʼ����ѯ������combo
	IniProdCode(*ui.comboBox_code);
	IniExchCode(*ui.comboBox_type);
	IniOffsetFlag(*ui.comboBox_KPFlag);

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
	connect(ui.comboBox_code, SIGNAL(currentIndexChanged(QString)), this, SLOT(OnCbnSelchangeComboProdCode(QString)));


	setFixedSize(1031, 480);
	ui.widget->setGeometry(0, 0, 1031, 380);
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("����ί���걨��ѯ"));
}

frmWTSearchDialog::~frmWTSearchDialog()
{

	g_TraderCpMgr.Unsubscribe(E_UPDATE_LIST, this);

}

void frmWTSearchDialog::comboBoxNumChanged(QString)
{
	OnSelchangeComboNum();
}


void frmWTSearchDialog::OnBnClickedOption()
{
	frmOptionDlg dlg;
	dlg.selectTreeItem("14");
	if (QDialog::Accepted == dlg.exec())
	{
		ClearList();
		LoadList();
	}
}


void frmWTSearchDialog::comboBoxPageChanged(QString str)
{
	OnBnClickedButtonQuery();
}

// ��Լ���������˵��Ĵ�����������Ӧ���ǽ������͵ı仯
void frmWTSearchDialog::OnCbnSelchangeComboProdCode(QString str)
{
	ProdCodeSelectChange(*ui.comboBox_code, *ui.comboBox_type);
}

//void frmWTSearchDialog::OnCbnSelchangeComboTypeCode()
//{
//	ProdCodeSelectChange(ui.comboBox_code, ui.comboBox_type);
//}

void frmWTSearchDialog::OnBnClickedButtonQuery()
{
	OnButtonQuery();
}

//��һҳ��ť�Ĵ�������
void frmWTSearchDialog::OnBnClickedButtonFirpage()
{
	OnButtonFirst();
}
//��һҳ��ť�Ĵ�������
void frmWTSearchDialog::OnBnClickedButtonPrepage()
{
	OnButtonPrev();
}

//��һҳ��ť�Ĵ�������
void frmWTSearchDialog::OnBnClickedButtonNexpage()
{
	OnButtonNext();
}

//���һҳ��ť�Ĵ�������
void frmWTSearchDialog::OnBnClickedButtonLaspage()
{
	OnButtonLast();
}


void frmWTSearchDialog::OnBnClickedOutTExcel()
{
	OnOutputToExce(QStringLiteral("ί���걨��ѯ"));
}

//�����Զ�����Ϣ
void frmWTSearchDialog::customEvent(QEvent * event)
{
	if (event->type() == WM_UPDATE_LIST)
	{
		ClearList();
		LoadList();
	}
}


string frmWTSearchDialog::GetQueryID()
{
	return "AcctEntrFlow";
}

void frmWTSearchDialog::GetQueryPara(QVector< pair<QString, QString> >  &vecPara)
{
	PairAdd(vecPara, "prod_code", CHJGlobalFun::str2qstr(GetProdCode(*ui.comboBox_code))); // ��Ӻ�Լ��������
	PairAdd(vecPara, "exch_code", GetExchCode(*ui.comboBox_type)); // ��ӽ�����������
	PairAdd(vecPara, "b_offset_flag", CHJGlobalFun::str2qstr(GetOffsetFlag(*ui.comboBox_KPFlag))); //��ӿ�ƽ��־
}