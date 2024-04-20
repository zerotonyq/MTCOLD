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

public slots:
    void addIndicatorWidget(QWidget *indicatorWidget);

private:

    QVBoxLayout *m_layout;
};

#endif // INDICATORMANAGER_H
