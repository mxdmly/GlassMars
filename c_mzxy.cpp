﻿#include "c_mzxy.h"
#include "ui_c_mzxy.h"
#include <x_file_tool.h>
#include <main_loading_thread.h>
#include <main_loading.h>
#include <windows.h>

using namespace std;

x_file_tool *xft0;//避免重复，以出现次数作后缀
QSqlQuery w_0sq;//储存查询数据库后返回的结果
main_loading *ml;
main_loading_thread *sd;
c_mzxy::c_mzxy(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::c_mzxy)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();//设置自动列宽，setColumnWidth(3,200)设置固定列宽
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//只能选中单个

    int today_i = QDate::currentDate().day();//用于更改选择的日期
    ui->calendarWidget->setSelectedDate(QDate::currentDate().addMonths(-1).addDays(1 - today_i));
    ui->calendarWidget_2->setSelectedDate(QDate::currentDate().addDays(- today_i));

    QRegExp le_qre("[1-9]{0,20}$"), le2_qre("^[\u4e00-\u9fa5,1-9,a-z,A-Z]{0,8}$");//使用正则表达式限制用户输入
    QValidator *le_qv = new QRegExpValidator(le_qre, this);
    QValidator *le2_qv = new QRegExpValidator(le2_qre, this);
    ui->lineEdit->setValidator(le_qv);
    ui->lineEdit_2->setValidator(le2_qv);
    ui->lineEdit_3->setValidator(le2_qv);

    xft0 = new x_file_tool();

}

c_mzxy::~c_mzxy()
{
    w_0sq.clear();//不添加这行程序会死掉
    if(xft0 != NULL)delete xft0;
    xft0 = NULL;
    delete ui;
}

