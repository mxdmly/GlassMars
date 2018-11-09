#include "x_about.h"
#include "ui_x_about.h"
#include <QRegExp>
#include <QDebug>
#include <QDate>
#include <x_sql_tool.h>

x_about::x_about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::x_about)
{
    ui->setupUi(this);
    x_sql_tool sd;
    sd.sendMsg(QDate::fromString("20180101", "yyyyMMdd").toString("yyyy年MM月dd日"));
    qDebug() << QDate::fromString("20180101", "yyyyMMdd").toString("yyyy年MM月dd日");
}

x_about::~x_about()
{
    delete ui;
}
