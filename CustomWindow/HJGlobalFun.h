#pragma once

#include <QVector>
#include <QString>
#include <QTime>
#include  <QCHAR>
#include <QNetworkInterface>
#include <QList>
#include <QHostAddress>
//using namespace std;

//#include "GuiGridCtrl.h"

#define QUERY_INI_SPLITER "��"
#define NEW_SPLITER "^"
#define LIST_INI_SPLITER "��"

typedef enum
{
	ROUND_HALF_UP  = 0,
	ROUND_UP,
} EDoubleFormatMode;

class CHJGlobalFun
{
public: // ����
	//
	//static void SetListCtrl(CGuiGridCtrl& listCtrl, int iItemHeight = 24);
	// ���list�ı��⣬�����ñ���Ŀ�ȺͶ��뷽ʽ
	//static void AddListColumn( CGuiGridCtrl& listCtrl, int iCount, QString* psTitle,int* piAlign, int* piWidth );

	//����INI�ļ�
	static void ReadUserChoose(const QString &csPath, const QString &csTitle, bool bName, QVector<QString> &vecUserNames);

	//
	static void GetIniValueToVector(const QString &csPath, const QString &csMainTitle, const QString &csTitle, const QString &csSplitter, const QString &csDefaulut, QVector<QString> &vecValue);
public:
	//
	static QString QStringToQString(QString &cstr);
	//
	static QString IntToQString(int iValue);

	// ��splitwordΪ�ָ��������ַ���str�е��ַ����ָ��vec;
	//static void SplitStrToVector( QString Str, QString SplitWord , QVector<QString> &Vec, bool bAddSplit = true, bool bRemoveBlank = true);

	// ��splitwordΪ�ָ��������ַ���str�е��ַ����ָ��vec;
	static void SplitStrToVector( QString &sOrg, const QString &sSplitter , QVector<QString> &Vec, bool bAddSplit = true, bool bRemoveBlank = true);

	static void SplitStrToVector( QString Str, QString SplitWord , QVector<int> &Vec, bool bAddSplit = true, bool bRemoveBlank = true);

	// ��ʽ�����������
	static QString FormatFloatQuote(QString strFloat, bool b45 = false); // ��ʽ������
	static QString FormatFloat(QString strFloat, bool b45 = false); // ��ʽ��������
	static QString DoubleToQString(double dValue, bool b45 = true);
	static bool CheckFloat(QString &sFloat);
	static QString DealKeXue(QString &strFloatALL, int iFindIndexE); // ����ƽ���������صĿ�ѧ��������ת��
	static QString Float45(QString &strZheng, QString &strXiao, int iReserve); // ������������������
	static int QStringXiaoAdd1(QString &strFloat); //

	// �ж�һ���ַ����Ƿ�ȫ�������������
	static bool IsNumber(const QString &sNum); 

	// ���ܣ���ȡDatetimepicker�ؼ���ʱ�䣬��ת��Ϊ"20100201"��ʽ���ַ���
	//static QString GetFormatTimeStr(CDateTimeCtrl &dtctrl);

	// ��ʽ�������ַ�����ʹ��Ϊ1980-02-01�ĸ�ʽ
	static QString FormatDate( QString sDateOrg );

	// ��ʽ��ʱ���ַ�������ʽ��ʱ��Ϊ12:06:01����ʽ
	static QString FormatTime( QString sTimeOrg );

	// ��һ�������ַ���ת����CTime����
	static QTime TranslateDateStrToCTime(QString sDate);
	static QTime TranslateDateStrToCTime( const QString &sDate);

	// ������������ID��ȡ������������
	static QString GetBuySellName(const QString &sID);

	//static void PairAdd(QQVector< QPair<QString,QString> > & v, QString sTitle, QString sValue);

	static bool IsDoubleZero(double dValue);


	static double DoubleFormat(double dValue, int iScale = 2, EDoubleFormatMode eMode = ROUND_HALF_UP);

    static double DoubleFormatNoNine(double dValue, int iScale = 2);

	static int DoubleToInt(double dValue);

	static bool IsContinuousNumber(const QString &sNum);

	static bool IsHasContinuousSameWord(const QString &sNum, int iCount);

	static int CompareDouble(double dValue1, double dValue2);

	// �ж�һ���ַ����Ƿ������䣨���䣩
	static bool IsEmail(const QString &strValue);

	// �ж�һ���ַ����Ƿ�����ϵ�绰�����棬�绰���룩
	static bool IsPhone(const QString &strValue);

	// ����nCountλ�������
	static std::string GetRandNumber( short nCount );

	static QString GetCurTimeFormat();

	static QString GetCurDateFormat();

	static bool RunFileExe( const QString &csFullPath );

	//static bool RunCreateProcess( const LPSTR pPath );

	//static bool RunShellExecute( const char* pPath, const char* pPara = "" );
	static QString getHostIpAddress();

	static QString str2qstr(const std::string& str);
	static std::string qstr2str(const QString & qstr);






};






