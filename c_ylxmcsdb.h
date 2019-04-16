#ifndef C_YLXMCSDB_H
#include <x_sql_tool.h>
#include <x_file_tool.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#define C_YLXMCSDB_H

#include <QDockWidget>

namespace Ui {
class c_ylxmcsdb;
}

class c_ylxmcsdb : public QDockWidget
{
    Q_OBJECT

public:
    explicit c_ylxmcsdb(QWidget *parent = 0);
    ~c_ylxmcsdb();
    x_sql_tool *xst;
    x_file_tool *xft;

    QStringList departmentItems_sl;

private slots:
    void on_pushButton_clicked();

private:
    Ui::c_ylxmcsdb *ui;
};

#endif // C_YLXMCSDB_H
