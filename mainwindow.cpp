#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <b_bagd.h>
#include <x_sql.h>

using namespace std;

b_bagd *b_bagd_w = NULL;
x_sql *x_sql_w = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("\u8087\u5e86\u5e02\u7aef\u5dde\u533a\u4eba\u6c11\u533b\u9662\u4fe1\u606f\u7cfb\u7edf\u0028\u6d4b\u8bd5\u7248\u0029"));//肇庆市端州区人民医院信息系统(测试版)
    QWidget* p = takeCentralWidget();//去掉MainWindow中间窗口以拉动ockWidget
    if(p)delete p;
    setDockNestingEnabled(true);

    ui->statusBar->showMessage("欢迎使用", 2000);
}

MainWindow::~MainWindow()
{
    if(b_bagd_w != NULL)delete b_bagd_w;
    b_bagd_w = NULL;
    if(x_sql_w != NULL)delete x_sql_w;
    x_sql_w = NULL;
    delete ui;
}

void MainWindow::on_action_7_triggered() //病案归档
{
    ui->statusBar->showMessage("正在打开......");
    if(b_bagd_w != NULL)b_bagd_w->show();
    else
    {
        b_bagd_w = new b_bagd(this);
        addDockWidget(Qt::RightDockWidgetArea, b_bagd_w);
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_12_triggered() //数据源
{
    ui->statusBar->showMessage("正在打开......");
    if(x_sql_w != NULL)x_sql_w->show();
    else
    {
        x_sql_w = new x_sql(this);
        addDockWidget(Qt::RightDockWidgetArea, x_sql_w);
    }
    ui->statusBar->clearMessage();
}
