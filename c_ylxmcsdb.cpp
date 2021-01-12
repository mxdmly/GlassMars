#include "c_ylxmcsdb.h"
#include "ui_c_ylxmcsdb.h"

QSqlQuery w2_sq;

c_ylxmcsdb::c_ylxmcsdb(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::c_ylxmcsdb)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate().addMonths(-1));
    ui->dateEdit_2->setDate(QDate::currentDate());

    xft = new x_file_tool();
    xft->setPath(QApplication::applicationDirPath() + "\\doc");
    QString str = xft->readFileText("Department.ini");
    QJsonParseError *e = new QJsonParseError();
    QJsonArray ja = QJsonDocument::fromJson(str.toUtf8(), e).array();
    qDebug() << e->errorString();
    for (int i = 0; i < ja.size(); ++i) {
        departmentItems_sl.append(ja.at(i).toString());
    }
    ui->comboBox->addItems(departmentItems_sl);
}

c_ylxmcsdb::~c_ylxmcsdb()
{
    if(xft != NULL)delete xft;
    w2_sq.clear();
    delete ui;
}

void c_ylxmcsdb::on_pushButton_clicked()//查询
{
    return;
    //int[] L1, L2;
    //float[][] Anum;
    QList<int> Az_str;
    QString sql_str;
    if(xst->ifIni_b)xst->iniDB();//初始化数据库工具
    sql_str = "SELECT dbo.IPPatCost.DeptId,dbo.IPPatCost.ChargeStandardId,dbo.IPPatCost.DeptNm,dbo.IPPatCost.FeeTypeNm,dbo.IPPatCost.ChargeStandardNm,Sum(dbo.IPPatCost.Quantity) FROM dbo.IPPatCost WHERE dbo.IPPatCost.ExeDt BETWEEN '2019-03-01' AND '2019-03-01' AND dbo.IPPatCost.FeeTypeId NOT IN (3,5) GROUP BY dbo.IPPatCost.DeptId,dbo.IPPatCost.ChargeStandardId,dbo.IPPatCost.DeptNm,dbo.IPPatCost.FeeTypeNm,dbo.IPPatCost.ChargeStandardNm";
    w2_sq = xst->getData(sql_str);
    w2_sq.size();
    while (w2_sq.next()) {
        ;
    }
}













