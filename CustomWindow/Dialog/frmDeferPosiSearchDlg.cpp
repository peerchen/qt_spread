#include "frmDeferPosiSearchDlg.h"
#include "TraderCpMgr.h"
#include "HJConstant.h"
#include "Macrodefs.h"
#include "HJGlobalFun.h"
#include "frmOptionDlg.h"

frmDeferPosiSearchDlg::frmDeferPosiSearchDlg(QWidget *parent)
	: frmFramelessDialogBase(parent)
{
	ui.setupUi(this);


	m_list       = ui.tableView;
	m_cmbNum     = ui.comboBox_num;
	m_cmbPage    = ui.comboBox_page;
	m_tableModle = new QStandardItemModel();
	//setWidgetStyleFromQssFile(ui.tableView, _RES_STYLES_PATH + _MY_TEXT("DeepBlack\\Dialog.css"));

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

	//// ��ʼ����ѯ������combo
	//IniProdCode(*ui.comboBox_code);
	//IniExchCode(*ui.comboBox_type);
	//��ʼ����ѯ������combo
	IniProdCode(*ui.comboBox_code, "02");
	IniLongShort(*ui.comboBox__buysell);

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

	setFixedSize(1041, 451);
	ui.widget->setGeometry(0, 0, 1041, 351);
	setContent(ui.widget);
	setWindowTitle(QStringLiteral("�������ڳֲ���ϸ��ѯ"));

}

frmDeferPosiSearchDlg::~frmDeferPosiSearchDlg()
{
	g_TraderCpMgr.Unsubscribe(E_UPDATE_LIST, this);
}

void frmDeferPosiSearchDlg::OnBnClickedOption()
{
	frmOptionDlg dlg;
	dlg.selectTreeItem("16");
	dlg.exec();
}

void frmDeferPosiSearchDlg::OnBnClickedOutTExcel()
{
	OnOutputToExce(QStringLiteral("���ڳֲֲ�ѯ"));
}

void frmDeferPosiSearchDlg::comboBoxNumChanged(QString)
{
	OnSelchangeComboNum();
}


//��ѯ��ť�Ĵ�������
void frmDeferPosiSearchDlg::comboBoxPageChanged(QString str)
{
	OnBnClickedButtonQuery();
}

// ��Լ���������˵��Ĵ�����������Ӧ���ǽ������͵ı仯
void frmDeferPosiSearchDlg::OnCbnSelchangeComboProdCode(QString str)
{
	ProdCodeSelectChange(*ui.comboBox_code, *ui.comboBox__buysell);
}

//void frmWTSearchDialog::OnCbnSelchangeComboTypeCode()
//{
//	ProdCodeSelectChange(ui.comboBox_code, ui.comboBox_type);
//}

void frmDeferPosiSearchDlg::OnBnClickedButtonQuery()
{
	OnButtonQuery();
}

//��һҳ��ť�Ĵ�������
void frmDeferPosiSearchDlg::OnBnClickedButtonFirpage()
{
	OnButtonFirst();
}
//��һҳ��ť�Ĵ�������
void frmDeferPosiSearchDlg::OnBnClickedButtonPrepage()
{
	OnButtonPrev();
}

//��һҳ��ť�Ĵ�������
void frmDeferPosiSearchDlg::OnBnClickedButtonNexpage()
{
	OnButtonNext();
}

//���һҳ��ť�Ĵ�������
void frmDeferPosiSearchDlg::OnBnClickedButtonLaspage()
{
	OnButtonLast();
}

//�����Զ�����Ϣ
void frmDeferPosiSearchDlg::customEvent(QEvent * event)
{
	if (event->type() == WM_UPDATE_LIST)
	{
		ClearList();
		LoadList();
	}
}

string frmDeferPosiSearchDlg::GetQueryID()
{
	return "AcctDeferPosiDetail";
}

void frmDeferPosiSearchDlg::GetQueryPara(QVector< pair<QString, QString> >  &vecPara)
{
	PairAdd(vecPara, "prod_code", CHJGlobalFun::str2qstr(GetProdCode(*ui.comboBox_code))); //��Ӻ�Լ��������
	PairAdd(vecPara, "long_short", CHJGlobalFun::str2qstr(GetLongShort(*ui.comboBox__buysell))); //��ӽ�����������

}