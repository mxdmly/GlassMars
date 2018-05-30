#ifndef X_SQL_TOOL_H
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QSqlError>
#define X_SQL_TOOL_H

class x_sql_tool
{
public:
    x_sql_tool();
    ~x_sql_tool();

    bool ifIni_b;
    bool isDBopen;
    QSqlDatabase dbEtone_qdb;

    void iniDB();
    void sendMsg(QString str);
    QString openSqlFile(QString str);
    QSqlQuery getData(QString q_str);
};

#endif // X_SQL_TOOL_H
