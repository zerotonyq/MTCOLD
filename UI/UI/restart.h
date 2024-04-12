#ifndef RESTART_H
#define RESTART_H

#include <QDialog>
#include "../core/scr/core.h"
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
    Ui::restart *ui;
    restart* restartWindow = nullptr;


protected:
    // void mousePressEvent(QMouseEvent* event) override;
    // bool event(QEvent *event);
private slots:
    void on_restart_2_clicked();
};

#endif // RESTART_H