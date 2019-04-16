#include "w_wjzbg.h"
#include "ui_w_wjzbg.h"
#include <QDate>
#include <QTime>

w_wjzbg::w_wjzbg(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::w_wjzbg)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate().addMonths(-1));
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->lcdNumber->display(3212);
    ui->lcdNumber_2->display(2);
    ui->tableWidget->resizeColumnsToContents(); //设置自动列宽，setColumnWidth(3,200)设置固定列宽
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//拉伸
}

w_wjzbg::~w_wjzbg()
{
    delete ui;
}

void w_wjzbg::on_pushButton_clicked()
{
    ui->label->setText("未处理危急值报告");
    ui->label->setStyleSheet("border: 2px solid;padding:2px;border-radius: 6px;color:red;border-color:red;");
    //ui->tableWidget->clearContents();
}

void w_wjzbg::on_pushButton_2_clicked()
{
    ui->label->setText("查询已处理情况");
    ui->label->setStyleSheet("border: 2px solid;padding:2px;border-radius: 6px;color:#7F1874;border-color:#7F1874;background-color:#DDF0ED;");
    //ui->tableWidget->clearContents();
}

void w_wjzbg::on_pushButton_3_clicked()
{
    ui->tableWidget->clearContents();
}
