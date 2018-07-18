#include "HJGlobalFun.h"

#include <sstream> // Ӧ��QStringstream��Ҫ�������ļ�
#include <cmath>

#include <time.h>
#include <app.h>




#pragma execution_character_set("utf-8")


//// �����б����
//void CHJGlobalFun::SetListCtrl( CGuiGridCtrl& listCtrl, int iItemHeight )
//{
//	listCtrl.SetTextFormat(DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
//	listCtrl.SetItemHeight(iItemHeight);
//    listCtrl.SetEvenColor(RGB(255, 255, 255));
//    listCtrl.SetOddColor(RGB(0xff, 0xff, 0xe0));
//    listCtrl.SetSelectedColor(RGB(0xc0, 0xf0, 0xec));
//    listCtrl.SetBorderColor(RGB(0xff, 0xff, 0xff));
//	((CGuiGridHeaderCtrl*)listCtrl.GetHeaderCtrl())->SetTextColor(RGB(0, 0, 0));
//	((CGuiGridHeaderCtrl*)listCtrl.GetHeaderCtrl())->SetBkgndColor(RGB(0xf0, 0xf3, 0xf5));
//	((CGuiGridHeaderCtrl*)listCtrl.GetHeaderCtrl())->SetSplitterColor(RGB(0xa9, 0xa9, 0xa9));
//}
//// ���list�ı��⣬�����ñ���Ŀ�ȺͶ��뷽ʽ
//void CHJGlobalFun::AddListColumn( CGuiGridCtrl& listCtrl, int iCount, QString* psTitle,int* piAlign, int* piWidth )
//{
//	for(int i = 0; i < iCount; i++)
//	{
//		listCtrl.InsertColumn(i, *psTitle++, *piAlign++, *piWidth++);
//	}
//}
bool CHJGlobalFun::CheckFloat(QString &sFloat)
{
	int iLen = sFloat.length();
	if(iLen != 0)
	{
		QChar ch;
		bool bHasPoint = false;
		for(int i = 0; i < iLen; i++)
		{
			ch = sFloat.at(i);
			if(ch < '0' || ch > '9') // �����������
			{
				if(ch == '-' && i == 0 && iLen > 1) // ����Ǹ��ţ������ǵ�һ���������ַ������ȴ���1����ͨ��
				{
					continue;
				}
				else if(ch == '.' && !bHasPoint) // �����С���㣬���һ�û���ֹ�
				{
					// ����С��λ��λ�����жϣ�������������͹�����".11"�Ĵ���
					bHasPoint = true;
					continue;

					/*bHasPoint = true;
					if(i == 0 || i == iLen -1)
					{
						return false;
					}
					else
					{
						continue;
					}*/
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;

}
// ��ʽ��������������˶Իƽ��������ݵķ�֧����
QString CHJGlobalFun::FormatFloat( QString strFloat, bool b45 /*= true */ )
{
	/*
	// �մ���
	if(strFloat == "" || strFloat == "-")//���Ϊ�գ��򷵻ؿ�
	{
		if(bQuotation)
		{
			return "0.00";
		}
		else
		{
			return strFloat;
			//return "";
		}
	}
	*/

	// ��ѧ�����������еı�����������ʽ
	int iFindIndexE = strFloat.indexOf('E');
	if(iFindIndexE != -1)
	{
		return FormatFloat(DealKeXue(strFloat, iFindIndexE));
	}

	// ������Ϸ�����ֱ�ӷ���
	if(!CheckFloat(strFloat))
	{
		return strFloat;
	}

	QString zheng,xiao,temp;
	int index;

	QString cstr = strFloat;//ת����QString���ͣ�Ϊ�˷��㴦��

	//����λ�������Ϊ��������Ϊ�գ����Ϊ�����������ʱ��ȥ����������������
	QString fuhao = "";
	if(cstr.at(0) == '-')//���Ϊ����
	{
		//ȥ�����ţ���¼����
		cstr = cstr.mid(1);
		fuhao = "-";
	}

	int len = cstr.length();//��ó���
	index =  cstr.indexOf(".");//���С����λ��

	//����С������
	if(index == -1)//���Ϊ���������ں������Ĭ��С��λ"00"
	{
		xiao = "00";
	}
	else//���ΪС��
	{
		xiao = cstr.mid(index + 1);//��ȡС������
		if(len - index == 2)//���ΪһλС��������һ��0��Ҫ��Ҫ����ֻ��С���㣬û��С��λ�ģ�
		{
			xiao += "0";
		}	
		else if(len - index >= 4)
		{
			// ���С��λ����3λ�����ȡ2λ
			if(b45)
			{
				cstr = Float45(QStringToQString(cstr.left(index)), QStringToQString(xiao), 2);
				// ���ڴ���������������ֿ��ܴ��ڱ仯�������²���
				index =  cstr.indexOf(".");//���С����λ��
				xiao = cstr.mid(index + 1);//��ȡС������
			}
			else
			{
				xiao = xiao.left(2);
			}
		}
	}

	//�����������֣�temp������¼��������
	if(index == -1)
	{
		temp = cstr;
	}
	else
	{
		temp = cstr.left(index);//��������
		if(temp == "")//�����������Ϊ�յĻ�������-.23���������
		{
			return fuhao + "0." + xiao;
		}
		len  = index;//��¼�������ֵĳ��ȵ�len
	}

	//���ǧλ�ָ���
	int count = -1;
	if(len % 3 != 0)//�����Ϊ3����
		count++;
	count = len/3 + count;
	zheng = temp.left(len - 3*count);
	while(count)
	{
		zheng += "," + temp.mid(len - 3*count, 3);
		count--;
	}
	return fuhao + zheng + "." + xiao;
}



// ��ʽ��������������˶Իƽ��������ݵķ�֧����
QString CHJGlobalFun::FormatFloatQuote(QString strFloat, bool b45 /*= true */)
{
	/*
	// �մ���
	if(strFloat == "" || strFloat == "-")//���Ϊ�գ��򷵻ؿ�
	{
	if(bQuotation)
	{
	return "0.00";
	}
	else
	{
	return strFloat;
	//return "";
	}
	}
	*/

	// ��ѧ�����������еı�����������ʽ
	int iFindIndexE = strFloat.indexOf('E');
	if (iFindIndexE != -1)
	{
		return FormatFloat(DealKeXue(strFloat, iFindIndexE));
	}

	// ������Ϸ�����ֱ�ӷ���
	if (!CheckFloat(strFloat))
	{
		return strFloat;
	}

	QString zheng, xiao, temp;
	int index;

	QString cstr = strFloat;//ת����QString���ͣ�Ϊ�˷��㴦��

							//����λ�������Ϊ��������Ϊ�գ����Ϊ�����������ʱ��ȥ����������������
	QString fuhao = "";
	if (cstr.at(0) == '-')//���Ϊ����
	{
		//ȥ�����ţ���¼����
		cstr = cstr.mid(1);
		fuhao = "-";
	}

	int len = cstr.length();//��ó���
	index = cstr.indexOf(".");//���С����λ��

							  //����С������
	if (index == -1)//���Ϊ���������ں������Ĭ��С��λ"00"
	{
		xiao = "00";
	}
	else//���ΪС��
	{
		xiao = cstr.mid(index + 1);//��ȡС������
		if (len - index == 2)//���ΪһλС��������һ��0��Ҫ��Ҫ����ֻ��С���㣬û��С��λ�ģ�
		{
			xiao += "0";
		}
		else if (len - index >= 4)
		{
			// ���С��λ����3λ�����ȡ2λ
			if (b45)
			{
				cstr = Float45(QStringToQString(cstr.left(index)), QStringToQString(xiao), 2);
				// ���ڴ���������������ֿ��ܴ��ڱ仯�������²���
				index = cstr.indexOf(".");//���С����λ��
				xiao = cstr.mid(index + 1);//��ȡС������
			}
			else
			{
				xiao = xiao.left(2);
			}
		}
	}

	//�����������֣�temp������¼��������
	if (index == -1)
	{
		temp = cstr;
	}
	else
	{
		temp = cstr.left(index);//��������
		if (temp == "")//�����������Ϊ�յĻ�������-.23���������
		{
			return fuhao + "0." + xiao;
		}
		len = index;//��¼�������ֵĳ��ȵ�len
	}

	//���ǧλ�ָ���
	//int count = -1;
	//if (len % 3 != 0)//�����Ϊ3����
	//	count++;
	//count = len / 3 + count;
	//zheng = temp.left(len - 3 * count);
	//while (count)
	//{
	//	zheng += "," + temp.mid(len - 3 * count, 3);
	//	count--;
	//}

	zheng = temp;
	return fuhao + zheng + "." + xiao;
}



QString CHJGlobalFun::DoubleToQString( double dValue, bool b45 /*= true*/ )
{
	//QStringstream   ss;   
	//ss << dValue;
	//return ss.str();

	if(b45) // ��������
	{
		// ��������98705.144999999990��������Ϊ98705.15�����ַ�ʽ��ʽΪ
		if( dValue > 0.0045 )
		{
			dValue += 0.005;
		}
		else
		{
			dValue -= 0.005;
		}
	}

	// �������ﲻ�����ݽ�����������
	if(dValue > -0.01 && dValue < 0.01)
	{
		dValue = 0.00;
	}

	QString sValue;
	char cTmp[64];
	sprintf(cTmp, "%f",dValue);
	sValue = cTmp;
	return sValue;
}

// ����ƽ���������صĿ�ѧ��������ת��
QString CHJGlobalFun::DealKeXue( QString &strFloatALL, int iFindIndexE )
{
#ifdef _VERSION_JH
	// ���а汾 "0E-10"
	int iWei;
	int iZheng;

	// ��ó���10�ĸ�����Ҳ����E���������
	int iLen = strFloatALL.length();
	QString strWei   = strFloatALL.substr(iFindIndexE+1, iLen-iFindIndexE);
	QStringstream ss(strWei); 
	ss >> iWei; 

	// ����������֣�����ѧ������Eǰ������֣�
	QStringstream ss2(strFloatALL.substr(0, iFindIndexE)); 
	ss2 >> iZheng;
	double dValue = pow((double)10, (double)iWei);

	// ���ԭʼ������
	dValue *= iZheng;

	// ת��Ϊ�ַ���
	QStringstream ss3;
	ss3 << dValue;
	return ss3.str();
#else
	QString strZheng;
	QString strXiao;
	int iWei=0;
	QString strWei;

	int iLen = strFloatALL.length();

	//����10�ĸ���
	strWei   = strFloatALL.mid(iFindIndexE+1, iLen-iFindIndexE);
	/*QStringstream ss(strWei); 
	ss >> iWei; */

	//��û�ԭ����������ֺ�С������
	int iFindIndexD = strFloatALL.indexOf('.');
	int nXiaoBegin = iFindIndexD+1+iWei; // ��ȡС��λ�Ŀ�ʼλ��
	if( nXiaoBegin < iFindIndexE ) // ���û��С��λ��������磺"1.0E7"
	{
		strZheng = strFloatALL.mid(0, iFindIndexD) + strFloatALL.mid(iFindIndexD+1, iWei);
	}
	else
	{
		strZheng = strFloatALL.mid(0, iFindIndexD) + strFloatALL.mid(iFindIndexD+1, iFindIndexE-iFindIndexD-1);
		strZheng.insert(nXiaoBegin-iFindIndexE, '0');
	}
		

#ifdef _VERSION_GF
	/*
	 �������ͨ������ԭʼ����9.89709008E7չʾΪ��9.8970900.8F��������
	*/
	
	// �ж��Ƿ񳬹�E��λ��
	if( nXiaoBegin < iFindIndexE )
		strXiao  = strFloatALL.substr(nXiaoBegin, iFindIndexE-nXiaoBegin);
	else
		strXiao = "00";
	
	return strZheng + "." + strXiao;
#else
	strXiao  = strFloatALL.mid(iFindIndexD+1+iWei, iFindIndexE-iFindIndexD-1);
	return Float45(strZheng, strXiao, 2);
#endif
	
#endif
}
//����iReserveλС����ʵ�־�ȷ�����һλ
QString CHJGlobalFun::Float45( QString &strZheng, QString &strXiao, int iReserve )
{
	char   cTemp;
	QString strXiaoF;
	int    izhengF;

	////����������ת��Ϊint��
	//QStringstream ss1(strZheng); 
	//ss1 >> izhengF; 
	//int iXiaoLen = strXiao.length();

	////��ñ���λ��Χ�ڵ�С�����ֵ��ַ���
	//strXiaoF = strXiao.substr(0, iReserve);

	////����С��������iReserveλ���һ������4��λ��
	//int iCount = iReserve;
	//cTemp = strXiao.at(iCount);
	//while(cTemp == '4' && iCount < iXiaoLen-1)
	//{
	//	iCount++;
	//	cTemp = strXiao.at(iCount);
	//}

	////��������ַ�������4����
	//if(cTemp > '4')
	//{
	//	izhengF += QStringXiaoAdd1(strXiaoF);
	//}

	//QStringstream ss;
	//ss << izhengF;
	//QString strFinal = ss.str();
	//strFinal += "." + strXiaoF;

	//return strFinal;
	return 1;
}
/*
��С�����ּ�1������н�λ�������Ļ����򷵻�1�����򷵻�0
���磺strFloat = "4445"��ִ�к�strFloatΪ"4446"
*/
int CHJGlobalFun::QStringXiaoAdd1( QString &strFloat )
{
	int  iLen    = strFloat.length();
	int  iCount  = iLen -1;
	int  iReturn = 0;

	//�ҵ����ұ߿�ʼ��һ������9���������ҽ���֮ǰ��ȫ����Ϊ0������"8999"�����Ϊ"9000"
	QChar cTemp  = strFloat.at(iCount);
	while(cTemp == '9' && iCount > 0)
	{
		// ��Ϊ9��������0����Ϊ��1��
		strFloat[iCount] = '0'; //����λ��0
		iCount--;
		cTemp = strFloat.at(iCount);
	}

	//����ǵ�0������cTemp��9���򷵻�ֵΪ1������Ϊ0
	if(iCount == 0 && cTemp == '9')
	{
		strFloat[iCount]= '0';
		iReturn++;	
	}
	else//�ַ�����1
	{
		//cTemp++;
		strFloat[iCount] = cTemp;
	}

	return iReturn;
}
// 
QString CHJGlobalFun::QStringToQString( QString &cstr )
{
	QString str(cstr.data()); //QString to QString
	cstr.clear();
	return str;
}


// ��ԭʼ�ַ���Str�Էָ��ַ���SplitWord�ָVector(Vec)����
//void CHJGlobalFun::SplitStrToVector( QString Str, QString SplitWord , QVector<QString> &Vec, bool bAddSplit /*= true*/, bool bRemoveBlank /*= true*/ )
//{
//	int index; // ��¼�ַ�����һ���ָ�����λ��
//	QString temp;
//	int iSplitterLen = SplitWord.length();
//
//	if(bAddSplit)
//	{
//		Str += SplitWord; // ��ӷָ������Ȼ������©�����һ��������ԭʼ���ַ������ַ���û�����������ӷָ���
//	}
//	
//	index = Str.indexOf(SplitWord);
//	while(index != -1)
//	{
//		// ��÷ָ���֮ǰ���ַ�������Ŀ���ַ���
//		temp = Str.left(index);
//
//		// �������Ҫȥ���ո� ���� �ַ�����Ϊ��
//		if(!bRemoveBlank || temp != "")
//		{
//			Vec.push_back(temp);
//		}
//
//		// ��÷ָ�������ַ�������Ϊ�µĴ����ַ���
//		Str   = Str.mid(index + iSplitterLen);
//
//		// ����µ��ַ����ĵ�һ���ָ�����λ��
//		index = Str.indexOf(SplitWord);
//	}
//}

void CHJGlobalFun::SplitStrToVector( QString Str, QString SplitWord , QVector<int> &Vec, bool bAddSplit /*= true*/, bool bRemoveBlank /*= true*/ )
{
	int index; // ��¼�ַ�����һ���ָ�����λ��
	QString temp;
	int iSplitterLen = SplitWord.length();

	if(bAddSplit)
	{
		Str += SplitWord; // ��ӷָ������Ȼ������©�����һ��������ԭʼ���ַ������ַ���û�����������ӷָ���
	}

	index = Str.indexOf(SplitWord);
	while(index != -1)
	{
		temp = Str.left(index);
		if(!bRemoveBlank || temp != "")
		{
			int iValue = temp.toInt();
			Vec.push_back(iValue);
		}

		Str   = Str.mid(index + iSplitterLen); //ע��SplitWord���ַ����Ļ���Ҫ����������ַ����ĳ���
		index = Str.indexOf(SplitWord);
	}

}

void CHJGlobalFun::SplitStrToVector( QString &sOrg, const QString &sSplitter , QVector<QString> &Vec, bool bAddSplit /*= true*/, bool bRemoveBlank /*= true*/ )
{
	int index; // ��¼�ַ�����һ���ָ�����λ��
	QString temp;

	int iSplitterLen = sSplitter.length();

	if(bAddSplit)
	{
		sOrg += sSplitter; // ��ӷָ������Ȼ������©�����һ��������ԭʼ���ַ������ַ���û�����������ӷָ���
	}

	index = sOrg.indexOf(sSplitter);
	while(index != -1)
	{
		temp = sOrg.mid(0, index);
		if( !bRemoveBlank || !temp.isEmpty() )
		{
			Vec.push_back(temp);
		}

		sOrg   = sOrg.mid(index + iSplitterLen); //ע��SplitWord���ַ����Ļ���Ҫ����������ַ����ĳ���
		index = sOrg.indexOf(sSplitter);
	}
}

// �ж�һ���ַ����Ƿ�ȫ�������������
bool CHJGlobalFun::IsNumber( const QString &sNum )
{
	// �ж��Ƿ�������
	for(int i = 0; i < sNum.length(); i++)
	{
		// ����0-9�����ֶ�Ӧһ����Χ��*��
		QChar mychar = sNum.at(i);// ��ȡQStringĳһ��λ���ϵ��ַ�
		if(mychar < 48 || mychar > 57) // �ж��Ƿ���0-9֮��
			return false;
	}

	return true;
}
// ���ܣ���ȡDatetimepicker�ؼ���ʱ�䣬��ת��Ϊ"20100201"��ʽ���ַ���
//QString CHJGlobalFun::GetFormatTimeStr( CDateTimeCtrl &dtctrl )
//{
//	CTime tt;
//	dtctrl.GetTime(tt);
//	return tt.Format("%Y%m%d");
//}
/*
��ʽ��ʱ���ַ�����ʹ��Ϊ1980-02-01�ĸ�ʽ
input��value�����Ǳ�׼�ĸ�ʽ��ʽ19800201
return��1980-02-01�ĸ�ʽ
*/
QString CHJGlobalFun::FormatDate( QString sDateOrg )
{
	if(sDateOrg.length() == 8)
		sDateOrg = sDateOrg.mid(0, 4) + "-"+ sDateOrg.mid(4, 2) + "-" + sDateOrg.mid(6, 2);

	return sDateOrg;
}
// ��ʽ�������ַ���������ʽΪ120601����ʽ��ʽ��Ϊ12:06:01����ʽ
QString CHJGlobalFun::FormatTime( QString sTimeOrg )
{
	if(sTimeOrg.length() == 6)
		sTimeOrg = sTimeOrg.mid(0, 2) + ":" + sTimeOrg.mid(2, 2) +  ":" + sTimeOrg.mid(4, 2);

	return sTimeOrg;
}
// ��һ�������ַ���ת����CTime����
QTime CHJGlobalFun::TranslateDateStrToCTime( QString sDate )
{
	QString cstrDate = sDate;
	if(cstrDate.length() != 8)
	{
		return QTime(0,0);
	}
	else
	{
		QTime timeTime;//(cstrDate.left(4).toInt(), atoi(cstrDate.mid(4, 2)), atoi(cstrDate.mid(6, 2)), 0, 0, 0);
		return timeTime;
	}
}

QTime CHJGlobalFun::TranslateDateStrToCTime( const QString &sDate )
{
	if(sDate.length() != 8)
	{
		return QTime(0,0,0,0);//("yyyy-MM-dd hh:mm:ss ddd"));
	}
	else
	{
		QTime timeTime;
		//timeTime.fromString()
		//(sDate.left(4).toInt(), sDate.mid(4, 2).toInt(), sDate.mid(6, 2).toInt(), 0, 0, 0);
		//timeTime.
		return timeTime;
	}
}

// ������������ID��ȡ������������
QString CHJGlobalFun::GetBuySellName( const QString &sID )
{
	if(sID == "s")
	{
		return "��";
	}
	else if(sID == "b")
	{
		return "��";
	}
	return sID;
}

QString CHJGlobalFun::IntToQString( int iValue )
{
	QString cstr= QString::number(iValue);
	//cstr.Format("%d", iValue);
	return cstr;
}

//void CHJGlobalFun::PairAdd( QVector< QPair<QString,QString> > & v, QString sTitle, QString sValue )
//{
//	QPair<QString,QString> p;
//	p.first  = sTitle;
//	p.second = sValue;
//	v.push_back(p);
//}

bool CHJGlobalFun::IsDoubleZero( double dValue )
{
	return dValue-0.0 < 1e-6 ? true : false;
}

// ��ʽ��
double CHJGlobalFun::DoubleFormat( double dValue, int iScale /*= 2*/, EDoubleFormatMode eMode /*= ROUND_HALF_UP*/ )
{
	// �쳣�򷵻�ԭֵ
	if(iScale < 0)
	{
		return dValue;
	}

	// ����dValue = 100.45434��iScale = 2 ����ROUND_HALF_UP����iFactor=1000��UINT64 u64 = (UINT64)(dValue * iFactor) + 5 = 100459��u64 = u64 / 10=10045��
	int iFactor = 10;
	while(iScale-- > 0)
	{
		iFactor *= 10;
	}

	quint64 u64 = (quint64)(dValue * iFactor);

	bool bInvert = false;
	if(u64 < 0)
	{
		bInvert = true;
		u64 = -u64;
	}

	if(eMode ==  ROUND_HALF_UP)
	{
		u64 += 5;
	}
	else // ROUND_UP
	{
		u64 += 9;
	}

	// ȥ���������ֵ����һλ
	u64 = u64 / 10;

	if(bInvert) u64 = -u64;

	return (double)u64 / (iFactor/10);
}

double CHJGlobalFun::DoubleFormatNoNine(double dValue, int iScale)
{
    // �쳣�򷵻�ԭֵ
    if(iScale < 0)
    {
        return dValue;
    }

    // ����dValue = 100.45434��iScale = 2 ����ROUND_HALF_UP����iFactor=1000��UINT64 u64 = (UINT64)(dValue * iFactor) + 5 = 100459��u64 = u64 / 10=10045��
    int iFactor = 10;
    while(iScale-- > 0)
    {
        iFactor *= 10;
    }

    quint64 u64 = (quint64)(dValue * iFactor);

    bool bInvert = false;
    if(u64 < 0)
    {
        bInvert = true;
        u64 = -u64;
    }

    int n = u64%10;
    if (n < 9 && n >= 5)
    {
        dValue += 0.005;
    }

    return dValue;
}

int CHJGlobalFun::DoubleToInt( double dValue )
{
	return (int)(dValue + 0.5);
}

// �ж�һ���ַ����Ƿ���������
bool CHJGlobalFun::IsContinuousNumber( const QString &sNum )
{
	int iLen = sNum.length()-1;

	// ���С��2λ������Ϊ������
	if(iLen < 1)
		return false;

	if(sNum.at(iLen) > sNum.at(0)) // ������һλ�ȵ�һλ������Ϊ���ܵĵ���
	{
		for(int i = 0; i < iLen; i++)
		{
			// ��ǰλ������Ⱥ���λС1����Ϊ����
			if(sNum.at(i)+1 != sNum.at(i+1))
				return false;
		}
	}
	else
	{
		for(int i = iLen; i > 0; i--)
		{
			if(sNum.at(i)+1 != sNum.at(i-1))
				return false;
		}
	}

	return true;
}

// �ж�һ���ַ����Ƿ���iCount����������ͬ�ַ�
bool CHJGlobalFun::IsHasContinuousSameWord( const QString &sNum, int iCount )
{
	if(sNum.length() < iCount)
		return false;

	int iFinalCount = 1;
	for(int i = 0; i < sNum.length()-1; i++)
	{
		// 
		if(sNum.at(i+1) == sNum.at(i))
		{
			iFinalCount++;

			if(iFinalCount >= iCount)
			{
				return true;
			}
		}
		else
		{
			iFinalCount=1;
		}	
	}

	return false;
}

int CHJGlobalFun::CompareDouble( double dValue1, double dValue2 )
{
	double dDif = fabs(dValue1 - dValue2);
	double dMinCom = 0.000001;

	if(dDif < dMinCom || dDif == dMinCom)
	{
		return 0;
	}
	else
	{
		return (dValue1 - dValue2 > 0.001) ? 1 : -1;
	}
}

bool CHJGlobalFun::IsEmail( const QString &strValue )
{
	//// �ж��Ƿ�Ϊ��
	//if(strValue.IsEmpty())
	//{
	//	return true;
	//}

	int iPos = strValue.indexOf("@");
	if(iPos == -1)
	{
		return false;
	}
	else
	{
		// �ж��Ƿ�������@
		int iPos2 = strValue.indexOf("@", iPos+1);
		if(iPos2 != -1)
		{
			return false;
		}
	}

	int iLen = strValue.length();

	// �ж�"@"�Ƿ��ڵ�һλ�������һλ
	if(iPos == 0 || iPos == iLen-1)
	{
		return false;
	}

	return true;
}

bool CHJGlobalFun::IsPhone( const QString &strValue )
{
	//// �ж��Ƿ�Ϊ��
	//if(strValue == "")
	//{
	//	return true;
	//}

	// �ж��Ƿ������ֻ���"-"��
	for( int i = 0; i < strValue.length(); i++ )
	{
		QChar cData = strValue.at(i);

		if(cData != '-')
		{
			if( cData < '0' || cData > '9' )
			{
				return false;
			}
		}
	}

	return true;
}

std::string CHJGlobalFun::GetRandNumber( short nCount )
{
	srand((unsigned int)time(NULL));

	// ��ȡ7λ�������
	unsigned int iFinalValue = 0;
	unsigned int iTemp = 1;
	for( short i = 0; i < nCount; i++ )
	{
		iFinalValue += rand()%(10)*iTemp;
		iTemp *= 10;
	}

	std::stringstream ss;
	ss << iFinalValue;
	return ss.str(); 
	//return "";
}

//2016.05.20 12:17:01.445 ����
//yyyy��ʾ�ꣻMM��ʾ�£�dd��ʾ�գ� hh��ʾСʱ��mm��ʾ�֣�ss��ʾ�룻zzz��ʾ���룻ddd��ʾ�ܼ�
QString CHJGlobalFun::GetCurTimeFormat()
{
	// ��õ�ǰʱ�䣬���Ҹ�ʽ��
	QDateTime current_date_time = QDateTime::currentDateTime();
	//QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
	QString current_time = current_date_time.time().toString("hh:mm:ss");

	return current_time;
	/*SYSTEMTIME st;
	GetLocalTime(&st);
	QString csTime;
	csTime.Format("%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	return csTime.GetBuffer();
	return  "";*/
}

QString CHJGlobalFun::GetCurDateFormat()
{
	//// ��õ�ǰʱ�䣬���Ҹ�ʽ��
	//SYSTEMTIME st;
	//GetLocalTime(&st);
	//QString csTime;
	//csTime.Format("%04d%02d%02d", st.wYear, st.wMonth, st.wDay);

	//return csTime.GetBuffer();
	return "";
}

/*
����exe�ļ���Ŀ¼����һ��exe�ļ�
input��fileName�ļ�������·��
return�������ɹ�����true������ʧ�ܷ���false
*/
bool CHJGlobalFun::RunFileExe( const QString &csFullPath )
{
	//QString csTemp(csFullPath);
	//// ���������������̵ķ�ʽ�������ĳ�ֻ�������������ʧ�ܵ�����
	//if( !RunCreateProcess(csTemp.GetBuffer()) )
	//{
	//	QString csExePath;
	//	QString csPara;
	//	int nPos = csFullPath.Find(" ");
	//	if( nPos != -1 )
	//	{
	//		csExePath = csFullPath.Left(nPos);
	//		csPara = csFullPath.mid(nPos+1);
	//	}
	//	else
	//	{
	//		csExePath = csFullPath;
	//	}

	//	ShellExecute( NULL, "open", csExePath, csPara, NULL, NULL );
	//}

	return true;
}

//bool CHJGlobalFun::RunCreateProcess( const LPSTR pPath )
//{
//	PROCESS_INFORMATION piProcInfo;
//
//	STARTUPINFO Info;
//	Info.cb          = sizeof(STARTUPINFO);
//	Info.lpReserved  = NULL;
//	Info.lpDesktop   = NULL;
//	Info.lpTitle     = NULL;
//	Info.cbReserved2 = 0;
//	Info.lpReserved2 = NULL;
//
//	BOOL bSuccess = CreateProcess(NULL, pPath, NULL, NULL,
//		FALSE, NULL, NULL, NULL, &Info, &piProcInfo);
//
//	return bSuccess ? true : false;
//}
//
//bool CHJGlobalFun::RunShellExecute( const char* pPath, const char* pPara /*= "" */ )
//{
//	ShellExecute( NULL, "open", pPath, pPara, NULL, NULL );
//
//	return true;
//}

QString CHJGlobalFun::getHostIpAddress()
{
	QString strIpAddress;
	auto ipAddressesList = QNetworkInterface::allAddresses();
	// ��ȡ��һ����������IPv4��ַ  
	int nListSize = ipAddressesList.size();
	for (int i = 0; i < nListSize; ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address()) {
			strIpAddress = ipAddressesList.at(i).toString();
			break;
		}
	}
	// ���û���ҵ������Ա���IP��ַΪIP  
	if (strIpAddress.isEmpty())
		strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
	return strIpAddress;
}



 QString CHJGlobalFun::str2qstr(const std::string& str)
{
	return QString::fromLocal8Bit(str.data());
}

std::string CHJGlobalFun::qstr2str(const QString & qstr)
{
	QByteArray cdata = qstr.toLocal8Bit();
	return std::string(cdata);
}



void CHJGlobalFun::ReadUserChoose(const QString &csPath, const QString &csTitle, bool bName, QVector<QString> &vecUserNames)
{
	//
	QVector<QString> vecAllNames;
	QVector<int> vecColumnIndexs;
	//char buf[2000] = { 0 };
	QString  buf;
	QString csAllTitle = bName ? "AllColumnNames" : "AllColumnIDs";
	// ��ȡȫ���ֶ����ƣ����ָvector
	//::GetPrivateProfileString("Info", csAllTitle, "", buf, sizeof(buf), csPath);
	App::GetPriProfileString(csPath, "Info", csAllTitle, buf);


	CHJGlobalFun::SplitStrToVector(buf, QUERY_INI_SPLITER, vecAllNames);

	// ��ȡλ���ֶΣ����ҷָvector
	//::GetPrivateProfileString("Info", csTitle, "", buf, sizeof(buf), csPath);
	App::GetPriProfileString(csPath, "Info", csTitle, buf);

	CHJGlobalFun::SplitStrToVector(buf, QUERY_INI_SPLITER, vecColumnIndexs);

	// ���ص�ǰ��ʾ��
	for (int i = 0; i < vecColumnIndexs.size(); i++)
	{
		vecUserNames.push_back(vecAllNames.at(vecColumnIndexs.at(i)));
	}
}

//
void CHJGlobalFun::GetIniValueToVector(const QString &csPath, const QString &csMainTitle, const QString &csTitle, const QString &csSplitter, const QString &csDefaulut, QVector<QString> &vecValue)
{
	//
	QString buf;

	App::GetPriProfileString(csPath, csMainTitle, csTitle,  buf);

	CHJGlobalFun::SplitStrToVector(buf, csSplitter, vecValue);
}
