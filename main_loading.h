#ifndef MAIN_LOADING_H
#define MAIN_LOADING_H

#include <QDialog>

namespace Ui {
class main_loading;
}

class main_loading : public QDialog
{
    Q_OBJECT

public:
    explicit main_loading(QWidget *parent = 0);
    ~main_loading();

private:
    Ui::main_loading *ui;
public slots:
    void updateProgressBar(int i);
    void updateProgressBar(int i, QString label_str);
};

#endif // MAIN_LOADING_H
