#include "ui_x_sql_listitem.h"
#include "ui_ui_x_sql_listitem.h"
#include <QDebug>

ui_x_sql_listitem::ui_x_sql_listitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_x_sql_listitem)
{
    ui->setupUi(this);
}

void ui_x_sql_listitem::setText(QString label_str){
    ui->label->setText(label_str);
}

ui_x_sql_listitem::~ui_x_sql_listitem()
{
    delete ui;
}

void ui_x_sql_listitem::on_pushButton_clicked()
{
    emit deleteItem_sign();
}

void ui_x_sql_listitem::setLableTextColor(QString str){
    ui->label->setStyleSheet(str);
}
