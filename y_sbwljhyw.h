#ifndef Y_SBWLJHYW_H
#include <x_net_tool.h>
#include <x_sql_tool.h>
#include <QRegExp>
#define Y_SBWLJHYW_H

#include <QDockWidget>

namespace Ui {
class y_sbwljhyw;
}

class y_sbwljhyw : public QDockWidget
{
    Q_OBJECT

public:
    explicit y_sbwljhyw(QWidget *parent = 0);
    ~y_sbwljhyw();
    x_net_tool *xnt;
    x_sql_tool *xst;

public slots:
    void on_pushButton_clicked();
    void onReadData(QString readDate_str);

private:
    Ui::y_sbwljhyw *ui;
};

#endif // Y_SBWLJHYW_H
