#ifndef Y_SBWLJHYW_DIALOG_H
#include <x_sql_tool.h>
#include <x_file_tool.h>
#include <x_doc.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QCloseEvent>
#define Y_SBWLJHYW_DIALOG_H

#include <QDialog>

namespace Ui {
class y_sbwljhyw_dialog;
}

class y_sbwljhyw_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit y_sbwljhyw_dialog(QWidget *parent = 0);
    ~y_sbwljhyw_dialog();
    QVector<QString> qv;
    x_sql_tool *xst;
    x_file_tool *xft;
    void setQV(QVector<QString>);
    void setXST(x_sql_tool *xst);

    QStringList docsssItems_sl;
    QStringList depItem_sl;
    QStringList heaItem_sl;
    QStringList docItem_sl;

    QStringList hairItems_sl;//Hospital approval information report
    QStringList ClassificationName_sl;
    QStringList CodeName_sl;
    QStringList CodeValue_sl;
    QStringList ValidityPeriod_sl;
    QList<int> ValidityPeriod_list;

    int BZ_index_i;
    int Doc_index_i;
    QString KS_str;

private slots:
    void on_comboBox_2_activated(int index);

    void on_comboBox_activated(int index);

    void on_buttonBox_accepted();

    void on_pushButton_2_clicked();

    void on_buttonBox_rejected();

    void closeEvent(QCloseEvent *e);

signals:
    void sendUploadData(QStringList uploadData_sl);

private:
    Ui::y_sbwljhyw_dialog *ui;
};

#endif // Y_SBWLJHYW_DIALOG_H
