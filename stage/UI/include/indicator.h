#ifndef INDICATOR_H
#define INDICATOR_H

#include "errorwindow.h"
#include "indicatormanager.h"
#include "macaddress.h"
#include "qabstractbutton.h"
#include "restart.h"
#include "connectcore.h"
#include <QDialog>
#include "../UI_Module/ui_indicator.h"


namespace Ui {
class indicator;
}

class indicator : public QDialog
{
    Q_OBJECT

public:

    explicit indicator(QWidget *parent = nullptr);
    ~indicator();

private slots:
    void on_build_clicked();
    void on_mistakes_clicked();
    void on_macAddress_clicked();

private:
    ConnectCore *core;
    quint32 indicatorsQuantity;

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
    void onValueChanged(int newValue);

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void valueChanged(int newValue);
    void infoTextChanged(const QString &text);

private slots:
    void onInfoTextChanged(const QString &text);
};
#endif // INDICATOR_H
