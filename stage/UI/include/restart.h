#ifndef RESTART_H
#define RESTART_H

#include <QDialog>
#include "../../Core/include/core.h"
#include <QHostAddress>
#include <QMessageBox>

namespace Ui {
class restart;
}

class restart : public QDialog
{
    Q_OBJECT

public:
    void setCore(Core *core){
        this->core = core;
    }
    explicit restart(QWidget *parent = nullptr);
    ~restart();

private:
    Core *core;
    Ui::restart *ui;
    restart* restartWindow = nullptr;


protected:
    // void mousePressEvent(QMouseEvent* event) override;
    // bool event(QEvent *event);
private slots:
    void on_restart_2_clicked();
};

#endif // RESTART_H
