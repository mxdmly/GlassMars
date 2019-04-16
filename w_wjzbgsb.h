#ifndef W_WJZBGSB_H
#define W_WJZBGSB_H

#include <QDockWidget>

namespace Ui {
class w_wjzbgsb;
}

class w_wjzbgsb : public QDockWidget
{
    Q_OBJECT

public:
    explicit w_wjzbgsb(QWidget *parent = 0);
    ~w_wjzbgsb();

private:
    Ui::w_wjzbgsb *ui;
};

#endif // W_WJZBGSB_H
