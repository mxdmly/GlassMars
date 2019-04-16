#include "y_sbwljhyw.h"
#include "ui_y_sbwljhyw.h"
#include <y_sbwljhyw_thread.h>
#include <y_sbwljhyw_dialog.h>
#include <main_loading.h>
#include <main_loading_thread.h>
#include <windows.h>

int queryNum_i;//返回数据的查询编号
int category_i;//煞笔的社保系统分个球的分
y_sbwljhyw_thread *yst; //新建线程避免查询冲突
QVector<QString> arStr1400_qv;
QVector<QString> arDoc1400_qv;
QVector<QString> arStr1600_qv;
QVector<QString> arDoc1600_qv;
QVector<QString> arStr1710_qv;
QVector<QString> arDoc1710_qv;
QListWidget *temp1600_qw;
x_doc myDoc;

y_sbwljhyw::y_sbwljhyw(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::y_sbwljhyw)
{
    ui->setupUi(this);
    isIni_b = true;
    //setBackgroundRole(QPalette::setColor(QPalette::Window, QColor(255, 192, 203, 255)));
    //ui->pushButton_2->setStyleSheet("border: 2px solid;padding:2px;border-radius: 6px;color:red;border-color:red;");

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
    docTemp_str = myDoc.docRe1710_str;
    docTemp_i = 1;
    while (docTemp_i >= 0) {
        docTemp_i = docTemp_str.indexOf("\|");
        arDoc1710_qv.append(docTemp_str.mid(0, docTemp_i));
        docTemp_str.remove(0, docTemp_i + 1);
    }
}

y_sbwljhyw::~y_sbwljhyw()
{
    delete ui;
}

void y_sbwljhyw::on_pushButton_clicked() //查询按钮
{
    isLoadingRun = true;
    my_ml = new main_loading();
    my_ml->show();

    if(isIni_b){
        xst->iniDB();
        sql3110_str = xst->openSqlFile(QApplication::applicationDirPath() + "\\sql\\y_sbwljhyw.sql");
        isIni_b = false;
    }

    queryNum_i = 1400;
    arStr1400_qv.clear();
    ui->tableWidget->clearContents();
    arStr1600_qv.clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();

    q1400();
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    int i = 0;
    while (isLoadingRun) {
        my_ml->updateProgressBar(i);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        Sleep(i * 10);
        if(i < 99){
            i++;
        }else{
            isLoadingRun = false;
            delete my_ml;
            my_ml = NULL;
            xst->sendMsg("未知错误        ");
        }
    }
}

void y_sbwljhyw::onReadData(int su_i, QString readDate_str){ //查询有结果后自动执行此函数
    QString temp1600_str = "";
    QString temp1710_str = "";
    QString temp3110_str = "";
    switch (queryNum_i) {
    case 1400:
        if(su_i != 0){ //查看是否成功返回数据
            xst->sendMsg(readDate_str.remove("\^"));
            closeLoading();
        }else{
            arStr1400_qv = parser(readDate_str);
            ui->lineEdit->setText(arStr1400_qv.value(3)); //更新身份证，因为有些时候会用个人编号查询
            ui->lineEdit_3->setText(arStr1400_qv.value(0)); //个人编号
            ui->lineEdit_2->setText(arStr1400_qv.value(4)); //姓名
            ui->lineEdit_4->setText(arStr1400_qv.value(26)); //参保类别
            ui->lineEdit_5->setText(arStr1400_qv.value(28)); //经办机构
            ui->tableWidget->setRowCount(arStr1400_qv.size() - 1);
            for (int var = 0; var < arStr1400_qv.size() - 1; ++var) { //排序后显示出来
                ui->tableWidget->setItem(var, 0, new QTableWidgetItem(arDoc1400_qv.value(var)));
                ui->tableWidget->setItem(var, 1, new QTableWidgetItem(arStr1400_qv.value(var)));
            }
            //ui->tableWidget->resizeColumnsToContents(); //设置自动列宽，setColumnWidth(3,200)设置固定列宽
            //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//拉伸
            //隐藏行号及以上ui调整可以在ui文件设置
            category_i = 14;
            temp1600_qw = ui->listWidget_2;
            q1600(category_i);
        }
        break;
    case 1600:
        if(su_i != 0){ //查看是否成功返回数据
            ;
        }else{
            if(temp1600_qw->count() > 0)temp1600_qw->addItem("-----------------------------"); //如果之前有数据而此次查询又有新增的数据，就用线隔开
            arStr1600_qv = parser(readDate_str);
            for (int var = 0; var < arStr1600_qv.size() - 1; ++var) { //排序后显示出来
                if(arStr1600_qv.value(var).indexOf("\$") != -1){ //如果遇到$符号换到下一个item
                    temp1600_qw->addItem(temp1600_str);
                    temp1600_qw->addItem("-----------------------------");
                    temp1600_str = "";
                    arStr1600_qv.replace(var, arStr1600_qv.value(var).remove(0, 1));
                }
                if(arStr1600_qv.value(var + 0) == "1"){
                    temp1600_str.append("审批通过");
                }else {
                    temp1600_str.append("未审批");
                }
                temp1600_str.append("\t" + arStr1600_qv.value(var + 4) + arStr1600_qv.value(var + 5) + "\n");
                temp1600_str.append(arStr1600_qv.value(var + 3) + "\n");
                if(arStr1600_qv.value(var + 7).isEmpty()){
                    temp1600_str.append(QDate::fromString(arStr1600_qv.value(var + 6), "yyyyMMdd").toString("yyyy年MM月dd日") + " - 长期有效");
                }else{
                    temp1600_str.append(QDate::fromString(arStr1600_qv.value(var + 6), "yyyyMMdd").toString("yyyy年MM月dd日") + " - " + QDate::fromString(arStr1600_qv.value(var + 7), "yyyyMMdd").toString("yyyy年MM月dd日"));
                }
                var = var + 10;
            }
            temp1600_qw->addItem(temp1600_str);
        }
        if(category_i == 14){
            category_i = 22;
            q1600(category_i);
        }else if(category_i == 22){
            if(ui->listWidget_2->count() <= 0 && su_i != 0){
                ui->listWidget_2->addItem(readDate_str.remove("\^"));
            }
            temp1600_qw = ui->listWidget_3;
            category_i = 13;
            q1600(category_i);
        }else if(category_i == 13 && su_i != 0){
            ui->listWidget_3->addItem(readDate_str.remove("\^")); //查询不到会返回负数，在此获取信息并显示
            if(arStr1400_qv.value(16) == 0){ //1600做完后就开始查询住院情况，0是不在院，1是在院
                ui->listWidget_4->addItem("不在院");
                closeLoading();
            }else {
                q1710();
            }
        }
        break;
    case 1710:
        arStr1710_qv = parser(readDate_str);
        temp1710_str.append(arStr1710_qv.value(7)).append("  ").append(arStr1710_qv.value(8)).append("\n");
        temp1710_str.append(arStr1710_qv.value(3)).append("\t").append(arStr1710_qv.value(9)).append("\n");
        temp1710_str.append(QDateTime::fromString(arStr1710_qv.value(6), "yyyyMMddHHmmss").toString("yyyy年MM月dd日 HH时mm分ss秒")).append(" 入院");
        ui->listWidget_4->addItem(temp1710_str);
        closeLoading();
        break;
    case 3110:
        temp3110_str = sql3110_str + QString("\'").append(QString::number(su_i)).append("\',");
        for (int i = 0; i < uploadData_sl.size(); ++i) {
            temp3110_str.append("\'").append(uploadData_sl.value(i)).append("\',");
        }
        temp3110_str.append("\'").append(readDate_str).append("\',");
        temp3110_str.append("\'").append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:ss:mm")).append("\'");
        temp3110_str.append(")");
        //ui->lineEdit->setText(temp3110_str);
        xst->saveData(temp3110_str);
        QMessageBox *msgBox;
        if(su_i != 0){ //查看是否成功返回数据
            msgBox = new QMessageBox("社保返回提示框",         ///--这里是设置消息框标题
                    QString(readDate_str).remove("^"),                               ///--这里是设置消息框显示的内容
                    QMessageBox::Critical,                      ///--这里是在消息框显示的图标
                    QMessageBox::NoButton,     ///---这里是显示消息框上的按钮情况
                    QMessageBox::Ok | QMessageBox::Escape,  ///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
                    0);
        }else {
            msgBox = new QMessageBox("社保返回提示框",         ///--这里是设置消息框标题
                    "成功",                               ///--这里是设置消息框显示的内容
                    QMessageBox::NoIcon,                      ///--这里是在消息框显示的图标
                    QMessageBox::NoButton,     ///---这里是显示消息框上的按钮情况
                    QMessageBox::Ok | QMessageBox::Escape,  ///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
                    0);
        }
        msgBox->show();
        break;
    default:
        break;
    }
}

