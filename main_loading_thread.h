#ifndef MAIN_LOADING_THREAD_H
#include <x_sql_tool.h>
#include <c_mzxy.h>
#include <y_sbwljhyw.h>
#include <main_loading.h>
#include <QTableWidget>
#define MAIN_LOADING_THREAD_H

#include <QThread>

class main_loading_thread : public QThread
{
    Q_OBJECT
    void run() override;
public:
    main_loading_thread();
    main_loading_thread(x_sql_tool *xst1);
    main_loading_thread(y_sbwljhyw *y, main_loading *l);
    main_loading_thread(x_sql_tool *xst1, c_mzxy *c);
    main_loading_thread(x_sql_tool *xst1, c_mzxy *c, QTableWidget *t);
    ~main_loading_thread();
    void setSqlString(QString str);
    QSqlQuery getSqlQuery();

    c_mzxy *c;
    y_sbwljhyw *y;
    main_loading *l;
    QTableWidget *t;
    x_sql_tool *xst1;
    bool isRun;
    short isCorY;//1=c,2=y
    QString sql_str;
    QSqlQuery m_sq;//储存查询数据库后返回的结果
signals:
    void resultReady(const QString &s);
    void updateBar(int);
};

#endif // MAIN_LOADING_THREAD_H
