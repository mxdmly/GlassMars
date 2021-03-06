﻿#ifndef X_FILE_TOOL_H
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
#define X_FILE_TOOL_H


class x_file_tool
{
public:
    x_file_tool();
    ~x_file_tool();

    QString setPath(QWidget *qwidge, QString name_str);
    QString setPath(QString path_str);
    QString setPath();
    bool writeFile(QString text_str);
    bool writeFile(QString fileName_str, QByteArray data_qba);
    QByteArray readFile(QString fileName_str);
    QByteArray readFile();
    void sendMsg(QString str);
    QString readFileText(QString fileName_str);

//private:
    QString filePath_str;
};

#endif // X_FILE_TOOL_H
