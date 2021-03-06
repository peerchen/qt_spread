﻿#ifndef MACRODEFS_H
#define MACRODEFS_H

#include <QFile>
#include <QTextStream>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTime>
#include <QWidget>
#include <QPushButton>
//#include "LxFloatDialog.h"
#include <QDebug>

#define MY_COLORREF unsigned long
#define MY_UNIT unsigned int

#define _MYTAB_TEXT(x) QString::fromLocal8Bit("  ") + QString::fromLocal8Bit(x) + QString::fromLocal8Bit(" ")
#define _MY_TEXT(x) QString::fromLocal8Bit(x)

__inline void setStringValue(QString &str,const QString & area,const QString & name,const QString & value)
{
    int head = str.indexOf(area);
    if(head == -1) return;
    int tail = str.indexOf("}",head);
    if(tail == -1) return;
    int nameHead = str.indexOf(name,head);
    if(nameHead == -1 || nameHead > tail) return;
    int nameTail = str.indexOf(";",nameHead);
    if(nameTail > tail) return;

    str.replace(nameHead+name.size(),nameTail-nameHead-name.size(),value);

}


//设置指定区域的css格式文件的值
//示例:qssFileName: ./Resources/styles/mainframe.css
//area:QMenuBar \n{
//name:background-color:
//value:#FFFFFF
//
__inline void setCssFile(const QString & qssFileName,const QStringList & area,const QStringList & name,const QStringList & value)
{
    if(!(area.size() == name.size() && name.size() == value.size()))
        return;
    QFile file(qssFileName);
    if(file.open(QFile::ReadWrite|QFile::Text))
    {
        QString temp = QString::fromUtf8(file.readAll());
        for(int i = 0; i < area.size(); i++)
        {
            setStringValue(temp,area.at(i),name.at(i),value.at(i));
        }
        file.resize(0);
        file.write(temp.toUtf8());

    }

}

#define SET_CSSFILE(q,a,n,v) setCssFile(q,a,n,v);

//读取Qss样式表对指定窗口设置显示风格
__inline void setWidgetStyleFromQssFile(QWidget *pWidget, QString qssFileName)
{
    QString  qss;
    qss = qssFileName;
    QFile file(qss);
    file.open(QFile::ReadOnly | QFile::Text);//QFile::ReadOnly
   
	if(file.isOpen())
    {
        QString btnstylesheet = QObject::tr(file.readAll());
        pWidget->setStyleSheet(btnstylesheet);
        file.close();
    }
}

#define SET_WIDGET_STYLE(x, f) setWidgetStyleFromQssFile(x, f)

//读取csv格式的Table配置文件做初始化
__inline void setTableModel(QString fileName, QStandardItemModel *p_model)
{
    QFile file(fileName);

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString line = stream.readLine();
        QStringList list = line.split(",", QString::SkipEmptyParts);
        p_model->setHorizontalHeaderLabels(list);

//         QTime time;
//         time= QTime::currentTime();
//         qsrand(time.msec()+time.second()*1000);
// 
// 
         int row = 0;
         while (!stream.atEnd()) {
             line = stream.readLine();
             if (!line.startsWith("#") && line.contains(",")) {
                 list= line.split(",");
                 for (int col = 0; col < list.length(); ++col)
                 {
                     p_model->setItem(row, col, new QStandardItem(list.at(col)));
                 }
                 ++row;
             }
         }
    }
    file.close();
}

/*
 * 函数作用：将按钮装换为图片格式
 * 参数1：图片的地址
 * 参数2：是否要改变图片，NULL表示新申请一个按钮资源，不为空表示是要更换指定按钮图片
 * 返回值：返回操作的按钮资源
 */
__inline QPushButton *TranBtnToIcon(QString strPicturePath, QPushButton *btn)
{
    QPushButton *pushButton = btn;
    QImage image(strPicturePath);
    QString strWidth = QString("%1").arg(image.width());
    QString strHeight = QString("%1").arg(image.height());
    QString strStyleSheet = "QPushButton{background-color: transparent; width: " + strWidth \
            + "px; height: " + strHeight + "px; border-image:url(" + strPicturePath + ");}";
    strStyleSheet.replace("\\", "/");
    pushButton->setStyleSheet(strStyleSheet);
    pushButton->setFixedSize(QSize(image.width(),image.height()));
    return pushButton;
}

__inline void ShowFloatMsg(QString strTitle, QString strText)
{
   /* LxFloatDialog *dlg = new LxFloatDialog();
    dlg->SetMsg(strTitle, strText);
    dlg->show();*/
}

#define SET_TABLE_MODEL(fn, m) setTableModel(fn, m)

#ifdef _WIN32

//文件路径前缀宏定义
#define _ROOT_PATH      _MY_TEXT(".\\")
#define _RESOURCE_PATH  _ROOT_PATH + _MY_TEXT("Resources\\")
#define _RES_CONFIG_PATH  _RESOURCE_PATH + _MY_TEXT("Config\\")
#define _RES_IMAGES_PATH  _RESOURCE_PATH + _MY_TEXT("Images\\")
#define _RES_STYLES_PATH  _RESOURCE_PATH + _MY_TEXT("Styles\\")
#define _RES_DATADB_PATH  _RESOURCE_PATH + _MY_TEXT("Datadb\\")
#define _RES_SPLASH_PATH  _RESOURCE_PATH + _MY_TEXT("Splash\\")
#define _RES_VOICE_PATH _RESOURCE_PATH + _MY_TEXT("Voice\\")
#define _RES_GIF_PATH _RESOURCE_PATH + _MY_TEXT("Gif\\")

#else

//文件路径前缀宏定义
#define _ROOT_PATH      _MY_TEXT("./")
#define _RESOURCE_PATH  _ROOT_PATH + _MY_TEXT("Resources/")
#define _QUERY_CONFIG_PATH  _ROOT_PATH + _MY_TEXT("QueryConfig/")

#define _RES_CONFIG_PATH  _RESOURCE_PATH + _MY_TEXT("Config/")
#define _RES_IMAGES_PATH  _RESOURCE_PATH + _MY_TEXT("Images/")
#define _RES_STYLES_PATH  _RESOURCE_PATH + _MY_TEXT("Styles/")
#define _RES_DATADB_PATH  _RESOURCE_PATH + _MY_TEXT("Datadb/")
#define _RES_SPLASH_PATH  _RESOURCE_PATH + _MY_TEXT("Splash/")
#define _RES_VOICE_PATH _RESOURCE_PATH + _MY_TEXT("Voice/")
#define _RES_GIF_PATH _RESOURCE_PATH + _MY_TEXT("Gif/")

#endif

#define TITLE_DEFAULT_COLOR "rgb(220, 220, 220);"
#define TITLE_HIGHLIGHT_CLOR "rgb(248, 182, 45);"

#endif // MACRODEFS_H

