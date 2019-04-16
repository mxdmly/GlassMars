#include "main_loading_thread.h"
#include <QDebug>
#include <QDateTime>


main_loading_thread::main_loading_thread(x_sql_tool *xst1, c_mzxy *c, QTableWidget *t){
    isCorY = 1;
    this->xst1 = xst1;
    this->c = c;
    this->t = t;
    isRun = true;
}

main_loading_thread::main_loading_thread(x_sql_tool *xst1, c_mzxy *c)
{
    isCorY = 1;//区分是哪个类调用
    this->xst1 = xst1;
    this->c = c;
    isRun = true;
}

main_loading_thread::main_loading_thread(y_sbwljhyw *y, main_loading *l)
{
    isCorY = 2;
    this->y = y;
    this->l = l;
    isRun = true;
}

main_loading_thread::~main_loading_thread(){
    m_sq.clear();
}

void main_loading_thread::run(){
    int i = 0;
    switch (isCorY) {
    case 1:
        c->clearTable();
        m_sq = xst1->getData(sql_str);
    /*
        int row_i;
        t->setRowCount(m_sq.numRowsAffected() + 1);
        while (m_sq.next()) {
            t->setItem(row_i, 0, new QTableWidgetItem(QString::number(row_i + 1, 10)));
            for (int i = 0; i < 7; i++) {
                t->setItem(row_i, i + 1, new QTableWidgetItem(m_sq.value(i).toString()));
            }
            t->setItem(row_i, 8, new QTableWidgetItem(m_sq.value(7).toDateTime().toString("yyyy-MM-dd HH:mm:ss")));
            row_i++;
        }
        t->setItem(row_i, 1, new QTableWidgetItem("以下没有数据..."));
        t->resizeColumnsToContents(); //设置自动列宽
    */
        break;
    case 2:
        break;
    default:
        break;
    }
    msleep(500);
    isRun = false;
}

void main_loading_thread::setSqlString(QString str){
    sql_str = str;
}

QSqlQuery main_loading_thread::getSqlQuery(){
    return m_sq;
}

