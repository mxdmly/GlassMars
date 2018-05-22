#include "b_bagd.h"
#include "ui_b_bagd.h"

b_bagd::b_bagd(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::b_bagd)
{
    ui->setupUi(this);

    ui->tableWidget->resizeColumnsToContents();//设置自动列宽，设置固定列宽 setColumnWidth(3,200)
}

b_bagd::~b_bagd()
{
    delete ui;
}

void b_bagd::on_pushButton_5_clicked()
{

}
