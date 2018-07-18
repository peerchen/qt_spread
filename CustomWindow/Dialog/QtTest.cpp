#include "QtTest.h"
#include <QFontDatabase>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QMenuBar>

QtTest::QtTest(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	setupTree();

	ui.treeWidget->setItemSelected(ui.treeWidget->topLevelItem(0), true);


	//��Ӳ��Բ˵�
	menu[0] = new QMenu("�ļ�");
	menu[0]->addAction("�༭");
	menu[0]->addAction("�鿴");
	menu[0]->addAction("����");

	act[0] = new QAction("�½�", this);
	act[0]->setShortcut(Qt::CTRL | Qt::Key_A);
	act[0]->setStatusTip("����һ���½��˵�");

	act[1] = new QAction("��", this);
	act[1]->setCheckable(true);

	menu[1] = new QMenu("����");
	menu[1]->addAction(act[0]);
	menu[1]->addAction(act[1]);

	menu[2] = new QMenu("��ӡ");
	menu[2]->addAction("��ӡ����");
	menu[2]->addMenu(menu[1]);


	menuBar = new QMenuBar(this);
	menuBar->addMenu(menu[0]);
	menuBar->addMenu(menu[2]);
	menuBar->setGeometry(0, 0, this->width(), 30);

}

QtTest::~QtTest()
{
}

void QtTest::setupTree()
{
	QFontDatabase database;
	ui.treeWidget->setColumnCount(1);
	ui.treeWidget->setHeaderLabels(QStringList() << tr("Font"));

	foreach(QString family, database.families()) {
		const QStringList styles = database.styles(family);
		if (styles.isEmpty())
			continue;

		QTreeWidgetItem *familyItem = new QTreeWidgetItem(ui.treeWidget);
		familyItem->setText(0, family);
		familyItem->setCheckState(0, Qt::Unchecked);
		familyItem->setFlags(familyItem->flags() | Qt::ItemIsAutoTristate);

		foreach(QString style, styles) {
			QTreeWidgetItem *styleItem = new QTreeWidgetItem(familyItem);
			styleItem->setText(0, style);
			styleItem->setCheckState(0, Qt::Unchecked);
			styleItem->setData(0, Qt::UserRole, QVariant(database.weight(family, style)));
			styleItem->setData(0, Qt::UserRole + 1, QVariant(database.italic(family, style)));
		}
	}
}