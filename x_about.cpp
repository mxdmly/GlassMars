#include "x_about.h"
#include "ui_x_about.h"

x_about::x_about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::x_about)
{
    ui->setupUi(this);
}

x_about::~x_about()
{
    delete ui;
}
