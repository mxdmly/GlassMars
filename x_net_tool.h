#ifndef X_NET_TOOL_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>
#define X_NET_TOOL_H


class x_net_tool
{
public:
    x_net_tool();
    ~x_net_tool();
    void onWriteData(int nu_i, QString da_str);

public slots:
    void onReadData();

signals:
    void onReadData_sign();

};

#endif // X_NET_TOOL_H
