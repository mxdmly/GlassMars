#ifndef C_MZXY_H
#include <QTextEdit>
#define C_MZXY_H

#include <QDockWidget>

namespace Ui {
class c_mzxy;
}

class c_mzxy : public QDockWidget
{
    Q_OBJECT

public:
    explicit c_mzxy(QWidget *parent = 0);
    ~c_mzxy();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::c_mzxy *ui;
};

#endif // C_MZXY_H
