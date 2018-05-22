#ifndef X_NET_H
#define X_NET_H

#include <QDockWidget>

namespace Ui {
class x_net;
}

class x_net : public QDockWidget
{
    Q_OBJECT

public:
    explicit x_net(QWidget *parent = 0);
    ~x_net();

private:
    Ui::x_net *ui;
};

#endif // X_NET_H
