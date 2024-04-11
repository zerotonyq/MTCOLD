
#ifndef INDICATORMANAGER_H
#define INDICATORMANAGER_H

#include "qlabel.h"
#include <QObject>
#include <QButtonGroup>
#include <QVBoxLayout>

class IndicatorManager : public QObject
{
    Q_OBJECT
public:
    IndicatorManager(QButtonGroup *buttonGroup, QLabel *indicatorCountLabel, QWidget *parentWidget);

public slots:
    void onButtonClicked(QAbstractButton* button);
    void updateIndicatorCount(int count);

private:
    QButtonGroup *m_buttonGroup;
    QLabel *m_indicatorCountLabel;
    QVBoxLayout *m_layout;
};

#endif // INDICATORMANAGER_H
