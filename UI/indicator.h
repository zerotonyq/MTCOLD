#ifndef INDICATOR_H
#define INDICATOR_H

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

    void on_info0_clicked();

    void on_info0_2_clicked();

private:
    Ui::indicator *ui;

// private slots:
//     void onButtonClicked(QAbstractButton* button);


};

#endif // INDICATOR_H
