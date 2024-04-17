#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>
#include "qbuttongroup.h"
#include "qlabel.h"

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
    explicit indicatorwidget(QWidget *parent = nullptr);
    ~indicatorwidget();
    void setIndicatorName(const QString &name);

private slots:
    void infoButtonClicked();
    void onButtonGroupClicked(QAbstractButton *button);

private:
    Ui::indicatorwidget *ui;
    QButtonGroup *buttonGroup;
    QLabel *infoLabel;
    QDialog *infoDialog;
};

#endif // INDICATORWIDGET_H

