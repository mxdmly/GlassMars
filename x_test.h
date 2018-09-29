#ifndef X_TEST_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>
#define X_TEST_H

#include <QDockWidget>

namespace Ui {
class x_test;
}

class x_test : public QDockWidget
{
    Q_OBJECT

public:
    explicit x_test(QWidget *parent = 0);
    ~x_test();

private slots:
    void on_pushButton_clicked();
    void onReadData();

private:
    Ui::x_test *ui;
};

#endif // X_TEST_H
