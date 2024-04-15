#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "indicator.h"
#include "restart.h"
#include "../../Core/include/core.h"
#include <QCoreApplication>
#include <QHostAddress>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Core core;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_request_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
