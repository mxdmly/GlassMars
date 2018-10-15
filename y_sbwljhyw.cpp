#include "y_sbwljhyw.h"
#include "ui_y_sbwljhyw.h"

int queryNum_i;//返回数据的查询编号
y_sbwljhyw::y_sbwljhyw(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::y_sbwljhyw)
{
    ui->setupUi(this);
}

y_sbwljhyw::~y_sbwljhyw()
{
    delete ui;
}

void y_sbwljhyw::on_pushButton_clicked()
{
    queryNum_i = 1400;
    xnt->onWriteData("1400", QString("441200^|").append(ui->lineEdit->text()).append("|01"));
}

void y_sbwljhyw::onReadData(QString readDate_str){ //查询有结果后自动执行此函数
    switch (queryNum_i) {
    case 1400:
        xst->sendMsg(readDate_str);
        queryNum_i = 1600;
        break;
    case 1600:
        queryNum_i = 1710;
        break;
    case 1710:
        queryNum_i = 1400;
        break;
    default:
        queryNum_i = 1400;
        break;
    }
}
/*
void y_sbwljhyw::qTM(){//1600
    xnt->onWriteData(queryNum_i, QString("441200^|").append(ui->lineEdit->text()).append("|01"));
}

void y_sbwljhyw::qZY(){//1710
    xnt->onWriteData(queryNum_i, QString("441200^|").append(ui->lineEdit->text()).append("|01"));
}
*/
