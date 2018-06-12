#ifndef B_BAGD_H
#include <QDockWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QTextEdit>
#define B_BAGD_H

namespace Ui {
class b_bagd;
}

class b_bagd : public QDockWidget
{
    Q_OBJECT

public:
    explicit b_bagd(QWidget *parent = 0);
    ~b_bagd();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::b_bagd *ui;
    void keyPressEvent(QKeyEvent *event);
};

#endif // B_BAGD_H
