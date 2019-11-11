#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <x_sql_tool.h>
#include <b_bagd.h>
#include <x_sql.h>
#include <c_mzxy.h>
#include <x_about.h>
#include <b_cxsfz.h>
#include <x_test.h>
#include <x_net_tool.h>
#include <y_sbwljhyw.h>
#include <y_jbylbxtdbzmzsqdjjjb.h>
#include <y_zflcx.h>
#include <w_wjzbg.h>
#include <w_wjzbgsb.h>
#include <c_ylxmcsdb.h>
#include <Lemon.h>
#include <n_tcpserver_thread.h>

using namespace std;

b_bagd *b_bagd_w = NULL;
b_cxsfz *b_cxsfz_d = NULL;
x_sql *x_sql_w = NULL;
c_mzxy *c_mzxy_w = NULL;
x_about *x_about_d = NULL;
x_sql_tool *mainSqlTool_t = NULL;
x_test *x_test_w = NULL;
x_net_tool *mainNetTool_t = NULL;
y_sbwljhyw *y_sbwljhyw_w = NULL;
y_jbylbxtdbzmzsqdjjjb *y_tm_w = NULL;
y_zflcx *y_zflcx_w = NULL;
w_wjzbg *w_wjzbg_w = NULL;
w_wjzbgsb *w_wjzbgsb_w = NULL;
c_ylxmcsdb *c_ylxmcsdb_w = NULL;
n_tcpserver_thread *nth = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("朝及软件(测试版 V1.4)");
    //setWindowTitle(QString::fromLocal8Bit("\u8087\u5e86\u5e02\u7aef\u5dde\u533a\u4eba\u6c11\u533b\u9662\u4fe1\u606f\u7cfb\u7edf\u0028\u6d4b\u8bd5\u7248\u0029"));//肇庆市端州区人民医院信息系统(测试版)
    //QWidget* p = takeCentralWidget();//去掉MainWindow中间窗口以拉动LockWidget
    //if(p)delete p;
    setDockNestingEnabled(true);
    ui->statusBar->showMessage("欢迎使用", 2000);

    mainSqlTool_t = new x_sql_tool();
    mainNetTool_t = new x_net_tool();

    nth = new n_tcpserver_thread();
    connect(nth, SIGNAL(n_tcpserver_thread::barMsg_sign(QString)), this, SLOT(MainWindow::barMsg_slots(QString)));
    nth->start();
}

MainWindow::~MainWindow()
{
    if(b_bagd_w != NULL)delete b_bagd_w;
    b_bagd_w = NULL;
    if(x_sql_w != NULL)delete x_sql_w;
    x_sql_w = NULL;
    if(b_bagd_w != NULL)delete b_bagd_w;
    b_bagd_w = NULL;
    if(c_mzxy_w != NULL)delete c_mzxy_w;
    c_mzxy_w = NULL;
    if(y_tm_w != NULL)delete y_tm_w;
    y_tm_w = NULL;
    if(y_zflcx_w != NULL)delete y_zflcx_w;
    y_zflcx_w = NULL;
    if(w_wjzbg_w != NULL)delete w_wjzbg_w;
    w_wjzbg_w = NULL;
    if(c_ylxmcsdb_w != NULL)delete c_ylxmcsdb_w;
    c_ylxmcsdb_w = NULL;

    if(mainSqlTool_t != NULL)delete mainSqlTool_t;
    mainSqlTool_t = NULL;
    if(mainNetTool_t != NULL)delete mainNetTool_t;
    mainNetTool_t = NULL;

    nth->isRun = false;
    if(nth != NULL)delete nth;
    nth = NULL;
    delete ui;
}

