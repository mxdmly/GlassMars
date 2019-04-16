#ifndef W_WJZBG_H
#define W_WJZBG_H

#include <QDockWidget>

namespace Ui {
class w_wjzbg;
}

class w_wjzbg : public QDockWidget
{
    Q_OBJECT

public:
    explicit w_wjzbg(QWidget *parent = 0);
    ~w_wjzbg();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::w_wjzbg *ui;
};

#endif // W_WJZBG_H
