#ifndef X_ABOUT_H
#define X_ABOUT_H

#include <QDialog>

namespace Ui {
class x_about;
}

class x_about : public QDialog
{
    Q_OBJECT

public:
    explicit x_about(QWidget *parent = 0);
    ~x_about();

private:
    Ui::x_about *ui;
};

#endif // X_ABOUT_H
