#ifndef UI_X_SQL_LISTITEM_H
#include <windows.h>
#define UI_X_SQL_LISTITEM_H

#include <QWidget>

namespace Ui {
class ui_x_sql_listitem;
}

class ui_x_sql_listitem : public QWidget
{
    Q_OBJECT

public:
    explicit ui_x_sql_listitem(QWidget *parent = 0);
    ~ui_x_sql_listitem();
    void setText(QString label_str);
    void setLableTextColor(QString str);

public slots:
    void on_pushButton_clicked();

signals:
    void deleteItem_sign();

private:
    Ui::ui_x_sql_listitem *ui;
};

#endif // UI_X_SQL_LISTITEM_H
