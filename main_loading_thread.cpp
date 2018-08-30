#include "main_loading_thread.h"
#include <QDebug>

main_loading_thread::main_loading_thread(x_sql_tool *xst1, c_mzxy *c)
{
    this->xst1 = xst1;
    this->c = c;
    isRun = true;
}

main_loading_thread::~main_loading_thread(){
    m_sq.clear();
}

void main_loading_thread::run(){
    c->clearTable();
    m_sq = xst1->getData(sql_str);
    msleep(500);
    isRun = false;
}

void main_loading_thread::setSqlString(QString str){
    sql_str = str;
}

QSqlQuery main_loading_thread::getSqlQuery(){
    return m_sq;
}
