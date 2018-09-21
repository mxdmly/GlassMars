#include "b_bagd.h"
#include "ui_b_bagd.h"
#include <x_file_tool.h>

using namespace std;

QString sDay_str, eDay_str, ks_str, name_str, zyh_str, recTime_str;//出院日期2个，科室，姓名，住院号，回收时间
QString xsql_str, ysql_str;//用于改变查询方式，改变插入或删除
int xsql_i;//用于改变查询列数
bool isSaveOrExport_b, isInsOrDel_b, isExist_b;//true是保存，false是导出Excel；true是插入，false是删除；true是存在归档记录，false是未归档
QSqlQuery w_sq;//储存查询数据库后返回的结果

b_bagd::b_bagd(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::b_bagd)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();//设置自动列宽，setColumnWidth(3,200)设置固定列宽
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//只能选中单个

    ui->dateEdit->setDate(QDate::currentDate().addDays(-31));
    ui->dateEdit_2->setDate(QDate::currentDate());

    on_pushButton_clicked();
}

b_bagd::~b_bagd()
{
    w_sq.clear();//不添加这行程序会死掉
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
    name_str = ui->lineEdit->text();
    zyh_str = ui->lineEdit_2->text();
    recTime_str = QDateTime(ui->calendarWidget->selectedDate(), QTime().currentTime()).toString("yyyy-MM-dd HH:mm:ss");

    if(xst->ifIni_b)xst->iniDB();//初始化数据库工具
    sql_str = xsql_str;//改变查询方式
    if (ks_str != "全部") {
        sql_str.append("OutDeptment = ").append("\'").append(ks_str).append("\'").append(" AND ");
    }
    sql_str.append("DischargeDT >= ").append("\'").append(sDay_str).append("\'").append(" AND ");
    sql_str.append("DischargeDT <= ").append("\'").append(eDay_str).append(" 23:59:59").append("\' ");
    if(name_str.length() > 0 && name_str.length() <= 10){
        sql_str.append("AND Name = ").append("\'").append(name_str).append("\' ");
    }
    if (zyh_str.length() > 0 && zyh_str.length() <= 10) {
        sql_str.append("AND CaseNo = ").append("\'").append(zyh_str).append("\'");
    }
    w_sq = xst->getData(sql_str);
    ui->tableWidget->setRowCount(w_sq.numRowsAffected() + 1);
    while (w_sq.next()) {
        for (int i = 0; i < 3; i++) {
            ui->tableWidget->setItem(row_i, i, new QTableWidgetItem(w_sq.value(i).toString()));
        }
        ui->tableWidget->setItem(row_i, 3, new QTableWidgetItem(w_sq.value(3).toDateTime().toString("yyyy-MM-dd HH:mm:ss")));
        for (int i = 4; i < xsql_i; i++) {
            ui->tableWidget->setItem(row_i, i, new QTableWidgetItem(w_sq.value(i).toString()));
        }
        if(xsql_i == 7){
            ui->tableWidget->setItem(row_i, xsql_i, new QTableWidgetItem(w_sq.value(xsql_i).toDateTime().toString("yyyy-MM-dd HH:mm:ss")));
        }
        ui->tableWidget->item(row_i, 0)->setFlags(Qt::NoItemFlags);
        row_i++;
    }
    ui->tableWidget->setItem(row_i, 1, new QTableWidgetItem("以下没有数据..."));

    ui->tableWidget->resizeColumnsToContents(); //设置自动列宽，setColumnWidth(3,200)设置固定列宽
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//拉伸

    if(isSaveOrExport_b){
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    }else {
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void b_bagd::keyPressEvent(QKeyEvent *event){
    int row_i, dayDeff_i; //当前选择的行数，日期时效
    row_i = ui->tableWidget->currentRow();
    if(isSaveOrExport_b && row_i > -1 && NULL != ui->tableWidget->item(row_i, 3)){ //判断是否打印模式，判断是否正确选择了一行
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){ //写入日期，自动生成时效数字
            ui->tableWidget->setItem(row_i, 7, new QTableWidgetItem(recTime_str));
            dayDeff_i = QDateTime::fromString(ui->tableWidget->item(row_i, 3)->text(), "yyyy-MM-dd HH:mm:ss").daysTo(QDateTime::fromString(recTime_str, "yyyy-MM-dd HH:mm:ss"));
            ui->tableWidget->setItem(row_i, 6, new QTableWidgetItem(QString::number(dayDeff_i, 10)));
        }else if(event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete){ //清除
            ui->tableWidget->setItem(row_i, 6, NULL);
            ui->tableWidget->setItem(row_i, 7, NULL);
        }
    }
}

void b_bagd::on_pushButton_6_clicked() //保存或导出
{
    xst->sendMsg("你没有此权限");
    return;
    if(isSaveOrExport_b){//判断是保存还是导出
        QString sql_str;
        if(xst->ifIni_b)xst->iniDB();//初始化数据库工具
        sql_str = ysql_str;//更改操作方式
        int j = 0;

        QRegExp int_qre("[0-9]*"); //sql安全性检测
        if(isInsOrDel_b){ //插入或删除
            int temp_i = ui->tableWidget->rowCount() - 1;//忽略最后一行空行
            int i; //j是记录有多少条数据需要更改
            for (i = 0; i < temp_i; i++) {
                if(NULL != ui->tableWidget->item(i, 7) && NULL != ui->tableWidget->item(i, 6)){
                    if(! int_qre.exactMatch(ui->tableWidget->item(i, 6)->text())){
                        xst->sendMsg(QString::fromLocal8Bit("\u7b2c").append(QString::number(i+1, 10)).append(QString::fromLocal8Bit("\u884c\u65f6\u6548\u51fa\u9519"))); //第i行时效出错
                        return;
                    }
                    if(! QDateTime().fromString(ui->tableWidget->item(i, 7)->text(), "yyyy-MM-dd HH:mm:ss").isValid()){
                        xst->sendMsg(QString::fromLocal8Bit("\u7b2c").append(QString::number(i+1, 10)).append(QString::fromLocal8Bit("\u884c\u65e5\u671f\u683c\u5f0f\u51fa\u9519"))); //第i行日期格式出错
                        return;
                    }
                    sql_str.append("(").append(ui->tableWidget->item(i, 0)->text()).append(",").append(ui->tableWidget->item(i, 6)->text()).append(",\'").append(ui->tableWidget->item(i, 7)->text()).append("\'),");
                    j++;
                }
            }
            if(j == 0){
                xst->sendMsg(QString::fromLocal8Bit("\u6ca1\u6709\u9009\u62e9\u4efb\u4f55\u4e00\u884c"));//没有选择任何一行
                return;
            }
            sql_str = sql_str.left(sql_str.length() - 1);//删除最后的逗号
        }else {
            sql_str.append("(");
            int temp_i = ui->tableWidget->rowCount() - 1;//忽略最后一行空行
            int i; //j是记录有多少条数据需要更改
            for (i = 0; i < temp_i; i++) {
                if((NULL == ui->tableWidget->item(i, 7) || NULL == ui->tableWidget->item(i, 6) )&& NULL != ui->tableWidget->item(i, 0)){
                    sql_str.append(ui->tableWidget->item(i, 0)->text()).append(",");
                    j++;
                }
            }
            if(j == 0){
                xst->sendMsg(QString::fromLocal8Bit("\u6ca1\u6709\u9009\u62e9\u4efb\u4f55\u4e00\u884c"));//没有选择任何一行
                return;
            }
            sql_str = sql_str.left(sql_str.length() - 1);//删除最后的逗号
            sql_str.append(")");
        }
        qDebug() << sql_str;
        xst->saveData(sql_str);
        xst->sendMsg(QString::fromLocal8Bit("\u66f4\u6539\u4e86").append(QString::number(j, 10).append(QString::fromLocal8Bit("\u884c"))));//更改了j行
        on_pushButton_5_clicked();
    }else {
        //Export Excel
        int row_i = ui->tableWidget->rowCount() - 1;//总行数
        int col_i = ui->tableWidget->columnCount();//总列数
        if(! isExist_b)col_i--; //判断是否点击了已归档或未归档记录，因为导出未归档记录会有NULL的Item

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
            }
            l_l.push_back(temp_str);
        }
        QTextEdit date_te;
        for (int i = 0; i < l_l.size(); i++) {
            date_te.append(l_l.at(i));
        }

        x_file_tool *xft;
        xft = new x_file_tool();
        qDebug() << xft->setPath("");
        xft->setPath(this, QString("").append(QDate::currentDate().toString("yyyy-MM-dd")).append(".xls"));
        qDebug() << xft->filePath_str;
        xft->writeFile(date_te.document()->toPlainText());
        delete xft;
    }
}

