#ifndef Y_JBYLBXTDBZMZSQDJJJB_H
#include <x_sql_tool.h>
#include <x_file_tool.h>
#include <x_doc.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#define Y_JBYLBXTDBZMZSQDJJJB_H

#include <QDockWidget>

namespace Ui {
class y_jbylbxtdbzmzsqdjjjb;
}

class y_jbylbxtdbzmzsqdjjjb : public QDockWidget
{
    Q_OBJECT

public:
    explicit y_jbylbxtdbzmzsqdjjjb(QWidget *parent = 0);
    ~y_jbylbxtdbzmzsqdjjjb();

    x_sql_tool *xst;
    x_file_tool *xft;
    bool isIni_b;

    QStringList docsssItems_sl;
    QStringList depItem_sl;
    QStringList heaItem_sl;
    QStringList docItem_sl;

private slots:
    void on_pushButton_clicked();

private:
    Ui::y_jbylbxtdbzmzsqdjjjb *ui;
};

#endif // Y_JBYLBXTDBZMZSQDJJJB_H
