#ifndef N_TCPSERVER_THREAD_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QTextCodec>
#include <QJsonObject>
#include <QJsonDocument>
#define N_TCPSERVER_THREAD_H

#include <QThread>

class n_tcpserver_thread : public QThread
{
    Q_OBJECT
    void run() override;
public:
    n_tcpserver_thread();
    ~n_tcpserver_thread();
    bool isRun;
    QTcpServer *server_qts;
    QTcpSocket *socket_qts;
    QVector<QTcpSocket> *socket_qts_qv;
    int socket_i;

signals:
    void onRestart_sign();
    void onStop_sign();
    void barMsg_sign(QString msg_str);

private slots:
    void newClient();
    void readData();
    void writeData();
    void onRestart_slots();
    void onStop_slots();

};

#endif // N_TCPSERVER_THREAD_H
