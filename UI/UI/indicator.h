#ifndef INDICATOR_H
#define INDICATOR_H

#include "errorwindow.h"
#include "qabstractbutton.h"
#include "restart.h"
#include <cstdlib>
#include "../core/scr/core.h"
#include "../core/scr/Pockets.h"
#include <QDialog>

namespace Ui {
class indicator;
}

class indicator : public QDialog
{
    Q_OBJECT

public:
    Core core;
    explicit indicator(QWidget *parent = nullptr);
    ~indicator();

private slots:
    void on_build_clicked();
    void on_mistakes_clicked();
    void onButtonClicked(QAbstractButton* button);
    // bool eventFilter(QObject *obj, QEvent *event);

    //void on_toggle0_toggled(bool checked);

private:
    char scount[1];
    sIndicatorsCountPack count = core.getIndicatorsQuantity();
    Ui::indicator *ui;
    QButtonGroup *buttonGroup;
private:
    restart* restartWindow = nullptr;
    errorWindow* errorwindow = nullptr;
};

#endif // INDICATOR_H
