#include "y_sbwljhyw_dialog.h"
#include "ui_y_sbwljhyw_dialog.h"
#include <QDebug>

using namespace std;

y_sbwljhyw_dialog::y_sbwljhyw_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::y_sbwljhyw_dialog)
{
    ui->setupUi(this);
    xft = new x_file_tool();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
}

y_sbwljhyw_dialog::~y_sbwljhyw_dialog()
{
    delete ui;
}

void y_sbwljhyw_dialog::setQV(QVector<QString> qv){
    this->qv = qv;
    ui->lineEdit->setText(qv.value(4));
    ui->lineEdit_2->setText(qv.value(26));
    ui->lineEdit_3->setText(qv.value(0));
}

void y_sbwljhyw_dialog::setXST(x_sql_tool *xst){
    this->xst = xst;
    this->xft = new x_file_tool();
    if(! qv.isEmpty()){
        xst->iniDB();
        x_doc x;
        QSqlQuery qsq = xst->getData(x.sqlCel_str + qv.value(0) + "\' ORDER BY nhis.dbo.ZhaoQingInVisitSiReg.VisitId DESC");
        if(qsq.numRowsAffected() >= 1){
            qsq.next();
            ui->lineEdit_4->setText(qsq.value(1).toString());
            qDebug() << qsq.value(1).toString();
        }
    }
    xft->setPath("C:\\Qt\\GP\\build-GlassMars-MinGw_XP-Debug\\debug\\doc");
    QString str = xft->readFileText("doctors.ini");
    QJsonParseError *e = new QJsonParseError();
    QJsonArray qja = QJsonDocument::fromJson(str.toUtf8(), e).array();
    qDebug() << e->errorString();
    for (int i = 0; i < qja.size(); ++i) {
        //qja.at(i).toObject().value("department").toString();
        docsssItems_sl.append(qja.at(i).toObject().value("department").toString() + "-----------------");
        depItem_sl.append("");
        heaItem_sl.append("");
        docItem_sl.append("");
        QJsonArray doc_qja = qja.at(i).toObject().value("doctors").toArray();
        for (int var = 0; var < doc_qja.size(); ++var) {
            depItem_sl.append(qja.at(i).toObject().value("department").toString());
            heaItem_sl.append(qja.at(i).toObject().value("head").toString());
            docItem_sl.append(doc_qja.at(var).toString());
            docsssItems_sl.append("   " + doc_qja.at(var).toString());
        }
    }
    ui->comboBox_2->addItems(docsssItems_sl);

    str = xft->readFileText("SpecificDiseaseClinicSign.ini");
    e = new QJsonParseError();
    qja = QJsonDocument::fromJson(str.toUtf8(), e).array();
    qDebug() << e->errorString();
    for (int i = 0; i < qja.size(); ++i) {
        if(i == 0){
            hairItems_sl.append("特门有限额-------------------------------------");
            ClassificationName_sl.append("");
            CodeName_sl.append("");
            CodeValue_sl.append("");
        }else if(i == 1){
            hairItems_sl.append("特门无限额-------------------------------------");
            ClassificationName_sl.append("");
            CodeName_sl.append("");
            CodeValue_sl.append("");
        }
        QJsonArray CodeName_qja = qja.at(i).toObject().value("CodeName").toArray();
        QJsonArray CodeValue_qja = qja.at(i).toObject().value("CodeValue").toArray();
        for (int var = 0; var < CodeName_qja.size(); ++var) {
            ClassificationName_sl.append(qja.at(i).toObject().value("ClassificationName").toString());
            CodeName_sl.append(CodeName_qja.at(var).toString());
            CodeValue_sl.append(CodeValue_qja.at(var).toString());
            hairItems_sl.append(CodeValue_qja.at(var).toString() + "\t" + CodeName_qja.at(var).toString());
        }
    }
    ui->comboBox->addItems(hairItems_sl);
}

void y_sbwljhyw_dialog::on_comboBox_2_activated(int index)
{
    if(index == 0){
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
    }else{
        ui->lineEdit_7->setText(docItem_sl.at(index - 1));
        ui->lineEdit_8->setText(heaItem_sl.at(index - 1));
    }
}

void y_sbwljhyw_dialog::on_comboBox_activated(int index)
{
    ui->lineEdit_5->setText(CodeValue_sl.at(index));
    ui->lineEdit_6->setText(CodeName_sl.at(index));
    ui->textEdit->setText(CodeName_sl.at(index));
}
