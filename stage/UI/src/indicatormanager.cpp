#include "../include/indicatormanager.h"
#include "qcheckbox.h"
#include <QAbstractButton>
#include <QFont>
#include <QFontMetrics>

IndicatorManager::IndicatorManager(QButtonGroup *buttonGroup, QLabel *indicatorCountLabel, QWidget *indicatorCentralWidget)
    : QObject(indicatorCentralWidget){}

IndicatorManager::~IndicatorManager()
{
    delete m_layout;
}
void IndicatorManager::addIndicatorWidget(QWidget *indicatorWidget)
{
    m_layout->addWidget(indicatorWidget);
}

