#include "y_sbwljhyw.h"
#include "ui_y_sbwljhyw.h"
#include <y_sbwljhyw_thread.h>
#include <y_sbwljhyw_dialog.h>
#include <main_loading.h>
#include <main_loading_thread.h>
#include <windows.h>

#include <QMenu>
#include <QAction>
#include <QModelIndex>
#include <QStandardItem>

int queryNum_i;//返回数据的查询编号
int category_i;//煞笔的社保系统分个球的分
int queryStatus_i;//查询的状态，用于更新进度条
bool isAlone1600_b;
y_sbwljhyw_thread *yst; //新建线程避免查询冲突
QVector<QString> arStr1400_qv;
QVector<QString> arDoc1400_qv;
QVector<QString> arStr1600_qv;
QVector<QString> arStr1600temp_qv;
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

    ui->listWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);

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
    arStr1600temp_qv.clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();


    queryStatus_i = 1;
    QString upBar_str = "正在查询个人信息";
    int i = 0, time_i = 0;
    float j = 0;
    q1400();
    while (isLoadingRun) {
        switch (queryStatus_i) {
        case 0:
            isLoadingRun = false;
            break;
        case 1:
            my_ml->updateProgressBar(i, "正在查询个人信息");
            break;
        case 1400:
            upBar_str = "正在查询特门审批信息";
            queryStatus_i = 1;
            i = 40;
            category_i = 14;
            isAlone1600_b = false;
            q1600(category_i);
            break;
        case 1614:
            upBar_str = "正在查询特门审批信息";
            i = 60;
            queryStatus_i = 1;
            break;
        case 1622:
            upBar_str = "正在查询在院信息";
            i = 70;
            queryStatus_i = 1;
            break;
        case 1613:
            upBar_str = "正在查询住院信息";
            i = 80;
            queryStatus_i = 1;
            q1710();
            break;
        case 1710:
            isLoadingRun = false;
            break;
        default:
            my_ml->updateProgressBar(99, "查询完毕，正在整理");
            break;
        }
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        Sleep(50);//至少留30秒
        if(time_i < 600){
            time_i++;
            j += 0.1;
            i = j;
        }else{
            isLoadingRun = false;
            xst->sendMsg("超时        ");
        }
    }
    closeLoading();
}

