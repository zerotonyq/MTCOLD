#ifndef INDICATORMANAGER_H
#define INDICATORMANAGER_H

#include <QObject>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include "indicatorwidget.h"

class IndicatorManager : public QObject
{
    Q_OBJECT

public:
    explicit IndicatorManager(QButtonGroup *buttonGroup, QLabel *indicatorCountLabel, QWidget *indicatorCentralWidget);
    ~IndicatorManager();

    void updateIndicatorCount(int count);

public slots:
    void addIndicatorWidget(QWidget *indicatorWidget);

private:
    QButtonGroup *m_buttonGroup;
    QLabel *m_indicatorCountLabel;
    QVBoxLayout *m_layout;
    QWidget *m_indicatorCentralWidget;
};

#endif // INDICATORMANAGER_H
