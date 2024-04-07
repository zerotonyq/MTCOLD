#ifndef INDICATOR_H
#define INDICATOR_H

#include "qabstractbutton.h"
#include <QDialog>

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
    void onButtonClicked(QAbstractButton* button);

private:
    Ui::indicator *ui;
    QButtonGroup *buttonGroup;

};

#endif // INDICATOR_H
