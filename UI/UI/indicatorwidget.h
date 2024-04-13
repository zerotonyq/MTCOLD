#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>

class IndicatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IndicatorWidget(const QString& text, QWidget *parent = nullptr);

    void setIndicatorName(const QString &name);

private:
         // Добавьте необходимые элементы дизайна для индикатора (название, кнопки и т. д.)
};

#endif // INDICATORWIDGET_H