void c_mzxy::on_pushButton_clicked()
{
    int row_i = 0;
    QString sql_str;
    QString fTypeId_str, sDay_str, eDay_str;//费用类型，开始日期，结束日期

    ml = new main_loading(this);
    ml->show();

    //ui->tableWidget->clearContents();//清空表格中的内容(不包含表头)(2018年8月30日耗时操作，放到新线程里)
    sDay_str = QDate(ui->calendarWidget->selectedDate()).toString(Qt::ISODate);
    eDay_str = QDate(ui->calendarWidget_2->selectedDate().addDays(1)).toString(Qt::ISODate);
    xst0->iniDB();
    //sql_str = xst0->openSqlFile("C:\\Qt\\GP\\c_mzxy.sql");
    sql_str = xst0->openSqlFile(QCoreApplication::applicationDirPath() + "\\sql\\c_mzxy.sql");

    if(ui->comboBox->currentIndex()){
        switch(ui->comboBox->currentIndex()){
            case 1 :
            fTypeId_str = "1";//自费医疗
            break;
            case 2 :
            fTypeId_str = "22";//门诊特殊病
            break;
            case 3 :
            fTypeId_str = "23";//离休门诊
            break;
            case 8 :
            fTypeId_str = "72";//城乡居民医保
            break;
        default:
            fTypeId_str = "";
        }
        sql_str.append("InsuranceTypeId = ").append(fTypeId_str).append(" AND ");
    }
    if(! ui->lineEdit->text().isEmpty()){
        sql_str.append("InvoiceNo = ").append(ui->lineEdit->text()).append(" AND ");
    }
    if(! ui->lineEdit_2->text().isEmpty()){
        sql_str.append("PatientName = \'").append(ui->lineEdit_2->text()).append("\' AND ");
    }
    if(! ui->lineEdit_3->text().isEmpty()){
        sql_str.append("OrderingDoctor = \'").append(ui->lineEdit_3->text()).append("\' AND ");
    }
    sql_str.append("WorkDT >= \'").append(sDay_str).append("\' AND ").append("WorkDT <= \'").append(eDay_str).append("\'");
    sql_str.append(" ORDER BY nhis.dbo.a_c_mzxy.WorkDT ASC");

    sd = new main_loading_thread(xst0, this);
    sd->setSqlString(sql_str);
    sd->start();
    //w_0sq = xst0->getData(sql_str);

    int i = 0;
    while (sd->isRun) {
        ml->updateProgressBar(i);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        Sleep(i * 10);
        if(i < 99)i++;
    }

    w_0sq = sd->getSqlQuery();//起错方法名，这是用新线程从数据库查询用的

    //qDebug() << w_0sq;

    ui->tableWidget->setRowCount(w_0sq.numRowsAffected() + 1);
    while (w_0sq.next()) {
        ui->tableWidget->setItem(row_i, 0, new QTableWidgetItem(QString::number(row_i + 1, 10)));
        /*for (int i = 0; i < 7; i++) {
            ui->tableWidget->setItem(row_i, i + 1, new QTableWidgetItem(w_0sq.value(i).toString()));
        }*/
        ui->tableWidget->setItem(row_i, 1, new QTableWidgetItem(w_0sq.value(0).toString()));
        ui->tableWidget->setItem(row_i, 2, new QTableWidgetItem(w_0sq.value(1).toString()));
        ui->tableWidget->setItem(row_i, 3, new QTableWidgetItem(QString::number(w_0sq.value(2).toFloat())));
        ui->tableWidget->setItem(row_i, 4, new QTableWidgetItem(QString::number(w_0sq.value(3).toFloat())));
        ui->tableWidget->setItem(row_i, 5, new QTableWidgetItem(QString::number(w_0sq.value(4).toFloat())));
        ui->tableWidget->setItem(row_i, 6, new QTableWidgetItem(QString::number(w_0sq.value(5).toFloat())));
        ui->tableWidget->setItem(row_i, 7, new QTableWidgetItem(w_0sq.value(6).toString()));
        ui->tableWidget->setItem(row_i, 8, new QTableWidgetItem(w_0sq.value(7).toString()));
        ui->tableWidget->setItem(row_i, 9, new QTableWidgetItem(w_0sq.value(8).toDateTime().toString("yyyy-MM-dd HH:mm:ss")));
        row_i++;
    }
    ui->tableWidget->setItem(row_i, 1, new QTableWidgetItem("以下没有数据..."));
    ui->tableWidget->resizeColumnsToContents(); //设置自动列宽

    //qDebug() << w_0sq.lastError();
    if(w_0sq.lastError().isValid()){
        xst0->sendMsg("查询出错！\n\n请检查输入情况，是否输入了错误的字符");
    }else{
        ml->updateProgressBar(100);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        Sleep(500);
    }

    delete sd;
    delete ml;
}

void c_mzxy::on_pushButton_2_clicked()
{
    //Export Excel
    int row_i = ui->tableWidget->rowCount() - 1;//总行数
    int col_i = ui->tableWidget->columnCount();//总列数
    if(row_i >= 1){
        //col_i--; //判断是否点击了已归档或未归档记录，因为导出未归档记录会有NULL的Item

        QList<QString> l_l;
        QString temp_str = "";
        for (int i = 0; i < col_i; i++) {
            temp_str.append(ui->tableWidget->horizontalHeaderItem(i)->text()).append("\t");
        }
        l_l.push_back(temp_str);
        for (int i = 0; i < row_i; i++) {
            temp_str = "";
            for (int j = 0; j < col_i; j++) {
                temp_str.append(ui->tableWidget->item(i, j)->text()).append("\t");
                //char *c = ui->tableWidget->item(i, j)->text().toLocal8Bit().data();

                //qDebug() << QString::fromLocal8Bit(ui->tableWidget->item(i, j)->text());
            }
            l_l.push_back(temp_str);
        }
        QTextEdit date_te;
        for (int i = 0; i < l_l.size(); i++) {
            date_te.append(l_l.at(i));
        }
        qDebug() << xft0->setPath("");
        xft0->setPath(this, QString("").append(QDate::currentDate().toString("yyyy-MM-dd")).append(".xls"));
        qDebug() << xft0->filePath_str;
        xft0->writeFile(date_te.document()->toPlainText());
    }else {
        xft0->sendMsg("错误！\n\n无有效数据");
    }
}

void c_mzxy::clearTable(){
    ui->tableWidget->clearContents();//清空表格中的内容(不包含表头)
}
