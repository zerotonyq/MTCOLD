#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>

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

private:
    Ui::indicatorwidget *ui;
};

#endif // INDICATORWIDGET_H

