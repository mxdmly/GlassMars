#include "w_wjzbgsb.h"
#include "ui_w_wjzbgsb.h"

w_wjzbgsb::w_wjzbgsb(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::w_wjzbgsb)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();//设置自动列宽，setColumnWidth(3,200)设置固定列宽
}

w_wjzbgsb::~w_wjzbgsb()
{
    delete ui;
}
