#include "b_bagd.h"
#include "ui_b_bagd.h"

b_bagd::b_bagd(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::b_bagd)
{
    ui->setupUi(this);
}

b_bagd::~b_bagd()
{
    delete ui;
}
