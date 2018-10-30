#ifndef X_NET_TOOL_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>
#define X_NET_TOOL_H

#include <QObject>

class x_net_tool : public QObject
{
    Q_OBJECT
public:
    explicit x_net_tool(QObject *parent = nullptr);
    ~x_net_tool();
    void onWriteData(QString nu_i, QString da_str);
    void onWriteData(int nu_i, QString da_str);
    QString onReadData_str;

public slots:
    void onReadData();

signals:
    void onReadData_sign(int, QString);

};

#endif // X_NET_TOOL_H
