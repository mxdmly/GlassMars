#include "x_file_tool.h"

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
        sendMsg("Path is null");
    }else{
        QFile f(filePath_str);
        try {
            isOpen_b = f.open(QFile::WriteOnly | QIODevice::Text);
            if(isOpen_b){
                QTextStream t(&f);
                t.setCodec("UTF-8");
                t<<text_str;
            }
            f.close();
        } catch (const std::exception&) {
            sendMsg(f.errorString());
        }
    }
    return isOpen_b;
}

bool x_file_tool::writeFile(QString fileName_str, QObject data_obj){//写入其他文件
    bool isOpen_b = false;
    if(filePath_str.isEmpty() | filePath_str.isNull()){
        sendMsg("Path is null");
    }else{
        QDir d(filePath_str);
        QFile f(filePath_str.append("\\").append(fileName_str));
        try {
            if(! d.exists()){
                d.mkpath(filePath_str);
            }
            isOpen_b = f.open(QFile::WriteOnly | QIODevice::WriteOnly);
            if(isOpen_b){
                QDataStream write_qds(&f);
                write_qds.setVersion(QDataStream::Qt_4_8);
                write_qds << data_obj;
                QByteArray a;

            }
            f.close();
        } catch (const std::exception&) {
            sendMsg(f.errorString());
        }
    }
    return isOpen_b;
}

void x_file_tool::sendMsg(QString str)//一个方便使用的文本弹出框
{
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}
