#ifndef X_SQL_H
#define X_SQL_H

#include <QDockWidget>

namespace Ui {
class x_sql;
}

class x_sql : public QDockWidget
{
    Q_OBJECT

public:
    explicit x_sql(QWidget *parent = 0);
    ~x_sql();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::x_sql *ui;
};

#endif // X_SQL_H
