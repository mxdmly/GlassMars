#include "x_about.h"
#include "ui_x_about.h"
#include <QRegExp>
#include <QDebug>

x_about::x_about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::x_about)
{
    ui->setupUi(this);
    QVector<QString> sd;
    QString readDate_str = "0007-20181029094716-079^1^00250824|sb0001|灵活就业人员（市直）|44280119490129001X|张适欣|1|01|1949-01-29|21||1|1|0|441200|3132|2018|0|59162.23|43461.4|48269.49|0.0|3040.0|3|0.0|51314.49|0.0|职工|44120020|市直|21|普通报销|编|否|||||||150.0|^0|||^";
    //qDebug() << readDate_str.indexOf(QRegExp("\\^[0-9]*\\|"));
    readDate_str.remove(QRegExp("[\\w,\\W]*\\^1\\^"));
    readDate_str.remove(QRegExp("\\^.*"));
    //readDate_str = readDate_str.remove(0, readDate_str.indexOf(QRegExp("\\^[0-9]*\\|")));
    qDebug() << readDate_str;
    int i = 1;
    while (i >= 0) {
        i = readDate_str.indexOf("\|");
        sd.append(readDate_str.mid(0, i));
        readDate_str.remove(0, i + 1);
    }
    for (int var = 0; var < sd.size(); ++var) {
        qDebug() << sd.value(var);
    }
}

x_about::~x_about()
{
    delete ui;
}
