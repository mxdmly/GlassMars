#include "x_sql_tool.h"

using namespace std;

x_sql_tool::x_sql_tool()
{
    isDBopen = true;
}

x_sql_tool::~x_sql_tool()
{
    try
    {
        if(dbEtone_qdb.isOpen())dbEtone_qdb.close();
    }
    catch (const std::exception&)
    {
        sendMsg("Close database error");
    }
}

QSqlQuery x_sql_tool::getData(QString q_str){ //普通查询使用
    QSqlQuery qData_sq(dbEtone_qdb);
    qData_sq.exec(q_str);
    return qData_sq;
}

bool x_sql_tool::saveData(QString q_str){ //重要操作使用
    bool isSuccess_b;
    QSqlQuery qDate_sq(dbEtone_qdb);
    isSuccess_b = qDate_sq.exec(q_str);
    if(isSuccess_b){
        //sendMsg("成功");
    }else {
        sendMsg("失败 \n" + qDate_sq.lastError().text());
        qDebug() << q_str;
        qDebug() << qDate_sq.lastError();
    }
    return isSuccess_b;
}

void x_sql_tool::iniDB()
{
    if(isDBopen)
    {
        dbEtone_qdb = QSqlDatabase::addDatabase("QODBC", "dbHU");
        dbEtone_qdb.setDatabaseName("dbHU");//数据连接名，在控制面板设置
        dbEtone_qdb.setUserName("YBB");
        dbEtone_qdb.setPassword("0");

        if(!dbEtone_qdb.open())
        {
            sendMsg("dbEtone_qdb open Error" + dbEtone_qdb.lastError().text());
            qDebug() << dbEtone_qdb.lastError();
        }
        isDBopen = false;
    }
}

QString x_sql_tool::openSqlFile(QString str)//打开sql文件读取文本内容
{
    QString query_str;
    QFile file(str);//打开这个文件
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))//尝试用只读和文本形式打开
    {
        sendMsg("Open sql file Error");
    }
    else
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            query_str.append(line);
        }
        if(query_str == NULL)sendMsg("sql query is NULL");
    }
    return query_str;
}

void x_sql_tool::sendMsg(QString str)//一个方便使用的文本弹出框
{
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}
