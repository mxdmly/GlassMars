#ifndef B_CXSFZ_H
#define B_CXSFZ_H

#include <QDialog>

namespace Ui {
class b_cxsfz;
}

class b_cxsfz : public QDialog
{
    Q_OBJECT

public:
    explicit b_cxsfz(QWidget *parent = 0);
    ~b_cxsfz();

private slots:
    void on_pushButton_clicked();

private:
    Ui::b_cxsfz *ui;
};

#endif // B_CXSFZ_H
