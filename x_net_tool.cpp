#include "x_net_tool.h"

QTcpSocket *qts1;
x_net_tool::x_net_tool(QObject *parent) : QObject(parent)
{
    qts1 = new QTcpSocket();
    qts1->connectToHost("127.0.0.1", 8190);
    connect(qts1, &QTcpSocket::readyRead, this, &x_net_tool::onReadData);
}
x_net_tool::~x_net_tool(){
    if(qts1->isOpen())qts1->close();
    delete qts1;
    qts1 = NULL;
}

void x_net_tool::onWriteData(QString nu_str, QString da_str)
{
    QJsonObject jo;
    QJsonDocument jd;
    jo.insert("nu", nu_str);
    jo.insert("da", da_str);
    jd.setObject(jo);
    qts1->write(jd.toBinaryData());
}

void x_net_tool::onWriteData(int nu_i, QString da_str)
{
    QJsonObject jo;
    QJsonDocument jd;
    jo.insert("nu", QString::number(nu_i));
    jo.insert("da", da_str);
    jd.setObject(jo);
    qts1->write(jd.toBinaryData());
}

void x_net_tool::onReadData(){
    QJsonDocument jd;
    QString display_str = "";
    QString readDate_str = "";
    QByteArray buffer = qts1->readAll();
    if(!buffer.isEmpty()){
        jd = QJsonDocument::fromBinaryData(buffer);
        display_str.append(QString::number(jd.object().value("su").toInt(), 10).append("\n").append("In:\n"));
        display_str.append(jd.object().value("se").toString())
                .append("\n")
                .append("Out:\n")
                .append(readDate_str = jd.object().value("re").toString());
    }
    qDebug() << jd;
    onReadData_str = display_str;
    emit onReadData_sign(jd.object().value("su").toInt(), readDate_str);
}
