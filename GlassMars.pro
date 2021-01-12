#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T16:25:05
#
#-------------------------------------------------

#win32 {
#QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
#}

QT       += core gui
QT       += sql
QT       += network
RC_ICONS = logo.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GlassMars
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    b_bagd.cpp \
    x_net.cpp \
    x_sql.cpp \
    x_sql_tool.cpp \
    x_file_tool.cpp \
    ui_x_sql_listitem.cpp \
    c_mzxy.cpp \
    x_about.cpp \
    main_loading.cpp \
    main_loading_thread.cpp \
    b_cxsfz.cpp \
    x_test.cpp \
    x_net_tool.cpp \
    y_sbwljhyw.cpp \
    x_doc.cpp \
    y_sbwljhyw_thread.cpp \
    y_sbwljhyw_dialog.cpp \
    y_jbylbxtdbzmzsqdjjjb.cpp \
    y_zflcx.cpp \
    w_wjzbg.cpp \
    w_wjzbgsb.cpp \
    c_ylxmcsdb.cpp \
    n_tcpserver_thread.cpp \
    Lemon.cpp

HEADERS += \
        mainwindow.h \
    b_bagd.h \
    x_net.h \
    x_sql.h \
    x_sql_tool.h \
    x_file_tool.h \
    ui_x_sql_listitem.h \
    c_mzxy.h \
    x_about.h \
    main_loading.h \
    main_loading_thread.h \
    b_cxsfz.h \
    x_test.h \
    x_net_tool.h \
    y_sbwljhyw.h \
    x_doc.h \
    y_sbwljhyw_thread.h \
    y_sbwljhyw_dialog.h \
    y_jbylbxtdbzmzsqdjjjb.h \
    y_zflcx.h \
    w_wjzbg.h \
    w_wjzbgsb.h \
    c_ylxmcsdb.h \
    Lemon.h \
    n_tcpserver_thread.h

FORMS += \
        mainwindow.ui \
    b_bagd.ui \
    x_net.ui \
    x_sql.ui \
    ui_x_sql_listitem.ui \
    c_mzxy.ui \
    x_about.ui \
    main_loading.ui \
    b_cxsfz.ui \
    x_test.ui \
    y_sbwljhyw.ui \
    y_sbwljhyw_dialog.ui \
    y_jbylbxtdbzmzsqdjjjb.ui \
    y_zflcx.ui \
    w_wjzbg.ui \
    w_wjzbgsb.ui \
    c_ylxmcsdb.ui

RESOURCES += \
    img.qrc
