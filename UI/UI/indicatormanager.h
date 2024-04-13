#ifndef INDICATORMANAGER_H
#define INDICATORMANAGER_H

#include <QObject>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include "indicatorwidget.h"
#include "qscrollarea.h"

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
    QScrollArea *m_scrollArea;
    QButtonGroup *m_buttonGroup;
    QLabel *m_indicatorCountLabel;
    QWidget *m_indicatorCentralWidget;
    QVBoxLayout *m_layout;
};

#endif // INDICATORMANAGER_H
