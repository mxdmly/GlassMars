#include "x_sql.h"
#include "ui_x_sql.h"
#include <QMultiHash>
#include <QDebug>
#include <x_file_tool.h>

QMultiHash<QString, QString> iniFile_hs;
x_file_tool *xft = NULL;

x_sql::x_sql(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::x_sql)
{
    ui->setupUi(this);
    xft = new x_file_tool();
    xft->setPath();
}

x_sql::~x_sql()
{
    if(xft != NULL){
        delete xft;
        xft = NULL;
    }
    delete ui;
}

void x_sql::on_pushButton_2_clicked()
{
    iniFile_hs.insert(ui->lineEdit->text(), ui->lineEdit_2->text());
    iniFile_hs.insert(ui->lineEdit->text(), ui->lineEdit_4->text());
    iniFile_hs.insert(ui->lineEdit->text(), ui->lineEdit_5->text());
    QMultiHash<QString, QString>::iterator i = iniFile_hs.find(ui->lineEdit->text());
    while (i != iniFile_hs.end() && i.key() == ui->lineEdit->text()) {
        qDebug() << i.value();
        ++i;
    }
    qDebug() << xft->filePath_str;
}