void MainWindow::on_action_7_triggered() //病案归档
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(b_bagd_w != NULL)b_bagd_w->show();
    else
    {
        b_bagd_w = new b_bagd(this);
        addDockWidget(Qt::RightDockWidgetArea, b_bagd_w);
        b_bagd_w->xst = mainSqlTool_t;
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_12_triggered() //数据源
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(x_sql_w != NULL)x_sql_w->show();
    else
    {
        x_sql_w = new x_sql(this);
        addDockWidget(Qt::RightDockWidgetArea, x_sql_w);
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_13_triggered() //出院小结上传
{
    //dosomething
}

void MainWindow::on_action_14_triggered() //门诊西药比例
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(c_mzxy_w != NULL)c_mzxy_w->show();
    else
    {
        c_mzxy_w = new c_mzxy(this);
        addDockWidget(Qt::RightDockWidgetArea, c_mzxy_w);
        c_mzxy_w->xst0 = mainSqlTool_t;
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_15_triggered()//关于
{
    x_about_d = new x_about(this);
    x_about_d->show();
}

void MainWindow::deleteP(){
    QWidget* p = takeCentralWidget();//去掉MainWindow中间窗口以拉动ockWidget
    if(p)delete p;
}

void MainWindow::on_action_16_triggered()
{
    b_cxsfz_d = new b_cxsfz(this);
    b_cxsfz_d->show();
    b_cxsfz_d->xst1 = mainSqlTool_t;
}

void MainWindow::on_action_triggered()//社保网络交互业务
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(y_sbwljhyw_w != NULL)y_sbwljhyw_w->show();
    else
    {
        y_sbwljhyw_w = new y_sbwljhyw(this);
        addDockWidget(Qt::RightDockWidgetArea, y_sbwljhyw_w);
        y_sbwljhyw_w->xnt = mainNetTool_t;
        y_sbwljhyw_w->xst = mainSqlTool_t;
        connect(mainNetTool_t, &x_net_tool::onReadData_sign, y_sbwljhyw_w, &y_sbwljhyw::onReadData);
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_11_triggered()//社保网络测试
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(x_test_w != NULL)x_test_w->show();
    else
    {
        x_test_w = new x_test(this);
        addDockWidget(Qt::RightDockWidgetArea, x_test_w);
        x_test_w->xnt = mainNetTool_t;
        connect(mainNetTool_t, &x_net_tool::onReadData_sign, x_test_w, &x_test::onReadData);
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_17_triggered()//特门交接表
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(y_tm_w != NULL)y_tm_w->show();
    else
    {
        y_tm_w = new y_jbylbxtdbzmzsqdjjjb(this);
        addDockWidget(Qt::RightDockWidgetArea, y_tm_w);
        y_tm_w->xst = mainSqlTool_t;
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_18_triggered()//自费率查询
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(y_zflcx_w != NULL)y_zflcx_w->show();
    else
    {
        y_zflcx_w = new y_zflcx(this);
        addDockWidget(Qt::RightDockWidgetArea, y_zflcx_w);
        y_zflcx_w->xst = mainSqlTool_t;
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_19_triggered()//危急值报告
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(w_wjzbg_w != NULL)w_wjzbg_w->show();
    else
    {
        w_wjzbg_w = new w_wjzbg(this);
        addDockWidget(Qt::RightDockWidgetArea, w_wjzbg_w);
        //w_wjzbg_w->xst = mainSqlTool_t;
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_20_triggered()//危急值报告上报
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(w_wjzbgsb_w != NULL)w_wjzbgsb_w->show();
    else
    {
        w_wjzbgsb_w = new w_wjzbgsb(this);
        addDockWidget(Qt::RightDockWidgetArea, w_wjzbgsb_w);
        //w_wjzbg_w->xst = mainSqlTool_t;
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_action_21_triggered()//医疗项目次数对比
{
    ui->statusBar->showMessage("正在打开......");
    deleteP();
    if(c_ylxmcsdb_w != NULL)c_ylxmcsdb_w->show();
    else
    {
        c_ylxmcsdb_w = new c_ylxmcsdb(this);
        addDockWidget(Qt::RightDockWidgetArea, c_ylxmcsdb_w);
        c_ylxmcsdb_w->xst = mainSqlTool_t;
    }
    ui->statusBar->clearMessage();
}

void MainWindow::barMsg_slots(QString msg_str){
    ui->statusBar->showMessage(msg_str);
}
