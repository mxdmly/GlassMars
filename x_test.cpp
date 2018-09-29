#include "x_test.h"
#include "ui_x_test.h"
#include <QTcpSocket>

QTcpSocket *qts;
x_test::x_test(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::x_test)
{
    ui->setupUi(this);
    qts = new QTcpSocket();
    qts->connectToHost("127.0.0.1", 8192);
    connect(qts, &QTcpSocket::readyRead, this, &x_test::onReadData);
}

x_test::~x_test()
{
    if(qts->isOpen())qts->close();
    delete qts;
    qts = NULL;
    delete ui;
}

void x_test::on_pushButton_clicked()
{
    QJsonObject jo;
    QJsonDocument jd;
    jo.insert("nu",ui->textEdit->toPlainText());
    jo.insert("da",ui->textEdit_2->toPlainText());
    jd.setObject(jo);
    qts->write(jd.toBinaryData());
}

void x_test::onReadData(){
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
}
