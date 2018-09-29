#include "x_net_tool.h"

QTcpSocket *qts;
x_net_tool::x_net_tool()
{
    qts = new QTcpSocket();
    qts->connectToHost("127.0.0.1", 8192);
    connect(qts, &QTcpSocket::readyRead, this, &x_net_tool::onReadData);
}
x_net_tool::~x_net_tool(){
    if(qts->isOpen())qts->close();
    delete qts;
    qts = NULL;
    delete ui;
}

void x_net_tool::onWriteData(QString nu_str, QString da_str)
{
    QJsonObject jo;
    QJsonDocument jd;
    jo.insert("nu", nu_str);
    jo.insert("da", da_str);
    jd.setObject(jo);
    qts->write(jd.toBinaryData());
}

void x_net_tool::onReadData(){
    QJsonDocument jd;
    QString display_str = "";
    QByteArray buffer = qts->readAll();
    if(!buffer.isEmpty()){
        jd = QJsonDocument::fromBinaryData(buffer);
        display_str.append(QString::number(jd.object().value("su").toInt(), 10).append("\n").append("In:\n"));
        display_str.append(jd.object().value("se").toString())
                .append("\n")
                .append("Out:\n")
                .append(jd.object().value("re").toString());
    }
    ui->textEdit_3->setPlainText(display_str);
    qDebug() << jd;
    emit onReadData_sign();
}
