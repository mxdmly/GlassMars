#include <QtCore>
#include <iostream>
#include <windows.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QByteArray>
#include <QSqlError>
#include <QString>
#include <iostream>
#include <QRegularExpression>
#include <QDebug>
#include <QDateTime>
#include <QApplication>

class Lemon
{
public:
    Lemon();
    ~Lemon();
    void ini();
    int Sign();
    int sendData(QString in_str);
    int SignOut();

    QString getTime();

    HINSTANCE hDLL;
    typedef int(*pTest)(char * a);
    pTest INIT;
    typedef int(*re_i_p)(char * inData, char *outData);
    re_i_p BUSINESS_HANDLE;
    QString myNum_str;//操作员编号
    QString bcNum_str;//业务周期号 Business cycle number
    char *outData_ch;
};
