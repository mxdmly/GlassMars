#include "x_net.h"
#include "ui_x_net.h"

x_net::x_net(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::x_net)
{
    ui->setupUi(this);
}

x_net::~x_net()
{
    delete ui;
}
