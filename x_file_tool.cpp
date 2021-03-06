﻿#include "x_file_tool.h"
#include <QDebug>

using namespace std;

x_file_tool::x_file_tool()
{
    //this
}

x_file_tool::~x_file_tool(){
    //asd
}

QString x_file_tool::setPath(QWidget *qwidge, QString name_str){//由用户输入，有弹出框的路径
    filePath_str = QFileDialog::getSaveFileName(qwidge, QObject::tr("Save as..."), QString(name_str), QObject::tr("EXCEL files (*.xls *.xlsx);;HTML-Files (*.txt);;"));
    return filePath_str;
}

QString x_file_tool::setPath(QString path_str){
    if(path_str.isEmpty() | path_str.isNull()){
        filePath_str = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    }else {
        filePath_str = path_str;
    }
    return filePath_str;
}

QString x_file_tool::setPath(){
    filePath_str = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return filePath_str;
}

bool x_file_tool::writeFile(QString text_str){//写入Excel专用
    bool isOpen_b = false;
    if(filePath_str.isEmpty() | filePath_str.isNull()){
        //sendMsg("Path is null");
    }else{
        QFile f(filePath_str);
        try {
            isOpen_b = f.open(QFile::WriteOnly | QIODevice::Text);
            if(isOpen_b){
                QTextStream t(&f);
                //t.setCodec("UTF-8");
                t.setCodec("GBK");
                t<<text_str;
            }
            f.close();
        } catch (const std::exception&) {
            sendMsg(f.errorString());
        }
    }
    return isOpen_b;
}

bool x_file_tool::writeFile(QString fileName_str, QByteArray data_qba){//写入其他文件
    bool isOpen_b = false;
    if(filePath_str.isEmpty() | filePath_str.isNull()){
        sendMsg("Path is null");
    }else{
        QDir d(filePath_str);
        QFile f(QString(filePath_str).append("\\").append(fileName_str));
        qDebug() << "Out " << QFileInfo(f).path();
        try {
            if(! d.exists()){
                d.mkpath(filePath_str);
            }
            isOpen_b = f.open(QFile::WriteOnly | QIODevice::WriteOnly);
            if(isOpen_b){
                QDataStream write_qds(&f);

                write_qds.setVersion(QDataStream::Qt_5_6);
                write_qds << data_qba;
            }
            f.close();
        } catch (const std::exception&) {
            sendMsg(f.errorString());
        }
    }
    return isOpen_b;
}

QByteArray x_file_tool::readFile(QString fileName_str){
    QByteArray temp_qba = NULL;
    if(filePath_str.isEmpty() | filePath_str.isNull()){
        sendMsg("Path is null");
    }else{
        QFile f(QString(filePath_str).append("\\").append(fileName_str));
        qDebug() << "In " << QFileInfo(f).path();
        try {
            if(f.open(QFile::ReadOnly | QIODevice::ReadOnly)){
                QDataStream read_qds(&f);
                read_qds.setVersion(QDataStream::Qt_5_6);
                read_qds >> temp_qba;
            }
        } catch (const std::exception&) {
            sendMsg(f.errorString());
        }
        f.close();
    }
    return temp_qba;
}

QString x_file_tool::readFileText(QString fileName_str){
    QString temp_str = NULL;
    if(filePath_str.isEmpty() | filePath_str.isNull()){
        sendMsg("Path is null");
    }else{
        QFile f(QString(filePath_str).append("\\").append(fileName_str));
        qDebug() << "In " << QFileInfo(f).path();
        try {
            if(f.open(QFile::ReadOnly | QIODevice::ReadOnly)){
                QTextStream read_qds(&f);
                temp_str = read_qds.readAll();
            }
        } catch (const std::exception&) {
            sendMsg(f.errorString());
        }
        f.close();
    }
    return temp_str;
}

void x_file_tool::sendMsg(QString str)//一个方便使用的文本弹出框
{
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}