void y_sbwljhyw::onReadData(int su_i, QString readDate_str){ //查询有结果后自动执行此函数
    QString temp1600_str = "";
    QString temp1710_str = "";
    QString temp3110_str = "";
    switch (queryNum_i) {
    case 1400:
        if(su_i != 0){ //查看是否成功返回数据
            xst->sendMsg(readDate_str.remove("\^"));
            queryStatus_i = 0;
            //closeLoading();
        }else{
            arStr1400_qv = parser(readDate_str);
            ui->lineEdit->setText(arStr1400_qv.value(3)); //更新身份证，因为有些时候会用个人编号查询
            ui->lineEdit_3->setText(arStr1400_qv.value(0)); //个人编号
            ui->lineEdit_2->setText(arStr1400_qv.value(4)); //姓名
            ui->lineEdit_4->setText(arStr1400_qv.value(26)); //参保类别
            ui->lineEdit_5->setText(arStr1400_qv.value(28)); //经办机构
            switch (arStr1400_qv.value(11).toInt()) {
            case 1:
                ui->lineEdit_6->setText("参保缴费"); //参保状态
                break;
            case 2:
                ui->lineEdit_6->setText("暂停参保");
                ui->lineEdit_6->setStyleSheet("background:yellow;");
                break;
            case 3:
                ui->lineEdit_6->setText("终止参保");
                ui->lineEdit_6->setStyleSheet("background:red;color:white;");
                break;
            default:
                break;
            }
            ui->tableWidget->setRowCount(arStr1400_qv.size() - 1);
            for (int var = 0; var < arStr1400_qv.size() - 1; ++var) { //排序后显示出来
                ui->tableWidget->setItem(var, 0, new QTableWidgetItem(arDoc1400_qv.value(var)));
                ui->tableWidget->setItem(var, 1, new QTableWidgetItem(arStr1400_qv.value(var)));
            }
            //ui->tableWidget->resizeColumnsToContents(); //设置自动列宽，setColumnWidth(3,200)设置固定列宽
            //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//拉伸
            //隐藏行号及以上ui调整可以在ui文件设置
            queryStatus_i = 1400;
            temp1600_qw = ui->listWidget_2;
            //1600;
        }
        break;
    case 1600:
        if(su_i != 0){ //查看是否成功返回数据
            ;
        }else{
            if(temp1600_qw->count() > 0)temp1600_qw->addItem("-----------------------------"); //如果之前有数据而此次查询又有新增的数据，就用线隔开
            arStr1600_qv = parser(readDate_str);
            for (int var = 0; var < arStr1600_qv.size() - 1; ++var) { //排序后显示出来
                arStr1600temp_qv.append(QString::number(category_i));
                arStr1600temp_qv.append(arStr1600_qv.value(var + 4));
                arStr1600temp_qv.append(arStr1600_qv.value(var + 5));
                arStr1600temp_qv.append(arStr1600_qv.value(var + 6));
                arStr1600temp_qv.append(arStr1600_qv.value(var + 7));
                if(arStr1600_qv.value(var).indexOf("\$") != -1){ //如果遇到$符号换到下一个item
                    temp1600_qw->addItem(temp1600_str);
                    temp1600_qw->addItem("-----------------------------");
                    temp1600_str = "";
                    arStr1600_qv.replace(var, arStr1600_qv.value(var).remove(0, 1));
                }
                if(arStr1600_qv.value(var + 0) == "1"){
                    temp1600_str.append("√审批通过");
                    //temp1600_qw->item(0)->setBackgroundColor();
                }else {
                    temp1600_str.append("×未审批");
                }
                temp1600_str.append("\t" + arStr1600_qv.value(var + 4) + arStr1600_qv.value(var + 5) + "\n");
                if(arStr1600_qv.value(var + 7).isEmpty()){
                    temp1600_str.append(QDate::fromString(arStr1600_qv.value(var + 6), "yyyyMMdd").toString("yyyy年MM月dd日") + " - 长期有效");
                }else{
                    temp1600_str.append(QDate::fromString(arStr1600_qv.value(var + 6), "yyyyMMdd").toString("yyyy年MM月dd日") + " - " + QDate::fromString(arStr1600_qv.value(var + 7), "yyyyMMdd").toString("yyyy年MM月dd日"));
                }
                temp1600_str.append("\n" + arStr1600_qv.value(var + 3));
                var = var + 10;
            }
            temp1600_qw->addItem(temp1600_str);
        }
        if(category_i == 14){
            category_i = 22;
            queryStatus_i = 1614;
            q1600(category_i);
        }else if(category_i == 22){
            if(ui->listWidget_2->count() <= 0 && su_i != 0){
                ui->listWidget_2->addItem(readDate_str.remove("\^"));
            }
            temp1600_qw = ui->listWidget_3;
            category_i = 13;
            queryStatus_i = 1622;
            if(! isAlone1600_b){//更新特门信息的自主查询而，或是点击查询按钮的全面信息查询
                q1600(category_i);
            }
        }else if(category_i == 13){ //&& su_i != 0
            if(su_i != 0){
                ui->listWidget_3->addItem(readDate_str.remove("\^")); //查询不到会返回负数，在此获取信息并显示
            }
            qDebug() << arStr1400_qv;
            if(arStr1400_qv.value(16) == "0" | arStr1400_qv.value(16) == ""){ //1600做完后就开始查询住院情况，0是不在院，1是在院
                ui->listWidget_4->addItem("不在院");
                queryStatus_i = 0;
                //closeLoading();
            }else {
                queryStatus_i = 1613;
                //1710;
            }
        }
        break;
    case 1710:
        arStr1710_qv = parser(readDate_str);
        temp1710_str.append(arStr1710_qv.value(7)).append("  ").append(arStr1710_qv.value(8)).append("\n");
        temp1710_str.append(arStr1710_qv.value(3)).append("\t").append(arStr1710_qv.value(9)).append("\n");
        temp1710_str.append(QDateTime::fromString(arStr1710_qv.value(6), "yyyyMMddHHmmss").toString("yyyy年MM月dd日 HH时mm分ss秒")).append(" 入院");
        ui->listWidget_4->addItem(temp1710_str);
        queryStatus_i = 0;
        //closeLoading();
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
        //ui->lineEdit_2->setText(temp3110_str);//return;
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
            category_i = 14;
            isAlone1600_b = true;
            ui->listWidget_2->clear();
            temp1600_qw = ui->listWidget_2;
            arStr1600temp_qv.clear();
            q1600(14);
        }
        msgBox->show();
        break;
    case 3120:
        QMessageBox *msgBox_1;
        if(su_i != 0){ //查看是否成功返回数据
            msgBox_1 = new QMessageBox("社保返回提示框",
                    QString(readDate_str).remove("^"),
                    QMessageBox::Critical,
                    QMessageBox::NoButton,QMessageBox::Ok | QMessageBox::Escape,0);
        }else {
            msgBox_1 = new QMessageBox("社保返回提示框",
                    "成功",QMessageBox::NoIcon,
                    QMessageBox::NoButton,QMessageBox::Ok | QMessageBox::Escape,0);
            category_i = 14;
            isAlone1600_b = true;
            ui->listWidget_2->clear();
            temp1600_qw = ui->listWidget_2;
            arStr1600temp_qv.clear();
            q1600(14);
        }
        msgBox_1->show();
        break;
    default:
        break;
    }
}

