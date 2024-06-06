#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>
#include "qbuttongroup.h"
#include "qlabel.h"
#include "../../Core/include/core.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>

namespace Ui {
class indicatorwidget;
}

class indicatorwidget : public QWidget
{
    Q_OBJECT

public:
    explicit indicatorwidget(Core *core_, quint32 numberOfIndicator, quint32 ma, QWidget *parent = nullptr);
    ~indicatorwidget();

    void setIndicatorName(const QString &name);
    void setInfoText(const QString &text);
    void showInfoButton();
    void hideInfoButton();
    quint32 numberOfIndicator;

private slots:
    void infoButtonClicked();
    void toggleClicked(int state);
    void onButtonGroupClicked(QAbstractButton *button);

private:
    Ui::indicatorwidget *ui;

    quint32 current_ma;

    Core *core;

    QButtonGroup *buttonGroup;
    QString infoText;
    quint16 stateOfToggle = 0;

signals:
    void infoTextChanged(const QString &text);
    void maWhenIndicatorOff(quint32 ma_value, quint32 indicator);
};

#endif // INDICATORWIDGET_H
