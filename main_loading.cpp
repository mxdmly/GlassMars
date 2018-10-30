#include "main_loading.h"
#include "ui_main_loading.h"

main_loading::main_loading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::main_loading)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);//点击叉叉delete自己
}

main_loading::~main_loading()
{
    delete ui;
}

void main_loading::updateProgressBar(int i){
    ui->progressBar->setValue(i);
}