void b_bagd::on_pushButton_clicked() //未归档
{
    isSaveOrExport_b = true;
    isInsOrDel_b = true;
    ui->pushButton_6->setText("保存");//保存
    ui->lineEdit_3->setText("未归档病历");
    ui->lineEdit_3->setStyleSheet("border: 2px solid;padding:2px;border-radius: 6px;color:red;border-color:red;");
    xsql_i = 6;
    xsql_str = "SELECT * FROM nhis.dbo.b_bagd_w WHERE ";
    ysql_str = "INSERT INTO nhis.dbo._b_bagd_date(InVisitId, Timeliness, RecTime) VALUES ";
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->tableWidget->clearContents();
}

void b_bagd::on_pushButton_2_clicked() //已回收
{
    isSaveOrExport_b = true;
    isInsOrDel_b = false;
    ui->pushButton_6->setText("保存");//保存
    ui->lineEdit_3->setText("查询已回收病历");
    ui->lineEdit_3->setStyleSheet("border: 2px solid;padding:2px;border-radius: 6px;color:#495A80;border-color:#495A80;");
    xsql_i = 7;
    xsql_str = "SELECT * FROM nhis.dbo.b_bagd_y WHERE ";
    ysql_str = "DELETE FROM nhis.dbo._b_bagd_date WHERE InVisitId IN ";
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->tableWidget->clearContents();
}

void b_bagd::on_pushButton_3_clicked()
{
    isSaveOrExport_b = false;
    isExist_b = true;
    ui->pushButton_6->setText("导出");//导出
    ui->lineEdit_3->setText("导出未归档病历");
    ui->lineEdit_3->setStyleSheet("border: 2px solid;padding:2px;border-radius: 6px;color:#CC2F69;border-color:#CC2F69;background-color:#FAFFEB;");
    xsql_i = 6;
    xsql_str = "SELECT * FROM nhis.dbo.b_bagd_w WHERE ";
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(true);
    ui->tableWidget->clearContents();
}

void b_bagd::on_pushButton_4_clicked()
{
    isSaveOrExport_b = false;
    isExist_b = false;
    ui->pushButton_6->setText("导出");//导出
    ui->lineEdit_3->setText("导出已回收病历");
    ui->lineEdit_3->setStyleSheet("border: 2px solid;padding:2px;border-radius: 6px;color:#7F1874;border-color:#7F1874;background-color:#DDF0ED;");
    xsql_i = 7;
    xsql_str = "SELECT * FROM nhis.dbo.b_bagd_y WHERE ";
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(false);
    ui->tableWidget->clearContents();
}
