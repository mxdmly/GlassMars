#include "b_cxsfz.h"
#include "ui_b_cxsfz.h"
#include <x_sql_tool.h>

x_sql_tool *xst1;
QSqlQuery w_sq1;
b_cxsfz::b_cxsfz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::b_cxsfz)
{
    ui->setupUi(this);

    xst1 = new x_sql_tool();

    QRegExp le_qre("[1-9]{0,20}$");
    QValidator *le_qv = new QRegExpValidator(le_qre, this);
    ui->lineEdit->setValidator(le_qv);
}

b_cxsfz::~b_cxsfz()
{
    w_sq1.clear();
    if(xst1 != NULL)delete xst1;
    xst1 = NULL;
    delete ui;
}

void b_cxsfz::on_pushButton_clicked()
{
    QString sql_str = xst1->openSqlFile(QCoreApplication::applicationDirPath() + "\\c_cxsfz.sql");
    sql_str.append(ui->lineEdit->text()).append("\'");
    xst1->iniDB();
    w_sq1 = xst1->getData(sql_str);
    if(w_sq1.numRowsAffected() >= 1){
        w_sq1.next();
        ui->lineEdit_2->setText(w_sq1.value(1).toString());
        ui->lineEdit_3->setText(w_sq1.value(2).toString());
    }
}
