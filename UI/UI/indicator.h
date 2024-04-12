#ifndef INDICATOR_H
#define INDICATOR_H

#include "errorwindow.h"
#include "indicatormanager.h"
#include "qabstractbutton.h"
#include "restart.h"
#include "../core/scr/core.h"
#include "../core/scr/Pockets.h"
#include <QDialog>
#include "ui_indicator.h"

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

private:
    IndicatorManager* m_indicatorManager;

public slots:
    void onValueChanged(int newValue);

protected:
    void showEvent(QShowEvent *event) override;

};

#endif // INDICATOR_H
