//#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>

#include "RandCodeLabel.h"
#include <chrono>  
//#include <boost/thread.hpp>  
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QTime>
#include <QEventLoop>
#include <QTimer>
#include "Global.h"

//#pragma comment( lib,"winmm.lib" )

RandCodeLabel::RandCodeLabel(QWidget * parent )
	: QLabel(parent)
{
	m_pVerificationCode = CCreateVerificationCode::GetInstance();
	m_pVerificationCode->SetCodeNum(4);

	m_width  = width()+30;
	m_height = height()+10;
	m_backPixel = new uint[m_width * m_height];

	
	connect(this, &RandCodeLabel::clicked, this, &RandCodeLabel::ShowCode);
	setText("");
	ShowCode();
	show();
}

RandCodeLabel::~RandCodeLabel()
{

}

void RandCodeLabel::sleepNow(quint32 paramMilsecond)
{
	QEventLoop eventloop;
	QTimer::singleShot(paramMilsecond, &eventloop, SLOT(quit()));
	eventloop.exec();

}


qint16 RandCodeLabel::generateRandom(qint16 paramLow, qint16 paramHigh)
{
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
	sleepNow(2);
	if (paramLow > 0) {
		return paramLow + rand() % (paramHigh - paramLow);
	}
	else {
		return paramLow + rand() % (abs(paramLow) + paramHigh);
	}
}

QColor RandCodeLabel::generateRandomBgColor()
{
	QVector<QColor> avaliableColor;
	// Ѽ����
	avaliableColor.push_back(QColor(209, 227, 219));
	// ��ɫ
	avaliableColor.push_back(QColor(245, 245, 220));
	// ����
	avaliableColor.push_back(QColor(235, 232, 219));
	// �׻�
	avaliableColor.push_back(QColor(197, 191, 173));
	// ��ʯ��
	avaliableColor.push_back(QColor(234, 220, 214));
	// ѩɫ
	avaliableColor.push_back(QColor(255, 250, 25));
	// ˮ��
	avaliableColor.push_back(QColor(190, 210, 182));
	// ����
	avaliableColor.push_back(QColor(123, 161, 168));
	// ǳ����
	avaliableColor.push_back(QColor(186, 195, 203));
	// ǳѪ��
	avaliableColor.push_back(QColor(234, 205, 209));
	return avaliableColor[generateRandom(1, avaliableColor.size()) - 1];
}

void RandCodeLabel::ShowCode()
{
	//QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ȷ��"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	//���Ƶ�ɫ
	m_strCode = m_pVerificationCode->GenerateVerificationCode();
	m_strCode.replace("1", "2");
	m_strCode.replace("I", "T");
	m_strCode.replace("i", "T");
	m_strCode.replace("L", "B");
	m_strCode.replace("l", "B");
	////��ʼ��������ɫ
	for (int i = 0; i < m_width*m_height; i++)
	{
		m_backPixel[i] = 0x00;//0x00000000
	}

	//����һ��������ɫ��ÿһ�����ص����»�ɫ
	//srand((unsigned)timeGetTime());//�������������
	ulong randNum;
	ulong randNum2;
	for (int i = 0;i<(m_width * m_height);i++)
	{
		//�ĸ��ֽڣ��������ҵ���Ϣ�ֱ�Ϊ��rgbReserved,r,g,b
		randNum = rand() % 0x00ffffff;
		randNum2 = rand() % 0x00ffffff;
		m_backPixel[i] = randNum & randNum2;
	}

	//���Ŷ����������

	//���������ڱ�����ע��ߵ�
	//srand((unsigned)timeGetTime());//�������������

	ulong totalPixel = m_width*m_height - 1;
	ulong pixelPos = 1;
	for (ulong j = 0;j<((ulong)(totalPixel*0.1));j++)
	{
		pixelPos = rand() % totalPixel;
		m_backPixel[pixelPos] = 0x00ffffff;
	}
    
	//QString strPath = QString("%1Resources\\Images\\DeepBlack\\randCode.png").arg(g_Global.GetSystemPath());

	//20180105  ����Format_RGB32�ǵ�ɫ͸�����������ͣ��ñ�����͸��
	QImage    *image32 = new QImage((uchar *)m_backPixel,m_width, m_height, QImage::Format_RGB666);//Format_RGB32
	//image32->fill(generateRandomBgColor());

	setPixmap(QPixmap::fromImage(*image32));

	show();
}

void RandCodeLabel::mousePressEvent(QMouseEvent *event)
{
	emit clicked();
}

void RandCodeLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);
	QPainter painter(this);

	//�ı仭�ʺ�����
	QPen pen = painter.pen();
	pen.setColor(Qt::white);
	QFont font = painter.font();
	//font.setBold(true);//�Ӵ�
	font.setPixelSize(25);//�ı������С
	painter.setPen(pen);
	painter.setFont(font);

	QFontMetrics fm = painter.fontMetrics();


	//QString list[] = { m_strCode[0],m_strCode[1],m_strCode[2],m_strCode[3] };
	//for (int i = 0; i<5; i++)
	{
		int width  = this->width();
		int height = this->height();

		painter.drawText(width , height ,m_strCode);
	}

	painter.drawText(QPoint(25, 28), m_strCode);
	return;
}