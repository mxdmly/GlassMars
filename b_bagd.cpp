#include "b_bagd.h"
#include "ui_b_bagd.h"
#include <x_sql_tool.h>

using namespace std;

x_sql_tool *xst;
QString sDay_str, eDay_str, ks_str, name_str, zyh_str, recTime_str;//出院日期2个，科室，姓名，住院号，回收时间
QSqlQuery w_sq;//储存查询数据库后返回的结果

b_bagd::b_bagd(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::b_bagd)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();//设置自动列宽，setColumnWidth(3,200)设置固定列宽
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//只能选中单个

    ui->dateEdit->setDate(QDate::currentDate().addDays(-30));
    ui->dateEdit_2->setDate(QDate::currentDate());

    xst = new x_sql_tool();
}

b_bagd::~b_bagd()
{
    if(xst != NULL)delete xst;
    delete ui;
}

void b_bagd::on_pushButton_5_clicked()//查询
{
    int row_i = 0;
    QString sql_str;
    ui->tableWidget->clearContents();//清空表格中的内容(不包含表头)
    ks_str = ui->comboBox->currentText();
    sDay_str = ui->dateEdit->date().toString(Qt::ISODate);
    eDay_str = ui->dateEdit_2->date().toString(Qt::ISODate);
    recTime_str = ui->calendarWidget->selectedDate().toString(Qt::ISODate);
    qDebug() << ks_str << "  " << sDay_str << "  " << recTime_str;

    if(xst->ifIni_b)xst->iniDB();//初始化数据库工具
    sql_str = "SELECT * FROM nhis.dbo.b_bagd_w WHERE ";
    if (ks_str != "全部") {
        sql_str.append("OutDeptment = ").append("\'").append(ks_str).append("\'").append(" AND ");
    }
    sql_str.append("DischargeDT >= ").append("\'").append(sDay_str).append("\'").append(" AND ");
    sql_str.append("DischargeDT <= ").append("\'").append(eDay_str).append(" 23:59:59").append("\'");
    qDebug() << sql_str;
    w_sq = xst->getData(sql_str);
    ui->tableWidget->setRowCount(w_sq.numRowsAffected() + 1);
    while (w_sq.next()) {
        for (int i = 0; i < 3; i++) {
            ui->tableWidget->setItem(row_i, i, new QTableWidgetItem(w_sq.value(i).toString()));
        }
        ui->tableWidget->setItem(row_i, 3, new QTableWidgetItem(w_sq.value(3).toDateTime().toString("yyyy-MM-dd HH:mm:ss")));
        for (int i = 4; i < 7; i++) {
            ui->tableWidget->setItem(row_i, i, new QTableWidgetItem(w_sq.value(i).toString()));
        }
        ui->tableWidget->item(row_i, 0)->setFlags(Qt::NoItemFlags);
        row_i++;
    }
    ui->tableWidget->setItem(row_i, 1, new QTableWidgetItem("以下没有数据..."));

    ui->tableWidget->resizeColumnsToContents();//设置自动列宽，setColumnWidth(3,200)设置固定列宽

}

void b_bagd::keyPressEvent(QKeyEvent *event){
    int row_i, dayDeff_i;//当前选择的行数，日期时效
    row_i = ui->tableWidget->currentRow();
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        qDebug() << "hkjhkjhkjh";
        qDebug() << "sadasdasd" << ui->tableWidget->rowCount();
        qDebug() << "asd" << row_i;
        ui->tableWidget->setItem(row_i, 7, new QTableWidgetItem(recTime_str));
        dayDeff_i = QDate::fromString(ui->tableWidget->item(row_i, 3)->text()).daysTo(QDate::fromString(recTime_str));
        ui->tableWidget->setItem(row_i, 6, new QTableWidgetItem(QString::number(dayDeff_i, 10)));
        qDebug() << "dat " << dayDeff_i;
    }
}
