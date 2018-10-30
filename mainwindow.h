#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void deleteP();

private slots:
    void on_action_7_triggered();

    void on_action_12_triggered();

    void on_action_13_triggered();

    void on_action_14_triggered();

    void on_action_15_triggered();

    void on_action_16_triggered();

    void on_action_triggered();

    void on_action_11_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
