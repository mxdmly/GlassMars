#include "y_sbwljhyw.h"
#include "ui_y_sbwljhyw.h"
#include <y_sbwljhyw_thread.h>

int queryNum_i;//返回数据的查询编号
y_sbwljhyw_thread *yst; //新建线程避免查询冲突
QVector<QString> arStr1400_qv;
QVector<QString> arDoc1400_qv;
QVector<QString> arStr1600_qv;
QVector<QString> arDoc1600_qv;
x_doc myDoc;
y_sbwljhyw::y_sbwljhyw(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::y_sbwljhyw)
{
    ui->setupUi(this);
    //setBackgroundRole(QPalette::setColor(QPalette::Window, QColor(255, 192, 203, 255)));
    QString docTemp_str = myDoc.docRe1400_str;
    int docTemp_i = 1;
    while (docTemp_i >= 0) {
        docTemp_i = docTemp_str.indexOf("\|");
        arDoc1400_qv.append(docTemp_str.mid(0, docTemp_i));
        docTemp_str.remove(0, docTemp_i + 1);
    }
    docTemp_str = myDoc.docRe1600_str;
    docTemp_i = 1;
    while (docTemp_i >= 0) {
        docTemp_i = docTemp_str.indexOf("\|");
        arDoc1600_qv.append(docTemp_str.mid(0, docTemp_i));
        docTemp_str.remove(0, docTemp_i + 1);
    }
}

y_sbwljhyw::~y_sbwljhyw()
{
    delete ui;
}

void y_sbwljhyw::on_pushButton_clicked() //查询按钮
{
    queryNum_i = 1400;
    q1400();
}

void y_sbwljhyw::onReadData(int su_i, QString readDate_str){ //查询有结果后自动执行此函数
    QString temp1600_str = "";
    if(su_i != 0){ //查看是否成功返回数据
        xst->sendMsg(readDate_str);
    }else{
        switch (queryNum_i) {
        case 1400:
            arStr1400_qv = parser(readDate_str);
            ui->lineEdit_3->setText(arStr1400_qv.value(0)); //个人编号
            ui->lineEdit_2->setText(arStr1400_qv.value(4)); //姓名
            ui->lineEdit_4->setText(arStr1400_qv.value(26)); //参保类别
            ui->lineEdit_5->setText(arStr1400_qv.value(28)); //经办机构
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(arStr1400_qv.size() - 1);
            for (int var = 0; var < arStr1400_qv.size() - 1; ++var) { //排序后显示出来
                ui->tableWidget->setItem(var, 0, new QTableWidgetItem(arDoc1400_qv.value(var)));
                ui->tableWidget->setItem(var, 1, new QTableWidgetItem(arStr1400_qv.value(var)));
            }
            //ui->tableWidget->resizeColumnsToContents(); //设置自动列宽，setColumnWidth(3,200)设置固定列宽
            //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//拉伸
            //隐藏行号及以上ui调整可以在ui文件设置
            q1600();
            break;
        case 1600:
            arStr1600_qv = parser(readDate_str);
            for (int var = 0; var < arStr1600_qv.size() - 1; ++var) { //排序后显示出来
                if(arStr1600_qv.value(var).indexOf("\$") != -1){ //如果遇到$符号换到下一个item
                    temp1600_str.append("\n---------------------------------------------");
                    ui->listWidget_2->addItem(temp1600_str);
                    temp1600_str = "";
                    arStr1600_qv.value(var).remove(0, 2);
                    arStr1600_qv.remove(0, var);
                    var = 0;
                }
                temp1600_str.append(arDoc1600_qv.value(var) + "\t" + arStr1600_qv.value(var) + "\n");
            }
            ui->listWidget_2->addItem(temp1600_str);

            break;
        case 1710:
            break;
        default:
            break;
        }
    }
}

void y_sbwljhyw::q1400(){ // 参保人员基本信息（1400）0211
    QString str = "";
    if(! ui->lineEdit_3->text().isEmpty()){
        str = ui->lineEdit_3->text();
    }
    str.append("|");
    if(! ui->lineEdit->text().isEmpty()){
        str = str.append(ui->lineEdit->text());
    }
    xnt->onWriteData("1400", QString("441200^").append(str).append("|01"));
}

void y_sbwljhyw::q1600(){ //2.2.3.2.10医疗待遇审批信息查询(1600)
    queryNum_i = 1600;
    xnt->onWriteData("1600", QString("441200^").append(arStr1400_qv.value(0)).append("|14|||||||||"));
}

void y_sbwljhyw::q1710(){ //1710
    //xnt->onWriteData(queryNum_i, QString("441200^|").append(ui->lineEdit->text()).append("|01"));
}

QVector<QString> y_sbwljhyw::parser(QString input_str){ //解析器，输出有序的list
    QVector<QString> temp_qv;
    int iof_i = 1;
    input_str = input_str.trimmed();
    input_str.remove(QRegExp("[\\w,\\W]*\\^1\\^"));
    input_str.remove(QRegExp("\\^.*"));
    while (iof_i >= 0) {
        iof_i = input_str.indexOf("\|");
        temp_qv.append(input_str.mid(0, iof_i));
        input_str.remove(0, iof_i + 1);
    }
    return temp_qv;
}
