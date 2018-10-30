#include "x_test.h"
#include "ui_x_test.h"

x_test::x_test(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::x_test)
{
    ui->setupUi(this);
}

x_test::~x_test()
{
    delete ui;
}

void x_test::on_pushButton_clicked()
{
    xnt->onWriteData(ui->textEdit->toPlainText(), ui->textEdit_2->toPlainText());
}

void x_test::onReadData(){
    ui->textEdit_3->setPlainText(xnt->onReadData_str);
    qDebug() << xnt->onReadData_str;
}
