#if !defined(CONST_H)
#define CONST_H

#include <QString>

const QString gc_ErrCodeSus("00000000");  // Ӧ���ĳɹ��ı�ʶ
const QString gc_ErrCode_ConSverFail("CON00001");  // Ӧ���ĳɹ��ı�ʶ

const QString gc_YesNo_Yes("1");
const QString gc_YesNo_No("0");

const QString gc_EmptyStr("");

const QString gc_BSFlag_Buy("b");   // ����
const QString gc_BSFlag_Sell("s");  // ����

const QString gc_OffsetFlag_Open("0");       // ����
const QString gc_OffsetFlag_Cov("1");        // ƽ��
const QString gc_OffsetFlag_ForceCov("2");   // ǿƽ
const QString gc_OffsetFlag_TodayCov("3");   // ƽ�� 

#endif