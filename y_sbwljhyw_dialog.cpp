#include "y_sbwljhyw_dialog.h"
#include "ui_y_sbwljhyw_dialog.h"
#include <QDebug>
#include <windows.h>
#include <y_sbwljhyw_thread.h>

using namespace std;

y_sbwljhyw_thread *lcd_t;

y_sbwljhyw_dialog::y_sbwljhyw_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::y_sbwljhyw_dialog)
{
    ui->setupUi(this);
    xft = new x_file_tool();
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm:ss"));
    ui->dateEdit->setDate(QDate::currentDate()); //停止日期

    BZ_index_i = 0;

    lcd_t = new y_sbwljhyw_thread();
    lcd_t->lcd = ui->lcdNumber;
    lcd_t->start();
}

y_sbwljhyw_dialog::~y_sbwljhyw_dialog()
{
    delete ui;
}

void y_sbwljhyw_dialog::setQV(QVector<QString> qv){
    this->qv = qv;
    ui->lineEdit->setText(qv.value(4)); //姓名
    ui->lineEdit_2->setText(qv.value(26)); //？？
    ui->lineEdit_3->setText(qv.value(0)); //个人编号#
}

void y_sbwljhyw_dialog::setXST(x_sql_tool *xst){
    this->xst = xst;
    this->xft = new x_file_tool();
    if(! qv.isEmpty()){
        xst->iniDB();
        QSqlQuery qsq = xst->getData(xst->openSqlFile(QApplication::applicationDirPath() + "\\sql\\y_sbwljhyw_c.sql") + qv.value(0) + "\' ORDER BY nhis.dbo.ZhaoQingInVisitSiReg.VisitId DESC");
        qDebug() << QString(xst->openSqlFile(QApplication::applicationDirPath() + "\\sql\\y_sbwljhyw_c.sql") + qv.value(0) + "\' ORDER BY nhis.dbo.ZhaoQingInVisitSiReg.VisitId DESC");
        if(qsq.numRowsAffected() >= 1){
            ui->comboBox_2->setItemText(0, "自动获取成功");
            qsq.next();
            ui->lineEdit_4->setText(qsq.value(1).toString());
            KS_str = qsq.value(3).toString(); //科室
            ui->lineEdit_7->setText(qsq.value(2).toString());
        }else {
            qsq = xst->getData(xst->openSqlFile(QApplication::applicationDirPath() + "\\sql\\y_sbwljhyw_c.sql") + qv.value(0) + "\' ORDER BY nhis.dbo.ZhaoQingInVisitSiReg.VisitId DESC");
            if(qsq.numRowsAffected() >= 1){
                ui->comboBox_2->setItemText(0, "自动获取成功");
                qsq.next();
                ui->lineEdit_4->setText(qsq.value(1).toString());
                KS_str = qsq.value(3).toString(); //科室
                ui->lineEdit_7->setText(qsq.value(2).toString());
            }else {
                ui->comboBox_2->setItemText(0, "获取失败，请手动选择");
            }
        }
        ui->lineEdit_10->setText(KS_str);
    }
    xft->setPath(QApplication::applicationDirPath() + "\\doc");
    QString str = xft->readFileText("doctors.ini");
    QJsonParseError *e = new QJsonParseError();
    QJsonArray ja = QJsonDocument::fromJson(str.toUtf8(), e).array();
    //qDebug() << e->errorString();
    for (int i = 0; i < ja.size(); ++i) {
        if(ja.at(i).toObject().value("department").toString() == KS_str){ //用科室筛选主任
            ui->lineEdit_8->setText(ja.at(i).toObject().value("head").toString());
        }
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
    ui->comboBox_2->addItems(docsssItems_sl);

    str = xft->readFileText("SpecificDiseaseClinicSign.ini");
    e = new QJsonParseError();
    ja = QJsonDocument::fromJson(str.toUtf8(), e).array();
    qDebug() << e->errorString();
    for (int i = 0; i < ja.size(); ++i) {
        if(i == 0){
            hairItems_sl.append("常见特门有限额-------------------------------------");
            ClassificationName_sl.append("");
            CodeName_sl.append("");
            CodeValue_sl.append("");
            ValidityPeriod_list.append(0);
        }else if(i == 1){
            hairItems_sl.append("特门无限额-----------------------------------------");
            ClassificationName_sl.append("");
            CodeName_sl.append("");
            CodeValue_sl.append("");
            ValidityPeriod_list.append(0);
        }else if(i == 2){
            hairItems_sl.append("其他特门有限额-------------------------------------");
            ClassificationName_sl.append("");
            CodeName_sl.append("");
            CodeValue_sl.append("");
            ValidityPeriod_list.append(0);
        }
        QJsonArray CodeName_ja = ja.at(i).toObject().value("CodeName").toArray();
        QJsonArray CodeValue_ja = ja.at(i).toObject().value("CodeValue").toArray();
        QJsonArray ValidityPeriod_ja = ja.at(i).toObject().value("ValidityPeriod").toArray();
        for (int var = 0; var < CodeName_ja.size(); ++var) {
            ClassificationName_sl.append(ja.at(i).toObject().value("ClassificationName").toString());
            CodeName_sl.append(CodeName_ja.at(var).toString());
            CodeValue_sl.append(CodeValue_ja.at(var).toString());
            ValidityPeriod_list.append(ValidityPeriod_ja.at(var).toInt());
            hairItems_sl.append(CodeValue_ja.at(var).toString() + "\t" + CodeName_ja.at(var).toString());
        }
    }
    ui->comboBox->addItems(hairItems_sl);
}

QJsonArray y_sbwljhyw_dialog::acText(QString fileName_str){ //获取json用
    xft->setPath(QApplication::applicationDirPath() + "\\doc");
    QString str = xft->readFileText(fileName_str);
    QJsonParseError *e = new QJsonParseError();
    QJsonArray ja = QJsonDocument::fromJson(str.toUtf8(), e).array();
    return ja;
}

void y_sbwljhyw_dialog::on_comboBox_2_activated(int index)
{
    Doc_index_i = index;
    if(index == 0){
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_10->clear();
    }else{
        ui->lineEdit_7->setText(docItem_sl.at(index - 1));
        ui->lineEdit_8->setText(heaItem_sl.at(index - 1));
        KS_str = depItem_sl.value(index - 1);
        ui->lineEdit_10->setText(KS_str);
    }
}

void y_sbwljhyw_dialog::on_comboBox_activated(int index)
{
    BZ_index_i = index;
    QJsonArray acText_ja = acText("acText.json");
    acText_ja;
    for (int i = 0; i < acText_ja.size(); ++i) {
        if(acText_ja.at(i).toObject().value("title").toString() == CodeName_sl.at(index)){ //用科室筛选主任
            ui->lineEdit_8->setText(acText_ja.at(i).toObject().value("head").toString());
        }

    }




    //ui->lineEdit_5->setText(CodeValue_sl.at(index));
    //ui->lineEdit_6->setText(CodeName_sl.at(index));
    ui->textEdit->setText(CodeName_sl.at(index));
    switch (index) {
    case 1:
        ui->textEdit->setText("高血压病");
        ui->textEdit_2->setText("患者有高血压病史，多次测血压高，血压最高  /  mmHg，需长期服药治疗。");
        break;
    case 2:
        ui->textEdit_2->setText("患者烦渴、多饮、多尿，多次测血糖高，血糖  mmol/L、  mmol/L，需长期服药治疗。");
        break;
    default:
        break;
    }
}

void y_sbwljhyw_dialog::on_buttonBox_accepted()
{ 
    lcd_t->isRun_boo = false;
    while (lcd_t->isRunning()) {
        Sleep(200);
    }
    delete lcd_t;

    if(BZ_index_i == NULL | BZ_index_i == 0 | BZ_index_i == 5 | BZ_index_i == 8 ){
        xst->sendMsg("请正确地选择病种");
    }else if(ui->lineEdit_4->text().isNull() ){
        xst->sendMsg("填写电话号码");
    }else{
        KS_str = ui->lineEdit_10->text();
        QStringList uploadData_sl;
        uploadData_sl.append(qv.value(0));
        uploadData_sl.append(ClassificationName_sl.value(BZ_index_i));
        uploadData_sl.append("");
        uploadData_sl.append("");
        uploadData_sl.append(CodeValue_sl.at(BZ_index_i));
        uploadData_sl.append(CodeName_sl.at(BZ_index_i));
        uploadData_sl.append("情况属实，同意办理。");
        uploadData_sl.append("");
        uploadData_sl.append("");
        uploadData_sl.append("");
        uploadData_sl.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        uploadData_sl.append(QDateTime(ui->dateTimeEdit->dateTime()).toString("yyyy-MM-dd HH:mm:ss"));
        if(ValidityPeriod_list.value(BZ_index_i) != 0){ //有效期
            uploadData_sl.append(QDateTime(ui->dateTimeEdit->dateTime()).addYears(ValidityPeriod_list.value(BZ_index_i)).toString("yyyy-MM-dd HH:mm:ss"));
        }else {
            uploadData_sl.append("");
        }
        uploadData_sl.append("医保办");
        uploadData_sl.append("");
        uploadData_sl.append("");
        uploadData_sl.append("100007");
        uploadData_sl.append("肇庆市端州区人民医院");
        uploadData_sl.append("");
        uploadData_sl.append("");
        uploadData_sl.append("");
        uploadData_sl.append("");
        uploadData_sl.append(ui->lineEdit_4->text());
        uploadData_sl.append("");
        uploadData_sl.append("");
        uploadData_sl.append(qv.value(4));
        uploadData_sl.append(qv.value(3));
        uploadData_sl.append(qv.value(6));
        uploadData_sl.append(QString::number(QDate::currentDate().year() - qv.value(7).left(4).toInt()));
        if(qv.value(26) == "居民"){
            uploadData_sl.append("52");
        }else {
            uploadData_sl.append("11");
        }
        uploadData_sl.append(ui->lineEdit_4->text());
        uploadData_sl.append(qv.value(2));
        uploadData_sl.append(ui->textEdit->toPlainText());
        uploadData_sl.append(ui->textEdit_2->toPlainText());
        uploadData_sl.append(ui->lineEdit_7->text());
        uploadData_sl.append(ui->lineEdit_8->text());
        uploadData_sl.append(QDate(ui->dateEdit_2->date()).toString("yyyy-MM-dd"));
        uploadData_sl.append("情况属实，同意办理。");
        uploadData_sl.append(ui->lineEdit_9->text());
        uploadData_sl.append(QDate(ui->dateEdit_3->date()).toString("yyyy-MM-dd"));
        uploadData_sl.append("");
        uploadData_sl.append(KS_str);
        emit sendUploadData(uploadData_sl); //少10个参数，上传时补齐
        qDebug() << uploadData_sl;
    }
}

/*void y_sbwljhyw_dialog::on_pushButton_2_clicked()现在改成停止日期
{
    for (int var = 0; var < 3; ++var) {
        xst->sendMsg("从前有座山");
        xst->sendMsg("山里有个庙");
        xst->sendMsg("庙里有个老和尚");
        xst->sendMsg("给小和尚讲故事");
        xst->sendMsg("他说：");
    }
    xst->sendMsg("“以后不要乱点奇怪的按钮！！！”");
}*/

void y_sbwljhyw_dialog::on_buttonBox_rejected()
{
    lcd_t->isRun_boo = false;
    while (lcd_t->isRunning()) {
        Sleep(200);
    }
    delete lcd_t;
}

void y_sbwljhyw_dialog::closeEvent(QCloseEvent *e){
    lcd_t->isRun_boo = false;
    while (lcd_t->isRunning()) {
        Sleep(200);
    }
    delete lcd_t;
}
