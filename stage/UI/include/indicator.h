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


namespace Ui {
class indicator;
}

class indicator : public QDialog
{
    Q_OBJECT

public:
    Core core;
    explicit indicator(quint32 count, QWidget *parent = nullptr);
    ~indicator();

    quint32 currentIndicatorsQuantity = 0;

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

    void errorFlashing();

public slots:
    void onValueChanged(quint32 newValue);

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void valueChanged(int newValue);
    void infoTextChanged(const QString &text);

private slots:
    void onInfoTextChanged(const QString &text);
//    void onInfoTextChanged(const sIndicatorStatisticsPack& indicatorStatisticsPack);
};
#endif // INDICATOR_H
