#ifndef INDICATOR_H
#define INDICATOR_H

#include "errorwindow.h"
#include "indicatormanager.h"
#include "macaddress.h"
#include "qabstractbutton.h"
#include "restart.h"
#include "../../Core/include/core.h"
#include "../../Core/include/Packets.h"
#include <QDialog>
#include "../UI_Module/ui_indicator.h"
#include <QWidget>
#include <QObject>


namespace Ui {
class indicator;
}

class indicator : public QDialog
{
    Q_OBJECT

public:
    Core *core;
    explicit indicator(Core *core_, QWidget *parent = nullptr);
    ~indicator();

    quint32 currentIndicatorsQuantity = 0;
    quint32 currentIndicatorNumber = 0;
    quint64 SerialNumber   ;
    quint32 type           ;
    quint32 power          ;
    quint32 color          ;
    quint32 current_ma     ;
    quint32 reserve        ;
    quint64 error_code     ;

private slots:
    void on_build_clicked();
    void on_mistakes_clicked();
    void on_macAddress_clicked();

private:

    Ui::indicator *ui;

    QButtonGroup *buttonGroup;
    QWidget *m_indicatorContainerWidget;
    QLabel *infoLabel;
    QVector<indicatorwidget*> indicators;
    indicatorwidget *activeInfoButton;
    restart* restartWindow = nullptr;
    errorWindow* errorwindow = nullptr;
    macaddress* macAddress = nullptr;
    IndicatorManager* m_indicatorManager;
    indicatorwidget *m_activeIndicatorWidget = nullptr;
    indicatorwidget *activeIndicator = nullptr;

    void errorFlashing();

public slots:
    void onValueChanged(quint32 newValue);
    void updateIndicatorInfo();
    void updateQuantity();

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void valueChanged(int newValue);
    void infoTextChanged(const QString &text);
    void ma_exceeded(quint32 ma_value, quint32 indicator);
    //void maWhenIndicatorOff(quint32 ma_value, quint32 indicator);

private slots:
    void onInfoTextChanged(quint32 currentIndicatorNumber, indicatorwidget *indicator);
    void on_restart_clicked();
};
#endif // INDICATOR_H