void y_sbwljhyw::closeLoading(){
    isLoadingRun = false;//关闭进度条
    my_ml->updateProgressBar(100);
    Sleep(500);
    delete my_ml;
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

void y_sbwljhyw::q1600(int category_i){ //2.2.3.2.10医疗待遇审批信息查询(1600)category_i类别,14特门有限额、22特门无限额、13转诊
    queryNum_i = 1600;
    xnt->onWriteData("1600", QString("441200^").append(arStr1400_qv.value(0)).append("|").append(QString::number(category_i, 10)).append("|||||||||"));
}

void y_sbwljhyw::q1710(){ //2.2.3.2.11在院状态查询(1710)
    queryNum_i = 1710;
    xnt->onWriteData("1710", QString("441200^").append(arStr1400_qv.value(0)).append("|||||"));
}

void y_sbwljhyw::q3110(QStringList uploadData_sl){ //3.2.3.4.2.1医院审批信息上报(3110)
    queryNum_i = 3110;
    QString temp_str, temp2_str;
    if(uploadData_sl.size() > 0 & uploadData_sl.value(0) != ""){
        for (int i = 0; i < 6; ++i) {
            temp2_str.append(uploadData_sl.value(i)).append("|");
        }
        for (int i = 6; i < uploadData_sl.size(); ++i) {
            temp_str.append(uploadData_sl.value(i)).append("|");
        }
        //qDebug() << QString("441200^").append(temp_str).append("||||||||||");
        temp_str.remove(" ");
        temp_str.remove("-");
        temp_str.remove(":");
        temp2_str.append(temp_str);
        xnt->onWriteData("3110", QString("441200^").append(temp2_str).append("||||||||||"));
    }
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

void y_sbwljhyw::on_pushButton_2_clicked() //特门登记弹出框
{
    y_sbwljhyw_dialog *xsd = new y_sbwljhyw_dialog();
    connect(xsd, &y_sbwljhyw_dialog::sendUploadData, this, &y_sbwljhyw::getUploadData);
    xsd->setQV(arStr1400_qv);
    xsd->setXST(xst);
    xsd->exec();
}

void y_sbwljhyw::on_lineEdit_textEdited(const QString &arg1)
{
    ui->lineEdit_3->clear();
}

void y_sbwljhyw::getUploadData(QStringList uploadData_sl){ //按下OK就可以获得信息
    this->uploadData_sl = uploadData_sl;
    q3110(uploadData_sl);
}


void y_sbwljhyw::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}


void y_sbwljhyw::on_lineEdit_3_returnPressed()
{
    on_pushButton_clicked();
}
