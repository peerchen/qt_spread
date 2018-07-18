#pragma once
#include <QString>
#include <QObject>

// CCreateVerificationCode ����Ŀ��
class CCreateVerificationCode //: public QObject
{
protected:
	CCreateVerificationCode();
public:
	virtual ~CCreateVerificationCode();


	class CGarbo // ����Ψһ��������������������ɾ��CSingleton��ʵ��
	{
	public:
		~CGarbo()
		{
			if (CCreateVerificationCode::m_Unique)
			{
				delete CCreateVerificationCode::m_Unique;
			}
		}
	};
	static CGarbo Garbo; // ����һ����̬��Ա���ڳ������ʱ��ϵͳ�����������������

public:
	static CCreateVerificationCode * GetInstance();
private:
	static CCreateVerificationCode * m_Unique;
	static char code[];
	int CodeNum;         //��֤���λ����

public:
	QString GenerateVerificationCode();
	void SetCodeNum(int t);

};


