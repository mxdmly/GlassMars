#include "y_jbylbxtdbzmzsqdjjjb.h"
#include "ui_y_jbylbxtdbzmzsqdjjjb.h"

QSqlQuery y_sq;//储存查询数据库后返回的结果

y_jbylbxtdbzmzsqdjjjb::y_jbylbxtdbzmzsqdjjjb(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::y_jbylbxtdbzmzsqdjjjb)
{
    ui->setupUi(this);
    isIni_b = true;

    this->xft = new x_file_tool();

    ui->tableWidget->resizeColumnsToContents(); //设置自动列宽，setColumnWidth(3,200)设置固定列宽
    xft->setPath(QApplication::applicationDirPath() + "\\doc");
    QString str = xft->readFileText("doctors.ini");
    QJsonParseError *e = new QJsonParseError();
    QJsonArray ja = QJsonDocument::fromJson(str.toUtf8(), e).array();
    qDebug() << e->errorString();
    for (int i = 0; i < ja.size(); ++i) {
        //ja.at(i).toObject().value("department").toString();
        docsssItems_sl.append(ja.at(i).toObject().value("department").toString() + "-----------------");
        depItem_sl.append("");
        heaItem_sl.append("");
        docItem_sl.append("");
        QJsonArray doc_ja = ja.at(i).toObject().value("doctors").toArray();
        for (int var = 0; var < doc_ja.size(); ++var) {
            depItem_sl.append(ja.at(i).toObject().value("department").toString());
            heaItem_sl.append(ja.at(i).toObject().value("head").toString());
            docItem_sl.append(doc_ja.at(var).toString());
            docsssItems_sl.append("   " + doc_ja.at(var).toString());
        }
    }
    ui->comboBox->addItems(docsssItems_sl);
}

y_jbylbxtdbzmzsqdjjjb::~y_jbylbxtdbzmzsqdjjjb()
{
    y_sq.clear();
    delete ui;
}

void y_jbylbxtdbzmzsqdjjjb::on_pushButton_clicked()//查询
{
    int row_i = 0;
    QString sql_str;
    ui->tableWidget->clearContents();//清空表格中的内容(不包含表头)
    if(isIni_b){
        xst->iniDB();
        //qDebug() << xst->isDBopen;
        isIni_b = false;
    }
    sql_str = xst->openSqlFile(QApplication::applicationDirPath() + "\\sql\\y_jbylbxtdbzmzsqdjjjb.sql");
    if(ui->lineEdit->text() != "" && ui->lineEdit->text() != NULL){ //参保类型
        sql_str.append("AND NAME = \'").append(ui->lineEdit->text()).append("\' ");
    }
    switch (ui->comboBox_3->currentIndex()) { //参保类别
    case 0:
        break;
    case 1:
        sql_str.append("AND InsuredCategory = 11" );
        break;
    case 2:
        sql_str.append("AND InsuredCategory = 52" );
        break;
    default:
        break;
    }
    switch (ui->comboBox_2->currentIndex()) { //交接情况
    case 0:
        break;
    case 1:
        sql_str.append("AND ISUPLOAD = 0" );
        break;
    case 2:
        sql_str.append("AND ISUPLOAD = 11" );
        break;
    case 3:
        sql_str.append("AND ISUPLOAD = 10" );
        break;
    case 4:
        sql_str.append("AND ISUPLOAD = 2" );
        break;
    default:
        break;
    }
    y_sq = xst->getData(sql_str);
    ui->tableWidget->setRowCount(y_sq.numRowsAffected() + 1);
    QString temp_str;
    while (y_sq.next()) {
        for (int i = 0; i < 7; ++i) {
            ui->tableWidget->setItem(row_i, i, new QTableWidgetItem(y_sq.value(i).toString()));
        }
        temp_str = "";
        switch (y_sq.value(7).toInt()) {
        case 0:
            temp_str = "已上传";
            break;
        case 11:
            temp_str = "卡已收回但未领取";
            break;
        case 10:
            temp_str = "已领取";
            break;
        case -2:
            temp_str = "回退 / 作废";
            break;
        default:
            break;
        }
        ui->tableWidget->setItem(row_i, 7, new QTableWidgetItem(temp_str));
        ui->tableWidget->setItem(row_i, 8, new QTableWidgetItem(y_sq.value(8).toDateTime().toString("yyyy-MM-dd hh:ss:mm")));
        row_i++;
    }
    ui->tableWidget->resizeColumnsToContents(); //设置自动列宽，setColumnWidth(3,200)设置固定列宽
}
