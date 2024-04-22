#ifndef RESTART_H
#define RESTART_H

#include <QDialog>
#include "connectcore.h"
#include <QHostAddress>
#include <QMessageBox>

namespace Ui {
class restart;
}

class restart : public QDialog
{
    Q_OBJECT

public:
    explicit restart(QWidget *parent = nullptr);
    ~restart();

private:
    ConnectCore *core;
    Ui::restart *ui;
    restart* restartWindow = nullptr;

private slots:
    void on_restart_2_clicked();
};

#endif // RESTART_H
