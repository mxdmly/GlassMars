#include "c_mzxy.h"
#include "ui_c_mzxy.h"
#include <x_sql_tool.h>

using namespace std;

x_sql_tool *xst0;
c_mzxy::c_mzxy(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::c_mzxy)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();//设置自动列宽，setColumnWidth(3,200)设置固定列宽
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//只能选中单个
}

c_mzxy::~c_mzxy()
{
    delete ui;
}

void c_mzxy::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();//清空表格中的内容(不包含表头)
}
