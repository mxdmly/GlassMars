#ifndef Y_ZFLCX_H
#include <x_sql_tool.h>
#include <x_file_tool.h>
#include <x_doc.h>
#define Y_ZFLCX_H

#include <QDockWidget>

namespace Ui {
class y_zflcx;
}

class y_zflcx : public QDockWidget
{
    Q_OBJECT

public:
    explicit y_zflcx(QWidget *parent = 0);
    ~y_zflcx();

    x_sql_tool *xst;
    x_file_tool *xft;
    bool isIni_b;

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::y_zflcx *ui;
};

#endif // Y_ZFLCX_H
