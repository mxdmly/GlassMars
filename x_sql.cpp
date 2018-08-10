#include "x_sql.h"
#include "ui_x_sql.h"
#include <QDebug>
#include <x_file_tool.h>
#include <ui_x_sql_listitem.h>

x_file_tool *xft = NULL;
int dbListNum_i = 0;
bool isNewItem_b = true;
int listRow_i = 0;

x_sql::x_sql(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::x_sql)
{
    ui->setupUi(this);
    xft = new x_file_tool();
    xft->setPath();
    dbList_jsa = QJsonDocument::fromBinaryData(xft->readFile("dbList.ini")).array();
    qDebug() << dbList_jsa;

    QListWidgetItem *ul[dbList_jsa.size()];
    ui_x_sql_listitem *aa[dbList_jsa.size()];

    dbListNum_i = dbList_jsa.size();//
    for (int i = 0; i < dbList_jsa.size(); i++) {
        //ui->listWidget->addItem(dbList_jsa.at(i).toObject().value("name").toString());

        ul[i] = new QListWidgetItem(ui->listWidget);
        ul[i]->setSizeHint(QSize(0, 15));
        aa[i] = new ui_x_sql_listitem();
        aa[i]->setText(dbList_jsa.at(i).toObject().value("name").toString());

        ui->listWidget->setItemWidget(ul[i], aa[i]);
        ui->listWidget->addItem(ul[i]);
    }
}

x_sql::~x_sql()
{
    xft->writeFile("dbList.ini", QJsonDocument(dbList_jsa).toBinaryData());
    qDebug() << dbList_jsa << " sssssssize is " << dbList_jsa.size();
    qDebug() << QJsonDocument(dbList_jsa);
    if(xft != NULL){
        delete xft;
        xft = NULL;
    }
    delete ui;
}

QString pass(QString str){
    char *c = str.toLatin1().data();
    for (int i = 0; i < str.length(); ++i) {
        qDebug() << QString(c[i]);
        qDebug() << QString(c[i]);
    }
    return str;
}

void x_sql::on_pushButton_2_clicked() //确定
{
    if(ui->lineEdit->text().isEmpty() | ui->lineEdit_2->text().isEmpty() | ui->lineEdit_4->text().isEmpty() | ui->lineEdit_5->text().isEmpty()){
        xft->sendMsg(QString::fromLocal8Bit("\u8f93\u5165\u4e0d\u80fd\u4e3a\u7a7a"));//输入不能为空
    }else {
        QJsonObject temp_jso;
        if(isNewItem_b){
            temp_jso.insert("name", ui->lineEdit->text());
            temp_jso.insert("ip", ui->lineEdit_2->text());
            temp_jso.insert("account", ui->lineEdit_4->text());
            temp_jso.insert("password", ui->lineEdit_5->text());
            dbList_jsa.insert(dbListNum_i, temp_jso);
            ui->listWidget->addItem(ui->lineEdit->text());
            dbListNum_i++;//数组下标加1
            qDebug() << xft->filePath_str;
            qDebug() << temp_jso;
        }else {
            ui->listWidget->item(listRow_i)->setText(ui->lineEdit->text());
            temp_jso.insert("name", ui->lineEdit->text());
            temp_jso.insert("ip", ui->lineEdit_2->text());
            temp_jso.insert("account", ui->lineEdit_4->text());
            temp_jso.insert("password", ui->lineEdit_5->text());
            dbList_jsa.replace(listRow_i, temp_jso);
            qDebug() << xft->filePath_str;
            qDebug() << temp_jso;
        }
    }
}

void x_sql::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    item->setTextColor(QColor(102, 204, 255)); //天依蓝
    ui->listWidget->item(listRow_i)->setTextColor(QColor(Qt::black));
    isNewItem_b = false;
    listRow_i = ui->listWidget->currentRow();
    QJsonObject temp_jso = dbList_jsa.at(listRow_i).toObject();
    setMyEdit(temp_jso.value("name").toString(), temp_jso.value("ip").toString(), temp_jso.value("account").toString(), temp_jso.value("password").toString());
}

void x_sql::on_pushButton_3_clicked() //新建链接
{
    ui->listWidget->item(listRow_i)->setTextColor(QColor(Qt::black));
    isNewItem_b = true;
    clearMyEdit();
}

void x_sql::setMyEdit(QString e1_str, QString e2_str, QString e3_str, QString e4_str){ //设置输入栏的参数
    ui->lineEdit->setText(e1_str);
    ui->lineEdit_2->setText(e2_str);
    ui->lineEdit_4->setText(e3_str);
    ui->lineEdit_5->setText(e4_str);
}

void x_sql::clearMyEdit(){ //清空输入栏的参数
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void x_sql::on_pushButton_clicked() //取消
{
    clearMyEdit();
}
