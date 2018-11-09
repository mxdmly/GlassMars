#include "x_sql.h"
#include "ui_x_sql.h"
#include <QDebug>
#include <ui_x_sql_listitem.h>

int dbListNum_i = 0;
bool isNewItem_b = true;
int listRow_i = 0;
QVector<QListWidgetItem*> item_qv;
QVector<ui_x_sql_listitem*> itemUi_qv;

x_sql::x_sql(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::x_sql)
{
    ui->setupUi(this);

    xft = new x_file_tool();
    xft->setPath();
    dbList_jsa = QJsonDocument::fromBinaryData(xft->readFile("dbList.ini")).array();
    qDebug() << dbList_jsa;

    item_qv = QVector<QListWidgetItem*>();
    itemUi_qv = QVector<ui_x_sql_listitem*>();

    dbListNum_i = dbList_jsa.size();//
    for (int i = 0; i < dbList_jsa.size(); i++) {
        //ui->listWidget->addItem(dbList_jsa.at(i).toObject().value("name").toString());

        item_qv.append(new QListWidgetItem(ui->listWidget));
        item_qv.value(i)->setSizeHint(QSize(0, 15));
        item_qv.value(i)->setBackground(QColor(255,255,255));

        itemUi_qv.append(new ui_x_sql_listitem());
        itemUi_qv.value(i)->setText(dbList_jsa.at(i).toObject().value("name").toString());
        connect(itemUi_qv.value(i), &ui_x_sql_listitem::deleteItem_sign, this, &x_sql::deleteItem);

        ui->listWidget->setItemWidget(item_qv.value(i), itemUi_qv.value(i));
        ui->listWidget->addItem(item_qv.value(i));
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
        xft->sendMsg(QString::fromLocal8Bit("输入不能为空"));//输入不能为空
    }else {
        QJsonObject temp_jso;
        if(isNewItem_b){
            dbListNum_i = dbList_jsa.size();
            temp_jso.insert("name", ui->lineEdit->text());
            temp_jso.insert("ip", ui->lineEdit_2->text());
            temp_jso.insert("account", ui->lineEdit_4->text());
            temp_jso.insert("password", ui->lineEdit_5->text());
            dbList_jsa.insert(dbListNum_i, temp_jso);

            item_qv.append(new QListWidgetItem(ui->listWidget));
            item_qv.value(dbListNum_i)->setSizeHint(QSize(0, 15));
            item_qv.value(dbListNum_i)->setBackground(QColor(255,255,255));
            itemUi_qv.append(new ui_x_sql_listitem());
            itemUi_qv.value(dbListNum_i)->setText(dbList_jsa.at(dbListNum_i).toObject().value("name").toString());
            connect(itemUi_qv.value(dbListNum_i), &ui_x_sql_listitem::deleteItem_sign, this, &x_sql::deleteItem);
            ui->listWidget->setItemWidget(item_qv.value(dbListNum_i), itemUi_qv.value(dbListNum_i));
            ui->listWidget->addItem(item_qv.value(dbListNum_i));

            qDebug() << xft->filePath_str;
            qDebug() << temp_jso;
        }else {
            temp_jso.insert("name", ui->lineEdit->text());
            temp_jso.insert("ip", ui->lineEdit_2->text());
            temp_jso.insert("account", ui->lineEdit_4->text());
            temp_jso.insert("password", ui->lineEdit_5->text());
            dbList_jsa.replace(listRow_i, temp_jso);

            itemUi_qv.value(listRow_i)->setText(dbList_jsa.at(listRow_i).toObject().value("name").toString());
            ui->listWidget->setItemWidget(item_qv.value(listRow_i), itemUi_qv.value(listRow_i));

            qDebug() << xft->filePath_str;
            qDebug() << temp_jso;
        }
    }
}

void x_sql::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    isNewItem_b = false;
    listRow_i = ui->listWidget->row(item);
    itemUi_qv.value(listRow_i)->setLableTextColor("color:rgb(102, 204, 255);");//天依蓝
    QJsonObject temp_jso = dbList_jsa.at(listRow_i).toObject();
    setMyEdit(temp_jso.value("name").toString(), temp_jso.value("ip").toString(), temp_jso.value("account").toString(), temp_jso.value("password").toString());
}

void x_sql::on_pushButton_3_clicked() //新建链接
{
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

void x_sql::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() << "cleck";
    return;
}

void x_sql::on_listWidget_itemPressed(QListWidgetItem *item)
{
    return;
}

void x_sql::on_listWidget_currentRowChanged(int currentRow)
{
    for (int i = 0; i < itemUi_qv.size(); ++i) {
        itemUi_qv.value(i)->setLableTextColor("color:black;");
    }
    itemUi_qv.value(currentRow)->setLableTextColor("color:white;");
}

void x_sql::deleteItem(){
    qDebug() << ui->listWidget->count();
    ui_x_sql_listitem * btn = qobject_cast<ui_x_sql_listitem*>(sender());
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if(btn == itemUi_qv.value(i)){
            ui->listWidget->takeItem(i);
            itemUi_qv.remove(i);
            item_qv.remove(i);
            dbList_jsa.removeAt(i);
            return;
        }
    }
}
