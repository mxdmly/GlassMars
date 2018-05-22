#include "x_sql.h"
#include "ui_x_sql.h"

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
