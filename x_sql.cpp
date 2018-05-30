#include "x_sql.h"
#include "ui_x_sql.h"
#include <QMultiHash>
#include <QDebug>

QMultiHash<QString, QString> inifile_hash;

x_sql::x_sql(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::x_sql)
{
    ui->setupUi(this);
}

x_sql::~x_sql()
{
    delete ui;
}

void x_sql::on_pushButton_2_clicked()
{
    inifile_hash.insert(ui->lineEdit->text(), ui->lineEdit_2->text());
    inifile_hash.insert(ui->lineEdit->text(), ui->lineEdit_4->text());
    inifile_hash.insert(ui->lineEdit->text(), ui->lineEdit_5->text());
    QMultiHash<QString, QString>::iterator i = inifile_hash.find(ui->lineEdit->text());
    while (i != inifile_hash.end() && i.key() == ui->lineEdit->text()) {
        qDebug() << i.value();
        ++i;
    }
}
