#include "y_zflcx.h"
#include "ui_y_zflcx.h"
#include <QXmlStreamReader>
#include <QDateTime>
#include <QDate>

y_zflcx::y_zflcx(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::y_zflcx)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate().addMonths(-1));
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->checkBox->setChecked(true);
    QRegExp le_qre("[0-9]{0,10}$");//使用正则表达式限制用户输入
    QValidator *le_qv = new QRegExpValidator(le_qre, this);
    ui->lineEdit->setValidator(le_qv);
}

y_zflcx::~y_zflcx()
{
    delete ui;
}

void y_zflcx::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();
    xft = new x_file_tool();
    QString sql_Str;
    int row_i = 0;
    float pzf_i = 0;
    float zf_i = 0;
    float tempxyf_i = 0;
    float allxyf_i = 0;
    float allzf_i = 0;
    float sum_i = 0;
    float sumxyf_i = 0;
    float sumzf_i = 0;

    xst->iniDB();
    xft->setPath(QApplication::applicationDirPath() + "\\doc");
    sql_Str = xst->openSqlFile(QApplication::applicationDirPath() + "\\sql\\y_zflcx.sql");
    sql_Str.append(" AND AdmitDT >= \'").append(ui->dateEdit->date().toString("yyyy-MM-dd")).append("\'");
    sql_Str.append(" AND DischargeDT <= \'").append(ui->dateEdit_2->date().toString("yyyy-MM-dd")).append("\'");
    if(ui->checkBox->isChecked()){
        sql_Str.append(" ORDER BY NEWID() ");
        sql_Str.insert(6, QString(" TOP ").append(ui->lineEdit->text()).append(" "));
    }
    QSqlQuery qsq = xst->getData(sql_Str);
    ui->tableWidget->setRowCount(qsq.numRowsAffected() + 1);
    while (qsq.next()) {
        ui->tableWidget->setItem(row_i, 0, new QTableWidgetItem(qsq.value(0).toString()));
        ui->tableWidget->setItem(row_i, 1, new QTableWidgetItem(qsq.value(1).toString()));
        ui->tableWidget->setItem(row_i, 2, new QTableWidgetItem(QDateTime(qsq.value(2).toDateTime()).toString("yyyy-MM-dd")));
        ui->tableWidget->setItem(row_i, 3, new QTableWidgetItem(QDateTime(qsq.value(3).toDateTime()).toString("yyyy-MM-dd")));
        ui->tableWidget->setItem(row_i, 4, new QTableWidgetItem(QString::number(qsq.value(4).toFloat())));
        pzf_i = 0;
        zf_i = 0;
        allxyf_i = 0;
        allzf_i = 0;

        QXmlStreamReader reader; //解析XML用
        reader.addData(qsq.value(5).toString());
        while (! reader.atEnd()) { //不是末尾标签就继续，一个一个读下去，不区分包含关系
            reader.readNext();
            if(reader.name() == "Amt"){
                tempxyf_i = reader.readElementText().toFloat();
            }else if (reader.name() == "PartSelfPayAmt") {
                pzf_i = reader.readElementText().toFloat();
            }else if (reader.name() == "SelfPayAmt") {
                zf_i = reader.readElementText().toFloat();
            }else if (reader.name() == "SiFeeType") {
                if(11 == reader.readElementText().toInt()){
                    allzf_i = allzf_i + zf_i;
                    allxyf_i += tempxyf_i;
                }
            }
        }
        sumxyf_i += allxyf_i;
        sumzf_i += allzf_i;
        sum_i += qsq.value(4).toFloat();

        ui->tableWidget->setItem(row_i, 5, new QTableWidgetItem(QString::number(allxyf_i, 'f', 2)));
        ui->tableWidget->setItem(row_i, 6, new QTableWidgetItem(QString::number(allzf_i, 'f', 2)));
        row_i++;
    }
    ui->tableWidget->setItem(row_i, 0, new QTableWidgetItem("合计"));
    ui->tableWidget->setItem(row_i, 4, new QTableWidgetItem(QString::number(sum_i, 'f', 2)));
    ui->tableWidget->setItem(row_i, 5, new QTableWidgetItem(QString::number(sumxyf_i, 'f', 2)));
    ui->tableWidget->setItem(row_i, 6, new QTableWidgetItem(QString::number(sumzf_i, 'f', 2)));
}

void y_zflcx::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->lineEdit->setEnabled(false);
    }else {
        ui->lineEdit->setEnabled(true);
    }
}
