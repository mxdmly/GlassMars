#include "n_tcpserver_thread.h"
#include <QDebug>
#include <Lemon.h>
#include <x_sql_tool.h>
#include <mainwindow.h>

using namespace std;

Lemon *lemon;
x_sql_tool *xst;
QString sendData_str;
QString returnedData_str;
int returnedSuccess_i;
bool isSign_b;
n_tcpserver_thread::n_tcpserver_thread()
{
    isRun = true;
    server_qts = new QTcpServer();
    connect(server_qts, &QTcpServer::newConnection, this, &n_tcpserver_thread::newClient);//有新的链接会发出信号
    connect(this, &n_tcpserver_thread::onRestart_sign, this, &n_tcpserver_thread::onRestart_slots);
    connect(this, &n_tcpserver_thread::onStop_sign, this, &n_tcpserver_thread::onStop_slots);
    socket_i = 0;
}

n_tcpserver_thread::~n_tcpserver_thread()
{
    isRun = false;
    onStop_sign();
    if(server_qts->isListening())server_qts->close();
    server_qts->deleteLater();
    delete server_qts;
    server_qts = NULL;
    if(isSign_b)lemon->SignOut();
    if(lemon != NULL)delete lemon;
    lemon = NULL;
}

void n_tcpserver_thread::run(){
    lemon = new Lemon();
    while (isRun) {
        onRestart_sign();
        if(lemon->Sign() == 0){ //如果签到成功会返回0
            isSign_b = true;
            qDebug() << "Server on runing(服务正在运行)...\t" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            emit barMsg_sign("签到成功");
            isRun = false;
        }else {
            qDebug() << "Sign Error(签到失败，正在重试)...\t" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            sleep(1000);
        }
    }
}

void n_tcpserver_thread::newClient(){
    socket_qts = server_qts->nextPendingConnection();
    //socket_qts_qv->append(server_qts->nextPendingConnection());
    connect(socket_qts, &QTcpSocket::readyRead, this, &n_tcpserver_thread::readData);
    //socket_i++;//区别客户端用，每多一个链接自增1
}

void n_tcpserver_thread::readData(){
    QJsonDocument jd;
    QByteArray data_qba = socket_qts->readAll();
    if(!data_qba.isEmpty()){
        jd = QJsonDocument::fromBinaryData(data_qba);
        sendData_str = jd.object().value("nu").toString();//number
        sendData_str.append("^100007^").append(lemon->myNum_str).append(lemon->bcNum_str).append("^");
        sendData_str.append(lemon->getTime()).append("-100007-1111^");
        sendData_str.append(jd.object().value("da").toString()).append("^1^");//data
    }
    returnedSuccess_i = lemon->sendData(sendData_str);
    writeData();
}

void n_tcpserver_thread::writeData(){
    QJsonObject jo;
    QJsonDocument jd;
    jo.insert("se", sendData_str);
    jo.insert("su", returnedSuccess_i);
    jo.insert("re", QString::fromLocal8Bit(lemon->outData_ch));
    jd.setObject(jo);
    socket_qts->write(jd.toBinaryData());
}

void n_tcpserver_thread::onRestart_slots(){ //兼顾重启与初始化功能
    if(! server_qts->listen(QHostAddress::LocalHost, 8190)){//侦听全网IP
        qDebug() << "listenErrot:->  " << server_qts->errorString();//链接失败输出错误信息
    }
}

void n_tcpserver_thread::onStop_slots(){
    if(socket_qts->isOpen())socket_qts->disconnectFromHost();
    server_qts->close();
}
