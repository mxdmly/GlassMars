#ifndef Y_SBWLJHYW_H
#include <x_net_tool.h>
#include <x_sql_tool.h>
#include <x_file_tool.h>
#include <QRegExp>
#include <x_doc.h>
#include <QDate>
#include <main_loading.h>
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
    QVector<QString> parser(QString input_str);
    QStringList uploadData_sl;
    void closeLoading();

    main_loading *my_ml;
    QString sql3110_str;
    QString sql1600_str;
    bool isIni_b;
    bool isLoadingRun;

public slots:
    void on_pushButton_clicked();
    void onReadData(int su_i, QString readDate_str);
    void q1400();
    void q1600(int category_i);
    void q1710();
    void q3110(QStringList uploadData_sl);
    void q3120(QStringList uploadData_sl);

    void getUploadData(QStringList uploadData_sl);

private slots:
    void on_pushButton_2_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_returnPressed();

    void on_lineEdit_3_returnPressed();

    void on_listWidget_2_customContextMenuRequested(const QPoint &pos);

    void on_rightMenuClick();

private:
    Ui::y_sbwljhyw *ui;
};

#endif // Y_SBWLJHYW_H
