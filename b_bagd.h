#ifndef B_BAGD_H
#define B_BAGD_H

#include <QDockWidget>

namespace Ui {
class b_bagd;
}

class b_bagd : public QDockWidget
{
    Q_OBJECT

public:
    explicit b_bagd(QWidget *parent = 0);
    ~b_bagd();

private:
    Ui::b_bagd *ui;
};

#endif // B_BAGD_H