void y_sbwljhyw::closeLoading(){
    isLoadingRun = false;//关闭进度条
    my_ml->updateProgressBar(100);
    Sleep(200);
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

void y_sbwljhyw::q3120(QStringList uploadData_sl){ //3.2.3.4.2.3医院审批信息上报撤销(3120)
    queryNum_i = 3120;
    QString temp_str;
    if(uploadData_sl.size() > 0 & uploadData_sl.value(0) != ""){
        for (int i = 0; i < uploadData_sl.size(); ++i) {
            temp_str.append(uploadData_sl.value(i)).append("|");
        }
        //qDebug() << QString("441200^").append(temp_str).append("||||||||||");
        temp_str.remove(" ");
        temp_str.remove("-");
        temp_str.remove(":");
        xnt->onWriteData("3120", QString("441200^").append(temp_str));
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

void y_sbwljhyw::on_listWidget_2_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    //添加菜单项，指定图标、名称、响应函数
    if(ui->listWidget_2->itemAt(pos) != NULL && ui->listWidget_2->currentRow() % 2 == 0){
        menu.addAction(QStringLiteral("撤销上传"),this,SLOT(on_rightMenuClick()));
        menu.addAction(QStringLiteral("----------"));
        menu.addAction(QStringLiteral("复制"));
        menu.addAction(QStringLiteral("取消"));
    }else{
        menu.addAction(QStringLiteral("我要飞得更高，飞得更高ヾ(≧O≦)〃嗷~"));
    }
    //在鼠标位置显示
    menu.exec(QCursor::pos());
}

void y_sbwljhyw::on_rightMenuClick(){
    QStringList uploadData_sl;
    int i = ui->listWidget_2->currentRow() / 2;//因为只有单数行有用
    int xs_i = 5; //系数，间隔记录用，一条记录有N个子项就乘以N再加1
    QString tempMsgBox_str;//显示在对话框中的文字
    QMessageBox msgBox;
    msgBox.setWindowTitle("撤销");
    if(arStr1600temp_qv.isEmpty()){
        msgBox.setText("没有要撤销的内容");
    }else{
        msgBox.setText("将要撤销的是：");
        /*if(arStr1600temp_qv.value(i * xs_i) == "14"){
            tempMsgBox_str.append("有限额");
        }else if(arStr1600temp_qv.value(i * xs_i) == "22"){
            tempMsgBox_str.append("无限额");
        }*/
        tempMsgBox_str.append("\n");
        tempMsgBox_str.append(arStr1600temp_qv.value(i * xs_i + 1));
        tempMsgBox_str.append(arStr1600temp_qv.value(i * xs_i + 2));
        msgBox.setInformativeText(tempMsgBox_str);
        QPushButton *connectButton = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
        QPushButton *cancelButton = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
        msgBox.exec();

        if (msgBox.clickedButton() == connectButton) {
            uploadData_sl.append(arStr1600temp_qv.value(i * xs_i));
            uploadData_sl.append(arStr1400_qv.value(0));
            uploadData_sl.append("");
            uploadData_sl.append(arStr1600temp_qv.value(i * xs_i + 1));
            uploadData_sl.append("");
            uploadData_sl.append("");
            uploadData_sl.append("");//备用，下同
            uploadData_sl.append("");
            uploadData_sl.append("");
            q3120(uploadData_sl);
        } else if (msgBox.clickedButton() == cancelButton) {
            // Cancel
        }
    }
}
