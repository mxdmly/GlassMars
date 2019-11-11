#include "y_sbwljhyw_thread.h"
#include <QDebug>

y_sbwljhyw_thread::y_sbwljhyw_thread()
{
    isRun_boo = true;
}

y_sbwljhyw_thread::~y_sbwljhyw_thread(){
    isRun_boo = false;
}

void y_sbwljhyw_thread::run(){
    int i = 0;
    while (isRun_boo) {
        lcd->display(QTime::currentTime().toString("hh:mm:ss"));
        msleep(200);
        //qDebug() << i;
        i++;
    }
}
