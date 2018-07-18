#include "mainWindow.h"
#include <QtWidgets/QApplication>
#include  "myhelper.h"
#include "frmLoginDialog.h"
#include "AppInt.h"
#include "Startup.h"
#include "Global.h"





//ֱ������1�ֽڶ���ᱨ������Ҫ����ĵط���Э�̴ξ�
//#pragma pack(push, 1)  

//������룬������ʾ
#pragma execution_character_set("utf-8")

///����dump����ֹ�����������dump�ļ������ڷ���
#include  "minidump.h"
LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	     char creashFile[100];
	     getcwd(creashFile, 100);
	    strcat(creashFile, "\\CreatFile.dmp");
	    CreateMiniDump(pExceptionInfo, (LPCTSTR)creashFile);
	     return EXCEPTION_EXECUTE_HANDLER;
 }


int main(int argc, char *argv[])
{

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	QApplication a(argc, argv);

	//���������ڴ�,�ж��Ƿ��Ѿ����г���
	QSharedMemory mem("gessClient");
	if (!mem.create(1))
	{
		QMessageBox::warning(nullptr, "��ʾ", "�����Ѿ�������, ������Զ��ر�!");
		return 1;
	}


	qApp->setFont(QFont(App::AppFontName, App::AppFontSize));

	//QTextCodec::setCodecForLocale(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
	a.setWindowIcon(QIcon(":/res/App.png"));    //����Ӧ�ó���ͼ��
	a.setApplicationName("gessClient");         //����Ӧ�ó�������
	a.setApplicationVersion("V201712");			//����Ӧ�ó���汾
	//myHelper::SetUTF8Code();					//���ó������ΪUTF-8
	myHelper::SetChinese();						//���ó���Ϊ�����ֿ�

	//��ֵ��ǰӦ�ó���·���������ȸ߶�
	App::AppPath    = QApplication::applicationDirPath() + "/";
	App::DeskWidth  = qApp->desktop()->availableGeometry().width();
	App::DeskHeight = qApp->desktop()->availableGeometry().height();
	g_Global.m_strSystemPath = App::AppPath;
	g_Global.SetCommonPath();
	//�������ʱ�ȼ�������������Ϣ
	App::ReadConfig();

	//���غ�Ӧ����ʽ
	//myHelper::SetAppStyle(App::AppStyle);

	//��װ�¼����ˣ���Ҫ���á�CanMove���ԡ������ڼ�����������¼���ڣ����õ���
	AppInit *pInit = new AppInit();
	
	//��¼
	frmLoginDialog  *login = new frmLoginDialog();
	QStartup::GetInstance()->SetApplication(&a);
	QStartup::GetInstance()->SetLoginDlg(login);
	if (!QStartup::GetInstance()->Initialize())
		return 0;


	//pInit->installEventFilter(login);
	//login->show();

	//QStartup::GetInstance()->SetApplication(&a);
	//QStartup::GetInstance()->SetLoginDlg(login);
	//if (QStartup::GetInstance()->Initialize()/*&& login->exec() == QDialog::Accepted*/)//�ɹ���¼
	
	if(login->exec() == QDialog::Accepted)
	{
		QMessageBox *box = new QMessageBox(QMessageBox::Information, "��½��ʾ", "      ��½�ɹ���      ");
		box->setModal(false);
		box->setAttribute(Qt::WA_DeleteOnClose);
		QTimer::singleShot(5000, box, SLOT(accept()));
		box->exec();

		mainWindow   w;
		w.InitUI();
		w.InitAllData();
		pInit->installEventFilter(&w);

		w.show();
		//w.showMaximized();
		//w.setGeometry(qApp->desktop()->availableGeometry());
		return a.exec();
	}
	else
		return 0;

}
