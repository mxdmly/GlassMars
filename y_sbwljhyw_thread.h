﻿#ifndef Y_SBWLJHYW_THREAD_H
#include <QLCDNumber>
#include <QTime>
#include <QCoreApplication>
#define Y_SBWLJHYW_THREAD_H

#include <QThread>

class y_sbwljhyw_thread : public QThread
{
    Q_OBJECT
    void run() override;
public:
    explicit y_sbwljhyw_thread();
    ~y_sbwljhyw_thread();
    QLCDNumber *lcd;
    bool isRun_boo;

signals:

public slots:
};

#endif // Y_SBWLJHYW_THREAD_H
