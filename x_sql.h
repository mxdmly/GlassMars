#ifndef X_SQL_H
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QListWidgetItem>
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

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemPressed(QListWidgetItem *item);

    void on_listWidget_currentRowChanged(int currentRow);

    void deleteItem();

private:
    Ui::x_sql *ui;
    QJsonArray dbList_jsa;
    void setMyEdit(QString e1_str, QString e2_str, QString e3_str, QString e4_str);
    void clearMyEdit();
};

#endif // X_SQL_H
